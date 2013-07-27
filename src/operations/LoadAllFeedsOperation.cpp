#include "LoadAllFeedsOperation.h"

LoadAllFeedsOperation::LoadAllFeedsOperation(QObject *parent, ListModel *feedList) :
    Operation(parent),
    feedList(feedList)
{
}

LoadAllFeedsOperation::~LoadAllFeedsOperation()
{
}


void LoadAllFeedsOperation::execute()
{
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
    
    // ...and we're done!  Yay!
    emit finished(this);
}
