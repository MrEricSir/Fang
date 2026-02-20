#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QRandomGenerator>

#include "src/db/DB.h"
#include "src/models/SearchFeedItem.h"
#include "src/models/ListModel.h"
#include "src/models/NewsList.h"
#include "src/models/NewsItem.h"
#include "src/operations/OperationManager.h"
#include "src/operations/SearchNewsOperation.h"

/**
 * Integration test for SearchNewsOperation running through OperationManager::run().
 *
 * This test exercises the exact production code path:
 *   1. Create SearchNewsOperation
 *   2. OperationManager::run(operation) -> operation->execute() via virtual dispatch
 *   3. Verify results in listAppend and feedItem->getNewsList()
 */
class TestSearchOperation : public QObject
{
    Q_OBJECT

public:
    TestSearchOperation();

private slots:
    void initTestCase();
    void cleanup();
    void cleanupTestCase();

    // Core integration tests
    void testSearchFindsResults();
    void testSearchReturnsHighlightedTitle();
    void testSearchThroughOperationManager();
    void testSearchEmptyQuery();
    void testSearchNoResults();
    void testSearchMultipleResults();
    void testSearchScopedToFeed();
    void testVirtualDispatchFromLoadNewsPointer();

private:
    void createSchema();
    void insertTestNews(qint64 feedId, const QString& title, const QString& summary,
                        const QString& content, const QString& author,
                        qint64 timestamp = 0);

    QSqlDatabase db;
    QString connectionName;
    OperationManager* operationManager;
    ListModel* feedList;
    SearchFeedItem* searchFeed;
};

TestSearchOperation::TestSearchOperation()
    : connectionName("testSearchOpDb")
    , operationManager(nullptr)
    , feedList(nullptr)
    , searchFeed(nullptr)
{
}

void TestSearchOperation::initTestCase()
{
    // Create in-memory DB with unique connection name.
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");

    QVERIFY2(db.open(), qPrintable(db.lastError().text()));

    // Create schema before initializing DB singleton.
    createSchema();

    // Initialize the DB singleton for testing.
    DB::instance()->initForTesting(db);

    // Create operation manager.
    operationManager = new OperationManager(this);

    // Create feed list and search feed.
    FeedItem* prototype = new FeedItem();
    feedList = new ListModel(prototype, this);
    searchFeed = new SearchFeedItem(feedList);
}

