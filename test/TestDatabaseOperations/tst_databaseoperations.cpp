#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

/**
 * Tests basic SQLite functionality.
 */
class TestDatabaseOperations : public QObject
{
    Q_OBJECT

public:
    TestDatabaseOperations();

private slots:
    void initTestCase();
    void cleanup();
    void cleanupTestCase();

    // Primary SQLite functionality
    void testDatabaseCreation();
    void testTableCreation();
    void testInsertData();
    void testSelectData();
    void testUpdateData();
    void testDeleteData();

    // Advanced-ish SQLite functionaly
    void testTransactions();
    void testPreparedStatements();
    void testForeignKeys();
    void testErrorHandling();

private:
    QSqlDatabase db;
    QString connectionName;
};

TestDatabaseOperations::TestDatabaseOperations()
    : connectionName("testdb")
{
}

void TestDatabaseOperations::initTestCase()
{
    // Create in-memory DB.
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");

    QVERIFY2(db.open(), qPrintable(db.lastError().text()));
}

void TestDatabaseOperations::cleanup()
{
    // Nuke our data between tests.
    QSqlQuery query(db);
    query.exec("DROP TABLE IF EXISTS test_feeds");
    query.exec("DROP TABLE IF EXISTS test_news");
}

void TestDatabaseOperations::cleanupTestCase()
{
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

void TestDatabaseOperations::testDatabaseCreation()
{
    QVERIFY(db.isOpen());
    QVERIFY(db.isValid());
    QCOMPARE(db.driverName(), QString("QSQLITE"));
}

void TestDatabaseOperations::testTableCreation()
{
    QSqlQuery query(db);

    // Test table.
    bool success = query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL,"
        "  url TEXT NOT NULL UNIQUE,"
        "  unread_count INTEGER DEFAULT 0"
        ")"
    );

    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Does our table exist?
    success = query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='test_feeds'");
    QVERIFY(success);
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("test_feeds"));
}

void TestDatabaseOperations::testInsertData()
{
    // Test table.
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL,"
        "  url TEXT NOT NULL,"
        "  unread_count INTEGER DEFAULT 0"
        ")"
    );

    // Perform an insert.
    query.prepare("INSERT INTO test_feeds (title, url, unread_count) VALUES (?, ?, ?)");
    query.addBindValue("Test Feed 1");
    query.addBindValue("http://example.com/feed1");
    query.addBindValue(5);

    bool success = query.exec();
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Did the insert succeed?
    qint64 id = query.lastInsertId().toLongLong();
    QVERIFY(id > 0);

    query.exec("SELECT COUNT(*) FROM test_feeds");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);
}

void TestDatabaseOperations::testSelectData()
{
    // Test table.
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL,"
        "  url TEXT NOT NULL,"
        "  unread_count INTEGER DEFAULT 0"
        ")"
    );

    // Test data.
    query.exec("INSERT INTO test_feeds (title, url, unread_count) VALUES ('Feed 1', 'http://example.com/1', 3)");
    query.exec("INSERT INTO test_feeds (title, url, unread_count) VALUES ('Feed 2', 'http://example.com/2', 7)");
    query.exec("INSERT INTO test_feeds (title, url, unread_count) VALUES ('Feed 3', 'http://example.com/3', 0)");

    // Try a SELECT
    bool success = query.exec("SELECT id, title, url, unread_count FROM test_feeds ORDER BY id");
    QVERIFY2(success, qPrintable(query.lastError().text()));

    // Row 1 check
    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("Feed 1"));
    QCOMPARE(query.value("url").toString(), QString("http://example.com/1"));
    QCOMPARE(query.value("unread_count").toInt(), 3);

    // Row 2 check
    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("Feed 2"));
    QCOMPARE(query.value("unread_count").toInt(), 7);

    // Row 3 check
    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("Feed 3"));

    // That's all, folks!
    QVERIFY(!query.next());
}

void TestDatabaseOperations::testUpdateData()
{
    // Test table.
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL,"
        "  url TEXT NOT NULL,"
        "  unread_count INTEGER DEFAULT 0"
        ")"
    );

    // Test data.
    query.exec("INSERT INTO test_feeds (title, url, unread_count) VALUES ('Old Title', 'http://example.com/feed', 5)");

    // Try an UPDATE
    query.prepare("UPDATE test_feeds SET title = ?, unread_count = ? WHERE url = ?");
    query.addBindValue("New Title");
    query.addBindValue(10);
    query.addBindValue("http://example.com/feed");

    bool success = query.exec();
    QVERIFY2(success, qPrintable(query.lastError().text()));
    QCOMPARE(query.numRowsAffected(), 1);

    // Did our UPDATE work?
    query.exec("SELECT title, unread_count FROM test_feeds WHERE url = 'http://example.com/feed'");
    QVERIFY(query.next());
    QCOMPARE(query.value("title").toString(), QString("New Title"));
    QCOMPARE(query.value("unread_count").toInt(), 10);
}

