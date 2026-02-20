#include "SetFolderOpenOperation.h"

SetFolderOpenOperation::SetFolderOpenOperation(OperationManager *parent, FeedItem* feed) :
    DBOperation(parent),
    feed(feed)
{
}

void SetFolderOpenOperation::execute()
{
    // Don't persist special feeds.
    if (feed->isSpecialFeed()) {
        return;
    }

    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET folder_open = :folder_open WHERE id = :feed_id");
    query.bindValue(":folder_open", feed->data(FeedItem::FolderOpenRole).toBool());
    query.bindValue(":feed_id", feed->getDbID());

    if (!query.exec()) {
        reportSQLError(query, "Unable to save folder open state.");
        return;
    }
}
