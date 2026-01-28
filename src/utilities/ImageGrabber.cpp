#include "ImageGrabber.h"

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QNetworkReply>
#include <QMimeDatabase>
#include "ErrorHandling.h"

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
    FANG_CHECK(urlsToCheck.contains(requestedUrl), "ImageGrabber: Unexpected URL received");

    //
    // TODO: Handle HTTP redirects correctly.
    //

    ImageData imageData;

    // Let's see what we got 'ere.
    if (reply->error() != QNetworkReply::NoError) {
        // Error: Don't do anything, maybe the image will work later, maybe not. *shrug*
    } else {
        // Great success!
        QByteArray rawData = reply->readAll();
        QImage image = QImage::fromData(rawData);

        if (!image.isNull()) {
            imageData.image = image;
            imageData.rawData = rawData;

            // Detect MIME type from the raw data.
            QMimeDatabase mimeDb;
            QMimeType mimeType = mimeDb.mimeTypeForData(rawData);
            imageData.mimeType = mimeType.name();
        }
    }

    results.insert(requestedUrl, imageData);

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

