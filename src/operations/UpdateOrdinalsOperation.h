#ifndef UPDATEORDINALSOPERATION_H
#define UPDATEORDINALSOPERATION_H

#include "DBOperation.h"

#include "../models/ListModel.h"

/**
 * @brief Saves the current ordinal for each feed to the database. Also responsible for reparenting
 *        items when they're removed from a folder.
 */
class UpdateOrdinalsOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit UpdateOrdinalsOperation(OperationManager *parent, ListModel *feedList);
    
public slots:
    virtual void execute();
    
private:
    ListModel *feedList;
    
};

#endif // UPDATEORDINALSOPERATION_H
