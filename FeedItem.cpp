#include "FeedItem.h"

FeedItem::FeedItem(QObject *parent) :
    ListItem(parent),
    title(""),
    subtitle(""),
    lastUpdated(),
    minutesToUpdate(0),
    url(),
    imageURL()
{
}

FeedItem::FeedItem(const QString &title, const QString &subtitle, const QDateTime &lastUpdated, 
                   quint32 minutesToUpdate, const QUrl &url, const QUrl &imageURL, ListModel* newsList, QObject* parent) :
    ListItem(parent),
    title(title),
    subtitle(subtitle),
    lastUpdated(lastUpdated),
    minutesToUpdate(minutesToUpdate),
    url(url),
    imageURL(imageURL),
    newsList(newsList)
{
}

QHash<int, QByteArray> FeedItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[SubtitleRole] = "subtitle";
    names[LastUpdatedRole] = "lastUpdated";
    names[MinutesToUpdateRole] = "minutesToUpdate";
    names[UrlRole] = "url";
    names[ImageURLRole] = "imageURL";
    names[NewsListRole] = "newsList";
    return names;
}

QVariant FeedItem::data(int role) const
{
    switch(role) {
    case TitleRole:
        return getTitle();
    case SubtitleRole:
        return getSubtitle();
    case LastUpdatedRole:
        return getLastUpdated();
    case MinutesToUpdateRole:
        return getMinutesToUpdate();
    case UrlRole:
        return getURL();
    case ImageURLRole:
        return getImageURL();
    case NewsListRole:
        return QVariant::fromValue(getNewsList());
    default:
        return QVariant();
    }
}

bool FeedItem::operator<(const FeedItem& rhs) {
    // TODO
    // add ordinal to DB
    return false;
}
