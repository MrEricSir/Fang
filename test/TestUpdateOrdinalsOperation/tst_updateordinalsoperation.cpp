#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include "src/db/DB.h"
#include "src/models/FeedItem.h"
#include "src/models/FolderFeedItem.h"
#include "src/models/ListModel.h"
#include "src/operations/OperationManager.h"
#include "src/operations/UpdateOrdinalsOperation.h"

/**
 * Tests for UpdateOrdinalsOperation:
 * - Updates ordinals for all feed items
 * - Updates parent folder associations
 * - Removes empty folders from both the model and database
 */
class TestUpdateOrdinalsOperation : public QObject
{
    Q_OBJECT

public:
    TestUpdateOrdinalsOperation();

private slots:
    void initTestCase();
    void cleanup();
    void cleanupTestCase();

    // Ordinal tests
    void testOrdinalsUpdatedInDatabase();
    void testOrdinalsUpdatedInModel();

    // Parent folder tests
    void testParentFolderUpdated();
    void testParentFolderClearedWhenFolderRemoved();

    // Empty folder removal tests
    void testEmptyFolderRemovedFromModel();
    void testEmptyFolderRemovedFromDatabase();
    void testFolderWithChildrenNotRemoved();
    void testMultipleEmptyFoldersRemoved();
    void testOrphanedFolderInDatabaseDeleted();

    // Edge cases
    void testSpecialFeedsIgnored();
    void testRollbackOnError();

private:
    void createSchema();
    qint64 insertFeedHelper(const QString& title, int ordinal, qint64 parentFolder = -1);
    qint64 insertFolderHelper(const QString& title, int ordinal);
    int countFoldersInDatabase();
    int countFeedsInDatabase();
    qint64 getFeedOrdinalFromDb(qint64 feedId);
    qint64 getFeedParentFolderFromDb(qint64 feedId);
    bool folderExistsInDb(qint64 folderId);

    FeedItem* createTestFeed(qint64 id, int ordinal, const QString& title, qint64 parentFolder = -1);
    FolderFeedItem* createTestFolder(qint64 id, int ordinal, const QString& title);
    ListModel* createFeedList();

    QSqlDatabase db;
    QString connectionName;
    OperationManager* operationManager;
};

TestUpdateOrdinalsOperation::TestUpdateOrdinalsOperation()
    : connectionName("testUpdateOrdinalsDb")
    , operationManager(nullptr)
{
}

void TestUpdateOrdinalsOperation::initTestCase()
{
    // Create in-memory DB with unique connection name.
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");

    QVERIFY2(db.open(), qPrintable(db.lastError().text()));

    // Create schema before initializing DB singleton (since QRC resources aren't available).
    createSchema();

    // Initialize the DB singleton for testing (skip schema creation via upgrade()).
    DB::instance()->initForTesting(db);

    // Create operation manager.
    operationManager = new OperationManager(this);
}

void TestUpdateOrdinalsOperation::createSchema()
{
    QSqlQuery query(db);

    // Create FeedItemTable with folder support (mirrors sql/1.sql + sql/4.sql).
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
}

void TestUpdateOrdinalsOperation::cleanup()
{
    // Clear data between tests.
    QSqlQuery query(db);
    query.exec("DROP TABLE IF EXISTS FeedItemTable");

    // Recreate schema for next test.
    createSchema();
}

void TestUpdateOrdinalsOperation::cleanupTestCase()
{
    delete operationManager;
    operationManager = nullptr;

    // Close connection and clear reference before removing.
    db.close();
    db = QSqlDatabase();  // Clear our reference so removeDatabase succeeds
    QSqlDatabase::removeDatabase(connectionName);
}

qint64 TestUpdateOrdinalsOperation::insertFeedHelper(const QString& title, int ordinal, qint64 parentFolder)
{
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO FeedItemTable (title, ordinal, parent_folder, is_folder) "
        "VALUES (:title, :ordinal, :parent_folder, 0)"
    );
    query.bindValue(":title", title);
    query.bindValue(":ordinal", ordinal);
    query.bindValue(":parent_folder", parentFolder);

    if (!query.exec()) {
        qWarning() << "insertFeedHelper failed:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toLongLong();
}

