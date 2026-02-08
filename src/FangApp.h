#ifndef FANGAPP_H
#define FANGAPP_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>
#include <QMap>

#include <QSingleInstanceCheck/QSingleInstanceCheck.h>

#include "operations/OperationManager.h"
#include "models/FeedItem.h"
#include "models/AllNewsFeedItem.h"
#include "models/PinnedFeedItem.h"
#include "models/ListModel.h"
#include "models/FangSettings.h"
#include "parser/RawFeed.h"
#include "FangObject.h"
#include "notifications/NotificationBase.h"
#include "db/DBSettings.h"
#include "server/WebServer.h"
#include "server/WebSocketServer.h"
#include "utilities/UpdateChecker.h"
#include "sync/SyncService.h"


class FangApp : public FangObject
{
    Q_OBJECT
public:
    explicit FangApp(QApplication *parent, QQmlApplicationEngine* engine, QSingleInstanceCheck* single);

    virtual ~FangApp();

protected:
    /*!
        \brief Protected constructor for testing without UI.
        Note: Only used for teseting. Test subclasses must call initForTesting() after construction.
     */
    explicit FangApp(QObject *parent);

    /*!
        \brief Initialize for testing with in-memory database.
        Note: Only used for testing.
     */
    void initForTesting();

public:

    void init();
    
    /*!
        \brief Returns the feed for a given index in the global feed list.
        \param index   0..n-1 position in feed list
        \return        The associated FeedItem object, or null if invalid
     */
    FeedItem *getFeed(qsizetype index);

    /*!
        \brief Returns the all news feed.
     */
    FeedItem *getAllNewsFeed();
    
    /*!
        \return A list of our feedz.
     */
    ListModel* getFeedList() { return &feedList; }

    /*!
        \return Our operation manager instance.
     */
    OperationManager* getOperationManager() { return &manager; }
    
    /*!
        \brief Sets the focus on the app window.
     */
    void focusApp();
    
    /*!
        \return Singleton instance of FangApp
     */
    static FangApp *instance();
    
signals:

    // Current feed changed from the previously selected feed.
    void currentFeedChanged();

    // The number of special feeds has changed, huzzah!
    void specialFeedCountChanged();

public slots:
    inline int feedCount() { return feedList.rowCount(); }

    /*!
        \return The number of visible special feeds (all news, pinned, etc.)
     */
    qint32 specialFeedCount();
    
    /*!
        \brief Adds a known, pre-processed feed.
        \param userURL
        \param rawFeed
        \param switchTo  If true, switch to the feed after adding it.
     */
    void addFeed(const QString userURL, const RawFeed* rawFeed, bool switchTo);
    
    /*!
        \brief Removes an existing feed.
        \param feed
     */
    void removeFeed(FeedItem *feed);

    /*!
        \brief Inserts a new folder at the given index.
        \param newIndex
        \return UUID of folder item
     */
    qint64 insertFolder(qsizetype newIndex);

    /*!
        \brief Marks all items in a feed as read.
        \param feed
     */
    void markAllAsRead(FeedItem* feed);

    /*!
        \brief Marks all items in a feed as unread.
        \param feed
     */
    void markAllAsUnread(FeedItem* feed);
    
    /*!
        \return Our special list for batch imports.
     */
    ListModel* getImportList() { return importList; }
    
    /*!
        \brief Refresh a single feed.
     */
    void refreshFeed(FeedItem* feed);
    
    /*!
        \brief Refresh ALL feeds.
     */
    void refreshAllFeeds();
    
    /*!
        \brief Refreshes the current feed.
     */
    void refreshCurrentFeed();
    
    /*!
        \brief Fetches the feed with the given ID.
     */
    FeedItem* feedForId(const qint64 id);

    /*!
        \brief Sets the bookmark, and fires a draw event.
     */
    void setBookmark(qint64 id, bool allowBackward = false);

    /*!
        \brief Pin or unpins an item.
     */
    void setPin(qint64 id, bool pin);

    /*!
        \brief Removes news from the list from either the start or end.
        This is used to prevent too many items from clogging up the news view.
     */
    void removeAndDelete(bool fromStart, qsizetype numberToRemove);

