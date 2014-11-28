#include "FangApp.h"

#include <QDebug>

#include "utilities/Utilities.h"

#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"
#include "operations/AddFeedOperation.h"
#include "operations/RemoveFeedOperation.h"
#include "operations/UpdateTitleOperation.h"

#if defined(Q_OS_MAC)
    #include "notifications/NotificationMac.h"
#elif defined(Q_OS_WIN)
    #include "notifications/NotificationWindows.h"
#endif

FangApp* FangApp::_instance = NULL;

FangApp::FangApp(QObject *parent, QQmlApplicationEngine* engine, SingleInstanceCheck* single) :
    FangObject(parent),
    engine(engine),
    single(single),
    manager(this),
    feedList(new ListModel(new FeedItem, this)),
    importList(new ListModel(new FeedItem, this)),
    currentFeed(NULL),
    loadAllFinished(false),
    fangSettings(NULL),
    interactor(NULL),
    updateTimer(new QTimer(this)),
    window(NULL),
    allNews(NULL),
    pinnedNews(NULL)
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
#ifdef QT_DEBUG
    bool isDebugBuild = true;
#else
    bool isDebugBuild = false;
#endif // QT_DEBUG
    engine->rootContext()->setContextProperty("isDebugBuild", isDebugBuild); // let QML know if we're a debug build or not
    //qDebug() << "Is debug build: " << isDebugBuild;
    
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
    
    if (!feed->isSpecialFeed() && loadAllFinished) {
        // Not special feed, so trigger an update.
        // TODO: Handle folders.
        refreshFeed(feed);
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

    // Find our special feeds.
    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList->row(i));
        if (item->getDbId() >=0)
            break; // We're done with special feeds.

        switch (item->getDbId()) {
        case FEED_ID_ALLNEWS:
            allNews = qobject_cast<AllNewsFeedItem*>(item);
            break;

        case FEED_ID_PINNED:
            pinnedNews = qobject_cast<PinnedFeedItem*>(item);
            break;

        default:
            Q_ASSERT(false); // You forgot to add the new special feed here.
        }
    }
    
    // Load teh cue em el.
    engine->load(QUrl("qrc:///qml/main.qml"));
}

void FangApp::updateAllFeeds()
{
    if (feedList == NULL || feedList->rowCount() == 0)
        return; // Somehow this was called too early.
    
    refreshAllFeeds();
}

void FangApp::refreshFeed(FeedItem *feed)
{
    Q_ASSERT(feed != NULL);
    
    QList<FeedItem*> feedsToUpdate;
    bool useCache = true; // Use cache by default.
    
    // Special handling for all news.
    // TODO: Handle folders
    if (feed->isSpecialFeed()) {
        // Update ALL the feeds.
        for (int i = 0; i < feedList->rowCount(); i++)
        {
            FeedItem* item = qobject_cast<FeedItem*>(feedList->row(i));
            Q_ASSERT(item != NULL);
            if (item->isSpecialFeed())
                continue; // Skip special feeds

            feedsToUpdate.append(item);
        }
        
        // Reset the "update all" timer.
        updateTimer->start();
    } else {
        feedsToUpdate.append(feed);
        useCache = false; // Don't check cache if we're just checking a single feed.
    }
    
    // Update 'em all!
    foreach(FeedItem* item, feedsToUpdate) {
        manager.add(new UpdateFeedOperation(&manager, item, NULL, useCache));
        manager.add(new FaviconUpdateOperation(&manager, item));
    }
}

void FangApp::refreshAllFeeds()
{
    // Use the "all news" trick (see above)
    refreshFeed(allNews);
}

void FangApp::refreshFeed(const qint64 id)
{
    refreshFeed(feedForId(id));
}

void FangApp::refreshCurrentFeed()
{
    if (NULL == currentFeed) {
        return;
    }
    
    refreshFeed(currentFeed);
}

FeedItem* FangApp::feedForId(const qint64 id)
{
    // Special feeds.
    if (id < 0) {
        switch (id) {
        case FEED_ID_ALLNEWS:
            return allNews;

        case FEED_ID_PINNED:
            return pinnedNews;

        default:
            Q_ASSERT(false); // You added a new special feed but forgot to update this switch
        }

        return NULL; // Should never make it this far.
    }

    // Plain ol' feeds.
    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != NULL);
        
        if (feed->getDbId() == id)
            return feed;
    }
    
    return NULL;
}

void FangApp::onObjectCreated(QObject* object, const QUrl& url)
{
    Q_UNUSED(url);
    //qDebug() << "Object created: " << object << " with url: " << url;
    
    // Save our window.
    window = qobject_cast<QQuickWindow*>(object);
    
    single->setWindow(window);
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
    
    // Grab the All News item.
    AllNewsFeedItem* allNews = qobject_cast<AllNewsFeedItem*>(feedList->row(0));
    
    // Notifications, activate!
#if defined(Q_OS_MAC)
    notifications = new NotificationMac(fangSettings, feedList,
                                        allNews, window, this);
#elif defined(Q_OS_WIN)
    notifications = new NotificationWindows(fangSettings, feedList,
                                            allNews, window, this);
#endif
    
    // Update!.
    updateAllFeeds();
    
    // Set a timer to update the feeds every ten minutes.
    // TODO: Customize news update timer frequency.
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateAllFeeds()));
    updateTimer->setInterval(10 * 60 * 1000);
    updateTimer->start();
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

