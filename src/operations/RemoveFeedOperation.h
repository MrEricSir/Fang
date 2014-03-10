#ifndef REMOVEFEEDOPERATION_H
#define REMOVEFEEDOPERATION_H

#include <QObject>

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/ListModel.h"

/**
 * @brief Removes an existing feed from the model and DB.
 */
class RemoveFeedOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit RemoveFeedOperation(OperationManager *parent, FeedItem* feed, ListModel *feedList);
    
public slots:
    virtual void execute();
    
private:
    FeedItem* feed;
    ListModel *feedList;
};

#endif // REMOVEFEEDOPERATION_H
