#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QMap>
#include <QQueue>

#include "../../src/parser/BatchNewsParser.h"
#include "../../src/parser/ParserInterface.h"
#include "../../src/parser/RawFeed.h"
#include "../MockNewsParser.h"

/**
 * @brief Testable version of BatchNewsParser that uses mock parsers
 */
class TestableBatchNewsParser : public BatchNewsParser
{
    Q_OBJECT

public:
    explicit TestableBatchNewsParser(QObject* parent = nullptr)
        : BatchNewsParser(parent)
    {
    }

    // Configure mock responses for specific URLs
    void addMockResponse(const QUrl& url, ParserInterface::ParseResult result, RawFeed* feed = nullptr)
    {
        MockResponseConfig config;
        config.result = result;
        config.feed = feed;
        mockConfigs[url] = config;
    }

protected:
    // Override factory method to create mock parsers instead of real ones
    ParserInterface* createParser() override
    {
        MockNewsParser* parser = new MockNewsParser(this);

        // Store the parser so we can configure it when parse() is called with a URL
        pendingParsers.enqueue(parser);

        return parser;
    }

public:
    // Override parse to configure parsers with their URLs
    void parse(const QList<QUrl> &urls) override
    {
        // Clear pending parsers from any previous calls
        pendingParsers.clear();

        // Call base class parse which will call createParser() for each URL
        BatchNewsParser::parse(urls);

        // Now configure each parser that was created
        // The parsers are connected and have already started parsing, but MockNewsParser
        // will emit done() asynchronously, so we can still configure them
        int urlIndex = 0;
        for (const QUrl& url : urls) {
            // Skip duplicates (BatchNewsParser skips them too)
            if (urlIndex > 0 && urls.mid(0, urlIndex).contains(url)) {
                continue;
            }

            if (!pendingParsers.isEmpty()) {
                MockNewsParser* parser = pendingParsers.dequeue();

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
                    parser->setResult(ParserInterface::NETWORK_ERROR);
                    parser->setURL(url);
                }
            }

            urlIndex++;
        }
    }

private:
    struct MockResponseConfig {
        ParserInterface::ParseResult result;
        RawFeed* feed = nullptr;
    };

    QMap<QUrl, MockResponseConfig> mockConfigs;
    QQueue<MockNewsParser*> pendingParsers;
};

class TestBatchNewsParser : public QObject
{
    Q_OBJECT

public:
    TestBatchNewsParser();

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

TestBatchNewsParser::TestBatchNewsParser()
{
}

RawFeed* TestBatchNewsParser::createTestFeed(const QString& url, const QString& title)
{
    RawFeed* feed = new RawFeed();
    feed->url = QUrl(url);
    feed->title = title;
    return feed;
}

// Test that an empty URL list doesn't crash and doesn't emit ready()
void TestBatchNewsParser::testEmptyURLList()
{
    TestableBatchNewsParser parser;
    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    QList<QUrl> urls;
    parser.parse(urls);

    // Empty list should not emit ready() signal
    QTest::qWait(100);
    QCOMPARE(spy.count(), 0);

    // Results should be empty
    QCOMPARE(parser.getResults().size(), 0);
}

// Test parsing a single feed successfully
void TestBatchNewsParser::testSingleFeedSuccess()
{
    TestableBatchNewsParser parser;

    QUrl url("http://example.com/feed.xml");
    RawFeed* feed = createTestFeed("http://example.com/feed.xml", "Test Feed");
    parser.addMockResponse(url, ParserInterface::OK, feed);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    // Wait for completion
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Check results
    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 1);
    QCOMPARE(results[url], ParserInterface::OK);

    // Check feed retrieval
    RawFeed* retrievedFeed = parser.getFeed(url);
    QVERIFY(retrievedFeed != nullptr);
    QCOMPARE(retrievedFeed->url, url);
    QCOMPARE(retrievedFeed->title, QString("Test Feed"));
}

