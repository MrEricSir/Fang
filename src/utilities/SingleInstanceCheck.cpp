#include "SingleInstanceCheck.h"
#include <QLocalSocket>
#include <QDebug>

SingleInstanceCheck::SingleInstanceCheck(QString uniqueID, FangObject* parent) :
    FangObject(parent), uniqueID(uniqueID), /*settingsGroup(settingsGroup),*/ isFirst(false)
{
    QObject::connect(&server, &QLocalServer::newConnection,
                     this, &SingleInstanceCheck::onClientConnected);

    sharedMemory.setKey(uniqueID);
    if (sharedMemory.create(1)) {
        // Delete any existing server (only for *nix systems) and start our named pipe server.
        server.removeServer(uniqueID);
        if (!server.listen(uniqueID)) {
            qCritical() << "SingleInstanceCheck: Unable to listen to server: "
                        << server.errorString();
        } else {
            // Shared memory and named pipe server are good to go.
            qDebug() << "SingleInstanceCheck: Server started";
            isFirst = true;
        }
    } else {
        qInfo() << "SingleInstanceCheck: Fang is already running";
    }
}

void SingleInstanceCheck::notify()
{
    if (isFirst) {
        return;
    }

    QLocalSocket socket;
    socket.connectToServer(uniqueID);
}

void SingleInstanceCheck::onClientConnected()
{
    qDebug() << "SingleInstanceCheck: Client connected";
    emit notified();
}
