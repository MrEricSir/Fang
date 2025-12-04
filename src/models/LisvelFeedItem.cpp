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
        // qDebug() << "canBookmark: yes because no current bookmark";
        return true;
    }

    // No change.
    if (getBookmark()->getDbID() == bookmarkID) {
        return false;
    }

    // ASSUMPTION: Since we always start from the bookmark, if the bookmark ID isn't -1 it
    // must therefore be in the _newsIDs list, my dear Watson.
    if (getBookmark()->getDbID() < 0) {
        // qDebug() << "canBookmark: yes because current bookmark has invalid id";
        return true;
    }

    // We can bookmark anything in this situation.
    // ASSUMPTION: The bookmark ID is valid.
    if (allowBackward) {
        // qDebug() << "canBookmark: allow backward is always true";
        return true;
    }

    // Compare index of proposed bookmark to index of current bookmark.
    qsizetype proposedIndex = bookmarkID == -1 ? 0 : getNewsList()->indexForItemID(bookmarkID);
    qsizetype currentIndex = getNewsList()->indexOf(getBookmark());

    // If the bookmark ID wasn't find
    if (proposedIndex < 0) {
        qDebug() << "Bookmark ID not found in memory: " << bookmarkID;
        return false;
    }

    // Otherwise, compare the index position of the proposed bookmark to the current one.
    return proposedIndex > currentIndex;
}
