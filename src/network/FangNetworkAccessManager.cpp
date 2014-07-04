#include "FangNetworkAccessManager.h"

#include <QNetworkDiskCache>
#include <QStandardPaths>

FangNetworkAccessManager::FangNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);
    if (!cacheDir.isEmpty())
        setCache(diskCache);
}

QNetworkReply* FangNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest& request, QIODevice* outgoingData)
{
    QNetworkRequest& req = const_cast<QNetworkRequest&>(request);
    
    // This SHOULD be the default, but just in case.
    req.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                          QNetworkRequest::PreferNetwork);
    
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    req.setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
    // Required for blogs.gnome.org.
    req.setRawHeader("Accept",
                         "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    
    return QNetworkAccessManager::createRequest(op, req, outgoingData);
}
