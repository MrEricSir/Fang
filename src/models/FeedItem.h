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
        ImageURLRole,
        IsUpdatingRole,
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
            const QUrl& imageURL,
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
    inline QUrl getImageURL() const { return imageURL; }
    inline int getIsUpdating() const { return isUpdating; }
    inline FeedItem* getSelf() const { return const_cast<FeedItem*>(this); }
    
    /**
     * @brief Appends a NewsItem to the end of the feed.
     * @param item
     */
    void append(NewsItem* item);
    
    /**
     * @brief Removes a NewsItem from the feed.
     * @param item
     */
    void remove(NewsItem* item);
    
    inline QList<NewsItem*>* getNewsList() { return newsList; }
    
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
    QUrl imageURL;
    QList<NewsItem*>* newsList;
    int isUpdating;
};

#endif // FEEDITEM_H
