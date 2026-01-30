#include "RawFeedRewriter.h"

#include <QDebug>

RawFeedRewriter::RawFeedRewriter(QObject *parent) :
    FangObject(parent),
    newsList(nullptr),
    sanitizer(),
    imageGrabber()
{
    connect(&imageGrabber, &ImageGrabber::finished, this, &RawFeedRewriter::onImageGrabberFinished);
}

void RawFeedRewriter::rewrite(QList<RawNews *> *newsList)
{
    this->newsList = newsList;

    // Reset sanitizer state for new batch.
    sanitizer.reset();

    QSet<QUrl> allImageURLs;

    // First pass: sanitize all HTML and collect image URLs.
    for (RawNews* news : *newsList) {
        QSet<QUrl> imageURLs;

        if (!news->content.isEmpty()) {
            news->content = sanitizer.sanitize(news->content, imageURLs);
            allImageURLs.unite(imageURLs);
        }

        if (!news->description.isEmpty()) {
            news->description = sanitizer.sanitize(news->description, imageURLs);
            allImageURLs.unite(imageURLs);
        }
    }

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
    finalizeAll();
    emit finished();
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
    }
}
