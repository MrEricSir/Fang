#include "RawFeedRewriter.h"

#include <QString>
#include <QWebElement>
#include <QDebug>

RawFeedRewriter::RawFeedRewriter(QObject *parent) :
    QObject(parent),
    imageSizer(),
    newsList(NULL)
{
    connect(&imageSizer, SIGNAL(finished()), this, SLOT(onImageSizerFinished()));
}


void RawFeedRewriter::onImageSizerFinished()
{
    QWebElement doc = imageSizer.getDocument();
    if (doc.isNull()) {
        // Nothing was returned, so nothing to do!.
        emit finished();
        
        return;
    }
    
    // Images are done, now it's time to take out the trash!
    for (int i = 0; i < newsList->size(); i++) {
        takeOutTrash(doc.findFirst("#" + elementName(i, true)));
        takeOutTrash(doc.findFirst("#" + elementName(i, false)));
    }
    
    // Build the HTML.
    int i = 0;
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

QString RawFeedRewriter::elementName(int i, bool description)
{
    return "rewriter_" + QString::number(i) + (description ? "_description" : "_content");
}


void RawFeedRewriter::rewrite(QList<RawNews*>* newsList)
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

void RawFeedRewriter::removeAll(const QString& selector, QWebElement element) {
    QWebElementCollection collection = element.findAll(selector);
    foreach (QWebElement e, collection)
        e.removeFromDocument();
}


void RawFeedRewriter::takeOutTrash(QWebElement newsContainer)
{
    // Remove stuff that I really hate.
    removeAll("script", newsContainer); // Javascript
    removeAll("style", newsContainer); // Custom styles.
    removeAll("iframe", newsContainer); // Iframes!
    removeAll("hr", newsContainer); // No horizontals allowed; they're ugly.
    removeAll(".feedflare", newsContainer); // Feedburger's 37 pieces of flare
    removeAll(".mf-viral", newsContainer); // Motherfucking viral?
    removeAll(".service-links-stumbleupon", newsContainer); // StubbleUponYourFace
    
    // Delete annoying images.
    QWebElementCollection collection = newsContainer.findAll("img");
    foreach (QWebElement e, collection) {
        QString parentHref = e.parent().tagName().toLower() == "a" ? e.parent().attribute("href") : "";
        QString src = e.attribute("src");
        QString sWidth = e.attribute("width");
        QString sHeight = e.attribute("height");
        
        bool removeElement = false;
        bool removeParent = false;
        
        // Remove tracking images.
        if (!sWidth.isEmpty() || !sHeight.isEmpty()) {
            int width = sWidth.toInt();
            int height = sWidth.toInt();
            if (width <= 3 && height <= 3)
                removeElement = true;
        }
        
        // Known trackers.
        if (src.contains("feedsportal.com/", Qt::CaseInsensitive))
            removeElement = true;
        
        // Delete social media icons.
        if (!parentHref.isEmpty()) {
            // Social media buttons and trackers.
            if (parentHref.contains("twitter.com/home?status", Qt::CaseInsensitive) ||
                    parentHref.contains("plus.google.com/shar", Qt::CaseInsensitive) ||
                    parentHref.contains("facebook.com/shar", Qt::CaseInsensitive) ||
                    parentHref.contains("feedsportal.com/", Qt::CaseInsensitive) ||
                    parentHref.contains("api.tweetmeme.com/", Qt::CaseInsensitive) ||
                    parentHref.contains("stumbleupon.com/submit", Qt::CaseInsensitive) ||
                    parentHref.contains("share.feedsportal.com/share", Qt::CaseInsensitive)) {
                // Social media buttons.
                removeParent = true;
            } else if (parentHref.length() > 200) {
                // Big links are suspiciously re-direct-y, look for keywords.
                if (parentHref.contains("twitter", Qt::CaseInsensitive) ||
                        parentHref.contains("facebook", Qt::CaseInsensitive) ||
                        parentHref.contains("linkedin", Qt::CaseInsensitive) ||
                        parentHref.contains("plus", Qt::CaseInsensitive) ||
                        parentHref.contains("twitter", Qt::CaseInsensitive) ||
                        parentHref.contains("mail", Qt::CaseInsensitive) ||
                        parentHref.contains("digg", Qt::CaseInsensitive) ||
                        parentHref.contains("social", Qt::CaseInsensitive) ||
                        parentHref.contains("yahoo", Qt::CaseInsensitive)) {
                    removeParent = true;
                }
            }
        }
        
        // Do the deed.
        if (removeParent)
            e.parent().removeFromDocument();
        else if (removeElement)
            e.removeFromDocument();
    }
    
    // Sometimes they throw line breaks at the bottom. Screw 'em.
    while (true) {
        QWebElement last = newsContainer.lastChild();
        QString tag = last.tagName().toLower();
        if (tag == "br" || tag == "hr") {
            last.removeFromDocument();
        } else {
            break; // exit loop
        }
    }
    
    // Almost done -- next steps are recursive.
    visitElement(newsContainer);
}

void RawFeedRewriter::visitElement(const QWebElement &parentElement)
{
    QWebElement e = parentElement.firstChild();
    while (!e.isNull()) {
        // Kiss your Javascript goodbye.
        e.removeAttribute("onload");
        e.removeAttribute("onunload");
        e.removeAttribute("onfocus");
        e.removeAttribute("onclick");
        e.removeAttribute("onmouseover");
        e.removeAttribute("onmouseout");
        e.removeAttribute("onmousedown");
        e.removeAttribute("onmouseup");
        e.removeAttribute("ondblclick");
        e.removeAttribute("onkeydown");
        e.removeAttribute("onkeypress");
        e.removeAttribute("onkeyup");
        e.removeAttribute("onabort");
        e.removeAttribute("onerror");
        e.removeAttribute("onresize");
        e.removeAttribute("onscroll");
        e.removeAttribute("onblur");
        e.removeAttribute("onchange");
        e.removeAttribute("onfocus");
        e.removeAttribute("onreset");
        e.removeAttribute("onselect");
        e.removeAttribute("onsubmit");
        
        // Next!
        visitElement(e);
        e = e.nextSibling();
    }
}
