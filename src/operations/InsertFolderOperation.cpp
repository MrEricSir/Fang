#include "InsertFolderOperation.h"
#include "../utilities/Utilities.h"
#include "../models/FolderFeedItem.h"

InsertFolderOperation::InsertFolderOperation(OperationManager *parent, int newIndex, QString name, ListModel *feedList)
    : DBOperation(IMMEDIATE, parent),
      newIndex(newIndex),
      name(name),
      feedList(feedList),
      newItem(NULL)
{
    Q_ASSERT(feedList != NULL);
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
    for (int i = newIndex; i < newIndex + 2; i++) {
        FeedItem* next = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(next);
        nextIDs.append(next->getDbId());
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
    feedList->insertRow(newIndex, folder);
    for (int i = newIndex + 1; i < newIndex + 3; i++) {
        FeedItem* next = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(next);
        next->setParentFolder(insertID);
    }

    // TODO: Model/DB: Redo all ordinals in the list

    emit finished(this);
}
