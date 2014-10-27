#include "SetBookmarkOperation.h"
#include <QDebug>

#include "../models/AllNewsFeedItem.h"
#include "../utilities/UnreadCountReader.h"
#include "../FangApp.h"

SetBookmarkOperation::SetBookmarkOperation(OperationManager *parent, FeedItem* feed, qint64 bookmarkID) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    bookmarkID(bookmarkID)
{
}

SetBookmarkOperation::~SetBookmarkOperation()
{
}


void SetBookmarkOperation::execute()
{
    //
    // TODO: 
    //
    AllNewsFeedItem* allNews = qobject_cast<AllNewsFeedItem*>(feed);
    if (allNews) {
        bookmarkAllNewsFeed(allNews);
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
        reportSQLError(update, "Unable to set bookmark to " +  QString::number(bookmarkID) + " for feed id: " + QString::number(feed->getDbId()));
        db().rollback();
        
        return;
    }
    
    //
    // Step 2: Update unread count for both the feed and All News.
    //
    UnreadCountReader::update(db(), FangApp::instance()->getFeedForID(feed->getDbId()));
    UnreadCountReader::update(db(), FangApp::instance()->getFeed(0));
    
    db().commit();
    
    emit finished(this);
}

void SetBookmarkOperation::bookmarkAllNewsFeed(AllNewsFeedItem* allNews)
{
    // TODO
    // If the bookmark is -1 for all news, that's a special case; we must un-bookmark
    // ALL feeds.
    if (bookmarkID == -1)
        Q_ASSERT(false);
    //
    
    
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
                            "(SELECT id FROM NewsItemTable WHERE id < :bookmark_id ORDER BY ID DESC LIMIT 1) "
                            "WHERE id = (SELECT feed_id FROM NewsItemTable WHERE id = :bookmark_id2)";
        
        QSqlQuery update(db());
        update.prepare(query);
        update.bindValue(":bookmark_id", newBookmark);
        update.bindValue(":bookmark_id2", newBookmark);
        
        if (!update.exec()) {
            reportSQLError(update, "Unable to set bookmark to " +  QString::number(newBookmark));
            db().rollback();
            
            return;
        }
        
        // Backward: decrement i.
        if (current > proposed) {
            i--;
        }
    }
    
    // Update all unread counts
    for (int i = 0; i < FangApp::instance()->feedCount(); i++) {
        UnreadCountReader::update(db(), FangApp::instance()->getFeed(i));
    }
    
    db().commit();
    
    emit finished(this);
}
