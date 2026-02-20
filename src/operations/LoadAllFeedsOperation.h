#ifndef LOADALLFEEDSOPERATION_H
#define LOADALLFEEDSOPERATION_H

#include "DBOperation.h"

#include <QUrl>
#include <QString>
#include <QDateTime>

#include "../models/FeedItem.h"
#include "../models/ListModel.h"

/*!
    \brief Initializes and loads all existing feeds off the disk.
    Adds "all news" meta-item to the list.
    (Does not perform network update or any fancy shenaniganry like that.)
 */
class LoadAllFeedsOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit LoadAllFeedsOperation(OperationManager *parent, ListModel *feedList);

public slots:
    virtual void execute();

private:
    ListModel *feedList;
};

#endif // LOADALLFEEDSOPERATION_H
