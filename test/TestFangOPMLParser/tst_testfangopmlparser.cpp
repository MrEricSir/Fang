#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QFile>

#include "../../src/parser/OPMLParser.h"


class TestFangOPMLParser : public QObject
{
    Q_OBJECT
    
public:
    TestFangOPMLParser();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

TestFangOPMLParser::TestFangOPMLParser()
{
}

void TestFangOPMLParser::initTestCase()
{
}

void TestFangOPMLParser::cleanupTestCase()
{
}

void TestFangOPMLParser::testCase1()
{
    QFETCH(QString, filename);
    QFETCH(QString, lastTitle);
    QFETCH(QString, lastURL);
    
    OPMLParser parser(this);
    
    QSignalSpy spy(&parser, SIGNAL(done()));
    
    // Parse the file.
    parser.parseFile("../TestFangOPMLParser/opml/" + filename);
    
    // Wait...
    
    // Verify the signal is only emitted once.
    QCOMPARE(spy.count(), 1);
    
    QList<RawFeed*> feedList = parser.getResult();
    QVERIFY2(feedList.size() > 0, "No feeds found. :(");
    
    // Grab the last feed.
    RawFeed* feed = feedList.last();
    
    // Verify our data.
    QCOMPARE(feed->title, lastTitle);
    QCOMPARE(feed->url, QUrl(lastURL));
}

void TestFangOPMLParser::testCase1_data()
{
    //
    // Test parameters go here (don't forget to add the test above!)
    //
    QTest::addColumn<QString>("filename");    // Filename of OPML file to verify.
    QTest::addColumn<QString>("lastTitle");   // Title of the last feed.
    QTest::addColumn<QString>("lastURL");     // URL of last feed.
    
    //
    // Test files go here!
    //
    QTest::newRow("FeedDeemon") << "feeddeemon.opml" << "Mission Mission" << "http://feeds.feedburner.com/MissionMission";
    QTest::newRow("RSSOwl") << "rssowl.opml" << "Mission Mission" << "http://missionmission.org";
}

QTEST_APPLESS_MAIN(TestFangOPMLParser)

#include "tst_testfangopmlparser.moc"
