#include "RawFeedRewriter.h"

#include <QDebug>
#include <QtConcurrent>

#include "ImageCache.h"

RawFeedRewriter::RawFeedRewriter(QObject *parent, QNetworkAccessManager* networkManager) :
    FangObject(parent),
    newsList(nullptr),
    sanitizer(),
    imageGrabber(nullptr, networkManager)
{
    connect(&imageGrabber, &ImageGrabber::finished, this, &RawFeedRewriter::onImageGrabberFinished);
    connect(&sanitizeWatcher, &QFutureWatcher<QSet<QUrl>>::finished, this, &RawFeedRewriter::onSanitizeFinished);
    connect(&finalizeWatcher, &QFutureWatcher<void>::finished, this, [this]() { emit finished(); });
}

void RawFeedRewriter::rewrite(QList<RawNews *> *newsList)
{
    this->newsList = newsList;

    // Reset sanitizer state for new batch.
    sanitizer.reset();

    // First pass: sanitize all HTML and collect image URLs.
    // Run on a background thread to avoid blocking the UI.
    auto future = QtConcurrent::run([this]() -> QSet<QUrl> {
        QSet<QUrl> allImageURLs;

        for (RawNews* news : *this->newsList) {
            QSet<QUrl> imageURLs;

            if (!news->content.isEmpty()) {
                news->content = sanitizer.sanitize(news->content, imageURLs);
                allImageURLs.unite(imageURLs);
            }

            if (!news->description.isEmpty()) {
                news->description = sanitizer.sanitize(news->description, imageURLs);
                allImageURLs.unite(imageURLs);
            }

            // Include media image URLs for downloading and caching.
            if (!news->mediaImageURL.isEmpty()) {
                allImageURLs.insert(QUrl(news->mediaImageURL));
            }
        }

        return allImageURLs;
    });
    sanitizeWatcher.setFuture(future);
}

void RawFeedRewriter::onSanitizeFinished()
{
    QSet<QUrl> allImageURLs = sanitizeWatcher.result();

    // No images? Finalize and we're done.
    if (allImageURLs.isEmpty()) {
        finalizeAll();
        emit finished();
        return;
    }

    // Fetch images, then finalize when done.
    imageGrabber.fetchUrls(allImageURLs.values());
}

void RawFeedRewriter::onImageGrabberFinished()
{
    // Run finalization on a background thread to avoid blocking the UI
    // during XML parsing and image caching.
    auto future = QtConcurrent::run([this]() {
        finalizeAll();
    });
    finalizeWatcher.setFuture(future);
}

void RawFeedRewriter::finalizeAll()
{
    QMap<QUrl, ImageData> imageResults = *imageGrabber.getResults();

    for (RawNews* news : *newsList) {
        if (!news->content.isEmpty()) {
            news->content = sanitizer.finalize(news->content, imageResults);
        }

        if (!news->description.isEmpty()) {
            news->description = sanitizer.finalize(news->description, imageResults);
        }

        // Cache media image and store cached path.
        if (!news->mediaImageURL.isEmpty()) {
            QUrl mediaUrl(news->mediaImageURL);
            if (imageResults.contains(mediaUrl)) {
                QString cachedPath = ImageCache::saveImage(mediaUrl, imageResults.value(mediaUrl));
                news->mediaImageURL = cachedPath;
            } else {
                news->mediaImageURL = "";
            }
        }
    }
}
