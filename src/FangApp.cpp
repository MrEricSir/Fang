#include "FangApp.h"

#include <QDebug>
#include <QDeclarativeEngine>

#include "../utilities/Utilities.h"

#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"
#include "operations/AddFeedOperation.h"
#include "operations/RemoveFeedOperation.h"
#include "operations/SetBookmarkOperation.h"
#include "operations/FaviconUpdateOperation.h"

#include "models/ScrollReader.h"

FangApp* FangApp::_instance = NULL;

FangApp::FangApp(QObject *parent, QmlApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    manager(this),
    newsWeb(),
    currentFeed(NULL)
{
    Q_ASSERT(_instance == NULL);
    _instance = this;
    
    // Create the list of feeds.
    feedList = new ListModel(new FeedItem, this);
    
    // Setup signals.
    connect(viewer, SIGNAL(statusChanged(QDeclarativeView::Status)),
                     this, SLOT(onViewerStatusChanged(QDeclarativeView::Status)));
    
    connect(&manager, SIGNAL(operationFinished(Operation*)),
                     this, SLOT(onOperationFinished(Operation*)));
    
    connect(&newsWeb, SIGNAL(ready()), this, SLOT(onNewsWebReady()));
    connect(&newsWeb, SIGNAL(newsItemBookmarked(NewsItem*)),
            this, SLOT(onNewsItemBookmarked(NewsItem*)));
    
    connect(feedList, SIGNAL(added(ListItem*)), this, SLOT(onFeedAdded(ListItem*)));
    connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
    connect(feedList, SIGNAL(selectedChanged(ListItem*)), this, SLOT(onFeedSelected(ListItem*)));
}

void FangApp::init()
{
    viewer->rootContext()->setContextProperty("feedListModel", feedList);
    viewer->addImportPath(QLatin1String("modules"));
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer->showExpanded();
    
    // Enable cache for remote QML elements.
    Utilities::addNetworkAccessManagerCache(viewer->engine()->networkAccessManager());
    
    // Load feed list.
    manager.add(new LoadAllFeedsOperation(&manager, feedList));
}

FeedItem* FangApp::getFeed(int index) {
    void* item = feedList->row(index);
    if (item == NULL) {
        qDebug() << "Feed #" << index << " was NULL";
        
        return NULL;
    }
                                //.data();
    return (FeedItem*) item;
}

void FangApp::onViewerStatusChanged(QDeclarativeView::Status status)
{
    if (status == QDeclarativeView::Ready) {
        QDeclarativeWebView *webView = viewer->rootObject()->findChild<QDeclarativeWebView*>("newsView");
        ScrollReader *scrollReader = viewer->rootObject()->findChild<ScrollReader*>("newsViewScrollReader");
        if (webView == NULL || scrollReader == NULL) {
            qDebug() << "Could not find objects: " << webView << " " << scrollReader;
            
            return;
        }
        
        newsWeb.init(webView, scrollReader); // Start the news!
    }
}

void FangApp::onOperationFinished(Operation *operation)
{
    if (operation->metaObject() == &LoadAllFeedsOperation::staticMetaObject) {
        // Data is loaded!
    }
}

void FangApp::onFeedAdded(ListItem *item)
{
    FeedItem* feed = qobject_cast<FeedItem *>(item);
    if (feed == NULL) {
        qDebug() << "Null feed was added!";
        
        return;
    }
    
    // Update the feed.
    if (feed->getDbId() > 0) {
        manager.add(new UpdateFeedOperation(&manager, feed));
        manager.add(new FaviconUpdateOperation(&manager, feed));
    }
}

void FangApp::onFeedRemoved(ListItem * listItem)
{
    FeedItem* item = qobject_cast<FeedItem *>(listItem);
    if (item != NULL)
        item->deleteLater(); // Well, bye.
}

void FangApp::onNewsWebReady()
{
    if (currentFeed != NULL)
        displayFeed();
}

void FangApp::onNewsItemBookmarked(NewsItem *item)
{
    if (currentFeed == NULL) {
        qDebug() << "Current feed was null, can't bookmark.";
        return;
    }
    
    manager.add(new SetBookmarkOperation(&manager, currentFeed, item));
    qDebug() << "Item bookmarked: " << item->getTitle();
}

void FangApp::onFeedSelected(ListItem* _item) {
    FeedItem* item = qobject_cast<FeedItem *>(_item);
    if (item != NULL) {
        currentFeed = item;
        if (newsWeb.isReady())
            displayFeed();
        
        // Connex0r the signals.
        //qDebug() << "Selected: " << feed->getTitle();
    } else {
        // How did this happen?!
        currentFeed = NULL;
    }
}

// Note: newsWeb MUST be ready and currentFeed MUST not be null before
// this method is called.  Got that?  Well, do ya punk?
void FangApp::displayFeed() {
    if (currentFeed == NULL || !newsWeb.isReady())
        return;
    
    newsWeb.setFeed(currentFeed);
}

FangApp* FangApp::instance()
{
    Q_ASSERT(_instance != NULL);
    return _instance;
}

void FangApp::addFeed(const QUrl &feedURL, const QUrl &imageURL, QString siteTitle)
{
    qDebug() << "Add feed " << siteTitle << " " << feedURL;
    manager.add(new AddFeedOperation(&manager, feedList, feedURL, imageURL, siteTitle));
}

void FangApp::removeFeed(FeedItem *feed)
{
    // Say goodbye to these (feeds), Michael.
    //qDebug() << "remove feed";
    manager.add(new RemoveFeedOperation(&manager, feed, feedList));
}

