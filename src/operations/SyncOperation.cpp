#include "SyncOperation.h"
#include "../utilities/FangLogging.h"

SyncOperation::SyncOperation(OperationManager *parent) :
    FangObject((QObject*)parent),
    operationManager(parent)
{

}

void SyncOperation::reportError(const QString &errorString)
{
    qCDebug(logOperation) << "Error: [ " << metaObject()->className() << " ] " << errorString;
    error = true;
    errorMsg = errorString;
}
