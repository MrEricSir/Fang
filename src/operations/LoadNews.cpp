#include "LoadNews.h"
#include <QDebug>

LoadNews::LoadNews(QObject *parent, FeedItem* feedItem) :
    DBOperation(parent),
    feedItem(feedItem)
{
}

void LoadNews::execute()
{
    // For now, just load a few items.
    //
    // TODO: have a load front, load prev, etc.
    //
    
    QSqlQuery query(db());
    query.prepare("SELECT * FROM NewsItemTable WHERE feed_id = :feed_id ORDER BY timestamp ASC LIMIT 15");
    query.bindValue(":feed_id", feedItem->getDbId());
    if (!query.exec()) {
        qDebug() << "Could not load news for feed id: " << feedItem->getDbId();
        // TODO : add error signal
        
        emit finished(this);
        return;
    }
    
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
        
        // Add directly to the model's data structure.
        feedItem->getNewsList()->append(newsItem);
        
        // If this is the bookmark, link 'er up.
        if (newsItem->getDbID() == feedItem->getBookmarkID())
            feedItem->setBookmark(newsItem, false);
    }
    
    emit finished(this);
}
