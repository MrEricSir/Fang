#include "GoogleDriveProvider.h"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QOAuth2AuthorizationCodeFlow>
#include <QUrlQuery>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logGDrive, "fang.sync.gdrive")

// Google Drive API endpoints
const QString GoogleDriveProvider::DRIVE_API_BASE = "https://www.googleapis.com/drive/v3";
const QString GoogleDriveProvider::DRIVE_UPLOAD_BASE = "https://www.googleapis.com/upload/drive/v3";
const QString GoogleDriveProvider::TOKEN_URL = "https://oauth2.googleapis.com/token";
const QString GoogleDriveProvider::AUTH_URL = "https://accounts.google.com/o/oauth2/v2/auth";
const QString GoogleDriveProvider::SCOPE = "https://www.googleapis.com/auth/drive.appdata";

GoogleDriveProvider::GoogleDriveProvider(QObject *parent)
    : CloudStorageProvider(parent)
    , m_network(new QNetworkAccessManager(this))
{
    connect(m_network, &QNetworkAccessManager::finished,
            this, &GoogleDriveProvider::onReplyFinished);

    loadStoredTokens();
}

GoogleDriveProvider::~GoogleDriveProvider()
{
    if (m_replyHandler) {
        m_replyHandler->close();
    }
}

void GoogleDriveProvider::setCredentials(const QString& clientId, const QString& clientSecret)
{
    m_clientId = clientId;
    m_clientSecret = clientSecret;

    if (m_oauth) {
        delete m_oauth;
        m_oauth = nullptr;
    }
}

void GoogleDriveProvider::setRedirectPort(quint16 port)
{
    m_redirectPort = port;
}

void GoogleDriveProvider::setupOAuth()
{
    if (m_oauth) return;

    m_oauth = new QOAuth2AuthorizationCodeFlow(this);
    m_oauth->setRequestedScopeTokens({SCOPE.toUtf8()});
    m_oauth->setAuthorizationUrl(QUrl(AUTH_URL));
    m_oauth->setTokenUrl(QUrl(TOKEN_URL));
    m_oauth->setClientIdentifier(m_clientId);
    m_oauth->setClientIdentifierSharedKey(m_clientSecret);

    // Set up local reply handler for OAuth callback
    m_replyHandler = new QOAuthHttpServerReplyHandler(m_redirectPort, this);
    m_oauth->setReplyHandler(m_replyHandler);

    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::granted,
            this, &GoogleDriveProvider::onAuthGranted);
    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::serverReportedErrorOccurred,
            this, &GoogleDriveProvider::onAuthError);

    // Open browser for authorization
    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
            &QDesktopServices::openUrl);
}

void GoogleDriveProvider::authenticate()
{
    if (m_clientId.isEmpty() || m_clientSecret.isEmpty()) {
        qCWarning(logGDrive) << "OAuth credentials not set";
        emit authenticationFailed(tr("OAuth credentials not configured"));
        return;
    }

    // Check if we have valid stored tokens
    if (!m_accessToken.isEmpty() && m_tokenExpiry > QDateTime::currentDateTime()) {
        qCDebug(logGDrive) << "Using stored access token";
        emit authenticated();
        return;
    }

    // Try to refresh if we have a refresh token
    if (!m_refreshToken.isEmpty()) {
        qCDebug(logGDrive) << "Attempting token refresh";
        if (refreshAccessToken()) {
            return;  // Will emit authenticated() on success
        }
    }

    // Need full OAuth flow
    qCDebug(logGDrive) << "Starting OAuth flow";
    setupOAuth();
    m_oauth->grant();
}

void GoogleDriveProvider::signOut()
{
    m_accessToken.clear();
    m_refreshToken.clear();
    m_tokenExpiry = QDateTime();
    m_fileIdCache.clear();
    clearStoredTokens();

    qCInfo(logGDrive) << "Signed out";
}

bool GoogleDriveProvider::isAuthenticated() const
{
    return !m_accessToken.isEmpty() && m_tokenExpiry > QDateTime::currentDateTime();
}

