#include "Operation.h"
#include <QDebug>

Operation::Operation(PriorityLevel priority, OperationManager* parent) :
    QObject((QObject*)parent),
    operationManager(parent),
    priority(priority),
    error(false)
{
    
}

Operation::~Operation()
{
    //qDebug() << "Operation deleted.";
}

void Operation::reportError(const QString& errorString)
{
    qDebug() << "Error: [ " << metaObject()->className() << " ] " << errorString;
    error = true;
    emit finished(this);
}
