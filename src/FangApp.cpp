#include "FangApp.h"

#include "utilities/FangLogging.h"
#include <QElapsedTimer>
#include <QImageReader>

#include "utilities/ErrorHandling.h"

#include "operations/UpdateFeedOperation.h"
#include "operations/LoadAllFeedsOperation.h"
#include "operations/AddFeedOperation.h"
#include "operations/RemoveFeedOperation.h"
#include "operations/UpdateOrdinalsOperation.h"
#include "operations/UpdateTitleOperation.h"
#include "operations/SetFolderOpenOperation.h"
#include "operations/ExpireNewsOperation.h"
#include "operations/SetBookmarkOperation.h"
#include "operations/SetPinOperation.h"
#include "operations/LoadAllNewsOperation.h"
#include "operations/LoadFolderOperation.h"
#include "operations/LoadPinnedNewsOperation.h"
#include "operations/SearchNewsOperation.h"
#include "operations/InsertFolderOperation.h"
#include "operations/MarkAllReadOrUnreadOperation.h"
#include "operations/FaviconUpdateOperation.h"
#include "operations/ReloadNewsOperation.h"
#include "src/models/NewsList.h"

#ifdef Q_OS_MAC
#include "platform/MacWindowHelper.h"
#endif


FangApp* FangApp::_instance = nullptr;

FangApp::FangApp(QApplication *parent, QQmlApplicationEngine* engine, QSingleInstanceCheck* single) :
    FangObject(parent),
    engine(engine),
    single(single),
    manager(this),
    feedList(new FeedItem, this),
    importList(new ListModel(new FeedItem, this)),
    currentFeed(nullptr),
    loadAllFinished(false),
    fangSettings(nullptr),
    dbSettings(&manager),
    updateTimer(new QTimer(this)),
    window(nullptr),
    allNews(nullptr),
    pinnedNews(nullptr),
    searchFeed(nullptr),
    isPinnedNewsVisible(true),
    isSearchFeedVisible(false),
    lastFeedSelected(nullptr),
    updateChecker(this),
    systemFont(QGuiApplication::font())
{
    if (_instance != nullptr) {
        qCCritical(logApp) << "FangApp: Multiple instances created! Previous instance exists.";
    }
    _instance = this;

    // Set config for webserver.
    webServer = new WebServer(this, this);
    webServer->setWebsocketPort(webSocketServer.getPort());
    
    // Setup signals.
    connect(parent, &QApplication::aboutToQuit, this, &FangApp::onQuit);

    connect(engine, &QQmlApplicationEngine::objectCreated, this, &FangApp::onObjectCreated);

    connect(single, &QSingleInstanceCheck::notified, this, &FangApp::onSecondInstanceStarted);
    
    connect(&feedList, &ListModel::added, this, &FangApp::onFeedAdded);
    connect(&feedList, &ListModel::removed, this, &FangApp::onFeedRemoved);
    connect(&feedList, &ListModel::selectedChanged, this, &FangApp::onFeedSelected);
}

FangApp::~FangApp()
{
    // Prevent signals on shutdown.
    disconnect(&feedList, &ListModel::added, this, &FangApp::onFeedAdded);
    disconnect(&feedList, &ListModel::removed, this, &FangApp::onFeedRemoved);
    disconnect(&feedList, &ListModel::selectedChanged, this, &FangApp::onFeedSelected);
}

FangApp::FangApp(QObject *parent) :
    FangObject(parent),
    engine(nullptr),
    single(nullptr),
    manager(this),
    feedList(new FeedItem, this),
    importList(new ListModel(new FeedItem, this)),
    currentFeed(nullptr),
    loadAllFinished(false),
    fangSettings(nullptr),
    dbSettings(&manager),
    updateTimer(nullptr),
    window(nullptr),
    webServer(nullptr),
    allNews(nullptr),
    pinnedNews(nullptr),
    searchFeed(nullptr),
    isPinnedNewsVisible(false),
    isSearchFeedVisible(false),
    lastFeedSelected(nullptr),
    updateChecker(this)
{
}