void GoogleDriveProvider::loadStoredTokens()
{
    QSettings settings;
    settings.beginGroup("Sync/GoogleDrive");
    m_accessToken = settings.value("accessToken").toString();
    m_refreshToken = settings.value("refreshToken").toString();
    m_tokenExpiry = settings.value("tokenExpiry").toDateTime();
    settings.endGroup();

    if (!m_accessToken.isEmpty()) {
        qCDebug(logGDrive) << "Loaded stored tokens, expiry:" << m_tokenExpiry;
    }
}

void GoogleDriveProvider::saveTokens()
{
    QSettings settings;
    settings.beginGroup("Sync/GoogleDrive");
    settings.setValue("accessToken", m_accessToken);
    settings.setValue("refreshToken", m_refreshToken);
    settings.setValue("tokenExpiry", m_tokenExpiry);
    settings.endGroup();
}

void GoogleDriveProvider::clearStoredTokens()
{
    QSettings settings;
    settings.beginGroup("Sync/GoogleDrive");
    settings.remove("");
    settings.endGroup();
}

bool GoogleDriveProvider::refreshAccessToken()
{
    if (m_refreshToken.isEmpty()) {
        return false;
    }

    QUrl tokenUrl(TOKEN_URL);
    QNetworkRequest request(tokenUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("client_id", m_clientId);
    params.addQueryItem("client_secret", m_clientSecret);
    params.addQueryItem("refresh_token", m_refreshToken);
    params.addQueryItem("grant_type", "refresh_token");

    QNetworkReply* reply = m_network->post(request, params.toString(QUrl::FullyEncoded).toUtf8());

    // Block for token refresh (it's fast and we need the token before proceeding)
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(logGDrive) << "Token refresh failed:" << reply->errorString();
        reply->deleteLater();
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = doc.object();
    reply->deleteLater();

    if (json.contains("error")) {
        qCWarning(logGDrive) << "Token refresh error:" << json["error"].toString();
        clearStoredTokens();
        return false;
    }

    m_accessToken = json["access_token"].toString();
    int expiresIn = json["expires_in"].toInt();
    m_tokenExpiry = QDateTime::currentDateTime().addSecs(expiresIn);

    // Refresh token might be returned (rare)
    if (json.contains("refresh_token")) {
        m_refreshToken = json["refresh_token"].toString();
    }

    saveTokens();
    qCInfo(logGDrive) << "Token refreshed, expires:" << m_tokenExpiry;
    emit authenticated();
    return true;
}

void GoogleDriveProvider::onAuthGranted()
{
    qCInfo(logGDrive) << "OAuth authorization granted";

    m_accessToken = m_oauth->token();
    m_refreshToken = m_oauth->refreshToken();
    int expiresIn = m_oauth->expirationAt().toSecsSinceEpoch() - QDateTime::currentSecsSinceEpoch();
    m_tokenExpiry = QDateTime::currentDateTime().addSecs(expiresIn);

    saveTokens();
    emit authenticated();
}

void GoogleDriveProvider::onAuthError(const QString& error, const QString& errorDescription, const QUrl& uri)
{
    Q_UNUSED(uri);
    QString message = error;
    if (!errorDescription.isEmpty()) {
        message += ": " + errorDescription;
    }
    qCWarning(logGDrive) << "OAuth error:" << message;
    emit authenticationFailed(message);
}

QNetworkRequest GoogleDriveProvider::createAuthenticatedRequest(const QUrl& url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + m_accessToken).toUtf8());
    return request;
}

void GoogleDriveProvider::getFileMetadata(const QString& fileName)
{
    if (!isAuthenticated()) {
        OperationResult result;
        result.success = false;
        result.errorMessage = tr("Not authenticated");
        emit metadataReceived(fileName, result);
        return;
    }

    findFileId(fileName, [this, fileName](const QString& fileId, const QString& etag) {
        OperationResult result;

        if (fileId.isEmpty()) {
            result.success = true;  // Success, but file doesn't exist
            result.metadata.exists = false;
        } else {
            result.success = true;
            result.metadata.exists = true;
            result.metadata.fileId = fileId;
            result.metadata.etag = etag;
            result.metadata.name = fileName;
        }

        emit metadataReceived(fileName, result);
    });
}

