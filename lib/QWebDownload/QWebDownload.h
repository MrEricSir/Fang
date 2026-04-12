#ifndef QWEBDOWNLOAD_H
#define QWEBDOWNLOAD_H

#include <QObject>
#include <QPointer>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QUrl>

#include "WebRetryPolicy.h"

/*!
    Result of a completed download, including response metadata.
 */
struct WebDownloadResult {
    QUrl url;
    QByteArray data;
    int statusCode = 0;
    bool permanentRedirect = false;
    QNetworkReply::NetworkError networkError = QNetworkReply::NoError;
    QString errorString;

    bool ok() const { return networkError == QNetworkReply::NoError; }
    QByteArray responseHeader(const QByteArray& name) const;

private:
    QList<QPair<QByteArray, QByteArray>> headers;
    friend class QWebDownload;
};

/*!
    Config options.
 */
struct WebDownloadConfig {
    int timeoutMs = 30000;           // Timeout in milliseconds
    int maxRedirects = 10;           // Maximum number of HTTP redirects to follow
    bool useInactivityTimeout = true; // true = QTimer reset on progress, false = setTransferTimeout
    WebRetryPolicy retryPolicy;      // Retry policy (default: no retry for backward compatibility)
};

/*!
    \brief QWebDownload is a straightforward, reusable HTTP/HTTPS downloader.

    Features:
      - Redirect handling with configurable limit
      - Cancel after timeout
      - Progress signal
      - Can be used with a mock QNetworkAccessManager for unit tests
 */
class QWebDownload : public QObject
{
    Q_OBJECT
public:
    explicit QWebDownload(WebDownloadConfig config = {},
                          QObject* parent = nullptr,
                          QNetworkAccessManager* networkManager = nullptr);
    ~QWebDownload();

    void setRequestHeader(const QByteArray& name, const QByteArray& value);
    void clearRequestHeaders();

    QNetworkReply::NetworkError lastNetworkError() const { return lastError; }

signals:
    /*!
        \brief Signals completion of a download.
        \param url The final URL (may have changed due to redirects)
        \param data The downloaded content
     */
    void finished(const QUrl& url, const QByteArray& data);

    /*!
        \brief Signals completion with full result metadata.
     */
    void finishedWithResult(WebDownloadResult result);

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
        \brief Starts an HTTP GET from a URL.
        Notes: URL must be absolute. Calling this function if a download is already in
        progress will cancel that download.
     */
    void get(const QUrl& url);

    /*!
        \brief Cancels the current download. No signal will fire.
     */
    void abort();

private slots:
    void getInternal(const QUrl& url);
    void onRequestFinished(QNetworkReply* reply);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onTimeout();
    void onRetryTimer();

private:
    void scheduleRetry();

    QPointer<QNetworkAccessManager> manager;
    WebDownloadConfig config;
    QNetworkReply* currentReply;
    QTimer inactivityTimer;
    QTimer retryTimer;
    int redirectCount;
    int currentAttemptCount;
    QUrl originalUrl;  // The URL originally requested (for error reporting)
    QNetworkReply::NetworkError lastError;
    QString lastErrorString;
    bool permanentRedirect;
    QList<QPair<QByteArray, QByteArray>> requestHeaders;
};

Q_DECLARE_METATYPE(WebDownloadResult)

#endif // QWEBDOWNLOAD_H
