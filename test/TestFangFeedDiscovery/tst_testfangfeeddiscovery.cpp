#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QUrl>

#include "../../src/utilities/FeedDiscovery.h"
#include "../../src/utilities/WebPageGrabber.h"

class TestFangFeedDiscovery : public QObject
{
    Q_OBJECT
    
public:
    TestFangFeedDiscovery();
    
private slots:
    void testCase1();
    void testCase1_data();
    
private:
};

TestFangFeedDiscovery::TestFangFeedDiscovery()
{
}

void TestFangFeedDiscovery::testCase1()
{
    QFETCH(QString, filename);
    QFETCH(bool, isValid);
    QFETCH(QString, rssURL);
    QFETCH(QString, atomURL);

    QString projectPath = PROJECT_PATH;
    QString fullFilename = projectPath + "/feeds/" + filename;
    QFile file(fullFilename);
    if (isValid) {
        QVERIFY2(file.exists(), "Input file does not exist");
    }

    bool couldOpen = file.open(QFile::ReadOnly | QFile::Text);
    if (!couldOpen) {
        qDebug() << "File: " << fullFilename;
        QVERIFY2(!isValid, "Unable to open file");
        return;
    }

    // We use WebPageGrabber for its ability to turn HTML into XML. Should not download anything.
    WebPageGrabber grabber;
    QString* xmlDoc = grabber.load(file.readAll());
    if (xmlDoc == nullptr) {
        QVERIFY2(!isValid, "Null document returned");
        return;
    }

    // Check to see if we found the expected RSS and/or Atom feeds.
    FeedDiscovery fd;
    fd.findFeeds(*xmlDoc);

    // qDebug() << "rss: " << fd.getRssURL();
    // qDebug() << "atom: " << fd.getAtomURL();

    // Check results.
    if (isValid) {
        QCOMPARE(fd.getRssURL(), rssURL);
        QCOMPARE(fd.getAtomURL(), atomURL);
    } else {
        QVERIFY2(fd.getRssURL() == "", "Unexpected RSS URL found");
        QVERIFY2(fd.getAtomURL() == "", "Unexpected Atom URL found");
    }
}

void TestFangFeedDiscovery::testCase1_data()
{
    QTest::addColumn<QString>("filename"); // Has to be in the feeds subfolder
    QTest::addColumn<bool>("isValid");     // True if we expect to get a URL
    QTest::addColumn<QString>("rssURL");   // The RSS URL we expect (or empty string if none)
    QTest::addColumn<QString>("atomURL");  // The Atom URL we expect (or empty string if none)

    //
    // Typical situations /////////////////////////////////////////////////////////////////////////
    //
    
    // Expected: Errors
    QTest::newRow("Bullshit URL") << "asfaw3f" << false << "" << "";
    QTest::newRow("No RSS feed") << "google.com" << false << "" << "";
    
    // Expected: Valid feeds.
    QTest::newRow("MrEricSir") << "mrericsir.com" << true
                               << "https://www.mrericsir.com/blog/feed/" << "";
    QTest::newRow("LaughingSquid") << "laughingsquid.com" << true
                                   << "https://laughingsquid.com/feed/" << "";
    QTest::newRow("Eater SF") << "sf.eater.com" << true
                           << "/rss/index.xml" << "";
    QTest::newRow("SFist") << "sfist.com" << true
                           << "https://sfist.com/rss/" << "";
    QTest::newRow("Fark") << "fark.com" << true
                          << "https://www.fark.com/fark.rss" << "";
    QTest::newRow("Old defunct Your Kickstarter Sucks Tumblr") << "yourkickstartersucks.tumblr.com" << true
                                                               << "https://yourkickstartersucks.tumblr.com/rss" << "";
    QTest::newRow("Mozilla Blog") << "blog.mozilla.org" << true
                                  << "https://blog.mozilla.org/en/feed/" << "";
    QTest::newRow("KQED") << "kqed.org" << true
                          << "https://ww2.kqed.org/news/feed/" << "";
    QTest::newRow("KRON") << "kron4.com" << true
                          << "https://www.kron4.com/feed/" << "";
    QTest::newRow("McSweeney's") << "mcsweeneys.net" << true
                                 << "https://feeds.feedburner.com/mcsweeneys" << "";
    QTest::newRow("Planet GNOME") << "planet.gnome.org" << true
                                  << "https://planet.gnome.org//rss20.xml" << "";
    QTest::newRow("BoingBoing") << "boingboing.net" << true
                                << "https://boingboing.net/feed" << "";
    QTest::newRow("Hacker News") << "news.ycombinator.com" << true
                                 << "rss" << "";
    QTest::newRow("TechCrunch") << "techcrunch.com" << true
                                << "https://techcrunch.com/feed/" << "";
    QTest::newRow("This American Life") << "thisamericanlife.org" << true
                                        << "https://www.thisamericanlife.org/podcast/rss.xml" << "";
    QTest::newRow("The Guardian") << "theguardian.com" << true
                                  << "https://www.theguardian.com/us/rss" << "";
    QTest::newRow("City Nerd on Bluesky") << "nerd4cities.bsky.social" << true
                                  << "https://bsky.app/profile/did:plc:wkflkbryiylhva4wg5jitzrv/rss" << "";
    QTest::newRow("DNA Lounge Blog") << "dnalounge.com" << true
                                          << "https://cdn.dnalounge.com/backstage/log/feed/" << "";

    //
    // Unusual situations /////////////////////////////////////////////////////////////////////////
    //

    // HTML contains an error: the RSS link is inside of another tag's attribute string.
    QTest::newRow("AV Club") << "avclub.com" << true << "" << "";

    // Mostly Javascript, no feed links.
    QTest::newRow("SFGate") << "sfgate.com" << true << "" << "";
}

QTEST_MAIN(TestFangFeedDiscovery)

#include "tst_testfangfeeddiscovery.moc"
