#include <QString>
#include <QtTest>
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
    QVERIFY(spy.wait());  // default: up to 5 seconds
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
            << QUrl("http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico");
    
    QTest::newRow("MissionMission.org")
            << QUrl("http://www.missionmission.org")
            << QUrl("http://www.missionmission.org/wp-content/uploads/2012/09/favicon2.ico");
    
    QTest::newRow("Slashdot.org")
                << QUrl("http://slashdot.org/")
                << QUrl("http://slashdot.org/favicon.ico");
    
    QTest::newRow("SFGate.com")
            << QUrl("http://www.sfgate.com/bayarea/feed/Bay-Area-News-429.php")
            << QUrl("http://www.sfgate.com/apple-touch-icon-152x152.png");
}

QTEST_MAIN(TestFangFaviconGrabberTest)

#include "tst_testfangfavicongrabbertest.moc"
