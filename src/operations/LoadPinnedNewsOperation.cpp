#include "LoadPinnedNewsOperation.h"

LoadPinnedNewsOperation::LoadPinnedNewsOperation(OperationManager *parent, PinnedFeedItem *feedItem, LoadMode mode, int loadLimit) :
    LisvelLoadNewsOperation(parent, feedItem, mode, loadLimit, false)
{
}


qint64 LoadPinnedNewsOperation::getFirstNewsID()
{
    const QString queryString = "SELECT id FROM NewsItemTable WHERE pinned ORDER BY timestamp ASC, id ASC LIMIT 1";

    QSqlQuery query(db());
    query.prepare(queryString);

    if (!query.exec() || !query.next()) {
        // No news yet!
        return -1;
    }

    return query.value("id").toULongLong();
}

QString LoadPinnedNewsOperation::appendNewQueryString()
{
    return "SELECT * FROM NewsItemTable WHERE pinned AND id NOT IN (" + getLoadedIDString() +
           ") ORDER BY timestamp ASC, id ASC LIMIT :load_limit";
}

QString LoadPinnedNewsOperation::prependNewQueryString()
{
    return "";
}


