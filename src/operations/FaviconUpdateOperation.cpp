#include "FaviconUpdateOperation.h"
#include <QDebug>
#include <QDateTime>

FaviconUpdateOperation::FaviconUpdateOperation(OperationManager *parent, FeedItem* feed) :
    DBOperation(BACKGROUND, parent),
    feed(feed),
    grabber()
{
    connect(&grabber, &FaviconGrabber::finished, this, &FaviconUpdateOperation::onGrabberFinished);
    
    requireObject(feed);
}

FaviconUpdateOperation::~FaviconUpdateOperation()
{
}

void FaviconUpdateOperation::execute()
{
    FANG_BACKGROUND_CHECK;

    // Only update icon once a week, unless we need to convert a URL to data URI.
    QDateTime lastWeek = QDateTime::currentDateTime().addDays(-7);
    if (feed->getLastIconUpdate() > lastWeek && feed->getImageURL().scheme() == "data") {
        emit finished(this);
        return; // Already up-to-date and embedded, nothing to do.
    }

    if (feed->getSiteURL().isValid() && !feed->getSiteURL().isRelative()) {
        grabber.find(feed->getSiteURL());
    } else {
        // No site to examine. Try the feed URL instead.
        grabber.find(feed->getURL());
    }
}

void FaviconUpdateOperation::onGrabberFinished(const QString& faviconDataUri)
{
    FANG_BACKGROUND_CHECK;

    if (faviconDataUri.isEmpty()) {
        reportError("No favicon found.");
        return;
    }

    QDateTime now = QDateTime::currentDateTime();

    // Convert data URI to QUrl for comparison and storage.
    QUrl dataUrl(faviconDataUri);

    if (dataUrl == feed->getImageURL()) {
        // Same favicon as before. Just update the timestamp.
        db().transaction();
        QSqlQuery query(db());
        query.prepare("UPDATE FeedItemTable SET lastIconUpdate = :lastIconUpdate WHERE id = :id");
        query.bindValue(":id", feed->getDbID());
        query.bindValue(":lastIconUpdate", now.toMSecsSinceEpoch());

        if (!query.exec()) {
            reportSQLError(query, "Unable to update favicon update timestamp.");
            db().rollback();
            return;
        } else {
            db().commit();
            feed->setLastIconUpdate(now);
        }

        emit finished(this);
        return;
    }

    // Save the favicon data to the DB and and update the timestamp.
    db().transaction();
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET imageURL = :imageURL, "
                  "lastIconUpdate = :lastIconUpdate WHERE id = :id");
    query.bindValue(":id", feed->getDbID());
    query.bindValue(":imageURL", faviconDataUri);
    query.bindValue(":lastIconUpdate", now.toMSecsSinceEpoch());

    if (!query.exec()) {
        reportSQLError(query, "Unable to update favicon.");
        db().rollback();
        return;
    } else {
        qDebug() << " ----- UPDATING FAVICON -----";
        db().commit();
        feed->setImageURL(dataUrl);
        feed->setLastIconUpdate(now);
    }

    emit finished(this);
}
