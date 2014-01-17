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

QDateTime Utilities::dateFromFeedString(QString timestamp)
{
    QDateTime ret;
    // Date time.
    // Examples:
    // Tue, 02 Jul 2013 01:01:24 +0000
    // Sun, 13 Oct 2013 19:15:29  PST
    
    // TODO: figure out the time zone issue
    // For now, we're shaving off everything after the last space.
    timestamp = timestamp.left(timestamp.trimmed().lastIndexOf(" "));
    timestamp = timestamp.trimmed();
    //qDebug() << "Time string: " << timestamp;
    
    ret = QDateTime::fromString(timestamp, "ddd, dd MMM yyyy hh:mm:ss"); 
    
    // Try RFC 3339, normally used by Atom.
    // Example: // 2013-08-07T16:47:54Z
    if (!ret.isValid())
        ret = QDateTime::fromString(timestamp.toUpper(), "yyyy-MM-ddThh:mm:ssZ"); 
    
    return ret;
}
