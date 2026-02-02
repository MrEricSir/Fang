#ifndef BATCHDOWNLOADCORE_H
#define BATCHDOWNLOADCORE_H

#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QMap>
#include <QList>

#include "../FangObject.h"
#include "NetworkDownloadCore.h"

class QNetworkAccessManager;

/*!
    \brief Result of a single download in a batch.
 */
struct BatchDownloadResult {
    QByteArray data;        // Downloaded content
    QUrl finalUrl;          // Final URL after redirects
    bool success = false;   // Whether download succeeded
    QString errorString;    // Error message if failed
};

/*!
    \brief BatchDownloadCore downloads multiple URLs in parallel by wrapping NetworkDownloadCore.

    Use case: You need to download multiple things and wait for all the results before proeeding.
 */
class BatchDownloadCore : public FangObject
{
    Q_OBJECT
public:
    /*!
        \param timeoutMs
        \param maxRedirects
        \param parent
        \param networkManager If specified, caller is responsible for its lifecycle.
     */
    explicit BatchDownloadCore(int timeoutMs = 30000,
                               int maxRedirects = 10,
                               QObject* parent = nullptr,
                               QNetworkAccessManager* networkManager = nullptr);
    virtual ~BatchDownloadCore();

    /*!
        Start downloading a list of URLs, emits finished() when done.
     */
    void download(const QList<QUrl>& urls);

    /*!
        Abort all pending downloads.
     */
    void abort();

    /*!
        Get the results (after finished() is emitted.)
     */
    inline QMap<QUrl, BatchDownloadResult> results() const { return _results; }

signals:
    /*!
        \brief Emitted when all downloads complete (success or failure).
     */
    void finished();

    /*!
        \brief Emitted as downloads complete to show progress.

        \param completed Number of completed downloads
        \param total Total number of downloads
     */
    void progress(int completed, int total);

private slots:
    void onDownloadFinished(const QUrl& url, const QByteArray& data);
    void onDownloadError(const QUrl& url, const QString& errorString);

private:
    void checkCompletion();

    QNetworkAccessManager* manager;
    NetworkDownloadConfig config;

    int totalCount;
    QMap<QUrl, BatchDownloadResult> _results;
    QMap<NetworkDownloadCore*, QUrl> downloaders;
};

#endif // BATCHDOWNLOADCORE_H
