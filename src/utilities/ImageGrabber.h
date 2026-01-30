#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QUrl>
#include <QMap>
#include <QByteArray>

#include "../FangObject.h"

class BatchDownloadCore;
class QNetworkAccessManager;

/*!
    \brief ImageData stores downloaded image data for offline embedding.
 */
struct ImageData {
    QImage image;       // Decoded image
    QByteArray rawData; // Original bytes (for base64 encoding)
    QString mimeType;   // MIME type (jpeg vs png, etc.)

    inline bool isValid() const { return !image.isNull() && !rawData.isEmpty(); }
};

/*!
    \brief The ImageGrabber attempts to download all images from a list of URLs.

    Uses BatchDownloadCore internally to handle parallel downloads with
    redirect and timeout handling.
 */
class ImageGrabber : public FangObject
{
    Q_OBJECT
public:
    explicit ImageGrabber(QObject *parent = nullptr, QNetworkAccessManager* networkManager = nullptr);

signals:
    /**
     * @brief Called when all images are found.
     */
    void finished();

public slots:

    /**
     * @brief Fetch a group of remote images.
     * @param urls
     */
    void fetchUrls(const QList<QUrl> &urls);

    /**
     * @brief Fetch a remote image.
     * @param url
     */
    void fetchUrl(const QUrl &url);

    inline QMap<QUrl, ImageData>* getResults() { return &results; }

private slots:
    void onBatchFinished();

private:
    BatchDownloadCore* batchDownloader;
    QMap<QUrl, ImageData> results;
};

#endif // IMAGEGRABBER_H
