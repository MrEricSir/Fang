#ifndef HTMLSANITIZER_H
#define HTMLSANITIZER_H

#include <QObject>
#include <QSet>
#include <QMap>
#include <QUrl>
#include <QString>
#include <functional>

#include "ImageGrabber.h"

/*!
    \brief Fang HTML sanitizer.

    First pass: converts untrusted HTML into clean XHTML via TidyLib, then
    applies configurable tag, class, and URL-pattern filtering.

    Second pass (finalize): removes marked elements and applies image data
    from ImageGrabber, caching images via QImageCache.
 */
class HTMLSanitizer : public QObject
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
    // Configuration (initialized in constructor)
    QSet<QString> tagsToRemove;
    QSet<QString> classesToRemove;
    QList<QString> shareButtonURLs;
    QSet<QString> containerTags;
    std::function<QString(const QString&)> urlTransform;

    // Two-pass state
    QSet<QString> idsToDelete;
    int currentId;

    // Helpers
    bool isShareURL(const QString& url);
    bool isHTMLEmpty(const QString& html);
    QString intToID(int id);
    void removeNewlinesBothSides(QString& str);
    void postProcessDocString(QString& docString);
};

#endif // HTMLSANITIZER_H
