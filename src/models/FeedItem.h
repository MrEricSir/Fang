#ifndef FEEDITEM_H
#define FEEDITEM_H

#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QVariant>
#include <QTextStream>

#include "DBObject.h"
#include "ListModel.h"
#include "src/models/NewsList.h"

class NewsItem;
class NewsList;

// IDs of special feeds.  (Normal feed IDs start at 0.)

enum SpecialFeedID {
    FEED_ID_ALLNEWS = -2,
    FEED_ID_PINNED = -1
};

class FeedItem : public ListItem, DBObject
{
    Q_OBJECT
    
public:
    
    enum Roles {
        TitleRole = Qt::UserRole+1,
        SubtitleRole,
        LastUpdatedRole,
        MinutesToUpdateRole,
        UrlRole,
        SiteURLRole,
        ImageURLRole,
        IsUpdatingRole,
        UnreadCountRole,
        DropTargetRole,
        ErrorFlagRole,
        IsSelectedRole,
        IsSpecialFeedRole,
        IsFolderRole,
        ParentFolderRole,
        FolderOpenRole,
        BookmarksEnabledRole,
        UIDRole,
        SelfRole
    };
    
    FeedItem(QObject *parent = nullptr);
    
    // This class is immutable, so this is the c'tor you'll want to use.
    explicit FeedItem(
            const qint64 id,
            const qint32 ordinal,
            const QString& title,
            const QString& subtitle,
            const QDateTime& lastUpdated,
            quint32 minutesToUpdate,
            const QUrl& url,
            const QUrl& siteURL,
            const QString& userURL,
            const QUrl& imageURL,
            const QDateTime& lastIconUpdate,
            qint64 parentFolder = -1, // Default values for top level non-folder.
            bool folderOpen = true,   // TODO: Save folder open state from last session.
            QObject *parent = nullptr);
    
    virtual ~FeedItem();
    
    /**
     * @brief Ordinal-based sort, used for re-sorting the list.
     * @param rhs
     * @return 
     */
    bool operator<(const FeedItem& rhs);
    
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);
    Qt::ItemFlags flags() const;
    QHash<int, QByteArray> roleNames() const;
    
    void setIsUpdating(bool isUpdating);
    
    // Unused, required for ListItem base class.
    inline QString id() const {
        QString ret;
        QTextStream output(&ret);
        output << "FeedItem_" << _id;
        return ret;
    }

public slots:
    
    inline QString getTitle() const { return title; }
    inline QString getSubtitle() const { return subtitle; }
    inline QDateTime getLastUpdated() const { return lastUpdated; }
    inline quint32 getMinutesToUpdate() const { return minutesToUpdate; }
    inline QUrl getURL() const { return url; }
    inline QUrl getSiteURL() const { return siteURL; }
    inline QString getUserURL() const { return userURL; }
    inline QUrl getImageURL() const { return imageURL; }
    inline int getIsUpdating() const { return isUpdating; }
    inline quint32 getUnreadCount() const { return unreadCount; }
    inline QString getDropTarget() const { return dropTarget; }
    inline FeedItem* getSelf() const { return const_cast<FeedItem*>(this); }
    virtual inline qint64 getDbID() const { return _id; }
    inline bool isSpecialFeed() const { return _id < 0; }
    
    void setImageURL(const QUrl& url);
    
    void setTitle(const QString& newTitle);
    
    void setDropTarget(const QString& dropTarget);
    
    void setIsSelected(bool s);

    // Override for folders.
    virtual bool isFolder() const { return false; }
    virtual void setIsFolder(bool isFolder) {
        Q_UNUSED(isFolder);
        qCritical() << "FeedItem::setIsFolder: Unsupported on base type";
    }

    void setParentFolder(qint64 parentFolder);
    void setFolderOpen(bool folderOpen);
    
    /**
     * @brief Clears all news items.  Does NOT signal.
     * @return 
     */
    virtual void clearNews();
    
    /**
     * @brief Provides direct access to the news list.
     *
     * Note: This represents news items that are loaded and can be viewed. As such it will
     * slowly grow as more news items are added to the feed.
     */
    inline NewsList* getNewsList() { return &newsList; }
    
    /**
     * @brief Used to set the bookmark internally.  External classes shouldn't need to call this.
     * @param bookmark Item ID or -1 to clear.t
     */
    virtual void setBookmark(qint64 toBookmarkID);
    
    /**
     * @param item
     * @param allowBackward
     * @return True if this item can be bookmarked.
     */
    virtual bool canBookmark(qint64 proposedBookmarkID, bool allowBackward);
    
    /**
     * @brief Returns the current bookmark ID or -1 if none.
     * @return 
     */
    inline qint64 getBookmarkID() const { return _bookmarkID; }
    
    /**
     * @brief Detaches the feed ID when this feed is being disconnected.
     */
    inline void clearDbId() { _id = -100; }
    
    /**
     * @return The ID of the very first item in the feed that we have in our database;
     *         not the ID that's necessarily currently loaded.
     */
    inline qint64 getFirstNewsID() { return firstNewsID; }
    
    /**
     * @brief setFirstNewsID Sets the first item available in the feed.  This is used
     *                       to tell if we should draw the top bookmark to unbookmark all.
     * @param id
     */
    inline void setFirstNewsID(qint64 id) { firstNewsID = id; }
    
    /**
     * @brief Sets the unread count to the new value and emits a change signal.
     * @param unreadCount
     */
    void setUnreadCount(qint32 unreadCount);
    
    /**
     * @brief Returns the ordinal (note: only really used in resorting the list.)
     * @return 
     */
    inline int getOrdinal() const { return ordinal; }
    
    /**
     * @brief Sets the ordinal.
     */
    void setOrdinal(int newOrdinal);
    
    /**
     * @brief Sets the optional error flag.  Used in batch import.
     * @param errorFlag
     */
    void setErrorFlag(bool errorFlag);
    
    /**
     * @return True if error flag is set, else false.
     */
    inline bool getErrorFlag() const { return _errorFlag; }
    
    /**
     * @brief Changes the URL.
     * @param url
     */
    void setURL(QUrl url);
    
    /**
     * @return True if this item is selected.
     */
    inline bool getIsSelected() const { return isSelected; }
    
    void setLastIconUpdate(QDateTime last) { lastIconUpdate = last; }
    QDateTime getLastIconUpdate() { return lastIconUpdate; }

    /**
     * @brief If true, the feed supports bookmarks.  Otherwise false.
     * @return  By default, returns true.  Override if you want it to return false.
     */
    virtual bool bookmarksEnabled() const;

    /**
     * @brief getParentFolderID
     * @return The ID of the parent folder, or -1 if none.
     */
    qint64 getParentFolderID() const {
        return _parentFolder;
    }
    
signals:
    
    void appended(NewsItem* item);
    void removed(NewsItem* item);
    void titleChanged();
    void unreadCountChanged(quint32 unread);
    void folderOpenChanged();
        
private:
    qint64 _id;
    qint32 ordinal;
    QString title;
    QString subtitle;
    QDateTime lastUpdated;
    quint32 minutesToUpdate;
    QUrl url;
    QUrl siteURL;
    QString userURL;
    QUrl imageURL;
    NewsList newsList;
    int isUpdating;
    qint32 unreadCount;
    qint64 _bookmarkID;
    QString dropTarget;
    bool _errorFlag;
    bool isSelected;
    QDateTime lastIconUpdate;
    qint64 firstNewsID;
    qint64 _parentFolder;
    bool _folderOpen;
};

#endif // FEEDITEM_H
