#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QUrl>
#include <QSignalSpy>

#include "../../src/utilities/FeedDiscovery.h"
#include "../../src/utilities/WebPageGrabber.h"
#include "../../src/utilities/PageMetadataExtractor.h"
#include "../../src/parser/RawNews.h"
#include "../../src/parser/SitemapParser.h"
#include "../../src/utilities/GoogleNewsSitemapSynthesizer.h"
#include "../MockNewsParser.h"
#include "../MockWebPageGrabber.h"
#include "../MockBatchNewsParser.h"
#include "../MockGoogleNewsSitemapSynthesizer.h"

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

    // Additional edge case tests for remaining coverage
    void testRelativeURLThatStaysRelative();
    void testAllFeedsFailValidation();

    // Empty feed rejection
    void testEmptyDirectFeedRejected();
    void testEmptyValidatedFeedsRejected();

    // Relative feed URL resolution
    void testRelativeFeedURLResolution();

    // Protocol-relative URL handling
    void testProtocolRelativeFeedURL();

    // Trailing slash normalization
    void testTrailingSlashStripped();

    // Common path probing
    void testCommonPathDiscovery();
    void testCommonPathAllFail();
    void testCommonPathAfterValidationFails();
    void testCommonPathSkippedWhenFeedsFound();

    // SitemapParser unit tests
    void testSitemapParserUrlSet();
    void testSitemapParserSitemapIndex();
    void testSitemapParserWithNamespaces();
    void testSitemapParserInvalid();
    void testSitemapParserNoLastmod();

    // PageMetadataExtractor unit tests
    void testPageMetadataOGTags();
    void testPageMetadataFallback();
    void testPageMetadataEmpty();

    // Google News sitemap tests
    void testSitemapParserAPNews();
    void testSitemapParserUSAToday();
    void testSitemapParserBloomberg();
    void testSitemapParserLanguageFiltering();

    // Robots.txt parsing tests
    void testRobotsTxtParsing();
    void testRobotsTxtAutoDiscovery();

    // Sitemap integration tests (injectable synthesizer)
    void testSitemapSuccessIntegration();
    void testSitemapErrorIntegration();

    // Full flow integration tests for specific sites
    void testESPNFullFlow();
    void testCommonPathFallbackFlow();

    // JSON Feed link detection
    void testJSONFeedLinkDetection();

    // Deduplication tests
    void testDeduplicateRepetitiveTitles();
    void testDeduplicateNoRepetition();
    void testDeduplicateKeepsMostRecent();
    void testDeduplicateSmallList();

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
                               << "https://www.mrericsir.com/blog/feed" << "";
    QTest::newRow("LaughingSquid") << "laughingsquid.com" << true
                                   << "https://laughingsquid.com/feed" << "";
    QTest::newRow("Eater SF") << "sf.eater.com" << true
                           << "/rss/index.xml" << "";
    QTest::newRow("SFist") << "sfist.com" << true
                           << "https://sfist.com/rss" << "";
    QTest::newRow("Fark") << "fark.com" << true
                          << "https://www.fark.com/fark.rss" << "";
    QTest::newRow("Old defunct Your Kickstarter Sucks Tumblr") << "yourkickstartersucks.tumblr.com" << true
                                                               << "https://yourkickstartersucks.tumblr.com/rss" << "";
    QTest::newRow("Mozilla Blog") << "blog.mozilla.org" << true
                                  << "https://blog.mozilla.org/en/feed" << "";
    QTest::newRow("KQED") << "kqed.org" << true
                          << "https://ww2.kqed.org/news/feed" << "";
    QTest::newRow("KRON") << "kron4.com" << true
                          << "https://www.kron4.com/feed" << "";
    QTest::newRow("McSweeney's") << "mcsweeneys.net" << true
                                 << "https://feeds.feedburner.com/mcsweeneys" << "";
    QTest::newRow("Planet GNOME") << "planet.gnome.org" << true
                                  << "https://planet.gnome.org//rss20.xml" << "";
    QTest::newRow("BoingBoing") << "boingboing.net" << true
                                << "https://boingboing.net/feed" << "";
    QTest::newRow("Hacker News") << "news.ycombinator.com" << true
                                 << "rss" << "";
    QTest::newRow("TechCrunch") << "techcrunch.com" << true
                                << "https://techcrunch.com/feed" << "";
    QTest::newRow("This American Life") << "thisamericanlife.org" << true
                                        << "https://www.thisamericanlife.org/podcast/rss.xml" << "";
    QTest::newRow("The Guardian") << "theguardian.com" << true
                                  << "https://www.theguardian.com/us/rss" << "";
    QTest::newRow("City Nerd on Bluesky") << "nerd4cities.bsky.social" << true
                                  << "https://bsky.app/profile/did:plc:wkflkbryiylhva4wg5jitzrv/rss" << "";
    QTest::newRow("DNA Lounge Blog") << "dnalounge.com" << true
                                          << "https://cdn.dnalounge.com/backstage/log/feed" << "";
    QTest::newRow("Mercury News Business") << "mercurynews.com" << true
                                           << "https://www.mercurynews.com/feed" << "";
    QTest::newRow("GetFang") << "getfang.com" << true
                             << "/feed.xml" << "";
    QTest::newRow("ABC7 News") << "abc7news.com" << true
                               << "//abc7news.com/feed" << "";
    QTest::newRow("CBS News") << "cbsnews.com" << true
                               << "https://www.cbsnews.com/latest/rss/main" << "";
    QTest::newRow("SF Examiner") << "sfexaminer.com" << true
                                 << "http://www.sfexaminer.com/search/?f=rss&t=article&l=50&s=start_time&sd=desc&k%5B%5D=%23topstory" << "";
    QTest::newRow("Le Monde") << "lemonde.fr" << true
                               << "https://www.lemonde.fr/en/rss/une.xml" << "";

    //
    // Unusual situations /////////////////////////////////////////////////////////////////////////
    //

    // HTML contains an error: the RSS link is inside of another tag's attribute string.
    QTest::newRow("AV Club") << "avclub.com" << true << "" << "";

    // Mostly Javascript, no feed links.
    QTest::newRow("SFGate") << "sfgate.com" << true << "" << "";

    // JS-heavy SPA with no RSS/Atom links.
    QTest::newRow("ESPN") << "espn.com" << false << "" << "";

    // Hearst CMS, same as SFGate, no RSS links in HTML.
    QTest::newRow("SF Chronicle") << "sfchronicle.com" << false << "" << "";

    // WordPress site with RSS feed.
    QTest::newRow("Times of San Diego") << "timesofsandiego.com" << true
                                        << "https://timesofsandiego.com/feed" << "";

    // SoCast CMS, no RSS links in HTML.
    QTest::newRow("1077 The Bone") << "1077thebone.com" << false << "" << "";

    // Captcha/JS challenge page, no feeds in HTML.
    QTest::newRow("NJ.com") << "nj.com" << false << "" << "";
    QTest::newRow("Syracuse.com") << "syracuse.com" << false << "" << "";
}

// Test that URLs without scheme get fixed up
void TestFangFeedDiscovery::testURLWithoutScheme()
{
    MockNewsParser* mockParser = new MockNewsParser();
    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, mockParser, new MockNewsParser(), new MockWebPageGrabber(), new MockBatchNewsParser(), sitemapSynth);

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

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, parser, new MockNewsParser(), grabber, new MockBatchNewsParser(), sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    // Start discovery - should fail first parse, try web grabber, then error
    fd.checkFeed("http://example.com");

    // Wait for async completion
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Page grab failed, common paths all fail, sitemap fails -> error
    QVERIFY(fd.error());
}

// Test page grabber returning null document
void TestFangFeedDiscovery::testPageGrabberNullDocument()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::NETWORK_ERROR);
    grabber->setError(true); // Returns nullptr document

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber, new MockBatchNewsParser(), sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));

    // Page grab failed, common paths all fail, sitemap fails -> error
    QVERIFY(fd.error());
}

// Test page grabber returning page with no feed links (falls through to sitemap, which also fails)
void TestFangFeedDiscovery::testPageGrabberNoFeedFound()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    // Page with no feed links
    static QString mockPage = "<html><head><title>No feeds here</title></head><body></body></html>";
    grabber->setMockDocument(&mockPage);

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber, new MockBatchNewsParser(), sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));

    // No RSS feeds found, sitemap fetch also fails -> error
    QVERIFY(fd.error());
    QVERIFY2(!fd.errorString().isEmpty(),
             qPrintable("Unexpected empty error string"));
}

