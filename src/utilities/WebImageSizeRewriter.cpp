#include "WebImageSizeRewriter.h"
#include <QWebFrame>
#include <QWebElement>
#include <QDebug>

WebImageSizeRewriter::WebImageSizeRewriter(int maxWidth, QObject *parent) :
    FangObject(parent),
    maxWidth(maxWidth),
    webGrabber(),
    imageGrabber()
{
    connect(&webGrabber, SIGNAL(ready(QWebPage*)), this, SLOT(onWebGrabberReady(QWebPage*)));
    connect(&imageGrabber, SIGNAL(finished()), this, SLOT(onImageGrabberFinished()));
}

void WebImageSizeRewriter::rewrite(const QString& html)
{
    this->html = html;
    document.removeAllChildren(); // reset doc.
    
    QString header = "<html><body>";
    QString footer = "</body></html>";
    
    webGrabber.load(header + html + footer);
}

QWebElement WebImageSizeRewriter::getDocument()
{
    return document.findFirst("body");
}

void WebImageSizeRewriter::onWebGrabberReady(QWebPage* page)
{
    document = page->mainFrame()->documentElement();
    QWebElementCollection imgs = getImgElementsInNeed();
    
    if (imgs.count() <= 0) {
        // No images, or no images that need dimension attributes.  Either way, we're done!
        emit finished();
        
        return;
    }
    
    // Throw all the elements into a set.
    foreach(QWebElement img, imgs) {
        QString sUrl = img.attribute("src");
        
        imageURLs.insert(QUrl(sUrl));
    }
    
    // Flatten to a list and make the request.
    imageGrabber.fetchUrls(QList<QUrl>::fromSet(imageURLs));
}

QWebElementCollection WebImageSizeRewriter::getImgElementsInNeed()
{
    // This CSS selector grabs all images that have a src tag.
    return document.findAll("img[src]");
}

void WebImageSizeRewriter::onImageGrabberFinished()
{
    foreach(QUrl imageUrl, imageURLs) {
        // Initialize dimension to -1.  If they stay that way, the image is deleted from the HTML.
        int width = -1;
        int height = -1;
        QImage myImage = imageGrabber.getResults()->value(imageUrl, QImage()); // default = null image
        if (!myImage.isNull()) {
            // We got 'em!
            width = myImage.width();
            height = myImage.height();
            
            if (maxWidth > 1 && width > maxWidth) {
                // Scale down the image.
                height = (double) height / (double) width * (double) maxWidth;
                width = maxWidth;
            }
        }
            
        QWebElementCollection elementList = document.findAll("img[src=\"" + imageUrl.toString() + "\"]");
        foreach(QWebElement imageElement, elementList) {
            imageElement.setAttribute("width", QString::number(width));
            imageElement.setAttribute("height", QString::number(height));
        }
    }
    
    html = document.findFirst("body").toInnerXml();
    //qDebug() << "HTML: [[ " << html << " ]]";
    
    emit finished();
}
