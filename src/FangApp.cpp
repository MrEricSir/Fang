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

FangApp::FangApp(QObject *parent, FangApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    manager(this),
    newsWeb(),
    currentFeed(NULL),
    loadAllFinished(false)
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
    viewer->displayWindow();
    
    // Enable cache for remote QML elements.
    Utilities::addNetworkAccessManagerCache(viewer->engine()->networkAccessManager());
    
    // Load feed list.
    LoadAllFeedsOperation* loadAllOp = new LoadAllFeedsOperation(&manager, feedList);
    connect(loadAllOp, SIGNAL(finished(Operation*)), this, SLOT(onLoadAllFinished(Operation*)));
    manager.add(loadAllOp);
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
        
        if (!newsWeb.isReady())
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
    displayFeed();
}

void FangApp::onNewsItemBookmarked(NewsItem *item)
{
    manager.add(new SetBookmarkOperation(&manager, item->getFeed(), item));
    qDebug() << "Item bookmarked: " << item->getTitle();
}

void FangApp::onFeedSelected(ListItem* _item) {
    FeedItem* item = qobject_cast<FeedItem *>(_item);
    if (item != NULL) {
        if (currentFeed != NULL)
            currentFeed->setIsCurrent(false);
        
        setCurrentFeed(item);
        
        // Connex0r the signals.
        //qDebug() << "Selected: " << feed->getTitle();
    } else {
        // How did this happen?!
        setCurrentFeed(NULL);
    }
}

void FangApp::onLoadAllFinished(Operation *op)
{
    Q_UNUSED(op);
    loadAllFinished = true;
    displayFeed();
}

// Note: newsWeb MUST be ready and currentFeed MUST not be null and the LoadAll operation MUST
// be finished before this operation can do jack.  Got that?  Well, do ya punk?
void FangApp::displayFeed()
{
    if (currentFeed == NULL || !newsWeb.isReady() || !loadAllFinished)
        return;
    
    if (newsWeb.getCurrentFeed() != currentFeed)
        currentFeed->setIsCurrent(true);
    
    newsWeb.setFeed(currentFeed);
}

void FangApp::setCurrentFeed(FeedItem *feed)
{
    // Disconnect signals.
    if (currentFeed != NULL) {
        disconnect(currentFeed, SIGNAL(bookmarkChanged(NewsItem*)),
                   this, SLOT(onNewsItemBookmarked(NewsItem*)));
    }
    
    currentFeed = feed;
    displayFeed();
    
    // Connect signals.
    if (currentFeed != NULL) {
        connect(currentFeed, SIGNAL(bookmarkChanged(NewsItem*)),
                this, SLOT(onNewsItemBookmarked(NewsItem*)));
    }
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

