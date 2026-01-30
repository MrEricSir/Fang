#include "MockNetworkAccessManager.h"
#include <QFile>
#include "FangLogging.h"

MockNetworkReply::MockNetworkReply(const QByteArray& data, const QNetworkRequest& request, QObject* parent,
                                   bool isError, QNetworkReply::NetworkError errorCode,
                                   int delayMs, const QUrl& redirectUrl)
    : QNetworkReply(parent)
    , aborted(false)
{
    QUrl url = request.url();
    setUrl(url);
    setRequest(request);
    setOperation(QNetworkAccessManager::GetOperation);

    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    if (isError) {
        setError(errorCode, "Mock error");
        if (errorCode == QNetworkReply::ContentNotFoundError) {
            setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 404);
        } else if (errorCode == QNetworkReply::InternalServerError) {
            setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 500);
        }
    } else {
        setError(NoError, QString());
        setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 200);
        setHeader(QNetworkRequest::ContentLengthHeader, QVariant(data.size()));
    }

    // Set redirect URL if provided
    if (redirectUrl.isValid()) {
        setAttribute(QNetworkRequest::RedirectionTargetAttribute, redirectUrl);
    }

    setOpenMode(QIODevice::ReadOnly);

    // Emit finished signal asynchronously to simulate network behavior
    // Use configurable delay for timeout testing
    QTimer::singleShot(delayMs, this, &MockNetworkReply::emitFinished);
}

// Backwards-compatible constructor that creates a QNetworkRequest from QUrl
MockNetworkReply::MockNetworkReply(const QByteArray& data, const QUrl& url, QObject* parent,
                                   bool isError, QNetworkReply::NetworkError errorCode,
                                   int delayMs, const QUrl& redirectUrl)
    : QNetworkReply(parent)
    , aborted(false)
{
    setUrl(url);
    setRequest(QNetworkRequest(url));  // Create and set a minimal request
    setOperation(QNetworkAccessManager::GetOperation);

    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    if (isError) {
        setError(errorCode, "Mock error");
        if (errorCode == QNetworkReply::ContentNotFoundError) {
            setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 404);
        } else if (errorCode == QNetworkReply::InternalServerError) {
            setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 500);
        }
    } else {
        setError(NoError, QString());
        setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 200);
        setHeader(QNetworkRequest::ContentLengthHeader, QVariant(data.size()));
    }

    // Set redirect URL if provided
    if (redirectUrl.isValid()) {
        setAttribute(QNetworkRequest::RedirectionTargetAttribute, redirectUrl);
    }

    setOpenMode(QIODevice::ReadOnly);

    // Emit finished signal asynchronously to simulate network behavior
    // Use configurable delay for timeout testing
    QTimer::singleShot(delayMs, this, &MockNetworkReply::emitFinished);
}

void MockNetworkReply::abort()
{
    aborted = true;
    setError(QNetworkReply::OperationCanceledError, "Operation canceled");
    emit errorOccurred(QNetworkReply::OperationCanceledError);
    emit finished();
}

void MockNetworkReply::emitFinished()
{
    if (!aborted) {
        // Emit progress signal first if enabled (simulates download completing)
        emitProgress();
        emit finished();
    }
}

void MockNetworkReply::emitProgress()
{
    if (!aborted) {
        emit downloadProgress(buffer.size(), buffer.size());
    }
}

qint64 MockNetworkReply::bytesAvailable() const
{
    return buffer.bytesAvailable() + QNetworkReply::bytesAvailable();
}

qint64 MockNetworkReply::readData(char* data, qint64 maxSize)
{
    qint64 bytesRead = buffer.read(data, maxSize);
    qCDebug(logMock) << "MockNetworkReply::readData() called for" << url() << "requested:" << maxSize << "read:" << bytesRead << "buffer.bytesAvailable():" << buffer.bytesAvailable();
    return bytesRead;
}

MockNetworkAccessManager::MockNetworkAccessManager(QObject* parent)
    : QNetworkAccessManager(parent)
    , nextError(QNetworkReply::NoError)
    , failuresRemaining(0)
    , shouldFail(false)
    , responseDelayMs(0)
    , emitProgressEnabled(false)
{
}

