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
    static FeedItem* feedItemFromRaw(const RawFeed *raw, qint64 dbId, QObject* parent);

    /**
     * @brief Generates a comma separated string list from a vector (no trailing comma)
     * @param input
     * @return
     */
    static QString commaSeparatedStringList(const QVector<qint64> input);
};

#endif // UTILITIES_H
