#ifndef UPDATEORDINALSOPERATION_H
#define UPDATEORDINALSOPERATION_H

#include "DBOperationSynchronous.h"

#include "../models/ListModel.h"

/*!
    \brief Saves the current ordinal for each feed to the database. Also responsible for reparenting
           items when they're removed from a folder.
 */
class UpdateOrdinalsOperation : public DBOperationSynchronous
{
    Q_OBJECT
public:
    explicit UpdateOrdinalsOperation(OperationManager *parent, ListModel *feedList);
    
public slots:
    virtual void executeSynchronous();
    
private:
    ListModel *feedList;
    
};

#endif // UPDATEORDINALSOPERATION_H
