#include "LoadAllNewsOperation.h"

LoadAllNewsOperation::LoadAllNewsOperation(OperationManager *parent, FeedItem* feedItem, LoadMode mode, int loadLimit) :
    LoadNews(parent, feedItem, mode, loadLimit),
    allNews(NULL)
{
    // Ensure we have All News!
    allNews = qobject_cast<AllNewsFeedItem*>(feedItem);
    Q_ASSERT(allNews != NULL);
}

void LoadAllNewsOperation::execute()
{
    // For an initial load, make sure the feed isn't populated yet.
    if (getMode() == LoadNews::Initial)
        Q_ASSERT(feedItem->getNewsList() != NULL || feedItem->getNewsList()->isEmpty());
    
    // DB query/ies.
    bool dbResult = true;
    switch (getMode()) {
    case Initial:
    {
        dbResult &= doAppend();  // First load everything after bookmark.
        dbResult &= doPrepend(); // Now the stuff on top
        
        break;
    }
    
    case Append:
    {
        dbResult &= doAppend();
        
        break;
    }
        
    case Prepend:
    {
        dbResult &= doPrepend();
        
        break;
    }
        
    default:
        // This means you added a new mode, but didn't add it to this switch.  Jerk.
        Q_ASSERT(false);
    }
    
    // Check if we done goofed.
    if (!dbResult) {
        reportError("DB error in LoadAllNewsOperation");
        
        return;
    }
    
    // Append/prepend items from our lists.
    if (listAppend != NULL)
        foreach (NewsItem* newsItem, *listAppend)
            feedItem->getNewsList()->append(newsItem);
    
    if (listPrepend != NULL)
        foreach (NewsItem* newsItem, *listPrepend)
            feedItem->getNewsList()->prepend(newsItem);
    
    // For the initial load, set the bookmark if we have one.
    if (getMode() == Initial) {
        NewsItem* bookmark = NULL;
        
        // Bookmark is prepended item.
        if (listPrepend != NULL)
            bookmark = listPrepend->first();
        
        if (bookmark != NULL)
            feedItem->setBookmark(bookmark);
    }
    
    // we r dun lol
    emit finished(this);
}

bool LoadAllNewsOperation::doPrepend()
{
    QString queryString = "SELECT * FROM NewsItemTable N where id <= (SELECT bookmark_id from "
            "FeedItemTable WHERE id = N.feed_id) AND id NOT IN (" + getLoadedIDString() +
            ") ORDER BY timestamp DESC LIMIT :load_limit";
    
    //qDebug() << "Query: " << queryString;
    QSqlQuery query(db());
    query.prepare(queryString);
    query.bindValue(":load_limit", getLoadLimit());
    
    if (!query.exec()) {
       qDebug() << "Could not load news for all news!";
       qDebug() << query.lastError();
       
       return false;
    }
    
    // Extract the query into our news list.
    listPrepend = new QList<NewsItem*>();
    queryToNewsList(query, listPrepend);
    
    if (listPrepend->size() == 0) {
        delete listPrepend;
        listPrepend = NULL;
    }
    
    return true;
}

bool LoadAllNewsOperation::doAppend()
{
    QString queryString = "SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from "
            "FeedItemTable WHERE id = N.feed_id) AND id NOT IN (" + getLoadedIDString() +
            ") ORDER BY timestamp ASC LIMIT :load_limit";
    
    //qDebug() << "Query: " << queryString;
    QSqlQuery query(db());
    query.prepare(queryString);
    query.bindValue(":load_limit", getLoadLimit());
    
    if (!query.exec()) {
       qDebug() << "Could not load news for all news!";
       qDebug() << query.lastError();
       
       return false;
    }
    
    // Extract the query into our news list.
    listAppend = new QList<NewsItem*>();
    queryToNewsList(query, listAppend);
    
    if (listAppend->size() == 0) {
        delete listAppend;
        listAppend = NULL;
    }
    
    return true;
}

QString LoadAllNewsOperation::getLoadedIDString()
{
    // Throw all our news items' IDs into a big ol' set.
    QSet<qint64> allItems;
    if (listAppend != NULL)
        foreach(NewsItem* item, *listAppend)
            allItems.insert(item->getDbID());
    
    if (listPrepend != NULL)
        foreach(NewsItem* item, *listPrepend)
            allItems.insert(item->getDbID());
    
    if (feedItem->getNewsList() != NULL)
        foreach(NewsItem* item, *feedItem->getNewsList())
            allItems.insert(item->getDbID());
    
    QString ret = "";
    
    int i = 0;
    foreach(qint64 id, allItems) {
        ret += QString::number(id);
        i++;
        
        if (allItems.size() != i)
            ret += ", ";
    }
    
    return ret;
}

// SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id) ORDER BY timestamp ASC


// SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id) AND id NOT IN (21, 22) ORDER BY timestamp ASC LIMIT 5
