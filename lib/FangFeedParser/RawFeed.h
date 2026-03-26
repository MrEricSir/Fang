#ifndef RAWFEED_H
#define RAWFEED_H

#include <memory>

#include <QList>
#include <QString>
#include <QUrl>
#include <QDateTime>

#include "RawNews.h"

class RawFeed
{
public:
    enum FeedType { RSS = 0, GoogleNewsSitemap = 1, JSONFeed = 2 };

    RawFeed() = default;

    FeedType feedType = RSS;

    QString title = "";
    QString subtitle = "";
    QUrl url;
    QDateTime lastUpdated;
    quint32 minutesToUpdate = 0;
    QUrl siteURL;
    QUrl imageURL;

    QList<std::shared_ptr<RawNews>> items;

    bool isPodcast = false;

    // For debuggin' and stuff.
    QString toString();
};

#endif // RAWFEED_H
