#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "../FangObject.h"
#include <QHttpServer>
#include <QTcpServer>

#include "../operations/LoadNewsOperation.h"

class WebServer : public FangObject
{
    Q_OBJECT
public:
    WebServer(QObject *parent = nullptr);

private:
    // Loads a file from the specified QRC folder.
    QByteArray loadResourceFile(QString folder, QString filename) const;

    // Updates a pin in the DB.
    QString updatePinObject(qint64 newsID, bool pinned);

    // Loads news from the DB.
    QString loadNews(LoadNewsOperation::LoadMode mode);

    void addNewsItem(NewsItem *item, QVariantList *newsList);

    QVariantList getCSS();

    QHttpServer server;
    QTcpServer* tcpServer;
};

#endif // WEBSERVER_H
