#include <QString>
#include <QTest>
#include <QSignalSpy>

#include "../../src/utilities/WebPageGrabber.h"
#include "../MockNetworkAccessManager.h"

#ifdef _WIN32
#define PLATFORM_TIDY "\"HTML Tidy for Windows (vers 13 April 2006), see www.w3.org\""
#elif __APPLE__
#define PLATFORM_TIDY "\"HTML Tidy for Mac OS X (vers 13 April 2006), see www.w3.org\""
#endif


#define TIDY_HEADER "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n" \
                    "    \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n" \
                    "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n" \
                    "<head>\n" \
                    "<meta name=\"generator\" content=\n" \
                    PLATFORM_TIDY \
                    " />\n" \
                    "<title></title>\n" \
                    "</head>\n" \
                    "<body>\n"

#define TIDY_FOOTER "</body>\n</html>\n";


class TestWebPageGrabber : public QObject
{
    Q_OBJECT

public:
    TestWebPageGrabber();

private slots:
    void testCase1_data();
    void testCase1();

    void testCase2_data();
    void testCase2();
};

TestWebPageGrabber::TestWebPageGrabber()
{
}

/**
 * Test 1: Load some raw HTML
 */

void TestWebPageGrabber::testCase1()
{
    QFETCH(QString, html);
    QFETCH(QString, expectedOutput);

    WebPageGrabber grabber;
    QString actualOutput = *grabber.load(html);
    actualOutput.replace("\r\n", "\n"); // Normalize so we can run on Mac & Win with same results

    qDebug() << "Expected output: " << expectedOutput;
    qDebug() << "Actual Output: " << actualOutput;

    // How does the actual output compare?
    QCOMPARE(expectedOutput, actualOutput);
}

void TestWebPageGrabber::testCase1_data()
{
    QTest::addColumn<QString>("html");
    QTest::addColumn<QString>("expectedOutput");

    QTest::newRow("Empty") << ""
                           << TIDY_HEADER
                              TIDY_FOOTER;

    QTest::newRow("Some simple HTML") << "<p>just some simple <em>HTML</em>!</p>"
                                      << TIDY_HEADER
                                        "<p>just some simple <em>HTML</em>!</p>\n"
                                        TIDY_FOOTER;

    QTest::newRow("Fix bad HTML") << "<div><b>bold"
                                  << TIDY_HEADER
                                     "<div><b>bold</b></div>\n"
                                     TIDY_FOOTER;
}

/**
 * Test 2: Fetch some web pages from files and the internets.
 *         We're only going to verify that we got a page.
 */

void TestWebPageGrabber::testCase2()
{
    QFETCH(QUrl, url);
    QFETCH(bool, reallyExists);
    QFETCH(QString, mockDataFile);

    // Create mock network manager
    MockNetworkAccessManager mockManager;

    // Load mock HTML response if expected to exist
    if (reallyExists && !mockDataFile.isEmpty()) {
        QString testDataPath = QString(SRCDIR) + "../testdata/" + mockDataFile;
        mockManager.addResponseFromFile(url, testDataPath);
    }

    WebPageGrabber grabber(true, 2000, nullptr, &mockManager);
    QSignalSpy spy(&grabber, &WebPageGrabber::ready); // Ignore meta-type warnings here, please.
    grabber.load(url);

    if (!spy.count()) {
        // Wait up to 5 seconds for signal to fire.
        QVERIFY(spy.wait());
    }

    QCOMPARE(spy.count(), 1);

    // Check out results.
    QString* document = grabber.getDocument();

    if (reallyExists) {
        QVERIFY(document);
    } else {
        // Make sure we got nothin' back.
        QVERIFY(document == nullptr);
    }
}

void TestWebPageGrabber::testCase2_data()
{
    QTest::addColumn<QUrl>("url");
    QTest::addColumn<bool>("reallyExists");
    QTest::addColumn<QString>("mockDataFile");

    QTest::newRow("Bad URL") << QUrl("e")
                           << false
                           << "";

    QTest::newRow("Nope.") << QUrl("http://safjdsafalskdfjasdlf")
                           << false
                           << "";

    QTest::newRow("Google") << QUrl("https://www.google.com/")
                            << true
                            << "google.com.html";
}


QTEST_MAIN(TestWebPageGrabber)

#include "tst_testwebpagegrabber.moc"
