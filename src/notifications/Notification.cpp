#include "Notification.h"

#include <QGuiApplication>

Notification::Notification(FangSettings *fangSettings,
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
}

void Notification::init()
{
    // Handle the global unread count.
    lastUnreadCount = allNews->getUnreadCount();
    onUnreadCountChanged(lastUnreadCount);
    connect(allNews, &AllNewsFeedItem::dataChanged, this, &Notification::allNewsDataChanged);
}

void Notification::onUnreadCountChanged(quint32 unread)
{
    qGuiApp->setBadgeNumber(unread);
}

void Notification::allNewsDataChanged()
{
    if (lastUnreadCount != allNews->getUnreadCount()) {
        // Update the unread count!
        lastUnreadCount = allNews->getUnreadCount();
        onUnreadCountChanged(lastUnreadCount);
    }
}
