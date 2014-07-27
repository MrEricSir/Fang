#ifndef FANGAPP_H
#define FANGAPP_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>
#include <QMap>

#include "operations/OperationManager.h"

#include "models/NewsItem.h"
#include "models/FeedItem.h"
#include "models/ListModel.h"
#include "models/FangSettings.h"
#include "models/WebInteractor.h"
#include "parser/Parser.h"
#include "FangObject.h"
#include "notifications/NotificationBase.h"
#include "utilities/SingleInstanceCheck.h"


class FangApp : public FangObject
{
    Q_OBJECT
public:
    explicit FangApp(QObject *parent, QQmlApplicationEngine* engine, SingleInstanceCheck* single);
    
    void init();
    
    /**
     * @brief Returns the feed for a given index in the global feed list.
     * @param index   0..n-1 position in feed list
     * @return        The associated FeedItem object, or null if invalid
     */
    FeedItem *getFeed(int index);
    
    /**
     * @brief Returns the feed associated with a given ID.
     * @param dbID   Database ID of feed.
     * @return       The associated FeedItem object, or null if invalid.
     */
    FeedItem* getFeedForID(qint64 dbID);
    
    /**
     * @return A (read-only) list of teh feedz.
     */
    ListModel* getFeedList() const { return feedList; }
    
    /**
     * @brief Sets the focus on the app window.
     */
    void focusApp();
    
    /**
     * @return Singleton instance of FangApp
     */
    static FangApp *instance();
    
signals:
    
public slots:
    inline int feedCount() { return feedList->rowCount(); }
    
    /**
     * @brief Adds a known, pre-processed feed.
     * @param feedURL
     * @param rawFeed
     * @param switchTo  If true, switch to the feed after adding it.
     */
    void addFeed(const QUrl &feedURL, const RawFeed* rawFeed, bool switchTo);
    
    /**
     * @brief Removes an existing feed.
     * @param feed
     */
    void removeFeed(FeedItem *feed);
    
    /**
     * @brief Updates every single damn feed.
     */
    void updateAllFeeds();
    
    /**
     * @return Our special list for batch imports.
     */
    ListModel* getImportList() { return importList; }
    
    
private slots:
    /**
     * @brief QML layer created something for us to look at.
     * @param object
     * @param url
     */
    void onObjectCreated(QObject *object, const QUrl &url);
    
    void onFeedAdded(ListItem*);
    
    void onFeedRemoved(ListItem*);
    
    void onFeedSelected(ListItem *item);
    
    // When a new feed is added, and we want to immediately select it.
    void onNewFeedAddedSelect(Operation* addFeedOperation);
    
    /**
     * @brief Monitors feed.
     * @param feed
     */
    void connectFeed(FeedItem* feed);
    
    /**
     * @brief Un-monitors feed.
     * @param feed
     */
    void disconnectFeed(FeedItem* feed);
    
    /**
     * @brief Called when all the feeds have been pulled from the database.
     * @param op
     */
    void onLoadAllFinished(Operation* op);
    
    /**
     * @brief Tells the web view to display the current feed.
     */
    void displayFeed();
    
    /**
     * @brief Used to change the current feed.
     * @param feed
     */
    void setCurrentFeed(FeedItem* feed);
    
    /**
     * @brief Updates the feed's title.
     * @param feed
     */
    void onFeedTitleChanged();
    
    /**
     * @return String representing the platform.
     */
    QString getPlatform();
    
private:
    static FangApp* _instance;
    QQmlApplicationEngine* engine;
    SingleInstanceCheck* single;
    OperationManager manager;
    ListModel *feedList;
    ListModel *importList;
    FeedItem* currentFeed;
    bool loadAllFinished;
    FangSettings *fangSettings;
    WebInteractor *interactor;
    QTimer *updateTimer;
    QMap<qint64, FeedItem*> feedIdMap;
    QQuickWindow* window;
    NotificationBase* notifications;
};

#endif // FANGAPP_H
