#include "LoadAllFeedsOperation.h"

#include <QDebug>

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
                    QDateTime::fromMSecsSinceEpoch(query.value("lastUpdated").toInt()),
                    query.value("minutesToUpdate").toUInt(),
                    query.value("url").toString(),
                    query.value("imageURL").toString()
                    );
        
        feedList->appendRow(item);
    }
    
    // ...and we're done!  Yay!
    emit finished(this);
}
