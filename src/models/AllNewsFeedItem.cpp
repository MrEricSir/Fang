#include "AllNewsFeedItem.h"
#include <QList>

AllNewsFeedItem::AllNewsFeedItem(ListModel *feedList) :
    FeedItem(-1, "All News", "", QDateTime(), 0, QUrl(), QUrl(), QUrl(), -1, feedList),
    feedList(feedList)
{
    // Do this here to avoid getting added/removed signals too early.
    connect(feedList, SIGNAL(added(ListItem*)), this, SLOT(onFeedAdded(ListItem*)));
    connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
}

void AllNewsFeedItem::onFeedAdded(ListItem* item)
{
    // When a feed is added to all news, we need to append the items and update the unread count
}

void AllNewsFeedItem::onFeedRemoved(ListItem* item)
{
    // TODO: 
    // * update unread count
    // * if it's the current feed, a view has to get refreshed.  Should I do that?
    
    Q_UNUSED(item);
}

void AllNewsFeedItem::onNewsAppended(NewsItem *item)
{
    // is this needed?
    Q_UNUSED(item);
}

void AllNewsFeedItem::onNewsRemoved(NewsItem *item)
{
    // is this needed?
    Q_UNUSED(item);
}

void AllNewsFeedItem::connectFeed(FeedItem *feed)
{
    connect(feed, SIGNAL(dataChanged()), this, SLOT(onFeedItemDataChanged()));
    connect(feed, SIGNAL(appended(NewsItem*)), this, SLOT(onNewsAppended(NewsItem*)));
    connect(feed, SIGNAL(removed(NewsItem*)), this, SLOT(onNewsRemoved(NewsItem*)));
}

void AllNewsFeedItem::disconnectFeed(FeedItem *feed)
{
    disconnect(feed, SIGNAL(dataChanged()), this, SLOT(onFeedItemDataChanged()));
    disconnect(feed, SIGNAL(appended(NewsItem*)), this, SLOT(onNewsAppended(NewsItem*)));
    disconnect(feed, SIGNAL(removed(NewsItem*)), this, SLOT(onNewsRemoved(NewsItem*)));
}

void AllNewsFeedItem::onFeedItemDataChanged()
{
    // Pass the signal up the chain.
   // emit dataChanged();
}

void AllNewsFeedItem::setBookmark(NewsItem *item, bool signal)
{
    qDebug() << "All news setting bookmark to: " << item->getTitle();
    
    
    // Set this feed's bookmark.
    FeedItem::setBookmark(item, signal);
}
