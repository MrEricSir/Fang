#include "ImageGrabber.h"

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QNetworkReply>

ImageGrabber::ImageGrabber(QObject *parent) :
    FangObject(parent),
    manager(),
    urlsToCheck(),
    results()
{
    // Signals!
    connect(&manager, &FangNetworkAccessManager::finished, this, &ImageGrabber::onRequestFinished);
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
    for (QUrl url : urls) {
        checkUrl(url);
    }
}

void ImageGrabber::checkUrl(const QUrl &url)
{
    if (urlsToCheck.contains(url)) {
        return; // Already workin' on this one.
    }
    
    urlsToCheck.append(url);
    
    QNetworkRequest request(url);
    manager.get(request);
}

void ImageGrabber::onRequestFinished(QNetworkReply * reply)
{
    QUrl requestedUrl = reply->request().url();
    Q_ASSERT(urlsToCheck.contains(requestedUrl));

    //
    // TODO: Handle HTTP redirects correctly.
    //
    
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
    if (results.size() != urlsToCheck.size()) {
        return;
    }
    
    // And we're done here!
    emit finished();
}

