#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QRandomGenerator>

/**
 * Tests FTS5 full-text search functionality for news items.
 */
class TestSearch : public QObject
{
    Q_OBJECT

public:
    TestSearch();

private slots:
    void initTestCase();
    void cleanup();
    void cleanupTestCase();

    // FTS5 basic functionality
    void testFTS5TableCreation();
    void testFTS5BasicSearch();
    void testFTS5MultipleTerms();
    void testFTS5RelevanceRanking();

    // Highlighting
    void testHighlightFunction();
    void testHighlightPreservesHTML();

    // Triggers
    void testInsertTrigger();
    void testDeleteTrigger();
    void testUpdateTrigger();

    // Edge cases
    void testEmptyQuery();
    void testSpecialCharacters();
    void testNoResults();

    // Integration test (mimics SearchNewsOperation query)
    void testHighlightWithJoin();

private:
    void createSchema();
    void insertTestNews(qint64 feedId, const QString& title, const QString& summary,
                        const QString& content, const QString& author);

    QSqlDatabase db;
    QString connectionName;
};

TestSearch::TestSearch()
    : connectionName("testsearchdb")
{
}

void TestSearch::initTestCase()
{
    // Create in-memory DB.
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");

    QVERIFY2(db.open(), qPrintable(db.lastError().text()));

    createSchema();
}

void TestSearch::createSchema()
{
    QSqlQuery query(db);

    // Create FeedItemTable (minimal version for testing)
    bool success = query.exec(
        "CREATE TABLE FeedItemTable ("
        "  id INTEGER PRIMARY KEY,"
        "  title TEXT NOT NULL"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Create NewsItemTable
    success = query.exec(
        "CREATE TABLE NewsItemTable ("
        "  id INTEGER PRIMARY KEY,"
        "  feed_id INTEGER REFERENCES FeedItemTable(id) ON DELETE CASCADE,"
        "  guid TEXT NOT NULL,"
        "  title TEXT NOT NULL,"
        "  author TEXT NOT NULL,"
        "  summary TEXT NOT NULL,"
        "  content TEXT NOT NULL,"
        "  timestamp INTEGER DEFAULT 0,"
        "  url TEXT NOT NULL,"
        "  pinned INTEGER DEFAULT 0,"
        "  UNIQUE(feed_id, guid) ON CONFLICT IGNORE"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Create FTS5 virtual table
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

    // Create triggers
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

    // Insert a test feed
    query.exec("INSERT INTO FeedItemTable (id, title) VALUES (1, 'Test Feed')");
}

void TestSearch::cleanup()
{
    // Clear news items between tests (but keep schema)
    QSqlQuery query(db);
    query.exec("DELETE FROM NewsItemTable");
}

void TestSearch::cleanupTestCase()
{
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

void TestSearch::insertTestNews(qint64 feedId, const QString& title, const QString& summary,
                                 const QString& content, const QString& author)
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
    query.bindValue(":timestamp", QDateTime::currentSecsSinceEpoch());
    query.bindValue(":url", "http://example.com/news");

    bool success = query.exec();
    QVERIFY2(success, qPrintable(query.lastError().text()));
}

void TestSearch::testFTS5TableCreation()
{
    QSqlQuery query(db);

    // Verify FTS table exists
    bool success = query.exec(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='NewsItemFTS'"
    );
    QVERIFY(success);
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("NewsItemFTS"));
}

void TestSearch::testFTS5BasicSearch()
{
    // Insert test data
    insertTestNews(1, "Climate Change Report", "Summary of climate findings",
                   "The climate is changing rapidly.", "Dr. Smith");
    insertTestNews(1, "Sports Update", "Latest sports news",
                   "The team won the championship.", "John Doe");
    insertTestNews(1, "Weather Forecast", "Weekly weather",
                   "Expect sunny skies this week.", "Jane Doe");

    // Search for "climate"
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT N.id, N.title FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH 'climate'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("Climate Change Report"));
    QVERIFY(!query.next());  // Only one result
}

