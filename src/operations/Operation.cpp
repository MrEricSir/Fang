#include "Operation.h"
#include <QDebug>

Operation::Operation(PriorityLevel priority, QObject *parent) :
    QObject(parent),
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
