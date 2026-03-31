#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QUuid>
#include <QVariant>
#include <QMap>

#include "src/db/DB.h"
#include "src/db/DBSettingsKey.h"
#include "src/models/FeedItem.h"
#include "src/models/FolderFeedItem.h"
#include "src/models/AllNewsFeedItem.h"
#include "src/models/PinnedFeedItem.h"
#include "src/models/ListModel.h"
#include "src/models/NewsItem.h"
#include "src/operations/OperationManager.h"
#include "src/operations/SetDBSettingOperation.h"
#include "src/operations/GetAllDBSettingsOperation.h"
#include "src/operations/UpdateTitleOperation.h"
#include "src/operations/UpdateFeedURLOperation.h"
#include "src/operations/SetFolderOpenOperation.h"
#include "src/operations/SetPinOperation.h"
#include "src/operations/InsertFolderOperation.h"
#include "src/operations/ExpireNewsOperation.h"
#include "src/operations/ReloadNewsOperation.h"

/**
 * Tests for various DB operations:
 * - SetDBSettingOperation / GetAllDBSettingsOperation
 * - UpdateTitleOperation
 * - UpdateFeedURLOperation
 * - SetFolderOpenOperation
 * - SetPinOperation
 * - InsertFolderOperation
 * - ExpireNewsOperation
 * - ReloadNewsOperation
 */
class TestFeedOperations : public QObject
{
    Q_OBJECT

public:
    TestFeedOperations();

private slots:
    void initTestCase();
    void cleanup();
    void cleanupTestCase();

    // SetDBSettingOperation
    void testSetDBSetting_insertsValue();
    void testSetDBSetting_replacesValue();

    // GetAllDBSettingsOperation
    void testGetAllDBSettings_empty();
    void testGetAllDBSettings_loadsValues();

    // UpdateTitleOperation
    void testUpdateTitle_updatesDB();
    void testUpdateTitle_skipsAllNewsFeed();

    // UpdateFeedURLOperation
    void testUpdateFeedURL_updatesDB();
    void testUpdateFeedURL_updatesFeedObject();

    // SetFolderOpenOperation
    void testSetFolderOpen_persistsTrue();
    void testSetFolderOpen_persistsFalse();
    void testSetFolderOpen_skipsSpecialFeed();

    // SetPinOperation
    void testSetPin_pins();
    void testSetPin_unpins();
    void testSetPin_updatesUnreadCount();

    // InsertFolderOperation
    void testInsertFolder_createsInDB();
    void testInsertFolder_reparentsChildren();
    void testInsertFolder_addsToModel();
    void testInsertFolder_invalidIndex();

    // ExpireNewsOperation
    void testExpireNews_deletesOldRead();
    void testExpireNews_keepsUnread();
    void testExpireNews_keepsPinned();
    void testExpireNews_savesNewest();
    void testExpireNews_skipsSpecialFeeds();

    // ReloadNewsOperation
    void testReloadNews_loadsItems();
    void testReloadNews_emptyList();
    void testReloadNews_preservesOrder();
    void testReloadNews_nonExistentIds();

private:
    void createSchema();
    qint64 insertFeedHelper(const QString& title, int ordinal, qint64 parentFolder = -1, qint64 bookmarkId = -1);
    qint64 insertNewsHelper(qint64 feedId, const QString& title, qint64 timestamp = 0, bool pinned = false);
    FeedItem* createTestFeed(qint64 id, int ordinal, const QString& title, qint64 parentFolder = -1);
    ListModel* createFeedList();

    QSqlDatabase db;
    QString connectionName;
    OperationManager* operationManager;
};

TestFeedOperations::TestFeedOperations()
    : connectionName("testFeedOperationsDb")
    , operationManager(nullptr)
{
}

void TestFeedOperations::initTestCase()
{
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");

    QVERIFY2(db.open(), qPrintable(db.lastError().text()));

    createSchema();

    DB::instance()->initForTesting(db);

    operationManager = new OperationManager(this);
}

