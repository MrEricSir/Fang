#include "RemoveFeedOperation.h"

#include <QDebug>
#include <QThread>

RemoveFeedOperation::RemoveFeedOperation(QObject *parent, FeedItem* feed, ListModel *feedList) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    feedList(feedList)
{
    
}

void RemoveFeedOperation::execute()
{
    Q_ASSERT(feed != NULL);
    Q_ASSERT(feedList != NULL);
    
    if (feed->getDbId() >= 0) {
        // Delete that feed, bro.
        db().transaction();
        QSqlQuery query(db());
        if (!query.prepare("DELETE FROM FeedItemTable WHERE id = :feed_id")) {
            reportSQLError(query, "Error preping SQL statement to remove a feed");
                    
            return;
        }
        query.bindValue(":feed_id", feed->getDbId());
        
        if (!query.exec()) {
            reportSQLError(query, "Unable to remove feed.");
            db().rollback();
            
            return;
        } else {
            // Good to go!
            //qDebug() << "Removal allegedly worked!";
            db().commit();
            feed->clearDbId(); // Remember that we did this.
        }
        
        // Well, that's it.  If SQLite did what we asked, all the corresponding
        // news items were removed as well.  And if not, D. Richard ain't so Hipp.
    } else {
        qDebug() << "Could not delete feed from database, id is: " << feed->getDbId();
    }
    
    // Remove from the model.
    feedList->removeItem(feed);
    
    emit finished(this);
}
