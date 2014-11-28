#include "PinnedFeedItem.h"

PinnedFeedItem::PinnedFeedItem(QObject *parent) :
    FeedItem(FEED_ID_PINNED, -1, "Pinned", "", QDateTime(), 0, QUrl(), QUrl(), QUrl(), QDateTime(), parent)
{
}

bool PinnedFeedItem::canBookmark(qint64 bookmarkID, bool allowBackward)
{
    Q_UNUSED(bookmarkID);
    Q_UNUSED(allowBackward);

    return false;
}
