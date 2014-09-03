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
    _bookmark(-1),
    dropTarget("none"),
    _errorFlag(false),
    isSelected(false),
    lastIconUpdate()
    
{
    newsList = new QList<NewsItem*>();
}

FeedItem::FeedItem(qint64 id, const qint32 ordinal, const QString &title, const QString &subtitle,
                   const QDateTime &lastUpdated, quint32 minutesToUpdate, const QUrl &url,
                   const QUrl& siteURL, const QUrl &imageURL, const QDateTime& lastIconUpdate, QObject* parent) :
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
    _bookmark(-1),
    dropTarget("none"),
    _errorFlag(false),
    isSelected(false),
    lastIconUpdate(lastIconUpdate)
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
    names[ErrorFlagRole] = "errorFlag";
    names[IsSelectedRole] = "isSelected";
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
        case ErrorFlagRole:
            return getErrorFlag();
        case IsSelectedRole:
            return getIsSelected();
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
    case IsSelectedRole:
        setIsSelected(value.toBool());
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

void FeedItem::setIsSelected(bool s)
{
    if (isSelected == s)
        return;
    
    isSelected = s;
    emit dataChanged();
}

void FeedItem::clearNews()
{
    // Delete each and every news item.
    while(newsList->size() > 0) {
        newsList->takeFirst()->deleteLater();
    }
}

bool FeedItem::canBookmark(qint64 bookmarkID, bool allowBackward)
{
    // What is this? I don't even.
    if (bookmarkID < 0)
        return false;
    
    // Given no current bookmark, anything will do.
    if (_bookmark == -1)
        return true;
    
    // That's a no-op for you, young man.
    if (_bookmark == bookmarkID)
        return false;
    
    // Sure, whatever you want.
    if (allowBackward)
        return true;
    
    // We asked SQLite to always increase our IDs, remember.
    return bookmarkID > _bookmark;
}

void FeedItem::setBookmarkID(qint64 bookmark)
{
    if (bookmark == _bookmark)
        return; // Nothing to do.
    
    _bookmark = bookmark;
    emit dataChanged();
}

void FeedItem::setUnreadCount(qint32 unreadCount)
{
    if (this->unreadCount == unreadCount)
        return;
    
    this->unreadCount = unreadCount;
    emit dataChanged();
}

void FeedItem::setOrdinal(int newOrdinal)
{
    ordinal = newOrdinal;
}

void FeedItem::setErrorFlag(bool errorFlag)
{
    if (_errorFlag == errorFlag)
        return;
    
    _errorFlag = errorFlag;
    emit dataChanged();
}

void FeedItem::setURL(QUrl url)
{
    if (this->url == url)
        return;
    
    this->url = url;
    emit dataChanged();
}