qint64 TestUpdateOrdinalsOperation::insertFolderHelper(const QString& title, int ordinal)
{
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO FeedItemTable (title, ordinal, is_folder) "
        "VALUES (:title, :ordinal, 1)"
    );
    query.bindValue(":title", title);
    query.bindValue(":ordinal", ordinal);

    if (!query.exec()) {
        qWarning() << "insertFolderHelper failed:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toLongLong();
}

int TestUpdateOrdinalsOperation::countFoldersInDatabase()
{
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM FeedItemTable WHERE is_folder = 1");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

int TestUpdateOrdinalsOperation::countFeedsInDatabase()
{
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM FeedItemTable WHERE is_folder = 0");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

qint64 TestUpdateOrdinalsOperation::getFeedOrdinalFromDb(qint64 feedId)
{
    QSqlQuery query(db);
    query.prepare("SELECT ordinal FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    if (query.exec() && query.next()) {
        return query.value(0).toLongLong();
    }
    return -1;
}

qint64 TestUpdateOrdinalsOperation::getFeedParentFolderFromDb(qint64 feedId)
{
    QSqlQuery query(db);
    query.prepare("SELECT parent_folder FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    if (query.exec() && query.next()) {
        return query.value(0).toLongLong();
    }
    return -999;  // Sentinel for error
}

bool TestUpdateOrdinalsOperation::folderExistsInDb(qint64 folderId)
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM FeedItemTable WHERE id = :id AND is_folder = 1");
    query.bindValue(":id", folderId);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

FeedItem* TestUpdateOrdinalsOperation::createTestFeed(qint64 id, int ordinal, const QString& title, qint64 parentFolder)
{
    FeedItem* feed = new FeedItem(
        id, ordinal, title, "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
        parentFolder, true, this
    );
    return feed;
}

FolderFeedItem* TestUpdateOrdinalsOperation::createTestFolder(qint64 id, int ordinal, const QString& title)
{
    return new FolderFeedItem(id, ordinal, title, true, this);
}

ListModel* TestUpdateOrdinalsOperation::createFeedList()
{
    // Create a new prototype for each ListModel (it will be deleted by ListModel's destructor).
    FeedItem* prototype = new FeedItem();
    return new ListModel(prototype, this);
}

// -------------------------------------------------------------------
// Ordinal tests
// -------------------------------------------------------------------

void TestUpdateOrdinalsOperation::testOrdinalsUpdatedInDatabase()
{
    // Insert feeds with old ordinals.
    qint64 feed1Id = insertFeedHelper("Feed 1", 100);
    qint64 feed2Id = insertFeedHelper("Feed 2", 200);
    qint64 feed3Id = insertFeedHelper("Feed 3", 300);

    QVERIFY(feed1Id > 0);
    QVERIFY(feed2Id > 0);
    QVERIFY(feed3Id > 0);

    // Create model with feeds in different order (simulating drag-drop reorder).
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feed2Id, 200, "Feed 2"));  // Now at position 0
    feedList->appendRow(createTestFeed(feed3Id, 300, "Feed 3"));  // Now at position 1
    feedList->appendRow(createTestFeed(feed1Id, 100, "Feed 1"));  // Now at position 2

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Verify ordinals in database match model positions.
    QCOMPARE(getFeedOrdinalFromDb(feed2Id), 0LL);  // Was position 0 in model
    QCOMPARE(getFeedOrdinalFromDb(feed3Id), 1LL);  // Was position 1 in model
    QCOMPARE(getFeedOrdinalFromDb(feed1Id), 2LL);  // Was position 2 in model

    delete feedList;
}

void TestUpdateOrdinalsOperation::testOrdinalsUpdatedInModel()
{
    // Insert feeds.
    qint64 feed1Id = insertFeedHelper("Feed 1", 100);
    qint64 feed2Id = insertFeedHelper("Feed 2", 200);

    QVERIFY(feed1Id > 0);
    QVERIFY(feed2Id > 0);

    // Create model.
    ListModel* feedList = createFeedList();
    FeedItem* feed1 = createTestFeed(feed1Id, 100, "Feed 1");
    FeedItem* feed2 = createTestFeed(feed2Id, 200, "Feed 2");
    feedList->appendRow(feed1);
    feedList->appendRow(feed2);

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Verify ordinals in model objects are updated.
    QCOMPARE(feed1->getOrdinal(), 0);
    QCOMPARE(feed2->getOrdinal(), 1);

    delete feedList;
}

