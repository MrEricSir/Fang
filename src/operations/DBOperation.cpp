#include "DBOperation.h"
#include "../db/DB.h"

DBOperation::DBOperation(OperationManager *parent) :
    SyncOperation(parent)
{
}

QSqlDatabase DBOperation::db()
{
    return DB::instance()->db();
}

void DBOperation::reportSQLError(const QSqlQuery &query, const QString &errorString)
{
    reportError(errorString + " SQLite says: " + query.lastError().text());
}