// Test full success flow: first parse succeeds
void TestFangFeedDiscovery::testFullSuccessFlow()
{
    MockNewsParser* firstParser = new MockNewsParser();
    RawFeed* mockFeed = new RawFeed();
    mockFeed->url = QUrl("http://example.com/feed.xml");
    mockFeed->title = "Test Feed";

    // Feed must have at least one item, otherwise it's rejected as empty.
    RawNews* item = new RawNews(mockFeed);
    item->title = "Test Item";
    item->url = QUrl("http://example.com/article");
    mockFeed->items.append(item);

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
    // Note: trailing slashes are stripped from discovered feed URLs
    RawFeed* feed1 = new RawFeed();
    feed1->title = "Mercury News Feed";
    feed1->url = QUrl("https://www.mercurynews.com/feed");
    RawNews* feed1Item = new RawNews(feed1);
    feed1Item->title = "Mercury News Article";
    feed1Item->url = QUrl("https://www.mercurynews.com/article1");
    feed1->items.append(feed1Item);

    RawFeed* feed2 = new RawFeed();
    feed2->title = "Mercury News Business Feed";
    feed2->url = QUrl("https://www.mercurynews.com/business/feed");
    RawNews* feed2Item = new RawNews(feed2);
    feed2Item->title = "Mercury News Business Article";
    feed2Item->url = QUrl("https://www.mercurynews.com/business/article1");
    feed2->items.append(feed2Item);

    feedParser->addResponse(QUrl("https://www.mercurynews.com/feed"), ParserInterface::OK, feed1);
    feedParser->addResponse(QUrl("https://www.mercurynews.com/business/feed"), ParserInterface::OK, feed2);

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
    // So /business/feed should come before /feed
    QCOMPARE(feeds[0].url, QUrl("https://www.mercurynews.com/business/feed"));
    QVERIFY(feeds[0].validated);

    QCOMPARE(feeds[1].url, QUrl("https://www.mercurynews.com/feed"));
    QVERIFY(feeds[1].validated);
}

// Test that a truly relative URL (one that urlFixup doesn't fix) gets rejected
void TestFangFeedDiscovery::testRelativeURLThatStaysRelative()
{
    MockNewsParser* firstParser = new MockNewsParser();
    firstParser->setResult(ParserInterface::PARSE_ERROR);  // Set a valid result in case URL gets fixed up

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), new MockWebPageGrabber(), new MockBatchNewsParser(), sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    // Try a path-only URL that NetworkUtilities::urlFixup might not handle
    // Note: Most URLs will get fixed up, so this tests the fallback error path
    fd.checkFeed("/just/a/path");

    // If it gets fixed up, it won't error immediately - wait for async completion
    // Either way, the test completes
    if (spy.count() == 0) {
        QVERIFY(spy.wait(5000));
    }

    // The URL likely got fixed up by NetworkUtilities::urlFixup, so it won't hit the
    // "Invalid URL" path. But we should still get an error since the mock isn't configured.
    // This test mainly exists to ensure we don't crash on edge-case URLs.
    QVERIFY(fd.error());
    // Accept any error message: the URL may be rejected immediately or fail downstream
    QVERIFY(!fd.errorString().isEmpty());
}

// Test that when all discovered feeds fail validation, we get an error
void TestFangFeedDiscovery::testAllFeedsFailValidation()
{
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="http://example.com/feed1.xml" />
            <link rel="alternate" type="application/atom+xml" href="http://example.com/feed2.xml" />
        </head>
        <body></body>
        </html>
    )";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtml = html;
    pageGrabber->setMockDocument(&persistentHtml);

    // Set both feeds to fail validation
    feedParser->addResponse(QUrl("http://example.com/feed1.xml"), ParserInterface::NETWORK_ERROR);
    feedParser->addResponse(QUrl("http://example.com/feed2.xml"), ParserInterface::PARSE_ERROR);

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser, sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // All feeds failed validation, falls through to sitemap which also fails
    QVERIFY(fd.error());
    QVERIFY2(!fd.errorString().isEmpty(),
             qPrintable("Unexpected empty error string"));
}

// Test that a directly-parsed feed with no items is rejected and falls through to web grabber
void TestFangFeedDiscovery::testEmptyDirectFeedRejected()
{
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* grabber = new MockWebPageGrabber();

    // Parser returns OK with a feed that has no items.
    RawFeed* emptyFeed = new RawFeed();
    emptyFeed->url = QUrl("http://example.com/feed.xml");
    emptyFeed->title = "Empty Feed";

    firstParser->setResult(ParserInterface::OK);
    firstParser->setFeed(emptyFeed);
    firstParser->setURL(QUrl("http://example.com/feed.xml"));

    // Web grabber returns an error (no page)
    grabber->setError(true);

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), grabber, new MockBatchNewsParser(), sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com/feed.xml");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Should have rejected the empty feed and fallen through to error
    QVERIFY(fd.error());
}

// Test that validated feeds with no items are rejected during batch validation
void TestFangFeedDiscovery::testEmptyValidatedFeedsRejected()
{
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="http://example.com/feed.xml" />
        </head>
        <body></body>
        </html>
    )";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtml2 = html;
    pageGrabber->setMockDocument(&persistentHtml2);

    // Feed parser returns OK but the feed has no items.
    RawFeed* emptyFeed = new RawFeed();
    emptyFeed->title = "Empty Feed";
    emptyFeed->url = QUrl("http://example.com/feed.xml");
    feedParser->addResponse(QUrl("http://example.com/feed.xml"), ParserInterface::OK, emptyFeed);

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser, sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Empty feed should be rejected, falls through to sitemap which also fails
    QVERIFY(fd.error());
}

// Test that relative feed URLs are resolved against the page URL
void TestFangFeedDiscovery::testRelativeFeedURLResolution()
{
    // HTML with a relative feed URL (like getfang.com uses)
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" title="Test Feed" href="/feed.xml" />
        </head>
        <body></body>
        </html>
    )";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    // First parse fails (it's HTML, not a feed)
    firstParser->setResult(ParserInterface::PARSE_ERROR);

    // Page grabber returns the HTML with relative feed URL
    static QString persistentHtml = html;
    pageGrabber->setMockDocument(&persistentHtml);

    // Feed parser should receive the RESOLVED absolute URL, not the relative one
    // The relative "/feed.xml" should be resolved to "https://example.com/feed.xml"
    RawFeed* feed = new RawFeed();
    feed->title = "Test Feed";
    feed->url = QUrl("https://example.com/feed.xml");
    RawNews* feedItem = new RawNews(feed);
    feedItem->title = "Test Article";
    feedItem->url = QUrl("https://example.com/article");
    feed->items.append(feedItem);
    feedParser->addResponse(QUrl("https://example.com/feed.xml"), ParserInterface::OK, feed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    // Start discovery with a full URL - the relative feed URL should be resolved against this
    fd.checkFeed("https://example.com/some/page.html");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Should succeed
    QVERIFY2(!fd.error(), qPrintable("Unexpected error: " + fd.errorString()));

    // The discovered feed should have the resolved absolute URL
    QCOMPARE(fd.feedCount(), 1);
    QList<FeedDiscovery::DiscoveredFeed> feeds = fd.discoveredFeeds();
    QCOMPARE(feeds.count(), 1);
    QCOMPARE(feeds.first().url, QUrl("https://example.com/feed.xml"));
    QVERIFY(feeds.first().validated);
}

// Test that protocol-relative feed URLs (like //abc7news.com/feed/) are resolved correctly
void TestFangFeedDiscovery::testProtocolRelativeFeedURL()
{
    // abc7news.com uses a protocol-relative feed URL: //abc7news.com/feed/
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" href="//abc7news.com/feed/" title="ABC7 San Francisco RSS" type="application/rss+xml" />
        </head>
        <body></body>
        </html>
    )";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtml3 = html;
    pageGrabber->setMockDocument(&persistentHtml3);

    // Protocol-relative //abc7news.com/feed/ resolved against https://abc7news.com
    // Trailing slash is stripped, then resolved to https://abc7news.com/feed
    QUrl resolvedUrl("https://abc7news.com/feed");

    // Set up feed parser to respond to the resolved URL
    RawFeed* feed = new RawFeed();
    feed->title = "ABC7 San Francisco RSS";
    feed->url = resolvedUrl;
    RawNews* item = new RawNews(feed);
    item->title = "Test Article";
    item->url = QUrl("https://abc7news.com/article");
    feed->items.append(item);
    feedParser->addResponse(resolvedUrl, ParserInterface::OK, feed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("https://abc7news.com/");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY2(!fd.error(), qPrintable("Feed discovery failed: " + fd.errorString()));
    QCOMPARE(fd.feedCount(), 1);
    QCOMPARE(fd.feedURL(), resolvedUrl);
}

