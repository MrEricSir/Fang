#include "LoadAllNewsOperation.h"

LoadAllNewsOperation::LoadAllNewsOperation(OperationManager *parent, AllNewsFeedItem *feedItem, LoadMode mode, int loadLimit) :
    LisvelLoadNewsOperation(parent, feedItem, mode, loadLimit, true)
{
}


qint64 LoadAllNewsOperation::getFirstNewsID()
{
    const QString queryString = "SELECT id FROM NewsItemTable ORDER BY timestamp ASC, id ASC LIMIT 1";

    QSqlQuery query(db());
    query.prepare(queryString);

    if (!query.exec() || !query.next()) {
        // No news yet!
        return -1;
    }

    return query.value("id").toULongLong();
}

QString LoadAllNewsOperation::appendNewQueryString()
{
    return "SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from "
           "FeedItemTable WHERE id = N.feed_id) AND id NOT IN (" + getLoadedIDString() +
           ") ORDER BY timestamp ASC, id ASC LIMIT :load_limit";
}

QString LoadAllNewsOperation::prependNewQueryString()
{
    return "SELECT * FROM NewsItemTable N where id <= (SELECT bookmark_id from "
           "FeedItemTable WHERE id = N.feed_id) AND id NOT IN (" + getLoadedIDString() +
           ") ORDER BY timestamp DESC, id DESC LIMIT :load_limit";
}

QString LoadAllNewsOperation::appendAfterPositionQueryString()
{
    // Load items chronologically after a given position, regardless of bookmark.
    // Used to reload trimmed items when scrolling back down through read items.
    return "SELECT * FROM NewsItemTable N WHERE "
           "(timestamp > :last_timestamp OR (timestamp = :last_timestamp AND id > :last_id)) "
           "AND id NOT IN (" + getLoadedIDString() + ") "
           "ORDER BY timestamp ASC, id ASC LIMIT :load_limit";
}