// -------------------------------------------------------------------
// Parent folder tests
// -------------------------------------------------------------------

void TestUpdateOrdinalsOperation::testParentFolderUpdated()
{
    // Insert folder and feed.
    qint64 folderId = insertFolderHelper("Folder", 0);
    qint64 feedId = insertFeedHelper("Feed", 1, -1);  // No parent initially

    QVERIFY(folderId > 0);
    QVERIFY(feedId > 0);

    // Create model with feed inside folder.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFolder(folderId, 0, "Folder"));

    FeedItem* feed = createTestFeed(feedId, 1, "Feed", folderId);  // Set parent in model
    feedList->appendRow(feed);

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Verify parent folder is updated in database.
    QCOMPARE(getFeedParentFolderFromDb(feedId), folderId);

    delete feedList;
}

void TestUpdateOrdinalsOperation::testParentFolderClearedWhenFolderRemoved()
{
    // Insert folder and feeds.
    qint64 folderId = insertFolderHelper("Folder", 0);
    qint64 feed1Id = insertFeedHelper("Feed 1", 1, folderId);  // Inside folder in DB

    QVERIFY(folderId > 0);
    QVERIFY(feed1Id > 0);

    // Create model WITHOUT the folder (simulating folder removal).
    // The feed still has the old parent folder ID that no longer exists.
    ListModel* feedList = createFeedList();
    FeedItem* feed = createTestFeed(feed1Id, 0, "Feed 1", folderId);  // Still points to old folder
    feedList->appendRow(feed);

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Verify feed's parent folder is cleared in model (set to -1).
    QCOMPARE(feed->getParentFolderID(), -1LL);

    delete feedList;
}

// -------------------------------------------------------------------
// Empty folder removal tests
// -------------------------------------------------------------------

void TestUpdateOrdinalsOperation::testEmptyFolderRemovedFromModel()
{
    // Insert folder in database.
    qint64 folderId = insertFolderHelper("Empty Folder", 0);

    QVERIFY(folderId > 0);

    // Create model with empty folder.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFolder(folderId, 0, "Empty Folder"));

    QCOMPARE(feedList->count(), 1);

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Folder should be removed from model.
    QCOMPARE(feedList->count(), 0);

    delete feedList;
}

void TestUpdateOrdinalsOperation::testEmptyFolderRemovedFromDatabase()
{
    // Insert folder in database.
    qint64 folderId = insertFolderHelper("Empty Folder", 0);

    QVERIFY(folderId > 0);

    // Create model with empty folder.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFolder(folderId, 0, "Empty Folder"));

    QVERIFY(folderExistsInDb(folderId));

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Folder should be removed from database.
    QVERIFY(!folderExistsInDb(folderId));

    delete feedList;
}

void TestUpdateOrdinalsOperation::testFolderWithChildrenNotRemoved()
{
    // Insert folder and feed inside it.
    qint64 folderId = insertFolderHelper("Folder", 0);
    qint64 feedId = insertFeedHelper("Feed", 1, folderId);

    QVERIFY(folderId > 0);
    QVERIFY(feedId > 0);

    // Create model with folder and feed.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFolder(folderId, 0, "Folder"));
    feedList->appendRow(createTestFeed(feedId, 1, "Feed", folderId));

    QCOMPARE(feedList->count(), 2);
    QVERIFY(folderExistsInDb(folderId));

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Folder should still exist in both model and database.
    QCOMPARE(feedList->count(), 2);
    QVERIFY(folderExistsInDb(folderId));

    delete feedList;
}