void FangApp::initForTesting()
{
    // Set up singleton for test access.
    _instance = this;

    // Create WebServer.
    webServer = new WebServer(this, this);

    // Connect signals.
    connect(&feedList, &ListModel::added, this, &FangApp::onFeedAdded);
    connect(&feedList, &ListModel::removed, this, &FangApp::onFeedRemoved);
    connect(&feedList, &ListModel::selectedChanged, this, &FangApp::onFeedSelected);

    // Create special feeds for testing.
    allNews = new AllNewsFeedItem(&feedList);
    feedList.appendRow(allNews);
    feedIdMap.insert(allNews->getDbID(), allNews);
    connectFeed(allNews);

    pinnedNews = new PinnedFeedItem(&feedList);
    // Pinned news starts hidden (added dynamically when items are pinned).
    feedIdMap.insert(pinnedNews->getDbID(), pinnedNews);
    connectFeed(pinnedNews);

    loadAllFinished = true;
}

void FangApp::init()
{
    qCInfo(logApp) << "FangApp init version: " << APP_VERSION;
    qCInfo(logApp) << "";

    qCInfo(logApp) << "Image formats: " << QImageReader::supportedImageFormats();

    // Let the native text engine handle kerning and hinting.
    // On macOS, this defers to Core Text for proper San Francisco tracking.
#ifdef Q_OS_MAC
    systemFont.setHintingPreference(QFont::PreferNoHinting);
#endif

    // Setup our QML.
    engine->rootContext()->setContextProperty("feedListModel", &feedList); // list of feeds
    engine->rootContext()->setContextProperty("importListModel", importList); // list of feeds to be batch imported
    engine->rootContext()->setContextProperty("platform", getPlatform()); // platform string ID
    engine->rootContext()->setContextProperty("isDesktop", isDesktop()); // whether we're on desktop (vs mobile etc.)
    engine->rootContext()->setContextProperty("fangVersion", APP_VERSION);
    engine->rootContext()->setContextProperty("localServerPort", webServer->port()); // Port the server is listening on
    engine->rootContext()->setContextProperty("nativeFont", systemFont);

#ifdef QT_DEBUG
    bool isDebugBuild = true;
#else
    bool isDebugBuild = false;
#endif // QT_DEBUG
    engine->rootContext()->setContextProperty("isDebugBuild", isDebugBuild); // let QML know if we're a debug build or not
    qCInfo(logApp) << "Is debug build: " << isDebugBuild;
    
    // Load feed list.
    LoadAllFeedsOperation loadAllOp(&manager, &feedList);
    manager.run(&loadAllOp);
    onLoadAllFinished();
}

FeedItem* FangApp::getFeed(qsizetype index)
{
    ListItem* listItem = feedList.row(index);
    FeedItem* item = qobject_cast<FeedItem*>(listItem);
    if (item == nullptr) {
        qCDebug(logApp) << "Feed #" << index << " was NULL";
        
        return nullptr;
    }
    
    return item;
}

FeedItem *FangApp::getAllNewsFeed()
{
    return getFeed(0);
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
        qCDebug(logApp) << "Null feed was added!";
        
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
    FeedItem* item = qobject_cast<FeedItem *>(_item);
    setCurrentFeed(item);
    lastFeedSelected = item;
}

void FangApp::onNewFeedAddedSelect(AsyncOperation* addFeedOperation)
{
    AddFeedOperation* op = qobject_cast<AddFeedOperation*>(addFeedOperation);
    if (!op) {
        qCCritical(logApp) << "FangApp::onNewFeedAddedSelect: Operation is not an AddFeedOperation";
        return;
    }

    // Tell me about it.
    feedList.setSelected(op->getFeedItem());
}

void FangApp::connectFeed(FeedItem *feed)
{
    connect(feed, &FeedItem::titleChanged, this, &FangApp::onFeedTitleChanged);
    connect(feed, &FeedItem::folderOpenChanged, this, &FangApp::onFolderOpenChanged);
}

