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

    // Get the position data (timestamp, id) for Lisvel ordering comparison.
    if (toBookmarkID >= 0) {
        NewsItem* item = getNewsList()->fullNewsItemForID(toBookmarkID);
        if (item) {
            _bookmarkPosition = NewsPosition(toBookmarkID, item->getTimestamp());
            qCDebug(logModel) << "LisvelFeedItem::setBookmark: ID" << toBookmarkID
                              << "timestamp" << item->getTimestamp().toString(Qt::ISODate);
        } else {
            // Item not in memory: clear the position so canBookmark will try to initialize
            // with the ID only (in other words, not the timestamp.)
            _bookmarkPosition = NewsPosition();
            qCDebug(logModel) << "LisvelFeedItem::setBookmark: ID" << toBookmarkID
                              << "not in memory, cleared position for lazy init";
        }
    } else {
        _bookmarkPosition = NewsPosition();
        qCDebug(logModel) << "LisvelFeedItem::setBookmark: Clearing bookmark";
    }
}

bool LisvelFeedItem::canBookmark(qint64 proposedBookmarkID, bool allowBackward)
{
    // Invalid ID.
    if (proposedBookmarkID < -1) {
        qCDebug(logModel) << "canBookmark: REJECTED - invalid ID" << proposedBookmarkID;
        return false;
    }

    // Given no current bookmark, anything will do.
    if (getBookmarkID() < 0) {
        qCDebug(logModel) << "canBookmark: ALLOWED - no current bookmark, accepting" << proposedBookmarkID;
        return true;
    }

    // No change.
    if (getBookmarkID() == proposedBookmarkID) {
        // Don't log this - it's very common and noisy
        return false;
    }

    // We can bookmark anything in this situation.
    if (allowBackward) {
        qCDebug(logModel) << "canBookmark: ALLOWED - allowBackward=true, proposed=" << proposedBookmarkID;
        return true;
    }

    // Get indices of both items in the list. We need to respect the order of this list as it
    // is expected to match what's displayed to the user on the web view.
    qsizetype proposedIndex = getNewsList()->fullIndexForItemID(proposedBookmarkID);
    qsizetype currentIndex = getNewsList()->fullIndexForItemID(getBookmarkID());

    qCDebug(logModel) << "canBookmark: proposed=" << proposedBookmarkID << "idx=" << proposedIndex
                      << "current=" << getBookmarkID() << "idx=" << currentIndex
                      << "listSize=" << getNewsList()->size();

    // Proposed item not in list.
    if (proposedIndex < 0) {
        qCDebug(logModel) << "canBookmark: REJECTED - proposed ID" << proposedBookmarkID << "not in list";
        return false;
    }

    // Both items in list, so compare the indicies.
    if (currentIndex >= 0) {
        bool result = proposedIndex > currentIndex;
        if (!result) {
            qCDebug(logModel) << "canBookmark: REJECTED - index" << proposedIndex << "<=" << currentIndex;
        }
        return result;
    }

    // Current bookmark not in list (was trimmed) so use NewsPosition comparison.
    qCDebug(logModel) << "canBookmark: Current bookmark" << getBookmarkID() << "not in list, using NewsPosition"
                      << "valid=" << _bookmarkPosition.isValid();

    // First, try to lazily initialize the bookmark position if we have the item now.
    // Also reinitialize if the position ID doesn't match the current bookmark ID
    // (could happen if state got out of sync).
    if (!_bookmarkPosition.isValid() || _bookmarkPosition.id() != getBookmarkID()) {
        NewsItem* bookmarkItem = getNewsList()->fullNewsItemForID(getBookmarkID());
        if (bookmarkItem) {
            _bookmarkPosition = NewsPosition(getBookmarkID(), bookmarkItem->getTimestamp());
            qCDebug(logModel) << "canBookmark: Lazy-initialized position to"
                              << _bookmarkPosition.timestamp().toString(Qt::ISODate);
        } else {
            // Can't find the item - clear stale position if IDs don't match
            if (_bookmarkPosition.isValid() && _bookmarkPosition.id() != getBookmarkID()) {
                qCDebug(logModel) << "canBookmark: Clearing stale position (ID mismatch:"
                                  << _bookmarkPosition.id() << "vs" << getBookmarkID() << ")";
                _bookmarkPosition = NewsPosition();
            }
        }
    }

    // Use NewsPosition comparison if available.
    if (_bookmarkPosition.isValid()) {
        // positionAt() works even if the item is unloaded.
        NewsPosition proposedPosition = getNewsList()->positionAt(proposedIndex);

        bool isAfter = proposedPosition.isAfter(_bookmarkPosition);
        qCDebug(logModel) << "canBookmark: NewsPosition comparison:"
                          << "proposed(" << proposedPosition.id() << "," << proposedPosition.timestamp().toString(Qt::ISODate) << ")"
                          << (isAfter ? ">" : "<=")
                          << "bookmark(" << _bookmarkPosition.id() << "," << _bookmarkPosition.timestamp().toString(Qt::ISODate) << ")";

        if (isAfter) {
            return true;
        }
        return false;
    }

    // No valid position available: this shouldn't happen.
    qCDebug(logModel) << "canBookmark: REJECTED - no valid bookmark position available";
    return false;
}
