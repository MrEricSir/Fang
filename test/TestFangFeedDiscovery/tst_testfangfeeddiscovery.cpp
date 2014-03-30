#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QCoreApplication>
#include <QUrl>

#include "../../src/utilities/FeedDiscovery.h"

class TestFangFeedDiscovery : public QObject
{
    Q_OBJECT
    
public:
    TestFangFeedDiscovery();
    
private Q_SLOTS:
    void testCase1();
    void testCase1_data();
    
private:
};

TestFangFeedDiscovery::TestFangFeedDiscovery()
{
}

void TestFangFeedDiscovery::testCase1()
{
    QFETCH(QString, url);
    
    FeedDiscovery fd;
    QSignalSpy spy(&fd, SIGNAL(done(FeedDiscovery*)));
    fd.checkFeed(QUrl(url));
    
    // Wait for the signal!
    QVERIFY(spy.wait());  // default: up to 5 seconds
    QCOMPARE(spy.count(), 1);
    
    QVERIFY(!fd.error());
    
    qDebug() << "URL: " << fd.feedURL();
}

void TestFangFeedDiscovery::testCase1_data()
{
    QTest::addColumn<QString>("url");
    
    //QTest::newRow("MrEricSir") << "http://www.mrericsir.com/blog/feed/";  // broken?!
    QTest::newRow("SFist") << "http://feeds.gothamistllc.com/SFist";
    QTest::newRow("SFist Minimal") << "sfist.com";
    QTest::newRow("LaughingSquid Minimal") << "laughingsquid.com";
    QTest::newRow("Fark Minimal") << "fark.com";
}

QTEST_MAIN(TestFangFeedDiscovery)

#include "tst_testfangfeeddiscovery.moc"
