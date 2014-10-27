#ifndef NEWSITEM_H
#define NEWSITEM_H

#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QVariant>
#include <QDebug>

#include "FeedItem.h"

#include "../FangObject.h"

class NewsItem : public FangObject
{
    Q_OBJECT
    
public:
    
    NewsItem(QObject *parent = 0);
    
    // This is the c'tor you'll want to use.
    explicit NewsItem(
            FeedItem* feed,
            qint64 id,
            qint64 feedId,
            const QString& title,
            const QString& author,
            const QString& summary,
            const QString& content,
            const QDateTime& timestamp,
            const QUrl& url);
    
    virtual ~NewsItem() {}
    
    // For sorting
    bool operator<(const NewsItem& rhs);
    static bool LessThan(const NewsItem* left, const NewsItem* right);
    static bool GreaterThan(const NewsItem* left, const NewsItem* right);
    
    inline FeedItem* getFeed() const { return feed; }
    
    // This returns the actual feed database ID
    inline qint64 getFeedId() const { return _feedId; }
    
    inline QString getTitle() const { return title; }
    inline QString getAuthor() const { return author; }
    inline QString getSummary() const { return summary; }
    inline QString getContent() const { return content; }
    inline QDateTime getTimestamp() const { return timestamp; }
    inline QUrl getURL() const { return url; }
    inline qint64 getDbID() const { return _id; }
   
  private:
    FeedItem* feed;
    qint64 _id;
    qint64 _feedId;
    QString title;
    QString author;
    QString summary;
    QString content;
    QDateTime timestamp;
    QUrl url;
};

#endif // NEWSITEM_H