// Test that trailing slashes are stripped from discovered feed URLs
// (cbsnews.com advertises /latest/rss/main/ but only /latest/rss/main returns 200)
void TestFangFeedDiscovery::testTrailingSlashStripped()
{
    FeedDiscovery fd;

    // HTML with feed URLs that have trailing slashes
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="https://example.com/latest/rss/main/" />
            <link rel="alternate" type="application/atom+xml" href="https://example.com/feed/" />
        </head>
        <body></body>
        </html>
    )";

    QList<QString> feedURLs = fd.parseFeedsFromXHTML(html);

    QCOMPARE(feedURLs.count(), 2);
    // Trailing slashes should be stripped
    QVERIFY(feedURLs.contains("https://example.com/latest/rss/main"));
    QVERIFY(feedURLs.contains("https://example.com/feed"));

    // Verify the originals with trailing slashes are NOT in the list
    QVERIFY(!feedURLs.contains("https://example.com/latest/rss/main/"));
    QVERIFY(!feedURLs.contains("https://example.com/feed/"));
}

// =====================================================================
// Common path probing tests
// =====================================================================

// Test that common path probing discovers a feed when HTML has no RSS links
void TestFangFeedDiscovery::testCommonPathDiscovery()
{
    // HTML with no feed links at all
    QString html = "<html><head><title>No feeds</title></head><body></body></html>";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlCommon1 = html;
    pageGrabber->setMockDocument(&persistentHtmlCommon1);

    // Set up /feed to return a valid feed
    RawFeed* feed = new RawFeed();
    feed->title = "Example Feed";
    feed->url = QUrl("http://example.com/feed");
    RawNews* item = new RawNews(feed);
    item->title = "Test Article";
    item->url = QUrl("http://example.com/article");
    feed->items.append(item);
    feedParser->addResponse(QUrl("http://example.com/feed"), ParserInterface::OK, feed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY2(!fd.error(), qPrintable("Unexpected error: " + fd.errorString()));
    QCOMPARE(fd.feedCount(), 1);
    QCOMPARE(fd.feedURL(), QUrl("http://example.com/feed"));
    QCOMPARE(fd.discoveredFeeds().first().title, QString("Example Feed"));
}

// Test that when all common paths fail, we fall through to sitemap (then error)
void TestFangFeedDiscovery::testCommonPathAllFail()
{
    QString html = "<html><head><title>No feeds</title></head><body></body></html>";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlCommon2 = html;
    pageGrabber->setMockDocument(&persistentHtmlCommon2);

    // Don't configure any responses -- all common paths will get NETWORK_ERROR by default

    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser, sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Common paths all fail, falls through to sitemap which also fails
    QVERIFY(fd.error());
    QVERIFY2(!fd.errorString().isEmpty(),
             qPrintable("Unexpected empty error string"));
}

// Test that after HTML-discovered feeds fail validation, common paths are tried
void TestFangFeedDiscovery::testCommonPathAfterValidationFails()
{
    // HTML with an RSS link that will fail validation
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="http://example.com/broken-feed.xml" />
        </head>
        <body></body>
        </html>
    )";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlCommon3 = html;
    pageGrabber->setMockDocument(&persistentHtmlCommon3);

    // HTML-discovered feed fails validation
    feedParser->addResponse(QUrl("http://example.com/broken-feed.xml"), ParserInterface::NETWORK_ERROR);

    // Common path /rss returns a valid feed
    RawFeed* feed = new RawFeed();
    feed->title = "Example RSS";
    feed->url = QUrl("http://example.com/rss");
    RawNews* item = new RawNews(feed);
    item->title = "Test Article";
    item->url = QUrl("http://example.com/article");
    feed->items.append(item);
    feedParser->addResponse(QUrl("http://example.com/rss"), ParserInterface::OK, feed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Should succeed via common path /rss
    QVERIFY2(!fd.error(), qPrintable("Unexpected error: " + fd.errorString()));
    QCOMPARE(fd.feedCount(), 1);
    QCOMPARE(fd.feedURL(), QUrl("http://example.com/rss"));
}

// Test that common path probing is skipped when HTML-discovered feeds validate successfully
void TestFangFeedDiscovery::testCommonPathSkippedWhenFeedsFound()
{
    // HTML with a valid RSS link
    QString html = R"(
        <html>
        <head>
            <link rel="alternate" type="application/rss+xml" href="http://example.com/my-feed.xml" />
        </head>
        <body></body>
        </html>
    )";

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlCommon4 = html;
    pageGrabber->setMockDocument(&persistentHtmlCommon4);

    // The HTML-discovered feed validates successfully
    RawFeed* feed = new RawFeed();
    feed->title = "My Feed";
    feed->url = QUrl("http://example.com/my-feed.xml");
    RawNews* item = new RawNews(feed);
    item->title = "Test Article";
    item->url = QUrl("http://example.com/article");
    feed->items.append(item);
    feedParser->addResponse(QUrl("http://example.com/my-feed.xml"), ParserInterface::OK, feed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("http://example.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Should succeed directly via the HTML-discovered feed
    QVERIFY2(!fd.error(), qPrintable("Unexpected error: " + fd.errorString()));
    QCOMPARE(fd.feedCount(), 1);
    QCOMPARE(fd.feedURL(), QUrl("http://example.com/my-feed.xml"));
    QCOMPARE(fd.discoveredFeeds().first().title, QString("My Feed"));
}

// =====================================================================
// SitemapParser unit tests
// =====================================================================

// Test parsing a standard <urlset> sitemap (like abc7news.com/sitemap/kgo/stories.xml)
void TestFangFeedDiscovery::testSitemapParserUrlSet()
{
    QString xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
    <url>
        <loc>https://abc7news.com/post/tribal-members-shape-bay-area-open-space/18721725/</loc>
        <lastmod>2026-03-17T21:35:07+00:00</lastmod>
    </url>
    <url>
        <loc>https://abc7news.com/post/former-democratic-presidents-havent-spoken-trump/18726156/</loc>
        <lastmod>2026-03-17T21:28:15+00:00</lastmod>
    </url>
    <url>
        <loc>https://abc7news.com/post/bodycam-video-shows-moments-leading-up-to-death/18722668/</loc>
        <lastmod>2026-03-17T21:15:49+00:00</lastmod>
    </url>
</urlset>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::UrlSet);
    QCOMPARE(parser.entries().size(), 3);
    QVERIFY(parser.subSitemaps().isEmpty());
    QVERIFY(!parser.hasNewsEntries());

    // Verify first entry
    QCOMPARE(parser.entries()[0].url, QUrl("https://abc7news.com/post/tribal-members-shape-bay-area-open-space/18721725/"));
    QVERIFY(parser.entries()[0].lastmod.isValid());
    QCOMPARE(parser.entries()[0].lastmod.date().year(), 2026);
    QCOMPARE(parser.entries()[0].lastmod.date().month(), 3);
    QCOMPARE(parser.entries()[0].lastmod.date().day(), 17);

    // Verify all entries have valid lastmod
    for (const SitemapEntry& entry : parser.entries()) {
        QVERIFY(entry.url.isValid());
        QVERIFY(entry.lastmod.isValid());
    }
}

// Test parsing a <sitemapindex> (like bbc.com/sitemap.xml pointing to sub-sitemaps)
void TestFangFeedDiscovery::testSitemapParserSitemapIndex()
{
    QString xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<sitemapindex xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
    <sitemap>
        <loc>https://www.bbc.com/sitemaps/https-sitemap-com-news-1.xml</loc>
    </sitemap>
    <sitemap>
        <loc>https://www.bbc.com/sitemaps/https-sitemap-com-news-2.xml</loc>
    </sitemap>
    <sitemap>
        <loc>https://www.bbc.com/sitemaps/https-sitemap-com-archive-1.xml</loc>
    </sitemap>
</sitemapindex>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::SitemapIndex);
    QVERIFY(parser.entries().isEmpty());
    QCOMPARE(parser.subSitemaps().size(), 3);
    QCOMPARE(parser.subSitemaps()[0].url, QUrl("https://www.bbc.com/sitemaps/https-sitemap-com-news-1.xml"));
    QCOMPARE(parser.subSitemaps()[1].url, QUrl("https://www.bbc.com/sitemaps/https-sitemap-com-news-2.xml"));
}

