#ifndef FANGAPP_H
#define FANGAPP_H

#include <QObject>
#include <QDeclarativeContext>

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
    
    // Returns the feed for the given index from 0..feedCount
    FeedItem *getFeed(int index);
    
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
    void onViewerStatusChanged(QDeclarativeView::Status);
    
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
};

#endif // FANGAPP_H
