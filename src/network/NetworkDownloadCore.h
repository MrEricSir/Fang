#ifndef NETWORKDOWNLOADCORE_H
#define NETWORKDOWNLOADCORE_H

#include <QObject>
#include <QPointer>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QUrl>

#include "../FangObject.h"
#include "NetworkRetryPolicy.h"

/*!
    Config options.
 */
struct NetworkDownloadConfig {
    int timeoutMs = 30000;           // Timeout in milliseconds
    int maxRedirects = 10;           // Maximum number of HTTP redirects to follow
    bool useInactivityTimeout = true; // true = QTimer reset on progress, false = setTransferTimeout
    NetworkRetryPolicy retryPolicy;  // Retry policy (default: no retry for backward compatibility)
};

/*!
`   \brief NetworkDownloadCore is a straightforward, reusable HTTP/HTTPS downloader.

    Features:
      - Redirect handling with configurable limit
      - Cancel after timeout
      - Progress signal
      - Can be used with a mock QNEtworkAccessManager for unit tests
 */
class NetworkDownloadCore : public FangObject
{
    Q_OBJECT
public:
    explicit NetworkDownloadCore(NetworkDownloadConfig config = {},
                                  QObject* parent = nullptr,
                                  QNetworkAccessManager* networkManager = nullptr);
    ~NetworkDownloadCore();

signals:
    /*!
        \brief Signals completion of a download.
        \param url The final URL (may have changed due to redirects)
        \param data The downloaded content
     */
    void finished(const QUrl& url, const QByteArray& data);

    /*!
        \brief Signals an error.
        \param url The URL that failed
        \param errorString Description of the error
     */
    void error(const QUrl& url, const QString& errorString);

    /*!
        \brief Progress indicator. Note that bytesTotal will be -1 if unknown.
     */
    void progress(const QUrl& url, qint64 bytesReceived, qint64 bytesTotal);

    /*!
        \brief Signals when a retry is scheduled.
     */
    void retrying(int attemptNumber, int delayMs);

public slots:
    /*!
        \brief Starts downloading from a URL.
        Notes: URL must be absolute. Calling this function if a download is already in
        progress will cancel that download..
     */
    void download(const QUrl& url);

    /*!
        \brief Cancels the current download. No signal will fire.
     */
    void abort();

private slots:
    void downloadInternal(const QUrl& url);
    void onRequestFinished(QNetworkReply* reply);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onTimeout();
    void onRetryTimer();

private:
    void scheduleRetry();
    void cleanupCurrentReply();

    QPointer<QNetworkAccessManager> manager;
    bool ownsManager;
    NetworkDownloadConfig config;
    QNetworkReply* currentReply;
    QTimer inactivityTimer;
    QTimer retryTimer;
    int redirectCount;
    int currentAttemptCount;
    QUrl originalUrl;  // The URL originally requested (for error reporting)
    QNetworkReply::NetworkError lastError;
    QString lastErrorString;
};

#endif // NETWORKDOWNLOADCORE_H
