#include "ExpireNewsOperation.h"

#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

ExpireNewsOperation::ExpireNewsOperation(OperationManager *parent, ListModel *feedList, QDateTime olderThan, qint32 saveLast) :
    DBOperation(IMMEDIATE, parent), // Must be immediate because we need to stop the app from shutting down.
    feedList(feedList),
    olderThan(olderThan),
    saveLast(saveLast)
{

}

void ExpireNewsOperation::execute()
{
    bool performVacuum = false;

    {
        db().transaction();

        // SQL can't easily do loops, so we need a little C++ magic.
        for (int i = 0; i < feedList->rowCount(); i++) {
            FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
            if (feed->isSpecialFeed()) {
                // Can't delete a special feed, DUH.
                continue;
            }

            QSqlQuery query(db());
            query.prepare("DELETE FROM NewsItemTable WHERE feed_id = :feed_id AND NOT pinned "
                          "AND id < ( SELECT bookmark_id FROM FeedItemTable WHERE id = :feed_id2 LIMIT 1 ) "
                          "AND timestamp < :olderThan AND id NOT IN "
                          "( SELECT id FROM NewsItemTable WHERE feed_id = :feed_id3 ORDER BY timestamp DESC LIMIT :saveLast )");
            query.bindValue(":feed_id", feed->getDbID());
            query.bindValue(":feed_id2", feed->getDbID());
            query.bindValue(":olderThan", olderThan.toMSecsSinceEpoch());
            query.bindValue(":feed_id3", feed->getDbID());
            query.bindValue(":saveLast", saveLast);

            if (!query.exec()) {
                reportSQLError(query, "Unable to remove old feed.");
                db().rollback();

                return;
            }

            if (query.numRowsAffected() > 0) {
                performVacuum = true;
            }
        }

        db().commit();
    }

    // If our delete accomplished anything, let's reclaim lost disk space with SQLite's VACUUM command.
    // According to the SQLite docs, you can't have an open transaction while vacuuming.
    if (performVacuum) {
        QSqlQuery query(db());
        query.exec("VACUUM");
    }

    emit finished(this);
}
