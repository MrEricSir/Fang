#include "DBOperation.h"
#include "../db/DB.h"

DBOperation::DBOperation(PriorityLevel priority, QObject *parent) :
    Operation(priority, parent)
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
