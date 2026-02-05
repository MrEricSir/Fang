#include "SetBookmarkOperation.h"
#include <QDebug>
#include <QMap>

#include "../models/AllNewsFeedItem.h"
#include "../utilities/ErrorHandling.h"
#include "../FangApp.h"
#include "src/models/NewsList.h"

SetBookmarkOperation::SetBookmarkOperation(OperationManager *parent, FeedItem* feed, NewsItem* bookmark) :
    BookmarkOperation(parent, feed),
    bookmark(bookmark)
{
}

void SetBookmarkOperation::executeSynchronous()
{
    AllNewsFeedItem* allNews = qobject_cast<AllNewsFeedItem*>(feed);
    if (allNews) {
        if (bookmark == nullptr) {
            unbookmarkAll();
        } else {
            bookmarkAllNewsFeed(allNews);
        }
    } else if (feed->isFolder()) {
        bookmarkFolderFeed(qobject_cast<FolderFeedItem*>(feed));
    } else {
        bookmarkSingleFeed(feed);
    }
}

void SetBookmarkOperation::bookmarkSingleFeed(FeedItem* feed)
{
    db().transaction();

    //
    // Step 1: Set the feed's bookmark.
    //
    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = "
                   ":feed_id");
    update.bindValue(":bookmark_id", bookmark->getDbID());
    update.bindValue(":feed_id", feed->getDbID());

    if (!update.exec()) {
        reportSQLError(update, "Unable to set bookmark to " + QString::number(bookmark->getDbID()) +
                                   " for feed id: " + QString::number(feed->getDbID()));
        db().rollback();

        return;
    }

    updateUnreadCounts();
    db().commit();
}

void SetBookmarkOperation::bookmarkFolderFeed(FolderFeedItem* feedFolder)
{
    Q_UNUSED(feedFolder);

    //
    // Step 1: Get the ID of the feed associated with the bookmark we're setting.
    //
    QSqlQuery query(db());
    query.prepare("SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id LIMIT 1");
    query.bindValue(":bookmark_id", bookmark->getDbID());
    if (!query.exec() || !query.next()) {
        reportSQLError(query, "Unable to locate news item for bookmark " + QString::number(bookmark->getDbID()));

        return;
    }

    qint64 feedId = query.value("feed_id").toULongLong();

    //
    // Step 2: Set the feed's bookmark.
    //
    bookmarkSingleFeed(FangApp::instance()->feedForId(feedId));
}

void SetBookmarkOperation::bookmarkAllNewsFeed(AllNewsFeedItem* allNews)
{
    // Use our list indices so we can handle items that have been trimmed from the display window.
    qsizetype proposed = allNews->getNewsList()->fullIndexForItemID(bookmark->getDbID());
    qsizetype current = allNews->getNewsList()->fullIndexForItemID(allNews->getBookmarkID());

    FANG_CHECK(proposed >= 0, "SetBookmarkOperation: Proposed bookmark not found in list");
    FANG_CHECK(proposed != current, "SetBookmarkOperation: Bookmark already at proposed position");

    db().transaction();

    // If current bookmark is not in the list (not in memory), we can't iterate through
    // intermediate items. In this case, just update the bookmark for the proposed item's
    // feed directly.
    if (current < 0) {
        QSqlQuery update(db());
        update.prepare("UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = "
                       "(SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2)");
        update.bindValue(":bookmark_id", bookmark->getDbID());
        update.bindValue(":bookmark_id2", bookmark->getDbID());

        if (!update.exec()) {
            reportSQLError(update, "Unable to set bookmark to " + QString::number(bookmark->getDbID()));
            db().rollback();
            return;
        }

        updateUnreadCounts();
        db().commit();
        return;
    }

    // Iterate through the list from current to proposed, updating bookmarks.
    // Use full list indices so we can handle items outside the display window.
    qsizetype i = current;
    while (i != proposed)
    {
        // Forward: increment i first, then process.
        if (current < proposed) {
            i++;
        }

        // Get the news ID from the full list (works even if item is unloaded).
        qint64 newBookmark = allNews->getNewsList()->positionAt(i).id();

        // Generate our query.
        //
        // * Forward:  Set the bookmark ID to the provided value.
        // * Backward: Set the bookmark ID to the PREVIOUS news item IN THE SAME FEED.
        //             This uses ID comparison which works correctly for unread count
        //             calculation (which also uses ID comparison: id > bookmark_id).
        //             Within a single feed, IDs correlate with insertion order/time.
        QString query = (current < proposed) ?
                            "UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = "
                            "(SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2)"
                          :
                            // Backward: Set the bookmark to the previous item IN THE SAME FEED.
                            // Without the feed_id filter, we'd get the previous item globally,
                            // which could belong to a different feed and corrupt the bookmark state.
                            "UPDATE FeedItemTable SET bookmark_id = "
                            "(SELECT IFNULL((SELECT id FROM NewsItemTable WHERE id < :bookmark_id "
                            "AND feed_id = (SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id) "
                            "ORDER BY id DESC LIMIT 1), -1)) "
                            "WHERE id = (SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2)";

        QSqlQuery update(db());
        update.prepare(query);
        update.bindValue(":bookmark_id", newBookmark);
        update.bindValue(":bookmark_id2", newBookmark);

        if (!update.exec()) {
            reportSQLError(update, "Unable to set bookmark to " + QString::number(newBookmark));
            db().rollback();

            return;
        }

        // Backward: decrement i after processing.
        if (current > proposed) {
            i--;
        }
    }

    updateUnreadCounts();
    db().commit();
}