    /*!
        \brief Used to change the current feed.
        \param feed
        \param reloadIfSameFeed If it's the same as the current feed, reinit.
     */
    void setCurrentFeed(FeedItem* feed, bool reloadIfSameFeed = false);

    /*!
        \return Pointer to the current feed.
     */
    FeedItem* getCurrentFeed() { return currentFeed; }

    /*!
        \return The last feed selected; feed may not be active yet due to startup order of operations.
     */
    FeedItem* getLastFeedSelected() { return lastFeedSelected; }

    /*!
        \brief loadNews Loads another batch of news into memory.  See also the loadNewsFinished signal.
        \param mode
     */
    LoadNewsOperation* loadNews(LoadNewsOperation::LoadMode mode);

    /*!
        \return The settings object, or null if the app hasn't initialized yet.
     */
    FangSettings* getSettings() { return fangSettings; }

    /*!
        \return String representing the platform.
     */
    QString getPlatform();

    /*!
        \return True on desktop platforms, else false. Default: true if unknown.
     */
    bool isDesktop();

    /*!
        \return Fang's news WebSocket server.
     */
    WebSocketServer* getWebSocketServer() { return &webSocketServer; }

    /*!
        \return The sync service for cloud synchronization.
     */
    SyncService* getSyncService() { return syncService; }

    /*!
        \brief Jumps the view to the bookmark (if any)
     */
    void jumpToBookmark();

    /*!
        \brief Jumps to the next news item (if any)
     */
    void jumpNext();

    /*!
        \brief Jumps to the previous news item (if any)
     */
    void jumpPrevious();

    /*!
        \brief Show the news view.
     */
    void showNews();

    /*!
        \brief Show the welcome/help view.
     */
    void showWelcome();

private slots:
    /*!
        \brief QML layer created something for us to look at.
        \param object
        \param url
     */
    void onObjectCreated(QObject *object, const QUrl &url);

    void onSecondInstanceStarted();

    /*!
        \brief Called at closing time, one last call for alcohol so finish your whiskey or beer.
     */
    void onQuit();
    
    void onFeedAdded(ListItem*);
    
    void onFeedRemoved(ListItem*);
    
    void onFeedSelected(ListItem *item);
    
    // When a new feed is added, and we want to immediately select it.
    void onNewFeedAddedSelect(Operation* addFeedOperation);
    
    /*!
        \brief Monitors feed.
        \param feed
     */
    void connectFeed(FeedItem* feed);
    
    /*!
        \brief Un-monitors feed.
        \param feed
     */
    void disconnectFeed(FeedItem* feed);
    
    /*!
        \brief Called when all the feeds have been pulled from the database.
        \param op
     */
    void onLoadAllFinished(Operation* op);
    
    /*!
        \brief Updates the feed's title.
     */
    void onFeedTitleChanged();

    /*!
        \brief Saves the folder open/closed state.
     */
    void onFolderOpenChanged();

    /*!
        \brief Adds/removes the pinned news item to the list.
     */
    void pinnedNewsWatcher();

    void markAllAsReadOrUnread(FeedItem* feed, bool read);

    // Updates the feed refresh timer.
    void setRefreshTimer();

    // Initialize sync service.
    void setupSyncService();

private:
    static FangApp* _instance;
    QQmlApplicationEngine* engine;
    QSingleInstanceCheck* single;
    OperationManager manager;
    ListModel feedList;
    ListModel *importList;
    FeedItem* currentFeed;
    bool loadAllFinished;
    FangSettings *fangSettings;
    DBSettings dbSettings;
    QTimer *updateTimer;
    QMap<qint64, FeedItem*> feedIdMap;
    QQuickWindow* window;
    NotificationBase* notifications;
    WebSocketServer webSocketServer;
    WebServer* webServer;
    UpdateChecker updateChecker;
    SyncService* syncService;

    // Special feeds.
    AllNewsFeedItem* allNews;
    PinnedFeedItem* pinnedNews;

    bool isPinnedNewsVisible;

    FeedItem* lastFeedSelected;
};

#endif // FANGAPP_H
