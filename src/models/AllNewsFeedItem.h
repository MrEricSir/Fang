#ifndef ALLNEWSFEEDITEM_H
#define ALLNEWSFEEDITEM_H

#include "FeedItem.h"

#include <QObject>
#include <QList>

#include "ListModel.h"
#include "NewsItem.h"

class AllNewsFeedItem : public FeedItem
{
    Q_OBJECT
public:
    explicit AllNewsFeedItem(ListModel *feedList);
    
    /**
     * @brief When the feed changes away from all news, this kills the view.
     * 
     * TODO: This general solution can work for any folder/container type.
     */
    virtual void clearNews();
    
    /**
     * @brief canBookmark
     * @param item
     * @param allowBackward
     * @return 
     */
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward);
    
    /**
     * @brief List of all news IDs that have been in the view.
     * 
     * TODO: This general solution can work for any folder/container type.
     * 
     * @return 
     */
    QList<qint64>* newsIDs() { return &_newsIDs; }
    
private:
    // Though the news items are shown temporarily, the view is inifinite.  This
    // ever-growing list of db IDs ensures that by containing a temporary view.
    QList<qint64> _newsIDs;
};

#endif // ALLNEWSFEEDITEM_H
