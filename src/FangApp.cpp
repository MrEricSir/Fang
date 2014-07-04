#include "FangApp.h"

#include <QDebug>

#include "utilities/Utilities.h"

#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"
#include "operations/AddFeedOperation.h"
#include "operations/RemoveFeedOperation.h"
#include "operations/UpdateTitleOperation.h"

FangApp* FangApp::_instance = NULL;

FangApp::FangApp(QObject *parent, QQmlApplicationEngine* engine) :
    FangObject(parent),
    engine(engine),
    manager(this),
    feedList(new ListModel(new FeedItem, this)),
    importList(new ListModel(new FeedItem, this)),
    currentFeed(NULL),
    loadAllFinished(false),
    fangSettings(NULL),
    interactor(NULL),
    updateTimer(new QTimer(this)),
    window(NULL)
{
    Q_ASSERT(_instance == NULL);
    _instance = this;
    
    // Setup signals.
    connect(engine, SIGNAL(objectCreated(QObject*,QUrl)), this, SLOT(onObjectCreated(QObject*,QUrl)));
    
    connect(feedList, SIGNAL(added(ListItem*)), this, SLOT(onFeedAdded(ListItem*)));
    connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
    connect(feedList, SIGNAL(selectedChanged(ListItem*)), this, SLOT(onFeedSelected(ListItem*)));
}

void FangApp::init()
{
    // Setup our QML.
    engine->rootContext()->setContextProperty("feedListModel", feedList); // list of feeds
    engine->rootContext()->setContextProperty("importListModel", importList); // list of feeds to be batch imported
    engine->rootContext()->setContextProperty("platform", getPlatform()); // platform string ID
    
    // Load feed list.
    LoadAllFeedsOperation* loadAllOp = new LoadAllFeedsOperation(&manager, feedList);
    connect(loadAllOp, SIGNAL(finished(Operation*)), this, SLOT(onLoadAllFinished(Operation*)));
    manager.add(loadAllOp);
}

FeedItem* FangApp::getFeed(int index)
{
    void* item = feedList->row(index);
    if (item == NULL) {
        qDebug() << "Feed #" << index << " was NULL";
        
        return NULL;
    }
    
    return (FeedItem*) item;
}

FeedItem *FangApp::getFeedForID(qint64 dbID)
{
    QMap<qint64, FeedItem*>::iterator it = feedIdMap.find(dbID);
    if (it == feedIdMap.end()) {
        qDebug() << "Um, we didn't find a feed for id: " << dbID;
        return NULL;
    }
    
    return it.value();
}

void FangApp::focusApp()
{
    if (window) {
        window->requestActivate();
    }
}

void FangApp::onFeedAdded(ListItem *item)
{
    FeedItem* feed = qobject_cast<FeedItem *>(item);
    if (feed == NULL) {
        qDebug() << "Null feed was added!";
        
        return;
    }
    
    feedIdMap.insert(feed->getDbId(), feed);
    
    // Hook up signals.
    connectFeed(feed);
    
    if (!feed->isAllNews() && loadAllFinished) {
        // Not all news, so trigger an update.
        // TODO: Handle folders.
        interactor->refreshFeed(feed);
    }
}

void FangApp::onFeedRemoved(ListItem * listItem)
{
    FeedItem* item = qobject_cast<FeedItem *>(listItem);
    if (item != NULL) {
        disconnectFeed(item);
        feedIdMap.take(item->getDbId());
        item->deleteLater(); // Well, bye.
    }
}

void FangApp::onFeedSelected(ListItem* _item)
{
    qDebug() << "New feed selected";
    FeedItem* item = qobject_cast<FeedItem *>(_item);
    setCurrentFeed(item);
}

void FangApp::onNewFeedAddedSelect(Operation* addFeedOperation)
{
    AddFeedOperation* op = qobject_cast<AddFeedOperation*>(addFeedOperation);
    Q_ASSERT(op != NULL);
    
    // Tell me about it.
    //qDebug() << "You should select: " << op->getFeedItem()->getTitle();
    feedList->setSelected(op->getFeedItem());
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
    
    // Load teh cue em el.
    engine->load(QUrl("qrc:///qml/main.qml"));
}

void FangApp::updateAllFeeds()
{
    if (feedList == NULL || feedList->rowCount() == 0 || interactor == NULL)
        return; // Somehow this was called too early.
    
    interactor->refreshAllFeeds();
}

void FangApp::onObjectCreated(QObject* object, const QUrl& url)
{
    Q_UNUSED(url);
    //qDebug() << "Object created: " << object << " with url: " << url;
    
    // Save our window.
    window = qobject_cast<QQuickWindow*>(object);
    
    interactor = object->findChild<WebInteractor*>("webInteractor");
    fangSettings = object->findChild<FangSettings*>("fangSettings");
    
    // Do a sanity check.
    if (interactor == NULL || fangSettings == NULL) {
        qDebug() << "Could not find QML objects!!!11";
        
        return;
    }
    
    // Show the current feed.
    displayFeed();
    
    // Init interactor with Mr. Manager, our list of feeds, and the settings.
    interactor->init(&manager, feedList, fangSettings);
    
    // Update!.
    updateAllFeeds();
    
    // Set a timer to update the feeds every ten minutes.
    // TODO: Customize news update timer frequency.
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateAllFeeds()));
    updateTimer->start(10 * 60 * 1000);
}

void FangApp::displayFeed()
{
    if (currentFeed && interactor) {
        interactor->setFeed(currentFeed);
    }
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

void FangApp::addFeed(const QUrl &feedURL, const RawFeed* rawFeed, bool switchTo)
{
    //qDebug() << "Add feed " << siteTitle << " " << feedURL;
    AddFeedOperation* addOp = new AddFeedOperation(
                                  &manager, feedList, feedURL, rawFeed);
    
    if (switchTo) {
        connect(addOp, SIGNAL(finished(Operation*)),
                this, SLOT(onNewFeedAddedSelect(Operation*)));
    }
    
    manager.add(addOp);
}

void FangApp::removeFeed(FeedItem *feed)
{
    // Say goodbye to these (feeds), Michael.
    //qDebug() << "remove feed";
    manager.add(new RemoveFeedOperation(&manager, feed, feedList));
}

