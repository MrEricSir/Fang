#include "Utilities.h"
#include <QDebug>

Utilities::Utilities()
{
}

FeedItem *Utilities::feedItemFromRaw(RawFeed *raw, qint64 dbId, QObject* parent)
{
    return new FeedItem(dbId,
                        raw->title,
                        raw->subtitle,
                        raw->lastUpdated,
                        raw->minutesToUpdate,
                        raw->url,
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
    qDebug() << "Get host: " << ret.toString();
    return ret;
}
