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
    QFETCH(bool, isValid);
    
    FeedDiscovery fd;
    QSignalSpy spy(&fd, &FeedDiscovery::done);
    fd.checkFeed(url);
    
    if (!spy.count()) {
        // Wait for the signal!
        QVERIFY(spy.wait(6000));  // Up to 6 seconds
    }

    QCOMPARE(spy.count(), 1);
    
    if (isValid) {
        qDebug() << "URL: " << fd.feedURL();
        qDebug() << "error: " << fd.errorString();
        QVERIFY(!fd.error());
    } else {
        QVERIFY(fd.error());
    }
}

void TestFangFeedDiscovery::testCase1_data()
{
    QTest::addColumn<QString>("url");
    QTest::addColumn<bool>("isValid");
    
    // // Errorz.
    // QTest::newRow("Bullshit URL") << "asfaw3f" << false;
    // QTest::newRow("No RSS feed") << "http://www.google.com" << false;
    
    // // Truly good sites.
    // QTest::newRow("MrEricSir") << "http://www.mrericsir.com/blog/feed/" << true;
    // QTest::newRow("MrEricSir minimal") << "mrericsir.com" << true;
    // QTest::newRow("SFist") << "https://sfist.com/rss/" << true;
    // QTest::newRow("SFist Minimal") << "sfist.com" << true;
    // QTest::newRow("LaughingSquid Minimal") << "laughingsquid.com" << true;
    //QTest::newRow("Fark Minimal") << "fark.com" << true;
    QTest::newRow("yourkickstartersucks") << "yourkickstartersucks.tumblr.com" << true;
}

QTEST_MAIN(TestFangFeedDiscovery)

#include "tst_testfangfeeddiscovery.moc"
