#include "Operation.h"
#include <QDebug>

Operation::Operation(PriorityLevel priority, OperationManager* parent) :
    FangObject((QObject*)parent),
    operationManager(parent),
    priority(priority),
    error(false),
    terminate(false)
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

void Operation::requireObject(QObject *object)
{
    Q_ASSERT(object != NULL);
    connect(object, SIGNAL(destroyed(QObject*)), this, SLOT(onRequiredQObjectDestroyed(QObject*)));
}

void Operation::onRequiredQObjectDestroyed(QObject *object)
{
    reportError("Required object destroyed: " + object->objectName());
    terminate = true;
}