void TestFeedOperations::createSchema()
{
    QSqlQuery query(db);

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
        "  parent_folder INTEGER DEFAULT -1,"
        "  etag TEXT DEFAULT '',"
        "  last_modified TEXT DEFAULT '',"
        "  user_url TEXT DEFAULT '',"
        "  feed_type INTEGER DEFAULT 0"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

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
        "  pinned INTEGER DEFAULT 0,"
        "  media_image_url TEXT DEFAULT ''"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));

    success = query.exec(
        "CREATE TABLE IF NOT EXISTS DBSettings ("
        "  id INTEGER PRIMARY KEY,"
        "  value TEXT"
        ")"
    );
    QVERIFY2(success, qPrintable(query.lastError().text()));
}

void TestFeedOperations::cleanup()
{
    QSqlQuery query(db);
    query.exec("DROP TABLE IF EXISTS NewsItemTable");
    query.exec("DROP TABLE IF EXISTS FeedItemTable");
    query.exec("DROP TABLE IF EXISTS DBSettings");

    createSchema();
}

void TestFeedOperations::cleanupTestCase()
{
    delete operationManager;
    operationManager = nullptr;

    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}

qint64 TestFeedOperations::insertFeedHelper(const QString& title, int ordinal, qint64 parentFolder, qint64 bookmarkId)
{
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO FeedItemTable (title, ordinal, parent_folder, is_folder, bookmark_id, subtitle, url, siteURL) "
        "VALUES (:title, :ordinal, :parent_folder, 0, :bookmark_id, '', '', '')"
    );
    query.bindValue(":title", title);
    query.bindValue(":ordinal", ordinal);
    query.bindValue(":parent_folder", parentFolder);
    query.bindValue(":bookmark_id", bookmarkId);

    if (!query.exec()) {
        qWarning() << "insertFeedHelper failed:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toLongLong();
}

qint64 TestFeedOperations::insertNewsHelper(qint64 feedId, const QString& title, qint64 timestamp, bool pinned)
{
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO NewsItemTable (feed_id, guid, title, timestamp, pinned) "
        "VALUES (:feed_id, :guid, :title, :timestamp, :pinned)"
    );
    query.bindValue(":feed_id", feedId);
    query.bindValue(":guid", QUuid::createUuid().toString());
    query.bindValue(":title", title);
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":pinned", (int)pinned);

    if (!query.exec()) {
        qWarning() << "insertNewsHelper failed:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toLongLong();
}

FeedItem* TestFeedOperations::createTestFeed(qint64 id, int ordinal, const QString& title, qint64 parentFolder)
{
    return new FeedItem(
        id, ordinal, title, "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
        parentFolder, true, FeedTypeRSS, this
    );
}

ListModel* TestFeedOperations::createFeedList()
{
    FeedItem* prototype = new FeedItem();
    return new ListModel(prototype, this);
}

// ---------------------------------------------------------------------------
// SetDBSettingOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testSetDBSetting_insertsValue()
{
    SetDBSettingOperation op(operationManager, CACHE_LENGTH, TWO_WEEKS);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT value FROM DBSettings WHERE id = :id");
    query.bindValue(":id", (int)CACHE_LENGTH);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toString(), TWO_WEEKS);
}

void TestFeedOperations::testSetDBSetting_replacesValue()
{
    // Insert initial value.
    SetDBSettingOperation op1(operationManager, CACHE_LENGTH, TWO_WEEKS);
    op1.execute();

    // Replace with new value.
    SetDBSettingOperation op2(operationManager, CACHE_LENGTH, SIX_MONTH);
    op2.execute();

    QSqlQuery query(db);
    query.prepare("SELECT value FROM DBSettings WHERE id = :id");
    query.bindValue(":id", (int)CACHE_LENGTH);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toString(), SIX_MONTH);

    // Verify there's only one row, not two.
    QSqlQuery countQuery(db);
    countQuery.exec("SELECT COUNT(*) FROM DBSettings");
    QVERIFY(countQuery.next());
    QCOMPARE(countQuery.value(0).toInt(), 1);
}

// ---------------------------------------------------------------------------
// GetAllDBSettingsOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testGetAllDBSettings_empty()
{
    QMap<DBSettingsKey, QString> settings;
    GetAllDBSettingsOperation op(operationManager, &settings);
    op.execute();

    QVERIFY(settings.isEmpty());
}

