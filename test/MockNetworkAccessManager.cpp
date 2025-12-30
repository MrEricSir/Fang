#include "MockNetworkAccessManager.h"
#include <QFile>
#include "FangLogging.h"

MockNetworkReply::MockNetworkReply(const QByteArray& data, const QUrl& url, QObject* parent, bool isError, QNetworkReply::NetworkError errorCode)
    : QNetworkReply(parent)
{
    setUrl(url);
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

    setOpenMode(QIODevice::ReadOnly);

    // Emit finished signal asynchronously to simulate network behavior
    QTimer::singleShot(0, this, &MockNetworkReply::finished);
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

QNetworkReply* MockNetworkAccessManager::createRequest(Operation op, const QNetworkRequest& request,
                                                       QIODevice* outgoingData)
{
    Q_UNUSED(outgoingData);

    if (op != GetOperation) {
        qWarning() << "MockNetworkAccessManager: Only GET operations are supported";
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }

    QUrl url = request.url();
    QString key = url.toString();

    // Check if we should force a failure
    if (shouldFail && failuresRemaining > 0) {
        qCDebug(logMock) << "MockNetworkAccessManager: Forcing error" << nextError << "for" << key;
        failuresRemaining--;
        if (failuresRemaining == 0) {
            shouldFail = false;
        }
        return new MockNetworkReply(QByteArray(), url, this, true, nextError);
    }

    if (responses.contains(key)) {
        qCDebug(logMock) << "MockNetworkAccessManager: Returning mock response for" << key;
        return new MockNetworkReply(responses[key], url, this);
    }

    qWarning() << "MockNetworkAccessManager: No mock response for" << key;
    // Return an error response for unmocked URLs
    return new MockNetworkReply(QByteArray(), url, this, true);
}
