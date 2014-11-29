#include "LoadPinnedNewsOperation.h"

LoadPinnedNewsOperation::LoadPinnedNewsOperation(OperationManager *parent, PinnedFeedItem *feedItem, LoadMode mode, int loadLimit) :
    LoadNews(parent, feedItem, mode, loadLimit),
    pinnedNews(feedItem)
{
}

void LoadPinnedNewsOperation::execute()
{
    // For an initial load, make sure the feed isn't populated yet.
    if (getMode() == LoadNews::Initial)
        Q_ASSERT(feedItem->getNewsList() != NULL || feedItem->getNewsList()->isEmpty());

    // DB query/ies.
    bool dbResult = true;
    switch (getMode()) {
    case Initial:
    {
        dbResult &= doAppend(-1); // Start at the start!

        break;
    }

    case Append:
    {
        dbResult &= doAppend(getStartIDForAppend());

        break;
    }

    case Prepend:
    {
        dbResult &= doPrepend(getStartIDForPrepend());

        break;
    }

    default:
        // This means you added a new mode, but didn't add it to this switch.  Jerk.
        Q_ASSERT(false);
    }

    // Check if we done goofed.
    if (!dbResult) {
        reportError("DB error in LoadPinnedNewsOperation");

        return;
    }

    // Append/prepend items from our lists.
    if (listAppend != NULL)
        foreach (NewsItem* newsItem, *listAppend) {
            // News item list.
            feedItem->getNewsList()->append(newsItem);
        }

    if (listPrepend != NULL)
        foreach (NewsItem* newsItem, *listPrepend) {
            // News item list.
            feedItem->getNewsList()->prepend(newsItem);
        }

    // And with that, we are done.
    emit finished(this);
}

bool LoadPinnedNewsOperation::executeLoadQuery(qint64 startId, bool append)
{
    QString direction = append ? ">=" : "<";
    QString sortOrder = append ? "ASC" : "DESC";
    QString queryString = "SELECT * FROM NewsItemTable WHERE pinned AND id "
            + direction + " :start_id ORDER BY timestamp " + sortOrder + ", id " + sortOrder
            + " LIMIT :load_limit";

    //qDebug() << "Query: " << queryString;
    QSqlQuery query(db());
    query.prepare(queryString);

    query.bindValue(":start_id", startId);
    query.bindValue(":load_limit", loadLimit);

    if (!query.exec()) {
       qDebug() << "Could not load news for feed id: " << feedItem->getDbId();
       qDebug() << query.lastError();

       return false;
    }

    // Extract the query into our news list.
    queryToNewsList(query, append ? listAppend : listPrepend);

    return true;
}


