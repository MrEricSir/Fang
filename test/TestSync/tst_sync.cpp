#include <QTest>
#include <QSignalSpy>
#include <QtCore/qelapsedtimer.h>

#include "src/sync/CloudStorageProvider.h"
#include "src/sync/SyncData.h"
#include "src/sync/SyncService.h"
#include "MockCloudStorageProvider.h"

/**
 * @brief Unit tests for the sync functionality.
 *
 * These tests use MockCloudStorageProvider to test sync logic
 * without requiring a real cloud account.
 */
class TestSync : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    // SyncData tests
    void testFeedDataSerialization();
    void testBookmarkDataSerialization();
    void testPinDataSerialization();
    void testSettingsDataSerialization();
    void testSyncPayloadSerialization();
    void testSyncPayloadMerge();
    void testFeedUuidFromUrl();
    void testMergeLastWriteWins();
    void testMergeWithTombstones();

    // MockCloudStorageProvider tests
    void testMockAuthentication();
    void testMockFileOperations();
    void testMockConflictDetection();
    void testMockSimulatedDelay();
    void testMockSimulatedFailure();

    // SyncService tests (with mock provider)
    void testSyncServiceBasicFlow();
    void testSyncServiceConflictResolution();
    void testSyncServiceNoRemoteFile();
    void testSyncServiceAuthenticationRequired();
};

void TestSync::initTestCase()
{
}

void TestSync::cleanupTestCase()
{
}

// -----------------------------------------------------------------------------
// SyncData tests
// -----------------------------------------------------------------------------

void TestSync::testFeedDataSerialization()
{
    SyncData::FeedData original;
    original.uuid = "test-uuid-123";
    original.url = "https://example.com/feed.xml";
    original.title = "Test Feed";
    original.siteUrl = "https://example.com";
    original.ordinal = 5;
    original.parentFolderUuid = "folder-uuid";
    original.isFolder = false;
    original.folderOpen = true;
    original.minutesToUpdate = 30;
    original.timestamp = 1234567890000;
    original.deviceId = "device-1";
    original.deleted = false;

    // Serialize to JSON
    QJsonObject json = original.toJson();

    // Deserialize back
    SyncData::FeedData restored = SyncData::FeedData::fromJson(json);

    // Verify
    QCOMPARE(restored.uuid, original.uuid);
    QCOMPARE(restored.url, original.url);
    QCOMPARE(restored.title, original.title);
    QCOMPARE(restored.siteUrl, original.siteUrl);
    QCOMPARE(restored.ordinal, original.ordinal);
    QCOMPARE(restored.parentFolderUuid, original.parentFolderUuid);
    QCOMPARE(restored.isFolder, original.isFolder);
    QCOMPARE(restored.folderOpen, original.folderOpen);
    QCOMPARE(restored.minutesToUpdate, original.minutesToUpdate);
    QCOMPARE(restored.timestamp, original.timestamp);
    QCOMPARE(restored.deviceId, original.deviceId);
    QCOMPARE(restored.deleted, original.deleted);
}

void TestSync::testBookmarkDataSerialization()
{
    SyncData::BookmarkData original;
    original.feedUuid = "feed-123";
    original.newsGuid = "news-456";
    original.newsTimestamp = 9876543210000;
    original.timestamp = 1234567890000;
    original.deviceId = "device-1";

    QJsonObject json = original.toJson();
    SyncData::BookmarkData restored = SyncData::BookmarkData::fromJson(json);

    QCOMPARE(restored.feedUuid, original.feedUuid);
    QCOMPARE(restored.newsGuid, original.newsGuid);
    QCOMPARE(restored.newsTimestamp, original.newsTimestamp);
    QCOMPARE(restored.timestamp, original.timestamp);
    QCOMPARE(restored.deviceId, original.deviceId);
}

void TestSync::testPinDataSerialization()
{
    SyncData::PinData original;
    original.feedUuid = "feed-123";
    original.newsGuid = "news-456";
    original.pinned = true;
    original.timestamp = 1234567890000;
    original.deviceId = "device-1";

    QJsonObject json = original.toJson();
    SyncData::PinData restored = SyncData::PinData::fromJson(json);

    QCOMPARE(restored.feedUuid, original.feedUuid);
    QCOMPARE(restored.newsGuid, original.newsGuid);
    QCOMPARE(restored.pinned, original.pinned);
    QCOMPARE(restored.timestamp, original.timestamp);
    QCOMPARE(restored.deviceId, original.deviceId);
}

