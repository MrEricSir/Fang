#include "LoadAllFeedsOperation.h"

#include <QDebug>
#include <QMap>

#include "../models/NewsItem.h"
#include "../models/AllNewsFeedItem.h"

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
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);
    
    // Kindly ask the database for the rest.
    QSqlQuery query(db());
    if (!query.exec("SELECT * FROM FeedItemTable ORDER BY ordinal ASC")) {
        qDebug() << "Could not load feeds. :(";
        // TODO : add error signal
        return;
    }
    
    QList<ListItem*> tempFeedItemList; // Use ListItem so we can do an appendAll later.
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
    foreach (ListItem* _item, tempFeedItemList) {
        FeedItem* item = qobject_cast<FeedItem*>(_item);
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
                item->setBookmark(newsItem, false);
        }
    }
    
    // Finally, put All News at the front and throw everything into the feed list.
    tempFeedItemList.push_front(allNews);
    feedList->appendRows(tempFeedItemList);
    
    // ...and we're done!  Yay!
    emit finished(this);
}