// Test parsing a single feed with network error
void TestBatchNewsParser::testSingleFeedNetworkError()
{
    TestableBatchNewsParser parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, ParserInterface::NETWORK_ERROR);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results[url], ParserInterface::NETWORK_ERROR);

    // Feed should be null on error
    QVERIFY(parser.getFeed(url) == nullptr);
}

// Test parsing a single feed with parse error
void TestBatchNewsParser::testSingleFeedParseError()
{
    TestableBatchNewsParser parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, ParserInterface::EMPTY_DOCUMENT);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results[url], ParserInterface::EMPTY_DOCUMENT);

    // Feed should be null on error
    QVERIFY(parser.getFeed(url) == nullptr);
}

// Test parsing multiple feeds, all succeed
void TestBatchNewsParser::testMultipleFeedsAllSuccess()
{
    TestableBatchNewsParser parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");
    QUrl url3("http://example.com/feed3.xml");

    parser.addMockResponse(url1, ParserInterface::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));
    parser.addMockResponse(url2, ParserInterface::OK, createTestFeed("http://example.com/feed2.xml", "Feed 2"));
    parser.addMockResponse(url3, ParserInterface::OK, createTestFeed("http://example.com/feed3.xml", "Feed 3"));

    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    QList<QUrl> urls;
    urls << url1 << url2 << url3;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 3);
    QCOMPARE(results[url1], ParserInterface::OK);
    QCOMPARE(results[url2], ParserInterface::OK);
    QCOMPARE(results[url3], ParserInterface::OK);

    // Check all feeds retrieved
    QVERIFY(parser.getFeed(url1) != nullptr);
    QVERIFY(parser.getFeed(url2) != nullptr);
    QVERIFY(parser.getFeed(url3) != nullptr);
}

// Test parsing multiple feeds with mixed success/failure
void TestBatchNewsParser::testMultipleFeedsMixedResults()
{
    TestableBatchNewsParser parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");
    QUrl url3("http://example.com/feed3.xml");
    QUrl url4("http://example.com/feed4.xml");

    parser.addMockResponse(url1, ParserInterface::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));
    parser.addMockResponse(url2, ParserInterface::NETWORK_ERROR);
    parser.addMockResponse(url3, ParserInterface::OK, createTestFeed("http://example.com/feed3.xml", "Feed 3"));
    parser.addMockResponse(url4, ParserInterface::EMPTY_DOCUMENT);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    QList<QUrl> urls;
    urls << url1 << url2 << url3 << url4;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Check results
    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 4);
    QCOMPARE(results[url1], ParserInterface::OK);
    QCOMPARE(results[url2], ParserInterface::NETWORK_ERROR);
    QCOMPARE(results[url3], ParserInterface::OK);
    QCOMPARE(results[url4], ParserInterface::EMPTY_DOCUMENT);

    // Check feed retrieval - only successful ones should have feeds
    QVERIFY(parser.getFeed(url1) != nullptr);
    QVERIFY(parser.getFeed(url2) == nullptr);
    QVERIFY(parser.getFeed(url3) != nullptr);
    QVERIFY(parser.getFeed(url4) == nullptr);
}

// Test that duplicate URLs are skipped
void TestBatchNewsParser::testDuplicateURLsSkipped()
{
    TestableBatchNewsParser parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, ParserInterface::OK, createTestFeed("http://example.com/feed.xml", "Test Feed"));

    QSignalSpy spy(&parser, &BatchNewsParser::ready);

    // Add same URL multiple times
    QList<QUrl> urls;
    urls << url << url << url;
    parser.parse(urls);

    QVERIFY(spy.wait(5000));

    // Should only have one result
    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 1);
    QCOMPARE(results[url], ParserInterface::OK);
}

