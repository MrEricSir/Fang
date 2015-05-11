#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QNetworkAccessManager>

#include "../../src/parser/NewsParser.h"

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
    QFETCH(QString, guid);
    QFETCH(QDateTime, firstNewsTimestamp);
    
    NewsParser parser(this);
    
    QSignalSpy spy(&parser, SIGNAL(done()));
    
    // Parse the file, with a timeout of 1 second.
    parser.parseFile("../TestFangParser/feeds/" + filename);
    
    // We *may* need to wait here.
    spy.wait(500); // Lame, but just wait 500 ms
    
    // Verify the signal is only emitted once.
    QCOMPARE(spy.count(), 1);
    
    RawFeed* feed = parser.getFeed();
    QVERIFY2(feed != NULL, "Feed was null");
    
    // Check all dates in the feed for validity, as this is a common issue.
    foreach (RawNews* newsItem, feed->items) {
        QVERIFY2(newsItem->timestamp.isValid(), "Invalid timestamp.");
    }
    
    RawNews* firstNews = feed->items.first();
    
    // All the times are in UTC; it's easier to set that here for the test cases.
    firstNewsTimestamp.setTimeSpec(Qt::UTC);
    
    // Verify our data.
    QCOMPARE(feed->title, title);
    QCOMPARE(feed->items.size(), newsCount);
    QCOMPARE(firstNews->title, firstNewsTitle);
    QCOMPARE(firstNews->url.toString(), firstNewsURL);
    QCOMPARE(firstNews->guid, guid);
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
    QTest::addColumn<QString>("guid");         // GUID of first news item.
    QTest::addColumn<QDateTime>("firstNewsTimestamp"); // Time of first news item -- in UTC/GMT

    //
    // Test files go here!
    //
    QTest::newRow("MrEricSir") << "mrericsir.com.rss" << "MrEricSir.com" << 10
                               << "Space reserved for mural" 
                               << "http://www.mrericsir.com/blog/local/space-reserved-for-mural/"
                               << "http://www.mrericsir.com/blog/?p=2831"
                               << QDateTime::fromString("12 Feb 2014 23:04:49", dtf);
    
    QTest::newRow("Slashdot.org") << "slashdot.org.rss" << "Slashdot" << 25
                                  << "Internet Shutdown Adds To Venezuela's Woes" 
                                  << "http://rss.slashdot.org/~r/Slashdot/slashdot/~3/WNpqP5TfVss/story01.htm"
                                  << "http://slashdot.feedsportal.com/c/35028/f/647410/s/376c3d57/sc/24/l/0Lyro0Bslashdot0Borg0Cstory0C140C0A20C230C0A2152130Cinternet0Eshutdown0Eadds0Eto0Evenezuelas0Ewoes0Dutm0Isource0Frss10B0Amainlinkanon0Gutm0Imedium0Ffeed/story01.htm"
                                  << QDateTime::fromString("23 Feb 2014 03:20:00", dtf);
    
    QTest::newRow("SFist") << "sfist.com.rss" << "SFist" << 25
                                  << "Day Around The Bay: Here Come The Bank Bros"
                                  << "http://feeds.gothamistllc.com/c/35360/f/663259/s/37657c64/sc/8/l/0Lsfist0N0C20A140C0A20C210Cday0Iaround0Ithe0Ibay0I12640Bphp/story01.htm"
                                  << "http://sfist.com/2014/02/21/day_around_the_bay_1264.php"
                                  << QDateTime::fromString("22 Feb 2014 01:20:54", dtf);
    
    QTest::newRow("The Onion") << "theonion.com.rss" << "The Onion" << 25
                                  << "[video] New Report Shows Record Year For Births Of Test Tube Abominations"
                                  << "http://feedproxy.google.com/~r/theonion/daily/~3/Kll--EhWgv4/story01.htm"
                                  << "http://www.theonion.com/video/new-report-shows-record-year-for-births-of-test-tu,35348/"
                                  << QDateTime::fromString("21 Feb 2014 21:17:00", dtf);
    
    QTest::newRow("Fark") << "fark.com.rss" << "Fark.com RSS" << 50
                                  << "Oldest known Holocaust survivor and subject of Oscar-nominated documentary dies at age 110 [Sad]"
                                  << "http://www.fark.com/comments/8153957"
                                  << "http://www.fark.com/comments/8153957"
                                  << QDateTime::fromString("23 Feb 2014 20:15:11", dtf);
    
    QTest::newRow("Laughing Squid") << "laughingsquid.com.rss" << "Laughing Squid" << 20
                                  << "The Smoking Machine, An Apparatus That Automatically Lights, Smokes, and Tosses Cigarettes on the Ground"
                                  << "http://laughingsquid.com/the-smoking-machine-an-apparatus-that-automatically-lights-smokes-and-tosses-cigarettes-on-the-ground/"
                                  << "http://laughingsquid.com/?p=375849"
                                  << QDateTime::fromString("23 Feb 2014 19:19:54", dtf);
    
    QTest::newRow("BBC (top) News") << "bbc.co.uk.rss" << "BBC News - Home" << 81
                                  << "Ukraine to seek European integration"
                                  << "http://www.bbc.co.uk/news/world-europe-26317912#sa-ns_mchannel=rss&ns_source=PublicRSS20-sa"
                                  << "http://www.bbc.co.uk/news/world-europe-26317912"
                                  << QDateTime::fromString("24 Feb 2014 01:53:44", dtf);
    
    QTest::newRow("Jimmy") << "zaphos.wordpress.com.rss" << "oh man." << 10
                                  << "Birds birds birds"
                                  << "http://zaphos.wordpress.com/2014/02/15/birds-birds-birds-2/"
                                  << "http://zaphos.wordpress.com/?p=1422"
                                  << QDateTime::fromString("15 Feb 2014 19:30:44", dtf);
    
    QTest::newRow("The Register") << "theregister.co.uk.atom" << "The Register" << 50
                                  << "Still hanging round: Kim Dotcom extradition hearings delayed"
                                  << "http://go.theregister.com/feed/www.theregister.co.uk/2014/02/25/kim_dotcom_extradition_hearings_delayed/"
                                  << "tag:theregister.co.uk,2005:story/2014/02/25/kim_dotcom_extradition_hearings_delayed/"
                                  << QDateTime::fromString("25 Feb 2014 04:01:10", dtf);
    
    QTest::newRow("SF Weekly") << "sfweekly.com.rss" << "SF Weekly | Complete Issue" << 31
                                  << "\"7 Boxes\": The Things People Transport for Money"
                                  << "http://www.sfweekly.com/2014-02-26/film/7-boxes-film-review/"
                                  << "http://www.sfweekly.com/2014-02-26/film/7-boxes-film-review/"
                                  << QDateTime::fromString("26 Feb 2014 08:00:00", dtf);
    
    QTest::newRow("People.com.cn Sports") << "sports.people.com.cn.rss" << " 体育新闻 " << 50
                                  << " 女足出征阿尔加夫杯 年轻队伍获得锻炼良机 "
                                  << "http://sports.people.com.cn/n/2014/0227/c22176-24479799.html"
                                  << "http://sports.people.com.cn/n/2014/0227/c22176-24479799.html"
                                  << QDateTime::fromString("27 Feb 2014 10:15:06", dtf);
    
    QTest::newRow("Economist Science & Tech") << "science.economist.com.rss" << "The Economist: Science and technology" << 20
                                  << "Climate change: Jet set"
                                  << "http://www.economist.com/news/science-and-technology/21596920-polar-warming-blame-americas-and-britains-bad-winter-weather-jet-set?fsrc=rss%7Csct"
                                  << "http://www.economist.com/news/science-and-technology/21596920-polar-warming-blame-americas-and-britains-bad-winter-weather-jet-set"
                                  << QDateTime::fromString("20 Feb 2014 15:58:34", dtf);
    
    QTest::newRow("NPR News") << "npr.org.rss" << "News" << 15
                                  << "First Look: The FDA's Nutrition Label Gets A Makeover "
                                  << "http://www.npr.org/blogs/thesalt/2014/02/27/283055089/first-look-the-fdas-nutrition-label-gets-a-makeover?ft=1&f=1001"
                                  << "http://www.npr.org/blogs/thesalt/2014/02/27/283055089/first-look-the-fdas-nutrition-label-gets-a-makeover?ft=1&f=1001"
                                  << QDateTime::fromString("27 Feb 2014 05:02:00", dtf);
    
    QTest::newRow("Smoking Gun") << "thesmokinggun.com.rss" << "The Smoking Gun RSS" << 50
                                  << "\"Breaking Bad\" Fan Collared In Meth Bust"
                                  << "http://www.thesmokinggun.com/documents/meth-dealer-breaking-bad-shirt-687432"
                                  << "208585 at http://www.thesmokinggun.com"
                                  << QDateTime::fromString("26 Feb 2014 17:33:51", dtf);
    
    QTest::newRow("Lifehacker") << "lifehacker.com.rss" << "Lifehacker" << 25
                                  << "Paperwhite Tricks, Touchpad Settings, and Flashcards"
                                  << "http://feeds.gawker.com/~r/lifehacker/full/~3/437hNRKLh6s/paperwhite-tricks-touchpad-settings-and-flashcards-1531994358"
                                  << "1531994358"
                                  << QDateTime::fromString("27 Feb 2014 01:00:00", dtf);
    
    QTest::newRow("MissionMission") << "missionmission.feedburner.rss" << "Mission Mission" << 15
                                  << "Candy Winters on the Google Glass controversy"
                                  << "http://feedproxy.google.com/~r/MissionMission/~3/g7sOB4s2Mwo/"
                                  << "http://www.missionmission.org/?p=52521"
                                  << QDateTime::fromString("27 Feb 2014 01:31:39", dtf);
    
    QTest::newRow("Uptown Almanac") << "uptownalmanac.com.rss" << "Uptown Almanac" << 50
                                  << "How to Know When You Can Call the Cops on a Glasshole"
                                  << "http://uptownalmanac.com/2014/02/how-know-when-you-can-call-cops-glasshole"
                                  << "8803 at http://uptownalmanac.com"
                                  << QDateTime::fromString("26 Feb 2014 23:44:00", dtf);
    
    QTest::newRow("Mirror") << "mirror.co.uk.rss" << "mirror - Home" << 25
                                  << "Arturo Licata crowned world's oldest living man - aged 111 years 302 days"
                                  << "http://www.mirror.co.uk/news/world-news/arturo-licata-crowned-worlds-oldest-3190842"
                                  << "http://www.mirror.co.uk/news/world-news/arturo-licata-crowned-worlds-oldest-3190842"
                                  << QDateTime::fromString("28 Feb 2014 02:27:38", dtf);
    
    QTest::newRow("dongA") << "donga.com.rss" << "동아닷컴 : 동아일보 전체 뉴스" << 50
                                  << "[NBA] 필라델피아, 아이버슨 등번호 ‘3번’ 영구결번"
                                  << "http://news.donga.com/3/all/20140228/61275241/1"
                                  << "http://news.donga.com/3/all/20140228/61275241/1"
                                  << QDateTime::fromString("28 Feb 2014 03:13:00", dtf);
    
    QTest::newRow("LokMat") << "lokmat.com.rss" << "Lokmat Marathi News : Main-Main (मुख्य-मुख्य)" << 38
                                  << "मंत्री वगळले, घोटाळे मांडले"
                                  << "http://onlinenews1.lokmat.com/dailynews/2014-03-02/MainEdition-1-1-02-03-2014-9152a/main.php"
                                  << "http://onlinenews1.lokmat.com/dailynews/2014-03-02/MainEdition-1-1-02-03-2014-9152a/main.php"
                                  << QDateTime::fromString("02 Mar 2014 00:56:28", dtf);
    
    QTest::newRow("The Hindu") << "thehindu.com.rss" << "The Hindu - News" << 225
                                  << "Modi choice may deny Advani Gandhinagar"
                                  << "http://www.thehindu.com/news/national/modi-choice-may-deny-advani-gandhinagar/article5741440.ece"
                                  << "http://www.thehindu.com/news/national/modi-choice-may-deny-advani-gandhinagar/article5741440.ece"
                                  << QDateTime::fromString("01 Mar 2014 21:02:01", dtf);
    
    QTest::newRow("TH Daily News") << "dailynews.co.th.rss" << "เดลินิวส์ - อ่านความจริง อ่านเดลินิวส์" << 10
                                  << "เว็บบ์ยังนำสวิงเอชเอสบีซี"
                                  << "http://www.dailynews.co.th/Content.do?contentId=219811"
                                  << "219811 at http://www.dailynews.co.th/"
                                  << QDateTime::fromString("01 Mar 2014 21:05:00", dtf);
    
    QTest::newRow("Krone") << "krone.at.rss" << "Krone.at - Nachrichten" << 35
                                  << "Russische Truppen kassieren die ukrainische Krim"
                                  << "http://www.krone.at/Nachrichten/Russische_Truppen_kassieren_die_ukrainische_Krim-Kriegsangst_waechst-Story-395414?utm_source=krone.at&utm_medium=RSS-Feed&utm_campaign=Nachrichten"
                                  << "http://www.krone.at/Nachrichten/Russische_Truppen_kassieren_die_ukrainische_Krim-Kriegsangst_waechst-Story-395414?utm_source=krone.at&utm_medium=RSS-Feed&utm_campaign=Nachrichten"
                                  << QDateTime::fromString("01 Mar 2014 19:56:27", dtf);
    
    QTest::newRow("Ouest-France") << "ouest-france.fr.rss" << "Ouest-France - Actualité" << 17
                                  << "Ukraine. Menaces de la Russie, l'armée ukrainienne en état d'alerte"
                                  << "http://www.ouest-france.fr/ukraine-suivez-les-evenements-de-ce-samedi-en-direct-1970380"
                                  << "http://www.ouest-france.fr/node/1970380"
                                  << QDateTime::fromString("01 Mar 2014 19:21:00", dtf);
    
    QTest::newRow("Hryx's Github") << "github.hryx.atom" << "hryx's Activity" << 30
                                  << "hryx commented on issue MrEricSir/Modipulate#60"
                                  << "https://github.com/MrEricSir/Modipulate/issues/60#issuecomment-36418854"
                                  << "tag:github.com,2008:IssueCommentEvent/1999031035"
                                  << QDateTime::fromString("01 Mar 2014 07:43:19", dtf);
    
    QTest::newRow("KP.ru") << "life.kp.ru.rss" << "KP.RU :: Общество" << 9
                                  << "Навального заключили под домашний арест"
                                  << "http://www.kp.ru/daily/26200/3087261/"
                                  << "http://www.kp.ru/daily/26200/3087261/"
                                  << QDateTime::fromString("28 Feb 2014 10:12:00", dtf);
    
    QTest::newRow("Yomiuri") << "yomiuri.co.jp.rss" << "YOMIURI ONLINE（読売新聞）主要ニュース" << 7
                                  << "ウクライナ軍事介入へ…露大統領提案、上院承認"
                                  << "http://rss.rssad.jp/rss/artclk/z0r9SvPmQy3H/4e9b00c230a30acc524b87cfb96a1bdf?ul=dTEkp0Q.3xQ0ioSSaARBwAjEz8VQ1gEH0sy7bPSX_q8UznMPrZFmLTGR9aXbjLSM8qt3_FOOWUtVeDP_oFQdpBUFfLqOYXwcTPjvcXUmcNM7aD2J."
                                  << "yomiuri.co.jp/20140301-OYT1T00816"
                                  << QDateTime::fromString("01 Mar 2014 16:44:21", dtf);
    
    QTest::newRow("Times of India Sports") << "sports.timesofindia.com.rss" << "The Times of India Sports: Extensive sports coverage, key statistics and free downloads" << 25
                                  << "Indo-Pak Express kicks up desert storm"
                                  << "http://timesofindia.feedsportal.com/c/33039/f/533921/s/37ad9914/sc/13/l/0Ltimesofindia0Bindiatimes0N0Csports0Ctennis0Ctop0Estories0CIndo0EPak0EExpress0Ekicks0Eup0Edesert0Estorm0Carticleshow0C312375150Bcms/story01.htm"
                                  << "http://timesofindia.indiatimes.com/sports/tennis/top-stories/Indo-Pak-Express-kicks-up-desert-storm/articleshow/31237515.cms"
                                  << QDateTime::fromString("01 Mar 2014 20:15:17", dtf);
    
    QTest::newRow("Chosun") << "chosun.com.rss" << "조선닷컴 : 전체기사" << 25
                                  << "中 92세 가정부, 주인집에서 안락한 노후…3대 잘 돌본 공로 인정"
                                  << "http://chosun.feedsportal.com/c/34674/f/636753/s/37adf5df/l/0Lnews0Bchosun0N0Csite0Cdata0Chtml0Idir0C20A140C0A30C0A20C20A140A30A20A0A0A570Bhtml/story01.htm"
                                  << "http://chosun.feedsportal.com/c/34674/f/636753/s/37adf5df/l/0Lnews0Bchosun0N0Csite0Cdata0Chtml0Idir0C20A140C0A30C0A20C20A140A30A20A0A0A570Bhtml/story01.htm"
                                  << QDateTime::fromString("01 Mar 2014 21:45:25", dtf);
    
    QTest::newRow("Asahi") << "asahi.com.rss" << "朝日新聞デジタル" << 49
                                  << "（ビキニ６０年）島民診療支える広島・長崎の経験"
                                  << "http://www.asahi.com/articles/ASG2W41VRG2WPTIL00R.html?ref=rss"
                                  << "http://www.asahi.com/articles/ASG2W41VRG2WPTIL00R.html?ref=rss"
                                  << QDateTime::fromString("01 Mar 2014 20:49:59", dtf);
    
    QTest::newRow("YouTube") << "youtube.com.rss" << "Uploads by The Onion" << 25
                                  << "Members Of Academy Can't Imagine What Would Happen If They Ever Selected Wrong Best Picture"
                                  << "http://www.youtube.com/watch?v=j3v35HcyEyI&feature=youtube_gdata"
                                  << "tag:youtube.com,2008:video:j3v35HcyEyI"
                                  << QDateTime::fromString("28 Feb 2014 20:52:26", dtf);
    
    QTest::newRow("Bild") << "bild.de.rss" << "Bild.de Home" << 62
                                  << "Ösi-„Tatort“ - „Wir haben den Hang zum Abgründigen“"
                                  << "http://www.bild.de/unterhaltung/tv/tatort/interview-mit-harald-krassnitzer-zum-tatort-abgruende-34902678.bild.html"
                                  << "http://www.bild.de/unterhaltung/tv/tatort/interview-mit-harald-krassnitzer-zum-tatort-abgruende-34902678.bild.html"
                                  << QDateTime::fromString("02 Mar 2014 20:57:50", dtf);
    
    QTest::newRow("Perez Hilton") << "perezhilton.com.rss" << "PerezHilton" << 10
                                  << "Once In A Blue Moon! Beck Performs On Saturday Night Live & Brings A Friend!"
                                  << "http://perezhilton.com/2014-03-02-beck-performs-saturday-night-live-blue-moon-and-wave"
                                  << "http://perezhilton.com/2014-03-02-beck-performs-saturday-night-live-blue-moon-and-wave"
                                  << QDateTime::fromString("02 Mar 2014 23:00:30", dtf);
    
    QTest::newRow("TMZ") << "tmz.com.rss" << "TMZ.com" << 20
                                  << "Academy Awards -- Weed Biz Booming ... With Oscar Partying Celebs"
                                  << "http://www.tmz.com/2014/03/02/academy-awards-weed-dispensary-deliver-oscars-party-celebs/"
                                  << "http://www.tmz.com/2014/03/02/academy-awards-weed-dispensary-deliver-oscars-party-celebs/"
                                  << QDateTime::fromString("02 Mar 2014 23:02:00", dtf);
    
    QTest::newRow("E") << "eonline.com.rss" << "E! Online (US) - Top Stories" << 20
                                  << "Debby Ryan Preps for 2014 Oscars Night Wearing Custom Gown--See the Pics!"
                                  << "http://www.eonline.com/news/516429/debby-ryan-preps-for-2014-oscars-night-wearing-custom-gown-see-the-pics?cmpid=rss-000000-rssfeed-365-topstories&utm_source=eonline&utm_medium=rssfeeds&utm_campaign=rss_topstories"
                                  << "b516429"
                                  << QDateTime::fromString("02 Mar 2014 22:48:00", dtf);
    
    QTest::newRow("Popsugar") << "popsugar.com.rss" << "POPSUGAR Celebrity" << 25
                                  << "The Stars Come Out For the Oscars Red Carpet!"
                                  << "http://www.popsugar.com/Celebrities-Oscars-Red-Carpet-2014-Pictures-34170716"
                                  << "34170716"
                                  << QDateTime::fromString("02 Mar 2014 15:07:31", dtf);
    
    QTest::newRow("Mashable") << "mashable.com.rss" << "Mashable" << 30
                                  << "Live Updates: The Oscars"
                                  << "http://feeds.mashable.com/~r/Mashable/~3/Pm6OrtL9p1o/"
                                  << "http://mashable.com/?p=2450301"
                                  << QDateTime::fromString("02 Mar 2014 23:15:10", dtf);
    
    QTest::newRow("Planet Gnome") << "planetgnome.atom" << "Planet GNOME" << 40
                                  << "Trip to San Jose GSoC 10 Year Reunion: Help!"
                                  << "http://feedproxy.google.com/~r/thismagpie/GNOME/~3/ywMHj6HEfok/trip-to-san-jose-gsoc-10-year-reunion.html"
                                  << "tag:blogger.com,1999:blog-2577584421986216597.post-2544334569132980889"
                                  << QDateTime::fromString("01 Jul 2014 22:05:25", dtf);
    
    QTest::newRow("Yelp") << "yelp.rss" << "Recent Reviews Near San Francisco, CA" << 25
                                  << "Lisa Z.'s Review of Score! Bar and Lounge - San Francisco (5/5) on Yelp"
                                  << "http://www.yelp.com/biz/score-bar-and-lounge-san-francisco?hrid=PNUmsy71RbWtCOq3sNKsDg"
                                  << "http://www.yelp.com/biz/score-bar-and-lounge-san-francisco?hrid=PNUmsy71RbWtCOq3sNKsDg"
                                  << QDateTime::fromString("04 Jul 2014 21:36:06", dtf);
    
    QTest::newRow("Hoodline") << "hoodline.atom" << "Hoodline" << 25
                                  << "Lower Haight Weekend Planner: 7/10"
                                  << "http://hoodline.com/2014/07/lower-haight-weekend-planner-7-10"
                                  << "tag:hoodwork.com,2010-01-01:/2014/07/lower-haight-weekend-planner-7-10"
                                  << QDateTime::fromString("10 Jul 2014 23:04:58", dtf);
    
    QTest::newRow("Reaper") << "reaper.fm.rss" << "REAPER news" << 11
                                  << "July 15, 2014"
                                  << "http://www.reaper.fm/download.php"
                                  << "http://www.reaper.fm/download.php" // Note that GUIDs aren't unique in this feed!!
                                  << QDateTime::fromString("15 Jul 2014 00:00:00", dtf);
    
    QTest::newRow("Foldplop") << "foldplop.rss" << "Foldplop News" << 16
                                  << "Creative Commons 4.0"
                                  << "http://foldplop.com/news/16"
                                  << "16"
                                  << QDateTime::fromString("27 Nov 2013 02:16:20", dtf);
    
    QTest::newRow("Bleep Podcast") << "bleep.podcast.rss" << "Bleep Podcast" << 125
                                  << "Bleep Podcast #125"
                                  << "http://bleep.com/podcasts"
                                  << "http://podcast.bleep.com/125/Bleep+podcast+125.mp3"
                                  << QDateTime::fromString("14 Jul 2014 12:00:00", dtf);
    
    QTest::newRow("3D Realms") << "3drealms.atom" << "3D Realms News" << 15
                                  << "Duke Nukem II Now Available for iOS"
                                  << "http://www.3drealms.com/news/2013/04/duke_nukem_ii_now_available_for_ios.html"
                                  << "tag:www.3drealms.com,2013://1.1575"
                                  << QDateTime::fromString("03 Apr 2013 17:23:40", dtf);
    
    QTest::newRow("The Verge") << "theverge.rss" << "The Verge -  All Posts" << 10
                                  << "Twitpic changes course yet again, will now be shutting down on October 25th"
                                  << "http://www.theverge.com/2014/10/16/6991567/twitpic-shutting-down-on-october-25th"
                                  << "http://www.theverge.com/2014/10/16/6991567/twitpic-shutting-down-on-october-25th"
                                  << QDateTime::fromString("17 Oct 2014 00:19:19", dtf);
    
    QTest::newRow("Valleywag") << "valleywag.rss" << "Valleywag" << 25
                                  << "Uber Fired a Driver Over a \"Hateful\" Tweet About the Company"
                                  << "http://feeds.gawker.com/~r/valleywag/full/~3/1_URVEiaSbI/uber-fired-a-driver-over-a-hateful-tweet-about-the-co-1647350304"
                                  << "1647350304"
                                  << QDateTime::fromString("16 Oct 2014 22:45:00", dtf);
    
    QTest::newRow("MakeUseOf") << "makeuseof.rss" << "MakeUseOf" << 15
                                  << "Famous Internet Firsts And Where We Are Now"
                                  << "http://www.makeuseof.com/tag/famous-internet-firsts-now/"
                                  << "http://www.makeuseof.com/?p=418618"
                                  << QDateTime::fromString("17 Oct 2014 02:30:20", dtf);
    
    QTest::newRow("BitTorrent blog") << "bittorrent.rss" << "The Official BitTorrent Blog" << 10
                                  << "Sync Stories: Kickstarter Project Playnode Takes Distributed Technology to DJs"
                                  << "http://blog.bittorrent.com/2014/10/14/sync-stories-kickstarter-project-playnode-takes-distributed-technology-to-djs/"
                                  << "http://bittorrent.gyre.wpengine.com/?p=5338"
                                  << QDateTime::fromString("14 Oct 2014 17:00:55", dtf);
    
    QTest::newRow("xkcd RSS") << "xkcd.rss" << "xkcd.com" << 4
                                  << "Presidential Alert"
                                  << "http://xkcd.com/1435/"
                                  << "http://xkcd.com/1435/"
                                  << QDateTime::fromString("17 Oct 2014 04:00:00", dtf);
    
    QTest::newRow("xkcd Atom") << "xkcd.atom" << "xkcd.com" << 4
                                  << "Presidential Alert"
                                  << "http://xkcd.com/1435/"
                                  << "http://xkcd.com/1435/"
                                  << QDateTime::fromString("17 Oct 2014 00:00:00", dtf);
    
    QTest::newRow("NBC News") << "nbcnews.rss" << "NBC News Top Stories" << 25
                                  << "'Deplorable': Foley Family Disgusted by Political Ad"
                                  << "http://feeds.nbcnews.com/c/35002/f/663303/s/3f8a588f/sc/7/l/0L0Snbcnews0N0Cnews0Cus0Enews0Cparents0Eslain0Ejournalist0Ejames0Efoley0Ecall0Epolitical0Ead0Edeplorable0En227866/story01.htm"
                                  << "http://www.nbcnews.com/news/us-news/parents-slain-journalist-james-foley-call-political-ad-deplorable-n227866"
                                  << QDateTime::fromString("17 Oct 2014 03:57:50", dtf);
    
    QTest::newRow("MIT Humanities.rss") << "mithumanities.rss" << "MIT News - Humanities" << 50
                                  << "Said and Done for September 2014 "
                                  << "http://newsoffice.mit.edu/2014/said-and-done-september-2014-0930"
                                  << "http://newsoffice.mit.edu/2014/said-and-done-september-2014-0930"
                                  << QDateTime::fromString("30 Sep 2014 22:01:02", dtf);
    
    QTest::newRow("CBSNews") << "cbsnews.rss" << "Home - CBSNews.com" << 29
                                  << "Obama mulls Ebola \"czar\""
                                  << "http://www.cbsnews.com/news/obama-says-ebola-czar-may-be-appropriate/"
                                  << "0c593429-8235-4bfb-92b2-2025ab0c334c"
                                  << QDateTime::fromString("17 Oct 2014 04:07:46", dtf);

    QTest::newRow("WSJ") << "wallstreetjournal.atom" << "WSJ.com: World News" << 39
                                  << "Two Hostages Killed in Rescue Bid in Yemen"
                                  << "http://online.wsj.com/articles/american-hostage-luke-somers-killed-in-rescue-attempt-1417862298?mod=fox_australian"
                                  << "SB10470281195569164720004580320502041250636"
                                  << QDateTime::fromString("06 Dec 2014 13:04:22", dtf);

    QTest::newRow("Recode") << "recode.atom" << "Re/code" << 25
                                  << "Facebook CEO Jabs Apple For Pricey Products"
                                  << "http://recode.net/2014/12/06/facebook-ceo-jabs-apple-for-pricey-products/"
                                  << "http://recode.net/?p=106809"
                                  << QDateTime::fromString("06 Dec 2014 19:06:23", dtf);

    QTest::newRow("NRO") << "nationalreview.rss" << "National Review Online" << 30
                                  << "More on TNR"
                                  << "https://www.nationalreview.com/postmodern-conservative/394135/more-tnr-carl-eric-scott"
                                  << "394135"
                                  << QDateTime::fromString("06 Dec 2014 18:28:43", dtf);

    QTest::newRow("TheNewRepublic") << "thenewrepublic.rss" << "New Republic" << 100
                                  << "Don't Let Police Killings of Unarmed Black Men Become Another Forgotten News Fad"
                                  << "http://www.newrepublic.com/article/120496/police-brutality-must-not-be-media-news-blip"
                                  << "120496 at http://www.newrepublic.com"
                                  << QDateTime::fromString("05 Dec 2014 23:11:00", dtf);

    QTest::newRow("Mission Local") << "missionlocal.rss" << "MissionLocal" << 10
                                  << "Medical Center Eyes Valencia, Opposition Mounts"
                                  << "http://missionlocal.org/2015/05/medical-center-eyes-valencia-opposition-mounts/"
                                  << "http://missionlocal.org/?p=291167"
                                  << QDateTime::fromString("10 May 2015 21:50:11", dtf);
}

QTEST_MAIN(TestFangParser)

#include "tst_fangparser.moc"
