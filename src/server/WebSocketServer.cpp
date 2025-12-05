#include "WebSocketServer.h"

#include <QDesktopServices>
#include <QDebug>
#include <QTextStream>

#include "../FangApp.h"

WebSocketServer::WebSocketServer(QObject *parent) :
    QObject(parent),
    server("Fang WebSocket", QWebSocketServer::NonSecureMode),
    pSocket(nullptr),
    isReady(false),
    fangSettings(nullptr)
{
    // Listen for incoming connections!
    if (!server.listen(QHostAddress::LocalHost, 2842)) {
        //
        // TODO: Panic!
        //
        qDebug() << "Websocket unable to listen";
    }

    connect(&server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

void WebSocketServer::init(FangSettings *fangSettings)
{
    this->fangSettings = fangSettings;
    connect(fangSettings, &FangSettings::fontSizeChanged, this, &WebSocketServer::onFontSizeChanged);
    connect(fangSettings, &FangSettings::currentStyleChanged, this, &WebSocketServer::onStyleChanged);

    connect(FangApp::instance(), &FangApp::currentFeedChanged, this, &WebSocketServer::onCurrentFeedChanged);
}

void WebSocketServer::onNewConnection()
{
    qDebug() << "NewsWebSocketServer::onNewConnection()";

    // Kill any existing connections.
    socketDisconnected();

    // Accept our new connection!
    pSocket = server.nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);
}

void WebSocketServer::processMessage(QString message)
{
    // qDebug() << "NewsWebSocketServer: " << message;

    // Break up our message into a command and execute it.
    int spaceIndex = message.indexOf(' ');
    if (spaceIndex <= 0) {
        qDebug() << "NewsWebSocketServer didn't understand this command: " << message;

        return;
    }

    execute(message.left(spaceIndex), message.mid(spaceIndex + 1));
}

void WebSocketServer::socketDisconnected()
{
    // qDebug() << "NewsWebSocketServer::socketDisconnected";
    if (pSocket) {
        pSocket->deleteLater();
        pSocket = NULL;

        isReady = false;
    }
}

void WebSocketServer::execute(const QString &command, const QString &data)
{
    // qDebug() << "command: " << command;
    // qDebug() << "data: " << data;

    FangApp* app = FangApp::instance();
    if ("removeNewsTop" == command) {
        app->removeAndDelete(true, data.toInt());
    } else if ("removeNewsBottom" == command) {
        app->removeAndDelete(false, data.toInt());
    }
}

void WebSocketServer::sendCommand(const QString &command, const QString &data)
{
    // TODO: Should we queue up messages before the socket's ready, or is that CrazyTalk (SM)?
    if (!pSocket) {
        qDebug() << "WebSocket: The socket is not connected yet! Slow down!";
        qDebug() << "WebSocket: Tried to send command " << command;

        return;
    }

    pSocket->sendTextMessage(command + " " + data);
}

void WebSocketServer::onStyleChanged(QString style)
{
    Q_UNUSED(style);
    sendCommand("styleChanged", "");
}

void WebSocketServer::onFontSizeChanged(QString font)
{
    Q_UNUSED(font);
    sendCommand("styleChanged", "");
}

void WebSocketServer::onCurrentFeedChanged()
{
    sendCommand("feedChanged", "");
}

void WebSocketServer::drawBookmark(qint64 bookmarkID)
{
    sendCommand("drawBookmark", QString::number(bookmarkID));
}

void WebSocketServer::jumpToBookmark()
{
    FeedItem* currentFeed = FangApp::instance()->getCurrentFeed();
    if (!currentFeed->bookmarksEnabled() && currentFeed->getBookmark()) {
        // Nothing to do!
        return;
    }

    // Find the bookmark.
    bool bookmarkLoaded = false;
    for (NewsItem* item : *currentFeed->getNewsList()) {
        if (currentFeed->getBookmark() == item) {
            bookmarkLoaded = true;
            break;
        }
    }

    if (bookmarkLoaded) {
        // Jump straight to the bookmark.
        sendCommand("jumpToBookmark", "");
    } else {
        // Re-init the feed.
        FangApp::instance()->setCurrentFeed(currentFeed, true);
    }
}

void WebSocketServer::jumpNext()
{
    sendCommand("jumpNext", "");
}

void WebSocketServer::jumpPrevious()
{
    sendCommand("jumpPrevious", "");
}

void WebSocketServer::showNews()
{
    sendCommand("showNews", "");
}

void WebSocketServer::showWelcome()
{
    sendCommand("showWelcome", "");
}
