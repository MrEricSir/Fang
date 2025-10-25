#ifndef NOTIFICATIONMAC_H
#define NOTIFICATIONMAC_H

#include "NotificationBase.h"

class NotificationMac : public NotificationBase
{
    Q_OBJECT
public:
    explicit NotificationMac(FangSettings *fangSettings,
                             ListModel *feedList,
                             AllNewsFeedItem *allNews,
                             QQuickWindow* window,
                             FangObject *parent = nullptr);

protected:
    virtual void onUnreadCountChanged(quint32 unread);

};

#endif // NOTIFICATIONMAC_H
