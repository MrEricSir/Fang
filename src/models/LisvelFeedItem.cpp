#include "LisvelFeedItem.h"
#include "src/models/NewsItem.h"
#include "src/models/NewsList.h"
#include "../utilities/FangLogging.h"

LisvelFeedItem::LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString& title, QObject *parent) :
    FeedItem(id, ordinal, title, "", QDateTime(), 0, QUrl(), QUrl(), "", QUrl(), QDateTime(), -1, true, parent)
{
}

void LisvelFeedItem::setBookmark(qint64 toBookmarkID)
{
    // Call base class implementation.
    FeedItem::setBookmark(toBookmarkID);

    // Capture the position (timestamp, id) for proper ordering comparison.
    if (toBookmarkID >= 0) {
        NewsItem* item = getNewsList()->newsItemForID(toBookmarkID);
        if (item) {
            _bookmarkPosition = NewsPosition(toBookmarkID, item->getTimestamp());
            qCDebug(logModel) << "LisvelFeedItem::setBookmark: ID" << toBookmarkID
                              << "timestamp" << item->getTimestamp().toString(Qt::ISODate);
        } else {
            // Item not in list? Keep any existing position for comparison purposes.
            // The position will be set correctly when the item is eventually found.
            qCDebug(logModel) << "LisvelFeedItem::setBookmark: ID" << toBookmarkID
                              << "not in list yet, keeping existing position";
        }
    } else {
        _bookmarkPosition = NewsPosition();
        qCDebug(logModel) << "LisvelFeedItem::setBookmark: Clearing bookmark";
    }
}

bool LisvelFeedItem::canBookmark(qint64 proposedBookmarkID, bool allowBackward)
{
    // Invalid ID - reject.
    if (proposedBookmarkID < -1) {
        return false;
    }

    // Given no current bookmark, anything will do.
    if (getBookmarkID() < 0) {
        return true;
    }

    // No change.
    if (getBookmarkID() == proposedBookmarkID) {
        return false;
    }

    // We can bookmark anything in this situation.
    if (allowBackward) {
        return true;
    }

    // Get indices of both items in the list.
    // The list is already sorted by (timestamp ASC, id ASC), so index comparison
    // gives us the correct reading order.
    qsizetype proposedIndex = getNewsList()->indexForItemID(proposedBookmarkID);
    qsizetype currentIndex = getNewsList()->indexForItemID(getBookmarkID());

    // Proposed item not in list - reject.
    if (proposedIndex < 0) {
        qCDebug(logModel) << "canBookmark: REJECTED - proposed ID" << proposedBookmarkID << "not in list";
        return false;
    }

    // Both items in list - use index comparison (most reliable).
    if (currentIndex >= 0) {
        bool result = proposedIndex > currentIndex;
        qCDebug(logModel) << "canBookmark: Index comparison:" << proposedIndex << ">" << currentIndex << "=" << result;
        return result;
    }

    // Current bookmark not in list (was trimmed) so we use NewsPosition comparison.
    // First, try to lazily initialize the bookmark position if we have the item now.
    if (!_bookmarkPosition.isValid()) {
        NewsItem* bookmarkItem = getNewsList()->newsItemForID(getBookmarkID());
        if (bookmarkItem) {
            _bookmarkPosition = NewsPosition(getBookmarkID(), bookmarkItem->getTimestamp());
            qCDebug(logModel) << "canBookmark: Lazy-initialized position to"
                              << _bookmarkPosition.timestamp().toString(Qt::ISODate);
        }
    }

    // Use NewsPosition comparison if available.
    if (_bookmarkPosition.isValid()) {
        NewsItem* proposedItem = getNewsList()->at(proposedIndex);
        NewsPosition proposedPosition(proposedBookmarkID, proposedItem->getTimestamp());

        if (proposedPosition.isAfter(_bookmarkPosition)) {
            qCDebug(logModel) << "canBookmark: ALLOWED - position forward";
            return true;
        }
        qCDebug(logModel) << "canBookmark: REJECTED - position"
                          << proposedPosition.timestamp().toString(Qt::ISODate)
                          << "<=" << _bookmarkPosition.timestamp().toString(Qt::ISODate);
        return false;
    }

    // Last resort: No valid position available.
    // This shouldn't happen in normal operation, but reject to be safe.
    qCDebug(logModel) << "canBookmark: REJECTED - no valid bookmark position available";
    return false;
}
