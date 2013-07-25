#include "FeedItem.h"
#include "NewsItem.h"

FeedItem::FeedItem(QObject *parent) :
    ListItem(parent),
    title(""),
    subtitle(""),
    lastUpdated(),
    minutesToUpdate(0),
    url(),
    imageURL(),
    isUpdating(false)
{
    newsList = new ListModel(new NewsItem, parent);
}

FeedItem::FeedItem(const QString &title, const QString &subtitle, const QDateTime &lastUpdated, 
                   quint32 minutesToUpdate, const QUrl &url, const QUrl &imageURL, QObject* parent) :
    ListItem(parent),
    title(title),
    subtitle(subtitle),
    lastUpdated(lastUpdated),
    minutesToUpdate(minutesToUpdate),
    url(url),
    imageURL(imageURL),
    isUpdating(false)
{
    newsList = new ListModel(new NewsItem, parent);
}

FeedItem::~FeedItem() {
    delete newsList;
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
    names[IsUpdatingRole] = "isUpdating";
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
    //case IsUpdatingRole:
        //return getIsUpdating();
    default:
        return QVariant();
    }
}

bool FeedItem::operator<(const FeedItem& rhs) {
    // TODO
    // add ordinal to DB
    return false;
}


void FeedItem::setIsUpdating(bool isUpdating)
{
    this->isUpdating = isUpdating;
    emit dataChanged();
}
