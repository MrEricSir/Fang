#ifndef SETBOOKMARKOPERATION_H
#define SETBOOKMARKOPERATION_H

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

/**
 * @brief Sets a bookmark, but only if it's newer than the current one.
 */
class SetBookmarkOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit SetBookmarkOperation(OperationManager *parent, FeedItem* feed, NewsItem* bookmarkItem);
    virtual ~SetBookmarkOperation();
signals:
    
public slots:
    virtual void execute();
    
    inline FeedItem* getFeed() { return feed; }
    
    // Returns the bookmarked item, or NULL if it's older than the bookmark.
    inline NewsItem* getBookmarkItem() { return bookmarkItem; }
    
private:
    FeedItem *feed;
    NewsItem* bookmarkItem;
};

#endif // SETBOOKMARKOPERATION_H
