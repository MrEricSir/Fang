#ifndef SETBOOKMARKOPERATION_H
#define SETBOOKMARKOPERATION_H

#include "BookmarkOperation.h"
#include "../models/FeedItem.h"
#include "../models/AllNewsFeedItem.h"
#include "../models/FolderFeedItem.h"

/**
 * @brief Sets a bookmark to whatever news id you'd like.
 */
class SetBookmarkOperation : public BookmarkOperation
{
    Q_OBJECT
public:
    explicit SetBookmarkOperation(OperationManager *parent, FeedItem* feed,
                                  qint64 bookmarkID);
    virtual ~SetBookmarkOperation();
signals:
    
public slots:
    virtual void execute();
    
    inline FeedItem* getFeed() { return feed; }
    
    // Returns the bookmarked item ID.
    inline qint64 getBookmarkID() { return bookmarkID; }
    
protected:
    
    void bookmarkSingleFeed(FeedItem *feed);

    void bookmarkFolderFeed(FolderFeedItem* folder);
    
    void bookmarkAllNewsFeed(AllNewsFeedItem* allNews);
    
private:
    qint64 bookmarkID;
};

#endif // SETBOOKMARKOPERATION_H