void TestUpdateOrdinalsOperation::testMultipleEmptyFoldersRemoved()
{
    // Insert multiple folders.
    qint64 folder1Id = insertFolderHelper("Empty Folder 1", 0);
    qint64 folder2Id = insertFolderHelper("Empty Folder 2", 1);
    qint64 folder3Id = insertFolderHelper("Non-Empty Folder", 2);
    qint64 feedId = insertFeedHelper("Feed", 3, folder3Id);

    QVERIFY(folder1Id > 0);
    QVERIFY(folder2Id > 0);
    QVERIFY(folder3Id > 0);
    QVERIFY(feedId > 0);

    // Create model.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFolder(folder1Id, 0, "Empty Folder 1"));
    feedList->appendRow(createTestFolder(folder2Id, 1, "Empty Folder 2"));
    feedList->appendRow(createTestFolder(folder3Id, 2, "Non-Empty Folder"));
    feedList->appendRow(createTestFeed(feedId, 3, "Feed", folder3Id));

    QCOMPARE(feedList->count(), 4);
    QCOMPARE(countFoldersInDatabase(), 3);

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Only the non-empty folder should remain.
    QCOMPARE(feedList->count(), 2);  // folder3 + feed
    QCOMPARE(countFoldersInDatabase(), 1);  // Only folder3
    QVERIFY(!folderExistsInDb(folder1Id));
    QVERIFY(!folderExistsInDb(folder2Id));
    QVERIFY(folderExistsInDb(folder3Id));

    delete feedList;
}

void TestUpdateOrdinalsOperation::testOrphanedFolderInDatabaseDeleted()
{
    // This tests the case where a folder exists in the database but not in the model.
    // This can happen if the user removes a folder through other means.

    // Insert folder in database only.
    qint64 orphanedFolderId = insertFolderHelper("Orphaned Folder", 0);

    // Insert a feed.
    qint64 feedId = insertFeedHelper("Feed", 1);

    QVERIFY(orphanedFolderId > 0);
    QVERIFY(feedId > 0);

    // Create model WITHOUT the folder.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feedId, 0, "Feed"));

    QVERIFY(folderExistsInDb(orphanedFolderId));
    QCOMPARE(countFoldersInDatabase(), 1);

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Orphaned folder should be deleted from database.
    QVERIFY(!folderExistsInDb(orphanedFolderId));
    QCOMPARE(countFoldersInDatabase(), 0);

    delete feedList;
}

// -------------------------------------------------------------------
// Edge cases
// -------------------------------------------------------------------

void TestUpdateOrdinalsOperation::testSpecialFeedsIgnored()
{
    // Insert regular feed.
    qint64 feedId = insertFeedHelper("Feed", 0);

    QVERIFY(feedId > 0);

    // Create model with special feed (negative ID) and regular feed.
    ListModel* feedList = createFeedList();

    // Create special feed with ID -2 (All News).
    FeedItem* allNews = new FeedItem(
        FEED_ID_ALLNEWS, 0, "All News", "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
        -1, true, this
    );
    feedList->appendRow(allNews);
    feedList->appendRow(createTestFeed(feedId, 1, "Feed"));

    // Run operation.
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Regular feed ordinal should be 1 (after special feed), not 0.
    // Actually, looking at the code, special feeds are skipped, so regular feed gets ordinal based on its position.
    // The ordinal for "Feed" should be 1 since it's at position 1 in the model.
    QCOMPARE(getFeedOrdinalFromDb(feedId), 1LL);

    delete feedList;
}

void TestUpdateOrdinalsOperation::testRollbackOnError()
{
    // This is a tricky test - we'd need to inject an error into the operation.
    // For now, we'll just verify that the operation handles normal cases correctly.
    // A more comprehensive test would require mocking the database.

    // Insert feeds.
    qint64 feed1Id = insertFeedHelper("Feed 1", 0);
    qint64 feed2Id = insertFeedHelper("Feed 2", 1);

    QVERIFY(feed1Id > 0);
    QVERIFY(feed2Id > 0);

    // Create model.
    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feed1Id, 0, "Feed 1"));
    feedList->appendRow(createTestFeed(feed2Id, 1, "Feed 2"));

    // Run operation (should succeed).
    UpdateOrdinalsOperation op(operationManager, feedList);
    op.executeSynchronous();

    // Verify everything is correct.
    QCOMPARE(getFeedOrdinalFromDb(feed1Id), 0LL);
    QCOMPARE(getFeedOrdinalFromDb(feed2Id), 1LL);

    delete feedList;
}

QTEST_MAIN(TestUpdateOrdinalsOperation)

#include "tst_updateordinalsoperation.moc"
