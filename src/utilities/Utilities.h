#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <QDateTime>

#include "../parser/RawFeed.h"
#include "../models/FeedItem.h"

class Utilities
{
public:
    Utilities();
    
    /**
     * @brief Converts a RawFeed object into a good, proper FeedItem.
     * @param raw
     * @param dbId
     * @param parent
     * @return 
     */
    static FeedItem* feedItemFromRaw(RawFeed *raw, qint64 dbId, QObject* parent);
};

#endif // UTILITIES_H
