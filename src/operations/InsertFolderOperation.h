#ifndef INSERTFOLDEROPERATION_H
#define INSERTFOLDEROPERATION_H

#include "DBOperation.h"

#include <QObject>
#include <QUrl>
#include <QString>
#include <QDebug>

#include "../models/ListModel.h"
#include "../models/FolderFeedItem.h"

/*!
    \brief Inserts a folder at the given index and reparents the next two items.
 */
class InsertFolderOperation : public DBOperation
{
public:
    InsertFolderOperation(OperationManager *parent, int newIndex, QString name, ListModel *feedList);
    ~InsertFolderOperation();

public slots:
    virtual void execute();

    FeedItem* getNewFeedItem() { return newItem; }

private:
    int newIndex;
    QString name;
    ListModel *feedList;
    FeedItem* newItem;
};

#endif // INSERTFOLDEROPERATION_H
