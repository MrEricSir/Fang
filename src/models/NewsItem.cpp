#include "NewsItem.h"
#include <QDebug>

NewsItem::NewsItem(QObject *parent) :
    QObject(parent),
    feed(NULL),
    _id(-1),
    _feedId(-1),
    title(""),
    author(""),
    summary(""),
    content(""),
    timestamp(),
    url()
{
}

NewsItem::NewsItem(FeedItem* feed, qint64 id, qint64 feedId, const QString &title,
                   const QString &author, const QString &summary, const QString &content,
                   const QDateTime &timestamp, const QUrl &url) :
    QObject(feed),
    feed(feed),
    _id(id),
    _feedId(feedId),
    title(title),
    author(author),
    summary(summary),
    content(content),
    timestamp(timestamp),
    url(url)
{
}

bool NewsItem::operator<(const NewsItem& right) {
    return LessThan(this, &right);
}

bool NewsItem::LessThan(const NewsItem* left, const NewsItem* right) {
    // Use title if dates are equal.
    if (left->timestamp == right->timestamp)
        return left->title < right->title;
    
    // Sort on timestamp.
    return left->timestamp < right->timestamp;
}

bool NewsItem::GreaterThan(const NewsItem *left, const NewsItem *right)
{
    return !LessThan(left, right);
}
