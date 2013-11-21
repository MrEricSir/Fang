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
                    query.value("bookmark_id").toULongLong(),
                    NULL
                    );
        
        tempFeedItemList.append(item);
    }
    
    // Finally, put All News at the front and throw everything into the feed list.
    tempFeedItemList.push_front(allNews);
    feedList->appendRows(tempFeedItemList);
    
    // ...and we're done!  Yay!
    emit finished(this);
}
