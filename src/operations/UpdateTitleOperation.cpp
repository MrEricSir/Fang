#include "UpdateTitleOperation.h"
#include "../models/AllNewsFeedItem.h"
#include <QDebug>

UpdateTitleOperation::UpdateTitleOperation(OperationManager *parent, FeedItem* feed) :
    DBOperation(parent),
    feed(feed)
{
}

void UpdateTitleOperation::execute()
{
    if (feed->metaObject() == &AllNewsFeedItem::staticMetaObject) {
        // Nope.
        
        return;
    }
    
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET title = :title WHERE id = :feed_id");
    query.bindValue(":title", feed->getTitle());
    query.bindValue(":feed_id", feed->getDbID());
    
    if (!query.exec()) {
        reportSQLError(query, "Unable to set title.");
        
        return;
    }
}
