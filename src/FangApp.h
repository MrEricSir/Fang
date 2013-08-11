#ifndef FANGAPP_H
#define FANGAPP_H

#include <QObject>
#include <QDeclarativeContext>

#include "operations/OperationManager.h"

#include "models/FangApplicationViewer.h"
#include "models/NewsItem.h"
#include "models/FeedItem.h"
#include "models/ListModel.h"
#include "models/FangWebView.h"
#include "parser/Parser.h"
#include "models/NewsWeb.h"


class FangApp : public QObject
{
    Q_OBJECT
public:
    explicit FangApp(QObject *parent, FangApplicationViewer* viewer);
    
    void init();
    
    // Returns the feed for the given index from 0..feedCount
    FeedItem *getFeed(int index);
    
    inline NewsWeb* getNewsWeb() { return &newsWeb; }
    
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
    
    void onOperationFinished(Operation* operation);
    
    void onFeedAdded(ListItem*);
    
    void onFeedRemoved(ListItem*);
    
    void onNewsWebReady();
    
    void onNewsItemBookmarked(NewsItem* item);
    
    void onFeedSelected(ListItem *item);
    
    /**
     * @brief Tells the web view to display the current feed.
     */
    void displayFeed();
    
private:
    static FangApp* _instance;
    FangApplicationViewer* viewer;
    OperationManager manager;
    ListModel *feedList;
    NewsWeb newsWeb;
    FeedItem* currentFeed;
};

#endif // FANGAPP_H
