#include "DBOperation.h"
#include "../db/DB.h"

DBOperation::DBOperation(QObject *parent) :
    Operation(parent)
{
}

QSqlDatabase DBOperation::db()
{
    return DB::instance()->db();
}