void TestSync::testSettingsDataSerialization()
{
    SyncData::SettingsData original;
    original.style = "DARK";
    original.fontSize = "LARGE";
    original.refreshInterval = "30MIN";
    original.cacheLength = "3MONTH";
    original.timestamp = 1234567890000;
    original.deviceId = "device-1";

    QJsonObject json = original.toJson();
    SyncData::SettingsData restored = SyncData::SettingsData::fromJson(json);

    QCOMPARE(restored.style, original.style);
    QCOMPARE(restored.fontSize, original.fontSize);
    QCOMPARE(restored.refreshInterval, original.refreshInterval);
    QCOMPARE(restored.cacheLength, original.cacheLength);
    QCOMPARE(restored.timestamp, original.timestamp);
    QCOMPARE(restored.deviceId, original.deviceId);
}

void TestSync::testSyncPayloadSerialization()
{
    SyncData::SyncPayload original;

    // Add a feed
    SyncData::FeedData feed;
    feed.uuid = "feed-1";
    feed.url = "https://example.com/feed.xml";
    feed.title = "Test Feed";
    feed.timestamp = 1000;
    original.feeds["feed-1"] = feed;

    // Add a bookmark
    SyncData::BookmarkData bookmark;
    bookmark.feedUuid = "feed-1";
    bookmark.newsGuid = "news-1";
    bookmark.timestamp = 2000;
    original.bookmarks["feed-1"] = bookmark;

    // Add settings
    original.settings.style = "LIGHT";
    original.settings.timestamp = 3000;

    original.lastModified = 4000;

    // Serialize and deserialize
    QByteArray json = original.toJson();
    bool ok = false;
    SyncData::SyncPayload restored = SyncData::SyncPayload::fromJson(json, &ok);

    QVERIFY(ok);
    QCOMPARE(restored.version, SyncData::SYNC_VERSION);
    QCOMPARE(restored.lastModified, original.lastModified);
    QCOMPARE(restored.feeds.size(), 1);
    QCOMPARE(restored.feeds["feed-1"].title, "Test Feed");
    QCOMPARE(restored.bookmarks.size(), 1);
    QCOMPARE(restored.bookmarks["feed-1"].newsGuid, "news-1");
    QCOMPARE(restored.settings.style, "LIGHT");
}

void TestSync::testSyncPayloadMerge()
{
    // Create two payloads simulating two devices
    SyncData::SyncPayload device1;
    device1.deviceId = "device-1";

    SyncData::SyncPayload device2;
    device2.deviceId = "device-2";

    // Device 1 has feed A
    SyncData::FeedData feedA;
    feedA.uuid = "feed-a";
    feedA.title = "Feed A";
    feedA.timestamp = 1000;
    feedA.deviceId = "device-1";
    device1.feeds["feed-a"] = feedA;

    // Device 2 has feed B
    SyncData::FeedData feedB;
    feedB.uuid = "feed-b";
    feedB.title = "Feed B";
    feedB.timestamp = 2000;
    feedB.deviceId = "device-2";
    device2.feeds["feed-b"] = feedB;

    // Merge device2 into device1
    device1.merge(device2);

    // Should have both feeds
    QCOMPARE(device1.feeds.size(), 2);
    QVERIFY(device1.feeds.contains("feed-a"));
    QVERIFY(device1.feeds.contains("feed-b"));
}

void TestSync::testFeedUuidFromUrl()
{
    QString url1 = "https://example.com/feed.xml";
    QString url2 = "https://example.com/other-feed.xml";

    QString uuid1a = SyncData::feedUuidFromUrl(url1);
    QString uuid1b = SyncData::feedUuidFromUrl(url1);
    QString uuid2 = SyncData::feedUuidFromUrl(url2);

    // Same URL should give same UUID
    QCOMPARE(uuid1a, uuid1b);

    // Different URL should give different UUID
    QVERIFY(uuid1a != uuid2);

    // UUID should be valid format
    QCOMPARE(uuid1a.length(), 36); // UUID without braces
}