void FangApp::disconnectFeed(FeedItem *feed)
{
    disconnect(feed, &FeedItem::titleChanged, this, &FangApp::onFeedTitleChanged);
    disconnect(feed, &FeedItem::folderOpenChanged, this, &FangApp::onFolderOpenChanged);
}

void FangApp::onLoadAllFinished()
{
    loadAllFinished = true;

    // Find our special feeds.
    for (int i = 0; i < feedList.rowCount(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList.row(i));
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
            // Note: Did you add a new type of special feed and forget to update the above switch?
            FANG_UNREACHABLE("Unknown special feed: Expected All News or Pinned feed");
            break;
        }
    }

    // We get signal.
    connect(pinnedNews, &PinnedFeedItem::dataChanged, this, &FangApp::pinnedNewsWatcher);

    // This has to be manually invoked the first time.
    pinnedNewsWatcher();
    
    // Load our QML.
    engine->load(QUrl("qrc:///qml/main.qml"));

    // Refresh all our feeds to check for the latest and greatest news.
    refreshAllFeeds();
}

void FangApp::refreshFeed(FeedItem *feed)
{
    if (!feed) {
        qCCritical(logApp) << "FangApp::refreshFeed: feed is null";
        return;
    }

    QList<FeedItem*> feedsToUpdate;
    bool useCache = true; // Use cache by default.
    
    // Special handling for all news.
    if (feed->isSpecialFeed()) {
        // Update ALL the feeds.
        for (int i = 0; i < feedList.rowCount(); i++)
        {
            FeedItem* item = qobject_cast<FeedItem*>(feedList.row(i));
            if (!item) {
                qCCritical(logApp) << "FangApp::refreshFeed: Feed item at index" << i << "is null";
                continue;
            }
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
        for (int i = 0; i < feedList.rowCount(); i++)
        {
            FeedItem* item = qobject_cast<FeedItem*>(feedList.row(i));
            if (!item) {
                qCCritical(logApp) << "FangApp::refreshFeed: Feed item at index" << i << "is null";
                continue;
            }
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
        manager.enqueue(new UpdateFeedOperation(&manager, item, nullptr, useCache));
        manager.enqueue(new FaviconUpdateOperation(&manager, item));
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

        case FEED_ID_SEARCH:
            return searchFeed;

        default:
            // Note: Did you add a new type of special feed and forget to update the above switch?
            FANG_UNREACHABLE("Unknown special feed: ID is not all news, pinned, or search");
            return nullptr;
        }
    }

    // Plain ol' feeds.
    for (int i = 0; i < feedList.rowCount(); ++i) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList.row(i));
        if (!feed) {
            qCCritical(logApp) << "FangApp::feedForId: Feed item at index" << i << "is null";
            continue;
        }

        if (feed->getDbID() == id) {
            return feed;
        }
    }

    return nullptr;
}

void FangApp::setBookmark(qint64 id, bool allowBackward)
{
    if (nullptr == currentFeed) {
        qCDebug(logApp) << "setBookmark: Current feed is null, cannot set bookmark to: " << id;
        return;
    }

    if (!currentFeed->canBookmark(id, allowBackward)) {
        // Only log rejections when not allowBackward to reduce noise
        if (!allowBackward) {
            qCDebug(logApp) << "setBookmark: canBookmark REJECTED id" << id
                            << "allowBackward=" << allowBackward
                            << "currentBookmark=" << currentFeed->getBookmarkID();
        }
        return;
    }

    // For force-bookmark (allowBackward=true), search the full list including items
    // that have been trimmed from the display window but are still in memory.
    // For regular bookmarks, only search the display window.
    NewsItem* bookmark = allowBackward
        ? currentFeed->getNewsList()->fullNewsItemForID(id)
        : currentFeed->getNewsList()->newsItemForID(id);

    if (nullptr == bookmark) {
        qCDebug(logApp) << "setBookmark: Item" << id << "not found in"
                        << (allowBackward ? "full list" : "display window");
        return;
    }

    qCDebug(logApp) << "setBookmark: ACCEPTING id" << id
                    << "allowBackward=" << allowBackward
                    << "previousBookmark=" << currentFeed->getBookmarkID()
                    << "itemIndex=" << currentFeed->getNewsList()->indexOf(bookmark)
                    << "fullIndex=" << currentFeed->getNewsList()->fullIndexForItemID(id);

    // I bookmark you!
    SetBookmarkOperation bookmarkOp(&manager, currentFeed, bookmark);
    manager.run(&bookmarkOp);

    currentFeed->setBookmark(bookmarkOp.getBookmark()->getDbID());
    webSocketServer.drawBookmark(currentFeed->getBookmarkID());
}

