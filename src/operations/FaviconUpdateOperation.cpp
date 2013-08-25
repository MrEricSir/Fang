#include "FaviconUpdateOperation.h"
#include <QDebug>

FaviconUpdateOperation::FaviconUpdateOperation(QObject *parent, FeedItem* feed) :
    DBOperation(parent),
    feed(feed),
    grabber(),
    wasDestroyed(false)
{
    connect(feed, SIGNAL(destroyed()), this, SLOT(onFeedDestroyed()));
    connect(&grabber, SIGNAL(finished(QUrl)), this, SLOT(onGrabberFinished(QUrl)));
}

FaviconUpdateOperation::~FaviconUpdateOperation()
{
}

void FaviconUpdateOperation::execute()
{
    if (feed->getSiteURL().isValid() && !feed->getSiteURL().isRelative()) {
        grabber.find(feed->getSiteURL());
    } else {
        // No site to examine.  Try the feed URL instead.
        grabber.find(feed->getURL());
    }
}

void FaviconUpdateOperation::onGrabberFinished(const QUrl &faviconUrl)
{
    if (wasDestroyed || feed->getDbId() < 0) {
        // Nothing more to do!
        //qDebug() << "FaviconUpdateOperation: Feed was destroyed, nothing to update.";
        emit finished(this);
        
        return;
    }
    
    if (!faviconUrl.isValid() || faviconUrl.isRelative()) {
        // Not a valid URL.
        //qDebug() << "FaviconUpdateOperation: No valid URL to update.";
        emit finished(this);
        
        return;
    }
    
    if (faviconUrl == feed->getImageURL()) {
        //qDebug() << "FaviconUpdateOperation: URL has not changed.";
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
        qDebug() << "Unable to update favicon.";
        qDebug() << "SQL error: " << query.lastError().text();
        db().rollback();
        
        // TODO: error signal
    } else {
        db().commit();
        feed->setImageURL(faviconUrl);
    }
    
    emit finished(this);
}

void FaviconUpdateOperation::onFeedDestroyed()
{
    wasDestroyed = true;
}
