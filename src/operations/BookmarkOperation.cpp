#include "BookmarkOperation.h"
#include <QDebug>

#include "../utilities/UnreadCountReader.h"
#include "../FangApp.h"

BookmarkOperation::BookmarkOperation(OperationManager *parent, FeedItem* feed) :
    DBOperation(IMMEDIATE, parent),
    feed(feed)
{
}

BookmarkOperation::~BookmarkOperation()
{
}

void BookmarkOperation::updateUnreadCounts()
{
    for (int i = 0; i < FangApp::instance()->feedCount(); i++) {
        UnreadCountReader::update(db(), FangApp::instance()->getFeed(i));
    }
}

void BookmarkOperation::unbookmarkAll()
{
    db().transaction();
    
    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable SET bookmark_id = -1");
    
    if (!update.exec()) {
        reportSQLError(update, "Unable to unset all bookmarks (aka all unread)");
        db().rollback();
        
        emit finished(this);
        return;
    }
    
    updateUnreadCounts();
    db().commit();
    emit finished(this);
}

void BookmarkOperation::bookmarkAll()
{
    db().transaction();

    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable AS f SET bookmark_id = "
                   "(SELECT id FROM NewsItemTable n WHERE n.feed_id = f.id ORDER BY timestamp DESC, id DESC LIMIT 1)");

    if (!update.exec()) {
        reportSQLError(update, "Unable to set all bookmarks (aka all read)");
        db().rollback();

        emit finished(this);
        return;
    }

    updateUnreadCounts();
    db().commit();
    emit finished(this);
}

void BookmarkOperation::unbookmarkAllInFolder(FolderFeedItem *folder)
{
    db().transaction();

    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable SET bookmark_id = -1 WHERE parent_folder = :feed_id");
    update.bindValue(":feed_id", folder->getDbId());

    if (!update.exec()) {
        reportSQLError(update, "Unable to unset bookmarks in folder (aka set folder unread)");
        db().rollback();

        emit finished(this);
        return;
    }

    updateUnreadCounts();
    db().commit();
    emit finished(this);
}

void BookmarkOperation::bookmarkAllInFolder(FolderFeedItem *folder)
{
    db().transaction();

    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable AS f SET bookmark_id = "
                   "(SELECT id FROM NewsItemTable n WHERE n.feed_id = f.id ORDER BY timestamp DESC, id DESC LIMIT 1) "
                   "WHERE f.parent_folder = :feed_id");
    update.bindValue(":feed_id", folder->getDbId());

    if (!update.exec()) {
        reportSQLError(update, "Unable to set all bookmarks in folder (aka set folder read)");
        db().rollback();

        emit finished(this);
        return;
    }

    updateUnreadCounts();
    db().commit();
    emit finished(this);
}

void BookmarkOperation::unbookmarkAllInFeed(FeedItem *feed)
{
    db().transaction();

    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable SET bookmark_id = -1 WHERE id = :feed_id");
    update.bindValue(":feed_id", feed->getDbId());

    if (!update.exec()) {
        reportSQLError(update, "Unable to unset bookmark for feed (aka set feed unread)");
        db().rollback();

        emit finished(this);
        return;
    }

    updateUnreadCounts();
    db().commit();
    emit finished(this);
}

void BookmarkOperation::bookmarkAllInFeed(FeedItem *feed)
{
    db().transaction();

    QSqlQuery update(db());
    update.prepare("UPDATE FeedItemTable SET bookmark_id = "
                   "(SELECT id FROM NewsItemTable WHERE feed_id = :feed_id ORDER BY timestamp DESC, id DESC LIMIT 1) "
                   "WHERE id = :feed_id");
    update.bindValue(":feed_id", feed->getDbId());

    if (!update.exec()) {
        reportSQLError(update, "Unable to set bookmark for feed (aka set feed read)");
        db().rollback();

        emit finished(this);
        return;
    }

    updateUnreadCounts();
    db().commit();
    emit finished(this);
}