void TestFeedOperations::testGetAllDBSettings_loadsValues()
{
    // Pre-insert rows directly.
    QSqlQuery query(db);
    query.exec("INSERT INTO DBSettings (id, value) VALUES (0, '2WEEK')");

    QMap<DBSettingsKey, QString> settings;
    GetAllDBSettingsOperation op(operationManager, &settings);
    op.execute();

    QCOMPARE(settings.size(), 1);
    QCOMPARE(settings.value(CACHE_LENGTH), TWO_WEEKS);
}

// ---------------------------------------------------------------------------
// UpdateTitleOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testUpdateTitle_updatesDB()
{
    qint64 feedId = insertFeedHelper("Old Title", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Old Title");
    feed->setTitle("New Title");

    UpdateTitleOperation op(operationManager, feed);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT title FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toString(), QString("New Title"));

    delete feed;
}

void TestFeedOperations::testUpdateTitle_skipsAllNewsFeed()
{
    // Insert a dummy row so we can verify nothing changed.
    qint64 feedId = insertFeedHelper("Original", 0);
    QVERIFY(feedId > 0);

    // AllNewsFeedItem requires a feedList for its constructor.
    ListModel* feedList = createFeedList();
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    UpdateTitleOperation op(operationManager, allNews);
    op.execute();

    // Verify the database row was not touched.
    QSqlQuery query(db);
    query.prepare("SELECT title FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toString(), QString("Original"));

    delete feedList;
}

// ---------------------------------------------------------------------------
// UpdateFeedURLOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testUpdateFeedURL_updatesDB()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");
    QUrl newURL("https://example.com/new-feed.xml");

    UpdateFeedURLOperation op(operationManager, feed, newURL);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT url FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toString(), newURL.toString());

    delete feed;
}

void TestFeedOperations::testUpdateFeedURL_updatesFeedObject()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");
    QUrl newURL("https://example.com/updated.xml");

    UpdateFeedURLOperation op(operationManager, feed, newURL);
    op.execute();

    // The operation should also update the in-memory feed object.
    QCOMPARE(feed->getURL(), newURL);

    delete feed;
}

// ---------------------------------------------------------------------------
// SetFolderOpenOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testSetFolderOpen_persistsTrue()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");
    feed->setFolderOpen(true);

    SetFolderOpenOperation op(operationManager, feed);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT folder_open FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toBool(), true);

    delete feed;
}

void TestFeedOperations::testSetFolderOpen_persistsFalse()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");
    feed->setFolderOpen(false);

    SetFolderOpenOperation op(operationManager, feed);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT folder_open FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toBool(), false);

    delete feed;
}

void TestFeedOperations::testSetFolderOpen_skipsSpecialFeed()
{
    // Insert a row to detect if anything got modified.
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    // Set the initial folder_open to true.
    QSqlQuery setup(db);
    setup.prepare("UPDATE FeedItemTable SET folder_open = 1 WHERE id = :id");
    setup.bindValue(":id", feedId);
    QVERIFY(setup.exec());

    // Create a special feed (negative ID). It should be skipped.
    FeedItem* specialFeed = new FeedItem(
        FEED_ID_ALLNEWS, 0, "All News", "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
        -1, false, FeedTypeRSS, this
    );

    SetFolderOpenOperation op(operationManager, specialFeed);
    op.execute();

    // Verify the existing feed row was not changed.
    QSqlQuery query(db);
    query.prepare("SELECT folder_open FROM FeedItemTable WHERE id = :id");
    query.bindValue(":id", feedId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toBool(), true);

    delete specialFeed;
}

// ---------------------------------------------------------------------------
// SetPinOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testSetPin_pins()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    qint64 newsId = insertNewsHelper(feedId, "News", 1000, false);
    QVERIFY(newsId > 0);

    ListModel* feedList = createFeedList();
    PinnedFeedItem* pinned = new PinnedFeedItem(feedList);

    SetPinOperation op(operationManager, pinned, newsId, true);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT pinned FROM NewsItemTable WHERE id = :id");
    query.bindValue(":id", newsId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    delete feedList;
}

