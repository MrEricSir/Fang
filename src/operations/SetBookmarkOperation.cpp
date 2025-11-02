#include "SetBookmarkOperation.h"
#include <QDebug>

#include "../models/AllNewsFeedItem.h"
#include "../FangApp.h"

SetBookmarkOperation::SetBookmarkOperation(OperationManager *parent, FeedItem* feed, qint64 bookmarkID) :
    BookmarkOperation(parent, feed),
    bookmarkID(bookmarkID)
{
}

SetBookmarkOperation::~SetBookmarkOperation()
{
}


void SetBookmarkOperation::execute()
{
    AllNewsFeedItem* allNews = qobject_cast<AllNewsFeedItem*>(feed);
    if (allNews) {
        if (bookmarkID == -1) {
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
    update.bindValue(":bookmark_id", bookmarkID);
    update.bindValue(":feed_id", feed->getDbId());

    if (!update.exec()) {
        reportSQLError(update, "Unable to set bookmark to " + QString::number(bookmarkID) +
                                   " for feed id: " + QString::number(feed->getDbId()));
        db().rollback();

        emit finished(this);
        return;
    }

    updateUnreadCounts();

    db().commit();

    emit finished(this);
}

void SetBookmarkOperation::bookmarkFolderFeed(FolderFeedItem* feedFolder)
{
    Q_UNUSED(feedFolder);

    //
    // Step 1: Get the ID of the feed associated with the bookmark we're setting.
    //
    QSqlQuery query(db());
    query.prepare("SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id LIMIT 1");
    query.bindValue(":bookmark_id", bookmarkID);
    if (!query.exec() || !query.next()) {
        reportSQLError(query, "Unable to locate news item for bookmark " + QString::number(bookmarkID));

        emit finished(this);
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
    int proposed = allNews->newsIDs()->indexOf(bookmarkID);
    int current = allNews->newsIDs()->indexOf(allNews->getBookmarkID());
    
    Q_ASSERT(proposed != current); // You have to double-check for this before starting this operation.
    
    db().transaction();
    
    // Start i at the current position.
    int i = current;
    while (i != proposed)
    {
        // Forward: increment i.
        if (current < proposed) {
            i++;
        }
        
        // Get the news ID.
        qint64 newBookmark = allNews->newsIDs()->at(i);
        
        // Generate our query.
        //
        // * Forward:  Set the bookmark ID to the provided value.
        // * Backward: Set the bookmark ID to the PREVIOUS news item.
        QString query = (current < proposed) ?
                            "UPDATE FeedItemTable SET bookmark_id = :bookmark_id WHERE id = "
                            "(SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2)"
                          :
                            "UPDATE FeedItemTable SET bookmark_id = "
                            "(SELECT IFNULL((SELECT id FROM NewsItemTable WHERE id < :bookmark_id ORDER BY ID DESC LIMIT 1), -1)) "
                            "WHERE id = (SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2)";
        
        QSqlQuery update(db());
        update.prepare(query);
        update.bindValue(":bookmark_id", newBookmark);
        update.bindValue(":bookmark_id2", newBookmark);
        
        if (!update.exec()) {
            reportSQLError(update, "Unable to set bookmark to " + QString::number(newBookmark));
            db().rollback();
            
            emit finished(this);
            return;
        }
        
        // Backward: decrement i.
        if (current > proposed) {
            i--;
        }
    }
    
    updateUnreadCounts();
    
    db().commit();
    
    emit finished(this);
}
