#include "LoadAllFeedsOperation.h"

#include <QDebug>
#include <QMap>

#include "../models/NewsItem.h"

LoadAllFeedsOperation::LoadAllFeedsOperation(QObject *parent, ListModel *feedList) :
    DBOperation(parent),
    feedList(feedList)
{
}

LoadAllFeedsOperation::~LoadAllFeedsOperation()
{
}


void LoadAllFeedsOperation::execute()
{
    // Immediately add All News.
    {
        QString title("All News");
        QString subtitle("");
        QDateTime lastUpdated;
        quint32 minUpdate = 0;
        QUrl url("");
        QUrl imageUrl("");
        
        feedList->appendRow(new FeedItem(0, title, subtitle, lastUpdated, minUpdate, url, imageUrl,
                                         imageUrl, NULL, feedList));
    }
    
    // Kindly ask the database for the rest.
    QSqlQuery query(db());
    if (!query.exec("SELECT * FROM FeedItemTable ORDER BY ordinal ASC")) {
        qDebug() << "Could not load feeds. :(";
        // TODO : add error signal
        return;
    }
    
    QList<FeedItem*> tempFeedItemList;
    QMap<FeedItem*, qint64> bookmarkIdMap; // I hate to associate via hashmap, but...
    while (query.next()) {
        FeedItem* item = new FeedItem(
                    query.value("id").toULongLong(),
                    query.value("title").toString(),
                    query.value("subtitle").toString(),
                    QDateTime::fromMSecsSinceEpoch(query.value("lastUpdated").toLongLong()),
                    query.value("minutesToUpdate").toUInt(),
                    query.value("url").toString(),
                    query.value("siteURL").toString(),
                    query.value("imageURL").toString(),
                    NULL
                    );
        
        bookmarkIdMap.insert(item, query.value("bookmark_id").toULongLong());
        tempFeedItemList.append(item);
    }
    
    // Load news items for each feed.
    foreach (FeedItem* item, tempFeedItemList) {
        QSqlQuery query(db());
        query.prepare("SELECT * FROM NewsItemTable WHERE feed_id = :feed_id ORDER BY timestamp ASC");
        query.bindValue(":feed_id", item->getDbId());
        if (!query.exec()) {
            qDebug() << "Could not load news for feed id: " << item->getDbId();
            // TODO : add error signal
            continue;
        }
        
        // Lookup the bookmark id.
        qint64 bookmarkId = bookmarkIdMap.value(item, -1);
        
        while (query.next()) {
            // Load from DB query result.
            NewsItem* newsItem = new NewsItem(
                        item,
                        query.value("id").toULongLong(),
                        query.value("title").toString(),
                        query.value("author").toString(),
                        query.value("summary").toString(),
                        query.value("content").toString(),
                        QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong()), 
                        query.value("url").toString()
                        );
            
            // Add to the model.
            item->append(newsItem);
            
            // If this is the bookmark, link 'er up.
            if (newsItem->getDbID() == bookmarkId)
                item->setBookmark(newsItem);
        }
    }
    
    // Finally, add our feeds to the model.
    foreach (FeedItem* item, tempFeedItemList)
        feedList->appendRow(item);
    
    // ...and we're done!  Yay!
    emit finished(this);
}