void TestSync::testMergeLastWriteWins()
{
    SyncData::SyncPayload local;
    local.deviceId = "local";

    SyncData::SyncPayload remote;
    remote.deviceId = "remote";

    // Same feed, different timestamps
    SyncData::FeedData localFeed;
    localFeed.uuid = "feed-1";
    localFeed.title = "Old Title";
    localFeed.timestamp = 1000;
    localFeed.deviceId = "local";
    local.feeds["feed-1"] = localFeed;

    SyncData::FeedData remoteFeed;
    remoteFeed.uuid = "feed-1";
    remoteFeed.title = "New Title";
    remoteFeed.timestamp = 2000;  // Newer
    remoteFeed.deviceId = "remote";
    remote.feeds["feed-1"] = remoteFeed;

    // Merge remote into local
    local.merge(remote);

    // Remote should win (newer timestamp)
    QCOMPARE(local.feeds["feed-1"].title, "New Title");
    QCOMPARE(local.feeds["feed-1"].deviceId, "remote");
}

void TestSync::testMergeWithTombstones()
{
    SyncData::SyncPayload local;
    local.deviceId = "local";

    SyncData::SyncPayload remote;
    remote.deviceId = "remote";

    // Local has active feed
    SyncData::FeedData localFeed;
    localFeed.uuid = "feed-1";
    localFeed.title = "Active Feed";
    localFeed.timestamp = 1000;
    localFeed.deleted = false;
    localFeed.deviceId = "local";
    local.feeds["feed-1"] = localFeed;

    // Remote has deleted it (later)
    SyncData::FeedData remoteFeed;
    remoteFeed.uuid = "feed-1";
    remoteFeed.title = "Active Feed";
    remoteFeed.timestamp = 2000;  // Later
    remoteFeed.deleted = true;    // Tombstone
    remoteFeed.deviceId = "remote";
    remote.feeds["feed-1"] = remoteFeed;

    local.merge(remote);

    // Should be marked as deleted
    QVERIFY(local.feeds["feed-1"].deleted);
}

// -----------------------------------------------------------------------------
// MockCloudStorageProvider tests
// -----------------------------------------------------------------------------

void TestSync::testMockAuthentication()
{
    MockCloudStorageProvider provider;

    QVERIFY(!provider.isAuthenticated());

    QSignalSpy authSpy(&provider, &CloudStorageProvider::authenticated);
    provider.authenticate();

    QTRY_COMPARE(authSpy.count(), 1);
    QVERIFY(provider.isAuthenticated());

    // Test failed auth
    MockCloudStorageProvider provider2;
    provider2.setAuthenticationWillSucceed(false);

    QSignalSpy failSpy(&provider2, &CloudStorageProvider::authenticationFailed);
    provider2.authenticate();

    QTRY_COMPARE(failSpy.count(), 1);
    QVERIFY(!provider2.isAuthenticated());
}

void TestSync::testMockFileOperations()
{
    MockCloudStorageProvider provider;
    provider.authenticate();

    // Upload a file
    QByteArray testData = "Hello, World!";
    QSignalSpy uploadSpy(&provider, &CloudStorageProvider::fileUploaded);

    provider.uploadFile("test.txt", testData);
    QTRY_COMPARE(uploadSpy.count(), 1);

    auto uploadResult = uploadSpy.first().at(1).value<CloudStorageProvider::OperationResult>();
    QVERIFY(uploadResult.success);
    QVERIFY(!uploadResult.metadata.etag.isEmpty());

    // Download the file
    QSignalSpy downloadSpy(&provider, &CloudStorageProvider::fileDownloaded);
    provider.downloadFile("test.txt");
    QTRY_COMPARE(downloadSpy.count(), 1);

    auto downloadResult = downloadSpy.first().at(1).value<CloudStorageProvider::OperationResult>();
    QVERIFY(downloadResult.success);
    QCOMPARE(downloadResult.data, testData);

    // Get metadata
    QSignalSpy metaSpy(&provider, &CloudStorageProvider::metadataReceived);
    provider.getFileMetadata("test.txt");
    QTRY_COMPARE(metaSpy.count(), 1);

    auto metaResult = metaSpy.first().at(1).value<CloudStorageProvider::OperationResult>();
    QVERIFY(metaResult.success);
    QVERIFY(metaResult.metadata.exists);
    QCOMPARE(metaResult.metadata.size, testData.size());

    // Delete
    QSignalSpy deleteSpy(&provider, &CloudStorageProvider::fileDeleted);
    provider.deleteFile("test.txt");
    QTRY_COMPARE(deleteSpy.count(), 1);

    QVERIFY(!provider.serverFileExists("test.txt"));
}