void GoogleDriveProvider::downloadFile(const QString& fileName)
{
    if (!isAuthenticated()) {
        OperationResult result;
        result.success = false;
        result.errorMessage = tr("Not authenticated");
        emit fileDownloaded(fileName, result);
        return;
    }

    // First, find the file ID
    findFileId(fileName, [this, fileName](const QString& fileId, const QString& etag) {
        if (fileId.isEmpty()) {
            OperationResult result;
            result.success = false;
            result.errorMessage = tr("File not found");
            emit fileDownloaded(fileName, result);
            return;
        }

        // Download the file content
        QUrl url(DRIVE_API_BASE + "/files/" + fileId);
        QUrlQuery query;
        query.addQueryItem("alt", "media");
        url.setQuery(query);

        QNetworkRequest request = createAuthenticatedRequest(url);
        QNetworkReply* reply = m_network->get(request);

        m_pendingDownloads[reply] = fileName;
        // Store etag for the result
        reply->setProperty("etag", etag);
    });
}

void GoogleDriveProvider::uploadFile(const QString& fileName, const QByteArray& data,
                                      const QString& expectedEtag)
{
    if (!isAuthenticated()) {
        OperationResult result;
        result.success = false;
        result.errorMessage = tr("Not authenticated");
        emit fileUploaded(fileName, result);
        return;
    }

    // Check if file exists
    findFileId(fileName, [this, fileName, data, expectedEtag](const QString& fileId, const QString& currentEtag) {
        if (fileId.isEmpty()) {
            // Create new file
            createFile(fileName, data);
        } else {
            // Check for conflict
            if (!expectedEtag.isEmpty() && expectedEtag != currentEtag) {
                FileMetadata meta;
                meta.name = fileName;
                meta.etag = currentEtag;
                emit conflictDetected(fileName, meta);
                return;
            }

            // Update existing file
            updateFile(fileId, fileName, data, currentEtag);
        }
    });
}

void GoogleDriveProvider::createFile(const QString& fileName, const QByteArray& data)
{
    // Use multipart upload for simplicity
    QUrl url(DRIVE_UPLOAD_BASE + "/files");
    QUrlQuery query;
    query.addQueryItem("uploadType", "multipart");
    url.setQuery(query);

    // Build multipart body
    QString boundary = "----FangSyncBoundary" + QString::number(QDateTime::currentMSecsSinceEpoch());

    QByteArray body;
    body.append("--" + boundary.toUtf8() + "\r\n");
    body.append("Content-Type: application/json; charset=UTF-8\r\n\r\n");

    QJsonObject metadata;
    metadata["name"] = fileName;
    metadata["parents"] = QJsonArray({"appDataFolder"});
    body.append(QJsonDocument(metadata).toJson(QJsonDocument::Compact));
    body.append("\r\n--" + boundary.toUtf8() + "\r\n");
    body.append("Content-Type: application/json\r\n\r\n");
    body.append(data);
    body.append("\r\n--" + boundary.toUtf8() + "--\r\n");

    QNetworkRequest request = createAuthenticatedRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "multipart/related; boundary=" + boundary);

    QNetworkReply* reply = m_network->post(request, body);

    PendingUpload pending;
    pending.fileName = fileName;
    pending.data = data;
    m_pendingUploads[reply] = pending;
}

void GoogleDriveProvider::updateFile(const QString& fileId, const QString& fileName,
                                      const QByteArray& data, const QString& etag)
{
    QUrl url(DRIVE_UPLOAD_BASE + "/files/" + fileId);
    QUrlQuery query;
    query.addQueryItem("uploadType", "media");
    url.setQuery(query);

    QNetworkRequest request = createAuthenticatedRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Use If-Match for optimistic concurrency
    if (!etag.isEmpty()) {
        request.setRawHeader("If-Match", etag.toUtf8());
    }

    QNetworkReply* reply = m_network->sendCustomRequest(request, "PATCH", data);

    PendingUpload pending;
    pending.fileName = fileName;
    pending.data = data;
    pending.expectedEtag = etag;
    m_pendingUploads[reply] = pending;
}

