#include "RawFeedRewriter.h"

#include <QString>
#include <QDomDocument>
#include <QDebug>

// Image width max.
#define MAX_ELEMENT_WIDTH 400

// Strings.
#define S_WIDTH "width"
#define S_HEIGHT "height"
#define S_SRC "src"
#define S_IMG "img"

RawFeedRewriter::RawFeedRewriter(QObject *parent) :
    FangObject(parent),
    webPageGrabber(false),
    imageGrabber(),
    newsList(NULL)
{
    connect(&imageGrabber, SIGNAL(finished()), this, SLOT(onImageGrabberFinished()));

    tagsToRemove << "script"    // Javascript
                 << "title"     // Titles WTF?
                 << "head"      // Don't need head
                 << "style"     // Custom styles.
                 << "iframe"    // Iframes!
                 << "object"    // Plugins!
                 << "embed"     // Other plugins!
                 << "hr";       // No horizontals allowed; they're ugly.

    classesToRemove << "feedflare"                  // Feedburger's 37 pieces of flare
                    << "mf-viral"                   // Motherfucking viral?
                    << "service-links-stumbleupon"; // StubbleUponYourFace

    attributesToRemove << "onload"      // Javascript...
                       << "onunload"
                       << "onfocus"
                       << "onclick"
                       << "onmouseover"
                       << "onmouseout"
                       << "onmousedown"
                       << "onmouseup"
                       << "ondblclick"
                       << "onkeydown"
                       << "onkeypress"
                       << "onkeyup"
                       << "onabort"
                       << "onerror"
                       << "onresize"
                       << "onscroll"
                       << "onblur"
                       << "onchange"
                       << "onfocus"
                       << "onreset"
                       << "onselect"
                       << "onsubmit"    // ...Javascript
                       << "style";      // No custom styles!

    shareButtonURLs << "twitter.com/home?status"
                    << "plus.google.com/shar"
                    << "facebook.com/shar"
                    << "feedsportal.com/"
                    << "api.tweetmeme.com/"
                    << "stumbleupon.com/submit"
                    << "share.feedsportal.com/share";
}

void RawFeedRewriter::rewrite(QList<RawNews *> *newsList)
{
    // Save our news list!</protestChant>
    this->newsList = newsList;

    // Preprocess!
    preProcess();

    QSet<QUrl> imageURLs;

    // Iterate over all the news we have.
    foreach(RawNews* news, *newsList) {
        if (news->content.size()) {
            news->content = rewriteHTML(news->content, imageURLs);
        }

        if (news->description.size()) {
            news->description = rewriteHTML(news->description, imageURLs);
        }
    }

    // No images? We're done, yay!
    if (imageURLs.size() == 0) {
        postProcess(); // Gotta do this, g.
        emit finished();

        return;
    }

    // Do the whole image resizing thang.
    imageGrabber.fetchUrls(QList<QUrl>::fromSet(imageURLs));
}

bool RawFeedRewriter::isHTMLEmpty(QString html)
{
    html.replace(" ", "");
    html.replace("\t", "");
    html.replace("\007", "");

    return html.size() == 0;
}

bool RawFeedRewriter::isShareURL(const QString &url)
{
    foreach (QString shareURL, shareButtonURLs) {
        if (url.contains(shareURL, Qt::CaseInsensitive)) {
            return true;
        }
    }

    return false;
}

