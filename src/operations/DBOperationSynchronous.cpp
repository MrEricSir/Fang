#include "DBOperationSynchronous.h"

DBOperationSynchronous::DBOperationSynchronous(OperationManager *parent) :
    DBOperation(SYNCHRONOUS, parent)
{
}

void DBOperationSynchronous::execute()
{
    // Run the operation and emmit the finished signal.
    executeSynchronous();
    emit finished(this);
}

