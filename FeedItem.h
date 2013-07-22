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
        AuthorRole,
        DescriptionRole,
        TimestampRole,
        UrlRole
    };
  
    FeedItem(QObject *parent = 0);
    
    // This class is immutable, so this is the c'tor you'll want to use.
    explicit FeedItem(
            const QString& title,
            const QString& author,
            const QString& description,
            const QDateTime& timestamp,
            const QUrl& url,
            QObject *parent = 0);
    
    // For sorting
    bool operator<(const FeedItem& rhs);
    
    
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    
    inline QString id() const { return title; }
    inline QString getTitle() const { return title; }
    inline QString getAuthor() const { return author; }
    inline QString getDescription() const { return description; }
    inline QDateTime getTimestamp() const { return timestamp; }
    inline QUrl getURL() const { return url; }
   
  private:
    QString title;
    QString author;
    QString description;
    QDateTime timestamp;
    QUrl url;
};

#endif // FEEDITEM_H
