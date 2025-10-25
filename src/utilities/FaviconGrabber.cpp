#include "FaviconGrabber.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QImage>
#include <QXmlStreamReader>

#include "NetworkUtilities.h"

FaviconGrabber::FaviconGrabber(QObject *parent) :
    FangObject(parent),
    repliesWaiting(0),
    manager(),
    webGrabber()
{
    // Set up our state machine.
    machine.setReceiver(this);
    
    machine.addStateChange(START, WEB_GRABBER, SLOT(onWebGrabber()));
    machine.addStateChange(WEB_GRABBER, CHECK_ICONS, SLOT(onCheckIcons()));
    machine.addStateChange(CHECK_ICONS, PICK_BEST, SLOT(onPickBest()));
    
    machine.addStateChange(-1, GRAB_ERROR, SLOT(onError())); // Many errors, one slot.
    
    // Signals!
    connect(&manager, &FangNetworkAccessManager::finished, this, &FaviconGrabber::onRequestFinished);
    connect(&webGrabber, &WebPageGrabber::ready, this, &FaviconGrabber::onWebGrabberReady);
}

void FaviconGrabber::find(const QUrl &url)
{
    urlsToCheck.clear();
    location = url;
    machine.start(START);
    
    // Make a list of "root" favicons.
    QUrl host = NetworkUtilities::getHost(location);
    QStringList extensions;
    extensions << "ico" << "jpg" << "jpeg" << "png" << "gif";
    
    // Add each extension to our list.
    foreach(QString ext, extensions) {
        QUrl toCheck(host);
        toCheck.setPath("/favicon." + ext);
        urlsToCheck << toCheck;
    }
    
    machine.setState(WEB_GRABBER);
}

void FaviconGrabber::onWebGrabber()
{
    //qDebug() << "onWebGrabber";
    
    // Check for favicons embedded in the HTML.
    // We look at the main page rather than the feed.
    webGrabber.load(NetworkUtilities::getHost(location));
}

void FaviconGrabber::onCheckIcons()
{
    //qDebug() << "onCheckIcons";
    if (urlsToCheck.size() == 0) {
        machine.setState(GRAB_ERROR);
        
        return;
    }
    
    // Pop each URL off the list and check it, g.
    repliesWaiting = 0;
    while (urlsToCheck.size()) {
        repliesWaiting++;
        
        QUrl url = urlsToCheck.takeFirst();
        
        // If it's not a fully formed URL, fill it out.
        if (url.isValid() && url.isRelative()) {
            QUrl newUrl = location;
            newUrl.setPath(url.path());
            url = newUrl;
        }
        
        QNetworkRequest request(url);
        manager.get(request);
    }
}

void FaviconGrabber::onPickBest()
{
    //qDebug() << "onPickBest";
    if (imagesToCheck.size() == 0) {
        machine.setState(GRAB_ERROR);
        
        return;
    }
    
    int topTotalPixels = 0;
    QImage topImage;
    QUrl topURL;
    
    // Go over all the images.  Find the one with the max total pixels.
    for (int i = 0; i < imagesToCheck.size(); i++) {
        QPair<QUrl, QImage> pair = imagesToCheck.at(i);
        QImage img = pair.second;
        int totalPixels = img.width() * img.height();
        if (totalPixels > topTotalPixels) {
            topTotalPixels = totalPixels;
            topImage = img;
            topURL = pair.first;
        }
    }
    
    if (topTotalPixels) {
        // We got one!
        emit finished(topURL);
        
        return;
    }
    
    machine.setState(GRAB_ERROR);
}

void FaviconGrabber::onError()
{
    //qDebug() << "onError";
    emit finished(QUrl()); // invalid URL
}

void FaviconGrabber::onRequestFinished(QNetworkReply * reply)
{
    //qDebug() << "Checked for a favicon at " << reply->url().toString() << " error: " << reply->errorString();
    
    if (!reply->error()) {
        QImage img;
        
        // Try to determine format from filename.
        
        // Read in the image, if possible.
        if (img.loadFromData(reply->readAll())) {
            imagesToCheck << QPair<QUrl, QImage>(reply->url(), img);
        }
    }
    
    repliesWaiting--;
    if (!repliesWaiting) {
        machine.setState(PICK_BEST);
    }
}

void FaviconGrabber::onWebGrabberReady(QString *document)
{
    // Could indicate no internet.
    if (document == nullptr || document->isEmpty()) {
        machine.setState(CHECK_ICONS);
        
        return;
    }

    findIcons(*document);
    
    machine.setState(CHECK_ICONS);
}

void FaviconGrabber::findIcons(const QString& document)
{
    // Examples of what we're looking for:
    //     <link rel="apple-touch-icon" href="/apple-touch-icon.png" />
    //     <link rel="icon" href="/favicon.ico" type="image/x-icon" />
    //     <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />
    const QString S_REL = "rel";
    const QString S_HREF = "href";

    QXmlStreamReader xml;
    xml.addData(document);

    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();

        if (xml.isStartElement()) {
            QString tagName = xml.name().toString().toLower();
            if (tagName == "body") {
                // We're done with the header, so bail.
                return;
            }

            if (tagName == "link") {
                // This could be a feed...
                QXmlStreamAttributes attributes = xml.attributes();
                if (attributes.hasAttribute(S_REL) && attributes.hasAttribute(S_HREF)) {
                    QString rel = attributes.value("", S_REL).toString().toLower();
                    if (rel == "apple-touch-icon" || rel == "icon" || rel == "shortcut icon") {
                        // We got one!
                        urlsToCheck << QUrl(attributes.value("", S_HREF).toString());
                    }
                }
            }
        }
    }
}