// Test that namespaced sitemaps with <news:news> extensions parse correctly
// (the parser only cares about <loc> and <lastmod>, ignoring news extensions)
void TestFangFeedDiscovery::testSitemapParserWithNamespaces()
{
    // This is what abc7news.com's actual sitemap looks like
    QString xml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9"
        xmlns:news="http://www.google.com/schemas/sitemap-news/0.9">
    <url>
        <loc>https://abc7news.com/post/tribal-members-shape-bay-area/18721725/</loc>
        <lastmod>2026-03-17T21:35:07+00:00</lastmod>
        <news:news>
            <news:publication>
                <news:name>KGO-TV</news:name>
                <news:language>en</news:language>
            </news:publication>
            <news:publication_date>2026-03-17T21:35:07+00:00</news:publication_date>
            <news:title>Tribal members to help shape Bay Area open space</news:title>
        </news:news>
    </url>
    <url>
        <loc>https://abc7news.com/post/teen-girl-jumps-from-moving-car/18725991/</loc>
        <lastmod>2026-03-17T20:47:32+00:00</lastmod>
        <news:news>
            <news:publication>
                <news:name>KGO-TV</news:name>
                <news:language>en</news:language>
            </news:publication>
            <news:publication_date>2026-03-17T20:47:32+00:00</news:publication_date>
            <news:title>Teen girl jumps from moving car to escape kidnapping</news:title>
        </news:news>
    </url>
</urlset>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::UrlSet);
    QCOMPARE(parser.entries().size(), 2);
    QVERIFY(parser.hasNewsEntries());

    // First entry
    QCOMPARE(parser.entries()[0].url, QUrl("https://abc7news.com/post/tribal-members-shape-bay-area/18721725/"));
    QVERIFY(parser.entries()[0].lastmod.isValid());
    QCOMPARE(parser.entries()[0].newsTitle, QString("Tribal members to help shape Bay Area open space"));
    QVERIFY(parser.entries()[0].publicationDate.isValid());
    QCOMPARE(parser.entries()[0].language, QString("en"));

    // Second entry
    QCOMPARE(parser.entries()[1].url, QUrl("https://abc7news.com/post/teen-girl-jumps-from-moving-car/18725991/"));
    QVERIFY(parser.entries()[1].lastmod.isValid());
    QCOMPARE(parser.entries()[1].newsTitle, QString("Teen girl jumps from moving car to escape kidnapping"));
    QCOMPARE(parser.entries()[1].language, QString("en"));
}

// Test that non-sitemap XML is rejected
void TestFangFeedDiscovery::testSitemapParserInvalid()
{
    // RSS feed
    SitemapParser parser1;
    QCOMPARE(parser1.parse("<rss version=\"2.0\"><channel></channel></rss>"), SitemapParser::Invalid);

    // HTML
    SitemapParser parser2;
    QCOMPARE(parser2.parse("<html><head></head><body></body></html>"), SitemapParser::Invalid);

    // Empty
    SitemapParser parser3;
    QCOMPARE(parser3.parse(""), SitemapParser::Invalid);

    // Garbage
    SitemapParser parser4;
    QCOMPARE(parser4.parse("not xml at all"), SitemapParser::Invalid);
}

// Test sitemap entries without <lastmod> (like bbc.com's main sitemap.xml)
void TestFangFeedDiscovery::testSitemapParserNoLastmod()
{
    // BBC's main sitemap has category pages with no lastmod
    QString xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
    <url>
        <loc>https://www.bbc.com/news</loc>
        <changefreq>hourly</changefreq>
        <priority>0.9</priority>
    </url>
    <url>
        <loc>https://www.bbc.com/sport</loc>
        <changefreq>hourly</changefreq>
        <priority>0.8</priority>
    </url>
</urlset>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::UrlSet);
    QCOMPARE(parser.entries().size(), 2);

    // All entries should have valid URLs but no lastmod
    for (const SitemapEntry& entry : parser.entries()) {
        QVERIFY(entry.url.isValid());
        QVERIFY(!entry.lastmod.isValid());
    }
}

// =====================================================================
// PageMetadataExtractor unit tests
// =====================================================================

// Test extraction of OG tags (like abc7news.com articles)
void TestFangFeedDiscovery::testPageMetadataOGTags()
{
    // Realistic XHTML as produced by TidyLib, based on abc7news.com article
    QString xhtml = R"(<?xml version="1.0" encoding="UTF-8"?>
<html xmlns="http://www.w3.org/1999/xhtml" lang="en-US">
<head>
    <title>Tribal members to help shape Bay Area open space - ABC7 San Francisco</title>
    <meta name="description" content="Indigenous communities in the South Bay are working to shape the future." />
    <meta property="og:title" content="Tribal members to help shape Bay Area open space as historic Juristac lands are reclaimed" />
    <meta property="og:description" content="Native American communities in the South Bay are working to shape the future of a newly-acquired open space." />
    <meta property="og:image" content="https://cdn.abcotvs.com/dip/images/18722796_031626-kgo-5p-sacred-gravel-vid.jpg" />
    <meta property="article:author" content="Drew Tuma" />
</head>
<body></body>
</html>)";

    PageMetadata meta = PageMetadataExtractor::extract(xhtml);

    // OG tags should take priority
    QCOMPARE(meta.title, QString("Tribal members to help shape Bay Area open space as historic Juristac lands are reclaimed"));
    QCOMPARE(meta.description, QString("Native American communities in the South Bay are working to shape the future of a newly-acquired open space."));
    QCOMPARE(meta.imageUrl, QUrl("https://cdn.abcotvs.com/dip/images/18722796_031626-kgo-5p-sacred-gravel-vid.jpg"));
    QCOMPARE(meta.author, QString("Drew Tuma"));
}

// Test fallback to standard HTML meta tags when OG tags are absent
void TestFangFeedDiscovery::testPageMetadataFallback()
{
    // HTML without OG tags, based on bbc.com news page structure
    QString xhtml = R"(<?xml version="1.0" encoding="UTF-8"?>
<html xmlns="http://www.w3.org/1999/xhtml" lang="en-GB">
<head>
    <title>BBC News - Breaking news and latest top stories</title>
    <meta name="description" content="Visit BBC News for the latest news, breaking news, video and analysis." />
    <meta name="author" content="BBC News" />
</head>
<body></body>
</html>)";

    PageMetadata meta = PageMetadataExtractor::extract(xhtml);

    // Should fall back to standard HTML tags
    QCOMPARE(meta.title, QString("BBC News - Breaking news and latest top stories"));
    QCOMPARE(meta.description, QString("Visit BBC News for the latest news, breaking news, video and analysis."));
    QVERIFY(!meta.imageUrl.isValid());
    QCOMPARE(meta.author, QString("BBC News"));
}

// Test empty/minimal HTML
void TestFangFeedDiscovery::testPageMetadataEmpty()
{
    // Minimal HTML with no metadata
    QString xhtml = R"(<html><head></head><body></body></html>)";

    PageMetadata meta = PageMetadataExtractor::extract(xhtml);

    QVERIFY(meta.title.isEmpty());
    QVERIFY(meta.description.isEmpty());
    QVERIFY(!meta.imageUrl.isValid());
    QVERIFY(meta.author.isEmpty());
}

// --------------------------------------------------------------------------
// Google News sitemap tests
// --------------------------------------------------------------------------

