#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QQuickWindow>

#include "../FangObject.h"
#include "../models/FangSettings.h"
#include "../models/ListModel.h"
#include "../models/AllNewsFeedItem.h"

/*!
    \brief Handles app badge notifications.

    Sets the app badge number via QGuiApplication::setBadgeNumber()
    whenever the unread count changes.  Subclasses can override
    onUnreadCountChanged() to add platform-specific behavior
    (e.g. window title updates on Windows).
 */
class Notification : public FangObject
{
    Q_OBJECT
public:
    explicit Notification(FangSettings *fangSettings,
                          ListModel *feedList,
                          AllNewsFeedItem *allNews,
                          QQuickWindow* window,
                          FangObject *parent = nullptr);

    /*!
        \brief Subclasses must call this from their constructor.
               When using Notification directly, call after construction.
     */
    void init();

protected:
    /*!
        \brief This method is called whenever the total unread count changes.

        The default implementation sets the app badge number via
        QGuiApplication::setBadgeNumber().  Subclasses can override to add
        platform-specific behavior (e.g. window title updates).

        \param unread
     */
    virtual void onUnreadCountChanged(quint32 unread);

private slots:

    void allNewsDataChanged();

protected:
    FangSettings *fangSettings;
    ListModel *feedList;
    AllNewsFeedItem *allNews;
    QQuickWindow* window;

    quint32 lastUnreadCount;
};

#endif // NOTIFICATION_H
