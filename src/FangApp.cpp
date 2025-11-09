#include "FangApp.h"

#include <QDebug>
#include <QImageReader>

#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"
#include "operations/AddFeedOperation.h"
#include "operations/RemoveFeedOperation.h"
#include "operations/UpdateOrdinalsOperation.h"
#include "operations/UpdateTitleOperation.h"
#include "operations/ExpireNewsOperation.h"
#include "operations/SetBookmarkOperation.h"
#include "operations/SetPinOperation.h"
#include "operations/LoadAllNewsOperation.h"
#include "operations/LoadFolderOperation.h"
#include "operations/LoadPinnedNewsOperation.h"
#include "operations/InsertFolderOperation.h"
#include "operations/MarkAllReadOrUnreadOperation.h"
#include "operations/FaviconUpdateOperation.h"
#include "src/models/NewsList.h"

#if defined(Q_OS_MAC)
    #include "notifications/NotificationMac.h"
#elif defined(Q_OS_WIN)
    #include "notifications/NotificationWindows.h"
#endif

FangApp* FangApp::_instance = nullptr;

FangApp::FangApp(QApplication *parent, QQmlApplicationEngine* engine, SingleInstanceCheck* single) :
    FangObject(parent),
    engine(engine),
    single(single),
    manager(this),
    windowHeight(0),
    feedList(new ListModel(new FeedItem, this)),
    importList(new ListModel(new FeedItem, this)),
    currentFeed(nullptr),
    loadAllFinished(false),
    fangSettings(nullptr),
    dbSettings(&manager),
    updateTimer(new QTimer(this)),
    window(nullptr),
    allNews(nullptr),
    pinnedNews(nullptr),
    isPinnedNewsVisible(true),
    isSettingBookmark(false),
    loadNewsInProgress(false),
    lastFeedSelected(nullptr)
{
    Q_ASSERT(_instance == nullptr);
    _instance = this;
    
    // Setup signals.
    connect(parent, &QApplication::aboutToQuit, this, &FangApp::onQuit);

    connect(engine, &QQmlApplicationEngine::objectCreated, this, &FangApp::onObjectCreated);
    
    connect(feedList, &ListModel::added, this, &FangApp::onFeedAdded);
    connect(feedList, &ListModel::removed, this, &FangApp::onFeedRemoved);
    connect(feedList, &ListModel::selectedChanged, this, &FangApp::onFeedSelected);

    connect(&newsServer, &NewsWebSocketServer::isLoadInProgressChanged, this,
            &FangApp::onLoadPageChanged);
}

void FangApp::init()
{
    qDebug() << "FangApp init version: " << APP_VERSION;
    qDebug() << "";

    qDebug() << "Image formats: " << QImageReader::supportedImageFormats();

    // Setup our QML.
    engine->rootContext()->setContextProperty("feedListModel", feedList); // list of feeds
    engine->rootContext()->setContextProperty("importListModel", importList); // list of feeds to be batch imported
    engine->rootContext()->setContextProperty("platform", getPlatform()); // platform string ID
    engine->rootContext()->setContextProperty("fangVersion", APP_VERSION);

#ifdef QT_DEBUG
    bool isDebugBuild = true;
#else
    bool isDebugBuild = false;
#endif // QT_DEBUG
    engine->rootContext()->setContextProperty("isDebugBuild", isDebugBuild); // let QML know if we're a debug build or not
    //qDebug() << "Is debug build: " << isDebugBuild;
    
    // Load feed list.
    LoadAllFeedsOperation* loadAllOp = new LoadAllFeedsOperation(&manager, feedList);
    connect(loadAllOp, &LoadAllFeedsOperation::finished, this, &FangApp::onLoadAllFinished);
    manager.add(loadAllOp);
}