void TestSearch::testFTS5MultipleTerms()
{
    insertTestNews(1, "Climate Change Report", "Summary",
                   "The global climate is changing.", "Dr. Smith");
    insertTestNews(1, "Local Weather Update", "Summary",
                   "Climate patterns affect local weather.", "Jane Doe");
    insertTestNews(1, "Sports News", "Summary",
                   "The team played in hot weather.", "John Doe");

    // Search for "climate weather" (implicit AND)
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT N.title FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH 'climate weather'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Should match "Local Weather Update" which has both terms
    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("Local Weather Update"));
    QVERIFY(!query.next());
}

void TestSearch::testFTS5RelevanceRanking()
{
    // Insert items with varying relevance to "climate"
    insertTestNews(1, "Climate Climate Climate", "climate climate",
                   "Climate is mentioned many times.", "Climate Expert");
    insertTestNews(1, "Weather Report", "Summary",
                   "The climate is changing.", "Jane Doe");
    insertTestNews(1, "Climate News", "Summary",
                   "Brief climate mention.", "John Doe");

    // Search with bm25 ranking
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT N.title FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH 'climate' "
        "ORDER BY bm25(NewsItemFTS)"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // First result should be the one with most "climate" mentions
    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("Climate Climate Climate"));
}

void TestSearch::testHighlightFunction()
{
    insertTestNews(1, "Climate Change Report", "A summary about climate",
                   "The climate is changing rapidly.", "Dr. Smith");

    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT "
        "  highlight(NewsItemFTS, 0, '<mark>', '</mark>') AS title_hl, "
        "  highlight(NewsItemFTS, 1, '<mark>', '</mark>') AS summary_hl, "
        "  highlight(NewsItemFTS, 2, '<mark>', '</mark>') AS content_hl "
        "FROM NewsItemFTS "
        "WHERE NewsItemFTS MATCH 'climate'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    QVERIFY(query.next());
    QCOMPARE(query.value("title_hl").toString(), QString("<mark>Climate</mark> Change Report"));
    QCOMPARE(query.value("summary_hl").toString(), QString("A summary about <mark>climate</mark>"));
    QCOMPARE(query.value("content_hl").toString(), QString("The <mark>climate</mark> is changing rapidly."));
}

void TestSearch::testHighlightPreservesHTML()
{
    // Insert content with HTML tags
    insertTestNews(1, "Climate Report", "Summary",
                   "<p>The <strong>climate</strong> is changing.</p>", "Dr. Smith");

    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT highlight(NewsItemFTS, 2, '<mark>', '</mark>') AS content_hl "
        "FROM NewsItemFTS "
        "WHERE NewsItemFTS MATCH 'climate'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    QVERIFY(query.next());
    QString highlighted = query.value("content_hl").toString();

    // The highlight should be inserted around the word, preserving HTML structure
    QVERIFY(highlighted.contains("<mark>climate</mark>"));
    QVERIFY(highlighted.contains("<p>"));
    QVERIFY(highlighted.contains("</p>"));
}

void TestSearch::testInsertTrigger()
{
    // Insert new item
    insertTestNews(1, "New Article About Space", "Space exploration summary",
                   "NASA launches new mission.", "Space Reporter");

    // Search should find it immediately (trigger should have updated FTS)
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT N.title FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH 'space'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("New Article About Space"));
}

void TestSearch::testDeleteTrigger()
{
    insertTestNews(1, "Article To Delete", "Summary",
                   "This will be deleted.", "Author");

    // Verify it's searchable
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemFTS WHERE NewsItemFTS MATCH 'deleted'");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    // Delete the news item
    query.exec("DELETE FROM NewsItemTable WHERE title = 'Article To Delete'");

    // Should no longer be searchable
    query.exec("SELECT COUNT(*) FROM NewsItemFTS WHERE NewsItemFTS MATCH 'deleted'");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 0);
}

