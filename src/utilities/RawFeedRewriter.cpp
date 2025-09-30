#include "RawFeedRewriter.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QString>
#include <QStack>
#include <QDebug>

#include "NetworkUtilities.h"

// Image width max.
#define MAX_ELEMENT_WIDTH 400

// Strings.
#define S_WIDTH "width"
#define S_HEIGHT "height"
#define S_SRC "src"
#define S_IMG "img"
#define S_HREF "href"
#define S_ID "id"

RawFeedRewriter::RawFeedRewriter(QObject *parent) :
    FangObject(parent),
    newsList(NULL),
    webPageGrabber(false),
    imageGrabber(),
    intID(0)
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

    shareButtonURLs << "twitter.com/home?status"
                    << "plus.google.com/shar"
                    << "facebook.com/shar"
                    << "feedsportal.com/"
                    << "api.tweetmeme.com/"
                    << "stumbleupon.com/submit"
                    << "share.feedsportal.com/share";

     containerTags << "p"
                   << "div"
                   << "span"
                   << "pre";
}

void RawFeedRewriter::rewrite(QList<RawNews *> *newsList)
{
    // Save our news list!</protestChant>
    this->newsList = newsList;

    QSet<QUrl> imageURLs;
    idsToDelete.clear();
    intID = 0;

    // Iterate over all the news we have.
    foreach(RawNews* news, *newsList) {
        if (news->content.size()) {
            news->content = rewriteFirstPass(news->content, imageURLs);
        }

        if (news->description.size()) {
            news->description = rewriteFirstPass(news->description, imageURLs);
        }
    }

    // No images? We're done, yay!
    if (imageURLs.size() == 0) {
        // Gotta do this, g.
        rewriteAllSecondPass();
        postProcess();

        emit finished();

        return;
    }

    // Do the whole image resizing thang.
    imageGrabber.fetchUrls(imageURLs.values());
}

