#ifndef NEWSWEBSOCKETSERVER_H
#define NEWSWEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets>
#include "../operations/LoadNews.h"
#include "FangSettings.h"

/**
 * @brief This is the WebSocket server that manages the news page.
 */
class NewsWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit NewsWebSocketServer(QObject *parent = 0);

    // Users MUST call this before using any method.
    void init(FangSettings *fangSettings);

signals:

    // Signals when a load is starting or ending.
    void isLoadInProgressChanged();

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

    /**
     * @return True if a load is in progress, else false.
     */
    bool isLoadInProgress() { return loadInProgress; }

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

    // Returns a list of CSS body classes.
    QVariantList getCSS();

    // Sends a command to update the CSS.
    void updateCSS();

    // Alert us to style changes.
    void onStyleChanged(QString style);

    // Alert us to font size changes.
    void onFontSizeChanged(QString font);

    // The window height changed!
    void onWindowHeightChanged();

private:
    QWebSocketServer server;
    QWebSocket *pSocket;
    bool isReady;
    bool loadInProgress;
    FangSettings *fangSettings;
};

#endif // NEWSWEBSOCKETSERVER_H
