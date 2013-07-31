#include "LoadAllFeedsOperation.h"

#include <QDebug>

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
        
        feedList->appendRow(new FeedItem(0, title, subtitle, lastUpdated, minUpdate, url, imageUrl, feedList));
    }
    
    // Kindly ask the database for the rest.
    QSqlQuery query(db());
    if (!query.exec("SELECT * FROM FeedItemTable ORDER BY ordinal ASC")) {
        qDebug() << "Could not load feeds. :(";
        // TODO : add error signal
        return;
    }
    
    while (query.next()) {
        FeedItem* item = new FeedItem(
                    query.value("id").toULongLong(),
                    query.value("title").toString(),
                    query.value("subtitle").toString(),
                    QDateTime::fromMSecsSinceEpoch(query.value("lastUpdated").toLongLong()),
                    query.value("minutesToUpdate").toUInt(),
                    query.value("url").toString(),
                    query.value("imageURL").toString()
                    );
        
        feedList->appendRow(item);
    }
    
    // Now load news items for each feed.
    // Start at one since All News is not a real feed.
    for (int i = 1; i < feedList->rowCount(); i++) {
        FeedItem* item = (FeedItem*) feedList->row(i);
        
        QSqlQuery query(db());
        query.prepare("SELECT * FROM NewsItemTable WHERE feed_id = :feed_id ORDER BY timestamp DESC");
        query.bindValue(":feed_id", item->getDbId());
        if (!query.exec()) {
            qDebug() << "Could not load news for feed id: " << item->getDbId();
            // TODO : add error signal
            continue;
        }
        
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
        }
    }
    
    // ...and we're done!  Yay!
    emit finished(this);
}
