#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "../FangObject.h"
#include <QHttpServer>
#include <QTcpServer>

#include "../operations/LoadNewsOperation.h"

// Forward declaration to avoid circular include
class FangApp;

/*!
  WebServer used internally by Fang for the WebView.
 */
class WebServer : public FangObject
{
    Q_OBJECT
public:
    /*!
        \brief Constructs WebServer with a reference to FangApp.
        \param appInstance The FangApp instance to use for all operations. (Can be mocked in tests.)
        \param parent QObject parent.
     */
    explicit WebServer(FangApp* appInstance, FangObject *parent = nullptr);

    // Gets the port for this server, or zero if invalid.
    inline quint16 port() { return tcpServer ? tcpServer->serverPort() : 0; }

    // Configures the weboscket server port.
    inline void setWebsocketPort(quint16 port) { webSocketPort = port; }

private:

    // Gets the config object.
    QString getConfig();

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

    QString getCSS();

    FangApp* app;
    QHttpServer server;
    QTcpServer* tcpServer;
    quint16 webSocketPort;
};

#endif // WEBSERVER_H
