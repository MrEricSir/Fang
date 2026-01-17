#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QQueue>

#include "../../src/utilities/BatchFeedDiscovery.h"
#include "../../src/models/ListModel.h"
#include "../../src/models/FeedItem.h"
#include "../MockNewsParser.h"
#include "../MockWebPageGrabber.h"
#include "../MockBatchNewsParser.h"

/**
 * @brief Mock FeedDiscovery that uses pre-configured results based on call order
 */
class MockFeedDiscovery : public FeedDiscovery
{
    Q_OBJECT

public:
    explicit MockFeedDiscovery(QQueue<bool>* results, QObject* parent = nullptr)
        : FeedDiscovery(parent,
                       new MockNewsParser(),
                       new MockNewsParser(),
                       new MockWebPageGrabber(),
                       new MockBatchNewsParser()),
          results(results),
          parser(qobject_cast<MockNewsParser*>(parserFirstTry))
    {
        // FeedDiscovery constructor now handles ownership automatically
    }

    void checkFeed(QString sURL) override
    {
        // Reconfigure the mock parser for each checkFeed() call
        if (results && !results->isEmpty()) {
            bool shouldSucceed = results->dequeue();
            if (shouldSucceed) {
                // Configure for success
                RawFeed* feed = new RawFeed();  // No parent - MockNewsParser owns it
                feed->url = QUrl("http://example.com/feed.xml");
                parser->setResult(ParserInterface::OK);
                parser->setFeed(feed);
                parser->setURL(QUrl("http://example.com/feed.xml"));
            } else {
                // Configure for failure
                parser->setResult(ParserInterface::NETWORK_ERROR);
            }
        }

        // Call parent implementation
        FeedDiscovery::checkFeed(sURL);
    }

private:
    QQueue<bool>* results;
    MockNewsParser* parser;
};

/**
 * @brief Mock BatchFeedDiscovery that creates mock FeedDiscovery instances
 */
class MockBatchFeedDiscovery : public BatchFeedDiscovery
{
    Q_OBJECT

public:
    explicit MockBatchFeedDiscovery(QObject* parent = nullptr)
        : BatchFeedDiscovery(parent)
    {
    }

    // Queue of pre-configured parser results (true = success, false = error)
    QQueue<bool> mockResults;

protected:
    FeedDiscovery* createFeedDiscovery() override
    {
        // Create MockFeedDiscovery that shares our results queue
        return new MockFeedDiscovery(&mockResults, this);
    }
};

class TestBatchFeedDiscovery : public QObject
{
    Q_OBJECT

public:
    TestBatchFeedDiscovery();

private slots:
    void testEmptyFeedList();
    void testSingleFeedSuccess();
    void testSingleFeedError();
    void testMaxConcurrentLimit();
    void testQueueProcessing();
    void testMixedResults();
    void testDoneSignalTiming();
    void testGetFeedListAccessor();

private:
    FeedItem* createTestFeedItem(const QString& url);
};

TestBatchFeedDiscovery::TestBatchFeedDiscovery()
{
}

FeedItem* TestBatchFeedDiscovery::createTestFeedItem(const QString& url)
{
    FeedItem* item = new FeedItem();
    item->setURL(QUrl(url));
    return item;
}

// Test that an empty feed list doesn't crash and doesn't emit done()
void TestBatchFeedDiscovery::testEmptyFeedList()
{
    MockBatchFeedDiscovery bfd;
    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    bfd.checkFeedList(&feedList, 3);

    // Empty list should not emit done() signal (current behavior)
    // Wait a bit to make sure no signal is emitted
    QTest::qWait(100);
    QCOMPARE(spy.count(), 0);
}

// Test single feed with success
void TestBatchFeedDiscovery::testSingleFeedSuccess()
{
    MockBatchFeedDiscovery bfd;
    bfd.mockResults.enqueue(true); // Success

    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    FeedItem* item = createTestFeedItem("http://example.com");
    feedList.appendRow(item);

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    bfd.checkFeedList(&feedList, 3);

    // Wait for async completion
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Verify feed item flags
    QVERIFY(!item->getIsUpdating());
    QVERIFY(!item->getErrorFlag());
    QVERIFY(item->getIsSelected());
}

// Test single feed with error
void TestBatchFeedDiscovery::testSingleFeedError()
{
    MockBatchFeedDiscovery bfd;
    bfd.mockResults.enqueue(false); // Error

    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    FeedItem* item = createTestFeedItem("http://example.com");
    feedList.appendRow(item);

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    bfd.checkFeedList(&feedList, 3);

    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Verify error flag is set
    QVERIFY(!item->getIsUpdating());
    QVERIFY(item->getErrorFlag());
    QVERIFY(!item->getIsSelected());
}

