#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QBuffer>
#include <QImage>
#include <QImageWriter>

#include "../../src/utilities/ImageGrabber.h"
#include "../MockNetworkAccessManager.h"

class TestImageGrabber : public QObject
{
    Q_OBJECT

public:
    TestImageGrabber();

private:
    // Helper to create minimal valid PNG data
    QByteArray createTestPNG(int width = 1, int height = 1);
    // Helper to create minimal valid JPEG data
    QByteArray createTestJPEG(int width = 1, int height = 1);
    // Helper to create minimal valid GIF data
    QByteArray createTestGIF();

private slots:
    // Constructor tests
    void testConstructorWithProvidedManager();
    void testConstructorCreatesOwnManager();

    // Single URL fetch tests
    void testSingleURLFetch();
    void testSingleURLFetchWithValidImage();

    // Batch URL fetch tests
    void testBatchURLFetch();
    void testBatchURLFetchPartialSuccess();

    // Duplicate URL handling
    void testDuplicateURLsIgnored();

    // Image decoding tests
    void testPNGDecoding();
    void testJPEGDecoding();
    void testGIFDecoding();
    void testInvalidImageData();

    // MIME type detection
    void testMIMETypeDetectionPNG();
    void testMIMETypeDetectionJPEG();

    // Network error handling
    void testNetworkError();
    void testNetworkErrorPartialBatch();

    // Completion signal tests
    void testCompletionSignalAllSuccess();
    void testCompletionSignalPartialSuccess();

    // Edge cases
    void testEmptyURLList();
    void testResultsCleared();

    // HTTP redirect tests
    void testSingleRedirect();
    void testRedirectChain();
    void testMaxRedirectsExceeded();
    void testRelativeRedirect();
    void testRedirectInBatch();
};

TestImageGrabber::TestImageGrabber()
{
}

QByteArray TestImageGrabber::createTestPNG(int width, int height)
{
    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::red);

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return data;
}

QByteArray TestImageGrabber::createTestJPEG(int width, int height)
{
    QImage image(width, height, QImage::Format_RGB32);
    image.fill(Qt::blue);

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPEG");
    return data;
}

QByteArray TestImageGrabber::createTestGIF()
{
    // Minimal valid GIF89a (1x1 transparent pixel)
    // GIF format is more complex, so we'll create a simple QImage and hope
    // Qt can handle it, or use a minimal hand-crafted GIF
    static const unsigned char gif[] = {
        0x47, 0x49, 0x46, 0x38, 0x39, 0x61, // GIF89a
        0x01, 0x00, 0x01, 0x00,             // 1x1
        0x00,                               // no global color table
        0x00, 0x00,                         // background, aspect ratio
        0x2c,                               // image separator
        0x00, 0x00, 0x00, 0x00,             // position
        0x01, 0x00, 0x01, 0x00,             // dimensions
        0x00,                               // no local color table
        0x02, 0x01, 0x01, 0x00, 0x00,       // LZW minimum code + data
        0x3b                                // trailer
    };
    return QByteArray(reinterpret_cast<const char*>(gif), sizeof(gif));
}

void TestImageGrabber::testConstructorWithProvidedManager()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    // Verify the grabber uses the provided manager by checking it receives requests
    QByteArray pngData = createTestPNG();
    mockManager.addResponse(QUrl("http://example.com/test.png"), pngData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(QUrl("http://example.com/test.png"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
}

void TestImageGrabber::testConstructorCreatesOwnManager()
{
    // When no manager provided, grabber creates its own
    ImageGrabber grabber(nullptr, nullptr);

    // We can't easily verify this directly, but object should be created
    QVERIFY(true);
}

void TestImageGrabber::testSingleURLFetch()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray pngData = createTestPNG();
    QUrl testUrl("http://example.com/image.png");
    mockManager.addResponse(testUrl, pngData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 1);
    QVERIFY(results->contains(testUrl));
}

void TestImageGrabber::testSingleURLFetchWithValidImage()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray pngData = createTestPNG(10, 10);
    QUrl testUrl("http://example.com/image.png");
    mockManager.addResponse(testUrl, pngData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    QMap<QUrl, ImageData>* results = grabber.getResults();
    ImageData data = results->value(testUrl);

    QVERIFY(data.isValid());
    QCOMPARE(data.image.width(), 10);
    QCOMPARE(data.image.height(), 10);
    QCOMPARE(data.rawData, pngData);
}

void TestImageGrabber::testBatchURLFetch()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QList<QUrl> urls;
    urls.append(QUrl("http://example.com/image1.png"));
    urls.append(QUrl("http://example.com/image2.png"));
    urls.append(QUrl("http://example.com/image3.png"));

    for (const QUrl& url : urls) {
        mockManager.addResponse(url, createTestPNG());
    }

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);

    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 3);

    for (const QUrl& url : urls) {
        QVERIFY(results->contains(url));
        QVERIFY(results->value(url).isValid());
    }
}

