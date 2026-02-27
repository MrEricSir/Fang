#include "WebServer.h"

#include <QDesktopServices>
#include <QFont>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QPalette>
#include <QUrl>

#include "../FangApp.h"
#include "../models/SearchFeedItem.h"
#include "../utilities/ErrorHandling.h"
#include "../utilities/FangLogging.h"
#include "../utilities/NetworkUtilities.h"

WebServer::WebServer(FangApp* appInstance, FangObject *parent) :
    FangObject(parent),
    app(appInstance),
    webSocketPort(0)
{
    qCDebug(logServer) << "Launching WebServer...";

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
        qCDebug(logServer) << "Open URL:" << url;

        QString urlFixed = NetworkUtilities::urlFixup(url);
        QDesktopServices::openUrl(QUrl(urlFixed));
        return "";
    });

    server.route("/api/set_bookmark/<arg>", this, [this] (qlonglong newsID) {
        app->setBookmark(newsID);
        return "";
    });

    server.route("/api/force_bookmark/<arg>", this, [this] (qlonglong newsID) {
        qCDebug(logServer) << "Force bookmark API called: newsID=" << newsID
                           << "currentBookmark=" << (app->getCurrentFeed()
                              ? app->getCurrentFeed()->getBookmarkID() : -1);
        app->setBookmark(newsID, true);
        qCDebug(logServer) << "Force bookmark completed: newsID=" << newsID
                           << "newBookmark=" << (app->getCurrentFeed()
                              ? app->getCurrentFeed()->getBookmarkID() : -1);
        return "";
    });

    server.route("/api/pin/<arg>", this, [this] (qlonglong newsID) {
        app->setPin(newsID, true);
        return updatePinObject(newsID, true);
    });

    server.route("/api/unpin/<arg>", this, [this] (qlonglong newsID) {
        app->setPin(newsID, false);
        return updatePinObject(newsID, false);
    });

    server.route("/api/load/<arg>", this, [this] (QString mode) {
        return loadNews(LoadNewsOperation::stringToMode(mode));
    });

    server.route("/api/css", this, [this] {
        return getCSS();
    });

    server.route("/api/config", this, [this]  {
        return getConfig();
    });

    server.route("/api/search", QHttpServerRequest::Method::Post, this, [this] (const QHttpServerRequest &request) {
        QJsonObject json = QJsonDocument::fromJson(request.body()).object();
        QString query = json.value("query").toString();
        QString scope = json.value("scope").toString("global");
        qint64 scopeId = json.value("scopeId").toInteger(-1);
        qCDebug(logServer) << "Search API called with query:" << query << "scope:" << scope << "scopeId:" << scopeId;
        return performSearch(query, scope, scopeId);
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
    LoadNewsOperation* loader = app->loadNews(mode);

    // Load mode.
    extras.insert("mode", LoadNewsOperation::modeToString(mode));

    FeedItem* currentFeed = app->getCurrentFeed();
    if (mode == LoadNewsOperation::Initial)  {
        // Bookmark (if needed)
        if (currentFeed->bookmarksEnabled() && currentFeed->getBookmarkID() >= 0) {
            qint64 idOfBookmark = currentFeed->getBookmarkID();
            extras.insert("bookmark", idOfBookmark);
        }
    }

    // // First news ID.
    extras.insert("firstNewsID", currentFeed->getFirstNewsID());

    // If this is a search feed, include the search query for client-side highlighting.
    SearchFeedItem* searchFeed = qobject_cast<SearchFeedItem*>(currentFeed);
    if (searchFeed && searchFeed->hasSearchQuery()) {
        extras.insert("searchQuery", searchFeed->getSearchQuery());
    }

    // Build our news list.
    // The prepend list comes from the DB query in DESC order (newest first among read items).
    // We need to reverse it so items are sent to the JS in chronological order (oldest first).
    QSet<qint64> sentIDs;  // Track IDs sent to JS to detect duplicates

    // Prepend older items to our list.
    if (loader != nullptr && !loader->getPrependList().isEmpty()) {
        qCDebug(logServer) << "loadNews: Sending" << loader->getPrependList().size() << "prepended items to JS";
        for (qsizetype i = loader->getPrependList().size() - 1; i >= 0; i--) {
            NewsItem* item = loader->getPrependList().at(i);
            if (sentIDs.contains(item->getDbID())) {
                qCCritical(logServer) << "loadNews: DUPLICATE in prependList! id=" << item->getDbID()
                                      << "already sent in this response";
            }
            sentIDs.insert(item->getDbID());
            addNewsItem(item, &newsList);
        }
    }

    // Stuff the new items into our feed.
    if (loader != nullptr && !loader->getAppendList().isEmpty()) {
        qCDebug(logServer) << "loadNews: Sending" << loader->getAppendList().size() << "appended items to JS"
                           << "mode=" << LoadNewsOperation::modeToString(mode);
        qint64 lastTimestamp = 0;
        for (NewsItem* item : std::as_const(loader->getAppendList())) {
            if (sentIDs.contains(item->getDbID())) {
                qCCritical(logServer) << "loadNews: DUPLICATE in appendList! id=" << item->getDbID()
                                      << "already sent in this response";
            }
            sentIDs.insert(item->getDbID());

            // Check if items are in timestamp order (should be ascending for append mode)
            qint64 itemTimestamp = item->getTimestamp().toMSecsSinceEpoch();
            if (lastTimestamp > 0 && itemTimestamp < lastTimestamp) {
                qCWarning(logServer) << "loadNews: Item id=" << item->getDbID()
                                     << "has EARLIER timestamp than previous item!"
                                     << "This may cause display order issues.";
            }
            lastTimestamp = itemTimestamp;

            addNewsItem(item, &newsList);
        }
    }

    // Add our news list and convert to a JSON string.
    return buildDocument(newsList, extras);
}

void WebServer::addNewsItem(NewsItem *item, QVariantList *newsList)
{
    QString feedTitle;
    if (item->getFeed()->isSpecialFeed() || item->getFeed()->isFolder()) {
        // For a special feeds and folder views, show the name of the feed for this news item.
        feedTitle = app->feedForId(item->getFeedId())->getTitle();
    } else if (item->getFeed()->getParentFolderID() >= 0) {
        // For feeds inside folders, show both the parent folder name and the feed name.
        feedTitle = app->feedForId(item->getFeed()->getParentFolderID())->getTitle() +
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

QString WebServer::buildDocument(const QVariantList &newsList, QVariantMap extras)
{
    QVariantMap document;
    document.insert("news", newsList);
    document.insert(extras);
    return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
}

QString WebServer::getCSS()
{
    QVariantList classes;

    classes << app->getPlatform();
    classes << "FONT_" + app->getSettings()->getFontSize();
    classes << app->getSettings()->getCurrentStyle();

    if (!app->getCurrentFeed()->bookmarksEnabled()) {
        classes << "bookmarksDisabled";
    }

    // Set up color scheme from system colors to match QML.
    QVariantMap result;
    result.insert("classes", classes);

    QPalette palette = QGuiApplication::palette();
    QColor accent = palette.accent().color();
    result.insert("accent", accent.name());  // e.g. "#007aff"

    QFont systemFont = QGuiApplication::font();
    result.insert("font", systemFont.family());  // e.g. ".AppleSystemUIFont"

    // Scrollbar color matching Style.qml values.
    QString currentStyle = app->getSettings()->getCurrentStyle();
    result.insert("scrollbar", currentStyle == "DARK" ? "#ddd" : "#999");

    return QString::fromUtf8(QJsonDocument::fromVariant(result).toJson());
}

QString WebServer::performSearch(const QString& query, const QString& scope, qint64 scopeId)
{
    QString trimmedQuery = query.trimmed();
    if (trimmedQuery.isEmpty()) {
        qCDebug(logServer) << "performSearch: Empty query";
        QVariantMap document;
        document.insert("error", "Empty search query");
        return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
    }

    // Convert string scope to enum.
    SearchFeedItem::Scope searchScope = SearchFeedItem::Scope::Global;
    if (scope == "feed") {
        searchScope = SearchFeedItem::Scope::Feed;
    } else if (scope == "folder") {
        searchScope = SearchFeedItem::Scope::Folder;
    }

    // Perform the search (this switches to the search feed).
    SearchFeedItem* searchFeed = app->performSearch(trimmedQuery, searchScope, scopeId);
    if (!searchFeed) {
        QVariantMap document;
        document.insert("error", "Search failed");
        return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
    }

    // Load the search results using the standard loadNews path.
    // performSearch already switched to the search feed, so loadNews will use it.
    return loadNews(LoadNewsOperation::Initial);
}


