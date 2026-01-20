#include "Operation.h"
#include "../utilities/ErrorHandling.h"
#include <QDebug>

Operation::Operation(PriorityLevel priority, OperationManager* parent) :
    FangObject((QObject*)parent),
    operationManager(parent),
    priority(priority),
    error(false),
    terminate(false)
{
    
}

void Operation::reportError(const QString& errorString)
{
    qDebug() << "Error: [ " << metaObject()->className() << " ] " << errorString;
    error = true;
    emit finished(this);
}

void Operation::requireObject(QObject *object)
{
    FANG_REQUIRE_VOID(object != nullptr);
    connect(object, &QObject::destroyed, this, &Operation::onRequiredQObjectDestroyed);
}

void Operation::onRequiredQObjectDestroyed(QObject *object)
{
    reportError("Required object destroyed: " + object->objectName());
    terminate = true;
}
