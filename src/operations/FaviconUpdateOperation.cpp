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
    
    // Only update icon once a week.
    QDateTime lastWeek = QDateTime::currentDateTime().addDays( -7 );
    if (feed->getLastIconUpdate() > lastWeek) {
        emit finished(this);
        
        return; // Nothing to do, bye!
    }
    
    if (feed->getSiteURL().isValid() && !feed->getSiteURL().isRelative()) {
        grabber.find(feed->getSiteURL());
    } else {
        // No site to examine.  Try the feed URL instead.
        grabber.find(feed->getURL());
    }
}

void FaviconUpdateOperation::onGrabberFinished(const QUrl &faviconUrl)
{
    FANG_BACKGROUND_CHECK;
    
    if (!faviconUrl.isValid() || faviconUrl.isRelative()) {
        // Not a valid URL.
        reportError("No valid URL to update. URL is: " + faviconUrl.toString());
        
        return;
    }
    
    QDateTime now = QDateTime::currentDateTime();
    
    if (faviconUrl == feed->getImageURL()) {
        // Well, we got the same favicon.  What a surprise!  Only not.
        
        // Update timestamp.
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
        
        //qDebug() << "FaviconUpdateOperation: URL has not changed.";
        emit finished(this);
        
        return;
    }
    
    // Save the new URL to the DB. Oh, and update the timestamp.
    db().transaction();
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET imageURL = :imageURL, "
                  "lastIconUpdate = :lastIconUpdate WHERE id = :id");
    query.bindValue(":id", feed->getDbID());
    query.bindValue(":imageURL", faviconUrl.toString());
    query.bindValue(":lastIconUpdate", now.toMSecsSinceEpoch());
    
    if (!query.exec()) {
        reportSQLError(query, "Unable to update favicon.");
        db().rollback();
        
        return;
    } else {
        db().commit();
        feed->setImageURL(faviconUrl);
        feed->setLastIconUpdate(now);
    }
    
    emit finished(this);
}
