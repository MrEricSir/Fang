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
    QFETCH(QDateTime, firstNewsTimestamp);
    
    Parser parser(this);
    
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
    
    // All the times are in UTC; it's easier to set that here for the test cases.
    firstNewsTimestamp.setTimeSpec(Qt::UTC);
    
    // Verify our data.
    QCOMPARE(feed->title, title);
    QCOMPARE(feed->items.size(), newsCount);
    QCOMPARE(firstNews->title, firstNewsTitle);
    QCOMPARE(firstNews->url.toString(), firstNewsURL);
    QCOMPARE(firstNews->timestamp, firstNewsTimestamp);
}

void TestFangParser::parseTest_data()
{
    // Date format example: 01 Feb 2014 01:20:54
    const QString dtf = "dd MMM yyyy hh:mm:ss";
    
    //
    // Test parameters go here (don't forget to add the test above!)
    //
    QTest::addColumn<QString>("filename");             // Filename of feed to verify.
    QTest::addColumn<QString>("title");                // Title of news feed.
    QTest::addColumn<qint32>("newsCount");             // Number of news items in the feed.
    QTest::addColumn<QString>("firstNewsTitle");       // Title of first news item.
    QTest::addColumn<QString>("firstNewsURL");         // URL of first news item.
    QTest::addColumn<QDateTime>("firstNewsTimestamp"); // Time of first news item -- in UTC/GMT
    
    //
    // Test files go here!
    //
    QTest::newRow("MrEricSir") << "mrericsir.com.rss" << "MrEricSir.com" << 10
                               << "Space reserved for mural" 
                               << "http://www.mrericsir.com/blog/local/space-reserved-for-mural/"
                               << QDateTime::fromString("12 Feb 2014 23:04:49", dtf);
    
    QTest::newRow("Slashdot.org") << "slashdot.org.rss" << "Slashdot" << 25
                                  << "Internet Shutdown Adds To Venezuela's Woes" 
                                  << "http://rss.slashdot.org/~r/Slashdot/slashdot/~3/WNpqP5TfVss/story01.htm"
                                  << QDateTime::fromString("23 Feb 2014 03:20:00", dtf);
    
    QTest::newRow("SFist") << "sfist.com.rss" << "SFist" << 25
                                  << "Day Around The Bay: Here Come The Bank Bros"
                                  << "http://feeds.gothamistllc.com/c/35360/f/663259/s/37657c64/sc/8/l/0Lsfist0N0C20A140C0A20C210Cday0Iaround0Ithe0Ibay0I12640Bphp/story01.htm"
                                  << QDateTime::fromString("22 Feb 2014 01:20:54", dtf);
    
    QTest::newRow("The Onion") << "theonion.com.rss" << "The Onion" << 25
                                  << "[video] New Report Shows Record Year For Births Of Test Tube Abominations"
                                  << "http://feedproxy.google.com/~r/theonion/daily/~3/Kll--EhWgv4/story01.htm"
                                  << QDateTime::fromString("21 Feb 2014 21:17:00", dtf);
    
    QTest::newRow("Fark") << "fark.com.rss" << "Fark.com RSS" << 50
                                  << "Oldest known Holocaust survivor and subject of Oscar-nominated documentary dies at age 110 [Sad]"
                                  << "http://www.fark.com/comments/8153957"
                                  << QDateTime::fromString("23 Feb 2014 20:15:11", dtf);
    
    QTest::newRow("Laughing Squid") << "laughingsquid.com.rss" << "Laughing Squid" << 20
                                  << "The Smoking Machine, An Apparatus That Automatically Lights, Smokes, and Tosses Cigarettes on the Ground"
                                  << "http://laughingsquid.com/the-smoking-machine-an-apparatus-that-automatically-lights-smokes-and-tosses-cigarettes-on-the-ground/"
                                  << QDateTime::fromString("23 Feb 2014 19:19:54", dtf);
    
    QTest::newRow("BBC (top) News") << "bbc.co.uk.rss" << "BBC News - Home" << 81
                                  << "Ukraine to seek European integration"
                                  << "http://www.bbc.co.uk/news/world-europe-26317912#sa-ns_mchannel=rss&ns_source=PublicRSS20-sa"
                                  << QDateTime::fromString("24 Feb 2014 01:53:44", dtf);
    
    QTest::newRow("Jimmy") << "zaphos.wordpress.com.rss" << "oh man." << 10
                                  << "Birds birds birds"
                                  << "http://zaphos.wordpress.com/2014/02/15/birds-birds-birds-2/"
                                  << QDateTime::fromString("15 Feb 2014 19:30:44", dtf);
    
    QTest::newRow("The Register") << "theregister.co.uk.atom" << "The Register" << 50
                                  << "Still hanging round: Kim Dotcom extradition hearings delayed"
                                  << "http://go.theregister.com/feed/www.theregister.co.uk/2014/02/25/kim_dotcom_extradition_hearings_delayed/"
                                  << QDateTime::fromString("25 Feb 2014 04:01:10", dtf);
    
    QTest::newRow("SF Weekly") << "sfweekly.com.rss" << "SF Weekly | Complete Issue" << 31
                                  << "\"7 Boxes\": The Things People Transport for Money"
                                  << "http://www.sfweekly.com/2014-02-26/film/7-boxes-film-review/"
                                  << QDateTime::fromString("26 Feb 2014 08:00:00", dtf);
    
    QTest::newRow("People.com.cn Sports") << "sports.people.com.cn.rss" << " 体育新闻 " << 50
                                  << " 女足出征阿尔加夫杯 年轻队伍获得锻炼良机 "
                                  << "http://sports.people.com.cn/n/2014/0227/c22176-24479799.html"
                                  << QDateTime::fromString("27 Feb 2014 10:15:06", dtf);
    
    QTest::newRow("Economist Science & Tech") << "science.economist.com.rss" << "The Economist: Science and technology" << 20
                                  << "Climate change: Jet set"
                                  << "http://www.economist.com/news/science-and-technology/21596920-polar-warming-blame-americas-and-britains-bad-winter-weather-jet-set?fsrc=rss%7Csct"
                                  << QDateTime::fromString("20 Feb 2014 15:58:34", dtf);
    
    QTest::newRow("NPR News") << "npr.org.rss" << "News" << 15
                                  << "First Look: The FDA's Nutrition Label Gets A Makeover "
                                  << "http://www.npr.org/blogs/thesalt/2014/02/27/283055089/first-look-the-fdas-nutrition-label-gets-a-makeover?ft=1&f=1001"
                                  << QDateTime::fromString("27 Feb 2014 05:02:00", dtf);
    
    QTest::newRow("Smoking Gun") << "thesmokinggun.com.rss" << "The Smoking Gun RSS" << 50
                                  << "\"Breaking Bad\" Fan Collared In Meth Bust"
                                  << "http://www.thesmokinggun.com/documents/meth-dealer-breaking-bad-shirt-687432"
                                  << QDateTime::fromString("26 Feb 2014 17:33:51", dtf);
    
    QTest::newRow("Lifehacker") << "lifehacker.com.rss" << "Lifehacker" << 25
                                  << "Paperwhite Tricks, Touchpad Settings, and Flashcards"
                                  << "http://feeds.gawker.com/~r/lifehacker/full/~3/437hNRKLh6s/paperwhite-tricks-touchpad-settings-and-flashcards-1531994358"
                                  << QDateTime::fromString("27 Feb 2014 01:00:00", dtf);
    
    QTest::newRow("MissionMission") << "missionmission.feedburner.rss" << "Mission Mission" << 15
                                  << "Candy Winters on the Google Glass controversy"
                                  << "http://feedproxy.google.com/~r/MissionMission/~3/g7sOB4s2Mwo/"
                                  << QDateTime::fromString("27 Feb 2014 01:31:39", dtf);
    
    QTest::newRow("Uptown Almanac") << "uptownalmanac.com.rss" << "Uptown Almanac" << 50
                                  << "How to Know When You Can Call the Cops on a Glasshole"
                                  << "http://uptownalmanac.com/2014/02/how-know-when-you-can-call-cops-glasshole"
                                  << QDateTime::fromString("26 Feb 2014 23:44:00", dtf);
    
    QTest::newRow("Mirror") << "mirror.co.uk.rss" << "mirror - Home" << 25
                                  << "Arturo Licata crowned world's oldest living man - aged 111 years 302 days"
                                  << "http://www.mirror.co.uk/news/world-news/arturo-licata-crowned-worlds-oldest-3190842"
                                  << QDateTime::fromString("28 Feb 2014 02:27:38", dtf);
    
    QTest::newRow("dongA") << "donga.com.rss" << "동아닷컴 : 동아일보 전체 뉴스" << 50
                                  << "[NBA] 필라델피아, 아이버슨 등번호 ‘3번’ 영구결번"
                                  << "http://news.donga.com/3/all/20140228/61275241/1"
                                  << QDateTime::fromString("28 Feb 2014 03:13:00", dtf);
}

QTEST_MAIN(TestFangParser)

#include "tst_fangparser.moc"