void FangApp::setPin(qint64 id, bool pin)
{
    qCDebug(logApp) << "Someone wants to " << (pin ? "pin: " : "unpin: ") << id;
    if (nullptr == currentFeed) {
        return;
    }

    PinnedFeedItem* pinnedNews = qobject_cast<PinnedFeedItem*>(feedForId(FEED_ID_PINNED));

    SetPinOperation pinOp(&manager, pinnedNews, id, pin);
    manager.run(&pinOp);
}

void FangApp::removeAndDelete(bool fromStart, qsizetype numberToRemove)
{
    if (!currentFeed) {
        return;
    }

    // NewsList keeps items in memory and just shrinks the display window.
    // Items can be paged back into view without re-fetching from DB.
    currentFeed->getNewsList()->removeAndDelete(fromStart, numberToRemove);
}

void FangApp::onObjectCreated(QObject* object, const QUrl& url)
{
    Q_UNUSED(url);
    
    // Save our window.
    window = qobject_cast<QQuickWindow*>(object);

#ifdef Q_OS_MAC
    configureTransparentTitleBar(window);
#endif

    // Locate settings.
    fangSettings = object->findChild<FangSettings*>("fangSettings");

    // Do a sanity check.
    FANG_REQUIRE_VOID(fangSettings != nullptr);

    // Init settings.
    fangSettings->init(&dbSettings);

    // Init WebSocket server.
    webSocketServer.init(fangSettings);
    
    // Grab the All News item.
    AllNewsFeedItem* allNews = qobject_cast<AllNewsFeedItem*>(feedList.row(0));
    
    // Notifications, activate!
    notifications = new Notification(fangSettings, &feedList,
                                     allNews, window, this);
    notifications->init();
    
    // Setup the feed refresh timer.
    setRefreshTimer();
    connect(updateTimer, &QTimer::timeout, this, &FangApp::refreshAllFeeds);
    updateTimer->start();

    // Maybe the user wants to change how often we refresh the feeds?  Let 'em.
    connect(fangSettings, &FangSettings::refreshChanged, this, &FangApp::setRefreshTimer);

    // Send update signal to QML via FangSettings. (Kind of an awkward fit.)
    connect(&updateChecker, &UpdateChecker::updateAvailable,
            fangSettings, &FangSettings::updateAvailable);

    // Start the update checker (checks immediately and then every 24 hours)
    updateChecker.start();
}

void FangApp::onSecondInstanceStarted()
{
    if (window) {
        if (window->visibility() == QWindow::Visibility::Minimized) {
            window->showNormal();
        } else if (window->visibility() == QWindow::Visibility::Hidden) {
            window->show();
        }
        window->requestActivate();
        window->raise();
    } else {
        qCWarning(logApp) << "Could not locate window";
    }
}

void FangApp::onQuit()
{
    // By default, cull items older than 3 months, save for the last 25.
    // (If read and unpinned, of course.)
    QDateTime olderThan = DBSettingsCacheLengthToDateTime(dbSettings.get(CACHE_LENGTH));
    qint32 saveLast = 25;

    // Clean up DB before we exit.
    ExpireNewsOperation expireOp(&manager, &feedList, olderThan, saveLast);
    manager.run(&expireOp);
}

