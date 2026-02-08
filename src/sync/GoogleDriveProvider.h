#ifndef GOOGLEDRIVEPROVIDER_H
#define GOOGLEDRIVEPROVIDER_H

#include "CloudStorageProvider.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QOAuthHttpServerReplyHandler>
#include <QSettings>

class QOAuth2AuthorizationCodeFlow;

/**
 * @brief Google Drive cloud storage provider
 *
 * Implements CloudStorageProvider for Google Drive using the REST API.
 * Uses the appDataFolder for hidden app-specific storage.
 */
class GoogleDriveProvider : public CloudStorageProvider
{
    Q_OBJECT

public:
    explicit GoogleDriveProvider(QObject *parent = nullptr);
    ~GoogleDriveProvider() override;

    // CloudStorageProvider interface
    void authenticate() override;
    void signOut() override;
    bool isAuthenticated() const override;

    void getFileMetadata(const QString& fileName) override;
    void downloadFile(const QString& fileName) override;
    void uploadFile(const QString& fileName, const QByteArray& data,
                    const QString& expectedEtag = QString()) override;
    void deleteFile(const QString& fileName) override;
    void listFiles() override;

    QString providerName() const override { return QStringLiteral("Google Drive"); }

    /**
     * @brief Set OAuth2 credentials
     *
     * Must be called before authenticate(). Credentials are obtained from
     * Google Cloud Console: https://console.cloud.google.com/
     *
     * @param clientId OAuth2 client ID
     * @param clientSecret OAuth2 client secret
     */
    void setCredentials(const QString& clientId, const QString& clientSecret);

    /**
     * @brief Set the redirect port for OAuth callback
     *
     * Default is 8080. Change if this port is in use.
     */
    void setRedirectPort(quint16 port);

private slots:
    void onAuthGranted();
    void onAuthError(const QString& error, const QString& errorDescription, const QUrl& uri);
    void onReplyFinished(QNetworkReply* reply);

private:
    // OAuth helpers
    void setupOAuth();
    void loadStoredTokens();
    void saveTokens();
    void clearStoredTokens();
    bool refreshAccessToken();

    // API helpers
    QNetworkRequest createAuthenticatedRequest(const QUrl& url);
    void findFileId(const QString& fileName,
                    std::function<void(const QString& fileId, const QString& etag)> callback);
    void createFile(const QString& fileName, const QByteArray& data);
    void updateFile(const QString& fileId, const QString& fileName,
                    const QByteArray& data, const QString& etag);

    // Response handlers
    void handleListResponse(QNetworkReply* reply);
    void handleDownloadResponse(QNetworkReply* reply, const QString& fileName);
    void handleUploadResponse(QNetworkReply* reply, const QString& fileName);
    void handleDeleteResponse(QNetworkReply* reply, const QString& fileName);
    void handleFileIdLookup(QNetworkReply* reply, const QString& fileName,
                            std::function<void(const QString&, const QString&)> callback);

    // Error handling
    void handleApiError(QNetworkReply* reply, const QString& operation);

    // OAuth2
    QOAuth2AuthorizationCodeFlow* m_oauth = nullptr;
    QOAuthHttpServerReplyHandler* m_replyHandler = nullptr;
    QString m_clientId;
    QString m_clientSecret;
    quint16 m_redirectPort = 8080;

    // Network
    QNetworkAccessManager* m_network = nullptr;

    // Token storage
    QString m_accessToken;
    QString m_refreshToken;
    QDateTime m_tokenExpiry;

    // Pending operations
    struct PendingUpload {
        QString fileName;
        QByteArray data;
        QString expectedEtag;
    };
    QMap<QNetworkReply*, PendingUpload> m_pendingUploads;
    QMap<QNetworkReply*, QString> m_pendingDownloads;
    QMap<QNetworkReply*, QString> m_pendingDeletes;
    QMap<QNetworkReply*, std::function<void(const QString&, const QString&)>> m_pendingFileIdLookups;

    // File ID cache (fileName -> fileId)
    QMap<QString, QString> m_fileIdCache;

    // API endpoints
    static const QString DRIVE_API_BASE;
    static const QString DRIVE_UPLOAD_BASE;
    static const QString TOKEN_URL;
    static const QString AUTH_URL;
    static const QString SCOPE;
};

#endif // GOOGLEDRIVEPROVIDER_H
