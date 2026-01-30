#ifndef FANGOBJECT_H
#define FANGOBJECT_H

#include <QObject>
#include <QSet>
#include <QMutex>

#ifdef QT_DEBUG
// If this is defined, we'll check for remaining objects
// when printRemainingObjects() is called.
#define FANG_OBJECT_LEAK_CHECK
#endif

/*!
    \brief Base object class for detecting leaks.
 */
class FangObject : public QObject
{
    Q_OBJECT
public:
    explicit FangObject(QObject *parent = nullptr);
    virtual ~FangObject();
    
    static void printRemainingObjects();

    #ifdef FANG_OBJECT_LEAK_CHECK
    // For testing purposes - returns count of tracked objects
    static int getRemainingObjectCount();
    #endif

signals:
    
public slots:
private:
    QMutex mutex;
    
    static QSet<FangObject*> allObjects;
    
};

#endif // FANGOBJECT_H
