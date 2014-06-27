#include "Utilities.h"

#include <QDebug>

Utilities::Utilities()
{
}

FeedItem *Utilities::feedItemFromRaw(const RawFeed *raw, qint64 dbId, QObject* parent)
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
                        QDateTime(),
                        parent
                        );
}
