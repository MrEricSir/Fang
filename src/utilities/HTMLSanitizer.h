#ifndef HTMLSANITIZER_H
#define HTMLSANITIZER_H

#include <QObject>
#include <QSet>
#include <QMap>
#include <QUrl>
#include <QString>

#include "../FangObject.h"
#include "ImageGrabber.h"
#include "WebPageGrabber.h"

/*!
    \brief Represents a DOM node during HTML parsing.
 */
class DOMNode {
public:
    DOMNode(QString tagName, int intID) :
        tagName(tagName),
        intID(intID),
        nonEmptyTextCount(0),
        numChildren(0)
    {}

    // Stack requires a default c'tor
    DOMNode() :
        intID(0),
        nonEmptyTextCount(0),
        numChildren(0)
    {}

    QString tagName;
    int intID;
    int nonEmptyTextCount;
    int numChildren;
};

/*!
    \brief HTMLSanitizer handles HTML cleanup and XHTML conversion.

    This is a synchronous component that:
      - Converts HTML to XHTML via TidyLib
      - Removes unwanted tags (script, style, iframe, etc.)
      - Removes social media share buttons
      - Removes tracking pixels
      - Extracts image URLs that need dimension fetching
      - Handles two-pass processing to remove empty elements
 */
class HTMLSanitizer : public FangObject
{
    Q_OBJECT
public:
    explicit HTMLSanitizer(QObject *parent = nullptr);

    /*!
        \brief First pass: sanitize HTML, returning clean XHTML and extracted image URLs.
        \param html Input HTML
        \param imageURLs [out] URLs of images that need dimension fetching
        \return Sanitized XHTML with FangID attributes for second pass
     */
    QString sanitize(const QString& html, QSet<QUrl>& imageURLs);

    /*!
        \brief Second pass: remove marked elements and apply image data.
        \param html First-pass output
        \param imageResults Map of URL to image data (from ImageGrabber)
        \return Final cleaned HTML
     */
    QString finalize(const QString& html, const QMap<QUrl, ImageData>& imageResults);

    /*!
        \brief Convert text-only content to HTML paragraphs.
        \param text Plain text input
        \return HTML with paragraphs
     */
    QString textToHtml(const QString& text);

    /*!
        \brief Reset state for a new batch of documents.

        Call this before processing a new set of documents to clear
        the idsToDelete set and reset the ID counter.
     */
    void reset();

private:
    WebPageGrabber webPageGrabber;

    // Configuration
    QSet<QString> tagsToRemove;
    QSet<QString> classesToRemove;
    QList<QString> shareButtonURLs;
    QSet<QString> containerTags;

    // State for two-pass processing
    QSet<QString> idsToDelete;
    int currentId;

    // Helpers
    bool isShareURL(const QString& url);
    bool isHTMLEmpty(const QString& html);
    QString intToID(int id);
    void removeNewlinesBothSides(QString& str);
    void imageResize(int width, int height, int* newWidth, int* newHeight);
    QString imageToDataUri(const ImageData& imageData);
    void postProcessDocString(QString& docString);
};

#endif // HTMLSANITIZER_H