void TestSearchOperation::createSchema()
{
    QSqlQuery query(db);

    // Create FeedItemTable (minimal for search testing).
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS FeedItemTable ("
        "  id INTEGER PRIMARY KEY,"
        "  title TEXT NOT NULL,"
        "  subtitle TEXT NOT NULL DEFAULT '',"
        "  lastUpdated INTEGER DEFAULT 0,"
        "  minutesToUpdate INTEGER DEFAULT 0,"
        "  url TEXT NOT NULL DEFAULT '',"
        "  siteURL TEXT NOT NULL DEFAULT '',"
        "  imageURL TEXT DEFAULT '',"
        "  lastIconUpdate INTEGER DEFAULT 0,"
        "  ordinal INTEGER DEFAULT 0,"
        "  bookmark_id INTEGER DEFAULT -1,"
        "  is_folder BOOLEAN DEFAULT FALSE,"
        "  folder_open BOOLEAN DEFAULT TRUE,"
        "  parent_folder INTEGER DEFAULT -1"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Create NewsItemTable.
    success = query.exec(
        "CREATE TABLE IF NOT EXISTS NewsItemTable ("
        "  id INTEGER PRIMARY KEY,"
        "  feed_id INTEGER REFERENCES FeedItemTable(id) ON DELETE CASCADE,"
        "  guid TEXT NOT NULL,"
        "  title TEXT NOT NULL,"
        "  author TEXT NOT NULL DEFAULT '',"
        "  summary TEXT NOT NULL DEFAULT '',"
        "  content TEXT NOT NULL DEFAULT '',"
        "  timestamp INTEGER DEFAULT 0,"
        "  url TEXT NOT NULL DEFAULT '',"
        "  pinned INTEGER DEFAULT 0"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Create FTS5 virtual table.
    success = query.exec(
        "CREATE VIRTUAL TABLE NewsItemFTS USING fts5("
        "  title,"
        "  summary,"
        "  content,"
        "  author,"
        "  content='NewsItemTable',"
        "  content_rowid='id'"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Create triggers for FTS sync.
    success = query.exec(
        "CREATE TRIGGER NewsItemFTS_ai AFTER INSERT ON NewsItemTable BEGIN "
        "  INSERT INTO NewsItemFTS(rowid, title, summary, content, author) "
        "  VALUES (new.id, new.title, new.summary, new.content, new.author); "
        "END"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    success = query.exec(
        "CREATE TRIGGER NewsItemFTS_ad AFTER DELETE ON NewsItemTable BEGIN "
        "  INSERT INTO NewsItemFTS(NewsItemFTS, rowid, title, summary, content, author) "
        "  VALUES ('delete', old.id, old.title, old.summary, old.content, old.author); "
        "END"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    success = query.exec(
        "CREATE TRIGGER NewsItemFTS_au AFTER UPDATE ON NewsItemTable BEGIN "
        "  INSERT INTO NewsItemFTS(NewsItemFTS, rowid, title, summary, content, author) "
        "  VALUES ('delete', old.id, old.title, old.summary, old.content, old.author); "
        "  INSERT INTO NewsItemFTS(rowid, title, summary, content, author) "
        "  VALUES (new.id, new.title, new.summary, new.content, new.author); "
        "END"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Insert test feeds.
    query.exec("INSERT INTO FeedItemTable (id, title) VALUES (1, 'Feed One')");
    query.exec("INSERT INTO FeedItemTable (id, title) VALUES (2, 'Feed Two')");
}

void TestSearchOperation::cleanup()
{
    // Clear news items between tests.
    QSqlQuery query(db);
    query.exec("DELETE FROM NewsItemTable");

    // Clear the search feed's news list.
    searchFeed->clearNews();
}

void TestSearchOperation::cleanupTestCase()
{
    delete feedList;
    feedList = nullptr;
    searchFeed = nullptr;  // Owned by feedList

    delete operationManager;
    operationManager = nullptr;

    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}

void TestSearchOperation::insertTestNews(qint64 feedId, const QString& title,
                                          const QString& summary, const QString& content,
                                          const QString& author, qint64 timestamp)
{
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO NewsItemTable (feed_id, guid, title, author, summary, content, timestamp, url) "
        "VALUES (:feed_id, :guid, :title, :author, :summary, :content, :timestamp, :url)"
    );
    query.bindValue(":feed_id", feedId);
    query.bindValue(":guid", QString("guid-%1").arg(QRandomGenerator::global()->generate()));
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":summary", summary);
    query.bindValue(":content", content);
    query.bindValue(":timestamp", timestamp > 0 ? timestamp : QDateTime::currentMSecsSinceEpoch());
    query.bindValue(":url", "http://example.com/news");

    bool success = query.exec();
    QVERIFY2(success, qPrintable(query.lastError().text()));
}

// -------------------------------------------------------------------
// Core integration tests
// -------------------------------------------------------------------

void TestSearchOperation::testSearchFindsResults()
{
    // Insert test data.
    insertTestNews(1, "Climate Change Report", "Summary of climate findings",
                   "The climate is changing rapidly.", "Dr. Smith");
    insertTestNews(1, "Sports Update", "Latest sports news",
                   "The team won the championship.", "John Doe");

    // Set up search feed.
    searchFeed->setSearchQuery("climate");
    searchFeed->clearNews();

    // Create and execute search operation directly.
    SearchNewsOperation op(operationManager, searchFeed, LoadNewsOperation::Initial,
                           "climate", SearchNewsOperation::Scope::Global);
    op.execute();

    // Verify results.
    QVERIFY2(!op.getAppendList().isEmpty(),
             "SearchNewsOperation::execute() should find results for 'climate'");
    QCOMPARE(op.getAppendList().size(), 1);
}

void TestSearchOperation::testSearchReturnsHighlightedTitle()
{
    insertTestNews(1, "Climate Change Report", "Summary of climate findings",
                   "The climate is changing rapidly.", "Dr. Smith");

    searchFeed->setSearchQuery("climate");
    searchFeed->clearNews();

    SearchNewsOperation op(operationManager, searchFeed, LoadNewsOperation::Initial,
                           "climate", SearchNewsOperation::Scope::Global);
    op.execute();

    QVERIFY(!op.getAppendList().isEmpty());

    // The title should have <mark> highlighting from FTS5 highlight().
    NewsItem* item = op.getAppendList().first();
    QVERIFY2(item->getTitle().contains("<mark>"),
             qPrintable("Title should contain <mark> highlight: " + item->getTitle()));
}

void TestSearchOperation::testSearchThroughOperationManager()
{
    // This is the KEY test: exercises the exact production code path.
    // FangApp::loadNews() creates a SearchNewsOperation, then calls
    // operationManager->run(loader), where loader is a LoadNewsOperation*.
    // This tests that virtual dispatch works correctly through the new hierarchy.

    insertTestNews(1, "Climate Change Report", "Summary of climate findings",
                   "The climate is changing rapidly.", "Dr. Smith");
    insertTestNews(1, "Sports Update", "Latest sports news",
                   "The team won the championship.", "John Doe");

    searchFeed->setSearchQuery("climate");
    searchFeed->clearNews();

    // Create as LoadNewsOperation* (same as FangApp::loadNews does).
    LoadNewsOperation* loader = new SearchNewsOperation(
        operationManager, searchFeed, LoadNewsOperation::Initial,
        "climate", SearchNewsOperation::Scope::Global);

    // Run through OperationManager (same as production code).
    operationManager->run(loader);

    // Verify results are in the loader's append list.
    QVERIFY2(!loader->getAppendList().isEmpty(),
             "OperationManager::run() should execute SearchNewsOperation via virtual dispatch");
    QCOMPARE(loader->getAppendList().size(), 1);

    // Verify results are also in the feed's news list.
    QVERIFY(!searchFeed->getNewsList()->isEmpty());
    QCOMPARE(searchFeed->getNewsList()->size(), 1);

    // Clean up (in production, FangApp calls loader->deleteLater()).
    delete loader;
}

void TestSearchOperation::testSearchEmptyQuery()
{
    insertTestNews(1, "Climate Report", "Summary", "Content.", "Author");

    searchFeed->setSearchQuery("");
    searchFeed->clearNews();

    SearchNewsOperation op(operationManager, searchFeed, LoadNewsOperation::Initial,
                           "", SearchNewsOperation::Scope::Global);
    op.execute();

    // Empty query should return no results.
    QVERIFY(op.getAppendList().isEmpty());
}

void TestSearchOperation::testSearchNoResults()
{
    insertTestNews(1, "Climate Report", "Summary", "Content.", "Author");

    searchFeed->setSearchQuery("dinosaurs");
    searchFeed->clearNews();

    SearchNewsOperation op(operationManager, searchFeed, LoadNewsOperation::Initial,
                           "dinosaurs", SearchNewsOperation::Scope::Global);
    op.execute();

    QVERIFY(op.getAppendList().isEmpty());
}

void TestSearchOperation::testSearchMultipleResults()
{
    insertTestNews(1, "Climate Change Report", "Summary", "Content about climate.", "Author",
                   1000);
    insertTestNews(1, "Climate News Update", "Climate summary", "More climate info.", "Author",
                   2000);
    insertTestNews(1, "Sports Update", "Sports summary", "No climate here.", "Author",
                   3000);

    searchFeed->setSearchQuery("climate");
    searchFeed->clearNews();

    SearchNewsOperation op(operationManager, searchFeed, LoadNewsOperation::Initial,
                           "climate", SearchNewsOperation::Scope::Global);
    op.execute();

    // Should find at least 2 results (the two climate articles).
    QVERIFY2(op.getAppendList().size() >= 2,
             qPrintable(QString("Expected >= 2 results, got %1").arg(op.getAppendList().size())));
}

void TestSearchOperation::testSearchScopedToFeed()
{
    // Insert items in different feeds.
    insertTestNews(1, "Climate Report Feed 1", "Summary", "Content about climate.", "Author");
    insertTestNews(2, "Climate Report Feed 2", "Summary", "Content about climate.", "Author");

    searchFeed->setSearchQuery("climate");
    searchFeed->setScope(SearchFeedItem::Scope::Feed, 1);
    searchFeed->clearNews();

    SearchNewsOperation op(operationManager, searchFeed, LoadNewsOperation::Initial,
                           "climate", SearchNewsOperation::Scope::Feed, 1);
    op.execute();

    // Should only find the result from feed 1.
    QCOMPARE(op.getAppendList().size(), 1);

    NewsItem* item = op.getAppendList().first();
    QCOMPARE(item->getFeedId(), 1LL);
}

void TestSearchOperation::testVirtualDispatchFromLoadNewsPointer()
{
    // Verify that calling execute() on a LoadNewsOperation* that points to a
    // SearchNewsOperation actually calls SearchNewsOperation::execute().
    // This is the exact scenario in the production code.

    insertTestNews(1, "Virtual Dispatch Test Article", "Summary about testing",
                   "This tests virtual dispatch.", "Tester");

    searchFeed->setSearchQuery("dispatch");
    searchFeed->clearNews();

    // Allocate as SearchNewsOperation but hold via LoadNewsOperation*.
    LoadNewsOperation* loader = new SearchNewsOperation(
        operationManager, searchFeed, LoadNewsOperation::Initial,
        "dispatch", SearchNewsOperation::Scope::Global);

    // Call execute through LoadNewsOperation* — must dispatch to SearchNewsOperation::execute().
    loader->execute();

    // If virtual dispatch works, we get search results.
    // If it called LoadNewsOperation::execute() instead, it would either:
    //   a) Early-return because SearchFeedItem is a special feed, OR
    //   b) Try to do a regular feed load using feed_id = -3 and find nothing.
    QVERIFY2(!loader->getAppendList().isEmpty(),
             "Virtual dispatch failed: execute() on LoadNewsOperation* should call "
             "SearchNewsOperation::execute() and find results");

    delete loader;
}

QTEST_MAIN(TestSearchOperation)

#include "tst_searchoperation.moc"
