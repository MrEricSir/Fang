#include "RemoveFeedOperation.h"

#include <QDebug>
#include <QSqlError>

RemoveFeedOperation::RemoveFeedOperation(QObject *parent, FeedItem* feed, ListModel *feedList) :
    DBOperation(parent),
    feed(feed),
    feedList(feedList)
{
}

void RemoveFeedOperation::execute()
{
    Q_ASSERT(feed != NULL);
    Q_ASSERT(feedList != NULL);
    
    // Remove from the model.
    feedList->removeItem(feed);
    
    if (feed->getDbId() >= 0) {
        // Delete that feed, bro.
        QSqlQuery query(db());
        query.prepare("DELETE FROM FeedItemTable WHERE id=:feed_id");
        query.bindValue(":feed_id", feed->getDbId());
        
        if (!query.exec()) {
            qDebug() << "Unable to remove feed.";
            qDebug() << "SQL error: " << query.lastError().text();
            
            // TODO error signal.
            // *for now, fall thru to emit finished.*
        }
        
        // Well, that's it.  If SQLite did what we asked, all the corresponding
        // news items were removed as well.  And if not, D. Richard ain't so Hipp.
    }
    
    //feed->deleteLater(); // Well, bye.
    
    emit finished(this);
}
