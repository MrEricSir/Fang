#include "WebServer.h"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QUrl>

#include "../FangApp.h"
#include "../utilities/NetworkUtilities.h"

WebServer::WebServer(QObject *parent) :
    FangObject(parent)
{
    qDebug() << "Launching WebServer...";

    tcpServer = new QTcpServer(this);

    // Listen for incoming connections!
    if (!tcpServer->listen(QHostAddress::LocalHost, 2844)) {
        qDebug() << "WebServer: TCP server unable to listen";

        // TODO: Throw an exception?
    }

    if (!server.bind(tcpServer)) {
        qDebug() << "WebServer: Unable to bind to TCP server";

        // TODO: Throw an exception?
    }

    // Needed for CORS due to qrc file paths.
    server.addAfterRequestHandler(&server, [](const QHttpServerRequest &, QHttpServerResponse &response) {
        auto headers = response.headers();
        headers.append(QHttpHeaders::WellKnownHeader::AccessControlAllowOrigin, "*");
        response.setHeaders(std::move(headers));
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
        return loadNews(LoadNewsOperation::stringToMode(mode));
    });

    server.route("/api/css", this, [this] {
        return QString::fromUtf8(QJsonDocument::fromVariant(getCSS()).toJson());
    });
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
    QVariantMap document;
    QVariantList newsList;

    // Perform load.
    LoadNewsOperation* loader = FangApp::instance()->loadNews(mode);

    // Load mode.
    document.insert("mode", LoadNewsOperation::modeToString(mode));

    FeedItem* currentFeed = FangApp::instance()->getCurrentFeed();
    if (mode == LoadNewsOperation::Initial)  {
        // Bookmark (if needed)
        if (currentFeed->bookmarksEnabled() && currentFeed->getBookmarkID() >= 0) {
            qint64 idOfBookmark = currentFeed->getBookmarkID();
            document.insert("bookmark", idOfBookmark);
        }
    }

    // // First news ID.
    document.insert("firstNewsID", currentFeed->getFirstNewsID());

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
    document.insert("news", newsList);
    QString json = QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());

    return json;
}

void WebServer::addNewsItem(NewsItem *item, QVariantList *newsList)
{
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

QVariantList WebServer::getCSS()
{
    FangApp* app = FangApp::instance();
    QVariantList classes;

    classes << app->getPlatform();
    classes << "FONT_" + app->getSettings()->getFontSize();
    classes << app->getSettings()->getCurrentStyle();

    if (!app->getCurrentFeed()->bookmarksEnabled()) {
        classes << "bookmarksDisabled";
    }

    return classes;
}

