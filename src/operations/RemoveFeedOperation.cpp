#include "RemoveFeedOperation.h"

#include <QDebug>
#include <QSqlError>
#include <QThread>

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
    
    if (feed->getDbId() >= 0) {
        // Delete that feed, bro.
        db().transaction();
        QSqlQuery query(db());
        if (!query.prepare("DELETE FROM FeedItemTable WHERE id = :feed_id")) {
            qDebug() << "Error preparing SQL query: " << query.lastError().text();
        }
        query.bindValue(":feed_id", feed->getDbId());
        
        if (!query.exec()) {
            qDebug() << "Unable to remove feed.";
            qDebug() << "SQL error: " << query.lastError().text();
            db().rollback();
            // TODO error signal.
            // *for now, fall thru to emit finished.*
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
