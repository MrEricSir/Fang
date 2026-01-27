#include "WebServer.h"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QUrl>

#include "../FangApp.h"
#include "../utilities/NetworkUtilities.h"
#include "../utilities/ErrorHandling.h"

WebServer::WebServer(QObject *parent) :
    FangObject(parent),
    webSocketPort(0)
{
    qDebug() << "Launching WebServer...";

    tcpServer = new QTcpServer(this);

    // Listen for incoming connections!
    FANG_CHECK(tcpServer->listen(QHostAddress::LocalHost),
               "WebServer: TCP server unable to listen");

    FANG_CHECK(server.bind(tcpServer),
               "WebServer: Unable to bind to TCP server");

    // Routes ------

    server.route("/html/<arg>", this, [] (QString path) {
        // Assume the files is in our QRC and attempt to load it.
        return QHttpServerResponse::fromFile(":/html/" + path);
    });

    server.route("/api/open_link", QHttpServerRequest::Method::Post, this, [] (const QHttpServerRequest &request) {
        QJsonObject json = QJsonDocument::fromJson(request.body()).object();
        QString url = json.value("url").toString();
        qDebug() << "Open URL:" << url;

        QString urlFixed = NetworkUtilities::urlFixup(url);
        QDesktopServices::openUrl(QUrl(urlFixed));
        return "";
    });

    server.route("/api/set_bookmark/<arg>", this, [] (qlonglong newsID) {
        FangApp::instance()->setBookmark(newsID);
        return "";
    });

    server.route("/api/force_bookmark/<arg>", this, [] (qlonglong newsID) {
        FangApp::instance()->setBookmark(newsID, true);
        return "";
    });

    server.route("/api/pin/<arg>", this, [this] (qlonglong newsID) {
        FangApp::instance()->setPin(newsID, true);
        return updatePinObject(newsID, true);
    });

    server.route("/api/unpin/<arg>", this, [this] (qlonglong newsID) {
        FangApp::instance()->setPin(newsID, false);
        return updatePinObject(newsID, false);
    });

    server.route("/api/load/<arg>", this, [this] (QString mode) {
        // Show news, or welcome screen if there's no feeds.
        if (FangApp::instance()->feedCount() <= 1) {
            return loadWelcome();
        } else {
            return loadNews(LoadNewsOperation::stringToMode(mode));
        }
    });

    server.route("/api/css", this, [this] {
        return getCSS();
    });

    server.route("/api/config", this, [this]  {
        return getConfig();
    });
}

QString WebServer::getConfig()
{
    // NOTE: If we wind up adding a lot of stuff in here, we may want to merge it
    // with the existing FangSettings object.
    QVariantMap document;
    document.insert("webSocketPort", webSocketPort);

    return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
}

QString WebServer::updatePinObject(qint64 newsID, bool pinned)
{
    QVariantMap document;
    document.insert("newsID", newsID);
    document.insert("pinned", pinned);

    return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
}

QString WebServer::loadNews(LoadNewsOperation::LoadMode mode)
{
    QVariantMap extras;
    QVariantList newsList;

    // Perform load.
    LoadNewsOperation* loader = FangApp::instance()->loadNews(mode);

    // Load mode.
    extras.insert("mode", LoadNewsOperation::modeToString(mode));

    FeedItem* currentFeed = FangApp::instance()->getCurrentFeed();
    if (mode == LoadNewsOperation::Initial)  {
        // Bookmark (if needed)
        if (currentFeed->bookmarksEnabled() && currentFeed->getBookmarkID() >= 0) {
            qint64 idOfBookmark = currentFeed->getBookmarkID();
            extras.insert("bookmark", idOfBookmark);
        }
    }

    // // First news ID.
    extras.insert("firstNewsID", currentFeed->getFirstNewsID());

    // Build our news list.
    if (!loader->getPrependList().isEmpty()) {
        if (mode == LoadNewsOperation::Initial) {
            // Reverse list.
            for (qsizetype i = loader->getPrependList().size() - 1; i >= 0; i--) {
                NewsItem* item = loader->getPrependList().at(i);
                addNewsItem(item, &newsList);
            }
        } else {
            for (NewsItem* item : loader->getPrependList()) {
                addNewsItem(item, &newsList);
            }
        }
    }

    // Stuff the new items into our feed.
    if (!loader->getAppendList().isEmpty()) {
        for (NewsItem* item : std::as_const(loader->getAppendList())) {
            addNewsItem(item, &newsList);
        }
    }

    // Add our news list and convert to a JSON string.
    return buildDocument(newsList, false, extras);
}

void WebServer::addNewsItem(NewsItem *item, QVariantList *newsList)
{
    QString feedTitle;
    if (item->getFeed()->isSpecialFeed() || item->getFeed()->isFolder()) {
        // For a special feeds and folder views, show the name of the feed for this news item.
        feedTitle = FangApp::instance()->feedForId(item->getFeedId())->getTitle();
    } else if (item->getFeed()->getParentFolderID() >= 0) {
        // For feeds inside folders, show both the parent folder name and the feed name.
        feedTitle = FangApp::instance()->feedForId(item->getFeed()->getParentFolderID())->getTitle() +
                    " → " + item->getFeed()->getTitle();
    } else {
        // For all other feeds simply show the feed title.
        feedTitle = item->getFeed()->getTitle();
    }

    QVariantMap itemMap;
    itemMap["id"] = item->getDbID();
    itemMap["title"] = item->getTitle();
    itemMap["url"] = item->getURL().toString();
    itemMap["feedTitle"] = feedTitle;
    itemMap["timestamp"] = item->getTimestamp().toMSecsSinceEpoch();
    itemMap["content"] = item->getContent() != "" ? item->getContent() : item->getSummary();
    itemMap["pinned"] = item->getPinned();

    // Replace empty titles with "no subject"
    if (itemMap["title"].toString().trimmed().isEmpty()) {
        itemMap["title"] = "<i>[ No Subject ]</i>";
    }

    // Add to the list.
    *newsList << itemMap;
}

QString WebServer::loadWelcome()
{
    QVariantList newsList;
    return buildDocument(newsList, true);
}

QString WebServer::buildDocument(const QVariantList &newsList, bool showWelcome, QVariantMap extras)
{
    QVariantMap document;
    document.insert("showWelcome", showWelcome);
    document.insert("news", newsList);
    document.insert(extras);
    return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
}

QString WebServer::getCSS()
{
    FangApp* app = FangApp::instance();
    QVariantList classes;

    classes << app->getPlatform();
    classes << "FONT_" + app->getSettings()->getFontSize();
    classes << app->getSettings()->getCurrentStyle();

    if (!app->getCurrentFeed()->bookmarksEnabled()) {
        classes << "bookmarksDisabled";
    }

    return QString::fromUtf8(QJsonDocument::fromVariant(classes).toJson());
}

