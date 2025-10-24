#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QSignalSpy>

#include "../../src/utilities/FaviconGrabber.h"

class TestFangFaviconGrabberTest : public QObject
{
    Q_OBJECT
    
public:
    TestFangFaviconGrabberTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

TestFangFaviconGrabberTest::TestFangFaviconGrabberTest()
{
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
    
    FaviconGrabber fg;
    QSignalSpy spy(&fg, SIGNAL(finished(QUrl)));
    fg.find(QUrl(siteURL));
    
    // Wait for the signal!
    QVERIFY(spy.wait(10000));  // Up to 10 seconds
    QCOMPARE(spy.count(), 1);
    
    QList<QVariant> arguments = spy.takeFirst(); // take the first signal
    QCOMPARE(arguments.at(0).toUrl(), faviconURL);
}

void TestFangFaviconGrabberTest::testCase1_data()
{
    QTest::addColumn<QUrl>("siteURL");
    QTest::addColumn<QUrl>("faviconURL");
    
    QTest::newRow("MrEricSir.com") 
            << QUrl("http://www.mrericsir.com/blog/")
            << QUrl("https://www.mrericsir.com/blog/wp-content/uploads/cropped-new-mrericsir-favicon-192x192.png");
    
    QTest::newRow("Fark")
            << QUrl("http://www.fark.com/")
            << QUrl("https://img.fark.net/images/2008/site/fark-webclip.png");
    
    QTest::newRow("Slashdot.org")
                << QUrl("http://slashdot.org/")
                << QUrl("https://slashdot.org/favicon.ico");
    
    QTest::newRow("SFGate.com")
            << QUrl("http://www.sfgate.com/bayarea/feed/Bay-Area-News-429.php")
            << QUrl("https://www.sfgate.com/sites/sfgate/apple-touch-icon-196x196.png");
}

QTEST_MAIN(TestFangFaviconGrabberTest)

#include "tst_testfangfavicongrabbertest.moc"
