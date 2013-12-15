#include "FaviconGrabber.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QWebElement>
#include <QWebFrame>

#include "Utilities.h"

FaviconGrabber::FaviconGrabber(QObject *parent) :
    QObject(parent),
    urlsToCheck(0),
    manager(),
    currentReply(NULL),
    results(),
    webGrabber(),
    webGrabberResults()
{
    // Caching!
    Utilities::addNetworkAccessManagerCache(&manager);
    
    // Signals!
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
    connect(&webGrabber, SIGNAL(ready(QWebPage*)), this, SLOT(onWebGrabberReady(QWebPage*)));
}

void FaviconGrabber::find(const QUrl &url)
{
    // Clear both result lists.
    results.clear();
    webGrabberResults.clear();
    
    location = url;
    
    // Check for favicons embedded in the HTML.
    webGrabber.load(url);
    //qDebug() << "Sending url: " << url;
    
    // Check for "root" favicons.
    QUrl host = Utilities::getHost(url);
    
    QStringList extensions;
    extensions << "ico" << "jpg" << "jpeg" << "png" << "gif";
    urlsToCheck = extensions.size() + 1; // The +1 is for the webGrabber above.
    
    // Check each extension.
    foreach(QString ext, extensions) {
        QUrl toCheck(host);
        toCheck.setPath("/favicon." + ext);
        checkUrl(toCheck);
    }
}

void FaviconGrabber::checkUrl(const QUrl &url)
{
    manager.get(QNetworkRequest(url));
}

void FaviconGrabber::onRequestFinished(QNetworkReply * reply)
{
    urlsToCheck--;
    if (!reply->error())
        results.append(QUrl(reply->url()));
    
    checkCompletion();
}

void FaviconGrabber::onWebGrabberReady(QWebPage *page)
{
    urlsToCheck--;
    
    // Could indicate no internet.
    if (page == NULL) {
        checkCompletion();
        
        return;
    }
    
    // Find the first feed URL.
    QWebElement doc = page->mainFrame()->documentElement();
    if (doc.isNull()) {
        checkCompletion();
        
        return;
    }
    
    // Several types of favicon links:
    //     <link rel="apple-touch-icon" href="/apple-touch-icon.png" />
    //     <link rel="icon" href="/favicon.ico" type="image/x-icon" />
    //     <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />
    QWebElement touchIconElement = doc.findFirst("link[rel=apple-touch-icon]");
    QWebElement winMetroIconElement = doc.findFirst("meta[name=msapplication-TileImage]");
    QWebElement iconElement = doc.findFirst("link[rel=icon]");
    QWebElement shortcutIconElement = doc.findFirst("link[rel=shortcut\\ icon]");
    
    // If we got one, set it!
    if (!touchIconElement.isNull() && touchIconElement.hasAttribute("href"))
        webGrabberResults.append(QUrl(touchIconElement.attribute("href")));
    
    if (!winMetroIconElement.isNull() && winMetroIconElement.hasAttribute("content"))
        webGrabberResults.append(QUrl(winMetroIconElement.attribute("content")));
    
    if (!iconElement.isNull() && iconElement.hasAttribute("href"))
        webGrabberResults.append(QUrl(iconElement.attribute("href")));
    
    if (!shortcutIconElement.isNull() && shortcutIconElement.hasAttribute("href"))
        webGrabberResults.append(QUrl(shortcutIconElement.attribute("href")));
    
    checkCompletion();
}

void FaviconGrabber::checkCompletion()
{
    // Only continue if we're done.
    if (urlsToCheck != 0)
        return;
    
    // If we didn't find anything, signal with an invalid URL.
    if (results.size() == 0 && webGrabberResults.size() == 0) {
        emit finished(QUrl());
        
        return;
    }
    
    // Great!  We found a URL.  Give a preference to the HTML version, if available.
    QUrl url;
    if (webGrabberResults.size() > 0)
        url = webGrabberResults.at(0);
    else
        url = results.at(0);
    
    // If we found a relative URL, try to add it as a path to the location.
    if (url.isValid() && url.isRelative()) {
        QUrl newUrl = location;
        newUrl.setPath(url.path());
        url = newUrl;
    }
    
    //qDebug() << "Found favicon: " << url;
    emit finished(url);
}

