#ifndef SINGLEINSTANCECHECK_H
#define SINGLEINSTANCECHECK_H

#include <QSharedMemory>
#include <QString>
#include <QWindow>
#include <QLocalServer>
#include "../FangObject.h"

class SingleInstanceCheck : public FangObject
{
    Q_OBJECT
public:
    SingleInstanceCheck(QString uniqueID, FangObject* parent = nullptr);
    
    virtual ~SingleInstanceCheck() = default;
    
    /**
     * @return True if another instance is running.
     */
    bool isAlreadyRunning() const { return !isFirst; }

    /**
     * @brief Sends a message to the original instance.
     */
    void notify();

signals:

    /**
     * @brief Fired when a second instance called its notify() method.
     */
    void notified();

private slots:

    /**
     * Used to log when a client connects, the fires the notified() signal.
     */
    void onClientConnected();
    
private:
    
    QSharedMemory sharedMemory;
    QLocalServer server;
    QString uniqueID;
    bool isFirst;
};

#endif // SINGLEINSTANCECHECK_H