void TestFangFeedDiscovery::testSitemapParserAPNews()
{
    // AP News news-sitemap-content.xml format
    QString xml = R"(<?xml version='1.0' encoding='UTF-8'?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9"
        xmlns:news="http://www.google.com/schemas/sitemap-news/0.9"
        xmlns:image="http://www.google.com/schemas/sitemap-image/1.1">
    <url>
        <lastmod>2026-03-18T05:11:51-04:00</lastmod>
        <loc>https://apnews.com/article/iran-confirms-security-chief-killed</loc>
        <news:news>
            <news:publication>
                <news:name>Associated Press</news:name>
                <news:language>eng</news:language>
            </news:publication>
            <news:publication_date>2026-03-17T00:03:19-04:00</news:publication_date>
            <news:title>Iran confirms security chief Larijani killed</news:title>
        </news:news>
    </url>
    <url>
        <lastmod>2026-03-18T16:59:58-04:00</lastmod>
        <loc>https://apnews.com/article/senegal-marruecos-copa-africana</loc>
        <news:news>
            <news:publication>
                <news:name>Associated Press</news:name>
                <news:language>spa</news:language>
            </news:publication>
            <news:publication_date>2026-03-18T16:59:46-04:00</news:publication_date>
            <news:title>Senegal condena decisión de quitarle la Copa África</news:title>
        </news:news>
    </url>
    <url>
        <lastmod>2026-03-17T22:10:13-04:00</lastmod>
        <loc>https://apnews.com/article/bruins-canadiens-score</loc>
        <news:news>
            <news:publication>
                <news:name>Associated Press</news:name>
                <news:language>eng</news:language>
            </news:publication>
            <news:publication_date>2026-03-17T22:09:43-04:00</news:publication_date>
            <news:title>Caufield scores in OT as Canadiens top Bruins</news:title>
        </news:news>
    </url>
</urlset>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::UrlSet);
    QCOMPARE(parser.entries().size(), 3);
    QVERIFY(parser.hasNewsEntries());

    QList<SitemapEntry> entries = parser.entries();

    // First entry
    const SitemapEntry& first = entries[0];
    QCOMPARE(first.url, QUrl("https://apnews.com/article/iran-confirms-security-chief-killed"));
    QCOMPARE(first.newsTitle, QString("Iran confirms security chief Larijani killed"));
    QCOMPARE(first.publicationName, QString("Associated Press"));
    QCOMPARE(first.language, QString("eng"));
    QVERIFY(first.publicationDate.isValid());
    QVERIFY(first.lastmod.isValid());

    // Spanish entry
    const SitemapEntry& spanish = entries[1];
    QCOMPARE(spanish.language, QString("spa"));
    QCOMPARE(spanish.newsTitle, QString("Senegal condena decisión de quitarle la Copa África"));
    QCOMPARE(spanish.publicationName, QString("Associated Press"));
}

void TestFangFeedDiscovery::testSitemapParserUSAToday()
{
    // USA Today news-sitemap.xml format (note: <news:publication_date> comes before <news:title>)
    QString xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9"
        xmlns:news="http://www.google.com/schemas/sitemap-news/0.9"
        xmlns:image="http://www.google.com/schemas/sitemap-image/1.1">
    <url>
        <loc>https://www.usatoday.com/story/entertainment/celebrities/2026/03/18/eric-dane-wife/89215612007/</loc>
        <lastmod>2026-03-18T22:42:41.291969436Z</lastmod>
        <news:news>
            <news:publication_date>2026-03-18T22:42:41.291969436Z</news:publication_date>
            <news:title>Rebecca Gayheart makes rare appearance since Eric Dane's death</news:title>
            <news:publication>
                <news:language>en</news:language>
                <news:name>USA TODAY</news:name>
            </news:publication>
        </news:news>
        <image:image>
            <image:loc>https://www.gannett-cdn.com/image.jpg</image:loc>
        </image:image>
    </url>
    <url>
        <loc>https://www.usatoday.com/story/news/nation/2026/03/18/cesar-chavez-legacy/89210079007/</loc>
        <lastmod>2026-03-18T22:41:11.193527492Z</lastmod>
        <news:news>
            <news:publication_date>2026-03-18T21:16:50.64041652Z</news:publication_date>
            <news:title>What happens to Cesar Chavez's legacy?</news:title>
            <news:publication>
                <news:language>en</news:language>
                <news:name>USA TODAY</news:name>
            </news:publication>
        </news:news>
    </url>
</urlset>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::UrlSet);
    QCOMPARE(parser.entries().size(), 2);
    QVERIFY(parser.hasNewsEntries());

    // USA Today puts <news:publication_date> before <news:title> and
    // <news:language> before <news:name> inside <news:publication>.
    QList<SitemapEntry> entries = parser.entries();

    const SitemapEntry& first = entries[0];
    QCOMPARE(first.newsTitle, QString("Rebecca Gayheart makes rare appearance since Eric Dane's death"));
    QCOMPARE(first.publicationName, QString("USA TODAY"));
    QCOMPARE(first.language, QString("en"));
    QVERIFY(first.publicationDate.isValid());
    QCOMPARE(first.imageUrl, QUrl("https://www.gannett-cdn.com/image.jpg"));

    const SitemapEntry& second = entries[1];
    QCOMPARE(second.newsTitle, QString("What happens to Cesar Chavez's legacy?"));
    QCOMPARE(second.publicationName, QString("USA TODAY"));
    QVERIFY(!second.imageUrl.isValid()); // No image in second entry
}

void TestFangFeedDiscovery::testSitemapParserBloomberg()
{
    // Bloomberg sitemaps/news/latest.xml format
    QString xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9"
        xmlns:news="http://www.google.com/schemas/sitemap-news/0.9">
    <url>
        <loc>https://www.bloomberg.com/news/articles/2026-03-18/us-snubbed-at-minerals-summit</loc>
        <lastmod>2026-03-18T22:34:15.466Z</lastmod>
        <changefreq>always</changefreq>
        <priority>1</priority>
        <news:news>
            <news:publication>
                <news:name>Bloomberg News</news:name>
                <news:language>en</news:language>
            </news:publication>
            <news:publication_date>2026-03-18T11:10:47.694Z</news:publication_date>
            <news:title>US Snubbed by Lula Government at Critical Minerals Summit</news:title>
        </news:news>
    </url>
    <url>
        <loc>https://www.bloomberg.com/news/newsletters/2026-03-18/powell-evening-briefing</loc>
        <lastmod>2026-03-18T22:32:39.892Z</lastmod>
        <changefreq>always</changefreq>
        <priority>1</priority>
        <news:news>
            <news:publication>
                <news:name>Bloomberg News</news:name>
                <news:language>en</news:language>
            </news:publication>
            <news:publication_date>2026-03-18T22:32:39.893Z</news:publication_date>
            <news:title>Powell Says He's Sticking Around: Evening Briefing Americas</news:title>
        </news:news>
    </url>
</urlset>)";

    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(xml);

    QCOMPARE(type, SitemapParser::UrlSet);
    QCOMPARE(parser.entries().size(), 2);
    QVERIFY(parser.hasNewsEntries());

    // Bloomberg includes <changefreq> and <priority> which we should ignore.
    QList<SitemapEntry> entries = parser.entries();

    const SitemapEntry& first = entries[0];
    QCOMPARE(first.newsTitle, QString("US Snubbed by Lula Government at Critical Minerals Summit"));
    QCOMPARE(first.publicationName, QString("Bloomberg News"));
    QCOMPARE(first.language, QString("en"));
    QVERIFY(first.publicationDate.isValid());
    QVERIFY(first.lastmod.isValid());
}

void TestFangFeedDiscovery::testSitemapParserLanguageFiltering()
{
    // Simulates AP News with mixed English and Spanish entries.
    // The SitemapParser itself doesn't filter, but we verify fields are correct
    // so GoogleNewsSitemapSynthesizer can filter.
    QString xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9"
        xmlns:news="http://www.google.com/schemas/sitemap-news/0.9">
    <url>
        <loc>https://example.com/article/english-one</loc>
        <news:news>
            <news:publication>
                <news:name>Example News</news:name>
                <news:language>eng</news:language>
            </news:publication>
            <news:publication_date>2026-03-18T10:00:00Z</news:publication_date>
            <news:title>English Article One</news:title>
        </news:news>
    </url>
    <url>
        <loc>https://example.com/article/spanish-one</loc>
        <news:news>
            <news:publication>
                <news:name>Example News</news:name>
                <news:language>spa</news:language>
            </news:publication>
            <news:publication_date>2026-03-18T09:00:00Z</news:publication_date>
            <news:title>Artículo en Español</news:title>
        </news:news>
    </url>
    <url>
        <loc>https://example.com/article/english-two</loc>
        <news:news>
            <news:publication>
                <news:name>Example News</news:name>
                <news:language>eng</news:language>
            </news:publication>
            <news:publication_date>2026-03-18T08:00:00Z</news:publication_date>
            <news:title>English Article Two</news:title>
        </news:news>
    </url>
</urlset>)";

    SitemapParser parser;
    parser.parse(xml);

    QCOMPARE(parser.entries().size(), 3);

    // Verify language codes are captured correctly for downstream filtering.
    QCOMPARE(parser.entries()[0].language, QString("eng"));
    QCOMPARE(parser.entries()[1].language, QString("spa"));
    QCOMPARE(parser.entries()[2].language, QString("eng"));

    // Verify all entries have the same publication name.
    for (const SitemapEntry& entry : parser.entries()) {
        QCOMPARE(entry.publicationName, QString("Example News"));
    }
}

