#include "ReloadNewsOperation.h"
#include "../utilities/FangLogging.h"

#include <QSqlQuery>
#include <QSqlError>

ReloadNewsOperation::ReloadNewsOperation(OperationManager *parent, FeedItem* feedItem, const QList<qint64>& ids) :
    DBOperation(parent),
    feedItem(feedItem),
    idsToReload(ids),
    reloadedItems()
{
}

void ReloadNewsOperation::execute()
{
    if (idsToReload.isEmpty()) {
        qCDebug(logOperation) << "ReloadNewsOperation: No IDs to reload";
        return;
    }

    // Build the IN clause for the query
    QStringList placeholders;
    for (int i = 0; i < idsToReload.size(); ++i) {
        placeholders << QString(":id%1").arg(i);
    }

    QString queryString = QString(
        "SELECT id, feed_id, title, author, summary, content, timestamp, url, pinned "
        "FROM NewsItemTable "
        "WHERE id IN (%1) "
        "ORDER BY timestamp ASC, id ASC"
    ).arg(placeholders.join(", "));

    QSqlQuery query(db());
    query.prepare(queryString);

    // Bind the ID values
    for (int i = 0; i < idsToReload.size(); ++i) {
        query.bindValue(QString(":id%1").arg(i), idsToReload.at(i));
    }

    if (!query.exec()) {
        qCWarning(logOperation) << "ReloadNewsOperation: Query failed:" << query.lastError().text();
        return;
    }

    // Create NewsItem objects from results
    while (query.next()) {
        NewsItem* newsItem = new NewsItem(
            feedItem,
            query.value("id").toLongLong(),
            query.value("feed_id").toLongLong(),
            query.value("title").toString(),
            query.value("author").toString(),
            query.value("summary").toString(),
            query.value("content").toString(),
            QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong()),
            query.value("url").toString(),
            query.value("pinned").toBool()
        );

        reloadedItems.append(newsItem);
    }

    qCDebug(logOperation) << "ReloadNewsOperation: Reloaded" << reloadedItems.size()
                          << "items for feed" << feedItem->getDbID();
}
