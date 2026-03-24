#include <memory>

#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QMap>
#include <QQueue>

#include "../../src/parser/BatchFeedFetcher.h"
#include "../../src/parser/FeedSource.h"
#include "../../src/parser/RawFeed.h"
#include "../MockFeedSource.h"

/**
 * @brief Testable version of BatchFeedFetcher that uses mock parsers
 */
class TestableBatchFeedFetcher : public BatchFeedFetcher
{
    Q_OBJECT

public:
    explicit TestableBatchFeedFetcher(QObject* parent = nullptr)
        : BatchFeedFetcher(parent)
    {
    }

    // Configure mock responses for specific URLs
    void addMockResponse(const QUrl& url, FeedSource::ParseResult result, RawFeed* feed = nullptr)
    {
        MockResponseConfig config;
        config.result = result;
        config.feed = feed;
        mockConfigs[url] = config;
    }

protected:
    // Override factory method to create mock parsers instead of real ones
    std::unique_ptr<FeedSource> createParser() override
    {
        auto parser = std::make_unique<MockFeedSource>();

        // Store the raw pointer so we can configure it when parse() is called with a URL
        pendingParsers.enqueue(parser.get());

        return parser;
    }

public:
    // Override parse to configure parsers with their URLs
    void parse(const QList<QUrl> &urls) override
    {
        // Clear pending parsers from any previous calls
        pendingParsers.clear();

        // Call base class parse which will call createParser() for each URL
        BatchFeedFetcher::parse(urls);

        // Now configure each parser that was created
        // The parsers are connected and have already started parsing, but MockFeedSource
        // will emit done() asynchronously, so we can still configure them
        int urlIndex = 0;
        for (const QUrl& url : urls) {
            // Skip duplicates (BatchFeedFetcher skips them too)
            if (urlIndex > 0 && urls.mid(0, urlIndex).contains(url)) {
                continue;
            }

            if (!pendingParsers.isEmpty()) {
                MockFeedSource* parser = pendingParsers.dequeue();

                // Configure the parser based on our mock configs
                if (mockConfigs.contains(url)) {
                    MockResponseConfig config = mockConfigs[url];
                    parser->setResult(config.result);
                    parser->setURL(url);
                    if (config.feed) {
                        parser->setFeed(config.feed);
                    }
                } else {
                    // Default to network error if not configured
                    parser->setResult(FeedSource::NETWORK_ERROR);
                    parser->setURL(url);
                }
            }

            urlIndex++;
        }
    }

private:
    struct MockResponseConfig {
        FeedSource::ParseResult result;
        RawFeed* feed = nullptr;
    };

    QMap<QUrl, MockResponseConfig> mockConfigs;
    QQueue<MockFeedSource*> pendingParsers;
};

class TestBatchFeedFetcher : public QObject
{
    Q_OBJECT

public:
    TestBatchFeedFetcher();

private slots:
    void testEmptyURLList();
    void testSingleFeedSuccess();
    void testSingleFeedNetworkError();
    void testSingleFeedParseError();
    void testMultipleFeedsAllSuccess();
    void testMultipleFeedsMixedResults();
    void testDuplicateURLsSkipped();
    void testGetFeedSuccess();
    void testGetFeedFailure();
    void testGetFeedUnknownURL();
    void testGetResultsAccessor();
    void testParserReuse();

private:
    RawFeed* createTestFeed(const QString& url, const QString& title);
};

TestBatchFeedFetcher::TestBatchFeedFetcher()
{
}

RawFeed* TestBatchFeedFetcher::createTestFeed(const QString& url, const QString& title)
{
    RawFeed* feed = new RawFeed();
    feed->url = QUrl(url);
    feed->title = title;
    return feed;
}

// Test that an empty URL list doesn't crash and doesn't emit ready()
void TestBatchFeedFetcher::testEmptyURLList()
{
    TestableBatchFeedFetcher parser;
    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    QList<QUrl> urls;
    parser.parse(urls);

    // Empty list should not emit ready() signal
    QTest::qWait(100);
    QCOMPARE(spy.count(), 0);

    // Results should be empty
    QCOMPARE(parser.getResults().size(), 0);
}

