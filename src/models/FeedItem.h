#ifndef FEEDITEM_H
#define FEEDITEM_H

#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QVariant>

#include "ListModel.h"

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
        NewsListRole
    };
    
    FeedItem(QObject *parent = 0);
    
    // This class is immutable, so this is the c'tor you'll want to use.
    explicit FeedItem(
            const QString& title,
            const QString& subtitle,
            const QDateTime& lastUpdated,
            quint32 minutesToUpdate,
            const QUrl& url,
            const QUrl& imageURL,
            ListModel *newsFeed,
            QObject *parent = 0);
    
    // For sorting
    bool operator<(const FeedItem& rhs);
    
    
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    
    inline QString id() const { return title; }
    inline QString getTitle() const { return title; }
    inline QString getSubtitle() const { return subtitle; }
    inline QDateTime getLastUpdated() const { return lastUpdated; }
    inline quint32 getMinutesToUpdate() const { return minutesToUpdate; }
    inline QUrl getURL() const { return url; }
    inline QUrl getImageURL() const { return imageURL; }
    inline ListModel* getNewsList() const { return newsList; }
   
  private:
    QString title;
    QString subtitle;
    QDateTime lastUpdated;
    quint32 minutesToUpdate;
    QUrl url;
    QUrl imageURL;
    ListModel* newsList;
};

#endif // FEEDITEM_H
