#include "NotificationBase.h"

NotificationBase::NotificationBase(FangSettings *fangSettings,
                                   ListModel *feedList,
                                   AllNewsFeedItem *allNews,
                                   QQuickWindow* window,
                                   FangObject *parent) :
    FangObject(parent),
    fangSettings(fangSettings),
    feedList(feedList),
    allNews(allNews),
    window(window)
{
    // You can't call virtual methods in C++ from within the constructor,
    // so we let implementors do this using the init method below.
}

void NotificationBase::init()
{
    // Handle the global unread count.
    lastUnreadCount = allNews->getUnreadCount();
    onUnreadCountChanged(lastUnreadCount);
    connect(allNews, &AllNewsFeedItem::dataChanged, this, &NotificationBase::allNewsDataChanged);
}

void NotificationBase::allNewsDataChanged()
{
    if (lastUnreadCount != allNews->getUnreadCount()) {
        // Update the unread count!
        lastUnreadCount = allNews->getUnreadCount();
        onUnreadCountChanged(lastUnreadCount);
    }
}
