#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets>
#include "../models/FangSettings.h"

/**
 * @brief This is the WebSocket server that manages the news page.
 */
class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = nullptr);

    // Users MUST call this before using any method.
    void init(FangSettings *fangSettings);

public slots:

    /**
     * @return True if the server is set up and ready to go.
     */
    bool isServerReady() { return isReady; }

    /**
     * @brief Manually moves the bookmark to the provided position. (Not needed on initial load)
     * @param bookmarkID
     */
    void drawBookmark(qint64 bookmarkID);

    /**
     * @brief Jumps the view to the bookmark (if any)
     */
    void jumpToBookmark();

    /**
     * @brief Jumps to the next news item (if any)
     */
    void jumpNext();

    /**
     * @brief Jumps to the previous news item (if any)
     */
    void jumpPrevious();

    /**
     * @brief Show the news view.
     */
    void showNews();

    /**
     * @brief Show the welcome/help view.
     */
    void showWelcome();

private slots:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();

    // Executes a command requested by the news page.
    void execute(const QString& command, const QString& data);

    // Sends a command to the WebSocket.
    void sendCommand(const QString& command, const QString& data);

    // Alert socket listener to style changes.
    void onStyleChanged(QString style);

    // Alert socket listener to font size change.
    void onFontSizeChanged(QString font);

    // Alert socket listener to feed change.
    void onCurrentFeedChanged();

private:
    QWebSocketServer server;
    QWebSocket *pSocket;
    bool isReady;
    FangSettings *fangSettings;
};

#endif // WEBSOCKETSERVER_H
