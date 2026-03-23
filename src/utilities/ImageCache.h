#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include <QDateTime>
#include <QString>
#include <QUrl>

#include "ImageGrabber.h"

/*!
    \brief Static utility class for storing cached images.

    Images are stored in the system cache directory and served via the local
    WebServer's /images/ route. Original URLs are preserved in a data-original-src
    attribute so images can be re-fetched if the cache gets wiped.
 */
class ImageCache
{
public:
    /*!
        \brief Returns the path to the image cache directory, creating it if needed.
     */
    static QString cacheDir();

    /*!
        \brief Saves image data to disk and returns the server path.
        \param url The original image URL, used for hashing.
        \param imageData The downloaded image data
        \return Web path like "/images/a1b2c3d4.jpeg", or empty string on failure.
     */
    static QString saveImage(const QUrl& url, const ImageData& imageData);

    /*!
        \brief Deletes cached image files older than the given cutoff date.
        \param cutoff Files with modification time before this are deleted.
        \return Number of files deleted.
     */
    static int evictOlderThan(const QDateTime& cutoff);

private:
    static QString hashUrl(const QUrl& url);
    static QString extensionForMimeType(const QString& mimeType);
};

#endif // IMAGECACHE_H
