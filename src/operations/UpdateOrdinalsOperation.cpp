#include "UpdateOrdinalsOperation.h"
#include "../models/FeedItem.h"
#include "../models/FolderFeedItem.h"
#include "../models/ListModel.h"
#include "../utilities/UnreadCountReader.h"

#include <QList>
#include <QSet>
#include <QDebug>

UpdateOrdinalsOperation::UpdateOrdinalsOperation(OperationManager *parent, ListModel *feedList) :
    DBOperation(parent),
    feedList(feedList)
{
}

void UpdateOrdinalsOperation::execute()
{
    QSet<qint64> folderIDs;
    QList<FeedItem*> removedFromFolder;
    db().transaction();

    // Update ordinals and gather folder IDs.
    for (int i = 0; i < feedList->count(); i++) {
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        if (feedItem->isSpecialFeed()) {
            continue;
        }

        // Track folder IDs for later cleanup.
        FolderFeedItem* folder = qobject_cast<FolderFeedItem*>(feedItem);
        if (folder) {
            folderIDs.insert(folder->getDbID());
        }

        QSqlQuery update(db());
        update.prepare("UPDATE FeedItemTable SET ordinal = :ordinal WHERE id = :feed_id");
        update.bindValue(":ordinal", i);
        update.bindValue(":feed_id", feedItem->getDbID());

        if (!update.exec()) {
            reportSQLError(update, "Unable to update ordinal for feed id " + QString::number(feedItem->getDbID()));
            db().rollback();
            return;
        }
    }

    // Update parent folder associations.
    for (int i = 0; i < feedList->count(); i++) {
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        if (feedItem->isSpecialFeed()) {
            continue;
        }

        if (!folderIDs.contains(feedItem->getParentFolderID())) {
            // Feed's parent folder no longer exists; track for model update later.
            removedFromFolder << feedItem;
        }

        QSqlQuery update(db());
        update.prepare("UPDATE FeedItemTable SET parent_folder = :parent_folder WHERE id = :feed_id");
        update.bindValue(":parent_folder", feedItem->getParentFolderID());
        update.bindValue(":feed_id", feedItem->getDbID());

        if (!update.exec()) {
            reportSQLError(update, "Unable to update parent for feed id " + QString::number(feedItem->getDbID()));
            db().rollback();
            return;
        }
    }

    // Check for empty folders and remove them from model, DB, and/or both.
    QSet<qint64> foldersWithChildren;
    for (int i = 0; i < feedList->count(); i++) {
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        if (feedItem->isSpecialFeed() || feedItem->isFolder()) {
            continue;
        }

        qint64 parentId = feedItem->getParentFolderID();
        if (parentId > 0) {
            foldersWithChildren.insert(parentId);
        }
    }

    // Remove empty folders from the model (work backwards to avoid altering the index).
    for (int i = feedList->count() - 1; i >= 0; i--) {
        FolderFeedItem* folder = qobject_cast<FolderFeedItem*>(feedList->row(i));
        if (folder && !foldersWithChildren.contains(folder->getDbID())) {
            feedList->removeItem(folder);
            folderIDs.remove(folder->getDbID());
        }
    }

    // Delete orphaned folders from the database.
    QSqlQuery selectFolders(db());
    selectFolders.prepare("SELECT id FROM FeedItemTable WHERE is_folder = 1");
    if (selectFolders.exec()) {
        while (selectFolders.next()) {
            qint64 dbFolderId = selectFolders.value(0).toLongLong();
            if (!folderIDs.contains(dbFolderId)) {
                QSqlQuery deleteFolder(db());
                deleteFolder.prepare("DELETE FROM FeedItemTable WHERE id = :folder_id");
                deleteFolder.bindValue(":folder_id", dbFolderId);
                if (!deleteFolder.exec()) {
                    reportSQLError(deleteFolder, "Unable to delete empty folder " + QString::number(dbFolderId));
                }
            }
        }
    }

    // Complete the DB transaction.
    db().commit();

    // Now we need to refresh our model. First up: ordinals.
    for (int i = 0; i < feedList->count(); i++) {
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        if (feedItem->isSpecialFeed()) {
            continue;
        }

        feedItem->setOrdinal(i);
    }

    // Second: parent folders (or lack thereof.)
    for (FeedItem* item : removedFromFolder) {
        item->setParentFolder(-1);
    }

    // Recalculate unread counts for all folders; this handles the case where a feed
    // item is moved from one folder to another and both folders need to have their
    // feed counts updated.
    for (int i = 0; i < feedList->count(); i++) {
        FolderFeedItem* folder = qobject_cast<FolderFeedItem*>(feedList->row(i));
        if (folder) {
            UnreadCountReader::update(db(), folder);
        }
    }
}
