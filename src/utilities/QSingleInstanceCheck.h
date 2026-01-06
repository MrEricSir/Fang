#ifndef QSINGLEINSTANCECHECK_H
#define QSINGLEINSTANCECHECK_H

#include <QSharedMemory>
#include <QString>
#include <QWindow>
#include <QLocalServer>
#include <QLocalSocket>

/**
 * @brief QSingleInstanceCheck can be used to test if your app is already running, or if this
 * instance is the first (or only) one running.
 *
 * Under the hood, it uses shared memory to check if it's the first instance or not, and a local
 * socket (domain socket or named pipe, depending on the platform) to notify the original instance
 * that another one has been started.
 */
class QSingleInstanceCheck : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief QSingleInstanceCheck
     * @param uniqueID Hard code this in your application as this string will identify your
     * instance to others
     * @param parent (Optional) Owner of the object.
     */
    inline QSingleInstanceCheck(const QString uniqueID, QObject* parent = nullptr) :
        QObject(parent), uniqueID(uniqueID), isFirst(false)
    {
        QObject::connect(&server, &QLocalServer::newConnection,
                         this, &QSingleInstanceCheck::notified);

        sharedMemory.setKey(uniqueID);
        if (sharedMemory.create(1)) {
            // Delete any existing server (for *nix systems) and start our named pipe server.
            server.removeServer(uniqueID);
            if (!server.listen(uniqueID)) {
                emit error("Unable to listen to server: " + server.errorString());
            } else {
                // Shared memory and named pipe server are ready and we're the first instance.
                isFirst = true;
            }
        }
    }
    
    virtual ~QSingleInstanceCheck() = default;
    
    /**
     * @return True if another instance is running.
     */
    inline bool isAlreadyRunning() const { return !isFirst; }

    /**
     * @brief Sends a message to the original instance.
     */
    inline void notify()
    {
        if (isFirst) {
            return;
        }

        QLocalSocket socket;
        socket.connectToServer(uniqueID);
    }

signals:

    /**
     * @brief Fired when a second instance called its notify() method.
     */
    void notified();

    void error(QString message);
    
private:
    
    QSharedMemory sharedMemory;
    QLocalServer server;
    QString uniqueID;
    bool isFirst;
};

#endif // QSINGLEINSTANCECHECK_H