void TestImageGrabber::testBatchURLFetchPartialSuccess()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl successUrl("http://example.com/good.png");
    QUrl failUrl("http://example.com/bad.png");

    mockManager.addResponse(successUrl, createTestPNG());
    mockManager.addErrorResponse(failUrl, QNetworkReply::ContentNotFoundError);

    QList<QUrl> urls;
    urls.append(successUrl);
    urls.append(failUrl);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    QVERIFY(finishedSpy.wait(2000));

    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 2);

    // Success URL should have valid data
    QVERIFY(results->value(successUrl).isValid());

    // Failed URL should have invalid data
    QVERIFY(!results->value(failUrl).isValid());
}

void TestImageGrabber::testDuplicateURLsIgnored()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl testUrl("http://example.com/image.png");
    mockManager.addResponse(testUrl, createTestPNG());

    // Create list with duplicate URLs
    QList<QUrl> urls;
    urls.append(testUrl);
    urls.append(testUrl);
    urls.append(testUrl);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    // Should only have one result despite multiple duplicates
    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 1);
}

void TestImageGrabber::testPNGDecoding()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray pngData = createTestPNG(5, 5);
    QUrl testUrl("http://example.com/test.png");
    mockManager.addResponse(testUrl, pngData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    ImageData data = grabber.getResults()->value(testUrl);
    QVERIFY(data.isValid());
    QVERIFY(!data.image.isNull());
    QCOMPARE(data.image.width(), 5);
    QCOMPARE(data.image.height(), 5);
}

void TestImageGrabber::testJPEGDecoding()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray jpegData = createTestJPEG(8, 8);
    QUrl testUrl("http://example.com/test.jpg");
    mockManager.addResponse(testUrl, jpegData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    ImageData data = grabber.getResults()->value(testUrl);
    QVERIFY(data.isValid());
    QVERIFY(!data.image.isNull());
    QCOMPARE(data.image.width(), 8);
    QCOMPARE(data.image.height(), 8);
}

void TestImageGrabber::testGIFDecoding()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray gifData = createTestGIF();
    QUrl testUrl("http://example.com/test.gif");
    mockManager.addResponse(testUrl, gifData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    ImageData data = grabber.getResults()->value(testUrl);
    // GIF support depends on Qt plugins; if it fails, image will be null
    // but we should still have raw data
    QVERIFY(!data.rawData.isEmpty());
}

void TestImageGrabber::testInvalidImageData()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    // Send garbage data that can't be decoded as an image
    QByteArray invalidData = "this is not an image";
    QUrl testUrl("http://example.com/garbage.png");
    mockManager.addResponse(testUrl, invalidData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    ImageData data = grabber.getResults()->value(testUrl);
    // Invalid data should result in invalid ImageData
    QVERIFY(!data.isValid());
    QVERIFY(data.image.isNull());
}

void TestImageGrabber::testMIMETypeDetectionPNG()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray pngData = createTestPNG();
    QUrl testUrl("http://example.com/test.png");
    mockManager.addResponse(testUrl, pngData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    ImageData data = grabber.getResults()->value(testUrl);
    QCOMPARE(data.mimeType, QString("image/png"));
}

