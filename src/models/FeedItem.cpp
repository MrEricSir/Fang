#include "FeedItem.h"
#include "NewsItem.h"

#include <QDebug>

FeedItem::FeedItem(QObject *parent) :
    ListItem(parent),
    _id(-1),
    ordinal(-1),
    title(""),
    subtitle(""),
    lastUpdated(),
    minutesToUpdate(0),
    url(),
    siteURL(),
    imageURL(),
    newsList(NULL),
    isUpdating(false),
    unreadCount(0),
    bookmark(NULL),
    dropTarget("none")
    
{
    newsList = new QList<NewsItem*>();
}

FeedItem::FeedItem(qint64 id, const qint32 ordinal, const QString &title, const QString &subtitle,
                   const QDateTime &lastUpdated, quint32 minutesToUpdate, const QUrl &url,
                   const QUrl& siteURL, const QUrl &imageURL, QObject* parent) :
    ListItem(parent),
    _id(id),
    ordinal(ordinal),
    title(title),
    subtitle(subtitle),
    lastUpdated(lastUpdated),
    minutesToUpdate(minutesToUpdate),
    url(url),
    siteURL(siteURL),
    imageURL(imageURL),
    newsList(NULL),
    isUpdating(false),
    unreadCount(0),
    bookmark(NULL),
    dropTarget("none")
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
    names[DropTargetRole] = "dropTarget";
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
    case DropTargetRole:
        return getDropTarget();
    default:
        return QVariant();
    }
}

bool FeedItem::setData(const QVariant &value, int role)
{
    switch(role) {
    case DropTargetRole:
        setDropTarget(value.toString());
        return true;
    }
    
    return false;
}

Qt::ItemFlags FeedItem::flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool FeedItem::operator<(const FeedItem& rhs) {
    return ordinal < rhs.getOrdinal();
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

void FeedItem::setTitle(const QString &newTitle)
{
    if (title == newTitle)
        return;
    
    title = newTitle;
    emit titleChanged();
    emit dataChanged();
}

void FeedItem::setDropTarget(const QString& newDropTarget)
{
    if (newDropTarget == dropTarget)
        return;
    
    dropTarget = newDropTarget;
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

void FeedItem::setUnreadCount(qint32 unreadCount)
{
    this->unreadCount = unreadCount;
    
    emit dataChanged();
}
