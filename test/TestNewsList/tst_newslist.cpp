#include <QTest>
#include "../../src/models/NewsList.h"
#include "../../src/models/NewsItem.h"
#include "../../src/models/FeedItem.h"

/**
 * @brief Tests NewsList dual list+set data structure
 */
class TestNewsList : public QObject
{
    Q_OBJECT

public:
    TestNewsList();

private slots:
    void initTestCase();
    void cleanup();

    // Constructor tests
    void testConstructor();

    // Basic operation tests
    void testIsEmpty();
    void testSize();
    void testClear();

    // Append/prepend single item
    void testAppendSingleItem();
    void testPrependSingleItem();

    // Access tests
    void testFirst();
    void testLast();
    void testAt();

    // Contains tests
    void testContains();
    void testContainsAfterAppend();
    void testContainsAfterPrepend();

    // Index tests
    void testIndexOf();

    // Remove and delete tests
    void testRemoveAndDeleteFromStart();
    void testRemoveAndDeleteFromEnd();
    void testRemoveAndDeleteMultiple();

    // News item lookup tests
    void testNewsItemForID();
    void testNewsItemForID_Invalid();
    void testIndexForItemID();
    void testIndexForItemID_NotFound();

    // Iteration tests
    void testIteration();

    // Integration tests
    void testListSetSynchronization();

private:
    FeedItem* createTestFeed();
    NewsItem* createTestNews(qint64 id, const QDateTime& timestamp, FeedItem* feed = nullptr);
    QList<NewsItem*>* createNewsList(int count, FeedItem* feed = nullptr);
};

TestNewsList::TestNewsList()
{
}

void TestNewsList::initTestCase()
{
}

void TestNewsList::cleanup()
{
}

FeedItem* TestNewsList::createTestFeed()
{
    return new FeedItem(
        1, 0, "Test Feed", "", QDateTime::currentDateTime(), 60,
        QUrl("http://example.com/feed.xml"), QUrl("http://example.com"),
        "http://example.com/feed.xml", QUrl(), QDateTime::currentDateTime(),
        -1, true, this
    );
}

NewsItem* TestNewsList::createTestNews(qint64 id, const QDateTime& timestamp, FeedItem* feed)
{
    if (!feed) {
        feed = createTestFeed();
    }

    return new NewsItem(
        feed, id, feed->getDbID(),
        QString("News %1").arg(id), "Author", "Summary", "Content",
        timestamp, QUrl(QString("http://example.com/%1").arg(id)), false
    );
}

QList<NewsItem*>* TestNewsList::createNewsList(int count, FeedItem* feed)
{
    if (!feed) {
        feed = createTestFeed();
    }

    QList<NewsItem*>* list = new QList<NewsItem*>();
    QDateTime base = QDateTime::currentDateTime();

    for (int i = 0; i < count; i++) {
        NewsItem* news = createTestNews(i + 1, base.addSecs(i), feed);
        list->append(news);
    }

    return list;
}

void TestNewsList::testConstructor()
{
    NewsList* newsList = new NewsList(this);

    QVERIFY(newsList->isEmpty());
    QCOMPARE(newsList->size(), 0);

    delete newsList;
}

void TestNewsList::testIsEmpty()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QVERIFY(newsList->isEmpty());

    NewsItem* news = createTestNews(1, QDateTime::currentDateTime(), feed);
    newsList->append(news);

    QVERIFY(!newsList->isEmpty());

    delete newsList;
    delete feed;
}

void TestNewsList::testSize()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QCOMPARE(newsList->size(), 0);

    for (int i = 0; i < 5; i++) {
        NewsItem* news = createTestNews(i + 1, QDateTime::currentDateTime().addSecs(i), feed);
        newsList->append(news);
        QCOMPARE(newsList->size(), i + 1);
    }

    delete newsList;
    delete feed;
}

