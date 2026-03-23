#ifndef RAWFEED_H
#define RAWFEED_H

#include <QObject>

#include "../FangObject.h"
#include "RawNews.h"

class RawFeed : public FangObject
{
    Q_OBJECT

public:
    enum FeedType { RSS = 0, GoogleNewsSitemap = 1 };

    explicit RawFeed(QObject *parent = nullptr);
    virtual ~RawFeed();

    FeedType feedType = RSS;

    QString title;
    QString subtitle;
    QUrl url;
    QDateTime lastUpdated;
    quint32 minutesToUpdate;
    QUrl siteURL;
    QUrl imageURL;
    
    QList<RawNews*> items;

    bool isPodcast = false;

    // For debuggin' and stuff.
    QString toString();
};

#endif // RAWFEED_H
