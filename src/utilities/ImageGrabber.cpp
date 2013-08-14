#include "ImageGrabber.h"

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QNetworkReply>

#include "Utilities.h"

ImageGrabber::ImageGrabber(QObject *parent) :
    QObject(parent),
    manager(),
    urlsToCheck(),
    results()
{
    // Caching!
    Utilities::addNetworkAccessManagerCache(&manager);
    
    // Signals!
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
}

void ImageGrabber::fetchUrl(const QUrl &url)
{
    QList<QUrl> urls;
    urls.append(url);
    fetchUrls(urls);
}

void ImageGrabber::fetchUrls(const QList<QUrl> &urls)
{
    // Reset everything.
    results.clear();
    urlsToCheck.clear();
    
    // Do it!
    foreach(QUrl url, urls)
        checkUrl(url);
}

void ImageGrabber::checkUrl(const QUrl &url)
{
    if (urlsToCheck.contains(url))
        return; // Already workin' on this one.
    
    urlsToCheck.append(url);
    manager.get(QNetworkRequest(url));
}

void ImageGrabber::onRequestFinished(QNetworkReply * reply)
{
    QUrl requestedUrl = reply->request().url();
    Q_ASSERT(urlsToCheck.contains(requestedUrl));
    
    // Let's see what we got 'ere.
    if (reply->error() != QNetworkReply::NoError) {
        // Error.
        // Insert an empty image.
        results.insert(requestedUrl, QImage());
    } else {
        // Great success!
        // Got something, maybe it's an image.  Who knows!  More importantly, who cares?
        results.insert(requestedUrl, QImage::fromData(reply->readAll()));
    }
    
    // Are we there yet?
    checkCompletion();
}


void ImageGrabber::checkCompletion()
{
    // Only continue if we're done.
    if (results.size() != urlsToCheck.size())
        return;
    
    // And we're done here!
    emit finished();
}