FeedItem* FangApp::getFeed(qsizetype index)
{
    void* item = feedList->row(index);
    if (item == nullptr) {
        qDebug() << "Feed #" << index << " was NULL";
        
        return nullptr;
    }
    
    return (FeedItem*) item;
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
    if (feed == nullptr) {
        qDebug() << "Null feed was added!";
        
        return;
    }

    feedIdMap.insert(feed->getDbID(), feed);
    
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
    if (item != nullptr) {
        disconnectFeed(item);
        feedIdMap.take(item->getDbID());

        if (!item->isSpecialFeed()) {
            item->deleteLater(); // Well, bye.
        }
    }
}

void FangApp::onFeedSelected(ListItem* _item)
{
    //qDebug() << "New feed selected";
    FeedItem* item = qobject_cast<FeedItem *>(_item);
    setCurrentFeed(item);
    lastFeedSelected = item;
}

void FangApp::onLoadPageChanged()
{
    static bool first = false;
    if (!first && !newsServer.isLoadInProgress()) {
        first = true;

        // Perform first feed update!
        updateAllFeeds();
    }
}

void FangApp::onNewFeedAddedSelect(Operation* addFeedOperation)
{
    AddFeedOperation* op = qobject_cast<AddFeedOperation*>(addFeedOperation);
    Q_ASSERT(op != nullptr);
    
    // Tell me about it.
    //qDebug() << "You should select: " << op->getFeedItem()->getTitle();
    feedList->setSelected(op->getFeedItem());
}

void FangApp::connectFeed(FeedItem *feed)
{
    connect(feed, &FeedItem::titleChanged, this, &FangApp::onFeedTitleChanged);
}

void FangApp::disconnectFeed(FeedItem *feed)
{
    disconnect(feed, &FeedItem::titleChanged, this, &FangApp::onFeedTitleChanged);
}

void FangApp::onLoadAllFinished(Operation *op)
{
    Q_UNUSED(op);
    loadAllFinished = true;

    // Find our special feeds.
    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList->row(i));
        if (item->getDbID() >=0) {
            break; // We're done with special feeds.
        }

        switch (item->getDbID()) {
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

    // We get signal.
    connect(pinnedNews, &PinnedFeedItem::dataChanged, this, &FangApp::pinnedNewsWatcher);

    // This has to be manually invoked the first time.
    pinnedNewsWatcher();
    
    // Load teh cue em el.
    engine->load(QUrl("qrc:///qml/main.qml"));
}

void FangApp::updateAllFeeds()
{
    if (feedList == nullptr || feedList->rowCount() == 0) {
        return; // Somehow this was called too early.
    }
    
    refreshAllFeeds();
}

void FangApp::refreshFeed(FeedItem *feed)
{
    Q_ASSERT(feed != nullptr);
    
    QList<FeedItem*> feedsToUpdate;
    bool useCache = true; // Use cache by default.
    
    // Special handling for all news.
    if (feed->isSpecialFeed()) {
        // Update ALL the feeds.
        for (int i = 0; i < feedList->rowCount(); i++)
        {
            FeedItem* item = qobject_cast<FeedItem*>(feedList->row(i));
            Q_ASSERT(item != nullptr);
            if (item->isSpecialFeed() || item->isFolder()) {
                continue; // Skip special feeds and folders.
            }

            feedsToUpdate.append(item);
        }
        
        // Reset the "update all" timer.
        updateTimer->start();
    } else if (feed->isFolder()) {
        // Update the feeds in this folder.
        qint64 folderID = feed->getDbID();
        for (int i = 0; i < feedList->rowCount(); i++)
        {
            FeedItem* item = qobject_cast<FeedItem*>(feedList->row(i));
            Q_ASSERT(item != nullptr);
            if (item->getParentFolderID() == folderID) {
                feedsToUpdate.append(item);
            }
        }

    } else {
        feedsToUpdate.append(feed);
        useCache = false; // Don't check cache if we're just checking a single feed.
    }
    
    // Update 'em all!
    for (FeedItem* item : feedsToUpdate) {
        manager.add(new UpdateFeedOperation(&manager, item, nullptr, useCache));
        manager.add(new FaviconUpdateOperation(&manager, item));
    }
}

void FangApp::refreshAllFeeds()
{
    // Use the "all news" trick (see above)
    refreshFeed(allNews);
}

