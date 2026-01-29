#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QSignalSpy>
#include <QImage>

#include "../../src/utilities/FaviconGrabber.h"
#include "../MockNetworkAccessManager.h"

class TestFangFaviconGrabberTest : public QObject
{
    Q_OBJECT

public:
    TestFangFaviconGrabberTest();

private:
    // Validate that a string is a valid PNG data URI
    bool isValidPngDataUri(const QString& dataUri);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

TestFangFaviconGrabberTest::TestFangFaviconGrabberTest()
{
}

bool TestFangFaviconGrabberTest::isValidPngDataUri(const QString& dataUri)
{
    // Check prefix
    if (!dataUri.startsWith("data:image/png;base64,")) {
        return false;
    }

    // Extract and decode base64
    QString base64Data = dataUri.mid(QString("data:image/png;base64,").length());
    QByteArray imageData = QByteArray::fromBase64(base64Data.toLatin1());

    // Verify it's a valid image
    QImage image;
    return image.loadFromData(imageData, "PNG");
}

void TestFangFaviconGrabberTest::initTestCase()
{
}

void TestFangFaviconGrabberTest::cleanupTestCase()
{
}

void TestFangFaviconGrabberTest::testCase1()
{
    QFETCH(QUrl, siteURL);
    QFETCH(QUrl, faviconURL);
    QFETCH(QString, mockDataFile);

    // Create mock network manager
    MockNetworkAccessManager mockManager;

    // Load mock HTML response for the site
    QString testDataPath = QString(SRCDIR) + "../testdata/" + mockDataFile;
    mockManager.addResponseFromFile(siteURL, testDataPath);

    // FaviconGrabber also tries to load the host URL (without path) to search for favicons
    QUrl hostUrl = siteURL;
    hostUrl.setPath("");
    mockManager.addResponseFromFile(hostUrl, testDataPath);

    // Mock empty responses for standard favicon URLs that FaviconGrabber checks
    // (FaviconGrabber tries /favicon.ico, /favicon.png, etc. first)
    QStringList extensions = {"ico", "jpg", "jpeg", "png", "gif"};
    for (const QString& ext : extensions) {
        QUrl faviconUrl = hostUrl;
        faviconUrl.setPath("/favicon." + ext);
        mockManager.addResponse(faviconUrl, QByteArray()); // Empty response
    }

    // Mock the actual favicon image URL that will be discovered from the HTML
    // FaviconGrabber needs to successfully download this to verify it exists
    // Create a minimal valid 1x1 PNG (69 bytes)
    QByteArray pngData = QByteArray::fromHex(
        "89504e470d0a1a0a0000000d4948445200000001000000010802000000907753"
        "de0000000c49444154789c63606060000000040001f61738550000000049454e"
        "44ae426082"
    );
    mockManager.addResponse(faviconURL, pngData);

    // Create FaviconGrabber with mock manager
    FaviconGrabber fg(nullptr, &mockManager);
    QSignalSpy spy(&fg, &FaviconGrabber::finished);
    fg.find(QUrl(siteURL));

    // Wait for the signal!
    QVERIFY(spy.wait(10000));  // Up to 10 seconds
    QCOMPARE(spy.count(), 1);

    // Verify we got a valid PNG data URI (favicons are now embedded for offline use)
    QList<QVariant> arguments = spy.takeFirst();
    QString dataUri = arguments.at(0).toString();
    QVERIFY2(isValidPngDataUri(dataUri), "Expected a valid PNG data URI");
}

void TestFangFaviconGrabberTest::testCase1_data()
{
    QTest::addColumn<QUrl>("siteURL");
    QTest::addColumn<QUrl>("faviconURL");
    QTest::addColumn<QString>("mockDataFile");

    QTest::newRow("MrEricSir.com")
            << QUrl("http://www.mrericsir.com/blog/")
            << QUrl("https://www.mrericsir.com/blog/wp-content/uploads/cropped-new-mrericsir-favicon-192x192.png")
            << "mrericsir.com.html";

    QTest::newRow("Fark")
            << QUrl("http://www.fark.com/")
            << QUrl("https://img.fark.net/images/2008/site/fark-webclip.png")
            << "fark.com.html";

    QTest::newRow("Slashdot.org")
                << QUrl("http://slashdot.org/")
                << QUrl("https://slashdot.org/favicon.ico")
                << "slashdot.org.html";

    QTest::newRow("SFGate.com")
            << QUrl("http://www.sfgate.com/bayarea/feed/Bay-Area-News-429.php")
            << QUrl("https://www.sfgate.com/sites/sfgate/apple-touch-icon-196x196.png")
            << "sfgate.com.html";
}

QTEST_MAIN(TestFangFaviconGrabberTest)

#include "tst_testfangfavicongrabbertest.moc"