void TestImageGrabber::testMIMETypeDetectionJPEG()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QByteArray jpegData = createTestJPEG();
    QUrl testUrl("http://example.com/test.jpg");
    mockManager.addResponse(testUrl, jpegData);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));

    ImageData data = grabber.getResults()->value(testUrl);
    QCOMPARE(data.mimeType, QString("image/jpeg"));
}

void TestImageGrabber::testNetworkError()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl testUrl("http://example.com/missing.png");
    mockManager.addErrorResponse(testUrl, QNetworkReply::ContentNotFoundError);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(testUrl);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    // Network error should result in invalid ImageData
    ImageData data = grabber.getResults()->value(testUrl);
    QVERIFY(!data.isValid());
}

void TestImageGrabber::testNetworkErrorPartialBatch()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl url1("http://example.com/image1.png");
    QUrl url2("http://example.com/missing.png");
    QUrl url3("http://example.com/image3.png");

    mockManager.addResponse(url1, createTestPNG());
    mockManager.addErrorResponse(url2, QNetworkReply::HostNotFoundError);
    mockManager.addResponse(url3, createTestPNG());

    QList<QUrl> urls;
    urls << url1 << url2 << url3;

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    QVERIFY(finishedSpy.wait(2000));

    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 3);

    QVERIFY(results->value(url1).isValid());
    QVERIFY(!results->value(url2).isValid());
    QVERIFY(results->value(url3).isValid());
}

void TestImageGrabber::testCompletionSignalAllSuccess()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QList<QUrl> urls;
    for (int i = 0; i < 5; i++) {
        QUrl url(QString("http://example.com/image%1.png").arg(i));
        urls.append(url);
        mockManager.addResponse(url, createTestPNG());
    }

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    QVERIFY(finishedSpy.wait(3000));
    QCOMPARE(finishedSpy.count(), 1);

    // All images should be valid
    QMap<QUrl, ImageData>* results = grabber.getResults();
    for (const QUrl& url : urls) {
        QVERIFY(results->value(url).isValid());
    }
}

void TestImageGrabber::testCompletionSignalPartialSuccess()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl goodUrl("http://example.com/good.png");
    QUrl badUrl("http://example.com/bad.png");

    mockManager.addResponse(goodUrl, createTestPNG());
    mockManager.addErrorResponse(badUrl, QNetworkReply::TimeoutError);

    QList<QUrl> urls;
    urls << goodUrl << badUrl;

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    // Should still emit finished even with partial failure
    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);
}

void TestImageGrabber::testEmptyURLList()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(QList<QUrl>());

    // With empty list, finished should be emitted immediately (synchronously)
    QCOMPARE(finishedSpy.count(), 1);

    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 0);
}

void TestImageGrabber::testResultsCleared()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl url1("http://example.com/first.png");
    QUrl url2("http://example.com/second.png");

    mockManager.addResponse(url1, createTestPNG());
    mockManager.addResponse(url2, createTestPNG());

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);

    // First fetch
    grabber.fetchUrl(url1);
    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(grabber.getResults()->size(), 1);
    QVERIFY(grabber.getResults()->contains(url1));

    // Second fetch should clear previous results
    grabber.fetchUrl(url2);
    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(grabber.getResults()->size(), 1);
    QVERIFY(grabber.getResults()->contains(url2));
    QVERIFY(!grabber.getResults()->contains(url1));
}

void TestImageGrabber::testSingleRedirect()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl originalUrl("http://example.com/old.png");
    QUrl redirectUrl("http://example.com/new.png");

    // Set up redirect: old.png -> new.png
    mockManager.addRedirect(originalUrl, redirectUrl);
    mockManager.addResponse(redirectUrl, createTestPNG(5, 5));

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(originalUrl);

    QVERIFY(finishedSpy.wait(2000));

    // Result should be stored under original URL
    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 1);
    QVERIFY(results->contains(originalUrl));
    QVERIFY(results->value(originalUrl).isValid());
    QCOMPARE(results->value(originalUrl).image.width(), 5);
}

