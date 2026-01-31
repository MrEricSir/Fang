#include "UpdateFeedURLOperation.h"
#include "../utilities/FangLogging.h"

UpdateFeedURLOperation::UpdateFeedURLOperation(OperationManager *parent, FeedItem* feed, QUrl newURL) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    newURL(newURL)
{
    requireObject(feed);
}

void UpdateFeedURLOperation::execute()
{
    qCDebug(logOperation) << "Updating feed URL from " << feed->getURL() << " to " << newURL;

    db().transaction();

    // Update URL
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET url = :url WHERE id = :feed_id");
    query.bindValue(":feed_id", feed->getDbID());
    query.bindValue(":url", newURL);

    if (!query.exec()) {
        reportSQLError(query, "Unable to update feed URL");
        db().rollback();

        emit finished(this);
        return;
    }

    db().commit();
    feed->setURL(newURL); // May or may not be needed, shouldn't hurt either way.
    emit finished(this);
}
