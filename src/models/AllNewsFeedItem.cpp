#include "AllNewsFeedItem.h"
#include <QList>

AllNewsFeedItem::AllNewsFeedItem(ListModel *feedList) :
    FeedItem(-1, "All News", "", QDateTime(), 0, QUrl(), QUrl(), QUrl(), -1, feedList),
    feedList(feedList),
    initialized(false),
    dirty(false)
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
    //qDebug() << "inits! current size: " << this->getNewsList()->size();
    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != NULL);
        
        if (feed == this)
            continue; // The first item is all news, of course.
        
        if (feed->getBookmark() == NULL) {
            // All items in this feed are unread (optimization.)
            //qDebug() << "Oh! ain't no b'mark for this feed " << feed->getTitle();
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
    
    //qDebug() << "# unread items: " << unreadNews.count();
    
    // Sort the lists.
    qSort(readNews.begin(), readNews.end(), NewsItem::LessThan);
    qSort(unreadNews.begin(), unreadNews.end(), NewsItem::LessThan);
    
    // Add all read items.
    foreach(NewsItem* newsItem, readNews)
        append(newsItem);
    
    // Add all unread items.
    foreach(NewsItem* newsItem, unreadNews)
        append(newsItem);
    
    // Set the last read item as the bookmark.
    if (readNews.count() > 0) { qDebug() << "Init setting b'mark to " << readNews.last()->getTitle();
        FeedItem::setBookmark(readNews.last()); }
    
    //qDebug() << "...init";
    
    dirty = false;
    initialized = true;
}

void AllNewsFeedItem::deinit()
{
    //qDebug() << "deinit";
    initialized = false; // Don't do anything when feeds are added/removed.
    
    // Clear our entire state, it'll be rebuilt on next init.
    clearNews();
    FeedItem::setBookmark(NULL);
    
    
    //qDebug() << "...deinit";
}

void AllNewsFeedItem::onFeedAdded(ListItem* item)
{
    FeedItem* feed = qobject_cast<FeedItem*>(item);
    if (feed == NULL || feed == this)
        return;
    
    // From here on out, monitor the feed.
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
    
    dirty = true; // Possibly unsorted items.
}

void AllNewsFeedItem::onFeedRemoved(ListItem* item)
{
    FeedItem* feed = qobject_cast<FeedItem*>(item);
    if (feed == NULL || feed == this)
        return;
    
    // Disconnect data change signal.
    disconnectFeed(feed);
    
    // Update unread count.
    emit dataChanged();
    
    // The following are only to be done while this feed is current & initialized.
    if (!initialized)
        return;
    
    // Remove 'em all from this feed.
    for(int i = 0; i < feed->getNewsList()->count(); i++)
        remove(feed->getNewsList()->at(i));
}

void AllNewsFeedItem::onNewsAppended(NewsItem *item)
{
    // If this is the current feed, update the data model accordingly.
    if (initialized)
        append(item);
}

void AllNewsFeedItem::onNewsRemoved(NewsItem *item)
{
    // See above.
    if (initialized)
        remove(item);
    
    dirty = true;
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
    emit dataChanged();
}

void AllNewsFeedItem::setBookmark(NewsItem *item, bool signal)
{
    if (!canBookmark(item) || !initialized)
        return;
    
    //qDebug() << "All news setting bookmark to: " << item->getTitle();
    
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
    FeedItem::setBookmark(item, signal);
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

void AllNewsFeedItem::setVisibleItems(NewsItem *first, NewsItem *last, bool atBottom)
{
    if (!initialized)
        return;
    
    FeedItem::setVisibleItems(first, last, atBottom);
    
    // Resort items below the visible area, if needed.
    
    if (!dirty || last == NULL || atBottom)
        return; // Nothing to do!
    qDebug() << "set vis";
    
    if (getNewsList()->size() <= 1 || getNewsList()->last() == last) {
        // Nothing to sort.
        dirty = false;
        qDebug() << "..set vis (early exit)";
        return;
    }
    
    // Remove everything after last and add them to a new list.
    QList<NewsItem*> toSort;
    while (getNewsList()->last() != last) {
        NewsItem* item = getNewsList()->last();
        toSort.append(item);
        remove(item);
    }
    
    // Sort the list.
    qSort(toSort.begin(), toSort.end(), NewsItem::LessThan);
    
    // Add 'em all back!
    foreach(NewsItem* item, toSort)
        append(item);
    qDebug() << "...set vis";
    dirty = false;
}