// Test getFeed returns correct feed on success
void TestBatchNewsParser::testGetFeedSuccess()
{
    TestableBatchNewsParser parser;

    QUrl url("http://example.com/feed.xml");
    RawFeed* feed = createTestFeed("http://example.com/feed.xml", "My Test Feed");
    parser.addMockResponse(url, ParserInterface::OK, feed);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);
    QVERIFY(spy.wait(5000));

    RawFeed* retrievedFeed = parser.getFeed(url);
    QVERIFY(retrievedFeed != nullptr);
    QCOMPARE(retrievedFeed->title, QString("My Test Feed"));
}

// Test getFeed returns nullptr on failure
void TestBatchNewsParser::testGetFeedFailure()
{
    TestableBatchNewsParser parser;

    QUrl url("http://example.com/feed.xml");
    parser.addMockResponse(url, ParserInterface::FILE_ERROR);

    QList<QUrl> urls;
    urls << url;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);
    QVERIFY(spy.wait(5000));

    QVERIFY(parser.getFeed(url) == nullptr);
}

// Test getFeed returns nullptr for unknown URL
void TestBatchNewsParser::testGetFeedUnknownURL()
{
    TestableBatchNewsParser parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");

    parser.addMockResponse(url1, ParserInterface::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));

    QList<QUrl> urls;
    urls << url1;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);
    QVERIFY(spy.wait(5000));

    // url2 was never parsed
    QVERIFY(parser.getFeed(url2) == nullptr);
}

// Test getResults accessor returns correct map
void TestBatchNewsParser::testGetResultsAccessor()
{
    TestableBatchNewsParser parser;

    QUrl url1("http://example.com/feed1.xml");
    QUrl url2("http://example.com/feed2.xml");

    parser.addMockResponse(url1, ParserInterface::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));
    parser.addMockResponse(url2, ParserInterface::NETWORK_ERROR);

    QList<QUrl> urls;
    urls << url1 << url2;
    parser.parse(urls);

    QSignalSpy spy(&parser, &BatchNewsParser::ready);
    QVERIFY(spy.wait(5000));

    QMap<QUrl, ParserInterface::ParseResult> results = parser.getResults();
    QCOMPARE(results.size(), 2);
    QVERIFY(results.contains(url1));
    QVERIFY(results.contains(url2));
    QCOMPARE(results[url1], ParserInterface::OK);
    QCOMPARE(results[url2], ParserInterface::NETWORK_ERROR);
}

// Test that calling parse() again clears previous results
void TestBatchNewsParser::testParserReuse()
{
    TestableBatchNewsParser parser;

    // First parse
    QUrl url1("http://example.com/feed1.xml");
    parser.addMockResponse(url1, ParserInterface::OK, createTestFeed("http://example.com/feed1.xml", "Feed 1"));

    QList<QUrl> urls1;
    urls1 << url1;
    parser.parse(urls1);

    QSignalSpy spy1(&parser, &BatchNewsParser::ready);
    QVERIFY(spy1.wait(5000));

    // Verify first results
    QMap<QUrl, ParserInterface::ParseResult> results1 = parser.getResults();
    QCOMPARE(results1.size(), 1);

    // Second parse with different URL
    QUrl url2("http://example.com/feed2.xml");
    parser.addMockResponse(url2, ParserInterface::OK, createTestFeed("http://example.com/feed2.xml", "Feed 2"));

    QList<QUrl> urls2;
    urls2 << url2;
    parser.parse(urls2);

    QSignalSpy spy2(&parser, &BatchNewsParser::ready);
    QVERIFY(spy2.wait(5000));

    // Verify second results - should only contain url2, not url1
    QMap<QUrl, ParserInterface::ParseResult> results2 = parser.getResults();
    QCOMPARE(results2.size(), 1);
    QVERIFY(results2.contains(url2));
    QVERIFY(!results2.contains(url1));

    // Old feed should not be accessible
    QVERIFY(parser.getFeed(url1) == nullptr);
    QVERIFY(parser.getFeed(url2) != nullptr);
}

QTEST_MAIN(TestBatchNewsParser)

#include "tst_testbatchnewsparser.moc"