void FangApp::refreshCurrentFeed()
{
    if (nullptr == currentFeed) {
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

        return nullptr; // Should never make it this far.
    }

    // Plain ol' feeds.
    for (int i = 0; i < feedList->rowCount(); ++i) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != nullptr);
        
        if (feed->getDbID() == id) {
            return feed;
        }
    }
    
    return nullptr;
}

void FangApp::setBookmark(qint64 id, bool allowBackward)
{
    if (isSettingBookmark || nullptr == currentFeed) {
        // qDebug() << "Cannot set bookmark to (early exit): " << id;
        return;
    }

    if (!currentFeed->canBookmark(id, allowBackward)) {
        isSettingBookmark = false;
        // qDebug() << "Cannot set bookmark to: " << id;

        return;
    }

    // I bookmark you!
    SetBookmarkOperation* bookmarkOp = new SetBookmarkOperation(
        &manager, currentFeed, currentFeed->getNewsList()->newsItemForID(id));
    isSettingBookmark =  true;
    connect(bookmarkOp, &SetBookmarkOperation::finished, this, &FangApp::onSetBookmarkFinished);
    manager.add(bookmarkOp);
}

void FangApp::setPin(qint64 id, bool pin)
{
    qDebug() << "Someone wants to " << (pin ? "pin: " : "unpin: ") << id;
    if (nullptr == currentFeed) {
        return;
    }

    PinnedFeedItem* pinnedNews = qobject_cast<PinnedFeedItem*>(feedForId(FEED_ID_PINNED));

    SetPinOperation* pinOp = new SetPinOperation(&manager, pinnedNews, id, pin);
    connect(pinOp, &SetPinOperation::finished, this, &FangApp::onSetPinFinished);
    manager.add(pinOp);
}

void FangApp::removeAndDelete(bool fromStart, qsizetype numberToRemove)
{
    if (!currentFeed) {
        return;
    }

    currentFeed->getNewsList()->removeAndDelete(fromStart, numberToRemove);
}

void FangApp::onObjectCreated(QObject* object, const QUrl& url)
{
    Q_UNUSED(url);
    //qDebug() << "Object created: " << object << " with url: " << url;
    
    // Save our window.
    window = qobject_cast<QQuickWindow*>(object);
    
    single->setWindow(window);
    fangSettings = object->findChild<FangSettings*>("fangSettings");
    
    // Do a sanity check.
    if (fangSettings == nullptr) {
        qDebug() << "Could not find QML objects!!!11";
        
        return;
    }

    // Init settings.
    fangSettings->init(&dbSettings);

    // Init WebSocket server.
    newsServer.init(fangSettings);
    
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
    
    // Setup the feed refresh timer.
    setRefreshTimer();
    connect(updateTimer, &QTimer::timeout, this, &FangApp::updateAllFeeds);
    updateTimer->start();

    // Maybe the user wants to change how often we refresh the feeds?  Let 'em.
    connect(fangSettings, &FangSettings::refreshChanged, this, &FangApp::setRefreshTimer);
}

void FangApp::onQuit()
{
    // By default, cull items older than 3 months, save for the last 25.
    // (If read and unpinned, of course.)
    QDateTime olderThan = DBSettingsCacheLengthToDateTime(dbSettings.get(CACHE_LENGTH));
    qint32 saveLast = 25;

    // Clean up DB before we exit.
    manager.add(new ExpireNewsOperation(&manager, feedList, olderThan, saveLast));
}

void FangApp::setCurrentFeed(FeedItem *feed, bool reloadIfSameFeed)
{
    if (!newsServer.isServerReady()) {
        return; // We were called too early.
    }

    if (feed == nullptr) {
        return;
    }

    if (feed == currentFeed && !reloadIfSameFeed) {
        return;
    }

    // To save memory, clean up the old feed before continuing.
    if (currentFeed != nullptr) {
        currentFeed->clearNews();
    }

    FeedItem* previousFeed = currentFeed;

    //qDebug() << "You've set the feed to "<< (feed != NULL ? feed->getTitle() : "(null)");

    currentFeed = feed;

    if (previousFeed == pinnedNews) {
        pinnedNewsWatcher(); // If we were on pinned items, it can be removed now.
    }

    // Show welcome screen if there's no feeds.
    if (feedCount() <= 1) {
        newsServer.showWelcome();

        return;
    }

    // Load up our new batch o' news!
    // TODO: On startup, somehow load All News before we even get here.
    loadNews(LoadNewsOperation::Initial);
}

