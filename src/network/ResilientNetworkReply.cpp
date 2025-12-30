#include "ResilientNetworkReply.h"
#include "FangNetworkAccessManager.h"
#include "../utilities/FangLogging.h"
#include <QDebug>

static const int DEFAULT_TIMEOUT_MS = 30000; // 30 seconds

ResilientNetworkReply::ResilientNetworkReply(FangNetworkAccessManager* manager,
                                             const QNetworkRequest& request,
                                             QNetworkAccessManager::Operation operation,
                                             const NetworkRetryPolicy& policy,
                                             QObject* parent)
    : QObject(parent)
    , networkManager(manager)
    , networkRequest(request)
    , operation(operation)
    , retryPolicy(policy)
    , currentReply(nullptr)
    , currentAttemptCount(0)
    , customTimeout(-1)
    , lastError(QNetworkReply::NoError)
    , isSuccessful(false)
    , fromCache(false)
    , aborted(false)
{
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, &QTimer::timeout, this, &ResilientNetworkReply::onTimeout);

    retryTimer.setSingleShot(true);
    connect(&retryTimer, &QTimer::timeout, this, &ResilientNetworkReply::onRetryTimerTimeout);
}

ResilientNetworkReply::~ResilientNetworkReply()
{
    cleanup();
}

void ResilientNetworkReply::start()
{
    if (aborted) {
        qCWarning(logNetwork) << "Cannot start aborted request";
        return;
    }

    currentAttemptCount = 0;
    errorHistory.clear();
    accumulatedData.clear();
    executeRequest();
}

void ResilientNetworkReply::abort()
{
    aborted = true;
    retryTimer.stop();
    cleanup();
}

void ResilientNetworkReply::setTimeout(int timeout)
{
    customTimeout = timeout;
}

void ResilientNetworkReply::executeRequest()
{
    if (aborted) {
        return;
    }

    currentAttemptCount++;
    requestTimer.start();

    qCDebug(logNetwork) << "Network request attempt" << currentAttemptCount
                        << "for" << networkRequest.url();

    // Clean up previous reply if exists
    cleanup();

    // Create new network request
    switch (operation) {
    case QNetworkAccessManager::GetOperation:
        currentReply = networkManager->get(networkRequest);
        break;
    case QNetworkAccessManager::PostOperation:
        // For POST, would need to handle body data
        qCWarning(logNetwork) << "POST operation not yet implemented in ResilientNetworkReply";
        currentReply = networkManager->get(networkRequest);
        break;
    case QNetworkAccessManager::HeadOperation:
        currentReply = networkManager->head(networkRequest);
        break;
    default:
        qCWarning(logNetwork) << "Unsupported network operation:" << operation;
        currentReply = networkManager->get(networkRequest);
        break;
    }

    if (!currentReply) {
        qCCritical(logNetwork) << "Failed to create network reply";
        emit failed(QNetworkReply::UnknownNetworkError);
        return;
    }

    // Connect signals
    connect(currentReply, &QNetworkReply::finished,
            this, &ResilientNetworkReply::onReplyFinished);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred),
            this, &ResilientNetworkReply::onReplyError);
    connect(currentReply, &QNetworkReply::downloadProgress,
            this, &ResilientNetworkReply::onDownloadProgress);

    // Start timeout.
    int timeout = (customTimeout > 0) ? customTimeout : DEFAULT_TIMEOUT_MS;
    timeoutTimer.start(timeout);

    // Check if cached.
    QVariant fromCache = currentReply->attribute(QNetworkRequest::SourceIsFromCacheAttribute);
    fromCache = fromCache.isValid() && fromCache.toBool();
}

void ResilientNetworkReply::onReplyFinished()
{
    timeoutTimer.stop();

    if (aborted || !currentReply) {
        return;
    }

    qint64 elapsed = requestTimer.elapsed();

    // Check for errors
    QNetworkReply::NetworkError error = currentReply->error();

    if (error == QNetworkReply::NoError) {
        // Yay! Success!
        accumulatedData = currentReply->readAll();
        isSuccessful = true;
        lastError = QNetworkReply::NoError;

        qCDebug(logNetwork) << "Network request succeeded for" << networkRequest.url()
                            << "in" << elapsed << "ms"
                            << "(" << accumulatedData.size() << "bytes)"
                            << "after" << currentAttemptCount << "attempts";

        emit finished();
    } else {
        // Error occurred :(
        onReplyError(error);
    }
}

