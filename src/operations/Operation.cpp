#include "Operation.h"
#include <QDebug>

Operation::Operation(PriorityLevel priority, QObject *parent) :
    QObject(parent),
    priority(priority)
{
}

Operation::~Operation()
{
    //qDebug() << "Operation deleted.";
}
