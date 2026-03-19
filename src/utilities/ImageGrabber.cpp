#include "ImageGrabber.h"
#include "../network/BatchDownloadCore.h"

#include <QMimeDatabase>
#include <QtConcurrent>

ImageGrabber::ImageGrabber(QObject *parent, QNetworkAccessManager* networkManager) :
    FangObject(parent),
    batchDownloader(new BatchDownloadCore(30000, 10, this, networkManager))
{
    connect(batchDownloader, &BatchDownloadCore::finished,
            this, &ImageGrabber::onBatchFinished);
    connect(&processWatcher, &QFutureWatcher<void>::finished,
            this, &ImageGrabber::finished);
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
    // Capture batch results on the main thread, then process on a background
    // thread to avoid blocking the UI during image decoding and MIME detection.
    QMap<QUrl, BatchDownloadResult> batchResults = batchDownloader->results();

    // Fast path: no images to process.
    if (batchResults.isEmpty()) {
        emit finished();
        return;
    }

    auto future = QtConcurrent::run([this, batchResults]() {
        QMimeDatabase mimeDb;

        for (auto it = batchResults.constBegin(); it != batchResults.constEnd(); ++it) {
            const QUrl& url = it.key();
            const BatchDownloadResult& batchResult = it.value();

            ImageData imageData;

            if (batchResult.success && !batchResult.data.isEmpty()) {
                QImage image = QImage::fromData(batchResult.data);

                if (!image.isNull()) {
                    imageData.image = image;
                    imageData.rawData = batchResult.data;

                    QMimeType mimeType = mimeDb.mimeTypeForData(batchResult.data);
                    imageData.mimeType = mimeType.name();
                }
            }

            results.insert(url, imageData);
        }
    });
    processWatcher.setFuture(future);
}
