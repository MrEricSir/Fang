#ifndef SETBOOKMARKOPERATION_H
#define SETBOOKMARKOPERATION_H

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/AllNewsFeedItem.h"
#include "../models/FolderFeedItem.h"

/**
 * @brief Sets a bookmark to whatever news id you'd like.
 */
class SetBookmarkOperation : public DBOperation
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
    
    // If the bookmark is -1 for all news, that's a special case; we must un-bookmark
    // ALL feeds.
    void unbookmarkAll();
    
private:
    FeedItem *feed;
    qint64 bookmarkID;
};

#endif // SETBOOKMARKOPERATION_H
