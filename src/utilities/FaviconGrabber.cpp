#include "FaviconGrabber.h"
#include "../network/BatchDownloadCore.h"

#include <QString>
#include <QStringList>
#include <QImage>
#include <QXmlStreamReader>

#include "NetworkUtilities.h"
#include "FangLogging.h"

FaviconGrabber::FaviconGrabber(QObject *parent, QNetworkAccessManager* networkManager) :
    FangObject(parent),
    batchDownloader(new BatchDownloadCore(15000, 10, this, networkManager)),
    webGrabber(true, 5000, this, networkManager)
{
    // Set up our state machine.
    machine.addStateChange(START, WEB_GRABBER, [this]() { onWebGrabber(); });
    machine.addStateChange(WEB_GRABBER, CHECK_ICONS, [this]() { onCheckIcons(); });
    machine.addStateChange(CHECK_ICONS, PICK_BEST, [this]() { onPickBest(); });

    machine.addStateChange(-1, GRAB_ERROR, [this]() { onError(); }); // Many errors, one slot.

    // Signals!
    connect(batchDownloader, &BatchDownloadCore::finished, this, &FaviconGrabber::onBatchFinished);
    connect(&webGrabber, &WebPageGrabber::ready, this, &FaviconGrabber::onWebGrabberReady);
}

void FaviconGrabber::find(const QUrl &url)
{
    urlsToCheck.clear();
    imagesToCheck.clear();
    location = url;
    machine.start(START);

    // Make a list of "root" favicons.
    QUrl host = NetworkUtilities::getHost(location);
    const QStringList extensions{"ico", "jpg", "jpeg", "png", "gif"};

    // Add each extension to our list.
    for (const QString& ext : extensions) {
        QUrl toCheck(host);
        toCheck.setPath("/favicon." + ext);
        urlsToCheck << toCheck;
    }

    machine.setState(WEB_GRABBER);
}

void FaviconGrabber::onWebGrabber()
{
    // Check for favicons embedded in the HTML.
    // We look at the main page rather than the feed.
    webGrabber.load(NetworkUtilities::getHost(location));
}

void FaviconGrabber::onCheckIcons()
{
    if (urlsToCheck.isEmpty()) {
        machine.setState(GRAB_ERROR);
        return;
    }

    // Start batch download of all favicon candidates.
    batchDownloader->download(urlsToCheck);
}

void FaviconGrabber::onBatchFinished()
{
    // Ignore if we've moved past CHECK_ICONS state.
    if (machine.getState() != CHECK_ICONS) {
        return;
    }

    // Process batch results.
    QMap<QUrl, BatchDownloadResult> results = batchDownloader->results();

    for (auto it = results.constBegin(); it != results.constEnd(); ++it) {
        const BatchDownloadResult& result = it.value();

        if (result.success && !result.data.isEmpty()) {
            QImage img;
            if (img.loadFromData(result.data)) {
                qCDebug(logFavicon) << "Successfully loaded image:" << img.width() << "x" << img.height();
                imagesToCheck << QPair<QUrl, QImage>(it.key(), img);
            } else {
                qCDebug(logFavicon) << "Failed to load image from data";
            }
        }
    }

    machine.setState(PICK_BEST);
}

void FaviconGrabber::onPickBest()
{
    if (imagesToCheck.isEmpty()) {
        machine.setState(GRAB_ERROR);
        return;
    }

    int topTotalPixels = 0;
    QImage topImage;

    // Go over all the images. Find the one with the max total pixels.
    for (const auto& pair : std::as_const(imagesToCheck)) {
        const QImage& img = pair.second;
        int totalPixels = img.width() * img.height();
        if (totalPixels > topTotalPixels) {
            topTotalPixels = totalPixels;
            topImage = img;
        }
    }

    if (topTotalPixels > 0) {
        QString dataUri = imageToDataUri(topImage);
        if (!dataUri.isEmpty()) {
            emit finished(dataUri);
            return;
        }
    }

    machine.setState(GRAB_ERROR);
}

void FaviconGrabber::onError()
{
    emit finished(QString()); // empty string indicates failure
}

QString FaviconGrabber::imageToDataUri(const QImage& image)
{
    if (image.isNull()) {
        // Not much we can do here.
        return "";
    }

    QImage finalImage = image;

    // Scale down large images. Shouldn't happen, but we want to be defensive.
    if (image.width() > MAX_FAVICON_DIMENSION || image.height() > MAX_FAVICON_DIMENSION) {
        finalImage = image.scaled(MAX_FAVICON_DIMENSION, MAX_FAVICON_DIMENSION,
                                  Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // Convert to PNG and base64 encode.
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    finalImage.save(&buffer, "PNG");

    return "data:image/png;base64," + QString::fromLatin1(imageData.toBase64());
}

void FaviconGrabber::onWebGrabberReady(WebPageGrabber* grabber, QString *document)
{
    Q_UNUSED(grabber);

    // Ignore responses that arrive after we've already moved past WEB_GRABBER state
    // (e.g., multiple async responses from favicon URLs being parsed as HTML)
    if (machine.getState() != WEB_GRABBER) {
        return;
    }

    // Could indicate no internet.
    if (document == nullptr || document->isEmpty()) {
        machine.setState(CHECK_ICONS);

        return;
    }

    findIcons(*document);

    machine.setState(CHECK_ICONS);
}

void FaviconGrabber::findIcons(const QString& document)
{
    // Examples of what we're looking for:
    //     <link rel="apple-touch-icon" href="/apple-touch-icon.png" />
    //     <link rel="icon" href="/favicon.ico" type="image/x-icon" />
    //     <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />

    QXmlStreamReader xml;
    xml.addData(document);

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            QString tagName = xml.name().toString().toLower();
            if (tagName == "body") {
                // We're done with the header, so bail.
                return;
            }

            if (tagName == "link") {
                QXmlStreamAttributes attributes = xml.attributes();
                if (attributes.hasAttribute("rel") && attributes.hasAttribute("href")) {
                    QString rel = attributes.value("", "rel").toString().toLower();
                    if (rel == "apple-touch-icon" || rel == "icon" || rel == "shortcut icon") {
                        urlsToCheck << QUrl(attributes.value("", "href").toString());
                    }
                }
            }
        }
    }
}
