#include "LoadFolderOperation.h"


LoadFolderOperation::LoadFolderOperation(OperationManager *parent, FolderFeedItem *feedItem, LoadNewsOperation::LoadMode mode, int loadLimit)
    : LisvelLoadNewsOperation(parent, feedItem, mode, loadLimit, true)
{

}

LoadFolderOperation::~LoadFolderOperation()
{

}

qint64 LoadFolderOperation::getFirstNewsID()
{
    const QString queryString = "SELECT id FROM NewsItemTable WHERE feed_id IN "
                                "(SELECT id FROM FeedItemTable F WHERE "
                                "F.parent_folder = :parent_folder) "
                                "ORDER BY timestamp ASC, id ASC LIMIT 1";

    QSqlQuery query(db());
    query.prepare(queryString);
    query.bindValue(":parent_folder", feedItem->getDbID());

    if (!query.exec() || !query.next()) {
        // No news yet!
        return -1;
    }

    return query.value("id").toULongLong();
}

QString LoadFolderOperation::appendNewQueryString()
{
    return "SELECT * FROM NewsItemTable N WHERE N.feed_id IN "
           "(SELECT id FROM FeedItemTable WHERE parent_folder = :parent_folder) "
           "AND id > (SELECT bookmark_id FROM FeedItemTable WHERE id = N.feed_id) AND "
           "id NOT IN (" + getLoadedIDString() + ") "
           "ORDER BY timestamp ASC, id ASC LIMIT :load_limit";
}

QString LoadFolderOperation::prependNewQueryString()
{
    return "SELECT * FROM NewsItemTable N WHERE N.feed_id IN "
           "(SELECT id FROM FeedItemTable WHERE parent_folder = :parent_folder) "
           "AND id <= (SELECT bookmark_id FROM FeedItemTable WHERE id = N.feed_id) AND "
           "id NOT IN (" + getLoadedIDString() + ") "
           "ORDER BY timestamp DESC, id DESC LIMIT :load_limit";
}

QString LoadFolderOperation::appendAfterPositionQueryString()
{
    // Load items chronologically after a given position, regardless of bookmark.
    // Used to reload trimmed items when scrolling back down through read items.
    return "SELECT * FROM NewsItemTable N WHERE N.feed_id IN "
           "(SELECT id FROM FeedItemTable WHERE parent_folder = :parent_folder) "
           "AND (timestamp > :last_timestamp OR (timestamp = :last_timestamp AND id > :last_id)) "
           "AND id NOT IN (" + getLoadedIDString() + ") "
           "ORDER BY timestamp ASC, id ASC LIMIT :load_limit";
}

void LoadFolderOperation::bindQueryParameters(QSqlQuery& query)
{
    query.bindValue(":parent_folder", feedItem->getDbID());
}
