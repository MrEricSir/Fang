#ifndef SETFOLDEROPENOPERATION_H
#define SETFOLDEROPENOPERATION_H

#include "DBOperationSynchronous.h"

#include <QObject>

#include "../models/FeedItem.h"

/*!
    \brief Saves the folder open/closed state to the database.
 */
class SetFolderOpenOperation : public DBOperationSynchronous
{
    Q_OBJECT
public:
    explicit SetFolderOpenOperation(OperationManager *parent, FeedItem* feed);

signals:

public slots:
    virtual void executeSynchronous();

private:
    FeedItem* feed;
};

#endif // SETFOLDEROPENOPERATION_H
