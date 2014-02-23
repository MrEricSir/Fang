#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QNetworkAccessManager>

#include "../../src/parser/Parser.h"

/**
 * @brief Tests a number of RSS feeds I've saved from around the web.  
 */
class TestFangParser : public QObject
{
    Q_OBJECT
    
public:
    TestFangParser();
    
    QNetworkAccessManager manager;
    
private Q_SLOTS:
    void parseTest();
    void parseTest_data();
};

TestFangParser::TestFangParser()
{
}

void TestFangParser::parseTest()
{
    QFETCH(QString, filename);
    QFETCH(QString, title);
    QFETCH(qint32, newsCount);
    QFETCH(QString, firstNewsTitle);
    QFETCH(QString, firstNewsURL);
    
    Parser parser(this, &manager);
    
    QSignalSpy spy(&parser, SIGNAL(done()));
    
    // Parse the file, with a timeout of 1 second.
    parser.parseFile("../TestFangParser/feeds/" + filename);
    
    // Note: at this point the main thread switches to the parser.  We don't need to do
    //       any waiting here because control returns only after emitting the done() signal.
    
    // Verify the signal is only emitted once.
    QCOMPARE(spy.count(), 1);
    
    RawFeed* feed = parser.getFeed();
    QVERIFY2(feed != NULL, "Feed was null");
    
    RawNews* firstNews = feed->items.first();
    
    // Verify our data.
    QCOMPARE(feed->title, title);
    QVERIFY2(feed->items.size() == newsCount, "Incorrect news count");
    QVERIFY2(firstNews->title == firstNewsTitle, "Incorrect first news title");
    QVERIFY2(firstNews->url.toString() == firstNewsURL, "Incorrect first news URL");
}

void TestFangParser::parseTest_data()
{
    //
    // Test parameters go here (don't forget to add the test above!)
    //
    QTest::addColumn<QString>("filename");        // Filename of feed to verify.
    QTest::addColumn<QString>("title");           // Title of news feed.
    QTest::addColumn<qint32>("newsCount");        // Number of news items in the feed.
    QTest::addColumn<QString>("firstNewsTitle");  // Title of first news item.
    QTest::addColumn<QString>("firstNewsURL");    // URL of first news item.
    
    //
    // Test files go here!
    //
    QTest::newRow("MrEricSir") << "mrericsir.com.rss" << "MrEricSir.com" << 10 
                               << "Space reserved for mural" << "http://www.mrericsir.com/blog/local/space-reserved-for-mural/";
    QTest::newRow("Slashdot.org") << "slashdot.org.rss" << "Slashdot" << 25 
                                  << "Internet Shutdown Adds To Venezuela's Woes" << "http://rss.slashdot.org/~r/Slashdot/slashdot/~3/WNpqP5TfVss/story01.htm";
}

QTEST_MAIN(TestFangParser)

#include "tst_fangparser.moc"
