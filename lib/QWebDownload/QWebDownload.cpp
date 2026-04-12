#include "QWebDownload.h"
#include "WebDownloadLogging.h"

#include <QNetworkAccessManager>

QByteArray WebDownloadResult::responseHeader(const QByteArray& name) const
{
    for (const auto& pair : headers) {
        if (pair.first.toLower() == name.toLower()) {
            return pair.second;
        }
    }
    return QByteArray();
}

QWebDownload::QWebDownload(WebDownloadConfig config,
                           QObject* parent,
                           QNetworkAccessManager* networkManager)
    : QObject(parent)
    , manager(networkManager ? networkManager : new QNetworkAccessManager(this))
    , config(config)
    , currentReply(nullptr)
    , redirectCount(0)
    , currentAttemptCount(0)
    , lastError(QNetworkReply::NoError)
    , permanentRedirect(false)
{
    inactivityTimer.setSingleShot(true);
    retryTimer.setSingleShot(true);

    connect(manager, &QNetworkAccessManager::finished, this, &QWebDownload::onRequestFinished);
    connect(&inactivityTimer, &QTimer::timeout, this, &QWebDownload::onTimeout);
    connect(&retryTimer, &QTimer::timeout, this, &QWebDownload::onRetryTimer);
}

QWebDownload::~QWebDownload()
{
    // Disconnect from manager to avoid receiving signals during destruction. This prevents
    // signals from being emitted on the object as its being destructed.
    if (manager) {
        disconnect(manager, &QNetworkAccessManager::finished, this, &QWebDownload::onRequestFinished);
    }

    retryTimer.stop();

    if (currentReply) {
        currentReply->abort();
        currentReply->deleteLater();
        currentReply = nullptr;
    }
}

void QWebDownload::get(const QUrl& url)
{
    // Reset counters for new download.
    redirectCount = 0;
    currentAttemptCount = 1;  // First attempt
    originalUrl = url;
    lastError = QNetworkReply::NoError;
    lastErrorString.clear();
    permanentRedirect = false;

    // Stop any pending retries.
    retryTimer.stop();

    getInternal(url);
}

void QWebDownload::getInternal(const QUrl& url)
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
        WebDownloadResult result;
        result.url = originalUrl;
        result.networkError = QNetworkReply::ProtocolInvalidOperationError;
        result.errorString = "Relative URLs are not allowed";
        emit finishedWithResult(result);
        emit error(originalUrl, result.errorString);
        return;
    }

    // Create and send request.
    QNetworkRequest request(url);

    // Configure timeout based on mode.
    if (!config.useInactivityTimeout) {
        request.setTransferTimeout(config.timeoutMs);
    }

    // Apply custom request headers.
    for (const auto& header : requestHeaders) {
        request.setRawHeader(header.first, header.second);
    }

    currentReply = manager->get(request);

    // Connect progress signal for inactivity timeout reset.
    if (config.useInactivityTimeout) {
        connect(currentReply, &QNetworkReply::downloadProgress,
                this, &QWebDownload::onDownloadProgress);
        inactivityTimer.start(config.timeoutMs);
    }
}

void QWebDownload::abort()
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

void QWebDownload::onRequestFinished(QNetworkReply* reply)
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
        qCDebug(logWebDownload) << "QWebDownload error:" << lastErrorString;

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
        WebDownloadResult result;
        result.url = originalUrl;
        result.networkError = lastError;
        result.errorString = lastErrorString;
        emit finishedWithResult(result);
        emit error(originalUrl, lastErrorString);
        return;
    }

    // Check for HTTP redirect.
    QVariant redirectVariant = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!redirectVariant.isNull()) {
        if (redirectCount >= config.maxRedirects) {
            currentReply = nullptr;  // Clean up before emitting signal.
            reply->deleteLater();

            WebDownloadResult result;
            result.url = originalUrl;
            result.networkError = QNetworkReply::TooManyRedirectsError;
            result.errorString = "Maximum HTTP redirects exceeded";
            emit finishedWithResult(result);
            emit error(originalUrl, result.errorString);
            return;
        }

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 301 || statusCode == 308) {
            permanentRedirect = true;
        }

        redirectCount++;
        QUrl redirectUrl = redirectVariant.toUrl();

        // Handle relative redirects.
        if (redirectUrl.isRelative()) {
            redirectUrl = reply->url().resolved(redirectUrl);
        }

        getInternal(redirectUrl);
        return;
    }

    // Success!
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QUrl finalUrl = reply->url();
    QByteArray data = reply->readAll();

    // Build result with response metadata.
    WebDownloadResult downloadResult;
    downloadResult.url = finalUrl;
    downloadResult.data = data;
    downloadResult.statusCode = statusCode;
    downloadResult.permanentRedirect = permanentRedirect;
    downloadResult.networkError = QNetworkReply::NoError;

    // Capture response headers.
    for (const auto& headerPair : reply->rawHeaderPairs()) {
        downloadResult.headers.append({headerPair.first, headerPair.second});
    }

    currentReply = nullptr;  // Clean up before emitting signal.
    reply->deleteLater();
    emit finishedWithResult(downloadResult);
    emit finished(finalUrl, data);
}

void QWebDownload::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // Reset inactivity timer on progress.
    inactivityTimer.start(config.timeoutMs);

    // Forward progress signal.
    if (currentReply) {
        emit progress(currentReply->url(), bytesReceived, bytesTotal);
    }
}

void QWebDownload::onTimeout()
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
        WebDownloadResult result;
        result.url = originalUrl;
        result.networkError = lastError;
        result.errorString = lastErrorString;
        emit finishedWithResult(result);
        emit error(originalUrl, lastErrorString);
    }
}

void QWebDownload::setRequestHeader(const QByteArray& name, const QByteArray& value)
{
    requestHeaders.append({name, value});
}

void QWebDownload::clearRequestHeaders()
{
    requestHeaders.clear();
}

void QWebDownload::scheduleRetry()
{
    int delay = config.retryPolicy.calculateDelay(currentAttemptCount);
    qCDebug(logWebDownload) << "QWebDownload: scheduling retry" << (currentAttemptCount + 1)
                        << "in" << delay << "ms for" << originalUrl;
    emit retrying(currentAttemptCount + 1, delay);
    retryTimer.start(delay);
}

void QWebDownload::onRetryTimer()
{
    currentAttemptCount++;
    redirectCount = 0; // Reset redirect count for new attempt.
    getInternal(originalUrl);
}
