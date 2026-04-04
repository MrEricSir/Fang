#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QObject>
#include <QFutureWatcher>
#include <QList>
#include <QUrl>
#include <QMap>

#include "ImageData.h"
#include <QObject>

class BatchDownloadCore;
class QNetworkAccessManager;

/*!
    \brief The ImageGrabber attempts to download all images from a list of URLs.

    Uses BatchDownloadCore internally to handle parallel downloads with
    redirect and timeout handling.
 */
class ImageGrabber : public QObject
{
    Q_OBJECT
public:
    explicit ImageGrabber(QObject *parent = nullptr, QNetworkAccessManager* networkManager = nullptr);

signals:
    /*!
        \brief Called when all images are found.
     */
    void finished();

public slots:

    /*!
        \brief Fetch a group of remote images.
        \param urls
     */
    void fetchUrls(const QList<QUrl> &urls);

    /*!
        \brief Fetch a remote image.
        \param url
     */
    void fetchUrl(const QUrl &url);

    inline QMap<QUrl, ImageData>* getResults() { return &results; }

private slots:
    void onBatchFinished();

private:
    BatchDownloadCore* batchDownloader;
    QMap<QUrl, ImageData> results;
    QFutureWatcher<void> processWatcher;
};

#endif // IMAGEGRABBER_H
