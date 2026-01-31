#include "FangObject.h"

#include <QMutexLocker>
#include <QMap>

#include "utilities/FangLogging.h"

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
    qCInfo(logApp);
    qCInfo(logApp) << "========== FangObject leak check ==========";
    qCInfo(logApp) << "Remaining objects: " << allObjects.size();
    qCInfo(logApp);

    // Key:   Class name
    // Value: Number of instances
    QMap<QString, int> instanceCount;

    // Tally up the totals.
    for (FangObject* object : allObjects) {
        instanceCount[object->metaObject()->className()]++;
    }

    // Print 'em out!
    for (QString className : instanceCount.keys()) {
        qCDebug(logApp) << QString("%1 : %2").
                    arg(instanceCount[className], 4).arg(className);
    }

    qCInfo(logApp) << "===========================================";
    qCInfo(logApp);
#endif
}

#ifdef FANG_OBJECT_LEAK_CHECK
int FangObject::getRemainingObjectCount()
{
    return allObjects.size();
}
#endif
