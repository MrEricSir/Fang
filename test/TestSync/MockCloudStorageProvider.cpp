#include "MockCloudStorageProvider.h"

#include <QUuid>

MockCloudStorageProvider::MockCloudStorageProvider(QObject *parent)
    : CloudStorageProvider(parent)
{
}

bool MockCloudStorageProvider::isAuthenticated() const
{
    return m_authenticated;
}

void MockCloudStorageProvider::authenticate()
{
    m_operationCount++;

    scheduleCallback([this]() {
        if (m_authWillSucceed) {
            m_authenticated = true;
            emit authenticated();
        } else {
            emit authenticationFailed("Authentication failed (simulated)");
        }
    });
}

void MockCloudStorageProvider::signOut()
{
    m_operationCount++;
    m_authenticated = false;

    scheduleCallback([this]() {
        emit signedOut();
    });
}

void MockCloudStorageProvider::getFileMetadata(const QString& fileName)
{
    m_operationCount++;

    scheduleCallback([this, fileName]() {
        OperationResult result;

        if (m_nextOpWillFail) {
            m_nextOpWillFail = false;
            result.success = false;
            result.errorMessage = m_nextOpError;
            emit metadataReceived(fileName, result);
            return;
        }

        if (m_files.contains(fileName)) {
            const StoredFile& file = m_files[fileName];
            result.success = true;
            result.metadata.fileId = fileName;
            result.metadata.name = fileName;
            result.metadata.etag = file.etag;
            result.metadata.size = file.data.size();
            result.metadata.modifiedTime = file.modifiedTime;
            result.metadata.exists = true;
        } else {
            result.success = true;
            result.metadata.exists = false;
        }

        emit metadataReceived(fileName, result);
    });
}

void MockCloudStorageProvider::downloadFile(const QString& fileName)
{
    m_operationCount++;

    scheduleCallback([this, fileName]() {
        OperationResult result;

        if (m_nextOpWillFail) {
            m_nextOpWillFail = false;
            result.success = false;
            result.errorMessage = m_nextOpError;
            emit fileDownloaded(fileName, result);
            return;
        }

        if (m_files.contains(fileName)) {
            const StoredFile& file = m_files[fileName];
            result.success = true;
            result.data = file.data;
            result.metadata.fileId = fileName;
            result.metadata.name = fileName;
            result.metadata.etag = file.etag;
            result.metadata.size = file.data.size();
            result.metadata.modifiedTime = file.modifiedTime;
            result.metadata.exists = true;
        } else {
            result.success = false;
            result.errorMessage = "File not found";
        }

        emit fileDownloaded(fileName, result);
    });
}

void MockCloudStorageProvider::uploadFile(const QString& fileName,
                                          const QByteArray& data,
                                          const QString& expectedEtag)
{
    m_operationCount++;

    scheduleCallback([this, fileName, data, expectedEtag]() {
        OperationResult result;

        if (m_nextOpWillFail) {
            m_nextOpWillFail = false;
            result.success = false;
            result.errorMessage = m_nextOpError;
            emit fileUploaded(fileName, result);
            return;
        }

        // Check for conflict (ETag mismatch)
        if (!expectedEtag.isEmpty() && m_files.contains(fileName)) {
            const StoredFile& existing = m_files[fileName];
            if (existing.etag != expectedEtag) {
                // Conflict detected
                FileMetadata serverMeta;
                serverMeta.fileId = fileName;
                serverMeta.name = fileName;
                serverMeta.etag = existing.etag;
                serverMeta.size = existing.data.size();
                serverMeta.modifiedTime = existing.modifiedTime;
                serverMeta.exists = true;

                emit conflictDetected(fileName, serverMeta);
                return;
            }
        }

        // Store the file
        StoredFile file;
        file.data = data;
        file.etag = generateEtag();
        file.modifiedTime = QDateTime::currentDateTimeUtc();
        m_files[fileName] = file;

        result.success = true;
        result.metadata.fileId = fileName;
        result.metadata.name = fileName;
        result.metadata.etag = file.etag;
        result.metadata.size = file.data.size();
        result.metadata.modifiedTime = file.modifiedTime;
        result.metadata.exists = true;

        emit fileUploaded(fileName, result);
    });
}

void MockCloudStorageProvider::deleteFile(const QString& fileName)
{
    m_operationCount++;

    scheduleCallback([this, fileName]() {
        OperationResult result;

        if (m_nextOpWillFail) {
            m_nextOpWillFail = false;
            result.success = false;
            result.errorMessage = m_nextOpError;
            emit fileDeleted(fileName, result);
            return;
        }

        if (m_files.contains(fileName)) {
            m_files.remove(fileName);
            result.success = true;
        } else {
            result.success = false;
            result.errorMessage = "File not found";
        }

        emit fileDeleted(fileName, result);
    });
}

void MockCloudStorageProvider::listFiles()
{
    m_operationCount++;

    scheduleCallback([this]() {
        QList<FileMetadata> files;

        for (auto it = m_files.constBegin(); it != m_files.constEnd(); ++it) {
            FileMetadata meta;
            meta.fileId = it.key();
            meta.name = it.key();
            meta.etag = it.value().etag;
            meta.size = it.value().data.size();
            meta.modifiedTime = it.value().modifiedTime;
            meta.exists = true;
            files.append(meta);
        }

        emit fileListReceived(files);
    });
}

void MockCloudStorageProvider::setSimulatedDelay(int delayMs)
{
    m_delayMs = delayMs;
}

void MockCloudStorageProvider::setAuthenticationWillSucceed(bool willSucceed)
{
    m_authWillSucceed = willSucceed;
}

void MockCloudStorageProvider::setServerFile(const QString& fileName,
                                             const QByteArray& data,
                                             const QString& etag)
{
    StoredFile file;
    file.data = data;
    file.etag = etag.isEmpty() ? generateEtag() : etag;
    file.modifiedTime = QDateTime::currentDateTimeUtc();
    m_files[fileName] = file;
}

QByteArray MockCloudStorageProvider::getServerFile(const QString& fileName) const
{
    if (m_files.contains(fileName)) {
        return m_files[fileName].data;
    }
    return QByteArray();
}

CloudStorageProvider::FileMetadata MockCloudStorageProvider::getServerMetadata(
    const QString& fileName) const
{
    FileMetadata meta;
    if (m_files.contains(fileName)) {
        const StoredFile& file = m_files[fileName];
        meta.fileId = fileName;
        meta.name = fileName;
        meta.etag = file.etag;
        meta.size = file.data.size();
        meta.modifiedTime = file.modifiedTime;
        meta.exists = true;
    }
    return meta;
}

bool MockCloudStorageProvider::serverFileExists(const QString& fileName) const
{
    return m_files.contains(fileName);
}

void MockCloudStorageProvider::clearServer()
{
    m_files.clear();
}

void MockCloudStorageProvider::setNextOperationWillFail(bool willFail,
                                                        const QString& errorMessage)
{
    m_nextOpWillFail = willFail;
    m_nextOpError = errorMessage;
}

QString MockCloudStorageProvider::generateEtag()
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces).left(8);
}

void MockCloudStorageProvider::scheduleCallback(std::function<void()> callback)
{
    if (m_delayMs > 0) {
        QTimer::singleShot(m_delayMs, this, callback);
    } else {
        // Execute immediately but still via event loop for consistent async behavior
        QTimer::singleShot(0, this, callback);
    }
}
