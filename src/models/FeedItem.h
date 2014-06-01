#ifndef FEEDITEM_H
#define FEEDITEM_H

#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QVariant>
#include <QTextStream>

#include "ListModel.h"

class NewsItem;

class FeedItem : public ListItem
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
        SelfRole
    };
    
    FeedItem(QObject *parent = 0);
    
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
            const QUrl& imageURL,
            QObject *parent = 0);
    
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
    
    inline QString id() const { 
        QString ret;
        QTextStream output(&ret);
        output << "FeedItem_" << _id;
        return ret;
    }
    
    Q_INVOKABLE inline QString getTitle() const { return title; }
    inline QString getSubtitle() const { return subtitle; }
    inline QDateTime getLastUpdated() const { return lastUpdated; }
    inline quint32 getMinutesToUpdate() const { return minutesToUpdate; }
    inline QUrl getURL() const { return url; }
    inline QUrl getSiteURL() const { return siteURL; }
    inline QUrl getImageURL() const { return imageURL; }
    inline int getIsUpdating() const { return isUpdating; }
    inline quint32 getUnreadCount() const { return unreadCount; }
    inline QString getDropTarget() const { return dropTarget; }
    inline FeedItem* getSelf() const { return const_cast<FeedItem*>(this); }
    inline qint64 getDbId() const { return _id; }
    inline bool isAllNews() const { return _id < 0; }
    
    void setImageURL(const QUrl& url);
    
    Q_INVOKABLE void setTitle(const QString& newTitle);
    
    Q_INVOKABLE void setDropTarget(const QString& dropTarget);
    
    /**
     * @brief Appends a NewsItem to the end of the feed.
     * @param item
     */
    virtual void append(NewsItem* item);
    
    /**
     * @brief Removes a NewsItem from the feed.
     * @param item
     */
    virtual void remove(NewsItem* item);
    
    /**
     * @brief Clears all news items.  Does NOT signal.
     * @return 
     */
    inline void clearNews() { newsList->clear(); }
    
    inline QList<NewsItem*>* getNewsList() { return newsList; }
    
    /**
     * @brief Used to set the bookmark internally.  External classes shouldn't need to call this.
     * @param item
     */
    virtual void setBookmark(NewsItem* item);
    
    /**
     * @param item
     * @return True if this item can be bookmarked.
     */
    bool canBookmark(NewsItem* item);
    
    /**
     * @brief Returns the current bookmark.
     * @return 
     */
    inline NewsItem* getBookmark() { return bookmark; }
    
    inline void clearDbId() { _id = -1; }
    
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
    
signals:
    
    void appended(NewsItem* item);
    void removed(NewsItem* item);
    void titleChanged();
        
private:
    qint64 _id;
    qint32 ordinal;
    QString title;
    QString subtitle;
    QDateTime lastUpdated;
    quint32 minutesToUpdate;
    QUrl url;
    QUrl siteURL;
    QUrl imageURL;
    QList<NewsItem*>* newsList;
    int isUpdating;
    qint32 unreadCount;
    NewsItem* bookmark;
    QString dropTarget;
};

#endif // FEEDITEM_H
