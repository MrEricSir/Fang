#include "UpdateOrdinalsOperation.h"
#include "../models/FeedItem.h"
#include "../models/ListModel.h"

#include <QList>
#include <QSet>
#include <QDebug>

UpdateOrdinalsOperation::UpdateOrdinalsOperation(OperationManager *parent, ListModel *feedList) :
    DBOperation(IMMEDIATE, parent),
    feedList(feedList)
{
}

void UpdateOrdinalsOperation::execute()
{
    QSet<int> folderIDs;
    QList<FeedItem*> removedFromFolder;
    db().transaction();
    
    // Update ordinals and gather folder IDs.
    for (int i = 0; i < feedList->count(); i++) {
        QSqlQuery update(db());
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        if (feedItem->isSpecialFeed()) {
            // Item isn't in the db.
            continue;
        }

        if (feedItem->isFolder()) {
            folderIDs << feedItem->getDbID();
        }
        
        update.prepare("UPDATE FeedItemTable SET ordinal = :ordinal WHERE id = "
                       ":feed_id");
        update.bindValue(":ordinal", i);
        update.bindValue(":feed_id", feedItem->getDbID());
        
        if (!update.exec()) {
            reportSQLError(update, "Unable to update ordinal for feed id " + QString::number(feedItem->getDbID()));
            db().rollback();
            
            return;
        }
    }

    // Update ordinals and gather folder IDs.
    for (int i = 0; i < feedList->count(); i++) {
        QSqlQuery update(db());
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        if (feedItem->isSpecialFeed()) {
            // Item isn't in the db.
            continue;
        }

        if (!folderIDs.contains(feedItem->getParentFolderID())) {
            // Build a list of feeds we've had to reparent so we can update the model later.
            removedFromFolder << feedItem;
        }

        update.prepare("UPDATE FeedItemTable SET parent_folder = :parent_folder WHERE id = "
                       ":feed_id");
        update.bindValue(":parent_folder", feedItem->getParentFolderID());
        update.bindValue(":feed_id", feedItem->getDbID());

        if (!update.exec()) {
            reportSQLError(update, "Unable to update parent for feed id " + QString::number(feedItem->getDbID()));
            db().rollback();

            return;
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
    foreach (FeedItem* item, removedFromFolder) {
        item->setParentFolder(-1);
    }

    emit finished(this);
}
