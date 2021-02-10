#include "LisvelFeedItem.h"

LisvelFeedItem::LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString& title, QObject *parent) :
    FeedItem(id, ordinal, title, "", QDateTime(), 0, QUrl(), QUrl(), QUrl(), QDateTime(), -1, true, parent),
    _newsIDs()
{
}

void LisvelFeedItem::clearNews()
{
    // Remove the view.
    _newsIDs.clear();

    // Bubble bobble up our chain.
    FeedItem::clearNews();
}
