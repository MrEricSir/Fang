#include "AllNewsFeedItem.h"
#include <QList>
#include <QDateTime>

AllNewsFeedItem::AllNewsFeedItem(ListModel *feedList) :
    LisvelFeedItem(FEED_ID_ALLNEWS, -2, "All News", feedList)
{
}