// Test parsing a single feed successfully
void TestBatchFeedFetcher::testSingleFeedSuccess()
{
    TestableBatchFeedFetcher parser;

    QUrl url("http://example.com/feed.xml");
    RawFeed* feed = createTestFeed("http://example.com/feed.xml", "Test Feed");
    parser.addMockResponse(url, FeedSource::OK, feed);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    // Wait for completion
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Check results
    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 1);
    QCOMPARE(results[url], FeedSource::OK);

    // Check feed retrieval
    RawFeed* retrievedFeed = parser.getFeed(url);
    QVERIFY(retrievedFeed != nullptr);
    QCOMPARE(retrievedFeed->url, url);
    QCOMPARE(retrievedFeed->title, QString("Test Feed"));
}

// Test parsing a single feed with network error
void TestBatchFeedFetcher::testSingleFeedNetworkError()
{
    TestableBatchFeedFetcher parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, FeedSource::NETWORK_ERROR);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results[url], FeedSource::NETWORK_ERROR);

    // Feed should be null on error
    QVERIFY(parser.getFeed(url) == nullptr);
}

// Test parsing a single feed with parse error
void TestBatchFeedFetcher::testSingleFeedParseError()
{
    TestableBatchFeedFetcher parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, FeedSource::EMPTY_DOCUMENT);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results[url], FeedSource::EMPTY_DOCUMENT);

    // Feed should be null on error
    QVERIFY(parser.getFeed(url) == nullptr);
}

// Test parsing multiple feeds, all succeed
void TestBatchFeedFetcher::testMultipleFeedsAllSuccess()
{
    TestableBatchFeedFetcher parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");
    QUrl url3("http://example.com/feed3.xml");

    parser.addMockResponse(url1, FeedSource::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));
    parser.addMockResponse(url2, FeedSource::OK, createTestFeed("http://example.com/feed2.xml", "Feed 2"));
    parser.addMockResponse(url3, FeedSource::OK, createTestFeed("http://example.com/feed3.xml", "Feed 3"));

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    QList<QUrl> urls;
    urls << url1 << url2 << url3;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 3);
    QCOMPARE(results[url1], FeedSource::OK);
    QCOMPARE(results[url2], FeedSource::OK);
    QCOMPARE(results[url3], FeedSource::OK);

    // Check all feeds retrieved
    QVERIFY(parser.getFeed(url1) != nullptr);
    QVERIFY(parser.getFeed(url2) != nullptr);
    QVERIFY(parser.getFeed(url3) != nullptr);
}

// Test parsing multiple feeds with mixed success/failure
void TestBatchFeedFetcher::testMultipleFeedsMixedResults()
{
    TestableBatchFeedFetcher parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");
    QUrl url3("http://example.com/feed3.xml");
    QUrl url4("http://example.com/feed4.xml");

    parser.addMockResponse(url1, FeedSource::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));
    parser.addMockResponse(url2, FeedSource::NETWORK_ERROR);
    parser.addMockResponse(url3, FeedSource::OK, createTestFeed("http://example.com/feed3.xml", "Feed 3"));
    parser.addMockResponse(url4, FeedSource::EMPTY_DOCUMENT);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    QList<QUrl> urls;
    urls << url1 << url2 << url3 << url4;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 4);
    QCOMPARE(results[url1], FeedSource::OK);
    QCOMPARE(results[url2], FeedSource::NETWORK_ERROR);
    QCOMPARE(results[url3], FeedSource::OK);
    QCOMPARE(results[url4], FeedSource::EMPTY_DOCUMENT);

    // Check feed retrieval - only successful ones should have feeds
    QVERIFY(parser.getFeed(url1) != nullptr);
    QVERIFY(parser.getFeed(url2) == nullptr);
    QVERIFY(parser.getFeed(url3) != nullptr);
    QVERIFY(parser.getFeed(url4) == nullptr);
}

