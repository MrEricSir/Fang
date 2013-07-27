#ifndef NEWSITEM_H
#define NEWSITEM_H

#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QVariant>
#include <QDebug>

#include "FeedItem.h"

class NewsItem : public QObject
{
    Q_OBJECT
    
public:
  
    NewsItem(QObject *parent = 0);
    
    // This is the c'tor you'll want to use.
    explicit NewsItem(
            FeedItem* feed,
            qint64 id,
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
    inline QString id() const { 
        QString ret;
        QTextStream output(&ret);
        output << "NewsItem_" << _id;
        return ret;
    }
    
    inline QString getTitle() const { return title; }
    inline QString getAuthor() const { return author; }
    inline QString getSummary() const { return summary; }
    inline QString getContent() const { return content; }
    inline QDateTime getTimestamp() const { return timestamp; }
    inline QUrl getURL() const { return url; }
   
  private:
    FeedItem* feed;
    qint64 _id;
    QString title;
    QString author;
    QString summary;
    QString content;
    QDateTime timestamp;
    QUrl url;
};

#endif // NEWSITEM_H