// --------------------------------------------------------------------------
// Robots.txt parsing tests
// --------------------------------------------------------------------------

void TestFangFeedDiscovery::testRobotsTxtParsing()
{
    QUrl baseUrl("https://www.bloomberg.com");

    // Bloomberg-style robots.txt
    QString robotsTxt =
        "User-agent: *\n"
        "Disallow: /api/\n"
        "\n"
        "Sitemap: https://www.bloomberg.com/sitemaps/news/index.xml\n"
        "Sitemap: https://www.bloomberg.com/sitemaps/news/latest.xml\n"
        "Sitemap: https://www.bloomberg.com/sitemaps/collections/index.xml\n"
        "Sitemap: https://www.bloomberg.com/sitemaps/media/video/index.xml\n"
        "Sitemap: https://www.bloomberg.com/billionaires/sitemap.xml\n";

    QList<QUrl> results = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(robotsTxt, baseUrl);

    // News sitemaps first, then generic sitemaps.
    QCOMPARE(results.size(), 5);
    QCOMPARE(results[0], QUrl("https://www.bloomberg.com/sitemaps/news/index.xml"));
    QCOMPARE(results[1], QUrl("https://www.bloomberg.com/sitemaps/news/latest.xml"));
    QCOMPARE(results[2], QUrl("https://www.bloomberg.com/sitemaps/collections/index.xml"));
    QCOMPARE(results[3], QUrl("https://www.bloomberg.com/sitemaps/media/video/index.xml"));
    QCOMPARE(results[4], QUrl("https://www.bloomberg.com/billionaires/sitemap.xml"));

    // AP News style
    QString apRobots =
        "Sitemap: https://apnews.com/ap-sitemap.xml\n"
        "Sitemap: https://apnews.com/news-sitemap-content.xml\n"
        "Sitemap: https://apnews.com/hubs-sitemap-content.xml\n"
        "Sitemap: https://apnews.com/video-sitemap.xml\n";

    QList<QUrl> apResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        apRobots, QUrl("https://apnews.com"));
    QCOMPARE(apResults.size(), 4);
    // News-specific first.
    QCOMPARE(apResults[0], QUrl("https://apnews.com/news-sitemap-content.xml"));
    // Then generic sitemaps.
    QCOMPARE(apResults[1], QUrl("https://apnews.com/ap-sitemap.xml"));
    QCOMPARE(apResults[2], QUrl("https://apnews.com/hubs-sitemap-content.xml"));
    QCOMPARE(apResults[3], QUrl("https://apnews.com/video-sitemap.xml"));

    // USA Today style
    QString usatRobots =
        "Sitemap: https://www.usatoday.com/news-sitemap.xml\n"
        "Sitemap: https://www.usatoday.com/web-sitemap-index.xml\n"
        "Sitemap: https://www.usatoday.com/money/blueprint/sitemap-news.xml\n"
        "Sitemap: https://www.usatoday.com/online-betting/news-sitemap.xml\n";

    QList<QUrl> usatResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        usatRobots, QUrl("https://www.usatoday.com"));
    QCOMPARE(usatResults.size(), 4);
    // News-specific first.
    QCOMPARE(usatResults[0], QUrl("https://www.usatoday.com/news-sitemap.xml"));
    QCOMPARE(usatResults[1], QUrl("https://www.usatoday.com/money/blueprint/sitemap-news.xml"));
    QCOMPARE(usatResults[2], QUrl("https://www.usatoday.com/online-betting/news-sitemap.xml"));
    // Then generic.
    QCOMPARE(usatResults[3], QUrl("https://www.usatoday.com/web-sitemap-index.xml"));

    // Empty robots.txt
    QList<QUrl> emptyResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        "", QUrl("https://example.com"));
    QVERIFY(emptyResults.isEmpty());

    // Sitemaps from a different host should be excluded.
    QString crossHost = "Sitemap: https://cdn.otherdomain.com/news-sitemap.xml\n";
    QList<QUrl> crossResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        crossHost, QUrl("https://www.example.com"));
    QVERIFY(crossResults.isEmpty());

    // www/non-www should be treated as the same host (e.g. reuters.com robots.txt
    // lists sitemaps on www.reuters.com).
    QString wwwSitemaps =
        "Sitemap: https://www.reuters.com/arc/outboundfeeds/news-sitemap/1\n";
    QList<QUrl> wwwResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        wwwSitemaps, QUrl("https://reuters.com"));
    QCOMPARE(wwwResults.size(), 1);
    QCOMPARE(wwwResults[0], QUrl("https://www.reuters.com/arc/outboundfeeds/news-sitemap/1"));

    // ESPN style: only a generic /sitemap.xml in robots.txt (no "news" in path).
    // Should still be returned (after news-specific ones, which there are none of).
    QString espnRobots =
        "Sitemap: https://www.espn.com/sitemap.xml\n";
    QList<QUrl> espnResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        espnRobots, QUrl("https://www.espn.com"));
    QCOMPARE(espnResults.size(), 1);
    QCOMPARE(espnResults[0], QUrl("https://www.espn.com/sitemap.xml"));
}

// Test robots.txt auto-discovery: generic sitemaps are returned as lower-priority
// candidates so that sitemap indexes (like ESPN's /sitemap.xml) can be crawled
// to discover news sub-sitemaps.
void TestFangFeedDiscovery::testRobotsTxtAutoDiscovery()
{
    // NJ.com (Advance Local): has both news-specific and generic sitemaps.
    // News-specific should come first.
    QString njRobots =
        "Sitemap: https://www.nj.com/arc/outboundfeeds/rss-latest/?outputType=xml\n"
        "Sitemap: https://www.nj.com/arc/outboundfeeds/sitemap-index/?outputType=xml\n"
        "Sitemap: https://www.nj.com/arc/outboundfeeds/news-sitemap-index/?outputType=xml\n"
        "Sitemap: https://www.nj.com/arc/outboundfeeds/sitemap-index-by-day/\n"
        "Sitemap: https://www.nj.com/arc/outboundfeeds/evg_updates/\n"
        "Sitemap: https://www.nj.com/arc/outboundfeeds/google-news-feed/\n";

    QList<QUrl> njResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        njRobots, QUrl("https://www.nj.com"));
    // "news" appears in news-sitemap-index and google-news-feed.
    QVERIFY(njResults.size() == 6);
    // News-specific first.
    QCOMPARE(njResults[0], QUrl("https://www.nj.com/arc/outboundfeeds/news-sitemap-index/?outputType=xml"));
    QCOMPARE(njResults[1], QUrl("https://www.nj.com/arc/outboundfeeds/google-news-feed/"));
    // Then generic.
    QCOMPARE(njResults[2], QUrl("https://www.nj.com/arc/outboundfeeds/rss-latest/?outputType=xml"));
    QCOMPARE(njResults[3], QUrl("https://www.nj.com/arc/outboundfeeds/sitemap-index/?outputType=xml"));
    QCOMPARE(njResults[4], QUrl("https://www.nj.com/arc/outboundfeeds/sitemap-index-by-day/"));
    QCOMPARE(njResults[5], QUrl("https://www.nj.com/arc/outboundfeeds/evg_updates/"));

    // Syracuse.com: same Advance Local pattern.
    QString syracuseRobots =
        "Sitemap: https://www.syracuse.com/arc/outboundfeeds/rss-latest/?outputType=xml\n"
        "Sitemap: https://www.syracuse.com/arc/outboundfeeds/sitemap-index/?outputType=xml\n"
        "Sitemap: https://www.syracuse.com/arc/outboundfeeds/news-sitemap-index/?outputType=xml\n"
        "Sitemap: https://www.syracuse.com/arc/outboundfeeds/sitemap-index-by-day/\n"
        "Sitemap: https://www.syracuse.com/arc/outboundfeeds/evg_updates/\n"
        "Sitemap: https://www.syracuse.com/arc/outboundfeeds/google-news-feed/\n";

    QList<QUrl> syracuseResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        syracuseRobots, QUrl("https://www.syracuse.com"));
    QCOMPARE(syracuseResults.size(), 6);
    // News-specific first.
    QCOMPARE(syracuseResults[0], QUrl("https://www.syracuse.com/arc/outboundfeeds/news-sitemap-index/?outputType=xml"));
    QCOMPARE(syracuseResults[1], QUrl("https://www.syracuse.com/arc/outboundfeeds/google-news-feed/"));

    // SF Chronicle (Hearst): has sitemap_news.xml (news-specific) and generic sitemaps.
    QString sfcRobots =
        "Sitemap: https://www.sfchronicle.com/sitemap.xml\n"
        "Sitemap: https://www.sfchronicle.com/sitemap_news.xml\n"
        "Sitemap: https://www.sfchronicle.com/projects/sitemap_projects.xml\n"
        "Sitemap: https://www.sfchronicle.com/video-sitemap-index.xml\n";

    QList<QUrl> sfcResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        sfcRobots, QUrl("https://www.sfchronicle.com"));
    QCOMPARE(sfcResults.size(), 4);
    // News-specific first: sitemap_news.xml has "news" in path.
    QCOMPARE(sfcResults[0], QUrl("https://www.sfchronicle.com/sitemap_news.xml"));
    // Then generic sitemaps.
    QCOMPARE(sfcResults[1], QUrl("https://www.sfchronicle.com/sitemap.xml"));
    QCOMPARE(sfcResults[2], QUrl("https://www.sfchronicle.com/projects/sitemap_projects.xml"));
    QCOMPARE(sfcResults[3], QUrl("https://www.sfchronicle.com/video-sitemap-index.xml"));

    // 1077thebone.com: only a generic /sitemap.xml.
    QString boneRobots =
        "Sitemap: https://www.1077thebone.com/sitemap.xml\n";
    QList<QUrl> boneResults = GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(
        boneRobots, QUrl("https://www.1077thebone.com"));
    QCOMPARE(boneResults.size(), 1);
    QCOMPARE(boneResults[0], QUrl("https://www.1077thebone.com/sitemap.xml"));
}

