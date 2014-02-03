#include "LoadNews.h"
#include <QDebug>

LoadNews::LoadNews(QObject *parent, FeedItem* feedItem, LoadMode mode, int loadLimit) :
    DBOperation(IMMEDIATE, parent),
    feedItem(feedItem),
    listAppend(NULL),
    listPrepend(NULL),
    mode(mode),
    loadLimit(loadLimit)
{
}

LoadNews::~LoadNews()
{
    delete listAppend;
    delete listPrepend;
}

void LoadNews::queryToNewsList(QSqlQuery& query, QList<NewsItem*>* list)
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
        
        // Add to our list.
        list->append(newsItem);
    }
}

qint64 LoadNews::getBookmarkID()
{
    QSqlQuery query(db());
    query.prepare("SELECT bookmark_id FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedItem->getDbId());
    
    if (!query.exec() || !query.next()) {
       qDebug() << "Could not update bookmark for feed id: " << feedItem->getDbId();
       qDebug() << query.lastError();
       
       return -1;
    }
    
    return query.value("bookmark_id").toULongLong();
}

bool LoadNews::doAppend(qint64 startId)
{
    // Extract the query into our news list.
    listAppend = new QList<NewsItem*>();
    bool ret = executeLoadQuery(startId, true);
    
    if (listAppend->size() == 0) {
        delete listAppend;
        listAppend = NULL;
    }
    
    return ret;
}

bool LoadNews::doPrepend(qint64 startId)
{
    // Extract the query into our news list.
    listPrepend = new QList<NewsItem*>();
    bool ret = executeLoadQuery(startId, false);
    
    if (listPrepend->size() == 0) {
        delete listPrepend;
        listPrepend = NULL;
    }
    
    return ret;
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
    queryToNewsList(query, append ? listAppend : listPrepend);
    
    return true;
}

void LoadNews::execute()
{
    if (feedItem->getDbId() < 0) {
        // This is AllNews, dumbass.  You called the wrong operation!
        Q_ASSERT(false);
        emit finished(this);
        
        return;
    }
    
    // For an initial load, make sure the feed isn't populated yet.
    if (mode == LoadNews::Initial)
        Q_ASSERT(feedItem->getNewsList() != NULL || feedItem->getNewsList()->isEmpty());
    
    // DB query/ies.
    bool dbResult = true;
    qint64 bookmarkID = -1;
    switch (mode) {
    case Initial:
    {
        qint64 startId = getBookmarkID();
        if (startId > 0) {
            // We has a bookmark, yo.
            bookmarkID = startId;
            
            // We have a bookmark, so try to load previous items.
            dbResult &= doPrepend(startId);
            
            qDebug() << "Start id: " << startId;
            //if (newsList->size() > 0)
            //qDebug() << "prepender: from " << newsList->first()->getDbID() << " to " << newsList->last()->getDbID();
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
        
        //qDebug() << "Append from " << startId;
        dbResult &= doAppend(startId);
        
        //qDebug() << "Adding: " << (listAppend != NULL ? listAppend->size() : 0);
        
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
    
    // Check if we done goofed.
    if (!dbResult) {
        reportError("Got no DB result.");
        
        return;
    }
    
    // Append/prepend items from our lists.
    if (listAppend != NULL)
        foreach (NewsItem* newsItem, *listAppend)
            feedItem->getNewsList()->append(newsItem);
    
    if (listPrepend != NULL)
        foreach (NewsItem* newsItem, *listPrepend)
            feedItem->getNewsList()->prepend(newsItem);
    
    // If we have a bookmark, find it and set it.
    if (bookmarkID > 0) {
        foreach (NewsItem* newsItem, *feedItem->getNewsList()) {
            // Oh, is this the bookmark?  Rad!
            if (newsItem->getDbID() == bookmarkID) {
                feedItem->setBookmark(newsItem);
                
                break;
            }
        }
    }
    
    // we r dun lol
    emit finished(this);
}
