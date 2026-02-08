#ifndef SYNCSERVICE_H
#define SYNCSERVICE_H

#include "../FangObject.h"
#include "CloudStorageProvider.h"
#include "SyncData.h"

#include <QObject>
#include <QTimer>

class FangApp;

/**
 * @brief Syncs between local data and cloud storage.
 *
 * Resolves conflicts with last write wins, with merge.
 *
 * Algorithm:
 * 1. Download remote file (if exists)
 * 2. Convert local data to SyncPayload
 * 3. Merge remote into local
 * 4. Apply merged data to local database
 * 5. Upload merged payload to cloud
 */
class SyncService : public FangObject
{
    Q_OBJECT
    Q_PROPERTY(bool syncing READ isSyncing NOTIFY syncingChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString lastSyncTime READ lastSyncTimeString NOTIFY lastSyncTimeChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit SyncService(FangApp* app, FangObject *parent = nullptr);
    ~SyncService();

    /**
     * @brief Sets the cloud storage provider to use.
     * Takes ownership of the provider.
     */
    void setProvider(CloudStorageProvider* provider);

    /**
     * @brief Gets the current provider (may be nullptr).
     */
    inline CloudStorageProvider* provider() const { return _provider; }

    /**
     * @brief Checks if a sync is currently in progress.
     */
    inline bool isSyncing() const { return syncing; }

    /**
     * @brief Checks if sync is enabled.
     */
    inline bool isEnabled() const { return enabled; }

    /**
     * @brief Enables or disables syncing
     */
    void setEnabled(bool enabled);

    /**
     * @brief Gets the last sync time as a human-readable string.
     */
    QString lastSyncTimeString() const;

    /**
     * @brief Gets the last sync time.
     */
    inline QDateTime lastSyncTime() const { return lastSyncAt; }

    /**
     * @brief Gets the last error message (empty if no error).
     */
    inline QString lastError() const { return _lastError; }

    /**
     * @brief Sets the sync interval in minutes.
     */
    void setSyncInterval(int minutes);

    /**
     * @brief Gets the sync interval in minutes.
     */
    inline int syncInterval() const { return intervalMinutes; }

    // Name of sync file.
    static constexpr const char* SYNC_FILE_NAME = "fang-sync.json";

public slots:
    /**
     * @brief Triggers a manual sync.
     */
    void sync();

    /**
     * @brief Starts the authentication process.
     */
    void authenticate();

    /**
     * @brief Signs out from the cloud provider.
     */
    void signOut();

signals:
    void syncingChanged();
    void enabledChanged();
    void lastSyncTimeChanged();
    void lastErrorChanged();

    void syncStarted();
    void syncCompleted();
    void syncFailed(const QString& errorMessage);

    void authenticationRequired();
    void authenticated();
    void signedOut();

private slots:
    void onAuthenticated();
    void onAuthenticationFailed(const QString& error);
    void onFileDownloaded(const QString& fileName,
                          const CloudStorageProvider::OperationResult& result);
    void onFileUploaded(const QString& fileName,
                        const CloudStorageProvider::OperationResult& result);
    void onConflictDetected(const QString& fileName,
                            const CloudStorageProvider::FileMetadata& serverMeta);
    void onSyncTimer();


private:
    enum class SyncState {
        Idle,
        Downloading,
        Uploading,
        ResolvingConflict
    };

    void setSyncing(bool syncing);
    void setLastError(const QString& error);
    void connectProvider();
    void disconnectProvider();

    SyncData::SyncPayload buildLocalPayload();
    void applyPayloadToLocal(const SyncData::SyncPayload& payload);

    // Sync state machine
    void startDownload();
    void processDownloadedData(const QByteArray& data);
    void uploadMergedData();
    void finishSync(bool success, const QString& error = QString());

    FangApp* app;
    CloudStorageProvider* _provider = nullptr;
    QTimer* syncTimer;

    bool syncing = false;
    bool enabled = false;
    SyncState state = SyncState::Idle;

    int intervalMinutes = 15;
    QDateTime lastSyncAt;
    QString _lastError;
    QString currentEtag; // ETag of the remote file for conflict detection

    SyncData::SyncPayload payloadLocal;
    SyncData::SyncPayload payloadRemote;
    SyncData::SyncPayload payloadMerged;
};

#endif // SYNCSERVICE_H
