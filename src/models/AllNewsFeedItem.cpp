#include "AllNewsFeedItem.h"
#include <QList>
#include <QDateTime>

AllNewsFeedItem::AllNewsFeedItem(ListModel *feedList) :
    LisvelFeedItem(FEED_ID_ALLNEWS, -2, "All News", feedList)
{
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
    
    int proposed = bookmarkID == -1 ? 0 : newsIDs()->indexOf(bookmarkID);
    int current = newsIDs()->indexOf(getBookmarkID());
    Q_ASSERT(proposed >= 0); // It HAS TO be in the news ids list at this point, or you're screwed.
    
    return proposed > current;
}
