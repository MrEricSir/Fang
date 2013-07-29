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
    
    /*
    // TODO: add sqlite layer
    // TODO: load news off disk
    
    // For now, make up the list.
    {
        QString title("All News");
        QString subtitle("");
        QDateTime lastUpdated;
        quint32 minUpdate = 0;
        QUrl url("http://www.mrericsir.com/blog/feed/");// TODO QUrl url("");
        QUrl imageUrl("");
        
        feedList->appendRow(new FeedItem(-1, title, subtitle, lastUpdated, minUpdate, url, imageUrl, feedList));
    }
    {
        QString title("MrEricSir.com");
        QString subtitle("");
        QDateTime lastUpdated;
        quint32 minUpdate = 0;
        QUrl url("http://www.mrericsir.com/blog/feed/");
        QUrl imageUrl("http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico");
        
        feedList->appendRow(new FeedItem(-1, title, subtitle, lastUpdated, minUpdate, url, imageUrl, feedList));
    }
    
    {
        QString title("Ars Technica");
        QString subtitle("");
        QDateTime lastUpdated;
        quint32 minUpdate = 0;
        QUrl url("http://rss.slashdot.org/Slashdot/slashdot");//http://feeds.arstechnica.com/arstechnica/index");
        QUrl imageUrl("http://static.arstechnica.net/favicon.ico");
        
        feedList->appendRow(new FeedItem(-1, title, subtitle, lastUpdated, minUpdate, url, imageUrl, feedList));
    }
    
    */
    
    // ...and we're done!  Yay!
    emit finished(this);
}
