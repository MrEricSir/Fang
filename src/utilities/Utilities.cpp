#include "Utilities.h"

#include <QDebug>
#include <QNetworkDiskCache>
#include <QStandardPaths>

Utilities::Utilities()
{
}

FeedItem *Utilities::feedItemFromRaw(RawFeed *raw, qint64 dbId, QObject* parent)
{
    return new FeedItem(dbId,
                        0,
                        raw->title,
                        raw->subtitle,
                        raw->lastUpdated,
                        raw->minutesToUpdate,
                        raw->url,
                        raw->siteURL,
                        raw->imageURL,
                        parent
                        );
}

QUrl Utilities::getHost(const QUrl& url) {
    QUrl ret = url;
    ret.setPath("");
    ret.setQuery("");
    QString sUrl = ret.toString();
    if (sUrl.endsWith("?"))
        sUrl = sUrl.remove(sUrl.length() - 1, 1);
    
    ret.setUrl(sUrl);
    return ret;
}

void Utilities::addNetworkAccessManagerCache(QNetworkAccessManager *manager)
{
    // Set default cache dir.
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(manager);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);
    if (!cacheDir.isEmpty())
        manager->setCache(diskCache);
}
