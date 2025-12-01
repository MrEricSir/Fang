#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "../FangObject.h"
#include <QHttpServer>
#include <QTcpServer>

class WebServer : public FangObject
{
    Q_OBJECT
public:
    WebServer(QObject *parent = nullptr);

private:
    QString updatePinObject(qint64 newsID, bool pinned);

    QHttpServer server;
    QTcpServer* tcpServer;
};

#endif // WEBSERVER_H
