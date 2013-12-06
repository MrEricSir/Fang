#include "LoadAllNewsOperation.h"

LoadAllNewsOperation::LoadAllNewsOperation(QObject *parent, FeedItem* feedItem, LoadMode mode, int loadLimit) :
    LoadNews(parent, feedItem, mode, loadLimit)
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
    
    // Create our list of news.
    newsList = new QList<NewsItem*>();
    
    // DB query/ies.
    bool dbResult = true;
    switch (getMode()) {
    case Initial:
    {
        dbResult &= doInitial();
        
        break;
    }
    
    case Append:
    {
        // TODO: Append
        
        break;
    }
        
    case Prepend:
    {
        // TODO:
        // prepend
        
        break;
    }
        
    default:
        // This means you added a new mode, but didn't add it to this switch.  Jerk.
        Q_ASSERT(false);
    }
    
    // Check if we done goofed.
    if (!dbResult) {
        //TODO : add error signal
        emit finished(this);
        
        return;
    }
    
    // Update list with our items.
    foreach (NewsItem* newsItem, *newsList) {
        if (getMode() != Prepend)
            feedItem->getNewsList()->append(newsItem);
        else
            feedItem->getNewsList()->prepend(newsItem);
    }
    
    // Set the bookmark if we found it.
    if (bookmark != NULL)
        feedItem->setBookmark(bookmark, false);
    
    // we r dun lol
    emit finished(this);
}

bool LoadAllNewsOperation::doInitial()
{
    QString queryString = "SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from "
            "FeedItemTable WHERE id = N.feed_id) ORDER BY timestamp ASC LIMIT :load_limit";
    
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
    queryToNewsList(query);
    
    return true;
}

bool LoadAllNewsOperation::doPrepend()
{
    
}

// SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id) ORDER BY timestamp ASC


// SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id) AND id NOT IN (21, 22) ORDER BY timestamp ASC LIMIT 5
