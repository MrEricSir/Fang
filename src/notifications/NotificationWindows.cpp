#include "NotificationWindows.h"

#include <QDebug>

NotificationWindows::NotificationWindows(FangSettings *fangSettings,
                                         ListModel *feedList,
                                         AllNewsFeedItem *allNews,
                                         QQuickWindow* window,
                                         FangObject *parent) :
    NotificationBase(fangSettings, feedList, allNews, window, parent)
{
    // Set everything up.
    init();
}

void NotificationWindows::onUnreadCountChanged(quint32 unread)
{
    //qDebug() << "NOTIFICATION: unread count = " << unread;
    QString windowTitle = "Fang";
    if (unread > 0) {
        // Append count.
        windowTitle = QString("(%1) ").arg(unread) + windowTitle;
    }
    
    window->setTitle(windowTitle);
}
