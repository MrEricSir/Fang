#ifndef NETWORKUTILITIES_H
#define NETWORKUTILITIES_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrl>

class NetworkUtilities
{
public:
    NetworkUtilities();
    
    
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

#endif // NETWORKUTILITIES_H
