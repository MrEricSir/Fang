#include "Operation.h"
#include <QDebug>

Operation::Operation(QObject *parent) :
    QObject(parent)
{
}

Operation::~Operation()
{
    //qDebug() << "Operation deleted.";
}
