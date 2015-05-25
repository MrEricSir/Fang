#ifndef NEWSWEBSOCKETSERVER_H
#define NEWSWEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets>
#include "../operations/LoadNews.h"

/**
 * @brief This is the WebSocket server that manages the news page.
 */
class NewsWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit NewsWebSocketServer(QObject *parent = 0);

signals:

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
     * @brief Updates the pinned status of a given news item.
     * @param newsID
     * @param pinned If true, the item is pinned. If not, then it's not pinned.
     */
    void updatePin(qint64 newsID, bool pinned);

private slots:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();

    // Executes a command requested by the news page.
    void execute(const QString& command, const QString& data);

    // Sends a command to the WebSocket.
    void sendCommand(const QString& command, const QString& data);

    // Some news got loaded, probably! Yay!
    void onLoadNewsFinished(LoadNews* loader);

    // Adds a news item to a variant list (to be turned into JSON)
    void addNewsItem(NewsItem *item, QVariantList* newsList);

private:
    QWebSocketServer server;
    QWebSocket *pSocket;
    bool isReady;
    bool loadInProgress;
};

#endif // NEWSWEBSOCKETSERVER_H