void TestSearch::testUpdateTrigger()
{
    insertTestNews(1, "Original Title", "Summary",
                   "Original content about cats.", "Author");

    // Verify original is searchable
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemFTS WHERE NewsItemFTS MATCH 'cats'");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    // Update the content
    query.exec("UPDATE NewsItemTable SET content = 'Updated content about dogs.' WHERE title = 'Original Title'");

    // Old term should not be found
    query.exec("SELECT COUNT(*) FROM NewsItemFTS WHERE NewsItemFTS MATCH 'cats'");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 0);

    // New term should be found
    query.exec("SELECT COUNT(*) FROM NewsItemFTS WHERE NewsItemFTS MATCH 'dogs'");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);
}

void TestSearch::testEmptyQuery()
{
    insertTestNews(1, "Test Article", "Summary", "Content", "Author");

    // Empty match should fail or return nothing
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT COUNT(*) FROM NewsItemFTS WHERE NewsItemFTS MATCH ''"
    );

    // FTS5 should reject empty queries
    QVERIFY(!success || (query.next() && query.value(0).toInt() == 0));
}

void TestSearch::testSpecialCharacters()
{
    // Insert content with special characters
    insertTestNews(1, "C++ Programming Guide", "Learn C++ basics",
                   "C++ is a powerful language.", "Developer");

    // FTS5 should handle this (though + is typically ignored)
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT N.title FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH 'programming'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    QVERIFY(query.next());
    QVERIFY(query.value("title").toString().contains("Programming"));
}

void TestSearch::testNoResults()
{
    insertTestNews(1, "Article About Cats", "Cats are great",
                   "Cats sleep a lot.", "Cat Lover");

    // Search for something that doesn't exist
    QSqlQuery query(db);
    bool success = query.exec(
        "SELECT N.title FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH 'dinosaurs'"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Should return no results
    QVERIFY(!query.next());
}

void TestSearch::testHighlightWithJoin()
{
    // This test mimics the exact query used in SearchNewsOperation to verify
    // that highlight() works correctly when combined with a JOIN.
    insertTestNews(1, "Climate Change Report", "A summary about climate",
                   "The climate is changing rapidly.", "Dr. Smith");

    QSqlQuery query(db);
    query.prepare(
        "SELECT "
        "  N.id, N.feed_id, N.guid, N.author, N.timestamp, N.url, N.pinned, "
        "  highlight(NewsItemFTS, 0, '<mark>', '</mark>') AS title, "
        "  highlight(NewsItemFTS, 1, '<mark>', '</mark>') AS summary, "
        "  highlight(NewsItemFTS, 2, '<mark>', '</mark>') AS content "
        "FROM NewsItemTable N "
        "JOIN NewsItemFTS F ON N.id = F.rowid "
        "WHERE NewsItemFTS MATCH :search_query "
        "AND N.id NOT IN (-1) "
        "ORDER BY bm25(NewsItemFTS), N.timestamp DESC, N.id DESC "
        "LIMIT :load_limit"
    );
    query.bindValue(":search_query", "\"climate\"");  // Quoted like sanitizeSearchQuery does
    query.bindValue(":load_limit", 15);

    bool success = query.exec();
    QVERIFY2(success, qPrintable(query.lastError().text()));

    QVERIFY(query.next());

    // Verify we get highlighted results
    QString title = query.value("title").toString();
    QString summary = query.value("summary").toString();
    QString content = query.value("content").toString();

    qDebug() << "Title:" << title;
    qDebug() << "Summary:" << summary;
    qDebug() << "Content:" << content;

    QVERIFY2(title.contains("<mark>"), qPrintable("Title should contain <mark>: " + title));
    QVERIFY2(summary.contains("<mark>"), qPrintable("Summary should contain <mark>: " + summary));
    QVERIFY2(content.contains("<mark>"), qPrintable("Content should contain <mark>: " + content));

    // Verify the exact highlighted strings
    QCOMPARE(title, QString("<mark>Climate</mark> Change Report"));
    QCOMPARE(summary, QString("A summary about <mark>climate</mark>"));
    QCOMPARE(content, QString("The <mark>climate</mark> is changing rapidly."));
}

QTEST_MAIN(TestSearch)

#include "tst_search.moc"
