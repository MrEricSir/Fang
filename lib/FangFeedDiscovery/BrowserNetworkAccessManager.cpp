#include "BrowserNetworkAccessManager.h"

#include <QNetworkDiskCache>
#include <QStandardPaths>

BrowserNetworkAccessManager::BrowserNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);
    if (!cacheDir.isEmpty()) {
        setCache(diskCache);
    }
}

QNetworkReply* BrowserNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest& request, QIODevice* outgoingData)
{
    QNetworkRequest& req = const_cast<QNetworkRequest&>(request);

    // This SHOULD be the default, but just in case.
    req.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                          QNetworkRequest::PreferNetwork);

    // Mimic Chromium to avoid servers that block non-browser User-Agents.
    // Qt WebEngine is Chromium-based, so this is honest enough.
    req.setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36");

    // Required for blogs.gnome.org.
    req.setRawHeader("Accept",
                         "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

    return QNetworkAccessManager::createRequest(op, req, outgoingData);
}