void GoogleDriveProvider::deleteFile(const QString& fileName)
{
    if (!isAuthenticated()) {
        OperationResult result;
        result.success = false;
        result.errorMessage = tr("Not authenticated");
        emit fileDeleted(fileName, result);
        return;
    }

    findFileId(fileName, [this, fileName](const QString& fileId, const QString& etag) {
        Q_UNUSED(etag);
        if (fileId.isEmpty()) {
            OperationResult result;
            result.success = false;
            result.errorMessage = tr("File not found");
            emit fileDeleted(fileName, result);
            return;
        }

        QUrl url(DRIVE_API_BASE + "/files/" + fileId);
        QNetworkRequest request = createAuthenticatedRequest(url);
        QNetworkReply* reply = m_network->deleteResource(request);
        m_pendingDeletes[reply] = fileName;
    });
}

void GoogleDriveProvider::listFiles()
{
    if (!isAuthenticated()) {
        emit fileListReceived({});
        return;
    }

    QUrl url(DRIVE_API_BASE + "/files");
    QUrlQuery query;
    query.addQueryItem("spaces", "appDataFolder");
    query.addQueryItem("fields", "files(id,name,modifiedTime,size,md5Checksum)");
    url.setQuery(query);

    QNetworkRequest request = createAuthenticatedRequest(url);
    QNetworkReply* reply = m_network->get(request);
    reply->setProperty("operation", "list");
}

void GoogleDriveProvider::findFileId(const QString& fileName,
                                      std::function<void(const QString&, const QString&)> callback)
{
    // Check cache first
    if (m_fileIdCache.contains(fileName)) {
        // Still need to get current etag - do a metadata request
        QString fileId = m_fileIdCache[fileName];
        QUrl url(DRIVE_API_BASE + "/files/" + fileId);
        QUrlQuery query;
        query.addQueryItem("fields", "id,name,etag");
        url.setQuery(query);

        QNetworkRequest request = createAuthenticatedRequest(url);
        QNetworkReply* reply = m_network->get(request);
        reply->setProperty("fileName", fileName);
        m_pendingFileIdLookups[reply] = callback;
        return;
    }

    // Search in appDataFolder
    QUrl url(DRIVE_API_BASE + "/files");
    QUrlQuery query;
    query.addQueryItem("spaces", "appDataFolder");
    query.addQueryItem("q", QString("name='%1'").arg(fileName));
    query.addQueryItem("fields", "files(id,name,etag)");
    url.setQuery(query);

    QNetworkRequest request = createAuthenticatedRequest(url);
    QNetworkReply* reply = m_network->get(request);
    reply->setProperty("fileName", fileName);
    reply->setProperty("isSearch", true);
    m_pendingFileIdLookups[reply] = callback;
}

void GoogleDriveProvider::onReplyFinished(QNetworkReply* reply)
{
    reply->deleteLater();

    // Check what operation this was
    if (reply->property("operation").toString() == "list") {
        handleListResponse(reply);
        return;
    }

    if (m_pendingDownloads.contains(reply)) {
        QString fileName = m_pendingDownloads.take(reply);
        handleDownloadResponse(reply, fileName);
        return;
    }

    if (m_pendingUploads.contains(reply)) {
        PendingUpload pending = m_pendingUploads.take(reply);
        handleUploadResponse(reply, pending.fileName);
        return;
    }

    if (m_pendingDeletes.contains(reply)) {
        QString fileName = m_pendingDeletes.take(reply);
        handleDeleteResponse(reply, fileName);
        return;
    }

    if (m_pendingFileIdLookups.contains(reply)) {
        auto callback = m_pendingFileIdLookups.take(reply);
        QString fileName = reply->property("fileName").toString();
        handleFileIdLookup(reply, fileName, callback);
        return;
    }
}

