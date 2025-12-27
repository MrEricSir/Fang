#include "LoadNewsOperation.h"
#include "../models/NewsList.h"
#include <QDebug>

LoadNewsOperation::LoadNewsOperation(OperationManager *parent, FeedItem* feedItem, LoadMode mode, int loadLimit) :
    DBOperationSynchronous(parent),
    feedItem(feedItem),
    listAppend(),
    listPrepend(),
    mode(mode),
    loadLimit(loadLimit)
{
}

LoadNewsOperation::~LoadNewsOperation()
{

}

QString LoadNewsOperation::modeToString(LoadMode mode)
{
    switch(mode) {
    case Initial:
        return "initial";
    case Prepend:
        return "prepend";
    case Append:
        return "append";
    default:
        qWarning() << "Invalid enum load mode: " << mode;
        Q_ASSERT(false);
    }
}

LoadNewsOperation::LoadMode LoadNewsOperation::stringToMode(QString modeString)
{
    if (modeString == "initial") {
        return LoadMode::Initial;
    } else if (modeString == "prepend") {
        return LoadMode::Prepend;
    } else if (modeString == "append") {
        return LoadMode::Append;
    } else {
        qWarning() << "Invalid string load mode: " << modeString;
        Q_ASSERT(false);
    }
}

void LoadNewsOperation::queryToNewsList(QSqlQuery& query, QList<NewsItem*>* list)
{
    while (query.next()) {
        // Load from DB query result.
        NewsItem* newsItem = new NewsItem(
                    feedItem,
                    query.value("id").toULongLong(),
                    query.value("feed_id").toULongLong(),
                    query.value("title").toString(),
                    query.value("author").toString(),
                    query.value("summary").toString(),
                    query.value("content").toString(),
                    QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong()), 
                    query.value("url").toString(),
                    (bool) query.value("pinned").toInt()
                    );
        
        // Add to our list.
        list->append(newsItem);
    }
}

qint64 LoadNewsOperation::getBookmarkID()
{
    QSqlQuery query(db());
    query.prepare("SELECT bookmark_id FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedItem->getDbID());
    
    if (!query.exec() || !query.next()) {
       qDebug() << "Could not update bookmark for feed id: " << feedItem->getDbID();
       qDebug() << query.lastError();
       
       return -1;
    }
    
    return query.value("bookmark_id").toULongLong();
}

qint64 LoadNewsOperation::getFirstNewsID()
{
    const QString queryString = "SELECT id FROM NewsItemTable WHERE feed_id = :feed_id "
            "ORDER BY timestamp ASC, id ASC LIMIT 1";
    
    QSqlQuery query(db());
    query.prepare(queryString);
    
    query.bindValue(":feed_id", feedItem->getDbID());
    
    if (!query.exec() || !query.next()) {
        // No news yet!
        return -1;
    }
    
    return query.value("id").toULongLong();
}

bool LoadNewsOperation::doAppend(qint64 startId)
{
    qDebug() << "LoadNewsOperation::doAppend " << startId;
    // Extract the query into our news list.
    return executeLoadQuery(startId, true);
}

bool LoadNewsOperation::doPrepend(qint64 startId)
{
    qDebug() << "LoadNewsOperation::doPrepend " << startId;
    // Extract the query into our news list.
    return executeLoadQuery(startId, false);
}

bool LoadNewsOperation::executeLoadQuery(qint64 startId, bool append)
{
    if (append) {
        listAppend.clear();
    } else {
        listPrepend.clear();
    }

    QString direction = append ? ">=" : "<";
    QString sortOrder = append ? "ASC" : "DESC";
    QString queryString = "SELECT * FROM NewsItemTable WHERE feed_id = :feed_id AND id " 
            + direction + " :start_id ORDER BY timestamp " + sortOrder + ", id " + sortOrder
            + " LIMIT :load_limit";
    
    qDebug() << "executeLoadQuery: Query string: " << queryString;
    QSqlQuery query(db());
    query.prepare(queryString);
    
    query.bindValue(":feed_id", feedItem->getDbID());
    query.bindValue(":start_id", startId);
    query.bindValue(":load_limit", loadLimit);
    
    if (!query.exec()) {
       qDebug() << "Could not load news for feed id: " << feedItem->getDbID();
       qDebug() << query.lastError();
       
       return false;
    }
    
    // Extract the query into our news list.
    queryToNewsList(query, append ? &listAppend : &listPrepend);
    
    return true;
}

qint64 LoadNewsOperation::getStartIDForAppend()
{
    qint64 startId = -1;
    if (feedItem->getNewsList() != nullptr && feedItem->getNewsList()->size() > 0) {
        startId = feedItem->getNewsList()->last()->getDbID() + 1; // Advance to next item
    }

    return startId;
}

qint64 LoadNewsOperation::getStartIDForPrepend()
{
    qint64 startId = -1;
    if (feedItem->getNewsList() != nullptr && feedItem->getNewsList()->size() > 0) {
        startId = feedItem->getNewsList()->first()->getDbID();
    }

    return startId;
}

void LoadNewsOperation::executeSynchronous()
{
    if (feedItem->isSpecialFeed()) {
        // Wrong type of load operation for special feed.
        Q_ASSERT(false);
        
        return;
    }
    
    // DB query/ies.
    bool dbResult = true;
    qint64 bookmarkID = getBookmarkID(); // Default: unbookmarked = -1
    qint64 firstNewsID = getFirstNewsID();
    switch (mode) {
    case Initial:
    {
        // For an initial load, make sure the feed isn't populated yet.
        Q_ASSERT(feedItem->getNewsList() == nullptr || feedItem->getNewsList()->isEmpty());
            
        qint64 startId = bookmarkID;
        if (startId > 0) {
            // We has a bookmark, yo!
            // Try to load previous items.
            dbResult &= doPrepend(startId);
            
            qDebug() << "Start id: " << startId;
        }
        
        // Load next items, if available.
        dbResult &= doAppend(startId);
        
        break;
    }
    
    case Append:
    {
        dbResult &= doAppend(getStartIDForAppend());
        
        break;
    }
        
    case Prepend:
    {
        dbResult &= doPrepend(getStartIDForPrepend());
        
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
    if (!listAppend.isEmpty()) {
        for (NewsItem* newsItem: listAppend) {
            feedItem->getNewsList()->append(newsItem);
        }
    }
    
    if (!listPrepend.isEmpty()) {
        for (NewsItem* newsItem: listPrepend) {
            feedItem->getNewsList()->prepend(newsItem);
        }
    }
    
    // Set our bookmark.
    if (bookmarkID >= 0) {
        feedItem->setBookmark(bookmarkID);
    }
    
    // Set the first known ID.
    feedItem->setFirstNewsID(firstNewsID);
}
