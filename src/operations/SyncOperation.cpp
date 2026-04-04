#include "SyncOperation.h"
#include "../utilities/FangLogging.h"

SyncOperation::SyncOperation(OperationManager *parent) :
    QObject((QObject*)parent),
    operationManager(parent)
{

}

void SyncOperation::reportError(const QString &errorString)
{
    qCDebug(logOperation) << "Error: [ " << metaObject()->className() << " ] " << errorString;
    error = true;
    errorMsg = errorString;
}
