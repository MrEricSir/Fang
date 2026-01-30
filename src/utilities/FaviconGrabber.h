#ifndef FAVICONGRABBER_H
#define FAVICONGRABBER_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QPair>
#include <QImage>
#include <QBuffer>

#include <QSimpleStateMachine/QSimpleStateMachine.h>

#include "WebPageGrabber.h"
#include "../FangObject.h"

class BatchDownloadCore;
class QNetworkAccessManager;

// Maximum favicon width and/or height to store.
#define MAX_FAVICON_DIMENSION 512

/*!
   Favicon Grabber attempts to find the best available favicon for a URL.
 */
class FaviconGrabber : public FangObject
{
    Q_OBJECT

private:

    enum FaviconGrabberState {
        START,           // Starts off our list by checking standard /favicon.* urls.
        WEB_GRABBER,     // Checks the webpage for links to favicons.
        CHECK_ICONS,     // Try downloading all of the icons.
        PICK_BEST,       // Determine which icon is best. (Emits finished() signal)
        GRAB_ERROR       // We're done, but there was a problemo.
    };

public:
    explicit FaviconGrabber(QObject *parent = nullptr, QNetworkAccessManager* networkManager = nullptr);

signals:
    /**
     * @brief Called when complete.
     * @param faviconDataUri A data URI containing the favicon as PNG, or empty string on failure.
     */
    void finished(const QString& faviconDataUri);

public slots:

    /**
     * @brief Looks for a favicon for the given URL.
     * @param url
     */
    void find(const QUrl& url);

private slots:

    // WEB_GRABBER
    void onWebGrabber();

    // CHECK_ICONS
    void onCheckIcons();

    // PICK_BEST
    void onPickBest();

    // ERROR
    void onError();

    /**
     * @brief Completion for CHECK_ICONS (from BatchDownloadCore)
     */
    void onBatchFinished();

    /**
     * @brief Completion for WEB_GRABBER
     */
    void onWebGrabberReady(WebPageGrabber* grabber, QString* document);

    // Searches for icons in our XHTML doc.
    void findIcons(const QString& document);

    // Convert a QImage to a PNG data URI, scaling down if needed.
    QString imageToDataUri(const QImage& image);

private:
    QSimpleStateMachine machine;
    QList<QUrl> urlsToCheck;
    QList<QPair<QUrl, QImage>> imagesToCheck;
    BatchDownloadCore* batchDownloader;
    WebPageGrabber webGrabber;
    QUrl location;
};

#endif // FAVICONGRABBER_H