void TestFeedOperations::testSetPin_unpins()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    qint64 newsId = insertNewsHelper(feedId, "News", 1000, true);
    QVERIFY(newsId > 0);

    ListModel* feedList = createFeedList();
    PinnedFeedItem* pinned = new PinnedFeedItem(feedList);

    SetPinOperation op(operationManager, pinned, newsId, false);
    op.execute();

    QSqlQuery query(db);
    query.prepare("SELECT pinned FROM NewsItemTable WHERE id = :id");
    query.bindValue(":id", newsId);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toInt(), 0);

    delete feedList;
}

void TestFeedOperations::testSetPin_updatesUnreadCount()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    insertNewsHelper(feedId, "Already Pinned", 1000, true);
    qint64 newsId = insertNewsHelper(feedId, "To Pin", 2000, false);
    QVERIFY(newsId > 0);

    ListModel* feedList = createFeedList();
    PinnedFeedItem* pinned = new PinnedFeedItem(feedList);

    // Initially the pinned feed doesn't know the count.
    QCOMPARE(pinned->getUnreadCount(), (quint32)0);

    SetPinOperation op(operationManager, pinned, newsId, true);
    op.execute();

    // After pinning, the unread count should reflect 2 pinned items.
    QCOMPARE(pinned->getUnreadCount(), (quint32)2);

    delete feedList;
}

// ---------------------------------------------------------------------------
// InsertFolderOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testInsertFolder_createsInDB()
{
    qint64 feed1Id = insertFeedHelper("Feed 1", 0);
    qint64 feed2Id = insertFeedHelper("Feed 2", 1);
    QVERIFY(feed1Id > 0);
    QVERIFY(feed2Id > 0);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feed1Id, 0, "Feed 1"));
    feedList->appendRow(createTestFeed(feed2Id, 1, "Feed 2"));

    InsertFolderOperation op(operationManager, 0, "My Folder", feedList);
    op.execute();

    // Verify the folder was inserted.
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM FeedItemTable WHERE is_folder = 1");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    // Verify the folder has the correct name.
    QSqlQuery nameQuery(db);
    nameQuery.exec("SELECT title FROM FeedItemTable WHERE is_folder = 1");
    QVERIFY(nameQuery.next());
    QCOMPARE(nameQuery.value(0).toString(), QString("My Folder"));

    delete feedList;
}

void TestFeedOperations::testInsertFolder_reparentsChildren()
{
    qint64 feed1Id = insertFeedHelper("Feed 1", 0);
    qint64 feed2Id = insertFeedHelper("Feed 2", 1);
    qint64 feed3Id = insertFeedHelper("Feed 3", 2);
    QVERIFY(feed1Id > 0);
    QVERIFY(feed2Id > 0);
    QVERIFY(feed3Id > 0);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feed1Id, 0, "Feed 1"));
    feedList->appendRow(createTestFeed(feed2Id, 1, "Feed 2"));
    feedList->appendRow(createTestFeed(feed3Id, 2, "Feed 3"));

    // Insert folder at index 0 - should reparent Feed 1 and Feed 2.
    InsertFolderOperation op(operationManager, 0, "Folder", feedList);
    op.execute();

    // Verify children got reparented in database.
    QSqlQuery query(db);
    query.prepare("SELECT parent_folder FROM FeedItemTable WHERE id = :id");

    query.bindValue(":id", feed1Id);
    QVERIFY(query.exec() && query.next());
    qint64 folderDbId = query.value(0).toLongLong();
    QVERIFY(folderDbId > 0);

    query.bindValue(":id", feed2Id);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toLongLong(), folderDbId);

    // Feed 3 should NOT be reparented.
    query.bindValue(":id", feed3Id);
    QVERIFY(query.exec() && query.next());
    QCOMPARE(query.value(0).toLongLong(), -1LL);

    delete feedList;
}

