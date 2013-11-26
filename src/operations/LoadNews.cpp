#include "LoadNews.h"
#include <QDebug>

LoadNews::LoadNews(QObject *parent, FeedItem* feedItem, LoadMode mode, int loadLimit) :
    DBOperation(parent),
    feedItem(feedItem),
    mode(mode),
    loadLimit(loadLimit),
    newsList(NULL),
    bookmark(NULL)
{
}

void LoadNews::queryToNewsList(QSqlQuery& query, bool append)
{
    while (query.next()) {
        // Load from DB query result.
        NewsItem* newsItem = new NewsItem(
                    feedItem,
                    query.value("id").toULongLong(),
                    query.value("title").toString(),
                    query.value("author").toString(),
                    query.value("summary").toString(),
                    query.value("content").toString(),
                    QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong()), 
                    query.value("url").toString()
                    );
        
        // Add to our temporary list.
        if (append)
            newsList->append(newsItem);
        else
            newsList->prepend(newsItem);
        
        // Remember if we found the bookmark.
        if (newsItem->getDbID() == feedItem->getBookmarkID())
            bookmark = newsItem;
    }
}

bool LoadNews::doAppend(qint64 startId)
{
    return executeLoadQuery(startId, true);
}

bool LoadNews::doPrepend(qint64 startId)
{
    return executeLoadQuery(startId, false);
}

bool LoadNews::executeLoadQuery(qint64 startId, bool append)
{
    QString direction = append ? ">=" : "<";
    QString sortOrder = append ? "ASC" : "DESC";
    QString queryString = "SELECT * FROM NewsItemTable WHERE feed_id = :feed_id AND id " + direction + " :start_id "
            "ORDER BY timestamp " + sortOrder + " LIMIT :load_limit";
    
    //qDebug() << "Query: " << queryString;
    QSqlQuery query(db());
    query.prepare(queryString);
    
    query.bindValue(":feed_id", feedItem->getDbId());
    query.bindValue(":start_id", startId);
    query.bindValue(":load_limit", loadLimit);
    
    if (!query.exec()) {
       qDebug() << "Could not load news for feed id: " << feedItem->getDbId();
       qDebug() << query.lastError();
       
       return false;
    }
    
    // Extract the query into our news list.
    queryToNewsList(query, append);
    
    return true;
}

void LoadNews::execute()
{
    // TODO: handle all news
    if (feedItem->getDbId() < 0) {
        emit finished(this);
        
        return;
    }
    
    // For an initial load, make sure the feed isn't populated yet.
    if (mode == LoadNews::Initial)
        Q_ASSERT(feedItem->getNewsList() != NULL || feedItem->getNewsList()->isEmpty());
    
    // Create our list of news.
    newsList = new QList<NewsItem*>();
    
    // DB query/ies.
    bool dbResult = true;
    switch (mode) {
    case Initial:
    {
        qint64 startId = feedItem->getBookmarkID();
        if (startId > 0) {
            // We have a bookmark, so try to load previous items.
            dbResult &= doPrepend(startId);
            
            qDebug() << "Start id: " << startId;
            if (newsList->size() > 0)
            qDebug() << "prepender: from " << newsList->first()->getDbID() << " to " << newsList->last()->getDbID();
        }
        
        // Load next items, if available.
        dbResult &= doAppend(startId);
        
        break;
    }
    
    case Append:
    {
        qint64 startId = -1;
        if (feedItem->getNewsList() != NULL && feedItem->getNewsList()->size() > 0)
            startId = feedItem->getNewsList()->last()->getDbID();
        
        startId++; // Advance to the next item.
        
        qDebug() << "Append from " << startId;
        dbResult &= doAppend(startId);
        
        qDebug() << "Adding: " << newsList->size();
        
        break;
    }
        
    case Prepend:
    {
        qint64 startId = -1;
        if (feedItem->getNewsList() != NULL && feedItem->getNewsList()->size() > 0)
            startId = feedItem->getNewsList()->first()->getDbID();
        
        dbResult &= doPrepend(startId);
        
        break;
    }
        
    default:
        // This means you added a new mode, but didn't add it to this switch.  Jerk.
        Q_ASSERT(false);
    }
    
    /*
    if (mode == LoadNews::Initial || mode == LoadNews::Append) {
        dbResult &= doAppend(startId);
    }
    
    if (mode == LoadNews::Initial || mode == LoadNews::Prepend) {
        dbResult &= doPrepend(startId);
    }
    
    */
    
    // Check if we done goofed.
    if (!dbResult) {
        //TODO : add error signal
        emit finished(this);
        
        return;
    }
    
    // Update list with our items.
    foreach (NewsItem* newsItem, *newsList)
         feedItem->getNewsList()->append(newsItem);
    
    // Set the bookmark if we found it.
    if (bookmark != NULL)
        feedItem->setBookmark(bookmark, false);
    
    // we r dun lol
    emit finished(this);
}