void TestNewsList::testClear()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    // Add items
    for (int i = 0; i < 3; i++) {
        NewsItem* news = createTestNews(i + 1, QDateTime::currentDateTime().addSecs(i), feed);
        newsList->append(news);
    }

    QCOMPARE(newsList->size(), 3);

    // Clear should delete all items
    newsList->clear();

    QCOMPARE(newsList->size(), 0);
    QVERIFY(newsList->isEmpty());

    // Process deleteLater calls
    QTest::qWait(10);

    delete newsList;
    delete feed;
}

void TestNewsList::testAppendSingleItem()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news = createTestNews(1, QDateTime::currentDateTime(), feed);
    newsList->append(news);

    QCOMPARE(newsList->size(), 1);
    QVERIFY(newsList->contains(news));
    QCOMPARE(newsList->first(), news);
    QCOMPARE(newsList->last(), news);

    delete newsList;
    delete feed;
}

void TestNewsList::testPrependSingleItem()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news = createTestNews(1, QDateTime::currentDateTime(), feed);
    newsList->prepend(news);

    QCOMPARE(newsList->size(), 1);
    QVERIFY(newsList->contains(news));
    QCOMPARE(newsList->first(), news);
    QCOMPARE(newsList->last(), news);

    delete newsList;
    delete feed;
}

void TestNewsList::testFirst()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news1 = createTestNews(1, QDateTime::currentDateTime(), feed);
    NewsItem* news2 = createTestNews(2, QDateTime::currentDateTime().addSecs(1), feed);

    newsList->append(news1);
    newsList->append(news2);

    QCOMPARE(newsList->first(), news1);

    delete newsList;
    delete feed;
}

void TestNewsList::testLast()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news1 = createTestNews(1, QDateTime::currentDateTime(), feed);
    NewsItem* news2 = createTestNews(2, QDateTime::currentDateTime().addSecs(1), feed);

    newsList->append(news1);
    newsList->append(news2);

    QCOMPARE(newsList->last(), news2);

    delete newsList;
    delete feed;
}

void TestNewsList::testAt()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(3, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    QCOMPARE(newsList->at(0), list->at(0));
    QCOMPARE(newsList->at(1), list->at(1));
    QCOMPARE(newsList->at(2), list->at(2));

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testContains()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news1 = createTestNews(1, QDateTime::currentDateTime(), feed);
    NewsItem* news2 = createTestNews(2, QDateTime::currentDateTime(), feed);

    QVERIFY(!newsList->contains(news1));

    newsList->append(news1);
    QVERIFY(newsList->contains(news1));
    QVERIFY(!newsList->contains(news2));

    delete news2;
    delete newsList;
    delete feed;
}

