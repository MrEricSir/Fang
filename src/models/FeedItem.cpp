#include "NewsItem.h"
#include "NewsList.h"
#include "FeedItem.h"

#include "../utilities/FangLogging.h"

FeedItem::FeedItem(QObject *parent) :
    ListItem(parent),
    _id(0),
    ordinal(-1),
    title(""),
    subtitle(""),
    lastUpdated(),
    minutesToUpdate(0),
    url(),
    siteURL(),
    imageURL(),
    newsList(),
    isUpdating(false),
    unreadCount(0),
    _bookmarkID(-1),
    dropTarget("none"),
    _errorFlag(false),
    isSelected(false),
    lastIconUpdate(),
    firstNewsID(-1),
    _parentFolder(-1),
    _folderOpen(true)
    
{
}

FeedItem::FeedItem(qint64 id, const qint32 ordinal, const QString &title, const QString &subtitle,
                   const QDateTime &lastUpdated, quint32 minutesToUpdate, const QUrl &url,
                   const QUrl& siteURL, const QString& userURL, const QUrl &imageURL,
                   const QDateTime& lastIconUpdate, qint64 parentFolder, bool folderOpen, QObject* parent) :
    ListItem(parent),
    _id(id),
    ordinal(ordinal),
    title(title),
    subtitle(subtitle),
    lastUpdated(lastUpdated),
    minutesToUpdate(minutesToUpdate),
    url(url),
    siteURL(siteURL),
    userURL(userURL),
    imageURL(imageURL),
    newsList(),
    isUpdating(false),
    unreadCount(0),
    _bookmarkID(-1),
    dropTarget("none"),
    _errorFlag(false),
    isSelected(false),
    lastIconUpdate(lastIconUpdate),
    firstNewsID(-1),
    _parentFolder(parentFolder),
    _folderOpen(folderOpen)
{
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
    names[IsSpecialFeedRole] = "isSpecialFeed";
    names[IsFolderRole] = "isFolder";
    names[ParentFolderRole] = "parentFolder";
    names[FolderOpenRole] = "folderOpen";
    names[BookmarksEnabledRole] = "bookmarksEnabled";
    names[UIDRole] = "uid";
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
        case IsSpecialFeedRole:
            return isSpecialFeed();
        case IsFolderRole:
            return isFolder();
        case ParentFolderRole:
            return QVariant::fromValue(_parentFolder);
        case FolderOpenRole:
            return QVariant::fromValue(_folderOpen);
        case BookmarksEnabledRole:
            return bookmarksEnabled();
        case UIDRole:
            return getDbID();
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
    case IsFolderRole:
        setIsFolder(value.toBool());
        return true;
    case ParentFolderRole:
        setParentFolder(value.toLongLong());
        return true;
    case FolderOpenRole:
        setFolderOpen(value.toBool());
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
    if (imageURL == url) {
        return;
    }
    
    imageURL = url;
    emit dataChanged();
}

void FeedItem::setTitle(const QString &newTitle)
{
    if (title == newTitle) {
        return;
    }
    
    title = newTitle;
    emit titleChanged();
    emit dataChanged();
}

void FeedItem::setDropTarget(const QString& newDropTarget)
{
    if (newDropTarget == dropTarget) {
        return;
    }
    
    dropTarget = newDropTarget;
    emit dataChanged();
}

void FeedItem::setIsSelected(bool s)
{
    if (isSelected == s) {
        return;
    }
    
    isSelected = s;
    emit dataChanged();
}

void FeedItem::setParentFolder(qint64 parentFolder)
{
    _parentFolder = parentFolder;
    emit dataChanged();
}

void FeedItem::setFolderOpen(bool folderOpen)
{
    _folderOpen = folderOpen;
    emit dataChanged();
}

void FeedItem::clearNews()
{
    newsList.clear();
}

bool FeedItem::canBookmark(qint64 proposedBookmarkID, bool allowBackward)
{
    // What is this? I don't even.
    if (proposedBookmarkID < -1) {
        return false;
    }
    
    // Given no current bookmark, anything will do.
    if (_bookmarkID < 0) {
        return true;
    }
    
    // That's a no-op for you, young man.
    if (_bookmarkID == proposedBookmarkID) {
        return false;
    }
    
    // Sure, whatever you want.
    if (allowBackward) {
        return true;
    }

    // We asked SQLite to always increase our IDs, remember.
    return proposedBookmarkID > _bookmarkID;
}

void FeedItem::setBookmark(qint64 toBookmarkID)
{
    qCDebug(logModel) << "FeedItem::setBookmark to " << toBookmarkID;
    if (toBookmarkID == _bookmarkID) {
        return; // Nothing to do.
    }
    
    _bookmarkID = toBookmarkID;
    emit dataChanged();
}

void FeedItem::setUnreadCount(qint32 unreadCount)
{
    if (this->unreadCount == unreadCount) {
        return;
    }
    
    this->unreadCount = unreadCount;
    emit dataChanged();
    emit unreadCountChanged(unreadCount);
}

void FeedItem::setOrdinal(int newOrdinal)
{
    ordinal = newOrdinal;
}

void FeedItem::setErrorFlag(bool errorFlag)
{
    if (_errorFlag == errorFlag) {
        return;
    }
    
    _errorFlag = errorFlag;
    emit dataChanged();
}

void FeedItem::setURL(QUrl url)
{
    if (this->url == url) {
        return;
    }
    
    this->url = url;
    emit dataChanged();
}

bool FeedItem::bookmarksEnabled() const
{
    return true;
}