bool RawFeedRewriter::isHTMLEmpty(QString html)
{
    html.replace(" ", "");
    html.replace("\t", "");
    html.replace("\n", "");

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

QString RawFeedRewriter::intToID(int id)
{
    return "FangID_" + QString::number(id);
}

QString RawFeedRewriter::rewriteFirstPass(const QString &document, QSet<QUrl> &imageURLs)
{
    // We use TidyLib via WebPageGrabber to convert the (potentially crappy) HTML into proper
    // XHTML.  This will add a doctype and other unwanted headers/footers, so we strip those
    // out in a separate post-processing method.  You'll see.
    QString* doc = webPageGrabber.load("<html><body>" + document + "</body></html>");
    if (doc == NULL) {
        qDebug() << "Error loading HTML document";

        return "";
    }

    // Swap out non-breaking spaces here since QXmlStreamReader doesn't handle them well.
    doc->replace("&nbsp;", " ", Qt::CaseInsensitive);

    // We're going to count the number of tags to determine if this is a real HTML document,
    // or a text document.
    int tagCount = 0;

    QXmlStreamReader xml;
    xml.addData(*doc);

    QString output;
    QXmlStreamWriter writer(&output);
    writer.setAutoFormatting(false);

    // If we're skipping elements, this is >= 1
    int skip = 0;

    // Current stack.
    QStack<DOMNode> stack;

    // Was the last node text?
    bool lastWasText = false;

    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();

        if (xml.isStartElement()) {
            // Start
            tagCount++;

            if (0 == skip) {
                QString tagName = xml.name().toString().toLower();
                QString classValue = xml.attributes().value("class").toString();
                QString href = xml.attributes().value(S_HREF).toString();

                if (tagsToRemove.contains(tagName) ||
                        classesToRemove.contains(classValue) || // Delete known bad classes
                        (tagName == "a" && isShareURL(href)) || // Delete share links
                        (tagName == "br" && !lastWasText)) {    // Delete br's that weren't preceeded by text.
                    // Skip it good!
                    skip = 1;
                } else {
                    // Write the tag.
                    writer.writeStartElement(tagName);

                    intID++;
                    writer.writeAttribute(S_ID, intToID(intID));

                    // If there's a parent node, add a child.
                    if (stack.size()) {
                        stack.top().numChildren++;
                    }

                    // Push it.
                    stack.push(DOMNode(tagName, intID));

                    // Anchor tags.
                    if (tagName == "a" && xml.attributes().hasAttribute(S_HREF)) {
                        writer.writeAttribute(S_HREF, xml.attributes().value(S_HREF).toString());
                    }

                    // Image tags.
                    if (tagName == S_IMG && xml.attributes().hasAttribute(S_SRC)) {
                        QString imgSrc =  NetworkUtilities::urlFixup(xml.attributes().value(S_SRC).toString());
                        writer.writeAttribute(S_SRC, imgSrc);

                        QString sWidth = xml.attributes().value(S_WIDTH).toString();
                        QString sHeight = xml.attributes().value(S_HEIGHT).toString();

                        bool widthOK, heightOK;
                        int width = sWidth.toInt(&widthOK);
                        int height = sHeight.toInt(&heightOK);

                        if (widthOK && heightOK) {
                            if (width < 3 || height < 3) {
                                // Delete tiny images.
                                idsToDelete << intToID(intID);
                            } else {
                                // Resize image if needed.
                                int newWidth, newHeight;
                                imageResize(width, height, &newWidth, &newHeight);
                                writer.writeAttribute(S_WIDTH, QString::number(newWidth));
                                writer.writeAttribute(S_HEIGHT, QString::number(newHeight));
                            }
                        } else {
                            // Dammit, we're gonna have to fetch this image!
                            imageURLs << imgSrc;
                        }
                    }
                }

                lastWasText = false;
            } else {
                 skip++;
            }
        } else if (xml.isEndElement()) {
            QString tagName = xml.name().toString().toLower();

            // End
            if (0 == skip) {
                writer.writeEndElement();

                // Pop our node and investigate.
                DOMNode dom = stack.pop();

                // If it's a container and we didn't write any text, then delete this tag in the
                // second pass.
                if (containerTags.contains(tagName) && dom.nonEmptyTextCount == 0 && dom.numChildren == 0) {
                    //
                    // This doesn't work -- at the very least the IDs are wrong.  We need to
                    // employ a stack here.
                    //
                    idsToDelete << intToID(dom.intID);
                }

                lastWasText = false;
            } else {
                skip--;
            }
        } else if (xml.isCharacters() && 0 == skip) {
            // Text
            QString text = xml.text().toString();
            bool isEmpty = isHTMLEmpty(text);

            // Don't allow pure empty tags, though a single space is ok.
            if (!isEmpty || text == " ") {
                bool addSpaceStart = text.startsWith('\n');
                bool addSpaceEnd = text.endsWith('\n');

                // Text can start or end with a newline -- delete 'em.
                removeNewlinesBothSides(text);

                 // Add back extra spaces so text doesn'truntogether.
                if (addSpaceStart) {
                    text = ' ' + text;
                }

                if (addSpaceEnd) {
                    text = text + ' ';
                }

                // Write the text!
                writer.writeCharacters(text);

                if (!isEmpty) {
                    stack.top().nonEmptyTextCount++;
                }

                lastWasText = true;
            }
        } else if (xml.isEntityReference() && 0 == skip) {
            // Entity
            QString entity = xml.name().toString();
            writer.writeEntityReference(entity);
        } else if (xml.isStartDocument()) {
            // Doc start
            writer.writeStartDocument("1.0");
        } else if (xml.isEndDocument()) {
            // Doc end
            writer.writeEndElement();
        }
    }

    if (xml.hasError()) {
        qDebug() << "Error reading XML: " << xml.errorString();
    }

    if (writer.hasError()) {
        qDebug() << "QXmlStreamWriter had an error of some kind.";
    }


    if (tagCount <= 5 && output !=
            "<?xml version=\"1.0\"?><html id=\"FangID_1\"><body id=\"FangID_2\"/></html>") {
        // Turns out we're not dealing with an HTML document: there's not enough tags, and it's
        // not an empty document (which can be caused by bad HTML.)
        // Ditch the Tidy'd doc and rewrite as plain text from the original.
        return rewriteTextOnlyNews(document);
    }

    // Return new document.
    return output;
}

void RawFeedRewriter::rewriteAllSecondPass()
{
    // Iterate over all the news... again!
    foreach(RawNews* news, *newsList) {
        if (news->content.size()) {
            news->content = rewriteSecondPass(news->content);
        }

        if (news->description.size()) {
            news->description = rewriteSecondPass(news->description);
        }
    }
}

