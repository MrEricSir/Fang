#include "RemoveFeedOperation.h"

#include <QDebug>
#include <QThread>

#include "../utilities/UnreadCountReader.h"
#include "../FangApp.h"

RemoveFeedOperation::RemoveFeedOperation(OperationManager *parent, FeedItem* feed, ListModel *feedList) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    feedList(feedList)
{
    Q_ASSERT(feed != NULL);
    Q_ASSERT(feedList != NULL);
}

void RemoveFeedOperation::execute()
{
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
    
    // Remove from the model (if it hasn't been already!)
    feedList->removeItem(feed);
    
    // Update the unread count of our special feeds.
    UnreadCountReader::update(db(), FangApp::instance()->getFeedForID(FEED_ID_ALLNEWS));
    UnreadCountReader::update(db(), FangApp::instance()->getFeedForID(FEED_ID_PINNED));
    
    emit finished(this);
}