void TestNewsList::testContainsAfterAppend()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(3, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    // Verify all items are in the set
    for (NewsItem* news : *list) {
        QVERIFY(newsList->contains(news));
    }

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testContainsAfterPrepend()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(3, feed);

    // Prepend each item individually
    for (NewsItem* news : *list) {
        newsList->prepend(news);
    }

    // Verify all items are in the set
    for (NewsItem* news : *list) {
        QVERIFY(newsList->contains(news));
    }

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testIndexOf()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(3, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    QCOMPARE(newsList->indexOf(list->at(0)), 0);
    QCOMPARE(newsList->indexOf(list->at(1)), 1);
    QCOMPARE(newsList->indexOf(list->at(2)), 2);

    // Item not in list
    NewsItem* notInList = createTestNews(99, QDateTime::currentDateTime(), feed);
    QCOMPARE(newsList->indexOf(notInList), -1);

    delete notInList;
    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testRemoveAndDeleteFromStart()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(5, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    NewsItem* firstItem = newsList->first();
    NewsItem* secondItem = newsList->at(1);

    // Remove 2 from start
    newsList->removeAndDelete(true, 2);

    QCOMPARE(newsList->size(), 3);
    QVERIFY(!newsList->contains(firstItem));
    QVERIFY(!newsList->contains(secondItem));

    // Third item should now be first
    QCOMPARE(newsList->first(), list->at(2));

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testRemoveAndDeleteFromEnd()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(5, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    NewsItem* lastItem = newsList->last();
    NewsItem* secondToLast = newsList->at(3);

    // Remove 2 from end
    newsList->removeAndDelete(false, 2);

    QCOMPARE(newsList->size(), 3);
    QVERIFY(!newsList->contains(lastItem));
    QVERIFY(!newsList->contains(secondToLast));

    // Third item should now be last
    QCOMPARE(newsList->last(), list->at(2));

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testRemoveAndDeleteMultiple()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(10, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    // Remove 3 from start
    newsList->removeAndDelete(true, 3);
    QCOMPARE(newsList->size(), 7);

    // Remove 2 from end
    newsList->removeAndDelete(false, 2);
    QCOMPARE(newsList->size(), 5);

    // Should have items 4-8 remaining (indices 3-7 from original list)
    QCOMPARE(newsList->first(), list->at(3));
    QCOMPARE(newsList->last(), list->at(7));

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testNewsItemForID()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news1 = createTestNews(100, QDateTime::currentDateTime(), feed);
    NewsItem* news2 = createTestNews(200, QDateTime::currentDateTime(), feed);
    NewsItem* news3 = createTestNews(300, QDateTime::currentDateTime(), feed);

    newsList->append(news1);
    newsList->append(news2);
    newsList->append(news3);

    QCOMPARE(newsList->newsItemForID(100), news1);
    QCOMPARE(newsList->newsItemForID(200), news2);
    QCOMPARE(newsList->newsItemForID(300), news3);

    delete newsList;
    delete feed;
}

void TestNewsList::testNewsItemForID_Invalid()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news = createTestNews(100, QDateTime::currentDateTime(), feed);
    newsList->append(news);

    // Non-existent ID
    QVERIFY(newsList->newsItemForID(999) == nullptr);

    delete newsList;
    delete feed;
}

void TestNewsList::testIndexForItemID()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news1 = createTestNews(100, QDateTime::currentDateTime(), feed);
    NewsItem* news2 = createTestNews(200, QDateTime::currentDateTime(), feed);
    NewsItem* news3 = createTestNews(300, QDateTime::currentDateTime(), feed);

    newsList->append(news1);
    newsList->append(news2);
    newsList->append(news3);

    QCOMPARE(newsList->indexForItemID(100), 0);
    QCOMPARE(newsList->indexForItemID(200), 1);
    QCOMPARE(newsList->indexForItemID(300), 2);

    delete newsList;
    delete feed;
}

void TestNewsList::testIndexForItemID_NotFound()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    NewsItem* news = createTestNews(100, QDateTime::currentDateTime(), feed);
    newsList->append(news);

    QCOMPARE(newsList->indexForItemID(999), -1);

    delete newsList;
    delete feed;
}

void TestNewsList::testIteration()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(5, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    int count = 0;
    for (NewsItem* news : *newsList) {
        QCOMPARE(news, list->at(count));
        count++;
    }

    QCOMPARE(count, 5);

    delete list;
    delete newsList;
    delete feed;
}

void TestNewsList::testListSetSynchronization()
{
    NewsList* newsList = new NewsList(this);
    FeedItem* feed = createTestFeed();

    QList<NewsItem*>* list = createNewsList(5, feed);

    // Append each item individually
    for (NewsItem* news : *list) {
        newsList->append(news);
    }

    // Verify list size matches
    QCOMPARE(newsList->size(), list->size());

    // Verify all items are in set (O(1) contains check)
    for (NewsItem* news : *list) {
        QVERIFY(newsList->contains(news));
    }

    // Remove some items
    newsList->removeAndDelete(true, 2);

    // Verify removed items are not in set
    QVERIFY(!newsList->contains(list->at(0)));
    QVERIFY(!newsList->contains(list->at(1)));

    // Verify remaining items are still in set
    QVERIFY(newsList->contains(list->at(2)));
    QVERIFY(newsList->contains(list->at(3)));
    QVERIFY(newsList->contains(list->at(4)));

    delete list;
    delete newsList;
    delete feed;
}

QTEST_MAIN(TestNewsList)

#include "tst_newslist.moc"
