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
    QHttpServer server;
    QTcpServer* tcpServer;
};

#endif // WEBSERVER_H
