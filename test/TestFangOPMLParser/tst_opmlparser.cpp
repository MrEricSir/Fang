#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QFile>

#include "../../src/parser/OPMLParser.h"


class TestOPMLParser : public QObject
{
    Q_OBJECT
    
public:
    TestOPMLParser();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

TestOPMLParser::TestOPMLParser()
{
}

void TestOPMLParser::initTestCase()
{
}

void TestOPMLParser::cleanupTestCase()
{
}

void TestOPMLParser::testCase1()
{
    QFETCH(QString, filename);
    QFETCH(qint32, numFeeds);
    QFETCH(QString, lastTitle);
    QFETCH(QString, lastURL);
    
    OPMLParser parser(this);

    QSignalSpy spy(&parser, SIGNAL(done()));

    // Parse the file (as a synchronous operation)
    parser.parseFile(QString(SRCDIR) + "opml/" + filename);

    // Verify the signal was emitted once
    QCOMPARE(spy.count(), 1);
    
    QList<RawFeed*> feedList = parser.getFeedList();
    QVERIFY2(feedList.size() > 0, "No feeds found. :(");
    
    // Grab the last feed.
    RawFeed* feed = feedList.last();
    
    // Verify our data.
    QCOMPARE(feedList.size(), numFeeds);
    QCOMPARE(feed->title, lastTitle);
    QCOMPARE(feed->url, QUrl(lastURL));
}

void TestOPMLParser::testCase1_data()
{
    //
    // Test parameters go here (don't forget to add the test above!)
    //
    QTest::addColumn<QString>("filename");    // Filename of OPML file to verify.
    QTest::addColumn<qint32>("numFeeds");   // Title of the last feed.
    QTest::addColumn<QString>("lastTitle");   // Title of the last feed.
    QTest::addColumn<QString>("lastURL");     // URL of last feed.
    
    //
    // Test files go here!
    //
    QTest::newRow("FeedDeemon") << "feeddeemon.opml" << 3 << "Mission Mission" << "http://feeds.feedburner.com/MissionMission";
    QTest::newRow("RSSOwl") << "rssowl.opml" << 3 << "Mission Mission" << "http://missionmission.org";
    QTest::newRow("Feedly") << "feedly.opml" << 3 << "Mission Mission" << "http://missionmission.wordpress.com/feed/";
    QTest::newRow("Fang") << "fang.opml" << 3 << "Mission Mission" << "http://feeds.feedburner.com/MissionMission";
}

QTEST_MAIN(TestOPMLParser)

#include "tst_opmlparser.moc"
