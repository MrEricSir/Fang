#include "ImageGrabber.h"
#include "BatchDownloadCore.h"

#include <QMimeDatabase>
#include <QSvgRenderer>
#include <QtConcurrent>

ImageGrabber::ImageGrabber(QObject *parent, QNetworkAccessManager* networkManager) :
    QObject(parent),
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
                QMimeType mimeType = mimeDb.mimeTypeForData(batchResult.data);
                imageData.mimeType = mimeType.name();

                if (mimeType.name() == "image/svg+xml") {
                    // Use QSvgRenderer to get the SVG's logical dimensions.
                    // QImage::fromData() rasterizes SVGs at an arbitrary size
                    // that doesn't reflect their actual width/height.
                    QSvgRenderer renderer(batchResult.data);
                    if (renderer.isValid()) {
                        QSize size = renderer.defaultSize();
                        imageData.image = QImage(size, QImage::Format_ARGB32);
                        imageData.rawData = batchResult.data;
                    }
                } else {
                    QImage image = QImage::fromData(batchResult.data);
                    if (!image.isNull()) {
                        imageData.image = image;
                        imageData.rawData = batchResult.data;
                    }
                }
            }

            results.insert(url, imageData);
        }
    });
    processWatcher.setFuture(future);
}