void TestSync::testMockConflictDetection()
{
    MockCloudStorageProvider provider;

    // Set up initial file with known ETag
    provider.setServerFile("sync.json", "original data", "etag-v1");

    // Try to upload with correct ETag
    QSignalSpy uploadSpy(&provider, &CloudStorageProvider::fileUploaded);
    provider.uploadFile("sync.json", "new data", "etag-v1");
    QTRY_COMPARE(uploadSpy.count(), 1);

    auto result = uploadSpy.first().at(1).value<CloudStorageProvider::OperationResult>();
    QVERIFY(result.success);
    QString newEtag = result.metadata.etag;

    // Try to upload with old ETag - should trigger conflict
    QSignalSpy conflictSpy(&provider, &CloudStorageProvider::conflictDetected);
    provider.uploadFile("sync.json", "conflicting data", "etag-v1");  // Old ETag
    QTRY_COMPARE(conflictSpy.count(), 1);

    auto serverMeta = conflictSpy.first().at(1).value<CloudStorageProvider::FileMetadata>();
    QCOMPARE(serverMeta.etag, newEtag);
}

void TestSync::testMockSimulatedDelay()
{
    MockCloudStorageProvider provider;
    provider.setSimulatedDelay(50);  // 50ms delay

    QElapsedTimer timer;
    timer.start();

    QSignalSpy uploadSpy(&provider, &CloudStorageProvider::fileUploaded);
    provider.uploadFile("test.txt", "data");

    QTRY_COMPARE(uploadSpy.count(), 1);

    // Should have taken at least 50ms
    QVERIFY(timer.elapsed() >= 50);
}

void TestSync::testMockSimulatedFailure()
{
    MockCloudStorageProvider provider;

    provider.setNextOperationWillFail(true, "Simulated network error");

    QSignalSpy uploadSpy(&provider, &CloudStorageProvider::fileUploaded);
    provider.uploadFile("test.txt", "data");
    QTRY_COMPARE(uploadSpy.count(), 1);

    auto result = uploadSpy.first().at(1).value<CloudStorageProvider::OperationResult>();
    QVERIFY(!result.success);
    QCOMPARE(result.errorMessage, "Simulated network error");

    // Next operation should succeed
    uploadSpy.clear();
    provider.uploadFile("test.txt", "data");
    QTRY_COMPARE(uploadSpy.count(), 1);

    result = uploadSpy.first().at(1).value<CloudStorageProvider::OperationResult>();
    QVERIFY(result.success);
}

// -----------------------------------------------------------------------------
// SyncService tests
// -----------------------------------------------------------------------------

void TestSync::testSyncServiceBasicFlow()
{
    // Note: This test requires FangApp which we don't have in unit tests
    // For now, just verify the class can be instantiated
    // Full integration tests would need FangApp

    // SyncService service(nullptr);  // Would need FangApp
    // MockCloudStorageProvider* provider = new MockCloudStorageProvider();
    // service.setProvider(provider);

    QSKIP("Requires FangApp integration - will be tested in integration tests");
}

void TestSync::testSyncServiceConflictResolution()
{
    QSKIP("Requires FangApp integration - will be tested in integration tests");
}

void TestSync::testSyncServiceNoRemoteFile()
{
    QSKIP("Requires FangApp integration - will be tested in integration tests");
}

void TestSync::testSyncServiceAuthenticationRequired()
{
    QSKIP("Requires FangApp integration - will be tested in integration tests");
}

QTEST_MAIN(TestSync)
#include "tst_sync.moc"
