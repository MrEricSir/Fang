#include "PinnedFeedItem.h"

PinnedFeedItem::PinnedFeedItem(ListModel *feedList) :
    LisvelFeedItem(FEED_ID_PINNED, -1, "Pinned", feedList)
{
}

bool PinnedFeedItem::canBookmark(qint64 bookmarkID, bool allowBackward)
{
    Q_UNUSED(bookmarkID);
    Q_UNUSED(allowBackward);

    return false;
}

bool PinnedFeedItem::bookmarksEnabled() const
{
    return false;
}
