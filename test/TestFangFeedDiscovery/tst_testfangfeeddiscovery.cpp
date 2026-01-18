#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QUrl>
#include <QSignalSpy>

#include "../../src/utilities/FeedDiscovery.h"
#include "../../src/utilities/WebPageGrabber.h"
#include "../MockNewsParser.h"
#include "../MockWebPageGrabber.h"
#include "../MockBatchNewsParser.h"

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
    void testPageGrabberNullDocument();
    void testPageGrabberNoFeedFound();
    void testFullSuccessFlow();
    void testMercuryNewsFullFlow();

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
    QList<QString> feedURLs = fd.parseFeedsFromXHTML(*xmlDoc);

    // Debug output for Mercury News test
    if (filename.contains("mercurynews")) {
        qDebug() << "Mercury News test - Found" << feedURLs.count() << "feed URLs:";
        for (const QString& url : feedURLs) {
            qDebug() << "  -" << url;
        }
    }

    // Check results - parseFeedsFromXHTML now returns all feed URLs in a list
    if (isValid) {
        // Check if we found the expected feed(s)
        if (!rssURL.isEmpty()) {
            QVERIFY2(feedURLs.contains(rssURL), "Expected RSS URL not found in feed list");
        }
        if (!atomURL.isEmpty()) {
            QVERIFY2(feedURLs.contains(atomURL), "Expected Atom URL not found in feed list");
        }
    } else {
        QVERIFY2(feedURLs.isEmpty(), "Unexpected feed URLs found");
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
    QTest::newRow("Mercury News Business") << "mercurynews.com" << true
                                           << "https://www.mercurynews.com/feed/" << "";

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

// Test that both RSS and Atom feeds are discovered when both are present
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

    QList<QString> feedURLs = fd.parseFeedsFromXHTML(html);

    // Both should be found in the list
    QVERIFY(feedURLs.contains("http://example.com/atom.xml"));
    QVERIFY(feedURLs.contains("http://example.com/rss.xml"));
    QCOMPARE(feedURLs.count(), 2);
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

    QList<QString> feedURLs = fd.parseFeedsFromXHTML(html);

    QCOMPARE(feedURLs.count(), 1);
    QVERIFY(feedURLs.contains("http://example.com/feed.rss"));
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

    QList<QString> feedURLs = fd.parseFeedsFromXHTML(html);

    QCOMPARE(feedURLs.count(), 1);
    QVERIFY(feedURLs.contains("http://example.com/feed.atom"));
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

    QList<QString> feedURLs = fd.parseFeedsFromXHTML(html);

    QCOMPARE(feedURLs.count(), 0);
    QVERIFY(feedURLs.isEmpty());
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

    // Set grabber to return error (nullptr document)
    grabber->setError(true);

    FeedDiscovery fd(nullptr, parser, new MockNewsParser(), grabber, new MockBatchNewsParser());
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

// Test page grabber returning null document
void TestFangFeedDiscovery::testPageGrabberNullDocument()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::NETWORK_ERROR);
    grabber->setError(true); // Returns nullptr document

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber, new MockBatchNewsParser());
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
    static QString mockPage = "<html><head><title>No feeds here</title></head><body></body></html>";
    grabber->setMockDocument(&mockPage);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber, new MockBatchNewsParser());
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
    mockFeed->title = "Test Feed";

    firstParser->setResult(ParserInterface::OK);
    firstParser->setFeed(mockFeed);
    firstParser->setURL(QUrl("http://example.com/feed.xml"));

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), new MockWebPageGrabber(), new MockBatchNewsParser());
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com/feed.xml");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY(!fd.error());
    QCOMPARE(fd.feedURL(), QUrl("http://example.com/feed.xml"));
    QVERIFY(fd.feedResult() != nullptr);

    // Verify discoveredFeeds list contains the feed
    QCOMPARE(fd.feedCount(), 1);
    QList<FeedDiscovery::DiscoveredFeed> feeds = fd.discoveredFeeds();
    QCOMPARE(feeds.count(), 1);
    QCOMPARE(feeds.first().url, QUrl("http://example.com/feed.xml"));
    QCOMPARE(feeds.first().title, QString("Test Feed"));
    QVERIFY(feeds.first().validated);
}

// Test full Mercury News discovery flow with actual HTML
void TestFangFeedDiscovery::testMercuryNewsFullFlow()
{
    // Load the actual Mercury News HTML
    QString projectPath = PROJECT_PATH;
    QString fullFilename = projectPath + "/feeds/mercurynews.com";
    QFile file(fullFilename);
    QVERIFY2(file.open(QFile::ReadOnly | QFile::Text), "Could not open Mercury News HTML file");

    QByteArray rawHtml = file.readAll();
    file.close();

    // Process HTML through WebPageGrabber to convert to XHTML (like the real flow does)
    WebPageGrabber webGrabber;
    QString* processedHtml = webGrabber.load(rawHtml);
    QVERIFY2(processedHtml != nullptr, "WebPageGrabber failed to process Mercury News HTML");

    QString htmlContent = *processedHtml;

    // Set up mocks
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    // First parse should fail (it's HTML, not a feed)
    firstParser->setResult(ParserInterface::PARSE_ERROR);

    // Page grabber should return the processed XHTML
    qDebug() << "Setting up page grabber with processed HTML content, length:" << htmlContent.length();
    qDebug() << "First 1000 chars:" << htmlContent.left(1000);

    // Store the HTML content in a persistent QString for the mock
    static QString persistentHtmlContent = htmlContent;
    pageGrabber->setMockDocument(&persistentHtmlContent);

    // Feed parser should successfully parse the discovered feed URLs
    RawFeed* feed1 = new RawFeed();
    feed1->title = "Mercury News Feed";
    feed1->url = QUrl("https://www.mercurynews.com/feed/");

    RawFeed* feed2 = new RawFeed();
    feed2->title = "Mercury News Business Feed";
    feed2->url = QUrl("https://www.mercurynews.com/business/feed/");

    feedParser->addResponse(QUrl("https://www.mercurynews.com/feed/"), ParserInterface::OK, feed1);
    feedParser->addResponse(QUrl("https://www.mercurynews.com/business/feed/"), ParserInterface::OK, feed2);

    // Create FeedDiscovery with our mocks
    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);

    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("https://www.mercurynews.com/business/");

    // Wait for async completion
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Verify no error
    QVERIFY2(!fd.error(), "Feed discovery should not error");
    QCOMPARE(fd.errorString(), QString(""));

    // Verify we found exactly 2 feeds
    QCOMPARE(fd.feedCount(), 2);

    QList<FeedDiscovery::DiscoveredFeed> feeds = fd.discoveredFeeds();
    QCOMPARE(feeds.count(), 2);

    // Feeds should be sorted by path length (longer = more specific first)
    // So /business/feed/ should come before /feed/
    QCOMPARE(feeds[0].url, QUrl("https://www.mercurynews.com/business/feed/"));
    QVERIFY(feeds[0].validated);

    QCOMPARE(feeds[1].url, QUrl("https://www.mercurynews.com/feed/"));
    QVERIFY(feeds[1].validated);
}

QTEST_MAIN(TestFangFeedDiscovery)

#include "tst_testfangfeeddiscovery.moc"
