#include "FangApp.h"
#include <QDebug>
#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"

FangApp::FangApp(QObject *parent, QmlApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    manager(this),
    newsWeb(),
    currentFeed(NULL)
{
    // Create the list of feeds.
    feedList = new ListModel(new FeedItem, this);
    
    // Setup signals.
    QObject::connect(viewer, SIGNAL(statusChanged(QDeclarativeView::Status)),
                     this, SLOT(onViewerStatusChanged(QDeclarativeView::Status)));
    
    QObject::connect(&manager, SIGNAL(operationFinished(Operation*)),
                     this, SLOT(onOperationFinished(Operation*)));
    
    QObject::connect(&newsWeb, SIGNAL(ready()), this, SLOT(onNewsWebReady()));
    
    QObject::connect(feedList, SIGNAL(added(ListItem*)), this, SLOT(onFeedAdded(ListItem*)));
    QObject::connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
    QObject::connect(feedList, SIGNAL(selectedChanged(ListItem*)), this, SLOT(onFeedSelected(ListItem*)));
}

void FangApp::init()
{
    viewer->rootContext()->setContextProperty("feedListModel", feedList);
    viewer->addImportPath(QLatin1String("modules"));
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer->showExpanded();
    
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
        qDebug() << "View is ready";
        
        QDeclarativeWebView *webView = viewer->rootObject()->findChild<QDeclarativeWebView*>("newsView");
        if (webView == NULL) {
            qDebug() << "Could not find newsView";
            
            return;
        }
        
        newsWeb.init(webView);
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
    
    qDebug() << "Feed added: " << feed->getTitle();
    
    // Update the feed.
    if (feed->getDbId() > 0) // Only real feeds, plox.
        manager.add(new UpdateFeedOperation(&manager, feed));
}

void FangApp::onFeedRemoved(ListItem *)
{
    qDebug() << "Feed removed!";
}

void FangApp::onNewsWebReady()
{
    //qDebug() << "Your potatoes have arrived.";
    
    if (currentFeed != NULL)
        displayFeed();
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
        currentFeed = NULL;
    }
}

// Note: newsWeb MUST be ready and currentFeed MUST not be null before
// this method is called.  Got that?  Well, do ya punk?
void FangApp::displayFeed() {
    if (currentFeed == NULL || !newsWeb.isReady())
        return;
    
    newsWeb.clear();
    
    QList<NewsItem*>* list = currentFeed->getNewsList();
    
    for (int i = 0; i < list->size(); i++) {
        NewsItem* item = list->at(i);
        newsWeb.append(item);
    }
}