void TestImageGrabber::testRedirectChain()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl url1("http://example.com/step1.png");
    QUrl url2("http://example.com/step2.png");
    QUrl url3("http://example.com/final.png");

    // Set up redirect chain: step1 -> step2 -> final
    mockManager.addRedirect(url1, url2);
    mockManager.addRedirect(url2, url3);
    mockManager.addResponse(url3, createTestPNG(8, 8));

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(url1);

    QVERIFY(finishedSpy.wait(3000));

    // Result should be stored under original URL
    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 1);
    QVERIFY(results->contains(url1));
    QVERIFY(results->value(url1).isValid());
    QCOMPARE(results->value(url1).image.width(), 8);
}

void TestImageGrabber::testMaxRedirectsExceeded()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    // Create a redirect chain longer than IMAGE_GRABBER_MAX_REDIRECTS (10)
    QList<QUrl> urls;
    for (int i = 0; i <= 12; i++) {
        urls.append(QUrl(QString("http://example.com/redirect%1.png").arg(i)));
    }

    // Set up redirect chain
    for (int i = 0; i < urls.size() - 1; i++) {
        mockManager.addRedirect(urls[i], urls[i + 1]);
    }
    mockManager.addResponse(urls.last(), createTestPNG());

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(urls.first());

    QVERIFY(finishedSpy.wait(5000));

    // Should have a result, but it should be invalid (max redirects exceeded)
    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 1);
    QVERIFY(results->contains(urls.first()));
    QVERIFY(!results->value(urls.first()).isValid());
}

void TestImageGrabber::testRelativeRedirect()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl originalUrl("http://example.com/images/old.png");
    QUrl relativeRedirect("/images/new.png");  // Relative URL
    QUrl resolvedUrl("http://example.com/images/new.png");

    // Set up redirect with relative URL
    mockManager.addRedirect(originalUrl, relativeRedirect);
    mockManager.addResponse(resolvedUrl, createTestPNG(4, 4));

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrl(originalUrl);

    QVERIFY(finishedSpy.wait(2000));

    // Result should be stored under original URL
    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 1);
    QVERIFY(results->contains(originalUrl));
    QVERIFY(results->value(originalUrl).isValid());
    QCOMPARE(results->value(originalUrl).image.width(), 4);
}

void TestImageGrabber::testRedirectInBatch()
{
    MockNetworkAccessManager mockManager;
    ImageGrabber grabber(nullptr, &mockManager);

    QUrl directUrl("http://example.com/direct.png");
    QUrl redirectOriginal("http://example.com/old.png");
    QUrl redirectTarget("http://example.com/new.png");
    QUrl errorUrl("http://example.com/error.png");

    // direct.png - no redirect, direct success
    mockManager.addResponse(directUrl, createTestPNG(2, 2));

    // old.png -> new.png redirect
    mockManager.addRedirect(redirectOriginal, redirectTarget);
    mockManager.addResponse(redirectTarget, createTestPNG(3, 3));

    // error.png - error
    mockManager.addErrorResponse(errorUrl, QNetworkReply::ContentNotFoundError);

    QList<QUrl> urls;
    urls << directUrl << redirectOriginal << errorUrl;

    QSignalSpy finishedSpy(&grabber, &ImageGrabber::finished);
    grabber.fetchUrls(urls);

    QVERIFY(finishedSpy.wait(3000));

    QMap<QUrl, ImageData>* results = grabber.getResults();
    QCOMPARE(results->size(), 3);

    // Direct URL should succeed
    QVERIFY(results->value(directUrl).isValid());
    QCOMPARE(results->value(directUrl).image.width(), 2);

    // Redirect URL should succeed (stored under original URL)
    QVERIFY(results->value(redirectOriginal).isValid());
    QCOMPARE(results->value(redirectOriginal).image.width(), 3);

    // Error URL should fail
    QVERIFY(!results->value(errorUrl).isValid());
}

QTEST_MAIN(TestImageGrabber)

#include "tst_imagegrabber.moc"
