#include <QTest>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QBuffer>
#include <QThread>
#include <QStandardPaths>

#include "QImageCache.h"

class TestImageCache : public QObject
{
    Q_OBJECT

private:
    QString testCacheDir;

    // Helper to create valid ImageData with the given MIME type.
    ImageData createImageData(const QString& mimeType, int width = 10, int height = 10);

    // Helper to create an invalid ImageData.
    ImageData createInvalidImageData();

private slots:
    void init();
    void cleanup();

    // cacheDir()
    void testCacheDirCreatesDirectory();
    void testCacheDirIdempotent();

    // saveImage() - basic saves with each MIME type
    void testSaveImageJpeg();
    void testSaveImagePng();
    void testSaveImageGif();
    void testSaveImageWebp();
    void testSaveImageSvg();
    void testSaveImageUnknownMimeType();

    // saveImage() - behavior
    void testSaveImageReturnsBareFilename();
    void testSaveImageSkipsExistingFile();
    void testSaveImageInvalidData();
    void testSaveImageWriteFailure();
    void testSaveImageDeterministicHash();
    void testSaveImageDifferentUrlsDifferentFiles();

    // evictOlderThan()
    void testEvictDeletesOldFiles();
    void testEvictKeepsNewFiles();
    void testEvictMixedAges();
    void testEvictEmptyDirectory();
    void testEvictReturnsCount();
};

void TestImageCache::init()
{
    // Use a unique temp directory for each test to avoid interference.
    testCacheDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation)
                   + "/fang_test_imagecache_" + QString::number(QCoreApplication::applicationPid());
    QDir().mkpath(testCacheDir);

    // Override the cache location for testing.
    QStandardPaths::setTestModeEnabled(true);

    // Clean the cache dir so each test starts fresh.
    QDir cacheDir(QImageCache::cacheDir());
    if (cacheDir.exists()) {
        cacheDir.removeRecursively();
    }
}

void TestImageCache::cleanup()
{
    // Remove test cache directory.
    QDir(testCacheDir).removeRecursively();
    QStandardPaths::setTestModeEnabled(false);

    // Also clean up the test-mode cache directory that QImageCache::cacheDir() creates.
    QString cacheDir = QImageCache::cacheDir();
    QDir(cacheDir).removeRecursively();
}

ImageData TestImageCache::createImageData(const QString& mimeType, int width, int height)
{
    ImageData data;
    data.image = QImage(width, height, QImage::Format_ARGB32);
    data.image.fill(Qt::red);
    data.mimeType = mimeType;

    // Generate raw bytes matching the format.
    QBuffer buffer(&data.rawData);
    buffer.open(QIODevice::WriteOnly);
    if (mimeType == "image/jpeg") {
        data.image.save(&buffer, "JPEG");
    } else {
        data.image.save(&buffer, "PNG");
    }

    return data;
}

ImageData TestImageCache::createInvalidImageData()
{
    ImageData data;
    // Leave image null and rawData empty - isValid() returns false.
    return data;
}

// --- cacheDir() tests ---

void TestImageCache::testCacheDirCreatesDirectory()
{
    QString dir = QImageCache::cacheDir();
    QVERIFY(!dir.isEmpty());
    QVERIFY(QDir(dir).exists());
}

void TestImageCache::testCacheDirIdempotent()
{
    QString dir1 = QImageCache::cacheDir();
    QString dir2 = QImageCache::cacheDir();
    QCOMPARE(dir1, dir2);
    QVERIFY(QDir(dir1).exists());
}

// --- saveImage() MIME type tests ---

void TestImageCache::testSaveImageJpeg()
{
    ImageData data = createImageData("image/jpeg");
    QString path = QImageCache::saveImage(QUrl("http://example.com/photo.jpg"), data);
    QVERIFY(path.endsWith(".jpeg"));
    QVERIFY(QFile::exists(QImageCache::cacheDir() + "/" + path));
}

void TestImageCache::testSaveImagePng()
{
    ImageData data = createImageData("image/png");
    QString path = QImageCache::saveImage(QUrl("http://example.com/icon.png"), data);
    QVERIFY(path.endsWith(".png"));
}

