#include "BatchWebPageGrabber.h"

BatchWebPageGrabber::BatchWebPageGrabber(QObject *parent)
    : FangObject{parent}
{}

void BatchWebPageGrabber::load(const QList<QUrl> &urls)
{
    // Clear any existing grabbers, in case this object is being reused.
    grabbers.clear();

    // Set up grabbers.
    for (const QUrl& url : urls) {
        // Skip this URL if we've already seen it.
        if (grabbers.keys().contains(url)) {
            continue;
        }

        WebPageGrabber *grabber = new WebPageGrabber(this);
        connect(grabber, &WebPageGrabber::ready, this, &BatchWebPageGrabber::onWebGrabberReady);
        grabber->load(url);
        grabbers[url] = grabber;
    }
}

void BatchWebPageGrabber::onWebGrabberReady(WebPageGrabber *grabber, QString *document)
{
    QUrl url = grabber->getOriginalURL();
    if (!grabbers.keys().contains(grabber->getOriginalURL())) {
        qWarning() << "BatchWebPageGrabber: URL returned but not found:" << url;
        // TODO: Should probably timeout or something if this happens.

        return;
    }

    // Insert result.
    results[url] = *document;

    // Check if we're done.
    for (const WebPageGrabber* grabber : grabbers.values()) {
        if (!grabber->isDone()) {
            // Not done yet!
            return;
        }
    }

    // We're done!
    emit ready();
}