void FangApp::setCurrentFeed(FeedItem *feed, bool reloadIfSameFeed)
{
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

    // Set up the reload callback for this feed's news list.
    // This allows the NewsList to reload unloaded items from the database.
    OperationManager* mgr = &manager;
    currentFeed->getNewsList()->setReloadCallback([this, mgr](const QList<qint64>& ids) {
        ReloadNewsOperation reloadOp(mgr, currentFeed, ids);
        mgr->run(&reloadOp);
        return reloadOp.getReloadedItems();
    });

    if (previousFeed == pinnedNews) {
        pinnedNewsWatcher(); // If we were on pinned items, it can be removed now.
    }

    // Close the search feed if we're on it and a different feed is selected.
    if (previousFeed == searchFeed && feed != searchFeed && isSearchFeedVisible) {
        closeSearchFeed();
    }

    // Signal that we've changed feeds.
    emit currentFeedChanged();
}

LoadNewsOperation* FangApp::loadNews(LoadNewsOperation::LoadMode mode)
{
    if (currentFeed == nullptr) {
        qCDebug(logApp) << "loadNews: Current feed is null";
        qCDebug(logApp) << "Loaded feeds: " << feedList.count();
        return nullptr;
    }

    QElapsedTimer timer;
    timer.start();

    if (mode == LoadNewsOperation::LoadMode::Initial) {
        // Make sure the news list is clear before an initial load. Sometimes this can cause
        // issues on slower machines when quickly switching between feeds.
        currentFeed->clearNews();
    }

    LoadNewsOperation* loader = nullptr;
    switch (currentFeed->getDbID()) {
    case FEED_ID_ALLNEWS:
        loader = new LoadAllNewsOperation(&manager, qobject_cast<AllNewsFeedItem*>(currentFeed), mode);
        break;

    case FEED_ID_PINNED:
        loader = new LoadPinnedNewsOperation(&manager, qobject_cast<PinnedFeedItem*>(currentFeed), mode);
        break;

    case FEED_ID_SEARCH:
    {
        SearchFeedItem* searchItem = qobject_cast<SearchFeedItem*>(currentFeed);
        if (searchItem && searchItem->hasSearchQuery()) {
            // Convert SearchFeedItem::Scope to SearchNewsOperation::Scope
            SearchNewsOperation::Scope opScope;
            switch (searchItem->getScope()) {
            case SearchFeedItem::Scope::Feed:
                opScope = SearchNewsOperation::Scope::Feed;
                break;
            case SearchFeedItem::Scope::Folder:
                opScope = SearchNewsOperation::Scope::Folder;
                break;
            case SearchFeedItem::Scope::Global:
            default:
                opScope = SearchNewsOperation::Scope::Global;
                break;
            }

            loader = new SearchNewsOperation(&manager, searchItem, mode,
                                              searchItem->getSearchQuery(),
                                              opScope, searchItem->getScopeId());
        } else {
            // No query set at this time, nothing to do.
            return nullptr;
        }
        break;
    }

    default:
        if (currentFeed->isFolder()) {
            loader = new LoadFolderOperation(&manager, qobject_cast<FolderFeedItem *>(currentFeed), mode);
        } else {
            loader = new LoadNewsOperation(&manager, currentFeed, mode);
        }
    }

    manager.run(loader);
    loader->deleteLater();

    qCDebug(logApp) << "Load news operation took [ " << timer.elapsed() << " ] milliseconds";
    return loader;
}

void FangApp::onFeedTitleChanged()
{
    // The sender is the feed itself, so grab it and do a DB update.
    FeedItem* feed = qobject_cast<FeedItem *>(sender());
    if (feed == nullptr) {
        return;
    }

    UpdateTitleOperation updateTitle(&manager, feed);
    manager.run(&updateTitle);
}

