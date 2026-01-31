#include "MarkAllReadOrUnreadOperation.h"

#include "../models/AllNewsFeedItem.h"
#include "../models/FolderFeedItem.h"
#include "../utilities/FangLogging.h"

MarkAllReadOrUnreadOperation::MarkAllReadOrUnreadOperation(OperationManager *parent, FeedItem* feed, bool markAsRead) :
    BookmarkOperation(parent, feed),
    markAsRead(markAsRead)
{

}

void MarkAllReadOrUnreadOperation::executeSynchronous()
{
    if (!feed) {
        qCWarning(logOperation) << "Unable to update bookmark; feed is null";

        return;
    }

    if (!feed->bookmarksEnabled()) {
        qCDebug(logOperation) << "Requested to update bookmark but feed does not support bookmarks.";

        return;
    }

    if (markAsRead) {
        // Set bookmark to end of one or more feeds.
        if (qobject_cast<AllNewsFeedItem*>(feed)) {
            qCDebug(logOperation) << "Bookmark all";
            bookmarkAll();
        } else if (feed->isFolder()) {
            bookmarkAllInFolder(qobject_cast<FolderFeedItem*>(feed));
        } else {
            bookmarkAllInFeed(feed);
        }
    } else {
        // Remove all bookmarks for one or more feeds.
        if (qobject_cast<AllNewsFeedItem*>(feed)) {
            qCDebug(logOperation) << "Unbookmark all";
            unbookmarkAll();
        } else if (feed->isFolder()) {
            unbookmarkAllInFolder(qobject_cast<FolderFeedItem*>(feed));
        } else {
            unbookmarkAllInFeed(feed);
        }
    }
}

