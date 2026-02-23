#include "NotificationWindows.h"

#include <QDebug>

NotificationWindows::NotificationWindows(FangSettings *fangSettings,
                                         ListModel *feedList,
                                         AllNewsFeedItem *allNews,
                                         QQuickWindow* window,
                                         FangObject *parent) :
    Notification(fangSettings, feedList, allNews, window, parent)
{
    // Set everything up.
    init();
}

void NotificationWindows::onUnreadCountChanged(quint32 unread)
{
    Notification::onUnreadCountChanged(unread);

    QString windowTitle = "Fang";
    if (unread > 0) {
        windowTitle = QString("(%1) ").arg(unread) + windowTitle;
    }

    window->setTitle(windowTitle);
}
