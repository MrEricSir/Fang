#include "NetworkUtilities.h"

#include <QNetworkDiskCache>
#include <QStandardPaths>


NetworkUtilities::NetworkUtilities()
{
}

QUrl NetworkUtilities::getHost(const QUrl& url) {
    QUrl ret = url;
    ret.setPath("");
    ret.setQuery("");
    QString sUrl = ret.toString();
    if (sUrl.endsWith("?"))
        sUrl = sUrl.remove(sUrl.length() - 1, 1);
    
    ret.setUrl(sUrl);
    return ret;
}

void NetworkUtilities::addCache(QNetworkAccessManager *manager)
{
    // Set default cache dir.
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(manager);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);
    if (!cacheDir.isEmpty())
        manager->setCache(diskCache);
}

void NetworkUtilities::useCache(QNetworkRequest* request)
{
    // This SHOULD be the default, but just in case.
    request->setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                          QNetworkRequest::PreferNetwork);
}
