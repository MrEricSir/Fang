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
    isUpdating(false),
    isCurrent(false)
    
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
    isUpdating(false),
    isCurrent(false)
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
    names[UnreadCountRole] = "unreadCount";
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
    case UnreadCountRole:
        return getUnreadCount();
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

quint32 FeedItem::getUnreadCount() const
{
    if (bookmark == NULL)
        return newsList->size();
    
    int index = newsList->indexOf(bookmark);
    if (index < 0)
        return newsList->size();
    
    int ret = newsList->size() - index - 1;
    
    if (ret < 0)
        return 0;
    
    return ret;
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
    if (newsList->contains(item))
        return;
    
    newsList->append(item);
    emit appended(item);
    
    emit dataChanged();
}

void FeedItem::remove(NewsItem *item)
{
    newsList->removeAll(item);
    emit removed(item);
    
    item->deleteLater();
    
    emit dataChanged();
}

bool FeedItem::canBookmark(NewsItem *item)
{
    if (bookmark == NULL)
        return true;
    
    if (item == NULL)
        return false;
    
    int currentBookmarkIndex = newsList->indexOf(bookmark);
    int newBookmarkIndex = newsList->indexOf(item);
    
    // If the new one is later in the list, we're good.
    return newBookmarkIndex > currentBookmarkIndex;
}

void FeedItem::setBookmark(NewsItem *item)
{
    if (item != NULL)
        Q_ASSERT(newsList->contains(item));
    
    if (bookmark == item)
        return; // Nothing to do.
    
    if (!canBookmark(item))
        return; // Shouldn't have called this method, sir.
    
    bookmark = item;
    emit dataChanged();
}

void FeedItem::setIsCurrent(bool current)
{
    isCurrent = current;
}
