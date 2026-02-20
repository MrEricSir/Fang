#ifndef BOOKMARKOPERATION_H
#define BOOKMARKOPERATION_H

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/FolderFeedItem.h"

/*!
    \brief Subclass that adds some bookmarking capabilities.
 */
class BookmarkOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit BookmarkOperation(OperationManager *parent, FeedItem* feed);
    virtual ~BookmarkOperation() = default;

public slots:
    inline FeedItem* getFeed() { return feed; }
    
protected slots:

    /*!
        \brief Updates the unread count for every feed.
     */
    virtual void updateUnreadCounts();

    /*!
        \brief Removes the bookmark for all feeds, making everything unread.
     */
    virtual void unbookmarkAll();

    /*!
        \brief Marks the most recent item in all feeds as bookmarked, making everything read.
     */
    virtual void bookmarkAll();

    /*!
        \brief Unbookmarks all the news in a folder, marking all items unread.
     */
    virtual void unbookmarkAllInFolder(FolderFeedItem* folder);

    /*!
        \brief Bbookmarks all the news in a folder, making all items read.
     */
    virtual void bookmarkAllInFolder(FolderFeedItem* folder);

    /*!
        \brief Unbookmarks all the news in a regular feed, marking all items unread.
     */
    virtual void unbookmarkAllInFeed(FeedItem* feed);

    /*!
        \brief Bbookmarks all the news in a regular feed, making all items read.
     */
    virtual void bookmarkAllInFeed(FeedItem* feed);

protected:
    FeedItem *feed;
};

#endif // BOOKMARKOPERATION_H
