#include "ImageGrabber.h"
#include "../network/BatchDownloadCore.h"

#include <QMimeDatabase>

ImageGrabber::ImageGrabber(QObject *parent, QNetworkAccessManager* networkManager) :
    FangObject(parent),
    batchDownloader(new BatchDownloadCore(30000, 10, this, networkManager))
{
    connect(batchDownloader, &BatchDownloadCore::finished,
            this, &ImageGrabber::onBatchFinished);
}

void ImageGrabber::fetchUrl(const QUrl &url)
{
    QList<QUrl> urls;
    urls.append(url);
    fetchUrls(urls);
}

void ImageGrabber::fetchUrls(const QList<QUrl> &urls)
{
    results.clear();
    batchDownloader->download(urls);
}

void ImageGrabber::onBatchFinished()
{
    // Convert batch results to results in ImageData format.
    QMap<QUrl, BatchDownloadResult> batchResults = batchDownloader->results();

    for (auto it = batchResults.constBegin(); it != batchResults.constEnd(); ++it) {
        const QUrl& url = it.key();
        const BatchDownloadResult& batchResult = it.value();

        ImageData imageData;

        if (batchResult.success && !batchResult.data.isEmpty()) {
            QImage image = QImage::fromData(batchResult.data);

            if (!image.isNull()) {
                imageData.image = image;
                imageData.rawData = batchResult.data;

                // Detect MIME type from the raw data.
                QMimeDatabase mimeDb;
                QMimeType mimeType = mimeDb.mimeTypeForData(batchResult.data);
                imageData.mimeType = mimeType.name();
            }
        }

        results.insert(url, imageData);
    }

    emit finished();
}
