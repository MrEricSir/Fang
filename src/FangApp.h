#ifndef FANGAPP_H
#define FANGAPP_H

#include <QObject>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

#include "../qtquick2applicationviewer/qtquick2applicationviewer.h"

#include "operations/OperationManager.h"

#include "models/FangApplicationViewer.h"
#include "models/NewsItem.h"
#include "models/FeedItem.h"
#include "models/ListModel.h"
#include "models/FangSettings.h"
#include "models/WebInteractor.h"
#include "parser/Parser.h"


class FangApp : public QObject
{
    Q_OBJECT
public:
    explicit FangApp(QObject *parent, FangApplicationViewer* viewer);
    
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
    
    static FangApp *instance();
signals:
    
public slots:
    inline int feedCount() { return feedList->rowCount(); }
    
    /**
     * @brief Adds a feed.
     * @param feedURL
     * @param imageURL
     * @param siteTitle
     */
    void addFeed(const QUrl& feedURL, const QUrl& imageURL, QString siteTitle);
    
    /**
     * @brief Removes an existing feed.
     * @param feed
     */
    void removeFeed(FeedItem *feed);
    
private slots:
    void onViewerStatusChanged(QQuickView::Status);
    
    void onWindowResized();
    
    void onOperationFinished(Operation* operation);
    
    void onFeedAdded(ListItem*);
    
    void onFeedRemoved(ListItem*);
    
    void onFeedSelected(ListItem *item);
    
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
     * @brief Updates every single damn feed.
     */
    void updateAllFeeds();
    
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
    FangApplicationViewer* viewer;
    OperationManager manager;
    ListModel *feedList;
    FeedItem* currentFeed;
    bool loadAllFinished;
    FangSettings *fangSettings;
    WebInteractor *interactor;
    QTimer *updateTimer;
};

#endif // FANGAPP_H
