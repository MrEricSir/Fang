#include "NewsWebSocketServer.h"

#include <QDesktopServices>
#include <QDebug>
#include <QTextStream>

#include "../FangApp.h"
#include "../utilities/NetworkUtilities.h"
#include "src/models/NewsList.h"

NewsWebSocketServer::NewsWebSocketServer(QObject *parent) :
    QObject(parent),
    server("Fang WebSocket", QWebSocketServer::NonSecureMode),
    pSocket(nullptr),
    isReady(false),
    loadInProgress(true),
    fangSettings(nullptr)
{
    // Listen for incoming connections!
    if (!server.listen(QHostAddress::LocalHost, 2842)) {
        //
        // TODO: Panic! (at the disco?)
        //
        qDebug() << "Websocket unable to listen";
    }

    connect(&server, &QWebSocketServer::newConnection, this, &NewsWebSocketServer::onNewConnection);
}

void NewsWebSocketServer::init(FangSettings *fangSettings)
{
    this->fangSettings = fangSettings;
    connect(fangSettings, &FangSettings::fontSizeChanged, this, &NewsWebSocketServer::onFontSizeChanged);
    connect(fangSettings, &FangSettings::styleChanged, this, &NewsWebSocketServer::onStyleChanged);

    connect(FangApp::instance(), &FangApp::windowHeightChanged,
            this, &NewsWebSocketServer::onWindowHeightChanged);
}

void NewsWebSocketServer::onNewConnection()
{
    qDebug() << "NewsWebSocketServer::onNewConnection()";

    // Kill any existing connections.
    socketDisconnected();

    // Accept our new connection!
    pSocket = server.nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &NewsWebSocketServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &NewsWebSocketServer::socketDisconnected);

    // Can't do this in the c'tor because FangApp hasn't fully initialized yet.
    connect(FangApp::instance(), &FangApp::loadNewsFinished, this, &NewsWebSocketServer::onLoadNewsFinished);
}

void NewsWebSocketServer::processMessage(QString message)
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

void NewsWebSocketServer::socketDisconnected()
{
    // qDebug() << "NewsWebSocketServer::socketDisconnected";
    if (pSocket) {
        pSocket->deleteLater();
        pSocket = NULL;

        isReady = false;
    }
}

void NewsWebSocketServer::execute(const QString &command, const QString &data)
{
    // qDebug() << "command: " << command;
    // qDebug() << "data: " << data;

    FangApp* app = FangApp::instance();
    if ("pageLoaded" == command) {
        isReady = true;
        loadInProgress = true;
        emit isLoadInProgressChanged();
        app->setCurrentFeed(app->getLastFeedSelected());
    } else if ("setBookmark" == command) {
        app->setBookmark(data.toLongLong());
    } else if ("forceBookmark" == command) {
        app->setBookmark(data.toLongLong(), true);
    } else if ("openLink" == command) {
        QString fixed = NetworkUtilities::urlFixup(data);
        QDesktopServices::openUrl(QUrl(fixed));
    } else if ("setPin" == command) {
        QString dataCopy(data);
        QTextStream stream(&dataCopy);
        qint64 id;
        int pin;
        stream >> id >> pin;

        app->setPin(id, (bool) pin);
    } else if ("removeNewsTop" == command) {
        app->removeAndDelete(true, data.toInt());
    } else if ("removeNewsBottom" == command) {
        app->removeAndDelete(false, data.toInt());
    } else if ("loadComplete" == command) {
        loadInProgress = false;
        emit isLoadInProgressChanged();
    } else if ("loadNext" == command) {
        if (!loadInProgress) {
            app->loadNews(LoadNewsOperation::Append);
        }
    } else if ("loadPrevious" == command) {
        if (!loadInProgress) {
            app->loadNews(LoadNewsOperation::Prepend);
        }
    }
}

void NewsWebSocketServer::sendCommand(const QString &command, const QString &data)
{
    // TODO: Should we queue up messages before the socket's ready, or is that CrazyTalk (SM)?
    if (!pSocket) {
        qDebug() << "WebSocket: The socket is not connected yet! Slow down!";
        qDebug() << "WebSocket: Tried to send command " << command;

        return;
    }

    pSocket->sendTextMessage(command + " " + data);
}

