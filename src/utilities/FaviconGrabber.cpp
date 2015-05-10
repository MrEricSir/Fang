#include "FaviconGrabber.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QImage>

#include "Utilities.h"
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
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
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

void FaviconGrabber::onWebGrabberReady(QDomDocument *page)
{
    // Could indicate no internet.
    if (page == NULL || page->isNull()) {
        machine.setState(CHECK_ICONS);
        
        return;
    }

    traveseXML(*page);
    
    machine.setState(CHECK_ICONS);
}

void FaviconGrabber::traveseXML(const QDomNode &node)
{
    QDomNode domNode = node;
    QDomElement domElement;

    // Loop sibblings at this level.
    while(!(domNode.isNull()))
    {
        QString nodeName = domNode.nodeName();
        //qDebug() << "Node: " << nodeName;
        //qDebug() << "Value: "  << domNode.nodeValue();

        // Stop condition.
        if (nodeName == "body") {
            // Given that we're only intersted in headers, we can stop when we get to the body node.

            return;
        }

        if (domNode.isElement())
        {
            domElement = domNode.toElement();
            if(!(domElement.isNull()))
            {
                // Examples of what we're looking for:
                //     <link rel="apple-touch-icon" href="/apple-touch-icon.png" />
                //     <link rel="icon" href="/favicon.ico" type="image/x-icon" />
                //     <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />
                if (nodeName == "link" && domElement.hasAttribute("href")) {
                    if (domElement.attribute("rel").toLower() == "apple-touch-icon" ||
                            domElement.attribute("rel").toLower() == "icon" ||
                            domElement.attribute("rel").toLower() == "shortcut icon") {
                        urlsToCheck << QUrl(domElement.attribute("href"));
                    }
                }
            }
        }

        // Recurse children.
        QDomNode child = domNode.firstChild();
        while(!child.isNull()) {
            // Recurse!
            traveseXML(child);
            child = child.nextSibling();
        }

        // Continue outter loop.
        domNode = domNode.nextSibling();
    }
}
