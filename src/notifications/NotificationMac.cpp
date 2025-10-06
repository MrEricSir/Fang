#include "NotificationMac.h"
#include <QDebug>

NotificationMac::NotificationMac(FangSettings *fangSettings,
                                 ListModel *feedList,
                                 AllNewsFeedItem *allNews,
                                 QQuickWindow* window,
                                 FangObject *parent) :
    NotificationBase(fangSettings, feedList, allNews, window, parent)
{
    // Set everything up.
    init();
}

void NotificationMac::onUnreadCountChanged(quint32 unread)
{
    //qDebug() << "NOTIFICATION: unread count = " << unread;

    QString unreadText = "";
    if (unread > 0) {
        unreadText = QString("%1").arg(unread);
    }

    // TODO: Port this to Qt6. [qt6]
    //QtMac::setBadgeLabelText(unreadText);
}
