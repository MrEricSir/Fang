#include "FeedItem.h"
#include "NewsItem.h"

#include <QDebug>

FeedItem::FeedItem(QObject *parent) :
    ListItem(parent),
    _id(-1),
    title(""),
    subtitle(""),
    lastUpdated(),
    minutesToUpdate(0),
    url(),
    siteURL(),
    imageURL(),
    bookmark(NULL),
    newsList(NULL),
    isUpdating(false)
    
{
    newsList = new QList<NewsItem*>();
}

FeedItem::FeedItem(qint64 id, const QString &title, const QString &subtitle, const QDateTime &lastUpdated,
                   quint32 minutesToUpdate, const QUrl &url, const QUrl& siteURL, const QUrl &imageURL,
                   NewsItem* bookmark, QObject* parent) :
    ListItem(parent),
    _id(id),
    title(title),
    subtitle(subtitle),
    lastUpdated(lastUpdated),
    minutesToUpdate(minutesToUpdate),
    url(url),
    siteURL(siteURL),
    imageURL(imageURL),
    bookmark(bookmark),
    newsList(NULL),
    isUpdating(false)
{
    newsList = new QList<NewsItem*>();
}

FeedItem::~FeedItem()
{
    //qDebug() << "Feed destroyed " << title;
}

QHash<int, QByteArray> FeedItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[SubtitleRole] = "subtitle";
    names[LastUpdatedRole] = "lastUpdated";
    names[MinutesToUpdateRole] = "minutesToUpdate";
    names[UrlRole] = "url";
    names[SiteURLRole] = "siteURL";
    names[ImageURLRole] = "imageURL";
    names[IsUpdatingRole] = "isUpdating";
    names[SelfRole] = "self";
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
    case SiteURLRole:
        return getSiteURL();
    case ImageURLRole:
        return getImageURL();
    case IsUpdatingRole:
        return getIsUpdating();
    case SelfRole:
        return QVariant::fromValue(getSelf());
    default:
        return QVariant();
    }
}

bool FeedItem::operator<(const FeedItem& rhs) {
    Q_UNUSED(rhs);
    // TODO
    // add ordinal to DB
    return false;
}


void FeedItem::setIsUpdating(bool isUpdating)
{
    this->isUpdating = isUpdating;
    emit dataChanged();
}

void FeedItem::setImageURL(const QUrl &url)
{
    if (imageURL == url)
        return;
    
    imageURL = url;
    emit dataChanged();
}

void FeedItem::append(NewsItem *item)
{
    newsList->append(item);
    emit appended(item);
}

void FeedItem::remove(NewsItem *item)
{
    newsList->removeAll(item);
    emit removed(item);
    
    delete item;
}

void FeedItem::setBookmark(NewsItem *item)
{
    if (item != NULL)
        Q_ASSERT(newsList->contains(item));
    
    bookmark = item;
}
