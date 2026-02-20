#ifndef SETBOOKMARKOPERATION_H
#define SETBOOKMARKOPERATION_H

#include "BookmarkOperation.h"
#include "../models/FeedItem.h"
#include "../models/AllNewsFeedItem.h"
#include "../models/FolderFeedItem.h"

/*!
    \brief Sets a bookmark to whatever news id you'd like.
 */
class SetBookmarkOperation : public BookmarkOperation
{
    Q_OBJECT
public:
    explicit SetBookmarkOperation(OperationManager *parent, FeedItem* feed,
                                  NewsItem* bookmark);
    virtual ~SetBookmarkOperation() = default;
signals:
    
public slots:
    virtual void execute();

    // Returns the bookmarked item.
    inline NewsItem* getBookmark() const { return bookmark; }
    
protected:
    
    void bookmarkSingleFeed(FeedItem *feed);

    void bookmarkFolderFeed(FolderFeedItem* folder);
    
    void bookmarkAllNewsFeed(AllNewsFeedItem* allNews);
    
private:
    NewsItem* bookmark;
};

#endif // SETBOOKMARKOPERATION_H
