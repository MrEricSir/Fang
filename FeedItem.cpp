#include "FeedItem.h"

FeedItem::FeedItem(QObject *parent) :
    ListItem(parent),
    title(""),
    author(""),
    description(""),
    timestamp(),
    url()
{
}

FeedItem::FeedItem(const QString &title, const QString &author, const QString &description, 
                   const QDateTime &timestamp, const QUrl &url, QObject *parent) :
    ListItem(parent),
    title(title),
    author(author),
    description(description),
    timestamp(timestamp),
    url(url)
{
}

QHash<int, QByteArray> FeedItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[AuthorRole] = "author";
    names[TimestampRole] = "timestamp";
    names[DescriptionRole] = "description";
    names[UrlRole] = "url";
    return names;
}

QVariant FeedItem::data(int role) const
{
    switch(role) {
    case TitleRole:
        return getTitle();
    case AuthorRole:
        return getAuthor();
    case TimestampRole:
        return getTimestamp();
    case DescriptionRole:
        return getDescription();
    case UrlRole:
        return getURL();
    default:
        return QVariant();
    }
}

bool FeedItem::operator<(const FeedItem& rhs) {
    // Use title if dates are equal.
    if (timestamp == rhs.timestamp)
        return title < rhs.title;
    
    // Sort on timestamp.
    return timestamp < rhs.timestamp;
}