void ResilientNetworkReply::onReplyError(QNetworkReply::NetworkError error)
{
    timeoutTimer.stop();

    if (aborted) {
        return;
    }

    lastError = error;
    lastErrorString = currentReply ? currentReply->errorString() : "Unknown error";

    // Record error.
    QString errorDesc = QString("Attempt %1: %2 (%3)")
                            .arg(currentAttemptCount)
                            .arg(QVariant::fromValue(error).toString())
                            .arg(lastErrorString);
    errorHistory.append(qMakePair(currentAttemptCount, errorDesc));

    qCWarning(logNetwork) << "Network error for"  << networkRequest.url()
                          << ":" << errorDesc;

    // Check if it's worth retrying.
    if (retryPolicy.shouldRetry(currentAttemptCount) && retryPolicy.isRetryable(error)) {
        scheduleRetry();
    } else {
        // No more retries or error not retryable
        qCWarning(logNetwork) << "Request failed after " << currentAttemptCount << " attempts:"
                              << networkRequest.url();
        qCWarning(logNetwork) << "Error history: ";
        for (const auto& entry : errorHistory) {
            qCWarning(logNetwork) << "  " << entry.second;
        }

        emit failed(error);
    }
}

void ResilientNetworkReply::onTimeout()
{
    if (aborted) {
        return;
    }

    qCWarning(logNetwork) << "Network timeout for" << networkRequest.url()
                          << "after" << requestTimer.elapsed() << "ms";

    // Record timeout.
    errorHistory.append(qMakePair(currentAttemptCount,
                                   QString("Attempt %1: Timeout").arg(currentAttemptCount)));

    // Abort!
    if (currentReply) {
        currentReply->abort();
    }

    lastError = QNetworkReply::TimeoutError;
    lastErrorString = "Request timed out";

    emit timeout();

    // Check if should retry.
    if (retryPolicy.shouldRetry(currentAttemptCount) && retryPolicy.isRetryable(QNetworkReply::TimeoutError)) {
        scheduleRetry();
    } else {
        qCWarning(logNetwork) << "Request timed out after " << currentAttemptCount << " attempts";
        emit failed(QNetworkReply::TimeoutError);
    }
}

void ResilientNetworkReply::scheduleRetry()
{
    int delay = retryPolicy.calculateDelay(currentAttemptCount);

    qCInfo(logNetwork) << "Scheduling retry " << (currentAttemptCount + 1)
                       << "for " << networkRequest.url()
                       << "in " << delay << " ms";

    emit retrying(currentAttemptCount + 1, delay);

    retryTimer.start(delay);
}

void ResilientNetworkReply::onRetryTimerTimeout()
{
    if (aborted) {
        return;
    }

    executeRequest();
}

void ResilientNetworkReply::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // Reset timeout if the download is progressing slowly (slow connection, large file, etc.)
    if (bytesReceived > 0) {
        int timeout = (customTimeout > 0) ? customTimeout : DEFAULT_TIMEOUT_MS;
        timeoutTimer.start(timeout);
    }

    emit downloadProgress(bytesReceived, bytesTotal);
}

void ResilientNetworkReply::cleanup()
{
    timeoutTimer.stop();

    if (currentReply) {
        currentReply->disconnect(this);
        if (currentReply->isRunning()) {
            currentReply->abort();
        }
        currentReply->deleteLater();
        currentReply = nullptr;
    }
}

QUrl ResilientNetworkReply::url() const
{
    if (currentReply) {
        return currentReply->url();
    }
    return networkRequest.url();
}

QByteArray ResilientNetworkReply::readAll()
{
    return accumulatedData;
}

QString ResilientNetworkReply::errorString() const
{
    if (!lastErrorString.isEmpty()) {
        return lastErrorString;
    }
    if (currentReply) {
        return currentReply->errorString();
    }
    return QString();
}

int ResilientNetworkReply::httpStatusCode() const
{
    if (currentReply) {
        return currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    }
    return 0;
}