// Test that maxConcurrent limit is respected
void TestBatchFeedDiscovery::testMaxConcurrentLimit()
{
    MockBatchFeedDiscovery bfd;

    // Set up 5 feeds, all should succeed
    for (int i = 0; i < 5; i++) {
        bfd.mockResults.enqueue(true);
    }

    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    for (int i = 0; i < 5; i++) {
        FeedItem* item = createTestFeedItem(QString("http://example.com/feed%1").arg(i));
        feedList.appendRow(item);
    }

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    // Set maxConcurrent to 2
    bfd.checkFeedList(&feedList, 2);

    // Verify that initially only 2 are being updated
    int updatingCount = 0;
    for (int i = 0; i < feedList.count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList.row(i));
        if (item->getIsUpdating()) {
            updatingCount++;
        }
    }
    QCOMPARE(updatingCount, 2);

    // Wait for all to complete
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    // Verify all completed successfully
    for (int i = 0; i < feedList.count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList.row(i));
        QVERIFY(!item->getIsUpdating());
        QVERIFY(!item->getErrorFlag());
        QVERIFY(item->getIsSelected());
    }
}

// Test queue processing - items are processed sequentially after initial batch
void TestBatchFeedDiscovery::testQueueProcessing()
{
    MockBatchFeedDiscovery bfd;

    // 4 feeds, maxConcurrent = 2
    for (int i = 0; i < 4; i++) {
        bfd.mockResults.enqueue(true);
    }

    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    for (int i = 0; i < 4; i++) {
        FeedItem* item = createTestFeedItem(QString("http://example.com/feed%1").arg(i));
        feedList.appendRow(item);
    }

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    bfd.checkFeedList(&feedList, 2);

    QVERIFY(spy.wait(5000));

    // All should be completed
    for (int i = 0; i < feedList.count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList.row(i));
        QVERIFY(!item->getIsUpdating());
        QVERIFY(item->getIsSelected());
    }
}

// Test mixed success and failure results
void TestBatchFeedDiscovery::testMixedResults()
{
    MockBatchFeedDiscovery bfd;

    // 5 feeds: success, error, success, error, success
    bfd.mockResults.enqueue(true);
    bfd.mockResults.enqueue(false);
    bfd.mockResults.enqueue(true);
    bfd.mockResults.enqueue(false);
    bfd.mockResults.enqueue(true);

    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    for (int i = 0; i < 5; i++) {
        FeedItem* item = createTestFeedItem(QString("http://example.com/feed%1").arg(i));
        feedList.appendRow(item);
    }

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    // Use maxConcurrent=1 for deterministic sequential processing
    bfd.checkFeedList(&feedList, 1);

    QVERIFY(spy.wait(5000));

    // Verify results match expected pattern
    FeedItem* item0 = qobject_cast<FeedItem*>(feedList.row(0));
    QVERIFY(!item0->getErrorFlag());
    QVERIFY(item0->getIsSelected());

    FeedItem* item1 = qobject_cast<FeedItem*>(feedList.row(1));
    QVERIFY(item1->getErrorFlag());
    QVERIFY(!item1->getIsSelected());

    FeedItem* item2 = qobject_cast<FeedItem*>(feedList.row(2));
    QVERIFY(!item2->getErrorFlag());
    QVERIFY(item2->getIsSelected());

    FeedItem* item3 = qobject_cast<FeedItem*>(feedList.row(3));
    QVERIFY(item3->getErrorFlag());
    QVERIFY(!item3->getIsSelected());

    FeedItem* item4 = qobject_cast<FeedItem*>(feedList.row(4));
    QVERIFY(!item4->getErrorFlag());
    QVERIFY(item4->getIsSelected());
}

// Test that done() signal is emitted only when queue is empty and all discoveries complete
void TestBatchFeedDiscovery::testDoneSignalTiming()
{
    MockBatchFeedDiscovery bfd;

    for (int i = 0; i < 3; i++) {
        bfd.mockResults.enqueue(true);
    }

    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    for (int i = 0; i < 3; i++) {
        FeedItem* item = createTestFeedItem(QString("http://example.com/feed%1").arg(i));
        feedList.appendRow(item);
    }

    QSignalSpy spy(&bfd, &BatchFeedDiscovery::done);

    bfd.checkFeedList(&feedList, 3);

    // Wait for completion
    QVERIFY(spy.wait(5000));

    // Should have emitted done() exactly once
    QCOMPARE(spy.count(), 1);
}

// Test that getFeedList returns the correct list
void TestBatchFeedDiscovery::testGetFeedListAccessor()
{
    MockBatchFeedDiscovery bfd;
    FeedItem* prototype = new FeedItem();
    ListModel feedList(prototype);

    bfd.checkFeedList(&feedList, 3);

    // Verify getFeedList returns the same list
    QCOMPARE(bfd.getFeedList(), &feedList);
}

QTEST_MAIN(TestBatchFeedDiscovery)

#include "tst_testbatchfeeddiscovery.moc"
