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
    
    virtual void setBookmark(NewsItem* item, bool signal = true); // Override
    
private slots:
    
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
};

#endif // ALLNEWSFEEDITEM_H
