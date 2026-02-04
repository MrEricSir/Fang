#include "LisvelLoadNewsOperation.h"
#include "src/models/NewsList.h"
#include "../utilities/ErrorHandling.h"
#include "../utilities/FangLogging.h"


LisvelLoadNewsOperation::LisvelLoadNewsOperation(OperationManager *parent, LisvelFeedItem *feedItem, LoadMode mode, int loadLimit, bool prependOnInit) :
    LoadNewsOperation(parent, feedItem, mode, loadLimit),
    lisvelNews(feedItem),
    prependOnInit(prependOnInit)
{
}

void LisvelLoadNewsOperation::executeSynchronous()
{
    qCDebug(logOperation) << "LisvelLoadNewsOperation::execute load for feed: " << lisvelNews->getDbID();

    // Ensure lists are empty just in case the operation object gets reused somehow.
    if (!listAppend.isEmpty() || !listPrepend.isEmpty()) {
        qCWarning(logOperation) << "LisvelLoadNewsOperation: Lists not empty at start!"
                                << "listAppend:" << listAppend.size()
                                << "listPrepend:" << listPrepend.size();
        listAppend.clear();
        listPrepend.clear();
    }

    // For an initial load, make sure the feed isn't populated yet.
    if (getMode() == LoadNewsOperation::Initial) {
        FANG_CHECK(feedItem->getNewsList() != nullptr || feedItem->getNewsList()->isEmpty(),
                   "LisvelLoadNewsOperation: Initial load on populated feed");
        // Clear the list for a fresh start if re-using an existing LisvelFeeditem.
        feedItem->getNewsList()->clear();
    }

    // DB query/ies.
    bool dbResult = true;
    switch (getMode()) {
    case Initial:
    {
        dbResult &= doAppend();  // First load everything after bookmark.

        if (prependOnInit) {
            dbResult &= doPrepend(); // Now the stuff on top
        }

        break;
    }

    case Append:
    {
        dbResult &= doAppend();

        break;
    }

    case Prepend:
    {
        dbResult &= doPrepend();

        break;
    }

    default:
        FANG_UNREACHABLE("Invalid LoadMode in LisvelLoadNewsOperation");
        break;
    }

    // Check if we done goofed.
    if (!dbResult) {
        reportError("DB error in LisvelLoadNewsOperation");

        return;
    }


    // For initial load, save the bookmark ID before modifying the lists.
    // We'll set the bookmark AFTER items are added to NewsList so the
    // NewsPosition can be properly captured.
    qint64 initialBookmarkID = -1;
    if (getMode() == Initial && !listPrepend.isEmpty()) {
        initialBookmarkID = listPrepend.first()->getDbID();

        // As an optimization, we only want to present *one* list -- an append list.
        // So we rewind our prepend list on top of it, then delete the prepend list.
        for (NewsItem* newsItem: std::as_const(listPrepend)) {
            listAppend.prepend(newsItem);
        }
        listPrepend.clear();
    }

    // Remove any duplicate IDs within the lists. (Note: should not be necessary.)
    QSet<qint64> seenIds;
    QList<NewsItem*> duplicatesToDelete;

    // Rmove duplicates from listAppend.
    for (int i = listAppend.size() - 1; i >= 0; --i) {
        NewsItem* item = listAppend.at(i);
        if (seenIds.contains(item->getDbID())) {
            qCCritical(logOperation) << "LisvelLoadNewsOperation: DUPLICATE ID" << item->getDbID()
                                     << "found in listAppend at index" << i << "- removing duplicate.";
            duplicatesToDelete.append(item);
            listAppend.removeAt(i);
        } else {
            seenIds.insert(item->getDbID());
        }
    }

    // Remove duplicates from listPrepend.
    for (int i = listPrepend.size() - 1; i >= 0; --i) {
        NewsItem* item = listPrepend.at(i);
        if (seenIds.contains(item->getDbID())) {
            qCCritical(logOperation) << "LisvelLoadNewsOperation: DUPLICATE ID" << item->getDbID()
                                     << "found in listPrepend at index" << i << "- removing duplicate.";
            duplicatesToDelete.append(item);
            listPrepend.removeAt(i);
        } else {
            seenIds.insert(item->getDbID());
        }
    }

    // Delete the duplicate NewsItem objects to prevent memory leaks.
    for (NewsItem* dup : duplicatesToDelete) {
        dup->deleteLater();
    }

    // Append/prepend items from our lists.
    // Note: listAppend/listPrepend may contain items that are already in NewsList
    // (paged from memory in step 1). We only call append/prepend for items NOT
    // already in the list. Paged items are already in NewsList (just outside the
    // display window) - pageUp/pageDown already expanded the window to include them.
    qCDebug(logOperation) << "LisvelLoadNewsOperation: Processing" << listAppend.size()
                          << "items to append," << listPrepend.size() << "items to prepend";

    int appendedCount = 0;
    int skippedAppend = 0;
    if (!listAppend.isEmpty()) {
        for (NewsItem* newsItem: std::as_const(listAppend)) {
            // Only add items not already in NewsList (i.e., items from DB queries).
            // Items paged from memory are already in NewsList - skip them.
            if (!feedItem->getNewsList()->containsID(newsItem->getDbID())) {
                feedItem->getNewsList()->append(newsItem);
                appendedCount++;
            } else {
                skippedAppend++;
            }
        }
    }

    int prependedCount = 0;
    int skippedPrepend = 0;
    if (!listPrepend.isEmpty()) {
        for (NewsItem* newsItem: std::as_const(listPrepend)) {
            // Only add items not already in NewsList.
            if (!feedItem->getNewsList()->containsID(newsItem->getDbID())) {
                feedItem->getNewsList()->prepend(newsItem);
                prependedCount++;
            } else {
                skippedPrepend++;
            }
        }
    }

    // Log final state
    qCDebug(logOperation) << "LisvelLoadNewsOperation: Added" << appendedCount << "appended,"
                          << prependedCount << "prepended. Skipped" << skippedAppend + skippedPrepend
                          << "already in list. NewsList now has"
                          << feedItem->getNewsList()->size() << "items in display window,"
                          << feedItem->getNewsList()->fullSize() << "total";

    // Set the bookmark, as by now the bookmarked item should be in the NewsList
    // with its correct position.
    if (initialBookmarkID >= 0) {
        feedItem->setBookmark(initialBookmarkID);
    }

    // Set the first possible ID for that top bookmark display action.
    lisvelNews->setFirstNewsID(getFirstNewsID());
}

