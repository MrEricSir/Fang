#include "AsyncOperation.h"
#include "../db/DB.h"
#include "../utilities/ErrorHandling.h"
#include "../utilities/FangLogging.h"

AsyncOperation::AsyncOperation(Priority priority, OperationManager* parent) :
    FangObject((QObject*)parent),
    operationManager(parent),
    priority(priority),
    error(false),
    terminate(false)
{

}

void AsyncOperation::reportError(const QString& errorString)
{
    qCDebug(logOperation) << "Error: [ " << metaObject()->className() << " ] " << errorString;
    error = true;
    emit finished(this);
}

void AsyncOperation::requireObject(QObject *object)
{
    FANG_REQUIRE_VOID(object != nullptr);
    connect(object, &QObject::destroyed, this, &AsyncOperation::onRequiredQObjectDestroyed);
}

void AsyncOperation::onRequiredQObjectDestroyed(QObject *object)
{
    reportError("Required object destroyed: " + object->objectName());
    terminate = true;
}

QSqlDatabase AsyncOperation::db()
{
    return DB::instance()->db();
}

void AsyncOperation::reportSQLError(const QSqlQuery &query, const QString &errorString)
{
    reportError(errorString + " SQLite says: " + query.lastError().text());
}
