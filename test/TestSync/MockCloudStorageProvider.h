#ifndef MOCKCLOUDSTORGEPROVIDER_H
#define MOCKCLOUDSTORGEPROVIDER_H

#include "src/sync/CloudStorageProvider.h"

#include <QMap>
#include <QTimer>

/**
 * @brief Mock implementation of CloudStorageProvider for testing.
 *
 * This mock provider stores files in memory and can simulate:
 * - Network delays
 * - Errors and failures
 * - Conflicts (ETag mismatches)
 * - Multiple devices (via different instances)
 *
 * Usage in tests:
 * @code
 *   MockCloudStorageProvider provider;
 *   provider.setSimulatedDelay(100); // 100ms delay
 *
 *   // Simulate a file already existing on "server"
 *   provider.setServerFile("sync.json", someData, "etag-1");
 *
 *   // Test sync logic...
 *   provider.uploadFile("sync.json", newData, "etag-1");
 *
 *   // Verify results
 *   QCOMPARE(provider.getServerFile("sync.json"), newData);
 * @endcode
 */
class MockCloudStorageProvider : public CloudStorageProvider
{
    Q_OBJECT

public:
    explicit MockCloudStorageProvider(QObject *parent = nullptr);

    // -------------------------------------------------------------------------
    // CloudStorageProvider interface
    // -------------------------------------------------------------------------

    bool isAuthenticated() const override;
    void authenticate() override;
    void signOut() override;

    void getFileMetadata(const QString& fileName) override;
    void downloadFile(const QString& fileName) override;
    void uploadFile(const QString& fileName, const QByteArray& data,
                    const QString& expectedEtag = QString()) override;
    void deleteFile(const QString& fileName) override;
    void listFiles() override;

    QString providerName() const override { return QStringLiteral("Mock Storage"); }

    // -------------------------------------------------------------------------
    // Test configuration
    // -------------------------------------------------------------------------

    /**
     * @brief Set simulated network delay in milliseconds.
     */
    void setSimulatedDelay(int delayMs);

    /**
     * @brief Set whether authentication should succeed.
     */
    void setAuthenticationWillSucceed(bool willSucceed);

    /**
     * @brief Set a file on the simulated server.
     */
    void setServerFile(const QString& fileName, const QByteArray& data,
                       const QString& etag = QString());

    /**
     * @brief Get a file from the simulated server (for test verification).
     */
    QByteArray getServerFile(const QString& fileName) const;

    /**
     * @brief Get metadata for a server file (for test verification).
     */
    FileMetadata getServerMetadata(const QString& fileName) const;

    /**
     * @brief Check if a file exists on the simulated server.
     */
    bool serverFileExists(const QString& fileName) const;

    /**
     * @brief Clear all files from the simulated server.
     */
    void clearServer();

    /**
     * @brief Set whether the next operation should fail.
     */
    void setNextOperationWillFail(bool willFail, const QString& errorMessage = "Simulated error");

    /**
     * @brief Get the number of operations performed (for test verification).
     */
    int operationCount() const { return m_operationCount; }

    /**
     * @brief Reset operation count.
     */
    void resetOperationCount() { m_operationCount = 0; }

private:
    struct StoredFile {
        QByteArray data;
        QString etag;
        QDateTime modifiedTime;
    };

    bool m_authenticated = false;
    bool m_authWillSucceed = true;
    int m_delayMs = 0;
    bool m_nextOpWillFail = false;
    QString m_nextOpError;
    int m_operationCount = 0;

    QMap<QString, StoredFile> m_files;

    QString generateEtag();
    void scheduleCallback(std::function<void()> callback);
};

#endif // MOCKCLOUDSTORGEPROVIDER_H
