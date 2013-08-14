#include "RawFeedImageSizeRewriter.h"

#include <QString>
#include <QWebElement>
#include <QDebug>

RawFeedImageSizeRewriter::RawFeedImageSizeRewriter(QObject *parent) :
    QObject(parent),
    imageSizer(),
    newsList(NULL)
{
    connect(&imageSizer, SIGNAL(finished()), this, SLOT(onImageSizerFinished()));
}


void RawFeedImageSizeRewriter::onImageSizerFinished()
{
    QWebElement doc = imageSizer.getDocument();
    if (doc.isNull()) {
        // Nothing was returned, so nothing to do!.
        emit finished();
        
        return;
    }
    
    // Build the HTML.
    int i = 0;
    QString html = "";
    foreach (RawNews* item, *newsList) {
        item->description = doc.findFirst("#" + elementName(i, true)).toInnerXml();
        item->content = doc.findFirst("#" + elementName(i, false)).toInnerXml();
        
        //qDebug();
        //qDebug() << item->description;
        
        i++;
    }
    
    // And we're done!  Yay!
    emit finished();
}

QString RawFeedImageSizeRewriter::elementName(int i, bool description)
{
    return "rewriter_" + QString::number(i) + (description ? "_description" : "_content");
}


void RawFeedImageSizeRewriter::rewrite(QList<RawNews*>* newsList)
{
    this->newsList = newsList;
    if (newsList->size() <= 0) {
        // Nothing to do.
        emit finished();
        
        return;
    }
    
    // Build the HTML.
    int i = 0;
    QString html = "";
    foreach (RawNews* item, *newsList) {
        html += "<div id=\"" + elementName(i, true) + "\">" + item->description + "</div>"
                + "<div id=\"" + elementName(i, false) + "\">" + item->content + "</div>";
        
        i++;
    }
    
    
    imageSizer.rewrite(html);
}