void RawFeedRewriter::traverseXmlNode(const QDomNode &node, QSet<QUrl> &imageURLs)
{
    QDomNode domNode = node;
    QDomElement domElement;

    QString lastSibling = "";

    // Loop sibblings at this level.
    while(!(domNode.isNull()))
    {
        QString nodeName = domNode.nodeName();
        //qDebug() << "Node: " << nodeName;
        bool remove = false;
        bool possibleShareButton = false;

        if (domNode.isElement())
        {
            domElement = domNode.toElement();
            if(!(domElement.isNull()))
            {
                // Check tag name.
                if (tagsToRemove.contains(nodeName)) {
                    remove = true;
                }

                // Check attributes.
                if (!remove && domElement.hasAttribute("class")) {
                    foreach(QString c, classesToRemove) {
                        if (domElement.attribute("class") == c) {
                            remove = true;
                            break;
                        }
                    }
                }

                // Delete shady attributes.
                foreach (QString a, attributesToRemove) {
                    domNode.attributes().removeNamedItem(a);
                }

                // Don't allow forced dimensions on non-image tags.
                if (nodeName != S_IMG) {
                    domNode.attributes().removeNamedItem(S_WIDTH);
                    domNode.attributes().removeNamedItem(S_HEIGHT);
                } else if (domNode.attributes().contains(S_WIDTH) || domNode.attributes().contains(S_HEIGHT)) {
                    // For images, if the width or height is too small, remove it.
                    QString sWidth = domNode.attributes().namedItem(S_WIDTH).nodeValue();
                    QString sHeight = domNode.attributes().namedItem(S_HEIGHT).nodeValue();

                    bool widthOK = true;
                    bool heightOK = true;
                    int width = sWidth.toInt(&widthOK);
                    int height = sHeight.toInt(&heightOK);

                    if (!widthOK || !heightOK) {
                        // Remove height and width because it wasn't a pixel value.  But it's OK;
                        // we'll fetch the actual image in these cases.
                        domNode.attributes().removeNamedItem(S_WIDTH);
                        domNode.attributes().removeNamedItem(S_HEIGHT);
                    } else if (width <=3 || height <=3) {
                        // They're too small.
                        remove = true;
                    } else if (width >= MAX_ELEMENT_WIDTH) {
                        // Downscale the image.
                        int newWidth, newHeight;
                        imageResize(width, height, &newWidth, &newHeight);
                        domElement.setAttribute(S_WIDTH, QString::number(newWidth));
                        domElement.setAttribute(S_HEIGHT, QString::number(newHeight));
                    }
                }

                // Always add a left align tag to all images, no matter what!
                if (nodeName == S_IMG) {
                    domElement.setAttribute("align", "left");
                }

                if (!remove && nodeName == S_IMG && domNode.attributes().contains(S_SRC) &&
                        (!domNode.attributes().contains(S_WIDTH) ||
                         !domNode.attributes().contains(S_HEIGHT))) {
                    // Image needs resizer! Put it in the to-resize bucket unless it's a relative
                    // URL, which doesn't belong in a damn RSS feed, kids. Now get off my lawn.
                    QUrl url(domNode.attributes().namedItem(S_SRC).nodeValue());
                    if (url.isValid() && !url.isRelative()) {
                        imageURLs.insert(url);
                    }
                }

                // Check for share button links.  (They'll be removed if they point to an image.)
                if (nodeName == "a" && isShareURL(domNode.attributes().namedItem("href").nodeValue())) {
                    possibleShareButton = true;
                }
            }
        }

        // Remove empty text.
        if (nodeName == "#text" && isHTMLEmpty(domNode.nodeValue())) {
            remove = true;
        }

        // Remove non-breaking spaces.
        // TODO: Replace with a text node?
        if (nodeName == "nbsp") {
            remove = true;
        }

        // Only permit line breaks between text.
        if (lastSibling != "#text" && nodeName == "br") {
            remove = true;
        }

        // Recurse children.
        if (!remove) {
            QDomNode child = domNode.firstChild();
            while(!child.isNull()) {
                // Check for share buttons.
                if (possibleShareButton && child.nodeName() == S_IMG) {
                    remove = true;
                    break;
                }

                // Recurse!
                traverseXmlNode(child, imageURLs);
                child = child.nextSibling();
            }
        }

        // Remove empty containers.
        // (Note: It may not be empty until the above completes.
        if (domNode.childNodes().size() == 0 && (nodeName == "p" || nodeName == "span" || nodeName == "div")) {
            remove = true;
        }

        // Remember what we just saw!
        lastSibling = nodeName;


        QDomNode oldNode = domNode;

        // Continue outter loop.
        domNode = domNode.nextSibling();

        // Remove unwanted node.  We have to do this AFTER advancing the current node (above)
        // in order to process the entire document.
        if (remove) {
            oldNode.parentNode().removeChild(oldNode);
        }
    }
}

QString RawFeedRewriter::rewriteHTML(const QString &input, QSet<QUrl> &imageURLs)
{
    // In this method we use TidyLib via WebPageGrabber to convert the (potentially crappy) HTML
    // into XHTML.  This will add a doctype and other unwanted headers/footers, so we strip those
    // out in a separate post-processing method.

    QDomDocument* doc = webPageGrabber.load(input);
    if (doc == NULL || doc->isNull()) {
        qDebug() << "ERROR!!!!!";
        return "";
    }

    // Sanitize the document.
    traverseXmlNode(*doc, imageURLs);
    QString docString = doc->toString( -1 ); // -1 means no newlines!

    return docString;
}

