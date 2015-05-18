#include <QString>
#include <QtTest>
#include <QSignalSpy>

#include "../../src/utilities/WebPageGrabber.h"

#define TIDY_HEADER "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\r\n" \
                    "    \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n" \
                    "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n" \
                    "<head>\r\n" \
                    "<meta name=\"generator\" content=\r\n" \
                    "\"HTML Tidy for Windows (vers 13 April 2006), see www.w3.org\" />\r\n" \
                    "<title></title>\r\n" \
                    "</head>\r\n" \
                    "<body>\r\n"

#define TIDY_FOOTER "</body>\r\n</html>\r\n";

class TestWebPageGrabber : public QObject
{
    Q_OBJECT

public:
    TestWebPageGrabber();

private Q_SLOTS:
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

    //qDebug() << "Expected output: " << expectedOutput;
    //qDebug() << "Actual Output: " << actualOutput;

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
                                        "<p>just some simple <em>HTML</em>!</p>\r\n"
                                        TIDY_FOOTER;

    QTest::newRow("Fix bad HTML") << "<div><b>bold"
                                  << TIDY_HEADER
                                     "<div><b>bold</b></div>\r\n"
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

    WebPageGrabber grabber(true, 2000);
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
        QVERIFY(document == NULL);
    }
}

void TestWebPageGrabber::testCase2_data()
{
    QTest::addColumn<QUrl>("url");
    QTest::addColumn<bool>("reallyExists");

    QTest::newRow("Bad URL") << QUrl("e")
                           << false;

    QTest::newRow("Nope.") << QUrl("http://safjdsafalskdfjasdlf")
                           << false;

    QTest::newRow("Google") << QUrl("https://www.google.com/")
                           << true;
}


QTEST_MAIN(TestWebPageGrabber)

#include "tst_testwebpagegrabber.moc"
