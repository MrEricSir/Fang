#ifndef CLOUDSTORAGEPROVIDER_H
#define CLOUDSTORAGEPROVIDER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QList>

/**
 * @brief Abstract interface for cloud storage providers.
 *
 * This interface abstracts cloud storage operations (Google Drive, Dropbox, etc.)
 * to allow for easy testing with mock implementations and future backend additions.
 *
 * All operations are asynchronous and report results via signals.
 */
class CloudStorageProvider : public QObject
{
    Q_OBJECT

public:
    explicit CloudStorageProvider(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~CloudStorageProvider() = default;

    /**
     * @brief Metadata about a stored file.
     */
    struct FileMetadata {
        QString fileId;         // Provider-specific file identifier
        QString name;           // File name
        QString etag;           // Version/revision identifier for conflict detection
        qint64 size = 0;        // File size in bytes
        QDateTime modifiedTime; // Last modification time
        bool exists = false;    // Whether the file exists
    };

    /**
     * @brief Result of a file operation.
     */
    struct OperationResult {
        bool success = false;
        QString errorMessage;
        FileMetadata metadata;
        QByteArray data;        // For download operations
    };

    // -------------------------------------------------------------------------
    // Authentication
    // -------------------------------------------------------------------------

    /**
     * @brief Check if the user is currently authenticated.
     */
    virtual bool isAuthenticated() const = 0;

    /**
     * @brief Start the authentication flow.
     * Emits authenticated() on success, authenticationFailed() on failure.
     */
    virtual void authenticate() = 0;

    /**
     * @brief Sign out and clear stored credentials.
     */
    virtual void signOut() = 0;

    // -------------------------------------------------------------------------
    // File Operations
    // -------------------------------------------------------------------------

    /**
     * @brief Get metadata for a file without downloading its contents.
     * @param fileName The name of the file in the app's storage area.
     *
     * Emits metadataReceived() with the result.
     */
    virtual void getFileMetadata(const QString& fileName) = 0;

    /**
     * @brief Download a file's contents.
     * @param fileName The name of the file to download.
     *
     * Emits fileDownloaded() with the result.
     */
    virtual void downloadFile(const QString& fileName) = 0;

    /**
     * @brief Upload/create a file with the given contents.
     * @param fileName The name of the file to create/update.
     * @param data The file contents.
     * @param expectedEtag If non-empty, only update if current etag matches (optimistic locking).
     *                     Pass empty string to create new or force overwrite.
     *
     * Emits fileUploaded() with the result.
     * If expectedEtag doesn't match, emits conflictDetected().
     */
    virtual void uploadFile(const QString& fileName, const QByteArray& data,
                            const QString& expectedEtag = QString()) = 0;

    /**
     * @brief Delete a file.
     * @param fileName The name of the file to delete.
     *
     * Emits fileDeleted() with the result.
     */
    virtual void deleteFile(const QString& fileName) = 0;

    /**
     * @brief List all files in the app's storage area.
     *
     * Emits fileListReceived() with the result.
     */
    virtual void listFiles() = 0;

    // -------------------------------------------------------------------------
    // Provider Information
    // -------------------------------------------------------------------------

    /**
     * @brief Get the name of this provider (e.g., "Google Drive", "Dropbox").
     */
    virtual QString providerName() const = 0;

signals:
    // Authentication signals
    void authenticated();
    void authenticationFailed(const QString& errorMessage);
    void signedOut();

    // File operation signals
    void metadataReceived(const QString& fileName, const OperationResult& result);
    void fileDownloaded(const QString& fileName, const OperationResult& result);
    void fileUploaded(const QString& fileName, const OperationResult& result);
    void fileDeleted(const QString& fileName, const OperationResult& result);
    void fileListReceived(const QList<FileMetadata>& files);

    // Conflict detection (when expectedEtag doesn't match)
    void conflictDetected(const QString& fileName, const FileMetadata& serverMetadata);

    // General error signal
    void errorOccurred(const QString& operation, const QString& errorMessage);
};

#endif // CLOUDSTORAGEPROVIDER_H