void RawFeedRewriter::rewriteImages(QString &docString)
{
    QDomDocument doc;
    if (!doc.setContent(docString) || doc.isNull()) {
        qDebug() << "ERROR!!!!!";
        return;
    }

    // Rewrite hte images.
    traveseAndResizeImages(doc);
    docString = doc.toString( -1 ); // -1 means no newlines!
}

void RawFeedRewriter::traveseAndResizeImages(const QDomNode &node)
{
    QDomNode domNode = node;
    QDomElement domElement;

    // Loop sibblings at this level.
    while(!(domNode.isNull()))
    {
        QString nodeName = domNode.nodeName();
        //qDebug() << "Node: " << nodeName;
        bool remove = false;

        if (domNode.isElement())
        {
            domElement = domNode.toElement();
            if(!(domElement.isNull()))
            {
                QString url = domElement.attribute(S_SRC);
                QString sWidth = domElement.attribute(S_WIDTH);

                bool widthOK = true;
                int width = sWidth.toInt(&widthOK);

                QImage image = imageGrabber.getResults()->value(url);

                if (widthOK && width <= MAX_ELEMENT_WIDTH) {
                    // We don't need to do anything!  Yay!
                } else if (nodeName == S_IMG && url.size()) {
                    if (image.isNull()) {
                        // We couldn't fetch this image, so delete it.
                        remove = true;
                    } else {
                        // Resize that baby, yeah!
                        int newWidth, newHeight;
                        imageResize(image.width(), image.height(), &newWidth, &newHeight);

                        domElement.setAttribute(S_WIDTH, QString::number(newWidth));
                        domElement.setAttribute(S_HEIGHT, QString::number(newHeight));
                    }
                }
            }
        }

        // Recurse children.
        if (!remove) {
            QDomNode child = domNode.firstChild();
            while(!child.isNull()) {
                // Recurse!
                traveseAndResizeImages(child);
                child = child.nextSibling();
            }
        }

        QDomNode oldNode = domNode;

        // Continue outter loop.
        domNode = domNode.nextSibling();

        // Remove unwanted node.  We have to do this AFTER advancing the current node (above)
        // in order to process the entire document.
        if (remove) {
            oldNode.parentNode().removeChild(oldNode);
        }
    }
}

void RawFeedRewriter::preProcess()
{
    // Iterate over all the news we have.
    foreach(RawNews* news, *newsList) {
        if (news->content.size()) {
            preProcessDocString(news->content);
        }

        if (news->description.size()) {
            preProcessDocString(news->description);
        }
    }
}

void RawFeedRewriter::postProcess()
{
    // Iterate over all the news we have.
    foreach(RawNews* news, *newsList) {
        if (news->content.size()) {
            postProcessDocString(news->content);
        }

        if (news->description.size()) {
            postProcessDocString(news->description);
        }
    }
}

void RawFeedRewriter::postProcessDocString(QString &docString)
{
    // Rip out headers/footers.
    docString.replace("<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>\n", "");
    docString.replace("<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Strict//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'>", "");
    docString.replace("<html xmlns=\"http://www.w3.org/1999/xhtml\"><body>", "");
    docString.replace("</body></html>", "");
    docString.replace("<html xmlns=\"http://www.w3.org/1999/xhtml\"><body/></html>", ""); // This only happens if there's no content at all.
    docString.replace("&#xd;\n", " "); // I don't know why this happens, but it does.

    // Unbeep our new lines.
    docString.replace("\007", "\n");

    // Sometimes they're newlines, spaces, etc. at the front or end of the string. Kill it.
    docString = docString.trimmed();
}

void RawFeedRewriter::preProcessDocString(QString &docString)
{
    docString.replace("&#07;", ""); // Unbeep
    docString.replace("\r", ""); // Fuck win32
    docString.replace("\n", "&#07;"); // Beep beep!
}

void RawFeedRewriter::imageResize(int width, int height, int *newWidth, int *newHeight)
{
    *newWidth = width;
    *newHeight = height;

    if (width >= MAX_ELEMENT_WIDTH) {
        // Scale down the image.
        *newWidth = MAX_ELEMENT_WIDTH;
        *newHeight = (double) height / (double) width * (double) MAX_ELEMENT_WIDTH;
    }
}

void RawFeedRewriter::onImageGrabberFinished()
{
    // Iterate over all the news... again!
    foreach(RawNews* news, *newsList) {
        if (news->content.size()) {
            rewriteImages(news->content);
        }

        if (news->description.size()) {
            rewriteImages(news->description);
        }
    }

    // We're done! Post-process our XHTML and emit signal.
    postProcess(); // Gotta do this, g.
    emit finished();
}


