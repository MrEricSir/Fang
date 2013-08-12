#include "AllNewsFeedItem.h"
#include <QList>

AllNewsFeedItem::AllNewsFeedItem(ListModel *feedList) :
    FeedItem(-1, "All News", "", QDateTime(), 0, QUrl(), QUrl(), QUrl(), NULL, feedList),
    feedList(feedList),
    initialized(false)
{
    // Do this here to avoid getting added/removed signals too early.
    connect(feedList, SIGNAL(added(ListItem*)), this, SLOT(onFeedAdded(ListItem*)));
    connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
}

void AllNewsFeedItem::init()
{
    // Grab all items from each feed and add them to two lists; unread and read news items.
    QList<NewsItem*> readNews;
    QList<NewsItem*> unreadNews;
    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != NULL);
        
        if (feed == this)
            continue; // The first item is all news, of course.
        
        if (feed->getBookmark() == NULL) {
            // All items in this feed are unread (optimization.)
            unreadNews.append(*feed->getNewsList());
        } else if (feed->getBookmark() == feed->getNewsList()->last()) {
            // All items in this feed are read (optimization.)
            readNews.append(*feed->getNewsList());
        } else {
            // In most cases, we need to separate out the feed into two halves: read and unread.
            // Read items are up to and including the bookmark; unread items are everything remaining.
            bool beforeBookmark = true;
            for (int j = 0; j < feed->getNewsList()->size(); j++) {
                NewsItem* news = feed->getNewsList()->at(j);
                
                if (beforeBookmark) {
                    // Put everything up to and including the bookmark into readNews.
                    readNews.append(news);
                    
                    if (feed->getBookmark() == news)
                        beforeBookmark = false;
                } else {
                    // Everything else goes into unreadNews.
                    unreadNews.append(news);
                }
            }
            
        }
    }
    
    // Sort the lists.
    qSort(readNews.begin(), readNews.end(), NewsItem::LessThan);
    qSort(unreadNews.begin(), unreadNews.end(), NewsItem::LessThan);
    
    // Add all read items.
    foreach(NewsItem* newsItem, readNews)
        append(newsItem);
    
    // Set the last read item as the bookmark.
    if (getNewsList()->count() > 0)
        setBookmark(getNewsList()->last());
    
    // Add all unread items.
    foreach(NewsItem* newsItem, unreadNews)
        append(newsItem);
    
    initialized = true;
}

void AllNewsFeedItem::deinit()
{
    initialized = false; // Don't do anything when feeds are added/removed.
    
    // Clear our news list.  It'll be rebuilt next time we init.
    clearNews();
}

void AllNewsFeedItem::onFeedAdded(ListItem* item)
{
    FeedItem* feed = qobject_cast<FeedItem*>(item);
    if (feed == NULL || feed == this)
        return;
    
    // Monitor other feeds!
    connectFeed(feed);
    
    // The following are only to be done while this feed is current & initialized.
    if (!initialized)
        return;
    
    // Add all unread items.
    int bookmarkIndex = 0;
    if (feed->getBookmark() != NULL)
        bookmarkIndex = feed->getNewsList()->indexOf(feed->getBookmark());
    
    for (int i = bookmarkIndex; i < feed->getNewsList()->size(); i++) {
        NewsItem* news = feed->getNewsList()->at(i);
        append(news);
    }
    
    // TODO: Figure out what to do about read items.
}

void AllNewsFeedItem::onFeedRemoved(ListItem* item)
{
    FeedItem* feed = qobject_cast<FeedItem*>(item);
    if (feed == NULL || feed == this)
        return;
    
    // Disconnect data change signal.
    disconnectFeed(feed);
    
    // The following are only to be done while this feed is current & initialized.
    if (!initialized)
        return;
    
    // Remove 'em all from this feed.
    for(int i = 0; i < feed->getNewsList()->count(); i++)
        remove(feed->getNewsList()->at(i));
    
    emit dataChanged();
}

void AllNewsFeedItem::connectFeed(FeedItem *feed)
{
    connect(feed, SIGNAL(dataChanged()), this, SLOT(onFeedItemDataChanged()));
}

void AllNewsFeedItem::disconnectFeed(FeedItem *feed)
{
    disconnect(feed, SIGNAL(dataChanged()), this, SLOT(onFeedItemDataChanged()));
}

void AllNewsFeedItem::onFeedItemDataChanged()
{
    // Pass the signal up the chain.
    emit dataChanged();
}

void AllNewsFeedItem::setBookmark(NewsItem *item)
{
    if (!canBookmark(item))
        return;
    
    // Compute indexes of current and new bookmark.
    NewsItem* currentBookmark = getBookmark();
    int newBookmarkIndex = getNewsList()->indexOf(item);
    int currentBookmarkIndex = 0;
    if (currentBookmark != NULL)
        currentBookmarkIndex = getNewsList()->indexOf(currentBookmark);
    
    // Bookmark everything up to and including the new bookmark in all feeds.
    // TODO: Optimize! No need to bookmark every single item, since some may be in the same feed.
    for (int i = currentBookmarkIndex; i <= newBookmarkIndex; i++) {
        NewsItem* toBookmark = getNewsList()->at(i);
        toBookmark->getFeed()->setBookmark(toBookmark);
    }
    
    // Set this feed's bookmark.
    FeedItem::setBookmark(item);
}

void AllNewsFeedItem::setIsCurrent(bool current)
{
    if (getIsCurrent() == current)
        return;
    
    if (current)
        init();
    else
        deinit();
    
    FeedItem::setIsCurrent(current);
}

quint32 AllNewsFeedItem::getUnreadCount() const
{
    quint32 ret = 0;
    
    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        if (feed == this)
            continue;
        
        ret += feed->getUnreadCount();
    }
    
    return ret;
}
