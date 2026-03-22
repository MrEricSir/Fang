#include "HTMLSanitizer.h"
#include "FangLogging.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStack>

#include "ImageCache.h"
#include "NetworkUtilities.h"

// Strings.
#define S_WIDTH "width"
#define S_HEIGHT "height"
#define S_SRC "src"
#define S_IMG "img"
#define S_HREF "href"
#define S_ID "id"

HTMLSanitizer::HTMLSanitizer(QObject *parent) :
    FangObject(parent),
    webPageGrabber(false),
    currentId(0)
{
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

void HTMLSanitizer::reset()
{
    idsToDelete.clear();
    currentId = 0;
}

bool HTMLSanitizer::isHTMLEmpty(const QString& html)
{
    QString copy = html;
    copy.replace(" ", "");
    copy.replace("\t", "");
    copy.replace("\n", "");

    return copy.size() == 0;
}

bool HTMLSanitizer::isShareURL(const QString &url)
{
    for (const QString& shareURL : shareButtonURLs) {
        if (url.contains(shareURL, Qt::CaseInsensitive)) {
            return true;
        }
    }

    return false;
}

QString HTMLSanitizer::intToID(int id)
{
    return "FangID_" + QString::number(id);
}

QString HTMLSanitizer::sanitize(const QString &document, QSet<QUrl> &imageURLs)
{
    // We use TidyLib via WebPageGrabber to convert the (potentially crappy) HTML into proper
    // XHTML.  This will add a doctype and other unwanted headers/footers, so we strip those
    // out in a separate post-processing method.  You'll see.
    QString* doc = webPageGrabber.load("<html><body>" + document + "</body></html>");
    if (doc == nullptr) {
        qCDebug(logRewriter) << "Error loading HTML document";

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

    // Track nesting depth inside <pre> to preserve whitespace.
    int preDepth = 0;

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

                    currentId++;
                    writer.writeAttribute(S_ID, intToID(currentId));

                    // If there's a parent node, add a child.
                    if (stack.size()) {
                        stack.top().numChildren++;
                    }

                    // Push it.
                    stack.push(DOMNode(tagName, currentId));

                    if (tagName == "pre") {
                        preDepth++;
                    }

                    // Anchor tags.
                    if (tagName == "a" && xml.attributes().hasAttribute(S_HREF)) {
                        writer.writeAttribute(S_HREF, xml.attributes().value(S_HREF).toString());
                    }

                    // Image tags.
                    if (tagName == S_IMG && xml.attributes().hasAttribute(S_SRC)) {
                        QString imgSrc = NetworkUtilities::urlFixup(xml.attributes().value(S_SRC).toString());
                        writer.writeAttribute(S_SRC, imgSrc);

                        // Check for tracking pixels using HTML dimensions.
                        QString sWidth = xml.attributes().value(S_WIDTH).toString();
                        QString sHeight = xml.attributes().value(S_HEIGHT).toString();

                        bool widthOK, heightOK;
                        int width = sWidth.toInt(&widthOK);
                        int height = sHeight.toInt(&heightOK);

                        if (widthOK && heightOK) {
                            if (width < 3 || height < 3) {
                                // Delete tiny images (tracking pixels).
                                idsToDelete << intToID(currentId);
                            } else {
                                // Pass dimensions as metadata for finalize() to use
                                // when the image fetch fails and we need to verify
                                // this isn't a tracking pixel.
                                writer.writeAttribute(S_WIDTH, sWidth);
                                writer.writeAttribute(S_HEIGHT, sHeight);
                            }
                        }

                        // Fetch images for caching and dimension verification.
                        if (!idsToDelete.contains(intToID(currentId))) {
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

                if (tagName == "pre") {
                    preDepth--;
                }

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
                if (preDepth == 0) {
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
        qCDebug(logRewriter) << "Error reading XML: " << xml.errorString();
    }

    if (writer.hasError()) {
        qCDebug(logRewriter) << "QXmlStreamWriter had an error of some kind.";
    }


    if (tagCount <= 5 && output !=
            "<?xml version=\"1.0\"?><html id=\"FangID_1\"><body id=\"FangID_2\"/></html>") {
        // Turns out we're not dealing with an HTML document: there's not enough tags, and it's
        // not an empty document (which can be caused by bad HTML.)
        // Ditch the Tidy'd doc and rewrite as plain text from the original.
        return textToHtml(document);
    }

    // Return new document.
    return output;
}

QString HTMLSanitizer::finalize(const QString &html, const QMap<QUrl, ImageData> &imageResults)
{
    // If it was a text-only document, we've prepended it with an ASCII beep.  All we have to do
    // here is remove the beep and return it.
    if (html.startsWith('\07')) {
        return html.mid(1);
    }

    QXmlStreamReader xml;
    xml.addData(html);

    QString output;
    QXmlStreamWriter writer(&output);
    writer.setAutoFormatting(false);
    int skip = 0; // Skip stack.
    int preDepth = 0; // Track nesting depth inside <pre> to preserve whitespace.
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
                    QString srcToUse = url;
                    bool keepImage = false;

                    int width = 0;
                    int height = 0;

                    ImageData imageData = imageResults.value(url);
                    if (imageData.isValid()) {
                        width = imageData.image.width();
                        height = imageData.image.height();

                        if (width > 2 && height > 2) {
                            QString cachedPath = ImageCache::saveImage(url, imageData);
                            if (!cachedPath.isEmpty()) {
                                srcToUse = cachedPath;
                            }
                            keepImage = true;
                        }
                    } else if (xml.attributes().hasAttribute(S_WIDTH) &&
                               xml.attributes().hasAttribute(S_HEIGHT)) {
                        // Fetch failed but image has known good dimensions from
                        // sanitize() - keep it with the original URL.
                        width = xml.attributes().value(S_WIDTH).toInt();
                        height = xml.attributes().value(S_HEIGHT).toInt();
                        keepImage = true;
                    }
                    // else: fetch failed and no known dimensions - skip.
                    // Could be a tracking pixel we can't verify.

                    if (keepImage) {
                        writer.writeStartElement(tagName);
                        writer.writeAttribute(S_SRC, srcToUse);
                        if (width > 0 && height > 0) {
                            writer.writeAttribute(S_WIDTH, QString::number(width));
                            writer.writeAttribute(S_HEIGHT, QString::number(height));
                        }
                        if (srcToUse != url) {
                            writer.writeAttribute("data-original-src", url);
                        }
                        lastTag = tagName;
                    } else {
                        skip = 1;
                    }
                } else {
                    // Write the tag and all attributes (except for ID)
                    writer.writeStartElement(tagName);
                    for (const QXmlStreamAttribute& attribute : xml.attributes()) {
                        if (attribute.name().toString() != S_ID) {
                            writer.writeAttribute(attribute);
                        }
                    }

                    if (tagName == "pre") {
                        preDepth++;
                    }

                    lastTag = tagName;
                }
            } else {
                skip++;
            }
        } else if (xml.isEndElement()) {
            // End
            if (0 == skip) {
                if (xml.name().toString().toLower() == "pre") {
                    preDepth--;
                }
                writer.writeEndElement();
            } else {
                skip--;
            }
        } else if (xml.isCharacters() && 0 == skip) {
            // Text
            QString text = xml.text().toString();
            if (preDepth == 0) {
                // Outside preformatted blocks, collapse newlines to spaces.
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
        qCDebug(logRewriter) << "QXmlStreamReader had error: " << xml.errorString();
    }

    if (writer.hasError()) {
        qCDebug(logRewriter) << "QXmlStreamWriter had an error of some kind.";
    }

    // Post-process and return.
    postProcessDocString(output);
    return output;
}

void HTMLSanitizer::postProcessDocString(QString &docString)
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

void HTMLSanitizer::removeNewlinesBothSides(QString &docString)
{
    while (docString.startsWith("\n")) {
        docString = docString.mid(1);
    }

    while (docString.endsWith("\n")) {
        docString = docString.left(docString.length() - 1);
    }
}

QString HTMLSanitizer::textToHtml(const QString& input)
{
    QString output;

    // Keep it simple, stupid.
    QString cleaned = input.trimmed();
    cleaned.replace("\r\n", "\r");
    cleaned.replace("\r", "\n");

    QStringList list = cleaned.split('\n', Qt::SkipEmptyParts);
    for (const QString& line : list) {
        // Trim lines, and skip empty ones.
        QString trimmed = line.trimmed();
        if (!trimmed.isEmpty()) {
            output += "<p>" + trimmed + "</p>";
        }
    }

    // As a signal to the 2nd pass, we prepend the output with an ASCII beep character.  2nd pass
    // will remove this and return the string without further modification.
    output = '\07' + output;

    return output;
}

