#ifndef RAWFEED_H
#define RAWFEED_H

#include <QObject>

#include "../FangObject.h"
#include "RawNews.h"

class RawFeed : public FangObject
{
    Q_OBJECT
    
public:
    explicit RawFeed(QObject *parent = 0);
    virtual ~RawFeed();
    
    QString title;
    QString subtitle;
    QUrl url;
    QDateTime lastUpdated;
    quint32 minutesToUpdate;
    QUrl siteURL;
    QUrl imageURL;
    
    QList<RawNews*> items;
    
    // For debuggin' and stuff.
    QString toString();
};

#endif // RAWFEED_H