void MockNetworkAccessManager::addResponse(const QUrl& url, const QByteArray& response)
{
    QString key = url.toString();
    responses[key] = response;
    qCDebug(logMock) << "MockNetworkAccessManager: Added response for" << key;
}

void MockNetworkAccessManager::addResponseFromFile(const QUrl& url, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "MockNetworkAccessManager: Failed to open file" << filePath;
        return;
    }

    QByteArray data = file.readAll();
    qCDebug(logMock) << "MockNetworkAccessManager: Read" << data.size() << "bytes from" << filePath;
    addResponse(url, data);
}

void MockNetworkAccessManager::clear()
{
    responses.clear();
    shouldFail = false;
    failuresRemaining = 0;
}

void MockNetworkAccessManager::setNextError(QNetworkReply::NetworkError errorCode)
{
    nextError = errorCode;
    shouldFail = true;
    failuresRemaining = 1;
}

void MockNetworkAccessManager::setFailureCount(int count, QNetworkReply::NetworkError errorCode)
{
    nextError = errorCode;
    shouldFail = true;
    failuresRemaining = count;
}

void MockNetworkAccessManager::addRedirect(const QUrl& fromUrl, const QUrl& toUrl)
{
    QString key = fromUrl.toString();
    redirects[key] = toUrl;
    qCDebug(logMock) << "MockNetworkAccessManager: Added redirect from" << key << "to" << toUrl.toString();
}

void MockNetworkAccessManager::addErrorResponse(const QUrl& url, QNetworkReply::NetworkError errorCode)
{
    QString key = url.toString();
    urlErrors[key] = errorCode;
    qCDebug(logMock) << "MockNetworkAccessManager: Added error response" << errorCode << "for" << key;
}

void MockNetworkAccessManager::setResponseDelay(int delayMs)
{
    responseDelayMs = delayMs;
    qCDebug(logMock) << "MockNetworkAccessManager: Set response delay to" << delayMs << "ms";
}

void MockNetworkAccessManager::setEmitProgress(bool enabled)
{
    emitProgressEnabled = enabled;
}

QNetworkReply* MockNetworkAccessManager::createRequest(Operation op, const QNetworkRequest& request,
                                                       QIODevice* outgoingData)
{
    Q_UNUSED(outgoingData);

    if (op != GetOperation && op != HeadOperation) {
        qWarning() << "MockNetworkAccessManager: Only GET/HEAD operations are supported";
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }

    QUrl url = request.url();
    QString key = url.toString();

    // Check if we should force a failure (global failure mode)
    if (shouldFail && failuresRemaining > 0) {
        qCDebug(logMock) << "MockNetworkAccessManager: Forcing error" << nextError << "for" << key;
        failuresRemaining--;
        if (failuresRemaining == 0) {
            shouldFail = false;
        }
        return new MockNetworkReply(QByteArray(), request, this, true, nextError, responseDelayMs);
    }

    // Check for URL-specific error
    if (urlErrors.contains(key)) {
        QNetworkReply::NetworkError errorCode = urlErrors[key];
        qCDebug(logMock) << "MockNetworkAccessManager: Returning URL-specific error" << errorCode << "for" << key;
        return new MockNetworkReply(QByteArray(), request, this, true, errorCode, responseDelayMs);
    }

    // Check for redirect
    QUrl redirectUrl;
    if (redirects.contains(key)) {
        redirectUrl = redirects[key];
        qCDebug(logMock) << "MockNetworkAccessManager: Redirecting" << key << "to" << redirectUrl.toString();
    }

    if (responses.contains(key)) {
        qCDebug(logMock) << "MockNetworkAccessManager: Returning mock response for" << key;
        return new MockNetworkReply(responses[key], request, this, false,
                                    QNetworkReply::NoError, responseDelayMs, redirectUrl);
    }

    // If we have a redirect but no response, return empty body with redirect
    if (redirectUrl.isValid()) {
        return new MockNetworkReply(QByteArray(), request, this, false,
                                    QNetworkReply::NoError, responseDelayMs, redirectUrl);
    }

    qWarning() << "MockNetworkAccessManager: No mock response for" << key;
    // Return an error response for unmocked URLs
    return new MockNetworkReply(QByteArray(), request, this, true,
                                QNetworkReply::ContentNotFoundError, responseDelayMs);
}
