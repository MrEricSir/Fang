#include <QTest>
#include "../../src/models/NewsItem.h"
#include "../../src/models/FeedItem.h"

/**
 * NewsItem model tests
 */
class TestNewsItem : public QObject
{
    Q_OBJECT

public:
    TestNewsItem();

private slots:
    void initTestCase();
    void cleanup();

    // Constructor
    void testDefaultConstructor();
    void testParameterizedConstructor();

    // Getter
    void testGetters();

    // Pinning
    void testPinnedState();

    // Comparitors
    void testLessThanOperator();
    void testLessThan_SameTimestamp();
    void testLessThan_DifferentTimestamp();

    // Sorting
    void testSortingStability();

private:
    FeedItem* createTestFeed();
    NewsItem* createTestNews(qint64 id, const QDateTime& timestamp, FeedItem* feed = nullptr);
};

TestNewsItem::TestNewsItem()
{
}

void TestNewsItem::initTestCase()
{
}

void TestNewsItem::cleanup()
{
}

FeedItem* TestNewsItem::createTestFeed()
{
    return new FeedItem(
        1,                                          // id
        0,                                          // ordinal
        "Test Feed",                                // title
        "",                                         // subtitle
        QDateTime::currentDateTime(),               // lastUpdated
        60,                                         // minutesToUpdate
        QUrl("http://example.com/feed.xml"),        // url
        QUrl("http://example.com"),                 // siteURL
        "http://example.com/feed.xml",              // userURL
        QUrl(),                                     // imageURL
        QDateTime::currentDateTime(),               // lastIconUpdate
        -1,                                         // parentFolder
        true,                                       // folderOpen
        this
    );
}

NewsItem* TestNewsItem::createTestNews(qint64 id, const QDateTime& timestamp, FeedItem* feed)
{
    if (!feed) {
        feed = createTestFeed();
    }

    return new NewsItem(
        feed,
        id,
        feed->getDbID(),
        QString("Test News %1").arg(id),
        "Test Author",
        "Test Summary",
        "Test Content",
        timestamp,
        QUrl(QString("http://example.com/news/%1").arg(id)),
        false
    );
}

void TestNewsItem::testDefaultConstructor()
{
    NewsItem* news = new NewsItem(this);

    QCOMPARE(news->getDbID(), -1LL);
    QCOMPARE(news->getFeedId(), -1LL);
    QCOMPARE(news->getTitle(), QString(""));
    QCOMPARE(news->getAuthor(), QString(""));
    QCOMPARE(news->getSummary(), QString(""));
    QCOMPARE(news->getContent(), QString(""));
    QVERIFY(!news->getTimestamp().isValid());
    QCOMPARE(news->getURL(), QUrl());
    QCOMPARE(news->getPinned(), false);
    QVERIFY(news->getFeed() == nullptr);

    delete news;
}

void TestNewsItem::testParameterizedConstructor()
{
    FeedItem* feed = createTestFeed();
    QDateTime now = QDateTime::currentDateTime();

    NewsItem* news = new NewsItem(
        feed,
        42,
        1,
        "Test Article",
        "John Doe",
        "This is a summary",
        "<p>This is the content</p>",
        now,
        QUrl("http://example.com/article"),
        true
    );

    QCOMPARE(news->getDbID(), 42LL);
    QCOMPARE(news->getFeedId(), 1LL);
    QCOMPARE(news->getTitle(), QString("Test Article"));
    QCOMPARE(news->getAuthor(), QString("John Doe"));
    QCOMPARE(news->getSummary(), QString("This is a summary"));
    QCOMPARE(news->getContent(), QString("<p>This is the content</p>"));
    QCOMPARE(news->getTimestamp(), now);
    QCOMPARE(news->getURL(), QUrl("http://example.com/article"));
    QCOMPARE(news->getPinned(), true);
    QCOMPARE(news->getFeed(), feed);

    delete news;
    delete feed;
}

