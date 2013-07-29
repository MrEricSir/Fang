#include "Utilities.h"

Utilities::Utilities()
{
}


QString Utilities::htmlify(const QString& content) {
    return "<html><body>" + content + "</body></html>";
}

FeedItem *Utilities::feedItemFromRaw(RawFeed *raw, qint64 dbId, QObject* parent)
{
    return new FeedItem(dbId,
                        raw->title,
                        raw->subtitle,
                        raw->lastUpdated,
                        raw->minutesToUpdate,
                        raw->url,
                        QUrl(""), // TODO site URL
                        parent
                        );
}