void TestFeedOperations::testInsertFolder_addsToModel()
{
    qint64 feed1Id = insertFeedHelper("Feed 1", 0);
    qint64 feed2Id = insertFeedHelper("Feed 2", 1);
    QVERIFY(feed1Id > 0);
    QVERIFY(feed2Id > 0);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feed1Id, 0, "Feed 1"));
    feedList->appendRow(createTestFeed(feed2Id, 1, "Feed 2"));

    QCOMPARE(feedList->count(), 2);

    InsertFolderOperation op(operationManager, 0, "Folder", feedList);
    op.execute();

    // Model should now have 3 items (folder + 2 feeds).
    QCOMPARE(feedList->count(), 3);

    // Folder should be at index 0.
    FeedItem* first = qobject_cast<FeedItem*>(feedList->row(0));
    QVERIFY(first != nullptr);
    QVERIFY(first->isFolder());
    QCOMPARE(first->getTitle(), QString("Folder"));

    delete feedList;
}

void TestFeedOperations::testInsertFolder_invalidIndex()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feedId, 0, "Feed"));

    int initialCount = feedList->count();

    // Negative index - should bail out without crash.
    InsertFolderOperation op1(operationManager, -1, "Bad Folder", feedList);
    op1.execute();
    QCOMPARE(feedList->count(), initialCount);

    // Out-of-bounds index - should also bail out.
    InsertFolderOperation op2(operationManager, 100, "Bad Folder", feedList);
    op2.execute();
    QCOMPARE(feedList->count(), initialCount);

    delete feedList;
}

// ---------------------------------------------------------------------------
// ExpireNewsOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testExpireNews_deletesOldRead()
{
    // Create a feed with bookmark_id set high so items below it are "read".
    qint64 feedId = insertFeedHelper("Feed", 0, -1, 1000);
    QVERIFY(feedId > 0);

    // Old read item (below bookmark, old timestamp).
    insertNewsHelper(feedId, "Old Read", 100, false);
    // Recent read item (below bookmark, recent timestamp).
    qint64 recentId = insertNewsHelper(feedId, "Recent Read", QDateTime::currentDateTime().toMSecsSinceEpoch(), false);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feedId, 0, "Feed"));

    // Expire items older than 1 day ago, save 0 newest.
    QDateTime oneDayAgo = QDateTime::currentDateTime().addDays(-1);
    ExpireNewsOperation op(operationManager, feedList, oneDayAgo, 0);
    op.execute();

    // Old item should be deleted, recent should remain.
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemTable");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    // The surviving item should be the recent one.
    QSqlQuery idQuery(db);
    idQuery.exec("SELECT id FROM NewsItemTable");
    QVERIFY(idQuery.next());
    QCOMPARE(idQuery.value(0).toLongLong(), recentId);

    delete feedList;
}

void TestFeedOperations::testExpireNews_keepsUnread()
{
    // Bookmark at 0 means all items with positive IDs are "unread"
    // (the delete condition is `id < bookmark_id`, so id < 0 is never true).
    qint64 feedId = insertFeedHelper("Feed", 0, -1, 0);
    QVERIFY(feedId > 0);

    // This item has a positive auto-increment ID, so it's above bookmark 0 - "unread".
    insertNewsHelper(feedId, "Unread Old", 100, false);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feedId, 0, "Feed"));

    QDateTime oneDayAgo = QDateTime::currentDateTime().addDays(-1);
    ExpireNewsOperation op(operationManager, feedList, oneDayAgo, 0);
    op.execute();

    // Unread item should still exist.
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemTable");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    delete feedList;
}

void TestFeedOperations::testExpireNews_keepsPinned()
{
    qint64 feedId = insertFeedHelper("Feed", 0, -1, 1000);
    QVERIFY(feedId > 0);

    // Old pinned item - should survive despite being old and read.
    insertNewsHelper(feedId, "Old Pinned", 100, true);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feedId, 0, "Feed"));

    QDateTime oneDayAgo = QDateTime::currentDateTime().addDays(-1);
    ExpireNewsOperation op(operationManager, feedList, oneDayAgo, 0);
    op.execute();

    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemTable");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    delete feedList;
}

