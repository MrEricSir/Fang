#include "SetBookmarkOperation.h"
#include <QDebug>

#include "../models/AllNewsFeedItem.h"
#include "../utilities/UnreadCountReader.h"
#include "../FangApp.h"

SetBookmarkOperation::SetBookmarkOperation(QObject *parent, FeedItem* feed, NewsItem* bookmarkItem) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    bookmarkItem(bookmarkItem)
{
}

SetBookmarkOperation::~SetBookmarkOperation()
{
}


void SetBookmarkOperation::execute()
{
    qint64 feedItemID = -1;
    db().transaction();
    
    // Step 1: Grab the ID of the feed.
    QSqlQuery query(db());
    query.prepare("SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id");
    query.bindValue(":bookmark_id", bookmarkItem->getDbID());
    
    if (!query.exec() || !query.next()) {
        db().rollback();
        
        qDebug() << "Unable to get ID of news item to set bookmark.";
        qDebug() << "SQL error: " << query.lastError().text();
        
        // TODO error signal.
        emit finished(this);
        return;
    }
    
    feedItemID = query.value(0).toLongLong();
    
    // Step 2: Set the feed's bookmark.
    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = "
                  ":feed_id");
    update.bindValue(":bookmark_id", bookmarkItem->getDbID());
    update.bindValue(":feed_id", feedItemID);
    
    if (!update.exec()) {
        db().rollback();
        
        qDebug() << "Unable to set bookmark to " << bookmarkItem->getDbID() << " for feed id: " << feedItemID;
        qDebug() << "SQL error: " << query.lastError().text();
        
        // TODO error signal.
        emit finished(this);
        return;
    }
    
    // Update unread count for both the feed and All News.
    UnreadCountReader::update(db(), FangApp::instance()->getFeedForID(feedItemID));
    UnreadCountReader::update(db(), FangApp::instance()->getFeed(0));
    
    db().commit();
    
    emit finished(this);
}