// =====================================================================
// Full flow integration tests for specific sites
// =====================================================================

// ESPN: No RSS in HTML -> common paths fail -> sitemap discovery via
// robots.txt generic /sitemap.xml -> sitemap index -> news sub-sitemap.
void TestFangFeedDiscovery::testESPNFullFlow()
{
    // Load the actual ESPN HTML.
    QString projectPath = PROJECT_PATH;
    QFile file(projectPath + "/feeds/espn.com");
    QVERIFY2(file.open(QFile::ReadOnly | QFile::Text), "Could not open ESPN HTML file");

    QByteArray rawHtml = file.readAll();
    file.close();

    // Process through WebPageGrabber.
    WebPageGrabber webGrabber;
    QString* processedHtml = webGrabber.load(rawHtml);
    QVERIFY2(processedHtml != nullptr, "WebPageGrabber failed to process ESPN HTML");
    QString htmlContent = *processedHtml;

    // Verify no RSS/Atom links in ESPN's HTML.
    FeedDiscovery fdCheck;
    QList<QString> feedURLs = fdCheck.parseFeedsFromXHTML(htmlContent);
    QVERIFY2(feedURLs.isEmpty(), "ESPN HTML unexpectedly contains RSS/Atom links");

    // Set up mocks for the full flow.
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();
    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlESPN = htmlContent;
    pageGrabber->setMockDocument(&persistentHtmlESPN);

    // No common paths configured -> all will fail with default NETWORK_ERROR.

    // Configure mock synthesizer to return a feed (simulating the
    // robots.txt -> sitemap.xml -> sitemap index -> googlenewssitemap chain).
    RawFeed* espnFeed = new RawFeed(sitemapSynth);
    espnFeed->feedType = RawFeed::GoogleNewsSitemap;
    espnFeed->title = "ESPN";
    espnFeed->url = QUrl("https://www.espn.com/googlenewssitemap");

    RawNews* item1 = new RawNews(espnFeed);
    item1->title = "LeBron James 6 dunks key Lakers 7th straight win";
    item1->url = QUrl("https://www.espn.com/nba/story/_/id/48246814");
    espnFeed->items.append(item1);

    RawNews* item2 = new RawNews(espnFeed);
    item2->title = "Morocco cannot claim Senegal AFCON title";
    item2->url = QUrl("https://www.espn.com/espn/story/_/id/48246762");
    espnFeed->items.append(item2);

    sitemapSynth->setResult(espnFeed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser, sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("https://www.espn.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY2(!fd.error(), qPrintable("ESPN discovery failed: " + fd.errorString()));
    QCOMPARE(fd.feedURL(), QUrl("https://www.espn.com/googlenewssitemap"));
    QVERIFY(fd.feedResult() != nullptr);
    QCOMPARE(fd.feedResult()->items.size(), 2);
    QCOMPARE(fd.feedResult()->title, QString("ESPN"));

    QCOMPARE(fd.feedCount(), 1);
    QVERIFY(fd.discoveredFeeds().first().validated);
}

// 1077thebone.com: No RSS in HTML -> common path /feed returns valid feed.
void TestFangFeedDiscovery::testCommonPathFallbackFlow()
{
    // Load the actual HTML.
    QString projectPath = PROJECT_PATH;
    QFile file(projectPath + "/feeds/1077thebone.com");
    QVERIFY2(file.open(QFile::ReadOnly | QFile::Text), "Could not open 1077thebone HTML file");

    QByteArray rawHtml = file.readAll();
    file.close();

    WebPageGrabber webGrabber;
    QString* processedHtml = webGrabber.load(rawHtml);
    QVERIFY2(processedHtml != nullptr, "WebPageGrabber failed to process 1077thebone HTML");
    QString htmlContent = *processedHtml;

    // Verify no RSS/Atom links in 1077thebone's HTML.
    FeedDiscovery fdCheck;
    QList<QString> feedURLs = fdCheck.parseFeedsFromXHTML(htmlContent);
    QVERIFY2(feedURLs.isEmpty(), "1077thebone HTML unexpectedly contains RSS/Atom links");

    // Set up mocks.
    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlBone = htmlContent;
    pageGrabber->setMockDocument(&persistentHtmlBone);

    // Common path /feed returns a valid feed.
    RawFeed* boneFeed = new RawFeed();
    boneFeed->title = "107.7 The Bone";
    boneFeed->url = QUrl("https://www.1077thebone.com/feed");
    RawNews* item = new RawNews(boneFeed);
    item->title = "Rock News Roundup";
    item->url = QUrl("https://www.1077thebone.com/rock-news-roundup");
    boneFeed->items.append(item);
    feedParser->addResponse(QUrl("https://www.1077thebone.com/feed"), ParserInterface::OK, boneFeed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("https://www.1077thebone.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY2(!fd.error(), qPrintable("1077thebone discovery failed: " + fd.errorString()));
    QCOMPARE(fd.feedURL(), QUrl("https://www.1077thebone.com/feed"));
    QVERIFY(fd.feedResult() != nullptr);
    QCOMPARE(fd.feedResult()->title, QString("107.7 The Bone"));
}

// =====================================================================
// Sitemap integration tests (injectable synthesizer)
// =====================================================================

void TestFangFeedDiscovery::testSitemapSuccessIntegration()
{
    // Full discovery: parse fails -> HTML has no feeds -> common paths fail ->
    // mock synthesizer returns a feed with 2 items -> FEED_FOUND.

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();
    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlSitemap1 = "<html><head><title>SFGate</title></head><body></body></html>";
    pageGrabber->setMockDocument(&persistentHtmlSitemap1);

    // Don't configure any feed parser responses -- all common paths will fail.

    // Configure mock synthesizer to return a feed with 2 items.
    RawFeed* sitemapFeed = new RawFeed(sitemapSynth);
    sitemapFeed->feedType = RawFeed::GoogleNewsSitemap;
    sitemapFeed->title = "SFGate";
    sitemapFeed->url = QUrl("https://www.sfgate.com/sitemap_news.xml");

    RawNews* item1 = new RawNews(sitemapFeed);
    item1->title = "Local news article one";
    item1->url = QUrl("https://www.sfgate.com/local/article1");
    sitemapFeed->items.append(item1);

    RawNews* item2 = new RawNews(sitemapFeed);
    item2->title = "Local news article two";
    item2->url = QUrl("https://www.sfgate.com/local/article2");
    sitemapFeed->items.append(item2);

    sitemapSynth->setResult(sitemapFeed);

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser, sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("https://www.sfgate.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY2(!fd.error(), qPrintable("Unexpected error: " + fd.errorString()));
    QCOMPARE(fd.feedURL(), QUrl("https://www.sfgate.com/sitemap_news.xml"));
    QVERIFY(fd.feedResult() != nullptr);
    QCOMPARE(fd.feedResult()->items.size(), 2);
    QCOMPARE(fd.feedResult()->title, QString("SFGate"));

    QCOMPARE(fd.feedCount(), 1);
    QList<FeedDiscovery::DiscoveredFeed> feeds = fd.discoveredFeeds();
    QCOMPARE(feeds.count(), 1);
    QCOMPARE(feeds.first().url, QUrl("https://www.sfgate.com/sitemap_news.xml"));
    QVERIFY(feeds.first().validated);
}

void TestFangFeedDiscovery::testSitemapErrorIntegration()
{
    // Same flow but mock synthesizer returns an error -> FEED_ERROR.

    MockNewsParser* firstParser = new MockNewsParser();
    MockWebPageGrabber* pageGrabber = new MockWebPageGrabber();
    MockBatchNewsParser* feedParser = new MockBatchNewsParser();
    MockGoogleNewsSitemapSynthesizer* sitemapSynth = new MockGoogleNewsSitemapSynthesizer();

    firstParser->setResult(ParserInterface::PARSE_ERROR);

    static QString persistentHtmlSitemap2 = "<html><head><title>Broken Site</title></head><body></body></html>";
    pageGrabber->setMockDocument(&persistentHtmlSitemap2);

    // Configure mock synthesizer to return an error.
    sitemapSynth->setError("No feed found");

    FeedDiscovery fd(nullptr, firstParser, new MockNewsParser(), pageGrabber, feedParser, sitemapSynth);
    QSignalSpy spy(&fd, &FeedDiscovery::done);

    fd.checkFeed("https://www.brokensite.com");

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    QVERIFY(fd.error());
    QCOMPARE(fd.errorString(), QString("No feed found"));
}

// =====================================================================
// Deduplication tests
// =====================================================================

void TestFangFeedDiscovery::testDeduplicateRepetitiveTitles()
{
    // 10 lottery entries with same 4-word prefix + 5 unique articles -> 1 + 5 = 6
    QList<SitemapEntry> entries;

    for (int i = 0; i < 10; ++i) {
        SitemapEntry entry;
        entry.newsTitle = QString("Winning numbers drawn in %1 Lottery").arg(
            QStringList({"California", "Texas", "Florida", "Nevada", "Ohio",
                         "Oregon", "Maine", "Idaho", "Utah", "Iowa"})[i]);
        entry.url = QUrl(QString("https://example.com/lottery/%1").arg(i));
        entry.publicationDate = QDateTime(QDate(2026, 3, 18), QTime(10, 0, 0), QTimeZone::UTC)
            .addSecs(-i * 3600);
        entries.append(entry);
    }

    for (int i = 0; i < 5; ++i) {
        SitemapEntry entry;
        entry.newsTitle = QString("Unique article number %1 about news").arg(i);
        entry.url = QUrl(QString("https://example.com/article/%1").arg(i));
        entry.publicationDate = QDateTime(QDate(2026, 3, 18), QTime(10, 0, 0), QTimeZone::UTC)
            .addSecs(-i * 3600);
        entries.append(entry);
    }

    QList<SitemapEntry> result = GoogleNewsSitemapSynthesizer::deduplicateRepetitiveTitles(entries);

    // 10 lottery -> 1 kept, 5 unique -> 5 kept = 6 total
    QCOMPARE(result.size(), 6);

    // Count lottery entries in result
    int lotteryCount = 0;
    for (const SitemapEntry& e : result) {
        if (e.newsTitle.startsWith("Winning numbers")) {
            lotteryCount++;
        }
    }
    QCOMPARE(lotteryCount, 1);
}

void TestFangFeedDiscovery::testDeduplicateNoRepetition()
{
    // 10 unique articles -> all 10 preserved
    QList<SitemapEntry> entries;

    QStringList titles = {
        "Mayor announces new transit plan",
        "Local restaurant wins prestigious award",
        "Tech company opens downtown office",
        "School board votes on budget proposal",
        "Fire department gets new equipment",
        "Park renovation project completed today",
        "Hospital expands emergency room capacity",
        "Bridge repair work begins next week",
        "Community center hosts annual festival",
        "Police department launches new program"
    };

    for (int i = 0; i < titles.size(); ++i) {
        SitemapEntry entry;
        entry.newsTitle = titles[i];
        entry.url = QUrl(QString("https://example.com/article/%1").arg(i));
        entry.publicationDate = QDateTime(QDate(2026, 3, 18), QTime(10, 0, 0), QTimeZone::UTC)
            .addSecs(-i * 3600);
        entries.append(entry);
    }

    QList<SitemapEntry> result = GoogleNewsSitemapSynthesizer::deduplicateRepetitiveTitles(entries);
    QCOMPARE(result.size(), 10);
}

void TestFangFeedDiscovery::testDeduplicateKeepsMostRecent()
{
    // 5 entries with same prefix, middle one most recent -> kept entry is the middle one
    QList<SitemapEntry> entries;

    QDateTime baseTime(QDate(2026, 3, 18), QTime(10, 0, 0), QTimeZone::UTC);

    for (int i = 0; i < 5; ++i) {
        SitemapEntry entry;
        entry.newsTitle = QString("Winning numbers drawn in State%1 Lottery").arg(i);
        entry.url = QUrl(QString("https://example.com/lottery/%1").arg(i));
        // Middle entry (i==2) has the most recent date
        if (i == 2) {
            entry.publicationDate = baseTime.addSecs(3600); // 1 hour ahead
        } else {
            entry.publicationDate = baseTime.addSecs(-i * 3600);
        }
        entries.append(entry);
    }

    QList<SitemapEntry> result = GoogleNewsSitemapSynthesizer::deduplicateRepetitiveTitles(
        entries, 4, 3);

    // Group of 5 > threshold of 3 -> deduplicated to 1
    QCOMPARE(result.size(), 1);
    // The kept entry should be the most recent one (index 2)
    QVERIFY(result[0].newsTitle.contains("State2"));
}

void TestFangFeedDiscovery::testDeduplicateSmallList()
{
    // 3 entries with same prefix (at threshold) -> not deduped, all 3 kept
    QList<SitemapEntry> entries;

    for (int i = 0; i < 3; ++i) {
        SitemapEntry entry;
        entry.newsTitle = QString("Winning numbers drawn in State%1 Lottery").arg(i);
        entry.url = QUrl(QString("https://example.com/lottery/%1").arg(i));
        entry.publicationDate = QDateTime(QDate(2026, 3, 18), QTime(10, 0, 0), QTimeZone::UTC)
            .addSecs(-i * 3600);
        entries.append(entry);
    }

    QList<SitemapEntry> result = GoogleNewsSitemapSynthesizer::deduplicateRepetitiveTitles(entries);

    // 3 == threshold of 3, so NOT deduped
    QCOMPARE(result.size(), 3);
}

// =====================================================================
// JSON Feed link detection
// =====================================================================

void TestFangFeedDiscovery::testJSONFeedLinkDetection()
{
    // HTML page with a JSON Feed link tag.
    QString html = R"(<!DOCTYPE html>
<html>
<head>
<title>Test Site</title>
<link rel="alternate" type="application/feed+json" title="JSON Feed" href="https://example.org/feed.json" />
<link rel="alternate" type="application/rss+xml" title="RSS Feed" href="https://example.org/feed.xml" />
</head>
<body><p>Hello</p></body>
</html>)";

    WebPageGrabber grabber;
    QString* xmlDoc = grabber.load(html.toUtf8());
    QVERIFY(xmlDoc != nullptr);

    FeedDiscovery fd;
    QList<QString> feedURLs = fd.parseFeedsFromXHTML(*xmlDoc);

    QVERIFY2(feedURLs.contains("https://example.org/feed.json"),
             "JSON Feed URL not found");
    QVERIFY2(feedURLs.contains("https://example.org/feed.xml"),
             "RSS Feed URL not found");
}

QTEST_MAIN(TestFangFeedDiscovery)

#include "tst_testfangfeeddiscovery.moc"