void TestNewsItem::testGetters()
{
    FeedItem* feed = createTestFeed();
    QDateTime timestamp = QDateTime::currentDateTime();

    NewsItem* news = new NewsItem(
        feed,
        100,
        1,
        "My Article",
        "Jane Smith",
        "Article summary here",
        "Full article content",
        timestamp,
        QUrl("http://test.com/story"),
        false
    );

    QCOMPARE(news->getDbID(), 100LL);
    QCOMPARE(news->getFeedId(), 1LL);
    QCOMPARE(news->getTitle(), QString("My Article"));
    QCOMPARE(news->getAuthor(), QString("Jane Smith"));
    QCOMPARE(news->getSummary(), QString("Article summary here"));
    QCOMPARE(news->getContent(), QString("Full article content"));
    QCOMPARE(news->getTimestamp(), timestamp);
    QCOMPARE(news->getURL(), QUrl("http://test.com/story"));
    QCOMPARE(news->getFeed(), feed);

    delete news;
    delete feed;
}

void TestNewsItem::testPinnedState()
{
    FeedItem* feed = createTestFeed();
    QDateTime now = QDateTime::currentDateTime();

    NewsItem* news = createTestNews(1, now, feed);

    // Initially not pinned
    QCOMPARE(news->getPinned(), false);

    // Pin
    news->setPinned(true);
    QCOMPARE(news->getPinned(), true);

    // Unpin
    news->setPinned(false);
    QCOMPARE(news->getPinned(), false);

    delete news;
    delete feed;
}

void TestNewsItem::testLessThanOperator()
{
    FeedItem* feed = createTestFeed();
    QDateTime earlier = QDateTime::currentDateTime().addSecs(-3600);
    QDateTime later = QDateTime::currentDateTime();

    NewsItem* news1 = createTestNews(1, earlier, feed);
    NewsItem* news2 = createTestNews(2, later, feed);

    // Should compare based on timestamps
    QVERIFY(*news1 < *news2);
    QVERIFY(!(*news2 < *news1));

    delete news1;
    delete news2;
    delete feed;
}

void TestNewsItem::testLessThan_SameTimestamp()
{
    FeedItem* feed = createTestFeed();
    QDateTime timestamp = QDateTime::currentDateTime();

    // Same timestamp, different IDs
    NewsItem* news1 = createTestNews(5, timestamp, feed);
    NewsItem* news2 = createTestNews(10, timestamp, feed);

    // When timestamps are equal, use ID for comparison
    QVERIFY(NewsItem::LessThan(news1, news2));  // 5 < 10
    QVERIFY(!NewsItem::LessThan(news2, news1)); // !(10 < 5)

    delete news1;
    delete news2;
    delete feed;
}

void TestNewsItem::testLessThan_DifferentTimestamp()
{
    FeedItem* feed = createTestFeed();
    QDateTime earlier = QDateTime::currentDateTime().addSecs(-7200);
    QDateTime later = QDateTime::currentDateTime();

    // Timestamp should take precedence over ID.
    NewsItem* news1 = createTestNews(100, earlier, feed);  // Earlier time, higher ID
    NewsItem* news2 = createTestNews(50, later, feed);     // Later time, lower ID
    QVERIFY(NewsItem::LessThan(news1, news2));  // earlier < later
    QVERIFY(!NewsItem::LessThan(news2, news1)); // !(later < earlier)

    delete news1;
    delete news2;
    delete feed;
}

void TestNewsItem::testSortingStability()
{
    FeedItem* feed = createTestFeed();
    QDateTime base = QDateTime::currentDateTime();

    // Create news items with timestamps.
    QList<NewsItem*> newsList;
    for (int i = 0; i < 5; i++) {
        QDateTime timestamp = base.addSecs(i);
        NewsItem* news = createTestNews(i + 1, timestamp, feed);
        newsList.append(news);
    }

    // Verify order.
    for (int i = 0; i < newsList.size() - 1; i++) {
        QVERIFY(NewsItem::LessThan(newsList[i], newsList[i + 1]));
    }

    // Create two items with same timestamp but different IDs.
    QDateTime sameTime = base.addSecs(10);
    NewsItem* news1 = createTestNews(100, sameTime, feed);
    NewsItem* news2 = createTestNews(200, sameTime, feed);

    // ID should break tie for consistency.
    QVERIFY(NewsItem::LessThan(news1, news2));
    QVERIFY(!NewsItem::LessThan(news2, news1));

    qDeleteAll(newsList);
    delete news1;
    delete news2;
    delete feed;
}

QTEST_MAIN(TestNewsItem)

#include "tst_newsitem.moc"