void GoogleDriveProvider::handleListResponse(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(logGDrive) << "List files failed:" << reply->errorString();
        emit fileListReceived({});
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonArray files = doc.object()["files"].toArray();

    QList<FileMetadata> result;
    for (const auto& fileRef : files) {
        QJsonObject file = fileRef.toObject();
        FileMetadata meta;
        meta.name = file["name"].toString();
        meta.etag = file["md5Checksum"].toString();
        meta.size = file["size"].toString().toLongLong();
        meta.modifiedTime = QDateTime::fromString(file["modifiedTime"].toString(), Qt::ISODate);

        // Cache the file ID
        m_fileIdCache[meta.name] = file["id"].toString();

        result.append(meta);
    }

    qCDebug(logGDrive) << "Found" << result.size() << "files in appDataFolder";
    emit fileListReceived(result);
}

void GoogleDriveProvider::handleDownloadResponse(QNetworkReply* reply, const QString& fileName)
{
    OperationResult result;

    if (reply->error() != QNetworkReply::NoError) {
        result.success = false;
        result.errorMessage = reply->errorString();
        if (reply->error() == QNetworkReply::ContentNotFoundError) {
            result.errorMessage = tr("File not found");
        }
    } else {
        result.success = true;
        result.data = reply->readAll();
        result.metadata.name = fileName;
        result.metadata.etag = reply->property("etag").toString();
    }

    emit fileDownloaded(fileName, result);
}

void GoogleDriveProvider::handleUploadResponse(QNetworkReply* reply, const QString& fileName)
{
    OperationResult result;

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode == 412) {
        // Precondition failed - ETag mismatch (conflict)
        qCInfo(logGDrive) << "Upload conflict detected for" << fileName;

        // Re-fetch metadata to get current etag
        findFileId(fileName, [this, fileName](const QString& fileId, const QString& etag) {
            Q_UNUSED(fileId);
            FileMetadata meta;
            meta.name = fileName;
            meta.etag = etag;
            emit conflictDetected(fileName, meta);
        });
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        result.success = false;
        result.errorMessage = reply->errorString();
    } else {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject json = doc.object();

        result.success = true;
        result.metadata.name = fileName;
        result.metadata.etag = json["md5Checksum"].toString();

        // Cache the file ID
        QString fileId = json["id"].toString();
        if (!fileId.isEmpty()) {
            m_fileIdCache[fileName] = fileId;
        }

        qCInfo(logGDrive) << "File uploaded:" << fileName << "etag:" << result.metadata.etag;
    }

    emit fileUploaded(fileName, result);
}

void GoogleDriveProvider::handleDeleteResponse(QNetworkReply* reply, const QString& fileName)
{
    OperationResult result;

    if (reply->error() != QNetworkReply::NoError &&
        reply->error() != QNetworkReply::ContentNotFoundError) {
        result.success = false;
        result.errorMessage = reply->errorString();
    } else {
        result.success = true;
        m_fileIdCache.remove(fileName);
        qCInfo(logGDrive) << "File deleted:" << fileName;
    }

    emit fileDeleted(fileName, result);
}

void GoogleDriveProvider::handleFileIdLookup(QNetworkReply* reply, const QString& fileName,
                                              std::function<void(const QString&, const QString&)> callback)
{
    if (reply->error() != QNetworkReply::NoError) {
        qCDebug(logGDrive) << "File ID lookup failed:" << reply->errorString();
        callback(QString(), QString());
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = doc.object();

    QString fileId;
    QString etag;

    if (reply->property("isSearch").toBool()) {
        // This was a search result
        QJsonArray files = json["files"].toArray();
        if (!files.isEmpty()) {
            QJsonObject file = files[0].toObject();
            fileId = file["id"].toString();
            etag = file["etag"].toString();
            m_fileIdCache[fileName] = fileId;
        }
    } else {
        // This was a direct metadata lookup
        fileId = json["id"].toString();
        etag = json["etag"].toString();
    }

    callback(fileId, etag);
}

void GoogleDriveProvider::handleApiError(QNetworkReply* reply, const QString& operation)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString body = QString::fromUtf8(reply->readAll());

    qCWarning(logGDrive) << operation << "failed:"
                         << "status=" << statusCode
                         << "error=" << reply->errorString()
                         << "body=" << body.left(500);
}
