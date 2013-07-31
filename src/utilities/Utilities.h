#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrl>

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
    
    /**
     * @brief Returns just the host for a given URL.
     * @param url
     * @return 
     */
    static QUrl getHost(const QUrl &url);
    
    /**
     * @brief Adds an HTTP cache to a network access manager.
     * @param manager
     */
    static void addNetworkAccessManagerCache(QNetworkAccessManager* manager);
};

#endif // UTILITIES_H
