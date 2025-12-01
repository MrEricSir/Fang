#ifndef DBOPERATION_H
#define DBOPERATION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "Operation.h"

class DBOperation : public Operation
{
    Q_OBJECT
public:
    explicit DBOperation(PriorityLevel priority, OperationManager* parent);
    virtual ~DBOperation() = default;
signals:
    
public slots:
    QSqlDatabase db();
    
protected:
    
    /**
     * @brief Call this to report a SQL error.  Automatically emits finished()
     * @param query
     * @param errorString The text that will be logged along with the error.
     */
    void reportSQLError(const QSqlQuery& query, const QString& errorString);
};

#endif // DBOPERATION_H
