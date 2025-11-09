#include "LisvelFeedItem.h"
#include "src/models/NewsItem.h"
#include "src/models/NewsList.h"

LisvelFeedItem::LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString& title, QObject *parent) :
    FeedItem(id, ordinal, title, "", QDateTime(), 0, QUrl(), QUrl(), "", QUrl(), QDateTime(), -1, true, parent)
{
}

bool LisvelFeedItem::canBookmark(qint64 bookmarkID, bool allowBackward)
{
    // You FAIL!
    if (bookmarkID < -1) {
        return false;
    }

    // Given no current bookmark, anything will do.
    if (getBookmark() == nullptr) {
        return true;
    }

    // No change.
    if (getBookmark()->getDbID() == bookmarkID) {
        return false;
    }

    // ASSUMPTION: Since we always start from the bookmark, if the bookmark ID isn't -1 it
    // must therefore be in the _newsIDs list, my dear Watson.
    if (getBookmark()->getDbID() < 0) {
        return true;
    }

    // YOLO
    if (allowBackward) {
        return true;
    }

    // Compare index of proposed bookmark to index of current bookmark.
    qsizetype proposedIndex = bookmarkID == -1 ? 0 : getNewsList()->indexForItemID(bookmarkID);
    qsizetype currentIndex = getNewsList()->indexOf(getBookmark());
    Q_ASSERT(proposedIndex >= 0); // It HAS TO be in the news ids list at this point, or you're screwed.

    return proposedIndex > currentIndex;
}
