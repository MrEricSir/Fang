#include "MarkAllReadOrUnreadOperation.h"

#include "../models/AllNewsFeedItem.h"
#include "../models/FolderFeedItem.h"

MarkAllReadOrUnreadOperation::MarkAllReadOrUnreadOperation(OperationManager *parent, FeedItem* feed, bool markAsRead) :
    BookmarkOperation(parent, feed),
    markAsRead(markAsRead)
{

}

void MarkAllReadOrUnreadOperation::executeSynchronous()
{
    if (!feed) {
        qWarning() << "Unable to update bookmark; feed is null";

        return;
    }

    if (!feed->bookmarksEnabled()) {
        qDebug() << "Requested to update bookmark but feed does not support bookmarks.";

        return;
    }

    if (markAsRead) {
        // Set bookmark to end of one or more feeds.
        if (qobject_cast<AllNewsFeedItem*>(feed)) {
            qDebug() << "Bookmark all";
            bookmarkAll();
        } else if (feed->isFolder()) {
            bookmarkAllInFolder(qobject_cast<FolderFeedItem*>(feed));
        } else {
            bookmarkAllInFeed(feed);
        }
    } else {
        // Remove all bookmarks for one or more feeds.
        if (qobject_cast<AllNewsFeedItem*>(feed)) {
            qDebug() << "Unbookmark all";
            unbookmarkAll();
        } else if (feed->isFolder()) {
            unbookmarkAllInFolder(qobject_cast<FolderFeedItem*>(feed));
        } else {
            unbookmarkAllInFeed(feed);
        }
    }
}

