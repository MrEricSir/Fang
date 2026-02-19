#ifndef DBOPERATION_H
#define DBOPERATION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "SyncOperation.h"

/*!
    \brief A synchronous operation with database access.
    Subclass this for operations that need to run DB queries synchronously.
 */
class DBOperation : public SyncOperation
{
    Q_OBJECT
public:
    explicit DBOperation(OperationManager* parent);
    virtual ~DBOperation() = default;

public slots:
    QSqlDatabase db();

protected:

    /*!
        \brief Call this to report a SQL error. Logs the error and sets the error flag.
        \param query
        \param errorString The text that will be logged along with the error.
     */
    void reportSQLError(const QSqlQuery& query, const QString& errorString);
};

#endif // DBOPERATION_H