void FangApp::loadNews(LoadNewsOperation::LoadMode mode)
{
    if (currentFeed == nullptr || loadNewsInProgress) {
        return;
    }

    LoadNewsOperation* loader = nullptr;
    switch (currentFeed->getDbID()) {
    case FEED_ID_ALLNEWS:
        loader = new LoadAllNewsOperation(&manager, qobject_cast<AllNewsFeedItem*>(currentFeed), mode);
        break;

    case FEED_ID_PINNED:
        loader = new LoadPinnedNewsOperation(&manager, qobject_cast<PinnedFeedItem*>(currentFeed), mode);

        break;

    default:
        if (currentFeed->isFolder()) {
            loader = new LoadFolderOperation(&manager, qobject_cast<FolderFeedItem *>(currentFeed), mode);
        } else {
            loader = new LoadNewsOperation(&manager, currentFeed, mode);
        }
    }

    loadNewsInProgress =  true;
    connect(loader, &LoadNewsOperation::finished, this, &FangApp::onLoadNewsFinished);
    manager.add(loader);
}

void FangApp::onFeedTitleChanged()
{
    // The sender is the feed itself, so grab it and do a DB update.
    FeedItem* feed = qobject_cast<FeedItem *>(sender());
    if (feed == nullptr) {
        return;
    }
    
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

void FangApp::jumpToBookmark()
{
    newsServer.jumpToBookmark();
}

void FangApp::jumpNext()
{
    newsServer.jumpNext();
}

void FangApp::jumpPrevious()
{
    newsServer.jumpPrevious();
}

void FangApp::showNews()
{
    newsServer.showNews();
}

void FangApp::showWelcome()
{
    newsServer.showWelcome();
}

void FangApp::pinnedNewsWatcher()
{
    if (isPinnedNewsVisible && pinnedNews->getUnreadCount() == 0 && currentFeed != pinnedNews) {
        // Remove pinned news from the feed list -- but ONLY if it's not the selected one!
        isPinnedNewsVisible = false;
        feedList->removeItem(pinnedNews);

        emit specialFeedCountChanged();
    } else if (!isPinnedNewsVisible && pinnedNews->getUnreadCount() > 0) {
        // Add pinned news to the feed list.
        isPinnedNewsVisible = true;
        feedList->insertRow(1, pinnedNews);

        emit specialFeedCountChanged();
    }
}

void FangApp::markAllAsReadOrUnread(FeedItem *feed, bool read)
{
    MarkAllReadOrUnreadOperation * markReadOp = new MarkAllReadOrUnreadOperation(&manager, feed, read);
    connect(markReadOp, &MarkAllReadOrUnreadOperation::finished, this, &FangApp::onMarkReadOrUnreadFinished);
    manager.add(markReadOp);
}

void FangApp::onSetBookmarkFinished(Operation *operation)
{
    if (!currentFeed) {
        return;
    }

    SetBookmarkOperation* bookmarkOp = qobject_cast<SetBookmarkOperation*>(operation);
    Q_ASSERT(bookmarkOp != nullptr);

    isSettingBookmark = false;

    if (bookmarkOp->getFeed() != currentFeed) {
        // Too slow, no go, bro.
        return;
    }

    currentFeed->setBookmark(bookmarkOp->getBookmark());
    newsServer.drawBookmark(currentFeed->getBookmark()->getDbID());
}

void FangApp::onMarkReadOrUnreadFinished(Operation *operation)
{
    if (!currentFeed) {
        return;
    }

    MarkAllReadOrUnreadOperation* markReadOp = qobject_cast<MarkAllReadOrUnreadOperation*>(operation);
    Q_ASSERT(markReadOp != nullptr);

    if (markReadOp->getFeed() != currentFeed) {
        return;
    }

    // Update UI to bookmark last item in list.
    // NOTE: May lead to bugs if the last news item is not loaded into newsList
    currentFeed->setBookmark(currentFeed->getNewsList()->last());
    newsServer.drawBookmark(currentFeed->getBookmark()->getDbID());
}

void FangApp::onSetPinFinished(Operation *operation)
{
    if (nullptr == currentFeed) {
        return;
    }

    SetPinOperation* pinOp = qobject_cast<SetPinOperation*>(operation);
    Q_ASSERT(pinOp != nullptr);

    // Update the view
    newsServer.updatePin(pinOp->getNewsID(), pinOp->getPin());
}

void FangApp::onLoadNewsFinished(Operation *operation)
{
    if (nullptr == currentFeed) {
        return;
    }

    LoadNewsOperation* loader = qobject_cast<LoadNewsOperation*>(operation);
    Q_ASSERT(loader != nullptr); // If this ever happens, we're fucked.

    if (currentFeed != loader->getFeedItem()) {
        loadNewsInProgress = false;

        return; // Throw this away, it's from a previous load attempt.
    }

    // Signal and reset our flag!
    emit loadNewsFinished(loader);
    loadNewsInProgress = false;
}

void FangApp::setRefreshTimer()
{
    int minutes = 10;
    QString refresh = fangSettings->getRefresh();
    if (refresh == "1MIN") {
        minutes = 1;
    } else if (refresh == "10MIN") {
        minutes = 10;
    } else if (refresh == "30MIN") {
        minutes = 30;
    } else if (refresh == "1HOUR") {
        minutes = 60;
    } else {
        // You added a new refresh rate timeout but didn't add it here
        Q_ASSERT(false);
    }

    updateTimer->setInterval(minutes * 60 * 1000);
}


FangApp* FangApp::instance()
{
    Q_ASSERT(_instance != nullptr);
    return _instance;
}

qint32 FangApp::specialFeedCount()
{
    // If pinned is visible, it's two.
    if (isPinnedNewsVisible) {
        return 2;
    }

    // Otherwise just one for all news.
    return 1;
}

void FangApp::setWindowHeight(int windowHeight)
{
    if (windowHeight == this->windowHeight) {
        return;
    }

    this->windowHeight = windowHeight;
    emit windowHeightChanged();
}

void FangApp::addFeed(const QString userURL, const RawFeed* rawFeed, bool switchTo)
{
    qDebug() << "Add feed: " << userURL;
    AddFeedOperation* addOp = new AddFeedOperation(
                                  &manager, feedList, userURL, rawFeed);
    
    if (switchTo) {
        connect(addOp, &AddFeedOperation::finished, this, &FangApp::onNewFeedAddedSelect);
    }
    
    manager.add(addOp);
}

void FangApp::removeFeed(FeedItem *feed)
{
    // Say goodbye to these (feeds), Michael.
    //qDebug() << "remove feed";
    manager.add(new RemoveFeedOperation(&manager, feed, feedList));

    // Update orinals based on the new list order.
    UpdateOrdinalsOperation* updateOp = new UpdateOrdinalsOperation(&manager, feedList);
    manager.add(updateOp);
}

qint64 FangApp::insertFolder(qsizetype newIndex)
{
    // Slap in a new folder, reparent the following two items.
    manager.add(new InsertFolderOperation(&manager, newIndex, "New folder", feedList));
    FeedItem* item = qobject_cast<FeedItem *>(feedList->row(newIndex));
    if (item == nullptr || !item->isFolder()) {
        return -1;
    }

    return item->getDbID();
}

void FangApp::markAllAsRead(FeedItem* feed)
{
    markAllAsReadOrUnread(feed, true);

}

void FangApp::markAllAsUnread(FeedItem* feed)
{
    markAllAsReadOrUnread(feed, false);
}