QString RawFeedRewriter::rewriteSecondPass(QString &docString)
{
    //qDebug() << "Second pass: " << docString;

    // If it was a text-only document, we've prepended it with an ASCII beep.  All we have to do
    // here is remove the beep and return it.
    if (docString.startsWith('\07')) {
        return docString.mid(1);
    }

    QXmlStreamReader xml;
    xml.addData(docString);

    QString output;
    QXmlStreamWriter writer(&output);
    writer.setAutoFormatting(false);
    int skip = 0; // Skip stack.
    QString lastTag = "";

    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();

        if (xml.isStartElement()) {
            if (0 == skip) {
                // Start
                QString tagName = xml.name().toString().toLower();
                QString id = xml.attributes().value(S_ID).toString();

                if (idsToDelete.contains(id)) {
                    // We need to delete this tag! Skip it.
                    skip = 1;
                } else if (tagName == S_IMG) {
                    QString url = xml.attributes().value(S_SRC).toString();

                    int width = 0;
                    int height = 0;

                    // We got an image.
                    if (xml.attributes().hasAttribute(S_WIDTH) &&
                            xml.attributes().hasAttribute(S_HEIGHT)) {
                        // Already have attributes?  Cool.
                        width = xml.attributes().value(S_WIDTH).toInt();
                        height = xml.attributes().value(S_HEIGHT).toInt();
                    } else {
                        QImage image = imageGrabber.getResults()->value(url);
                        if (!image.isNull()) {
                            // Resize that baby, yeah!
                            imageResize(image.width(), image.height(), &width, &height);
                        }
                    }

                    if (width > 2 && height > 2) {
                        // Okay, we got a good image and it's not a tracking pixel. Satisfaction!
                        writer.writeStartElement(tagName);
                        writer.writeAttribute(S_SRC, url);
                        writer.writeAttribute(S_WIDTH, QString::number(width));
                        writer.writeAttribute(S_HEIGHT, QString::number(height));
                        writer.writeAttribute("align", "left"); // Always left-align.

                        lastTag = tagName;
                    } else {
                        // Bad image! Skip!
                        skip = 1;
                    }
                } else {
                    // Write the tag and all attributes (except for ID)
                    writer.writeStartElement(tagName);
                    foreach(QXmlStreamAttribute attribute, xml.attributes()) {
                        if (attribute.name().toString() != S_ID) {
                            writer.writeAttribute(attribute);
                        }
                    }

                    lastTag = tagName;
                }
            } else {
                skip++;
            }
        } else if (xml.isEndElement()) {
            // End
            if (0 == skip) {
                writer.writeEndElement();
            } else {
                skip--;
            }
        } else if (xml.isCharacters() && 0 == skip) {
            // Text
            QString text = xml.text().toString();
            if (lastTag != "pre" && lastTag != "code") {
                // This happens due to some kind of auto-formatting glitch.
                text.replace("\n", " ");
            }

            writer.writeCharacters(text);
            lastTag = "#text";
        } else if (xml.isEntityReference() && 0 == skip) {
            // Entity
            QString entity = xml.name().toString();
            writer.writeEntityReference(entity);
            lastTag = "#entity";
        } else if (xml.isStartDocument()) {
            // Doc start
            writer.writeStartDocument(xml.documentVersion().toString());
        } else if (xml.isEndDocument()) {
            // Doc end;xml.documentVersion()
            writer.writeEndElement();
        }
    }

    if (xml.hasError()) {
        qDebug() << "QXmlStreamReader had error: " << xml.errorString();
    }

    if (writer.hasError()) {
        qDebug() << "QXmlStreamWriter had an error of some kind.";
    }

    // Return new document.
    return output;
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
    // The R is for Redundant!
    docString.replace("\r", "");

    // Rip out headers/footers.
    docString.replace("<?xml version=\"1.0\"?><html>", "");
    docString.replace("<body>", "");
    docString.replace("</body></html>", "");
    docString.replace("<body/></html>", ""); // Empty body!

    // This happens.
    docString = docString.trimmed();
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

void RawFeedRewriter::removeNewlinesBothSides(QString &docString)
{
    while (docString.startsWith("\n")) {
        docString = docString.mid(1);
    }

    while (docString.endsWith("\n")) {
        docString = docString.left(docString.length() - 1);
    }
}

QString RawFeedRewriter::rewriteTextOnlyNews(QString input)
{
    QString output;

    // Keep it simple, stupid.
    input = input.trimmed();
    input.replace("\r\n", "\r");
    input.replace("\r", "\n");

    QStringList list = input.split('\n', Qt::SkipEmptyParts);
    foreach(QString line, list) {
        // Trim lines, and skip empty ones.
        QString trimmed = line.trimmed();
        if (!trimmed.isEmpty()) {
            output += "<p>" + trimmed + "</p>";
        }
    }

    // As a signal to the 2nd pass, we prepend the output with an ASCII beep character.  2nd pass
    // will remove this and return the string without further modification.s
    output = '\07' + output;

    return output;
}

void RawFeedRewriter::onImageGrabberFinished()
{
    // Gotta do this, g.
    rewriteAllSecondPass();
    postProcess();

    emit finished();
}
