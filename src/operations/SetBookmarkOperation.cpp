#include "SetBookmarkOperation.h"
#include <QDebug>

#include "../models/AllNewsFeedItem.h"

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
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = "
                  "(SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2 )");
    query.bindValue(":bookmark_id", bookmarkItem->getDbID());
    query.bindValue(":bookmark_id2", bookmarkItem->getDbID());
    
    if (!query.exec()) {
        qDebug() << "Unable to set bookmark.";
        qDebug() << "SQL error: " << query.lastError().text();
        
        // TODO error signal.
    }
    
    emit finished(this);
}