bool LisvelLoadNewsOperation::doPrepend()
{
    // Remaining items to load.
    int remainingLoadLimit = getLoadLimit();
    NewsList* newsList = lisvelNews->getNewsList();

    // Log current list state for debugging
    if (!newsList->isEmpty()) {
        NewsItem* first = newsList->first();
        qCDebug(logOperation) << "doPrepend: First item in display window: id=" << first->getDbID()
                              << "timestamp=" << first->getTimestamp().toString(Qt::ISODate)
                              << "displayStart=" << newsList->getDisplayStart()
                              << "fullSize=" << newsList->fullSize();
    }

    //
    // STEP ONE: Page up through items already in memory (before the display window).
    //
    if (newsList->canPageUp()) {
        // Record current start before paging so we can add the newly-visible items to listPrepend.
        qsizetype oldDisplayStart = newsList->getDisplayStart();

        qsizetype paged = newsList->pageUp(remainingLoadLimit);
        qCDebug(logOperation) << "doPrepend step 1: Paged up" << paged << "items from memory";
        remainingLoadLimit -= paged;

        // Add the newly-visible items to listPrepend so they get sent to JS.
        // Items need to be in DESC order (newest first among the paged items) to match DB query order.
        for (qsizetype i = oldDisplayStart - 1; i >= newsList->getDisplayStart(); --i) {
            NewsItem* item = newsList->fullAt(i);
            if (item) {
                listPrepend.append(item);
            } else {
                qCWarning(logOperation) << "doPrepend: Unexpected null item at index" << i;
            }
        }
    }

    //
    // STEP TWO: Load new items from DB if we still need more.
    //
    QString prependQuery = prependNewQueryString();
    if (remainingLoadLimit > 0 && !prependQuery.isEmpty()) {
        QSqlQuery query(db());
        query.prepare(prependQuery);
        query.bindValue(":load_limit", remainingLoadLimit);
        bindQueryParameters(query);

        if (!query.exec()) {
            qCDebug(logOperation) << "Could not load news! (lisvel prepend step 2)";
            qCDebug(logOperation) << query.lastError();

            return false;
        }

        // Extract the query into our news list.
        int beforeCount = listPrepend.size();
        queryToNewsList(query, &listPrepend);

        // Log the prepended items to debug ordering issues
        qCDebug(logOperation) << "Prepend loaded" << (listPrepend.size() - beforeCount) << "items from DB";
        for (int i = beforeCount; i < listPrepend.size(); i++) {
            NewsItem* item = listPrepend.at(i);
            qCDebug(logOperation) << "  [" << i << "] id=" << item->getDbID()
                                  << "timestamp=" << item->getTimestamp().toString(Qt::ISODate)
                                  << "feed=" << item->getFeedId();
        }
    }

    return true;
}

