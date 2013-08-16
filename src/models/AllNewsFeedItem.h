#ifndef ALLNEWSFEEDITEM_H
#define ALLNEWSFEEDITEM_H

#include "FeedItem.h"

#include <QObject>

#include "ListModel.h"
#include "NewsItem.h"

class AllNewsFeedItem : public FeedItem
{
    Q_OBJECT
public:
    explicit AllNewsFeedItem(ListModel *feedList);
    
    virtual void setBookmark(NewsItem *item); // Override
    virtual void setIsCurrent(bool current); // Override
    virtual quint32 getUnreadCount() const; // Override
    
private slots:
    
    /**
     * @brief Call this before displaying all news.
     */
    void init();
    
    /**
     * @brief Stops all news when it's not the current item.
     */
    void deinit();
    
    // Called when a feed is added or removed from the master list.
    void onFeedAdded(ListItem *item);
    void onFeedRemoved(ListItem *item);
    
    // Called when a feed is updated.
    void onNewsAppended(NewsItem* item);
    void onNewsRemoved(NewsItem* item);
    
    // Setup signals for sub-feeds.
    void connectFeed(FeedItem* feed);
    void disconnectFeed(FeedItem* feed);
    
    // Called when any sub-feed is changed.
    void onFeedItemDataChanged();
    
private:
    ListModel* feedList;
    bool initialized;
};

#endif // ALLNEWSFEEDITEM_H
