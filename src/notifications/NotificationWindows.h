#ifndef NOTIFICATIONWINDOWS_H
#define NOTIFICATIONWINDOWS_H

#include "NotificationBase.h"

#if defined(Q_OS_WIN)

class NotificationWindows : public NotificationBase
{
    Q_OBJECT
public:
    explicit NotificationWindows(FangSettings *fangSettings,
                                 ListModel *feedList,
                                 AllNewsFeedItem *allNews,
                                 QQuickWindow* window,
                                 FangObject *parent = 0);
    
protected:
    virtual void onUnreadCountChanged(quint32 unread);
    
};

#endif // defined(Q_OS_WIN)

#endif // NOTIFICATIONWINDOWS_H