// Test that duplicate URLs are skipped
void TestBatchFeedFetcher::testDuplicateURLsSkipped()
{
    TestableBatchFeedFetcher parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, FeedSource::OK, createTestFeed("http://example.com/feed.xml", "Test Feed"));

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);

    // Add same URL multiple times
    QList<QUrl> urls;
    urls << url << url << url;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Should only have one result
    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 1);
    QCOMPARE(results[url], FeedSource::OK);
}

// Test getFeed returns correct feed on success
void TestBatchFeedFetcher::testGetFeedSuccess()
{
    TestableBatchFeedFetcher parser;

    QUrl url("http://example.com/feed.xml");
    RawFeed* feed = createTestFeed("http://example.com/feed.xml", "My Test Feed");
    parser.addMockResponse(url, FeedSource::OK, feed);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);
    QVERIFY(spy.wait(5000));

    RawFeed* retrievedFeed = parser.getFeed(url);
    QVERIFY(retrievedFeed != nullptr);
    QCOMPARE(retrievedFeed->title, QString("My Test Feed"));
}

// Test getFeed returns nullptr on failure
void TestBatchFeedFetcher::testGetFeedFailure()
{
    TestableBatchFeedFetcher parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, FeedSource::FILE_ERROR);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);
    QVERIFY(spy.wait(5000));

    QVERIFY(parser.getFeed(url) == nullptr);
}

// Test getFeed returns nullptr for unknown URL
void TestBatchFeedFetcher::testGetFeedUnknownURL()
{
    TestableBatchFeedFetcher parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");

    parser.addMockResponse(url1, FeedSource::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));

    QList<QUrl> urls;
    urls << url1;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);
    QVERIFY(spy.wait(5000));

    // url2 was never parsed
    QVERIFY(parser.getFeed(url2) == nullptr);
}

// Test getResults accessor returns correct map
void TestBatchFeedFetcher::testGetResultsAccessor()
{
    TestableBatchFeedFetcher parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");

    parser.addMockResponse(url1, FeedSource::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));
    parser.addMockResponse(url2, FeedSource::NETWORK_ERROR);

    QList<QUrl> urls;
    urls << url1 << url2;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchFeedFetcher::ready);
    QVERIFY(spy.wait(5000));

    QMap<QUrl, FeedSource::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 2);
    QVERIFY(results.contains(url1));
    QVERIFY(results.contains(url2));
    QCOMPARE(results[url1], FeedSource::OK);
    QCOMPARE(results[url2], FeedSource::NETWORK_ERROR);
}

// Test that calling parse() again clears previous results
void TestBatchFeedFetcher::testParserReuse()
{
    TestableBatchFeedFetcher parser;

    // First parse
    QUrl url1("http://example.com/feed1.xml");
    parser.addMockResponse(url1, FeedSource::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));

    QList<QUrl> urls1;
    urls1 << url1;
    parser.parse(urls1);

    QSignalSpy spy1(&parser, &BatchFeedFetcher::ready);
    QVERIFY(spy1.wait(5000));

    // Verify first results
    QMap<QUrl, FeedSource::ParseResult> results1 = parser.getResults();
    QCOMPARE(results1.size(), 1);

    // Second parse with different URL
    QUrl url2("http://example.com/feed2.xml");
    parser.addMockResponse(url2, FeedSource::OK, createTestFeed("http://example.com/feed2.xml", "Feed 2"));

    QList<QUrl> urls2;
    urls2 << url2;
    parser.parse(urls2);

    QSignalSpy spy2(&parser, &BatchFeedFetcher::ready);
    QVERIFY(spy2.wait(5000));

    // Verify second results - should only contain url2, not url1
    QMap<QUrl, FeedSource::ParseResult> results2 = parser.getResults();
    QCOMPARE(results2.size(), 1);
    QVERIFY(results2.contains(url2));
    QVERIFY(!results2.contains(url1));

    // Old feed should not be accessible
    QVERIFY(parser.getFeed(url1) == nullptr);
    QVERIFY(parser.getFeed(url2) != nullptr);
}

QTEST_MAIN(TestBatchFeedFetcher)

#include "tst_testbatchnewsparser.moc"
