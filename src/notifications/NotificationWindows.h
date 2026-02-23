#ifndef NOTIFICATIONWINDOWS_H
#define NOTIFICATIONWINDOWS_H

#include "Notification.h"

class NotificationWindows : public Notification
{
    Q_OBJECT
public:
    explicit NotificationWindows(FangSettings *fangSettings,
                                 ListModel *feedList,
                                 AllNewsFeedItem *allNews,
                                 QQuickWindow* window,
                                 FangObject *parent = nullptr);
    
protected:
    virtual void onUnreadCountChanged(quint32 unread);
    
};

#endif // NOTIFICATIONWINDOWS_H
