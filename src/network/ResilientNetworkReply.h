#ifndef RESILIENTNETWORKREPLY_H
#define RESILIENTNETWORKREPLY_H

#include <QNetworkReply>
#include <QTimer>
#include <QElapsedTimer>
#include "NetworkRetryPolicy.h"

class FangNetworkAccessManager;

/**
 * @brief Wraps a QNetworkReply with timeout/retry logic.
 */
class ResilientNetworkReply : public QObject
{
    Q_OBJECT

public:
    ResilientNetworkReply(FangNetworkAccessManager* manager,
                         const QNetworkRequest& request,
                         QNetworkAccessManager::Operation operation,
                         const NetworkRetryPolicy& policy,
                         QObject* parent = nullptr);

    ~ResilientNetworkReply();

    /**
     * @brief Starts our network request.
     */
    void start();

    /**
     * @brief Aborts our request.
     */
    void abort();

    /**
     * @brief Returns out QNetworkReply.
     */
    QNetworkReply* reply() const { return currentReply; }

    /**
     * @brief Returns the final URL (may have redirected)
     */
    QUrl url() const;

    /**
     * @brief Returns all data received (wait until complete to get all of it)
     */
    QByteArray readAll();

    /**
     * @brief Returns true if request completed without errors.
     */
    bool isSuccess() const { return isSuccessful; }

    /**
     * @brief Returns the last error.
     */
    QNetworkReply::NetworkError error() const { return lastError; }

    /**
     * @brief Returns the error as a string.
     */
    QString errorString() const;

    /**
     * @brief Returns number of attempts made.
     */
    int attemptCount() const { return currentAttemptCount; }

    /**
     * @brief Returns true if data was cached.
     */
    bool isFromCache() const { return fromCache; }

    /**
     * @brief Returns HTTP status code, if available.
     */
    int httpStatusCode() const;

    /**
     * @brief Sets a custom timeout in ms.
     */
    void setTimeout(int timeout);

signals:


    void finished();

    void failed(QNetworkReply::NetworkError error);

    void retrying(int attemptNumber, int delay);

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    void timeout();

private slots:
    void onReplyFinished();
    void onReplyError(QNetworkReply::NetworkError error);
    void onTimeout();
    void onRetryTimerTimeout();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    void executeRequest();
    void scheduleRetry();
    void cleanup();

    FangNetworkAccessManager* networkManager;
    QNetworkRequest networkRequest;
    QNetworkAccessManager::Operation operation;
    NetworkRetryPolicy retryPolicy;

    QNetworkReply* currentReply;
    QByteArray accumulatedData;

    QTimer timeoutTimer;
    QTimer retryTimer;
    QElapsedTimer requestTimer;

    int currentAttemptCount;
    int customTimeout;  // -1 is default
    QNetworkReply::NetworkError lastError;
    QString lastErrorString;
    bool isSuccessful;
    bool fromCache;
    bool aborted;

    // Track errors across all attempts for debugging
    QList<QPair<int, QString>> errorHistory;  // attempt number, error description
};

#endif // RESILIENTNETWORKREPLY_H
