#include "SetBookmarkOperation.h"
#include <QDebug>
#include <QSqlError>

SetBookmarkOperation::SetBookmarkOperation(QObject *parent, FeedItem* feed, NewsItem* bookmarkItem) :
    DBOperation(parent),
    feed(feed),
    bookmarkItem(bookmarkItem)
{
}

SetBookmarkOperation::~SetBookmarkOperation()
{
}


void SetBookmarkOperation::execute()
{
    feed->setBookmark(bookmarkItem);
    
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = :feed_id");
    query.bindValue(":bookmark_id", bookmarkItem->getDbID());
    query.bindValue(":feed_id", feed->getDbId());
    
    if (!query.exec()) {
        qDebug() << "Unable to set bookmark.";
        qDebug() << "SQL error: " << query.lastError().text();
        
        // TODO error signal.
    }
    
    emit finished(this);
}
