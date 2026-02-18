#include "RemoveFeedOperation.h"

#include <QThread>

#include "../utilities/UnreadCountReader.h"
#include "../utilities/FangLogging.h"
#include "../models/FolderFeedItem.h"
#include "../FangApp.h"

RemoveFeedOperation::RemoveFeedOperation(OperationManager *parent, FeedItem* feed, ListModel *feedList) :
    DBOperationSynchronous(parent),
    feed(feed),
    feedList(feedList)
{
    requireObject(feed);
    requireObject(feedList);
}

void RemoveFeedOperation::executeSynchronous()
{
    if (!feed) {
        qCCritical(logOperation) << "RemoveFeedOperation::executeSynchronous: feed is null";
        return;
    }

    if (feed->isSpecialFeed()) {
        qCDebug(logOperation) << "Cannot remove special feed";
    }

    bool isFolder = feed->isFolder();
    qint64 dbID = feed->getDbID();
    qint64 parentFolderID = feed->getParentFolderID();

    // Delete the feed.
    db().transaction();
    QSqlQuery removeFeed(db());
    removeFeed.prepare("DELETE FROM FeedItemTable WHERE id = :feed_id");
    removeFeed.bindValue(":feed_id", dbID);
    if (!removeFeed.exec()) {
        reportSQLError(removeFeed, "Unable to remove feed.");
        db().rollback();

        return;
    }

    if (isFolder) {
        // Unset folder for feeds previously in the folder.
        QSqlQuery unlinkFolder(db());
        unlinkFolder.prepare("UPDATE FeedItemTable SET parent_folder = 0 WHERE parent_folder = :folder_id");
        unlinkFolder.bindValue(":folder_id", dbID);
        if (!unlinkFolder.exec()) {
            reportSQLError(removeFeed, "Unable to unlink feed.");
            db().rollback();

            return;
        }
    }

    // Good to go!
    db().commit();

        
    // Remove from the model.
    feed->clearDbId();
    feedList->removeItem(feed);
    if (isFolder) {
        // Set model's parent feed to -1
        ListModel * feedList = FangApp::instance()->getFeedList();
        for (int i = 0; i < feedList->rowCount(); i++) {
            FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
            if (!feed) {
                qCCritical(logOperation) << "RemoveFeedOperation: Feed item at index" << i << "is null";
                continue;
            }
            if (feed->getParentFolderID() == dbID) {
                feed->setParentFolder(-1);
            }
        }
    }
    
    // Update the unread count of our special feeds.
    UnreadCountReader::update(db(), FangApp::instance()->feedForId(FEED_ID_ALLNEWS));
    UnreadCountReader::update(db(), FangApp::instance()->feedForId(FEED_ID_PINNED));

    // If feed was in a folder, update the folder's unread count.
    if (parentFolderID > 0) {
        FolderFeedItem* parentFolder = qobject_cast<FolderFeedItem*>(FangApp::instance()->feedForId(parentFolderID));
        if (parentFolder) {
            UnreadCountReader::update(db(), parentFolder);
        }
    }
}
