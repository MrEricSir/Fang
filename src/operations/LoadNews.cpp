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

void LoadNews::queryToNewsList(QSqlQuery& query)
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
        newsList->append(newsItem);
        
        // Remember if we found the bookmark.
        if (newsItem->getDbID() == feedItem->getBookmarkID())
            bookmark = newsItem;
    }    
}

void LoadNews::execute()
{
    // For an initial load, make sure the feed isn't populated yet.
    if (mode == LoadNews::Initial)
        Q_ASSERT(feedItem->getNewsList() != NULL || feedItem->getNewsList()->isEmpty());
    
    // Start with lowest possible ID.
    qint64 startId = -1;
    
    if (feedItem->getNewsList() != NULL && feedItem->getNewsList()->size() > 0) {
        // If the news list already has one or more items, set the start ID to the
        // first or last item in the list.
        startId = (mode == LoadNews::Append) ? feedItem->getNewsList()->last()->getDbID() :
                                               feedItem->getNewsList()->first()->getDbID();
    } else if (mode == LoadNews::Initial) {
        // For the initial load, start at the bookmark.
        startId = feedItem->getBookmarkID();
    }
    
    qDebug() << "start id is: " << startId;
    
    QSqlQuery query(db());
    
    // TODO: handle init load & prepend
    //   proally need a big ol' if else block here
    
    
    // The "internal" mode exists so if there's no bookmark and you're doing an initial load, we can just do
    // a plain ol' append instead.
    LoadMode internalMode = mode;
    //if (feedItem->getBookmarkID() < 0 && mode == LoadNews::Initial)
        internalMode = LoadNews::Append;
    
    QString queryString;
    switch (internalMode) {
    case LoadNews::Initial:
        queryString = "";
        break;
        
    case LoadNews::Append:
        queryString = "SELECT * FROM NewsItemTable WHERE feed_id = :feed_id AND id > :start_id ORDER BY timestamp ASC LIMIT :load_limit";
        break;
        
    case LoadNews::Prepend:
    default:
        Q_ASSERT(false); // should never reach here!!!!1
    }

    query.prepare(queryString);
    
    query.bindValue(":feed_id", feedItem->getDbId());
    query.bindValue(":start_id", startId);
    query.bindValue(":load_limit", loadLimit);
    
    if (!query.exec()) {
        qDebug() << "Could not load news for feed id: " << feedItem->getDbId();
        // TODO : add error signal
        emit finished(this);
        
        return;
    }
    
    // Create our list of news.
    newsList = new QList<NewsItem*>();
    
    // Extract the query into our news list.
    queryToNewsList(query);
    
    // Append all items.
    // TODO: handle prepend
    foreach (NewsItem* newsItem, *newsList)
        feedItem->getNewsList()->append(newsItem);
    
    // Set the bookmark if we found it.
    if (bookmark != NULL)
        feedItem->setBookmark(bookmark, false);
    
    // we r dun lol
    emit finished(this);
}
