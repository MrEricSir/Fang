#include "SearchNewsOperation.h"
#include "../models/NewsList.h"
#include "../utilities/FangLogging.h"

#include <QRegularExpression>

SearchNewsOperation::SearchNewsOperation(OperationManager *parent, LisvelFeedItem *feedItem,
                                         LoadMode mode, const QString& searchQuery,
                                         Scope scope, qint64 scopeId, int loadLimit) :
    LisvelLoadNewsOperation(parent, feedItem, mode, loadLimit, false),  // prependOnInit = false
    searchQuery(searchQuery),
    scope(scope),
    scopeId(scopeId)
{
}

QString SearchNewsOperation::sanitizeSearchQuery(const QString& query) const
{
    // FTS5 query syntax special characters:
    // - Double quotes start phrase queries
    // - Asterisk is a prefix operator
    // - Parentheses group expressions
    // - Plus/minus are boolean operators
    // - Caret for column filters
    // - Colon for column specification
    // - AND, OR, NOT are boolean operators (case-insensitive)
    //
    // For user-entered queries, we wrap each word in double quotes to treat them as literals.

    QString sanitized = query.trimmed();
    if (sanitized.isEmpty()) {
        return QString();
    }

    // Split on whitespace and quote each term.
    QStringList terms = sanitized.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QStringList quotedTerms;

    for (const QString& term : terms) {
        // Escape double quotes.
        QString escaped = term;
        escaped.replace("\"", "\"\"");  // FTS5 escapes " by doubling it.

        // Wrap in double quotes to treat as literal
        quotedTerms.append("\"" + escaped + "\"");
    }

    // Join with spaces to AND the terms together.
    return quotedTerms.join(" ");
}

qint64 SearchNewsOperation::getFirstNewsID()
{
    QString sanitized = sanitizeSearchQuery(searchQuery);
    if (sanitized.isEmpty()) {
        return -1;
    }

    const QString queryString =
        "SELECT N.id FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH :search_query "
        "ORDER BY bm25(NewsItemFTS), N.timestamp DESC, N.id DESC "
        "LIMIT 1";

    QSqlQuery query(db());
    query.prepare(queryString);
    query.bindValue(":search_query", sanitized);

    if (!query.exec() || !query.next()) {
        return -1;
    }

    return query.value("id").toLongLong();
}

QString SearchNewsOperation::appendNewQueryString()
{
    // Note: bm25() returns negative values where more negative = more relevant,
    // so ORDER BY bm25() puts most relevant first.

    QString baseQuery =
           "SELECT "
           "  N.id, N.feed_id, N.guid, N.author, N.timestamp, N.url, N.pinned, "
           "  highlight(NewsItemFTS, 0, '<mark>', '</mark>') AS title, "
           "  N.summary, "
           "  N.content "
           "FROM NewsItemTable N "
           "JOIN NewsItemFTS F ON N.id = F.rowid ";

    // Add scope-specific JOINs and WHERE clauses
    QString scopeFilter;
    switch (scope) {
    case Scope::Feed:
        // Search within a specific feed
        scopeFilter = "AND N.feed_id = :scope_id ";
        break;

    case Scope::Folder:
        // Search within all feeds in a folder - need to join FeedItemTable
        baseQuery += "JOIN FeedItemTable FI ON N.feed_id = FI.id ";
        scopeFilter = "AND FI.parent_folder = :scope_id ";
        break;

    case Scope::Global:
    default:
        // No additional filter for global search
        break;
    }

    return baseQuery +
           "WHERE NewsItemFTS MATCH :search_query "
           + scopeFilter +
           "AND N.id NOT IN (" + getLoadedIDString() + ") "
           "ORDER BY bm25(NewsItemFTS), N.timestamp DESC, N.id DESC "
           "LIMIT :load_limit";
}

QString SearchNewsOperation::prependNewQueryString()
{
    // Prepend not supported for search results. This LISVEL window should handle this for us.
    return QString();
}

void SearchNewsOperation::bindQueryParameters(QSqlQuery& query)
{
    QString sanitized = sanitizeSearchQuery(searchQuery);
    query.bindValue(":search_query", sanitized);

    if (scope == Scope::Feed || scope == Scope::Folder) {
        query.bindValue(":scope_id", scopeId);
    }
}

void SearchNewsOperation::queryToNewsListWithHighlights(QSqlQuery& query, QList<NewsItem*>* list)
{
    while (query.next()) {
        QString title = query.value("title").toString();
        QString summary = query.value("summary").toString();
        QString content = query.value("content").toString();

        // Debug our highlighting method.
        qCDebug(logOperation) << "SearchNewsOperation: Highlighted title:" << title.left(100);
        qCDebug(logOperation) << "SearchNewsOperation: Title contains <mark>:" << title.contains("<mark>");

        NewsItem* newsItem = new NewsItem(
            feedItem,
            query.value("id").toLongLong(),
            query.value("feed_id").toLongLong(),
            title,                                // Already highlighted
            query.value("author").toString(),     // Author not highlighted (column 3 in FTS)
            summary,                              // Already highlighted
            content,                              // Already highlighted
            QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong()),
            query.value("url").toString(),
            query.value("pinned").toInt() != 0
        );

        list->append(newsItem);
    }
}

void SearchNewsOperation::execute()
{
    qCDebug(logOperation) << "SearchNewsOperation::executeSynchronous for query:" << searchQuery;

    // Validate search query.
    QString sanitized = sanitizeSearchQuery(searchQuery);
    if (sanitized.isEmpty()) {
        qCDebug(logOperation) << "SearchNewsOperation: Empty or invalid search query";
        return;
    }

    // Ensure lists are empty.
    if (!listAppend.isEmpty() || !listPrepend.isEmpty()) {
        qCWarning(logOperation) << "SearchNewsOperation: Lists not empty at start!";
        listAppend.clear();
        listPrepend.clear();
    }

    // For search, we only support Initial and Append modes.
    // Prepend doesn't make sense for relevance-ordered results - just return empty.
    LoadMode currentMode = getMode();
    if (currentMode == Prepend) {
        qCDebug(logOperation) << "SearchNewsOperation: Prepend mode not supported, returning empty";
        return;
    }

    // For Initial load, ensure the list is empty
    if (currentMode == Initial) {
        if (feedItem->getNewsList() != nullptr && !feedItem->getNewsList()->isEmpty()) {
            qCWarning(logOperation) << "SearchNewsOperation: Initial load but list not empty, clearing";
            feedItem->getNewsList()->clear();
        }
    }

    // Execute the search query
    QSqlQuery query(db());
    query.prepare(appendNewQueryString());
    query.bindValue(":load_limit", getLoadLimit());
    bindQueryParameters(query);

    if (!query.exec()) {
        qCWarning(logOperation) << "SearchNewsOperation: Query failed:" << query.lastError();
        reportError("Search query failed: " + query.lastError().text());
        return;
    }

    // Extract results with highlighted fields
    queryToNewsListWithHighlights(query, &listAppend);

    qCDebug(logOperation) << "SearchNewsOperation: Found" << listAppend.size() << "results";

    // Add items to the feed's news list
    if (!listAppend.isEmpty()) {
        for (NewsItem* newsItem : std::as_const(listAppend)) {
            if (!feedItem->getNewsList()->containsID(newsItem->getDbID())) {
                feedItem->getNewsList()->append(newsItem);
            }
        }
    }

    // Set the first news ID for bookmark display logic.
    // TODO: How does pinned news handle bookmarks? Maybe we could go that route.
    feedItem->setFirstNewsID(getFirstNewsID());
}
