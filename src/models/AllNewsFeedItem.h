#ifndef ALLNEWSFEEDITEM_H
#define ALLNEWSFEEDITEM_H

#include "LisvelFeedItem.h"

#include <QObject>
#include <QList>

#include "ListModel.h"
#include "NewsItem.h"

class AllNewsFeedItem : public LisvelFeedItem
{
    Q_OBJECT
public:
    explicit AllNewsFeedItem(ListModel *feedList);
    
    /**
     * @brief canBookmark
     * @param item
     * @param allowBackward
     * @return 
     */
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward);
};

#endif // ALLNEWSFEEDITEM_H
