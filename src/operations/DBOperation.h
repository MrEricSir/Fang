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
    explicit DBOperation(PriorityLevel priority, QObject *parent = 0);
    virtual ~DBOperation() {}
signals:
    
public slots:
    QSqlDatabase db();
    
};

#endif // DBOPERATION_H
