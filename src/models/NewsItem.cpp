#include "NewsItem.h"
#include "FeedItem.h"
#include <QDebug>

NewsItem::NewsItem(QObject *parent) :
    FangObject(parent),
    feed(nullptr),
    _id(-1),
    _feedId(-1),
    title(""),
    author(""),
    summary(""),
    content(""),
    timestamp(),
    url(),
    pinned(false)
{
}

NewsItem::NewsItem(FeedItem* feed, qint64 id, qint64 feedId, const QString &title,
                   const QString &author, const QString &summary, const QString &content,
                   const QDateTime &timestamp, const QUrl &url, bool pinned) :
    FangObject(feed),
    feed(feed),
    _id(id),
    _feedId(feedId),
    title(title),
    author(author),
    summary(summary),
    content(content),
    timestamp(timestamp),
    url(url),
    pinned(pinned)
{
}

bool NewsItem::operator<(const NewsItem& right) {
    return LessThan(this, &right);
}

bool NewsItem::LessThan(const NewsItem* left, const NewsItem* right) {
    // Use id if dates are equal.
    if (left->timestamp == right->timestamp)
        return left->_id < right->_id;
    
    // Sort on timestamp.
    return left->timestamp < right->timestamp;
}

bool NewsItem::GreaterThan(const NewsItem *left, const NewsItem *right)
{
    return !LessThan(left, right);
}
