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
    qDebug() << "Get Host returning: " << ret;
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

void NetworkUtilities::fakeBrowserHeaders(QNetworkRequest* request)
{
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    request->setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
    // Required for blogs.gnome.org.
    request->setRawHeader("Accept",
                         "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
}
