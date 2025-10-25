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
    static void addCache(QNetworkAccessManager* manager);
    
    /**
     * @brief Give me a network request, and I'll set it to use the cache.
     * @param request
     */
    static void useCache(QNetworkRequest* request);
    
    /**
     * @brief Adds fake browser headers to make weird web servers happy.
     * @param request
     */
    static void fakeBrowserHeaders(QNetworkRequest* request);

    /**
     * @brief (Attempts to) fix a missing protocol or base URL on a URL.
     */
    static QString urlFixup(const QString& url, QUrl baseURL = QUrl());
};

#endif // NETWORKUTILITIES_H