void TestImageCache::testSaveImageGif()
{
    ImageData data = createImageData("image/gif");
    QString path = QImageCache::saveImage(QUrl("http://example.com/anim.gif"), data);
    QVERIFY(path.endsWith(".gif"));
}

void TestImageCache::testSaveImageWebp()
{
    ImageData data = createImageData("image/webp");
    QString path = QImageCache::saveImage(QUrl("http://example.com/photo.webp"), data);
    QVERIFY(path.endsWith(".webp"));
}

void TestImageCache::testSaveImageSvg()
{
    ImageData data = createImageData("image/svg+xml");
    QString path = QImageCache::saveImage(QUrl("http://example.com/logo.svg"), data);
    QVERIFY(path.endsWith(".svg"));
}

void TestImageCache::testSaveImageUnknownMimeType()
{
    ImageData data = createImageData("image/bmp");
    QString path = QImageCache::saveImage(QUrl("http://example.com/weird.bmp"), data);
    QVERIFY(path.endsWith(".bin"));
}

// --- saveImage() behavior tests ---

void TestImageCache::testSaveImageReturnsBareFilename()
{
    ImageData data = createImageData("image/png");
    QString path = QImageCache::saveImage(QUrl("http://example.com/test.png"), data);
    QVERIFY(!path.startsWith("/"));
    QVERIFY(!path.contains("/"));
    QVERIFY(!path.isEmpty());
}

void TestImageCache::testSaveImageSkipsExistingFile()
{
    QUrl url("http://example.com/existing.png");
    ImageData data = createImageData("image/png");

    // First save.
    QString path1 = QImageCache::saveImage(url, data);
    QVERIFY(!path1.isEmpty());

    QString filePath = QImageCache::cacheDir() + "/" + path1;
    QFileInfo infoBefore(filePath);
    QDateTime mtimeBefore = infoBefore.lastModified();

    // Small delay to ensure mtime would differ if rewritten.
    QThread::msleep(50);

    // Second save with different data - should skip write.
    ImageData data2 = createImageData("image/png", 20, 20);
    QString path2 = QImageCache::saveImage(url, data2);
    QCOMPARE(path1, path2);

    // File should not have been rewritten.
    QFileInfo infoAfter(filePath);
    QCOMPARE(infoBefore.size(), infoAfter.size());
}

void TestImageCache::testSaveImageInvalidData()
{
    ImageData data = createInvalidImageData();
    QString path = QImageCache::saveImage(QUrl("http://example.com/bad.png"), data);
    QVERIFY(path.isEmpty());
}