void TestDatabaseOperations::testDeleteData()
{
    // Test table.
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL,"
        "  url TEXT NOT NULL"
        ")"
    );

    // Test data
    query.exec("INSERT INTO test_feeds (title, url) VALUES ('Feed 1', 'http://example.com/1')");
    query.exec("INSERT INTO test_feeds (title, url) VALUES ('Feed 2', 'http://example.com/2')");
    query.exec("INSERT INTO test_feeds (title, url) VALUES ('Feed 3', 'http://example.com/3')");

    // Delete it all.
    // "Pull the boards!" - RoboCop
    query.prepare("DELETE FROM test_feeds WHERE url = ?");
    query.addBindValue("http://example.com/2");

    bool success = query.exec();
    QVERIFY2(success, qPrintable(query.lastError().text()));
    QCOMPARE(query.numRowsAffected(), 1);

    // Did we delete?
    query.exec("SELECT COUNT(*) FROM test_feeds");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 2);

    // Did we delete what we *meant* to delete?
    query.exec("SELECT url FROM test_feeds WHERE url = 'http://example.com/2'");
    QVERIFY(!query.next());  // Should be gone

    query.exec("SELECT url FROM test_feeds WHERE url = 'http://example.com/1'");
    QVERIFY(query.next());  // Should still exist
}

void TestDatabaseOperations::testTransactions()
{
    // Test table.
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL"
        ")"
    );

    // Start a transaction.
    QVERIFY(db.transaction());

    // Test data.
    query.exec("INSERT INTO test_feeds (title) VALUES ('Feed 1')");
    query.exec("INSERT INTO test_feeds (title) VALUES ('Feed 2')");

    // Complete transaction.
    QVERIFY(db.commit());

    // Did our transaction succeed?
    query.exec("SELECT COUNT(*) FROM test_feeds");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 2);

    // Start a transaction.
    QVERIFY(db.transaction());

    // Test data.
    query.exec("INSERT INTO test_feeds (title) VALUES ('Feed 3')");
    query.exec("INSERT INTO test_feeds (title) VALUES ('Feed 4')");

    // Roll back the transaction. Just like Wal-Mart, rolling back those prices.
    QVERIFY(db.rollback());

    // Did our rollback succeed? If so we should have the original two rows, but not the new ones.
    query.exec("SELECT COUNT(*) FROM test_feeds");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 2);
}

void TestDatabaseOperations::testPreparedStatements()
{
    // Test table.
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL,"
        "  unread_count INTEGER"
        ")"
    );

    // Prepare statement, use  it 5x.
    query.prepare("INSERT INTO test_feeds (title, unread_count) VALUES (:title, :count)");

    for (int i = 1; i <= 5; i++) {
        query.bindValue(":title", QString("Feed %1").arg(i));
        query.bindValue(":count", i * 2);
        QVERIFY2(query.exec(), qPrintable(query.lastError().text()));
    }

    // We should have five separate rows from the inserts.
    query.exec("SELECT COUNT(*) FROM test_feeds");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 5);

    // Double check an inserted value.
    query.exec("SELECT title, unread_count FROM test_feeds WHERE title = 'Feed 3'");
    QVERIFY(query.next());
    QCOMPARE(query.value("unread_count").toInt(), 6);
}

void TestDatabaseOperations::testForeignKeys()
{
    QSqlQuery query(db);

    // Enable foreign key support.
    query.exec("PRAGMA foreign_keys = ON");

    // Test table.
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  title TEXT NOT NULL"
        ")"
    );

    // "Child" test table.
    query.exec(
        "CREATE TABLE test_news ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  feed_id INTEGER NOT NULL,"
        "  title TEXT NOT NULL,"
        "  FOREIGN KEY (feed_id) REFERENCES test_feeds(id) ON DELETE CASCADE"
        ")"
    );

    // Insert into parent table.
    query.exec("INSERT INTO test_feeds (title) VALUES ('Test Feed')");
    qint64 feedId = query.lastInsertId().toLongLong();

    // Insert into child table.
    query.prepare("INSERT INTO test_news (feed_id, title) VALUES (?, ?)");
    query.addBindValue(feedId);
    query.addBindValue("News Item 1");
    QVERIFY2(query.exec(), qPrintable(query.lastError().text()));

    // Try to insert with invalid foreign key.
    query.prepare("INSERT INTO test_news (feed_id, title) VALUES (?, ?)");
    query.addBindValue(99999);  // Fake feed_id
    query.addBindValue("Invalid News");
    QVERIFY(!query.exec());

    // Deleting parent should delete from child table.
    query.exec(QString("DELETE FROM test_feeds WHERE id = %1").arg(feedId));
    query.exec("SELECT COUNT(*) FROM test_news");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 0);
}

void TestDatabaseOperations::testErrorHandling()
{
    QSqlQuery query(db);

    // What happens if we insert invalid SQL?
    bool success = query.exec("SELECT * FROM nonexistent_table");
    QVERIFY(!success);
    QVERIFY(!query.lastError().text().isEmpty());

    // Mangled SQL syntax.
    success = query.exec("INVALID SQL STATEMENT");
    QVERIFY(!success);

    // Test table with unique URL per row.
    query.exec(
        "CREATE TABLE test_feeds ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  url TEXT NOT NULL UNIQUE"
        ")"
    );

    // Second insertion should fail due to non-UNIQUE value.
    query.exec("INSERT INTO test_feeds (url) VALUES ('http://example.com')");
    success = query.exec("INSERT INTO test_feeds (url) VALUES ('http://example.com')");
    QVERIFY(!success);
}

QTEST_MAIN(TestDatabaseOperations)

#include "tst_databaseoperations.moc"
