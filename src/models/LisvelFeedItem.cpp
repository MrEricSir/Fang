#include "LisvelFeedItem.h"
#include "src/models/NewsItem.h"
#include "src/models/NewsList.h"

LisvelFeedItem::LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString& title, QObject *parent) :
    FeedItem(id, ordinal, title, "", QDateTime(), 0, QUrl(), QUrl(), "", QUrl(), QDateTime(), -1, true, parent)
{
}

bool LisvelFeedItem::canBookmark(qint64 proposedBookmarkID, bool allowBackward)
{
    // You FAIL!
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
    // ASSUMPTION: The bookmark ID is valid.
    if (allowBackward) {
        return true;
    }

    // Compare index of proposed bookmark to index of current bookmark.
    qsizetype proposedIndex = proposedBookmarkID == -1 ? 0 : getNewsList()->indexForItemID(proposedBookmarkID);
    qsizetype currentIndex = getNewsList()->indexForItemID(getBookmarkID());

    // If the bookmark ID wasn't find
    if (proposedIndex < 0) {
        qDebug() << "Bookmark ID not found in memory: " << proposedBookmarkID;
        return false;
    }

    // Otherwise, compare the index position of the proposed bookmark to the current one.
    return proposedIndex > currentIndex;
}
