#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QObject>
#include <QDebug>
#include "../parser/RawFeed.h"
#include "../models/FeedItem.h"

class Utilities
{
public:
    Utilities();
    
    static QString htmlify(const QString &content);
    
    static FeedItem* feedItemFromRaw(RawFeed *raw, qint64 dbId, QObject* parent);
};

#endif // UTILITIES_H