void TestImageCache::testSaveImageWriteFailure()
{
#ifdef Q_OS_WIN
    QSKIP("Directory read-only permissions don't prevent file creation on Windows NTFS");
#endif
    // Create a read-only directory to force a write failure.
    QString readOnlyDir = testCacheDir + "/readonly_cache";
    QDir().mkpath(readOnlyDir);

    // Create a file where the cache file would go, but make the directory read-only.
    // We can't easily override cacheDir(), so instead we test by verifying that
    // saveImage returns empty string when write fails.
    // The simplest way: make the cache dir read-only temporarily.
    QString cacheDir = QImageCache::cacheDir();
    QFile::setPermissions(cacheDir, QFileDevice::ReadOwner | QFileDevice::ExeOwner);

    ImageData data = createImageData("image/png");
    QString path = QImageCache::saveImage(QUrl("http://example.com/fail.png"), data);
    QVERIFY(path.isEmpty());

    // Restore permissions for cleanup.
    QFile::setPermissions(cacheDir, QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
}

void TestImageCache::testSaveImageDeterministicHash()
{
    ImageData data = createImageData("image/png");
    QUrl url("http://example.com/deterministic.png");

    QString path1 = QImageCache::saveImage(url, data);

    // Remove the file so the second call writes again.
    QString filePath = QImageCache::cacheDir() + "/" + path1;
    QFile::remove(filePath);

    QString path2 = QImageCache::saveImage(url, data);
    QCOMPARE(path1, path2);
}

void TestImageCache::testSaveImageDifferentUrlsDifferentFiles()
{
    ImageData data = createImageData("image/png");

    QString path1 = QImageCache::saveImage(QUrl("http://example.com/a.png"), data);
    QString path2 = QImageCache::saveImage(QUrl("http://example.com/b.png"), data);

    QVERIFY(path1 != path2);
}

// --- evictOlderThan() tests ---

void TestImageCache::testEvictDeletesOldFiles()
{
    // Save an image, then evict with a future cutoff.
    ImageData data = createImageData("image/png");
    QString path = QImageCache::saveImage(QUrl("http://example.com/old.png"), data);
    QVERIFY(!path.isEmpty());

    // Evict everything older than 1 second from now (which is everything).
    QDateTime futureCutoff = QDateTime::currentDateTime().addSecs(1);
    int deleted = QImageCache::evictOlderThan(futureCutoff);
    QCOMPARE(deleted, 1);

    // File should be gone.
    QString filePath = QImageCache::cacheDir() + "/" + path;
    QVERIFY(!QFile::exists(filePath));
}

void TestImageCache::testEvictKeepsNewFiles()
{
    ImageData data = createImageData("image/png");
    QString path = QImageCache::saveImage(QUrl("http://example.com/new.png"), data);
    QVERIFY(!path.isEmpty());

    // Evict with a cutoff in the past - should keep everything.
    QDateTime pastCutoff = QDateTime::currentDateTime().addDays(-1);
    int deleted = QImageCache::evictOlderThan(pastCutoff);
    QCOMPARE(deleted, 0);

    // File should still exist.
    QString filePath = QImageCache::cacheDir() + "/" + path;
    QVERIFY(QFile::exists(filePath));
}

void TestImageCache::testEvictMixedAges()
{
    QString cacheDir = QImageCache::cacheDir();

    // Create an "old" file by writing directly with a backdated mtime.
    QString oldFile = cacheDir + "/old_file.png";
    {
        QFile f(oldFile);
        QVERIFY(f.open(QIODevice::WriteOnly));
        f.write("old data");
        f.close();
    }

    // Backdate the old file's modification time using Qt API (cross-platform).
    QFile oldFileHandle(oldFile);
    QVERIFY(oldFileHandle.open(QIODevice::ReadWrite));
    QDateTime oldDate(QDate(2020, 1, 1), QTime(0, 0, 0));
    QVERIFY(oldFileHandle.setFileTime(oldDate, QFileDevice::FileModificationTime));
    oldFileHandle.close();

    // Create a "new" file via saveImage.
    ImageData data = createImageData("image/png");
    QString newPath = QImageCache::saveImage(QUrl("http://example.com/fresh.png"), data);
    QVERIFY(!newPath.isEmpty());

    // Evict with a cutoff that's recent (only old file should be deleted).
    QDateTime cutoff = QDateTime::currentDateTime().addDays(-1);
    int deleted = QImageCache::evictOlderThan(cutoff);
    QCOMPARE(deleted, 1);

    // Old file gone, new file remains.
    QVERIFY(!QFile::exists(oldFile));
    QString newFilePath = cacheDir + "/" + newPath;
    QVERIFY(QFile::exists(newFilePath));
}

void TestImageCache::testEvictEmptyDirectory()
{
    // Ensure the cache dir exists but is empty.
    QImageCache::cacheDir();

    int deleted = QImageCache::evictOlderThan(QDateTime::currentDateTime().addSecs(1));
    QCOMPARE(deleted, 0);
}

void TestImageCache::testEvictReturnsCount()
{
    ImageData data = createImageData("image/png");

    // Save three images.
    QImageCache::saveImage(QUrl("http://example.com/one.png"), data);
    QImageCache::saveImage(QUrl("http://example.com/two.png"), data);
    QImageCache::saveImage(QUrl("http://example.com/three.png"), data);

    // Evict all.
    QDateTime futureCutoff = QDateTime::currentDateTime().addSecs(1);
    int deleted = QImageCache::evictOlderThan(futureCutoff);
    QCOMPARE(deleted, 3);
}

QTEST_MAIN(TestImageCache)

#include "tst_imagecache.moc"
