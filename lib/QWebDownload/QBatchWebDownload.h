#ifndef QBATCHWEBDOWNLOAD_H
#define QBATCHWEBDOWNLOAD_H

#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QMap>
#include <QList>

#include "QWebDownload.h"

class QNetworkAccessManager;

/*!
    \brief Result of a single download in a batch.
 */
struct BatchWebDownloadResult {
    QByteArray data;        // Downloaded content
    QUrl finalUrl;          // Final URL after redirects
    bool success = false;   // Whether download succeeded
    QString errorString;    // Error message if failed
};

/*!
    \brief QBatchWebDownload downloads multiple URLs in parallel by wrapping QWebDownload.

    Use case: You need to download multiple things and wait for all the results before proceeding.
 */
class QBatchWebDownload : public QObject
{
    Q_OBJECT
public:
    /*!
        \param timeoutMs
        \param maxRedirects
        \param parent
        \param networkManager If specified, caller is responsible for its lifecycle.
     */
    explicit QBatchWebDownload(int timeoutMs = 30000,
                               int maxRedirects = 10,
                               QObject* parent = nullptr,
                               QNetworkAccessManager* networkManager = nullptr);
    virtual ~QBatchWebDownload();

    /*!
        Start downloading a list of URLs, emits finished() when done.
     */
    void get(const QList<QUrl>& urls);

    /*!
        Abort all pending downloads.
     */
    void abort();

    /*!
        Get the results (after finished() is emitted.)
     */
    inline QMap<QUrl, BatchWebDownloadResult> results() const { return _results; }

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
    WebDownloadConfig config;

    int totalCount;
    QMap<QUrl, BatchWebDownloadResult> _results;
    QMap<QWebDownload*, QUrl> downloaders;
};

#endif // QBATCHWEBDOWNLOAD_H
