#include "LoadNews.h"
#include <QDebug>

LoadNews::LoadNews(QObject *parent, FeedItem* feedItem, bool append, int loadLimit) :
    DBOperation(parent),
    feedItem(feedItem),
    append(append),
    loadLimit(loadLimit),
    newsList(NULL)
{
}

void LoadNews::execute()
{
    // Start with lowest possible ID.
    qint64 startId = -1;
    
    if (feedItem->getNewsList() != NULL && feedItem->getNewsList()->size() > 0) {
        // If the news list already has one or more items, set the start ID to the
        // first or last item in the list.
        startId = append ? feedItem->getNewsList()->last()->getDbID() :
                           feedItem->getNewsList()->first()->getDbID();
        
        qDebug() << "start id is: " << startId;
    }
    
    // TODO: handle prepend
    QSqlQuery query(db());
    query.prepare("SELECT * FROM NewsItemTable WHERE feed_id = :feed_id AND id > :start_id ORDER BY timestamp ASC LIMIT 15");
    query.bindValue(":feed_id", feedItem->getDbId());
    query.bindValue(":start_id", startId);
    if (!query.exec()) {
        qDebug() << "Could not load news for feed id: " << feedItem->getDbId();
        // TODO : add error signal
        
        emit finished(this);
        return;
    }
    
    // Create our list.
    newsList = new QList<NewsItem*>();
    
    // If we find the bookmark during the load, this will be set.
    NewsItem* bookmark = NULL;
    
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
        newsList->append(newsItem);
        
        // Remember if we found the bookmark.
        if (newsItem->getDbID() == feedItem->getBookmarkID())
            bookmark = newsItem;
    }
    
    // Append all items.
    // TODO: handle prepend
    foreach (NewsItem* newsItem, *newsList)
        feedItem->getNewsList()->append(newsItem);
    
    // Set the bookmark if we found it.
    if (bookmark != NULL)
        feedItem->setBookmark(bookmark, false);
    
    // we r done lol
    emit finished(this);
}