void TestFeedOperations::testExpireNews_savesNewest()
{
    qint64 feedId = insertFeedHelper("Feed", 0, -1, 1000);
    QVERIFY(feedId > 0);

    // Insert 3 old read items with different timestamps.
    insertNewsHelper(feedId, "Oldest", 100, false);
    insertNewsHelper(feedId, "Middle", 200, false);
    qint64 newestId = insertNewsHelper(feedId, "Newest", 300, false);

    ListModel* feedList = createFeedList();
    feedList->appendRow(createTestFeed(feedId, 0, "Feed"));

    // saveLast=1 should preserve the newest item.
    QDateTime oneDayAgo = QDateTime::currentDateTime().addDays(-1);
    ExpireNewsOperation op(operationManager, feedList, oneDayAgo, 1);
    op.execute();

    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemTable");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 1);

    QSqlQuery idQuery(db);
    idQuery.exec("SELECT id FROM NewsItemTable");
    QVERIFY(idQuery.next());
    QCOMPARE(idQuery.value(0).toLongLong(), newestId);

    delete feedList;
}

void TestFeedOperations::testExpireNews_skipsSpecialFeeds()
{
    qint64 feedId = insertFeedHelper("Feed", 0, -1, 1000);
    QVERIFY(feedId > 0);

    insertNewsHelper(feedId, "Old Item", 100, false);

    ListModel* feedList = createFeedList();

    // Add a special feed (All News) at the front of the list.
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);
    feedList->appendRow(allNews);
    feedList->appendRow(createTestFeed(feedId, 1, "Feed"));

    QDateTime oneDayAgo = QDateTime::currentDateTime().addDays(-1);
    ExpireNewsOperation op(operationManager, feedList, oneDayAgo, 0);
    op.execute();

    // The old item for the regular feed should still be deleted normally.
    // The key is that the special feed was skipped without error.
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM NewsItemTable");
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 0);

    delete feedList;
}

// ---------------------------------------------------------------------------
// ReloadNewsOperation
// ---------------------------------------------------------------------------

void TestFeedOperations::testReloadNews_loadsItems()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    qint64 news1Id = insertNewsHelper(feedId, "News 1", 1000, false);
    qint64 news2Id = insertNewsHelper(feedId, "News 2", 2000, false);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");

    QList<qint64> ids = {news1Id, news2Id};
    ReloadNewsOperation op(operationManager, feed, ids);
    op.execute();

    QList<NewsItem*>& items = op.getReloadedItems();
    QCOMPARE(items.size(), 2);
    QCOMPARE(items[0]->getTitle(), QString("News 1"));
    QCOMPARE(items[1]->getTitle(), QString("News 2"));

    qDeleteAll(items);
    delete feed;
}

void TestFeedOperations::testReloadNews_emptyList()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");

    QList<qint64> ids;
    ReloadNewsOperation op(operationManager, feed, ids);
    op.execute();

    QVERIFY(op.getReloadedItems().isEmpty());

    delete feed;
}

void TestFeedOperations::testReloadNews_preservesOrder()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    // Insert with timestamps out of ID order.
    qint64 id1 = insertNewsHelper(feedId, "Later", 3000, false);
    qint64 id2 = insertNewsHelper(feedId, "Earlier", 1000, false);
    qint64 id3 = insertNewsHelper(feedId, "Middle", 2000, false);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");

    QList<qint64> ids = {id1, id2, id3};
    ReloadNewsOperation op(operationManager, feed, ids);
    op.execute();

    QList<NewsItem*>& items = op.getReloadedItems();
    QCOMPARE(items.size(), 3);

    // Should be ordered by timestamp ASC, then id ASC.
    QCOMPARE(items[0]->getTitle(), QString("Earlier"));    // timestamp 1000
    QCOMPARE(items[1]->getTitle(), QString("Middle"));     // timestamp 2000
    QCOMPARE(items[2]->getTitle(), QString("Later"));      // timestamp 3000

    qDeleteAll(items);
    delete feed;
}

void TestFeedOperations::testReloadNews_nonExistentIds()
{
    qint64 feedId = insertFeedHelper("Feed", 0);
    QVERIFY(feedId > 0);

    FeedItem* feed = createTestFeed(feedId, 0, "Feed");

    QList<qint64> ids = {99999, 88888, 77777};
    ReloadNewsOperation op(operationManager, feed, ids);
    op.execute();

    QVERIFY(op.getReloadedItems().isEmpty());

    delete feed;
}

QTEST_MAIN(TestFeedOperations)

#include "tst_feedoperations.moc"
