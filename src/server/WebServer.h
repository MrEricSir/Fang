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

    // Updates a pin in the DB.
    QString updatePinObject(qint64 newsID, bool pinned);

    // Loads news from the DB.
    QString loadNews(LoadNewsOperation::LoadMode mode);

    void addNewsItem(NewsItem *item, QVariantList *newsList);

    // Indicates that we should show the welcome screen.
    QString loadWelcome();

    // Puts together the return object for loadNews() and loadWelcome().
    QString buildDocument(const QVariantList& newsList, bool showWelcome,
                          QVariantMap extras = QVariantMap());

    QVariantList getCSS();

    QHttpServer server;
    QTcpServer* tcpServer;
};

#endif // WEBSERVER_H
