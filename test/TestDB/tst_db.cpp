#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QStringList>
#include "../../src/db/DB.h"

/**
 * Verify DB schema creation, upgrades, and simple query execution.
 */
class TestDB : public QObject
{
    Q_OBJECT

public:
    TestDB();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testInitForTesting_createsSchema();
    void testSchemaVersion_isLatest();
    void testForeignKeys_enabled();
    void testForeignKeys_enforced();
    void testExecuteSimpleQuery_validQuery();
    void testExecuteSimpleQuery_invalidQuery();
    void testFTS5Table_exists();
    void testIndexes_exist();
    void testAllColumns_feedItemTable();
    void testAllColumns_newsItemTable();

private:
    QSqlDatabase testDb;
    QString connectionName;

    bool tableExists(const QString& tableName);
    bool indexExists(const QString& indexName);
    QStringList getColumnNames(const QString& tableName);
};

TestDB::TestDB()
    : connectionName("test_db_connection")
{
}

void TestDB::initTestCase()
{
    testDb = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    testDb.setDatabaseName(":memory:");
    QVERIFY2(testDb.open(), qPrintable(testDb.lastError().text()));

    DB::instance()->initForTesting(testDb);
}

void TestDB::cleanupTestCase()
{
    testDb.close();
    QSqlDatabase::removeDatabase(connectionName);
}

bool TestDB::tableExists(const QString& tableName)
{
    QSqlQuery q(testDb);
    q.prepare("SELECT name FROM sqlite_master WHERE type IN ('table', 'view') AND name = ?");
    q.addBindValue(tableName);
    q.exec();
    return q.next();
}

bool TestDB::indexExists(const QString& indexName)
{
    QSqlQuery q(testDb);
    q.prepare("SELECT name FROM sqlite_master WHERE type='index' AND name = ?");
    q.addBindValue(indexName);
    q.exec();
    return q.next();
}

QStringList TestDB::getColumnNames(const QString& tableName)
{
    QStringList columns;
    QSqlQuery q(testDb);
    q.exec(QString("PRAGMA table_info(%1)").arg(tableName));
    while (q.next()) {
        columns << q.value(1).toString();
    }
    return columns;
}

void TestDB::testInitForTesting_createsSchema()
{
    QVERIFY(tableExists("FeedItemTable"));
    QVERIFY(tableExists("NewsItemTable"));
    QVERIFY(tableExists("DBSettings"));
}

void TestDB::testSchemaVersion_isLatest()
{
    QSqlQuery q(testDb);
    QVERIFY(q.exec("PRAGMA user_version"));
    QVERIFY(q.next());
    QCOMPARE(q.value(0).toInt(), 10);
}

void TestDB::testForeignKeys_enabled()
{
    QSqlQuery q(testDb);
    QVERIFY(q.exec("PRAGMA foreign_keys"));
    QVERIFY(q.next());
    QCOMPARE(q.value(0).toInt(), 1);
}

void TestDB::testForeignKeys_enforced()
{
    QSqlQuery q(testDb);

    // Insert with a non-existent feed_id should fail.
    bool result = q.exec(
        "INSERT INTO NewsItemTable (id, feed_id, guid, title, author, summary, content, timestamp, url) "
        "VALUES (99999, 99999, 'test-guid', 'Test', '', '', '', 0, '')"
    );

    QVERIFY2(!result, "INSERT with invalid FK should fail when foreign keys are enforced");
}

void TestDB::testExecuteSimpleQuery_validQuery()
{
    QVERIFY(DB::instance()->executeSimpleQuery("SELECT 1"));
}

void TestDB::testExecuteSimpleQuery_invalidQuery()
{
    QVERIFY(!DB::instance()->executeSimpleQuery("THIS IS NOT VALID SQL"));
}

void TestDB::testFTS5Table_exists()
{
    QVERIFY(tableExists("NewsItemFTS"));
}

void TestDB::testIndexes_exist()
{
    // v6 compound indexes
    QVERIFY(indexExists("NewsItemTableFeedTimestampIdIndex"));
    QVERIFY(indexExists("FeedItemTableFolderOrdinalIndex"));
    QVERIFY(indexExists("NewsItemTableTimestampIdIndex"));
    QVERIFY(indexExists("NewsItemTableFeedPinnedTimestampIndex"));
}

void TestDB::testAllColumns_feedItemTable()
{
    QStringList columns = getColumnNames("FeedItemTable");

    // v1 columns
    QVERIFY(columns.contains("id"));
    QVERIFY(columns.contains("title"));
    QVERIFY(columns.contains("subtitle"));
    QVERIFY(columns.contains("lastUpdated"));
    QVERIFY(columns.contains("minutesToUpdate"));
    QVERIFY(columns.contains("url"));
    QVERIFY(columns.contains("siteURL"));
    QVERIFY(columns.contains("imageURL"));
    QVERIFY(columns.contains("lastIconUpdate"));
    QVERIFY(columns.contains("ordinal"));
    QVERIFY(columns.contains("bookmark_id"));

    // v4 columns (folders)
    QVERIFY(columns.contains("is_folder"));
    QVERIFY(columns.contains("folder_open"));
    QVERIFY(columns.contains("parent_folder"));

    // v5 columns
    QVERIFY(columns.contains("user_url"));

    // v8 columns
    QVERIFY(columns.contains("feed_type"));

    // v9 columns
    QVERIFY(columns.contains("etag"));
    QVERIFY(columns.contains("last_modified"));
}

void TestDB::testAllColumns_newsItemTable()
{
    QStringList columns = getColumnNames("NewsItemTable");

    // v1 columns
    QVERIFY(columns.contains("id"));
    QVERIFY(columns.contains("feed_id"));
    QVERIFY(columns.contains("guid"));
    QVERIFY(columns.contains("title"));
    QVERIFY(columns.contains("author"));
    QVERIFY(columns.contains("summary"));
    QVERIFY(columns.contains("content"));
    QVERIFY(columns.contains("timestamp"));
    QVERIFY(columns.contains("url"));

    // v2 columns (pinning)
    QVERIFY(columns.contains("pinned"));

    // v10 columns
    QVERIFY(columns.contains("media_image_url"));
}

QTEST_MAIN(TestDB)

#include "tst_db.moc"