void FangApp::onFolderOpenChanged()
{
    // The sender is the feed itself, so grab it and do a DB update.
    FeedItem* feed = qobject_cast<FeedItem *>(sender());
    if (feed == nullptr) {
        return;
    }

    SetFolderOpenOperation setFolderOpen(&manager, feed);
    manager.run(&setFolderOpen);
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
    FANG_UNREACHABLE("Unknown platform");
    return "UNKNOWN";
#endif
}

bool FangApp::isDesktop()
{
#if defined(Q_OS_MAC)
    return true;
#elif defined(Q_OS_WIN)
    return true;
#elif defined(Q_OS_IOS)
    return false;
#elif defined(Q_OS_ANDROID)
    return false;
#elif defined(Q_OS_LINUX) // Should be near last
    return true;
#elif defined(Q_OS_UNIX)  // Should be next-to last
    return true;
#else                     // Must be last!
    FANG_UNREACHABLE("Unknown platform");
    return true;
#endif
}

void FangApp::jumpToBookmark()
{
    webSocketServer.jumpToBookmark();
}

void FangApp::jumpNext()
{
    webSocketServer.jumpNext();
}

void FangApp::jumpPrevious()
{
    webSocketServer.jumpPrevious();
}

void FangApp::showNews()
{
    webSocketServer.showNews();
}

void FangApp::showWelcome()
{
    webSocketServer.showWelcome();
}

void FangApp::pinnedNewsWatcher()
{
    if (isPinnedNewsVisible && pinnedNews->getUnreadCount() == 0 && currentFeed != pinnedNews) {
        // Remove pinned news from the feed list -- but ONLY if it's not the selected one!
        isPinnedNewsVisible = false;
        feedList.removeItem(pinnedNews);

        emit specialFeedCountChanged();
    } else if (!isPinnedNewsVisible && pinnedNews->getUnreadCount() > 0) {
        // Add pinned news to the feed list.
        isPinnedNewsVisible = true;
        feedList.insertRow(1, pinnedNews);

        emit specialFeedCountChanged();
    }
}

void FangApp::markAllAsReadOrUnread(FeedItem *feed, bool read)
{
    MarkAllReadOrUnreadOperation markReadOp(&manager, feed, read);
    manager.run(&markReadOp);

    // Update UI to bookmark last item in list.
    // NOTE: May lead to bugs if the last news item is not loaded into newsList
    currentFeed->setBookmark(currentFeed->getNewsList()->last()->getDbID());
    webSocketServer.drawBookmark(currentFeed->getBookmarkID());
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
        // You added a new refresh rate timeout but didn't add it here. Either that or someone is
        // messing with the preferences outside of Fang. Or the drive is failing?
        FANG_UNREACHABLE("Invalid refresh rate");

        // Default: 10 minutes
        minutes = 10;
    }

    updateTimer->setInterval(minutes * 60 * 1000);
}


FangApp* FangApp::instance()
{
    if (!_instance) {
        qCCritical(logApp) << "FangApp instance is not initialized";
    }

    return _instance;
}

qint32 FangApp::specialFeedCount()
{
    qint32 count = 1;  // All News is always visible

    if (isPinnedNewsVisible) {
        count++;
    }

    if (isSearchFeedVisible) {
        count++;
    }

    return count;
}

void FangApp::addFeed(const QString userURL, const RawFeed* rawFeed, bool switchTo)
{
    qCDebug(logApp) << "Add feed: " << userURL;
    AddFeedOperation* addOp = new AddFeedOperation(
                                  &manager, &feedList, userURL, rawFeed);
    
    if (switchTo) {
        connect(addOp, &AddFeedOperation::finished, this, &FangApp::onNewFeedAddedSelect);
    }
    
    manager.enqueue(addOp);
}

void FangApp::removeFeed(FeedItem *feed)
{
    // Remove feed from the DB and our feed list.
    RemoveFeedOperation removeFeedOp(&manager, feed, &feedList);
    manager.run(&removeFeedOp);

    // Update orinals based on the new list order.
    UpdateOrdinalsOperation updateOp(&manager, &feedList);
    manager.run(&updateOp);
}

