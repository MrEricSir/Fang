#include "FangApp.h"

#include <QDebug>
#include <QDeclarativeEngine>

#include "../utilities/Utilities.h"

#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"
#include "operations/AddFeedOperation.h"
#include "operations/RemoveFeedOperation.h"
#include "operations/FaviconUpdateOperation.h"
#include "operations/UpdateTitleOperation.h"

FangApp* FangApp::_instance = NULL;

FangApp::FangApp(QObject *parent, FangApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    manager(this),
    currentFeed(NULL),
    loadAllFinished(false),
    fangSettings(NULL),
    interactor(NULL)
{
    Q_ASSERT(_instance == NULL);
    _instance = this;
    
    // Create the list of feeds.
    feedList = new ListModel(new FeedItem, this);
    
    // Setup signals.
    connect(viewer, SIGNAL(statusChanged(QDeclarativeView::Status)),
                     this, SLOT(onViewerStatusChanged(QDeclarativeView::Status)));
    connect(viewer, SIGNAL(windowResized()), this, SLOT(onWindowResized()));
    
    connect(&manager, SIGNAL(operationFinished(Operation*)),
                     this, SLOT(onOperationFinished(Operation*)));
    
    connect(feedList, SIGNAL(added(ListItem*)), this, SLOT(onFeedAdded(ListItem*)));
    connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
    connect(feedList, SIGNAL(selectedChanged(ListItem*)), this, SLOT(onFeedSelected(ListItem*)));
}

void FangApp::init()
{
    viewer->rootContext()->setContextProperty("feedListModel", feedList); // list of feeds
    viewer->rootContext()->setContextProperty("platform", getPlatform()); // platform string ID
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
    
    return (FeedItem*) item;
}

void FangApp::onViewerStatusChanged(QDeclarativeView::Status status)
{
    if (status != QDeclarativeView::Ready)
        return;
    
    // OH! We're ready! Well I'll be damned. Grab all the stuff from 
    interactor = viewer->rootObject()->findChild<WebInteractor*>("webInteractor");
    fangSettings = viewer->rootObject()->findChild<FangSettings*>("fangSettings");
    
    // Do a sanity check.
    if (interactor == NULL || fangSettings == NULL) {
        qDebug() << "Could not find QML objects!!!11";
        
        return;
    }
    
    // Init interactor with Mr. Manager.
    interactor->init(&manager);
}

void FangApp::onWindowResized()
{

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
    
    connectFeed(feed);
    
    // Update the feed.
    if (feed->getDbId() > 0) {
        manager.add(new UpdateFeedOperation(&manager, feed));
        manager.add(new FaviconUpdateOperation(&manager, feed));
    }
}

void FangApp::onFeedRemoved(ListItem * listItem)
{
    FeedItem* item = qobject_cast<FeedItem *>(listItem);
    if (item != NULL) {
        disconnectFeed(item);
        item->deleteLater(); // Well, bye.
    }
}

void FangApp::onFeedSelected(ListItem* _item) {
    FeedItem* item = qobject_cast<FeedItem *>(_item);
    setCurrentFeed(item);
}

void FangApp::connectFeed(FeedItem *feed)
{
    connect(feed, SIGNAL(titleChanged()), this, SLOT(onFeedTitleChanged()));
}

void FangApp::disconnectFeed(FeedItem *feed)
{
    disconnect(feed, SIGNAL(titleChanged()), this, SLOT(onFeedTitleChanged()));
}

void FangApp::onLoadAllFinished(Operation *op)
{
    Q_UNUSED(op);
    loadAllFinished = true;
    displayFeed();
}

void FangApp::displayFeed()
{
    if (currentFeed != NULL)
        interactor->setFeed(currentFeed);
}

void FangApp::setCurrentFeed(FeedItem *feed)
{
    qDebug() << "You've set the feed to "<< (feed != NULL ? feed->getTitle() : "(null)");
    
    currentFeed = feed;
    displayFeed();
}

void FangApp::onFeedTitleChanged()
{
    // The sender is the feed itself, so grab it and do a DB update.
    FeedItem* feed = qobject_cast<FeedItem *>(sender());
    if (feed == NULL)
        return;
    
    manager.add(new UpdateTitleOperation(&manager, feed));
}

QString FangApp::getPlatform()
{
#if defined(Q_OS_MAC)
    return "MAC";
#elif defined(Q_OS_WIN)
    return "WIN";
#elif defined(Q_OS_IOS)
    return "IOS";
#elif defined(Q_OS_ANDROID)
    return "ANDROID";
#elif defined(Q_OS_LINUX) // Should be near last
    return "LINUX";
#elif defined(Q_OS_UNIX)  // Should be next-to last
    return "UNIX";
#else                     // Must be last!
    Q_ASSERT(false);
    return "UNKNOWN";
#endif
}

FangApp* FangApp::instance()
{
    Q_ASSERT(_instance != NULL);
    return _instance;
}

void FangApp::addFeed(const QUrl &feedURL, const QUrl &imageURL, QString siteTitle)
{
    //qDebug() << "Add feed " << siteTitle << " " << feedURL;
    manager.add(new AddFeedOperation(&manager, feedList, feedURL, imageURL, siteTitle));
}

void FangApp::removeFeed(FeedItem *feed)
{
    // Say goodbye to these (feeds), Michael.
    //qDebug() << "remove feed";
    manager.add(new RemoveFeedOperation(&manager, feed, feedList));
}