bool LisvelLoadNewsOperation::doAppend()
{
    // Remaining items to load.
    int remainingLoadLimit = getLoadLimit();
    NewsList* newsList = lisvelNews->getNewsList();

    //
    // STEP ONE: Page down through items already in memory (after the display window).
    //
    if (newsList->canPageDown()) {
        // Record current end before paging so we can add the newly-visible items to listAppend.
        qsizetype oldDisplayEnd = newsList->getDisplayEnd();

        qsizetype paged = newsList->pageDown(remainingLoadLimit);
        qCDebug(logOperation) << "doAppend step 1: Paged down" << paged << "items from memory";
        remainingLoadLimit -= paged;

        // Add the newly-visible items to listAppend so they get sent to JS.
        for (qsizetype i = oldDisplayEnd; i < newsList->getDisplayEnd(); ++i) {
            NewsItem* item = newsList->fullAt(i);
            if (item) {
                listAppend.append(item);
            } else {
                qCWarning(logOperation) << "doAppend: Unexpected null item at index" << i;
            }
        }
    }

    // Get the last item for position-based queries
    NewsItem* lastItem = newsList->isEmpty() ? nullptr : newsList->last();

    //
    // STEP TWO: Load new (unread) items from DB.
    //
    if (remainingLoadLimit > 0) {
        QSqlQuery query(db());
        query.prepare(appendNewQueryString());
        query.bindValue(":load_limit", remainingLoadLimit);
        bindQueryParameters(query);

        if (!query.exec()) {
            qCDebug(logOperation) << "Could not load news! (lisvel append step 2)";
            qCDebug(logOperation) << query.lastError();

            return false;
        }

        // Extract the query into our news list.
        int beforeCount = listAppend.size();
        queryToNewsList(query, &listAppend);
        remainingLoadLimit -= (listAppend.size() - beforeCount);

        qCDebug(logOperation) << "doAppend step 2: Loaded" << (listAppend.size() - beforeCount) << "unread items from DB";
    }

    //
    // STEP THREE: If we still need items and have a position reference,
    // try loading items that come chronologically after the last item.
    // This handles loading read items that we haven't seen yet.
    //
    if (remainingLoadLimit > 0 && lastItem != nullptr) {
        QString fallbackQuery = appendAfterPositionQueryString();
        if (!fallbackQuery.isEmpty()) {
            QSqlQuery query(db());
            query.prepare(fallbackQuery);
            query.bindValue(":load_limit", remainingLoadLimit);
            query.bindValue(":last_timestamp", lastItem->getTimestamp());
            query.bindValue(":last_id", lastItem->getDbID());
            bindQueryParameters(query);

            if (query.exec()) {
                int beforeCount = listAppend.size();
                queryToNewsList(query, &listAppend);
                qCDebug(logOperation) << "doAppend step 3 (fallback): Loaded" << (listAppend.size() - beforeCount)
                                      << "items after position" << lastItem->getTimestamp().toString(Qt::ISODate);
            } else {
                qCDebug(logOperation) << "doAppend fallback query failed:" << query.lastError();
            }
        }
    }

    return true;
}

void LisvelLoadNewsOperation::bindQueryParameters(QSqlQuery& query)
{
    Q_UNUSED(query);
}

QString LisvelLoadNewsOperation::appendAfterPositionQueryString()
{
    // Default: no fallback query. Subclasses can override.
    return QString();
}

QString LisvelLoadNewsOperation::getLoadedIDString()
{
    // Get all IDs from the full NewsList to prevent loading duplicates.
    // positionAt() works even for unloaded items.
    NewsList* newsList = lisvelNews->getNewsList();

    QSet<qint64> ids;

    // Add IDs from the NewsList.
    qsizetype newsListCount = 0;
    for (qsizetype i = 0; i < newsList->fullSize(); ++i) {
        ids.insert(newsList->positionAt(i).id());
        newsListCount++;
    }

    // Also add IDs from items already loaded in this operation (listAppend/listPrepend).
    // This prevents the same item from being loaded by multiple steps within doAppend/doPrepend.
    qsizetype listAppendCount = 0;
    for (NewsItem* item : std::as_const(listAppend)) {
        if (!ids.contains(item->getDbID())) {
            listAppendCount++;  // Count only IDs not already in NewsList
        }
        ids.insert(item->getDbID());
    }
    qsizetype listPrependCount = 0;
    for (NewsItem* item : std::as_const(listPrepend)) {
        if (!ids.contains(item->getDbID())) {
            listPrependCount++;  // Count only IDs not already counted
        }
        ids.insert(item->getDbID());
    }

    qCDebug(logOperation) << "getLoadedIDString: Excluding" << ids.size() << "IDs"
                          << "(NewsList:" << newsListCount
                          << "listAppend:" << listAppendCount
                          << "listPrepend:" << listPrependCount << ")";

    if (ids.isEmpty()) {
        return "-1";  // Return invalid ID to avoid SQL syntax error with empty IN clause
    }

    QString ret = "";
    bool first = true;

    for (qint64 id : ids) {
        if (!first) {
            ret += ", ";
        }
        ret += QString::number(id);
        first = false;
    }

    return ret;
}
