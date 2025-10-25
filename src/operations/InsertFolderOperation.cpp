#include "InsertFolderOperation.h"
#include "../utilities/Utilities.h"
#include "../models/FolderFeedItem.h"

InsertFolderOperation::InsertFolderOperation(OperationManager *parent, int newIndex, QString name, ListModel *feedList)
    : DBOperation(IMMEDIATE, parent),
      newIndex(newIndex),
      name(name),
      feedList(feedList),
      newItem(nullptr)
{
    Q_ASSERT(feedList != nullptr);
}

InsertFolderOperation::~InsertFolderOperation()
{

}

void InsertFolderOperation::execute()
{
    qint64 insertID = -1;

    // Make sure we have a realistic newIndex before we get started.
    Q_ASSERT(newIndex < feedList->count());
    Q_ASSERT(newIndex >= 0);

    // Grab next two ids in the list.
    QVector<qint64> nextIDs;
    QVector<FeedItem *> nextItems;
    for (int i = newIndex; i < newIndex + 2; i++) {
        FeedItem* next = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(next);
        nextIDs.append(next->getDbId());
        nextItems.append(next);
    }

    // DB: Insert the new folder into the db and get it's new ID.
    db().transaction();

    {
        QSqlQuery query(db());
        query.prepare("INSERT INTO FeedItemTable (title, ordinal, is_folder, subtitle, "
                      "url, siteURL) VALUES "
                      "(:title, :ordinal, :isFolder, '', '', '')");
        query.bindValue(":title", name);
        query.bindValue(":ordinal", newIndex);
        query.bindValue(":isFolder", true);

        if (!query.exec()) {
            reportSQLError(query, "Could not add new folder");
            db().rollback();

            return;
        }

        // Our new ID.
        insertID = query.lastInsertId().toLongLong();
    }

    Q_ASSERT(insertID > -1);

    {
        QString ids = Utilities::commaSeparatedStringList(nextIDs);
        // qDebug() << "inserting folder with id " << insertID << " the following IDs: " << ids;

        QSqlQuery query(db());
        query.prepare("UPDATE FeedItemTable SET parent_folder = :parentFolder "
                      "WHERE id IN (" + ids + ")");
        query.bindValue(":parentFolder", insertID);
        if (!query.exec()) {
            reportSQLError(query, "Could not set children for new folder");
            db().rollback();

            return;
        }
    }

    db().commit();


    // Update our model.
    FolderFeedItem* folder = new FolderFeedItem(insertID, newIndex, name, feedList);
    for (FeedItem* item: nextItems) {
        item->setParentFolder(insertID);
    }
    feedList->insertRow(newIndex, folder);

    // TODO: Model/DB: Redo all ordinals in the list

    emit finished(this);
}