qint64 FangApp::insertFolder(qsizetype newIndex)
{
    // Slap in a new folder, reparent the following two items.
    InsertFolderOperation insertOp(&manager, newIndex, "New folder", &feedList);
    manager.run(&insertOp);
    FeedItem* item = qobject_cast<FeedItem *>(feedList.row(newIndex));
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

SearchFeedItem* FangApp::performSearch(const QString& query)
{
    return performSearch(query, SearchFeedItem::Scope::Global, -1);
}

SearchFeedItem* FangApp::performSearch(const QString& query,
                                        SearchFeedItem::Scope scope,
                                        qint64 scopeId)
{
    QString trimmedQuery = query.trimmed();
    if (trimmedQuery.isEmpty()) {
        qCDebug(logApp) << "performSearch: Empty query, ignoring";
        return nullptr;
    }

    // Create search feed lazily on first use.
    if (searchFeed == nullptr) {
        searchFeed = new SearchFeedItem(&feedList);
        feedIdMap.insert(searchFeed->getDbID(), searchFeed);
        connectFeed(searchFeed);
    }

    // Set up the search query and scope (this also clears previous results).
    searchFeed->setSearchQuery(trimmedQuery);
    searchFeed->setScope(scope, scopeId);

    // Set up the reload callback for the search feed's news list.
    OperationManager* mgr = &manager;
    QString searchQuery = trimmedQuery;  // Capture for lambda
    searchFeed->getNewsList()->setReloadCallback([this, mgr, searchQuery](const QList<qint64>& ids) {
        // For search results, we need to re-run the search query to get highlighted results.
        // ReloadNewsOperation doesn't apply the FTS5 highlighting, so we use SearchNewsOperation.
        // However, this is a simplified reload that just returns the items by ID without highlighting.
        ReloadNewsOperation reloadOp(mgr, searchFeed, ids);
        mgr->run(&reloadOp);
        return reloadOp.getReloadedItems();
    });

    // Switch to the search feed and load initial results.
    setCurrentFeed(searchFeed, true);

    return searchFeed;
}

void FangApp::showSearchFeed()
{
    qCDebug(logApp) << "showSearchFeed: Showing search feed";

    // Create search feed if it doesn't exist.
    if (searchFeed == nullptr) {
        searchFeed = new SearchFeedItem(&feedList);
        feedIdMap.insert(searchFeed->getDbID(), searchFeed);
        connectFeed(searchFeed);
    }

    // Add to feed list if not already present.
    if (!isSearchFeedVisible) {
        isSearchFeedVisible = true;

        // Insert after other special feeds.
        qsizetype insertIndex = specialFeedCount() - 1;  // -1 because we just set isSearchFeedVisible
        feedList.insertRow(insertIndex, searchFeed);

        emit specialFeedCountChanged();
    }

    // Clear any previous search state for a fresh start.
    searchFeed->setSearchQuery("");
    searchFeed->clearNews();

    // Note: QML handles selection via feedListView.currentIndex
}

void FangApp::closeSearchFeed()
{
    if (searchFeed == nullptr || !isSearchFeedVisible) {
        return;
    }

    qCDebug(logApp) << "closeSearchFeed: Removing search feed from list";

    // Remove from feed list.
    QModelIndex idx = feedList.indexFromItem(searchFeed);
    if (idx.isValid()) {
        feedList.removeRow(idx.row());
    }
    isSearchFeedVisible = false;

    // Clear the search query and results.
    searchFeed->setSearchQuery("");
    searchFeed->clearNews();

    emit specialFeedCountChanged();
}

void FangApp::clearSearch()
{
    if (searchFeed == nullptr) {
        return;
    }

    qCDebug(logApp) << "clearSearch: Clearing search results";

    // Clear the search query and results.
    searchFeed->setSearchQuery("");

    // If currently viewing search results, switch back to all news.
    if (currentFeed == searchFeed) {
        setCurrentFeed(allNews);
    }
}
