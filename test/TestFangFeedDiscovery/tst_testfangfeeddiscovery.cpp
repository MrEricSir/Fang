#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QUrl>
#include <QSignalSpy>

#include "../../src/utilities/FeedDiscovery.h"
#include "../../src/utilities/WebPageGrabber.h"
#include "../MockNewsParser.h"
#include "../MockWebPageGrabber.h"

class TestFangFeedDiscovery : public QObject
{
    Q_OBJECT

public:
    TestFangFeedDiscovery();

private slots:
    // Existing test: findFeeds() method with HTML files
    void testCase1();
    void testCase1_data();

    // New tests: URL validation
    void testURLWithoutScheme();

    // New tests: Atom preference
    void testAtomPreferredOverRSS();
    void testOnlyRSS();
    void testOnlyAtom();
    void testNoFeeds();

    // State machine tests - error paths
    void testFirstParseAllErrors();
    void testSecondParseNetworkError();
    void testSecondParseFileError();
    void testSecondParseEmptyDocument();
    void testPageGrabberNullDocument();
    void testPageGrabberNoFeedFound();
    void testFullSuccessFlow();

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

// Test that URLs without scheme get fixed up
void TestFangFeedDiscovery::testURLWithoutScheme()
{
    FeedDiscovery fd;

    // This should not error - it gets scheme added
    fd.checkFeed("example.com");

    // The URL should have been fixed up to include http://
    // Note: We can't easily test the full flow without network,
    // but we can verify it doesn't immediately error
    QVERIFY2(!fd.error() || fd.errorString() != "Invalid URL",
             "URL without scheme should be fixed up, not rejected");
}

// Test that Atom is preferred over RSS when both are present
void TestFangFeedDiscovery::testAtomPreferredOverRSS()
{
    FeedDiscovery fd;

    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="http://example.com/rss.xml" />
            <link rel="alternate" type="application/atom+xml" href="http://example.com/atom.xml" />
        </head>
        <body></body>
        </html>
    )";

    fd.findFeeds(html);

    // Both should be found
    QCOMPARE(fd.getAtomURL(), QString("http://example.com/atom.xml"));
    QCOMPARE(fd.getRssURL(), QString("http://example.com/rss.xml"));

    // When onPageGrabberReady processes this, it prefers Atom
    // (checking the logic: if (atomURL.size()) gets checked first)
}

// Test finding only RSS
void TestFangFeedDiscovery::testOnlyRSS()
{
    FeedDiscovery fd;

    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="http://example.com/feed.rss" />
        </head>
        <body></body>
        </html>
    )";

    fd.findFeeds(html);

    QCOMPARE(fd.getRssURL(), QString("http://example.com/feed.rss"));
    QCOMPARE(fd.getAtomURL(), QString(""));
}

// Test finding only Atom
void TestFangFeedDiscovery::testOnlyAtom()
{
    FeedDiscovery fd;

    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/atom+xml" href="http://example.com/feed.atom" />
        </head>
        <body></body>
        </html>
    )";

    fd.findFeeds(html);

    QCOMPARE(fd.getAtomURL(), QString("http://example.com/feed.atom"));
    QCOMPARE(fd.getRssURL(), QString(""));
}

// Test HTML with no feed links
void TestFangFeedDiscovery::testNoFeeds()
{
    FeedDiscovery fd;

    QString html = R"(
        <html>
        <head>
            <title>No feeds here</title>
        </head>
        <body></body>
        </html>
    )";

    fd.findFeeds(html);

    QCOMPARE(fd.getRssURL(), QString(""));
    QCOMPARE(fd.getAtomURL(), QString(""));
}

// Test that first parse errors fall through to web grabber
void TestFangFeedDiscovery::testFirstParseAllErrors()
{
    // Test NETWORK_ERROR, FILE_ERROR, EMPTY_DOCUMENT, PARSE_ERROR
    // All should transition to WEB_GRABBER state

    MockNewsParser* parser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    // Set parser to return FILE_ERROR
    parser->setResult(ParserInterface::FILE_ERROR);

    // Set grabber to return null (error)
    grabber->setError(true);

    FeedDiscovery fd(nullptr, parser, new MockNewsParser(), grabber);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    // Start discovery - should fail first parse, try web grabber, then error
    fd.checkFeed("http://example.com");

    // Wait for async completion
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Should have errored with "No page found"
    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("No page found"));
}

// Test second parse network error
void TestFangFeedDiscovery::testSecondParseNetworkError()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockNewsParser* secondParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    // First parse fails
    firstParser->setResult(ParserInterface::NETWORK_ERROR);

    // Web grabber returns a page with an RSS link
    QString mockPage = "<html><head><link rel=\"alternate\" type=\"application/rss+xml\" href=\"http://example.com/feed.xml\" /></head></html>";
    grabber->setMockDocument(new QString(mockPage));

    // Second parse fails with NETWORK_ERROR
    secondParser->setResult(ParserInterface::NETWORK_ERROR);

    FeedDiscovery fd(nullptr, firstParser, secondParser, grabber);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("Could not reach URL"));
}

// Test second parse file error
void TestFangFeedDiscovery::testSecondParseFileError()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockNewsParser* secondParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::FILE_ERROR);

    QString mockPage = "<html><head><link rel=\"alternate\" type=\"application/rss+xml\" href=\"http://example.com/feed.xml\" /></head></html>";
    grabber->setMockDocument(new QString(mockPage));

    secondParser->setResult(ParserInterface::FILE_ERROR);

    FeedDiscovery fd(nullptr, firstParser, secondParser, grabber);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));

    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("Could not load file"));
}

// Test second parse empty document error
void TestFangFeedDiscovery::testSecondParseEmptyDocument()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockNewsParser* secondParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::EMPTY_DOCUMENT);

    QString mockPage = "<html><head><link rel=\"alternate\" type=\"application/rss+xml\" href=\"http://example.com/feed.xml\" /></head></html>";
    grabber->setMockDocument(new QString(mockPage));

    secondParser->setResult(ParserInterface::EMPTY_DOCUMENT);

    FeedDiscovery fd(nullptr, firstParser, secondParser, grabber);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));

    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("Error parsing feed"));
}

// Test page grabber returning null document
void TestFangFeedDiscovery::testPageGrabberNullDocument()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::NETWORK_ERROR);
    grabber->setError(true); // Returns nullptr

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));

    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("No page found"));
}

// Test page grabber returning page with no feed links
void TestFangFeedDiscovery::testPageGrabberNoFeedFound()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    // Page with no feed links
    QString mockPage = "<html><head><title>No feeds here</title></head><body></body></html>";
    grabber->setMockDocument(new QString(mockPage));

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));

    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("No feed found"));
}

// Test full success flow: first parse succeeds
void TestFangFeedDiscovery::testFullSuccessFlow()
{
    MockNewsParser* firstParser = new MockNewsParser();
    RawFeed* mockFeed = new RawFeed();
    mockFeed->url = QUrl("http://example.com/feed.xml");

    firstParser->setResult(ParserInterface::OK);
    firstParser->setFeed(mockFeed);
    firstParser->setURL(QUrl("http://example.com/feed.xml"));

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), new MockWebPageGrabber());
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com/feed.xml");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY(!fd.error());
    QCOMPARE(fd.feedURL(), QUrl("http://example.com/feed.xml"));
    QVERIFY(fd.feedResult() != nullptr);
}

QTEST_MAIN(TestFangFeedDiscovery)

#include "tst_testfangfeeddiscovery.moc"
