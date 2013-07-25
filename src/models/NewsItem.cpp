#include "NewsItem.h"
#include <QDebug>

NewsItem::NewsItem(QObject *parent) :
    ListItem(parent),
    feed(NULL),
    title(""),
    author(""),
    description(""),
    timestamp(),
    url()
{
}

NewsItem::NewsItem(FeedItem* feed, const QString &title, const QString &author, 
                   const QString &description, const QDateTime &timestamp, const QUrl &url, 
                   QObject *parent) :
    ListItem(parent),
    feed(feed),
    title(title),
    author(author),
    description(description),
    timestamp(timestamp),
    url(url)
{
}

QHash<int, QByteArray> NewsItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FeedRole] = "feed";
    names[TitleRole] = "title";
    names[AuthorRole] = "author";
    names[TimestampRole] = "timestamp";
    names[DescriptionRole] = "description";
    names[UrlRole] = "url";
    names[SiteTitleRole] = "siteTitle";
    names[SiteImageURLRole] = "siteImageURL";
    return names;
}

QVariant NewsItem::data(int role) const
{
    switch(role) {
    case TitleRole:
        return getTitle();
    case AuthorRole:
        return getAuthor();
    case TimestampRole:
        qDebug() << "timestamp "<< getTimestamp().toString();
        return getTimestamp();
    case DescriptionRole:
        return getDescription();
    case UrlRole:
        return getURL();
    case SiteTitleRole:
        return feed->getTitle();
    case SiteImageURLRole:
        return feed->getImageURL();
    default:
        return QVariant();
    }
}

bool NewsItem::operator<(const NewsItem& rhs) {
    // Use title if dates are equal.
    if (timestamp == rhs.timestamp)
        return title < rhs.title;
    
    // Sort on timestamp.
    return timestamp < rhs.timestamp;
}