void NewsWebSocketServer::onLoadNewsFinished(LoadNewsOperation *loader)
{
    //qDebug() << "Load complete for news feed: " << loader->getFeedItem()->getTitle();

    if (loader->getMode() != LoadNewsOperation::Initial && loader->getPrependList().isEmpty() &&
            loader->getAppendList().isEmpty()) {
        // Nothing to do!
        sendCommand("loadEmpty", "");

        return;
    }

    QString operationName = loader->getMode() == LoadNewsOperation::Initial ? "initial" :
                            loader->getMode() == LoadNewsOperation::Append ? "append" : "prepend";

    QVariantMap document;
    QVariantList newsList;

    // Load mode.
    document.insert("mode", operationName);

    FeedItem* currentFeed = FangApp::instance()->getCurrentFeed();
    if (loader->getMode() == LoadNewsOperation::Initial)  {
        // Bookmark (if needed)
        if (currentFeed->bookmarksEnabled() && currentFeed->getBookmark()) {
            qint64 idOfBookmark = currentFeed->getBookmark()->getDbID();
            document.insert("bookmark", idOfBookmark);
        }

        // CSS
        document.insert("css", getCSS());
    }

    // Window height.
    document.insert("windowHeight", QString::number(
                        FangApp::instance()->getWindowHeight()));

    // First news ID.
    document.insert("firstNewsID", currentFeed->getFirstNewsID());

    // Build our news list.
    if (!loader->getPrependList().isEmpty()) {
        if (loader->getMode() == LoadNewsOperation::Initial) {
            // Reverse list.
            for (int i = loader->getPrependList().size() - 1; i >= 0; i--) {
                NewsItem* item = loader->getPrependList().at(i);
                addNewsItem(item, &newsList);
            }
        } else {
            foreach(NewsItem* item, loader->getPrependList()) {
                addNewsItem(item, &newsList);
            }
        }
    }

    // Stuff the new items into our feed.
    if (!loader->getAppendList().isEmpty()) {
        foreach(NewsItem* item, loader->getAppendList()) {
            addNewsItem(item, &newsList);
        }
    }



    // Add our news list.
    document.insert("news", newsList);

   // emit addInProgress(false, operationName);

    QString json = QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
    //qDebug() << "JSON:" << json;

    sendCommand("load", json);
}

void NewsWebSocketServer::addNewsItem(NewsItem *item, QVariantList *newsList)
{
    //qDebug() << "Add news: " << item->id();

    // Make sure we get the real feed title for All News and folders.
    QString feedTitle = (!item->getFeed()->isSpecialFeed() && !item->getFeed()->isFolder()) ?
                            item->getFeed()->getTitle() :
                            FangApp::instance()->feedForId(item->getFeedId())->getTitle();

    QVariantMap itemMap;
    itemMap["id"] = item->getDbID();
    itemMap["title"] = item->getTitle();
    itemMap["url"] = item->getURL().toString();
    itemMap["feedTitle"] = feedTitle;
    itemMap["timestamp"] = item->getTimestamp().toMSecsSinceEpoch();
    itemMap["content"] = item->getContent() != "" ? item->getContent() : item->getSummary();
    itemMap["pinned"] = item->getPinned();

    // Add to the list.
    *newsList << itemMap;
}

QVariantList NewsWebSocketServer::getCSS()
{
    FangApp* app = FangApp::instance();
    QVariantList classes;

    classes << app->getPlatform();
    classes << "FONT_" + app->getSettings()->getFontSize();
    classes << app->getSettings()->getStyle();

    if (!app->getCurrentFeed()->bookmarksEnabled()) {
        classes << "bookmarksDisabled";
    }

    return classes;
}

void NewsWebSocketServer::updateCSS()
{
    sendCommand("updateCSS", QString::fromUtf8(QJsonDocument::fromVariant(getCSS()).toJson()));
}

void NewsWebSocketServer::onStyleChanged(QString style)
{
    Q_UNUSED(style);
    updateCSS();
}

void NewsWebSocketServer::onFontSizeChanged(QString font)
{
    Q_UNUSED(font);
    updateCSS();
}

void NewsWebSocketServer::onWindowHeightChanged()
{
    sendCommand("windowHeight", QString::number(
                    FangApp::instance()->getWindowHeight()));
}

void NewsWebSocketServer::drawBookmark(qint64 bookmarkID)
{
    sendCommand("drawBookmark", QString::number(bookmarkID));
}

void NewsWebSocketServer::updatePin(qint64 newsID, bool pinned)
{
    QVariantMap document;
    document.insert("id", newsID);
    document.insert("pinned", pinned);

    QString json = QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
    sendCommand("updatePin", json);
}

void NewsWebSocketServer::jumpToBookmark()
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

void NewsWebSocketServer::jumpNext()
{
    sendCommand("jumpNext", "");
}

void NewsWebSocketServer::jumpPrevious()
{
    sendCommand("jumpPrevious", "");
}

void NewsWebSocketServer::showNews()
{
    sendCommand("showNews", "");
}

void NewsWebSocketServer::showWelcome()
{
    updateCSS();
    sendCommand("showWelcome", "");
}
