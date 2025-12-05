#ifndef REMOVEFEEDOPERATION_H
#define REMOVEFEEDOPERATION_H

#include <QObject>

#include "DBOperationSynchronous.h"
#include "../models/FeedItem.h"
#include "../models/ListModel.h"

/**
 * @brief Removes an existing feed from the model and DB.
 */
class RemoveFeedOperation : public DBOperationSynchronous
{
    Q_OBJECT
public:
    explicit RemoveFeedOperation(OperationManager *parent, FeedItem* feed, ListModel *feedList);
    
public slots:
    virtual void executeSynchronous();
    
private:
    FeedItem* feed;
    ListModel *feedList;
};

#endif // REMOVEFEEDOPERATION_H
