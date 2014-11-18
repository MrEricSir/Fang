#include "AllNewsFeedItem.h"
#include <QList>
#include <QDateTime>

AllNewsFeedItem::AllNewsFeedItem(ListModel *feedList) :
    FeedItem(-1, -1, "All News", "", QDateTime(), 0, QUrl(), QUrl(), QUrl(), QDateTime(), feedList),
    _newsIDs()
{
}

void AllNewsFeedItem::clearNews()
{
    // Remove the view.
    _newsIDs.clear();
    
    // Bubble bobble up our chain.
    FeedItem::clearNews();
}

bool AllNewsFeedItem::canBookmark(qint64 bookmarkID, bool allowBackward)
{
    // You FAIL!
    if (bookmarkID < -1)
        return false;
    
    // No change.
    if (getBookmarkID() == bookmarkID)
        return false;
    
    // ASSUMPTION: Since we always start from the bookmark, if the bookmark ID isn't -1 it
    // must therefore be in the _newsIDs list, my dear Watson.
    if (getBookmarkID() < 0)
        return true;
    
    // YOLO
    if (allowBackward)
        return true;
    
    int proposed = bookmarkID == -1 ? 0 : _newsIDs.indexOf(bookmarkID);
    int current = _newsIDs.indexOf(getBookmarkID());
    Q_ASSERT(proposed >= 0); // It HAS TO be in the news ids list at this point, or you're screwed.
    
    return proposed > current;
}
