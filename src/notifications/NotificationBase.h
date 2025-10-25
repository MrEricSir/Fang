#ifndef NOTIFICATIONBASE_H
#define NOTIFICATIONBASE_H

#include <QQuickWindow>

#include "../FangObject.h"
#include "../models/FangSettings.h"
#include "../models/ListModel.h"
#include "../models/AllNewsFeedItem.h"

/**
 * @brief Base class for notification handlers.
 * 
 * This class defines a few virtual protected methods which
 * update information that might be of interest to the platform.
 */
class NotificationBase : public FangObject
{
    Q_OBJECT
public:
    explicit NotificationBase(FangSettings *fangSettings,
                              ListModel *feedList,
                              AllNewsFeedItem *allNews,
                              QQuickWindow* window,
                              FangObject *parent = nullptr);
    
protected:
    
    /**
     * @brief Implementors must call this from their constructor.
     * 
     * WARNING
     * WARNING
     * WARNING ^ Read the brief!!
     */
    void init();
    
    /**
     * @brief This method is called whenever the total unread count changes.
     * 
     * Use this for notifications, badges, title bar updates, etc.  You should
     * alawys consult with fangSettings to see if that's what the user wants.
     * 
     * @param unread
     */
    virtual void onUnreadCountChanged(quint32 unread) =0;
    
private slots:
    
    void allNewsDataChanged();
    
protected:
    FangSettings *fangSettings;
    ListModel *feedList;
    AllNewsFeedItem *allNews;
    QQuickWindow* window;
    
    quint32 lastUnreadCount;
};

#endif // NOTIFICATIONBASE_H
