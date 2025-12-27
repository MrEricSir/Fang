#include "MockNetworkAccessManager.h"
#include <QFile>
#include <QDebug>

// MockNetworkReply implementation
MockNetworkReply::MockNetworkReply(const QByteArray& data, const QUrl& url, QObject* parent)
    : QNetworkReply(parent)
{
    setUrl(url);
    setOperation(QNetworkAccessManager::GetOperation);

    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    setError(NoError, QString());
    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 200);

    open(ReadOnly | Unbuffered);

    // Emit finished signal asynchronously to simulate network behavior
    QTimer::singleShot(0, this, &MockNetworkReply::finished);
}

qint64 MockNetworkReply::bytesAvailable() const
{
    return buffer.bytesAvailable() + QNetworkReply::bytesAvailable();
}

qint64 MockNetworkReply::readData(char* data, qint64 maxSize)
{
    return buffer.read(data, maxSize);
}

// MockNetworkAccessManager implementation
MockNetworkAccessManager::MockNetworkAccessManager(QObject* parent)
    : QNetworkAccessManager(parent)
{
}

void MockNetworkAccessManager::addResponse(const QUrl& url, const QByteArray& response)
{
    QString key = url.toString();
    responses[key] = response;
    qDebug() << "MockNetworkAccessManager: Added response for" << key;
}

void MockNetworkAccessManager::addResponseFromFile(const QUrl& url, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "MockNetworkAccessManager: Failed to open file" << filePath;
        return;
    }

    QByteArray data = file.readAll();
    addResponse(url, data);
}

void MockNetworkAccessManager::clear()
{
    responses.clear();
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

    if (responses.contains(key)) {
        qDebug() << "MockNetworkAccessManager: Returning mock response for" << key;
        return new MockNetworkReply(responses[key], url, this);
    }

    qWarning() << "MockNetworkAccessManager: No mock response for" << key;
    // Return an empty response instead of making a real request
    return new MockNetworkReply(QByteArray(), url, this);
}
