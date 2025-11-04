#include "RemoveFeedOperation.h"

#include <QDebug>
#include <QThread>

#include "../utilities/UnreadCountReader.h"
#include "../FangApp.h"

RemoveFeedOperation::RemoveFeedOperation(OperationManager *parent, FeedItem* feed, ListModel *feedList) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    feedList(feedList)
{
    Q_ASSERT(feed != nullptr);
    Q_ASSERT(feedList != nullptr);
}

void RemoveFeedOperation::execute()
{
    Q_ASSERT(feed);

    if (feed->isSpecialFeed()) {
        qDebug() << "Cannot remove special feed";
    }

    bool isFolder = feed->isFolder();
    qint64 dbID = feed->getDbId();

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
            Q_ASSERT(feed);
            if (feed->getParentFolderID() == dbID) {
                feed->setParentFolder(-1);
            }
        }
    }
    
    // Update the unread count of our special feeds.
    UnreadCountReader::update(db(), FangApp::instance()->feedForId(FEED_ID_ALLNEWS));
    UnreadCountReader::update(db(), FangApp::instance()->feedForId(FEED_ID_PINNED));
    
    emit finished(this);
}
