#include "FangObject.h"

#include <QMutexLocker>
#include <QDebug>
#include <QMap>

QSet<FangObject*> FangObject::allObjects;

FangObject::FangObject(QObject *parent) :
    QObject(parent)
{
#ifdef FANG_OBJECT_LEAK_CHECK
    QMutexLocker locker(&mutex);
    allObjects.insert(this);
#endif
}

FangObject::~FangObject()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    QMutexLocker locker(&mutex);
    allObjects.remove(this);
#endif
}

void FangObject::printRemainingObjects()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    qInfo();
    qInfo() << "========== FangObject leak check ==========";
    qInfo() << "Remaining objects: " << allObjects.size();
    qInfo();

    // Key:   Class name
    // Value: Number of instances
    QMap<QString, int> instanceCount;

    // Tally up the totals.
    for (FangObject* object : allObjects) {
        instanceCount[object->metaObject()->className()]++;
    }

    // Print 'em out!
    for (QString className : instanceCount.keys()) {
        qDebug() << QString("%1 : %2").
                    arg(instanceCount[className], 4).arg(className);
    }

    qInfo() << "===========================================";
    qInfo();
#endif
}

#ifdef FANG_OBJECT_LEAK_CHECK
int FangObject::getRemainingObjectCount()
{
    return allObjects.size();
}
#endif
