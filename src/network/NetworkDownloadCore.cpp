#include "NetworkDownloadCore.h"
#include "FangNetworkAccessManager.h"

#include "../utilities/FangLogging.h"

NetworkDownloadCore::NetworkDownloadCore(NetworkDownloadConfig config,
                                          QObject* parent,
                                          QNetworkAccessManager* networkManager)
    : FangObject(parent)
    , manager(networkManager ? networkManager : new FangNetworkAccessManager(this))
    , ownsManager(networkManager == nullptr)
    , config(config)
    , currentReply(nullptr)
    , redirectCount(0)
    , currentAttemptCount(0)
    , lastError(QNetworkReply::NoError)
{
    inactivityTimer.setSingleShot(true);
    retryTimer.setSingleShot(true);

    connect(manager, &QNetworkAccessManager::finished, this, &NetworkDownloadCore::onRequestFinished);
    connect(&inactivityTimer, &QTimer::timeout, this, &NetworkDownloadCore::onTimeout);
    connect(&retryTimer, &QTimer::timeout, this, &NetworkDownloadCore::onRetryTimer);
}

NetworkDownloadCore::~NetworkDownloadCore()
{
    // Disconnect from manager to avoid receiving signals during destruction. This prevents
    // signals from being emitted on the object as its being destructed.
    if (manager) {
        disconnect(manager, &QNetworkAccessManager::finished, this, &NetworkDownloadCore::onRequestFinished);
    }

    retryTimer.stop();

    if (currentReply) {
        currentReply->abort();
        currentReply->deleteLater();
        currentReply = nullptr;
    }
}

void NetworkDownloadCore::download(const QUrl& url)
{
    // Reset counters for new download.
    redirectCount = 0;
    currentAttemptCount = 1;  // First attempt
    originalUrl = url;
    lastError = QNetworkReply::NoError;
    lastErrorString.clear();

    // Stop any pending retries.
    retryTimer.stop();

    downloadInternal(url);
}

void NetworkDownloadCore::downloadInternal(const QUrl& url)
{
    // Clean up existing reply if needed.
    if (currentReply) {
        // Clear currentReply BEFORE aborting to prevent onRequestFinished from processing.
        QNetworkReply* oldReply = currentReply;
        currentReply = nullptr;
        oldReply->disconnect(this);
        oldReply->abort();
        oldReply->deleteLater();
    }

    // Stop any existing timer.
    inactivityTimer.stop();

    // Validate URL.
    if (url.isRelative()) {
        emit error(originalUrl, "Relative URLs are not allowed");
        return;
    }

    // Create and send request.
    QNetworkRequest request(url);

    // Configure timeout based on mode.
    if (!config.useInactivityTimeout) {
        request.setTransferTimeout(config.timeoutMs);
    }

    currentReply = manager->get(request);

    // Connect progress signal for inactivity timeout reset.
    if (config.useInactivityTimeout) {
        connect(currentReply, &QNetworkReply::downloadProgress,
                this, &NetworkDownloadCore::onDownloadProgress);
        inactivityTimer.start(config.timeoutMs);
    }
}

void NetworkDownloadCore::abort()
{
    inactivityTimer.stop();
    retryTimer.stop();

    if (currentReply) {
        // Clear currentReply BEFORE aborting to prevent onRequestFinished from processing.
        QNetworkReply* reply = currentReply;
        currentReply = nullptr;

        reply->abort();
        reply->deleteLater();
    }
}

void NetworkDownloadCore::onRequestFinished(QNetworkReply* reply)
{
    // Sanity check: Only process *our* reply.
    if (reply != currentReply) {
        return;
    }

    inactivityTimer.stop();

    // Check for network errors.
    if (reply->error() != QNetworkReply::NoError) {
        lastError = reply->error();
        lastErrorString = reply->errorString();
        qCDebug(logNetwork) << "NetworkDownloadCore error:" << lastErrorString;

        // Clean up the reply.
        currentReply = nullptr;
        reply->deleteLater();

        // Check if we should retry.
        if (config.retryPolicy.shouldRetry(currentAttemptCount) &&
            config.retryPolicy.isRetryable(lastError)) {
            scheduleRetry();
            return;
        }

        // No more retries - emit error.
        emit error(originalUrl, lastErrorString);
        return;
    }

    // Check for HTTP redirect.
    QVariant redirectVariant = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!redirectVariant.isNull()) {
        if (redirectCount >= config.maxRedirects) {
            currentReply = nullptr;  // Clean up before emitting signal.
            reply->deleteLater();
            emit error(originalUrl, "Maximum HTTP redirects exceeded");
            return;
        }

        redirectCount++;
        QUrl redirectUrl = redirectVariant.toUrl();

        // Handle relative redirects.
        if (redirectUrl.isRelative()) {
            redirectUrl = reply->url().resolved(redirectUrl);
        }

        downloadInternal(redirectUrl);
        return;
    }

    // Success!
    QUrl finalUrl = reply->url();
    QByteArray data = reply->readAll();
    currentReply = nullptr;  // Clean up before emitting signal.
    reply->deleteLater();
    emit finished(finalUrl, data);
}

void NetworkDownloadCore::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // Reset inactivity timer on progress.
    inactivityTimer.start(config.timeoutMs);

    // Forward progress signal.
    if (currentReply) {
        emit progress(currentReply->url(), bytesReceived, bytesTotal);
    }
}

void NetworkDownloadCore::onTimeout()
{
    if (currentReply) {
        // Clear currentReply BEFORE aborting to prevent onRequestFinished from processing.
        QNetworkReply* reply = currentReply;
        currentReply = nullptr;

        reply->abort();
        reply->deleteLater();

        lastError = QNetworkReply::TimeoutError;
        lastErrorString = "Download timeout";

        // Check if we should retry.
        if (config.retryPolicy.shouldRetry(currentAttemptCount) &&
            config.retryPolicy.isRetryable(lastError)) {
            scheduleRetry();
            return;
        }

        // No more retries - emit error.
        emit error(originalUrl, lastErrorString);
    }
}

void NetworkDownloadCore::scheduleRetry()
{
    int delay = config.retryPolicy.calculateDelay(currentAttemptCount);
    qCDebug(logNetwork) << "NetworkDownloadCore: scheduling retry" << (currentAttemptCount + 1)
                        << "in" << delay << "ms for" << originalUrl;
    emit retrying(currentAttemptCount + 1, delay);
    retryTimer.start(delay);
}

void NetworkDownloadCore::onRetryTimer()
{
    currentAttemptCount++;
    redirectCount = 0; // Reset redirect count for new attempt.
    downloadInternal(originalUrl);
}
