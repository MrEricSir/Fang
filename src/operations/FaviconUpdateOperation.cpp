#include "FaviconUpdateOperation.h"
#include <QDebug>

FaviconUpdateOperation::FaviconUpdateOperation(OperationManager *parent, FeedItem* feed) :
    DBOperation(BACKGROUND, parent),
    feed(feed),
    grabber()
{
    connect(&grabber, SIGNAL(finished(QUrl)), this, SLOT(onGrabberFinished(QUrl)));
    
    requireObject(feed);
}

FaviconUpdateOperation::~FaviconUpdateOperation()
{
}

void FaviconUpdateOperation::execute()
{
    FANG_BACKGROUND_CHECK;
    
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
        reportError("No valid URL to update.");
        
        return;
    }
    
    if (faviconUrl == feed->getImageURL()) {
        //qDebug() << "FaviconUpdateOperation: Nothing to do: URL has not changed.";
        emit finished(this);
        
        return;
    }
    
    // Save the new URL to the DB.
    db().transaction();
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET imageURL = :imageURL WHERE id = :id");
    query.bindValue(":id", feed->getDbId());
    query.bindValue(":imageURL", faviconUrl.toString());
    
    if (!query.exec()) {
        reportSQLError(query, "Unable to update favicon.");
        db().rollback();
        
        return;
    } else {
        db().commit();
        feed->setImageURL(faviconUrl);
    }
    
    emit finished(this);
}
