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
        SelfRole
    };
    
    FeedItem(QObject *parent = 0);
    
    // This class is immutable, so this is the c'tor you'll want to use.
    explicit FeedItem(
            const qint64 id,
            const QString& title,
            const QString& subtitle,
            const QDateTime& lastUpdated,
            quint32 minutesToUpdate,
            const QUrl& url,
            const QUrl& siteURL,
            const QUrl& imageURL,
            NewsItem* bookmark,
            QObject *parent = 0);
    
    virtual ~FeedItem();
    
    // For sorting
    bool operator<(const FeedItem& rhs);
    
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    
    void setIsUpdating(bool isUpdating);
    
    inline QString id() const { 
        QString ret;
        QTextStream output(&ret);
        output << "FeedItem_" << _id;
        return ret;
    }
    
    inline QString getTitle() const { return title; }
    inline QString getSubtitle() const { return subtitle; }
    inline QDateTime getLastUpdated() const { return lastUpdated; }
    inline quint32 getMinutesToUpdate() const { return minutesToUpdate; }
    inline QUrl getURL() const { return url; }
    inline QUrl getSiteURL() const { return siteURL; }
    inline QUrl getImageURL() const { return imageURL; }
    inline int getIsUpdating() const { return isUpdating; }
    inline FeedItem* getSelf() const { return const_cast<FeedItem*>(this); }
    inline qint64 getDbId() const { return _id; }
    virtual quint32 getUnreadCount() const;
    
    void setImageURL(const QUrl& url);
    
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
     * @param item
     * @return True if this item can be bookmarked.
     */
    bool canBookmark(NewsItem* item);
    
    inline NewsItem* getBookmark() { return bookmark; }
    virtual void setBookmark(NewsItem* item);
    
    inline void clearDbId() { _id = -1; }
    
    /**
     * @brief This is set before the feed changes.
     * @param current
     */
    virtual void setIsCurrent(bool current);
    
    inline bool getIsCurrent() { return isCurrent; }
    
signals:
    
    void appended(NewsItem* item);
    void removed(NewsItem* item);
    
private:
    qint64 _id;
    QString title;
    QString subtitle;
    QDateTime lastUpdated;
    quint32 minutesToUpdate;
    QUrl url;
    QUrl siteURL;
    QUrl imageURL;
    NewsItem* bookmark;
    QList<NewsItem*>* newsList;
    int isUpdating;
    bool isCurrent;
};

#endif // FEEDITEM_H
