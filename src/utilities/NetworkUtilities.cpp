#include "NetworkUtilities.h"

#include <QNetworkDiskCache>
#include <QStandardPaths>


NetworkUtilities::NetworkUtilities()
{
}

QUrl NetworkUtilities::getHost(const QUrl& url) {
    QUrl ret = url;
    ret.setPath("");
    ret.setQuery("");
    QString sUrl = ret.toString();
    if (sUrl.endsWith("?"))
        sUrl = sUrl.remove(sUrl.length() - 1, 1);
    
    ret.setUrl(sUrl);
    return ret;
}

void NetworkUtilities::addCache(QNetworkAccessManager *manager)
{
    // Set default cache dir.
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(manager);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);
    if (!cacheDir.isEmpty())
        manager->setCache(diskCache);
}

void NetworkUtilities::useCache(QNetworkRequest* request)
{
    // This SHOULD be the default, but just in case.
    request->setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                          QNetworkRequest::PreferNetwork);
}

void NetworkUtilities::fakeBrowserHeaders(QNetworkRequest* request)
{
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    request->setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
    // Required for blogs.gnome.org.
    request->setRawHeader("Accept",
                          "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
}

QString NetworkUtilities::urlFixup(const QString &url, QUrl baseURL)
{

    QUrl qURL(url);

    // If the URL is valid and not relative, there's nothing more to do.
    if (!qURL.isRelative() && qURL.isValid()) {
        return url;
    }

    // If the URL is relative, try prepending the base URL.
    if (qURL.isRelative() && !baseURL.isRelative()) {
        QUrl urlRet(baseURL);
        if (url.startsWith("/")) {
            // Absolute path
            urlRet.setPath(url);
        } else {
            // Relative path
            QString urlPath = baseURL.path() + "/" + url; // Build new path
            urlPath = urlPath.replace("//", "/");  // Remove redudant slashes
            urlRet.setPath(urlPath);
        }

        return urlRet.toString();
    }

    // Attempt to correct basic protocol errors.
    if (url.startsWith("//")) {
        // Just assume it's http.
        return "http:" + url;
    } else if (url.startsWith("/")) {
        // Same as above, but we have to add an extra slash.
        return "http:/" + url;
    } else if (url.startsWith(":")) {
        // Starts with a :, assume everything after it is valid.
        return "http" + url;
    }

    if (!url.contains(':') && url.size() && url.at(0).isLetterOrNumber()) {
        // Also assume it's http.
        return "http://" + url;
    }

    // Hopefully it's correct!
    return url;
}
