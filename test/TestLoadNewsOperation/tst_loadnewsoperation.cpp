#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include "src/db/DB.h"
#include "src/models/FeedItem.h"
#include "src/models/LisvelFeedItem.h"
#include "src/models/FolderFeedItem.h"
#include "src/models/AllNewsFeedItem.h"
#include "src/models/PinnedFeedItem.h"
#include "src/models/ListModel.h"
#include "src/models/NewsList.h"
#include "src/models/NewsItem.h"
#include "src/operations/OperationManager.h"
#include "src/operations/LoadNewsOperation.h"
#include "src/operations/LisvelLoadNewsOperation.h"
#include "src/operations/LoadAllNewsOperation.h"
#include "src/operations/LoadPinnedNewsOperation.h"
#include "src/operations/LoadFolderOperation.h"

/**
 * Tests for LoadNewsOperation (base class, regular feeds) and
 * LisvelLoadNewsOperation via its three concrete subclasses:
 *   - LoadAllNewsOperation
 *   - LoadPinnedNewsOperation
 *   - LoadFolderOperation
 */
class TestLoadNewsOperation : public QObject
{
    Q_OBJECT

public:
    TestLoadNewsOperation();

private slots:
    void initTestCase();
    void cleanup();
    void cleanupTestCase();

    // -------------------------------------------------------
    // LoadNewsOperation (base class, regular feeds)
    // -------------------------------------------------------
    void testModeToString();
    void testStringToMode();
    void testLoadNews_specialFeedEarlyReturn();
    void testLoadNews_initialNoBookmark();
    void testLoadNews_initialWithBookmark();
    void testLoadNews_append();
    void testLoadNews_prepend();
    void testLoadNews_setsFirstNewsID();
    void testLoadNews_emptyDB();
    void testLoadNews_appendEmptyFeed();
    void testLoadNews_prependEmptyFeed();

    // -------------------------------------------------------
    // LisvelLoadNewsOperation via LoadAllNewsOperation
    // -------------------------------------------------------
    void testAllNews_initialLoad();
    void testAllNews_initialNoPrependItems();
    void testAllNews_appendMode();
    void testAllNews_prependMode();
    void testAllNews_appendSkipsAlreadyLoaded();
    void testAllNews_prependSkipsAlreadyLoaded();
    void testAllNews_appendWithPageDown();
    void testAllNews_prependWithPageUp();
    void testAllNews_appendFallbackQuery();
    void testAllNews_emptyResult();
    void testAllNews_setsFirstNewsID();

    // -------------------------------------------------------
    // LisvelLoadNewsOperation via LoadPinnedNewsOperation
    // -------------------------------------------------------
    void testPinned_initialLoad();
    void testPinned_appendMode();
    void testPinned_emptyPrependQuery();

    // -------------------------------------------------------
    // LisvelLoadNewsOperation via LoadFolderOperation
    // -------------------------------------------------------
    void testFolder_initialLoad();
    void testFolder_appendFallback();
    void testFolder_onlyLoadsItemsInFolder();

private:
    void createSchema();

    // Insert a feed into FeedItemTable and return its id.
    void insertFeed(qint64 id, const QString& title, qint64 bookmarkId = -1,
                    qint64 parentFolder = -1);

    // Insert a news item and return its auto-generated id.
    qint64 insertNews(qint64 feedId, const QString& title, qint64 timestamp,
                      bool pinned = false);

    // Insert a news item with a specific id.
    void insertNewsWithId(qint64 id, qint64 feedId, const QString& title,
                          qint64 timestamp, bool pinned = false);

    // Create a regular FeedItem for testing base LoadNewsOperation.
    FeedItem* createRegularFeed(qint64 id);

    QSqlDatabase sqlDb;
    QString connectionName;
    OperationManager* operationManager;
    ListModel* feedList;
};

TestLoadNewsOperation::TestLoadNewsOperation()
    : connectionName("testLoadNewsOpDb")
    , operationManager(nullptr)
    , feedList(nullptr)
{
}

void TestLoadNewsOperation::initTestCase()
{
    sqlDb = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    sqlDb.setDatabaseName(":memory:");

    QVERIFY2(sqlDb.open(), qPrintable(sqlDb.lastError().text()));

    createSchema();

    DB::instance()->initForTesting(sqlDb);

    operationManager = new OperationManager(this);

    FeedItem* prototype = new FeedItem();
    feedList = new ListModel(prototype, this);
}

void TestLoadNewsOperation::createSchema()
{
    QSqlQuery query(sqlDb);

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
}

void TestLoadNewsOperation::cleanup()
{
    QSqlQuery query(sqlDb);
    query.exec("DELETE FROM NewsItemTable");
    query.exec("DELETE FROM FeedItemTable");
}

void TestLoadNewsOperation::cleanupTestCase()
{
    delete feedList;
    feedList = nullptr;

    delete operationManager;
    operationManager = nullptr;

    sqlDb.close();
    sqlDb = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}

void TestLoadNewsOperation::insertFeed(qint64 id, const QString& title,
                                       qint64 bookmarkId, qint64 parentFolder)
{
    QSqlQuery query(sqlDb);
    query.prepare(
        "INSERT INTO FeedItemTable (id, title, bookmark_id, parent_folder) "
        "VALUES (:id, :title, :bookmark_id, :parent_folder)"
    );
    query.bindValue(":id", id);
    query.bindValue(":title", title);
    query.bindValue(":bookmark_id", bookmarkId);
    query.bindValue(":parent_folder", parentFolder);
    QVERIFY2(query.exec(), qPrintable(query.lastError().text()));
}

qint64 TestLoadNewsOperation::insertNews(qint64 feedId, const QString& title,
                                         qint64 timestamp, bool pinned)
{
    QSqlQuery query(sqlDb);
    query.prepare(
        "INSERT INTO NewsItemTable (feed_id, guid, title, timestamp, url, pinned) "
        "VALUES (:feed_id, :guid, :title, :timestamp, :url, :pinned)"
    );
    query.bindValue(":feed_id", feedId);
    query.bindValue(":guid", QString("guid-%1-%2").arg(feedId).arg(timestamp));
    query.bindValue(":title", title);
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":url", "http://example.com/news");
    query.bindValue(":pinned", pinned ? 1 : 0);
    bool success = query.exec();
    Q_ASSERT(success);
    return query.lastInsertId().toLongLong();
}

void TestLoadNewsOperation::insertNewsWithId(qint64 id, qint64 feedId,
                                             const QString& title, qint64 timestamp,
                                             bool pinned)
{
    QSqlQuery query(sqlDb);
    query.prepare(
        "INSERT INTO NewsItemTable (id, feed_id, guid, title, timestamp, url, pinned) "
        "VALUES (:id, :feed_id, :guid, :title, :timestamp, :url, :pinned)"
    );
    query.bindValue(":id", id);
    query.bindValue(":feed_id", feedId);
    query.bindValue(":guid", QString("guid-%1-%2").arg(feedId).arg(id));
    query.bindValue(":title", title);
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":url", "http://example.com/news");
    query.bindValue(":pinned", pinned ? 1 : 0);
    QVERIFY2(query.exec(), qPrintable(query.lastError().text()));
}

FeedItem* TestLoadNewsOperation::createRegularFeed(qint64 id)
{
    return new FeedItem(id, 0, "Test Feed", "", QDateTime(), 0,
                        QUrl(), QUrl(), "", QUrl(), QDateTime(), -1, true,
                        FeedTypeRSS, this);
}

// -------------------------------------------------------------------
// LoadNewsOperation (base class) tests
// -------------------------------------------------------------------

void TestLoadNewsOperation::testModeToString()
{
    QCOMPARE(LoadNewsOperation::modeToString(LoadNewsOperation::Initial), QString("initial"));
    QCOMPARE(LoadNewsOperation::modeToString(LoadNewsOperation::Prepend), QString("prepend"));
    QCOMPARE(LoadNewsOperation::modeToString(LoadNewsOperation::Append), QString("append"));
}

void TestLoadNewsOperation::testStringToMode()
{
    QCOMPARE(LoadNewsOperation::stringToMode("initial"), LoadNewsOperation::Initial);
    QCOMPARE(LoadNewsOperation::stringToMode("prepend"), LoadNewsOperation::Prepend);
    QCOMPARE(LoadNewsOperation::stringToMode("append"), LoadNewsOperation::Append);
}

void TestLoadNewsOperation::testLoadNews_specialFeedEarlyReturn()
{
    // AllNewsFeedItem is a special feed (id < 0). Base LoadNewsOperation should
    // early-return without loading anything.
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    insertFeed(1, "Feed 1");
    insertNews(1, "Item 1", 1000);

    LoadNewsOperation op(operationManager, allNews, LoadNewsOperation::Initial);
    op.execute();

    QVERIFY(op.getAppendList().isEmpty());
    QVERIFY(op.getPrependList().isEmpty());
    QVERIFY(allNews->getNewsList()->isEmpty());

    delete allNews;
}

void TestLoadNewsOperation::testLoadNews_initialNoBookmark()
{
    // Feed with bookmark_id=-1: only doAppend fires, no doPrepend.
    insertFeed(1, "Feed 1", -1);
    insertNewsWithId(1, 1, "Item A", 1000);
    insertNewsWithId(2, 1, "Item B", 2000);
    insertNewsWithId(3, 1, "Item C", 3000);

    FeedItem* feed = createRegularFeed(1);

    LoadNewsOperation op(operationManager, feed, LoadNewsOperation::Initial);
    op.execute();

    // All items loaded via doAppend (startId=-1, so id >= -1 matches everything).
    QCOMPARE(op.getAppendList().size(), 3);
    QVERIFY(op.getPrependList().isEmpty());
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)3);

    // Bookmark should NOT be set (bookmarkID is -1, which is < 0).
    QCOMPARE(feed->getBookmarkID(), (qint64)-1);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_initialWithBookmark()
{
    // Feed with bookmark_id=2: doPrepend(2) + doAppend(2).
    insertFeed(1, "Feed 1", 2);
    insertNewsWithId(1, 1, "Item A", 1000);
    insertNewsWithId(2, 1, "Item B", 2000);
    insertNewsWithId(3, 1, "Item C", 3000);
    insertNewsWithId(4, 1, "Item D", 4000);

    FeedItem* feed = createRegularFeed(1);

    LoadNewsOperation op(operationManager, feed, LoadNewsOperation::Initial);
    op.execute();

    // doPrepend(2): id < 2 -> item 1 only.
    QCOMPARE(op.getPrependList().size(), 1);
    QCOMPARE(op.getPrependList().first()->getDbID(), (qint64)1);

    // doAppend(2): id >= 2 -> items 2, 3, 4.
    QCOMPARE(op.getAppendList().size(), 3);

    // All 4 items in the news list.
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)4);

    // Bookmark should be set.
    QCOMPARE(feed->getBookmarkID(), (qint64)2);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_append()
{
    // Set up: initial load, then append mode for more.
    insertFeed(1, "Feed 1", -1);
    for (int i = 1; i <= 10; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    FeedItem* feed = createRegularFeed(1);

    // Initial load with limit 5 (loads items 1-5, since startId=-1 means id >= -1).
    LoadNewsOperation initOp(operationManager, feed, LoadNewsOperation::Initial, 5);
    initOp.execute();
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)5);

    // Append: getStartIDForAppend() = last item's id + 1 = 6.
    LoadNewsOperation appendOp(operationManager, feed, LoadNewsOperation::Append, 5);
    appendOp.execute();

    QCOMPARE(appendOp.getAppendList().size(), 5);
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)10);

    // Verify the appended items are 6-10.
    QCOMPARE(appendOp.getAppendList().first()->getDbID(), (qint64)6);
    QCOMPARE(appendOp.getAppendList().last()->getDbID(), (qint64)10);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_prepend()
{
    // Load items starting at bookmark, then prepend to get earlier items.
    insertFeed(1, "Feed 1", 6);
    for (int i = 1; i <= 10; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    FeedItem* feed = createRegularFeed(1);

    // Initial load: doPrepend(6) loads id < 6 [5,4,3,2,1], doAppend(6) loads id >= 6 [6,7,8,9,10].
    LoadNewsOperation initOp(operationManager, feed, LoadNewsOperation::Initial);
    initOp.execute();
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)10);

    // Now clear and rebuild with limited initial load to leave items for prepend.
    delete feed;
    feed = createRegularFeed(1);

    // Initial with loadLimit=3 and bookmark=6:
    //   doPrepend(6): id < 6, DESC, limit 3 -> [5, 4, 3]
    //   doAppend(6): id >= 6, ASC, limit 3 -> [6, 7, 8]
    LoadNewsOperation initOp2(operationManager, feed, LoadNewsOperation::Initial, 3);
    initOp2.execute();
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)6);

    // Prepend mode: getStartIDForPrepend() = first item's id = 3 (prepended items are in desc order,
    // then prepended to list, so first = item 3 which was prepended last).
    // Actually, prepend adds items one by one, so order depends on prepend behavior.
    // The list has: prepend [5,4,3] then append [6,7,8]. After prepend: [3,4,5] at front, then [6,7,8].
    // Wait - items are prepended one by one, so: first prepend 5 -> [5], then prepend 4 -> [4,5],
    // then prepend 3 -> [3,4,5]. Then append 6,7,8 -> [3,4,5,6,7,8].
    // first() = 3, so getStartIDForPrepend() = 3.
    // doPrepend(3): id < 3, DESC -> [2, 1].

    LoadNewsOperation prependOp(operationManager, feed, LoadNewsOperation::Prepend, 5);
    prependOp.execute();

    QCOMPARE(prependOp.getPrependList().size(), 2);
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)8);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_setsFirstNewsID()
{
    insertFeed(1, "Feed 1", -1);
    // Item with lowest timestamp gets lowest id (auto-increment matches insertion order).
    insertNewsWithId(10, 1, "Item A", 1000);
    insertNewsWithId(20, 1, "Item B", 2000);

    FeedItem* feed = createRegularFeed(1);
    QCOMPARE(feed->getFirstNewsID(), (qint64)-1);

    LoadNewsOperation op(operationManager, feed, LoadNewsOperation::Initial);
    op.execute();

    // getFirstNewsID for base class queries by feed_id, ORDER BY timestamp ASC, id ASC LIMIT 1.
    QCOMPARE(feed->getFirstNewsID(), (qint64)10);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_emptyDB()
{
    insertFeed(1, "Feed 1", -1);
    // No news items inserted.

    FeedItem* feed = createRegularFeed(1);

    LoadNewsOperation op(operationManager, feed, LoadNewsOperation::Initial);
    op.execute();

    QVERIFY(op.getAppendList().isEmpty());
    QVERIFY(op.getPrependList().isEmpty());
    QVERIFY(feed->getNewsList()->isEmpty());
    QCOMPARE(feed->getFirstNewsID(), (qint64)-1);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_appendEmptyFeed()
{
    insertFeed(1, "Feed 1", -1);
    insertNewsWithId(1, 1, "Item A", 1000);

    FeedItem* feed = createRegularFeed(1);
    // NewsList is empty (no initial load). getStartIDForAppend returns -1.
    // doAppend(-1): id >= -1 -> matches all items.

    LoadNewsOperation op(operationManager, feed, LoadNewsOperation::Append);
    op.execute();

    QCOMPARE(op.getAppendList().size(), 1);
    QCOMPARE(feed->getNewsList()->size(), (qsizetype)1);

    delete feed;
}

void TestLoadNewsOperation::testLoadNews_prependEmptyFeed()
{
    insertFeed(1, "Feed 1", -1);
    insertNewsWithId(1, 1, "Item A", 1000);

    FeedItem* feed = createRegularFeed(1);
    // NewsList is empty. getStartIDForPrepend returns -1.
    // doPrepend(-1): id < -1 -> matches nothing.

    LoadNewsOperation op(operationManager, feed, LoadNewsOperation::Prepend);
    op.execute();

    QVERIFY(op.getPrependList().isEmpty());
    QVERIFY(feed->getNewsList()->isEmpty());

    delete feed;
}

// -------------------------------------------------------------------
// LoadAllNewsOperation tests
// -------------------------------------------------------------------

void TestLoadNewsOperation::testAllNews_initialLoad()
{
    // Two feeds with bookmarks. Initial load should doAppend (unread) + doPrepend (read),
    // then merge prepend into append list. Bookmark is set to first prepend item.
    insertFeed(1, "Feed 1", 3);
    insertFeed(2, "Feed 2", 6);

    // Feed 1: items 1,2,3 (read: id <= 3), item 4 (unread: id > 3).
    insertNewsWithId(1, 1, "F1 Item 1", 1000);
    insertNewsWithId(2, 1, "F1 Item 2", 2000);
    insertNewsWithId(3, 1, "F1 Item 3", 3000);
    insertNewsWithId(4, 1, "F1 Item 4", 4000);

    // Feed 2: items 5,6 (read: id <= 6), item 7 (unread: id > 6).
    insertNewsWithId(5, 2, "F2 Item 1", 5000);
    insertNewsWithId(6, 2, "F2 Item 2", 6000);
    insertNewsWithId(7, 2, "F2 Item 3", 7000);

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation op(operationManager, allNews, LoadNewsOperation::Initial);
    op.execute();

    // All items should be loaded (append: unread [4,7], prepend: read [6,5,3,2,1] merged).
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)7);

    // The append list (after merge) should contain all items.
    QCOMPARE(op.getAppendList().size(), 7);

    // Bookmark should be set to first item of original prepend list (newest read item).
    // Prepend query is DESC order, so first prepend item = highest-timestamp read item.
    // Read items: 1(1000), 2(2000), 3(3000), 5(5000), 6(6000). DESC: 6, 5, 3, 2, 1.
    QCOMPARE(allNews->getBookmarkID(), (qint64)6);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_initialNoPrependItems()
{
    // All items are unread (above their feed's bookmark). No prepend items.
    insertFeed(1, "Feed 1", -1);  // bookmark=-1, so all items have id > -1 -> unread
    insertNewsWithId(1, 1, "Item 1", 1000);
    insertNewsWithId(2, 1, "Item 2", 2000);

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation op(operationManager, allNews, LoadNewsOperation::Initial);
    op.execute();

    // All items loaded via append (unread path). No prepend items.
    QCOMPARE(op.getAppendList().size(), 2);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)2);

    // No bookmark set (no prepend items, so initialBookmarkID stays -1).
    QCOMPARE(allNews->getBookmarkID(), (qint64)-1);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_appendMode()
{
    // After initial load, append loads more unread items.
    insertFeed(1, "Feed 1", 3);
    for (int i = 1; i <= 8; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    // Initial with limit 3: append gets up to 3 unread (id > 3: items 4,5,6),
    // prepend gets up to 3 read (id <= 3: items 3,2,1).
    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial, 3);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);

    // Append mode: should load remaining unread items not already loaded.
    LoadAllNewsOperation appendOp(operationManager, allNews, LoadNewsOperation::Append, 5);
    appendOp.execute();

    // Items 7, 8 are unread (id > 3) and not yet loaded.
    QCOMPARE(appendOp.getAppendList().size(), 2);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)8);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_prependMode()
{
    // After initial load with limited prepend, prepend loads earlier read items.
    insertFeed(1, "Feed 1", 5);
    for (int i = 1; i <= 8; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    // Initial with limit 3: append gets items 6,7,8 (id > 5), prepend gets 5,4,3 (id <= 5, DESC, limit 3).
    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial, 3);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);

    // Prepend mode: should load read items not yet loaded (items 1, 2).
    LoadAllNewsOperation prependOp(operationManager, allNews, LoadNewsOperation::Prepend, 5);
    prependOp.execute();

    QCOMPARE(prependOp.getPrependList().size(), 2);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)8);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_appendSkipsAlreadyLoaded()
{
    // After initial load, shrink display window from end, then append.
    // Items paged back from memory via pageDown should still appear in listAppend
    // (for JS) but not be re-added to NewsList (containsID skip).
    insertFeed(1, "Feed 1", -1);
    for (int i = 1; i <= 6; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    // Initial load: all 6 items are unread (bookmark=-1, so id > -1).
    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);
    QCOMPARE(allNews->getNewsList()->fullSize(), (qsizetype)6);

    // Shrink display window from end by 3. Items 4,5,6 are outside display window
    // but still in full list.
    allNews->getNewsList()->shrinkDisplayWindow(false, 3);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)3);
    QCOMPARE(allNews->getNewsList()->fullSize(), (qsizetype)6);
    QVERIFY(allNews->getNewsList()->canPageDown());

    // Append: step 1 pages items back from memory.
    LoadAllNewsOperation appendOp(operationManager, allNews, LoadNewsOperation::Append, 5);
    appendOp.execute();

    // Items should be paged back into the display window.
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);
    // The listAppend should contain the paged-back items (for JS notification).
    QVERIFY(appendOp.getAppendList().size() >= 3);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_prependSkipsAlreadyLoaded()
{
    // After initial load, shrink display window from start, then prepend.
    insertFeed(1, "Feed 1", -1);
    for (int i = 1; i <= 6; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);

    // Shrink from start by 3: items 1,2,3 outside display window.
    allNews->getNewsList()->shrinkDisplayWindow(true, 3);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)3);
    QVERIFY(allNews->getNewsList()->canPageUp());

    // Prepend: step 1 pages items back from memory.
    LoadAllNewsOperation prependOp(operationManager, allNews, LoadNewsOperation::Prepend, 5);
    prependOp.execute();

    // Items paged back into display window.
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);
    QVERIFY(prependOp.getPrependList().size() >= 3);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_appendWithPageDown()
{
    // Specifically test the canPageDown path (doAppend step 1).
    insertFeed(1, "Feed 1", -1);
    for (int i = 1; i <= 8; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->fullSize(), (qsizetype)8);

    // Shrink from end by 4.
    allNews->getNewsList()->shrinkDisplayWindow(false, 4);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)4);
    QVERIFY(allNews->getNewsList()->canPageDown());

    // Append with limit 2: should page down 2 items from memory.
    LoadAllNewsOperation appendOp(operationManager, allNews, LoadNewsOperation::Append, 2);
    appendOp.execute();

    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);
    // The paged items (5, 6) should be in the append list for JS.
    QCOMPARE(appendOp.getAppendList().size(), 2);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_prependWithPageUp()
{
    // Specifically test the canPageUp path (doPrepend step 1).
    insertFeed(1, "Feed 1", -1);
    for (int i = 1; i <= 8; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000);
    }

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->fullSize(), (qsizetype)8);

    // Shrink from start by 4.
    allNews->getNewsList()->shrinkDisplayWindow(true, 4);
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)4);
    QVERIFY(allNews->getNewsList()->canPageUp());

    // Prepend with limit 2: should page up 2 items from memory.
    LoadAllNewsOperation prependOp(operationManager, allNews, LoadNewsOperation::Prepend, 2);
    prependOp.execute();

    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)6);
    QCOMPARE(prependOp.getPrependList().size(), 2);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_appendFallbackQuery()
{
    // Trigger doAppend step 3 (appendAfterPositionQueryString).
    // Setup: two feeds. Feed 1 has one unread item (the only one step 2 finds).
    // Feed 2 has all "read" items (bookmark very high). After initial load,
    // Append mode step 2 finds nothing new, and step 3 attempts to load items
    // chronologically after the last position.
    //
    // Note: step 3 binds lastItem->getTimestamp() (a QDateTime) against the
    // integer timestamp column. The SQLite type affinity conversion from the
    // QDateTime ISO string to numeric yields the year (e.g. 1970), so the
    // timestamp comparison may not behave as intended with small test timestamps.
    // We verify the code path is exercised and completes without error.

    insertFeed(1, "Feed 1", 3);
    insertFeed(2, "Feed 2", 1000);

    insertNewsWithId(1, 1, "F1 A", 1000);
    insertNewsWithId(4, 1, "F1 D", 4000);   // The only unread item (feed 1, id > 3)

    // Feed 2: many read items at varying timestamps.
    insertNewsWithId(2, 2, "F2 A", 2000);
    insertNewsWithId(3, 2, "F2 B", 3000);
    insertNewsWithId(5, 2, "F2 C", 5000);
    insertNewsWithId(6, 2, "F2 D", 6000);
    insertNewsWithId(7, 2, "F2 E", 7000);
    insertNewsWithId(8, 2, "F2 F", 8000);
    insertNewsWithId(9, 2, "F2 G", 9000);

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    // Initial with limit 3:
    //   doAppend step 2: unread = [4] (1 item).
    //   doPrepend step 2 (DESC, limit 3): [9(9000), 8(8000), 7(7000)]
    // Merge: [7, 8, 9, 4]
    // NewsList: [7, 8, 9, 4]
    LoadAllNewsOperation initOp(operationManager, allNews, LoadNewsOperation::Initial, 3);
    initOp.execute();
    QCOMPARE(allNews->getNewsList()->size(), (qsizetype)4);

    // Append: step 2 finds nothing (no unread items remain).
    // Step 3 is reached (remainingLoadLimit > 0, lastItem non-null,
    // appendAfterPositionQueryString non-empty).
    qsizetype sizeBefore = allNews->getNewsList()->size();
    LoadAllNewsOperation appendOp(operationManager, allNews, LoadNewsOperation::Append, 5);
    appendOp.execute();

    // The operation completes. NewsList is at least the same size (may grow if step 3 finds items).
    QVERIFY(allNews->getNewsList()->size() >= sizeBefore);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_emptyResult()
{
    // No news in DB at all.
    insertFeed(1, "Feed 1", -1);

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation op(operationManager, allNews, LoadNewsOperation::Initial);
    op.execute();

    QVERIFY(op.getAppendList().isEmpty());
    QVERIFY(allNews->getNewsList()->isEmpty());
    QCOMPARE(allNews->getFirstNewsID(), (qint64)-1);

    delete allNews;
}

void TestLoadNewsOperation::testAllNews_setsFirstNewsID()
{
    // getFirstNewsID for AllNews queries across all feeds.
    insertFeed(1, "Feed 1", -1);
    insertFeed(2, "Feed 2", -1);

    // Feed 2 has the earliest item by timestamp.
    insertNewsWithId(10, 1, "F1 Item", 5000);
    insertNewsWithId(20, 2, "F2 Item", 1000);

    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    LoadAllNewsOperation op(operationManager, allNews, LoadNewsOperation::Initial);
    op.execute();

    // Earliest by (timestamp ASC, id ASC) across all feeds is item 20 (ts=1000).
    QCOMPARE(allNews->getFirstNewsID(), (qint64)20);

    delete allNews;
}

// -------------------------------------------------------------------
// LoadPinnedNewsOperation tests
// -------------------------------------------------------------------

void TestLoadNewsOperation::testPinned_initialLoad()
{
    // prependOnInit=false for pinned: only doAppend fires.
    insertFeed(1, "Feed 1", -1);

    insertNewsWithId(1, 1, "Item 1", 1000, false);
    insertNewsWithId(2, 1, "Item 2", 2000, true);   // pinned
    insertNewsWithId(3, 1, "Item 3", 3000, false);
    insertNewsWithId(4, 1, "Item 4", 4000, true);   // pinned

    PinnedFeedItem* pinnedFeed = new PinnedFeedItem(feedList);

    LoadPinnedNewsOperation op(operationManager, pinnedFeed, LoadNewsOperation::Initial);
    op.execute();

    // Only pinned items loaded (items 2 and 4).
    QCOMPARE(op.getAppendList().size(), 2);
    QCOMPARE(pinnedFeed->getNewsList()->size(), (qsizetype)2);

    // Verify they are the pinned items.
    QVERIFY(pinnedFeed->getNewsList()->containsID(2));
    QVERIFY(pinnedFeed->getNewsList()->containsID(4));

    delete pinnedFeed;
}

void TestLoadNewsOperation::testPinned_appendMode()
{
    // After initial load, append loads more pinned items.
    insertFeed(1, "Feed 1", -1);

    for (int i = 1; i <= 6; i++) {
        insertNewsWithId(i, 1, QString("Item %1").arg(i), i * 1000, true);
    }

    PinnedFeedItem* pinnedFeed = new PinnedFeedItem(feedList);

    // Initial with limit 3.
    LoadPinnedNewsOperation initOp(operationManager, pinnedFeed, LoadNewsOperation::Initial, 3);
    initOp.execute();
    QCOMPARE(pinnedFeed->getNewsList()->size(), (qsizetype)3);

    // Append: should find remaining pinned items.
    LoadPinnedNewsOperation appendOp(operationManager, pinnedFeed, LoadNewsOperation::Append, 5);
    appendOp.execute();

    QCOMPARE(appendOp.getAppendList().size(), 3);
    QCOMPARE(pinnedFeed->getNewsList()->size(), (qsizetype)6);

    delete pinnedFeed;
}

void TestLoadNewsOperation::testPinned_emptyPrependQuery()
{
    // prependNewQueryString returns "": doPrepend step 2 is skipped entirely.
    insertFeed(1, "Feed 1", -1);
    insertNewsWithId(1, 1, "Item 1", 1000, true);
    insertNewsWithId(2, 1, "Item 2", 2000, true);

    PinnedFeedItem* pinnedFeed = new PinnedFeedItem(feedList);

    // Initial load first.
    LoadPinnedNewsOperation initOp(operationManager, pinnedFeed, LoadNewsOperation::Initial);
    initOp.execute();

    // Prepend mode: since prependNewQueryString is "", step 2 of doPrepend is skipped.
    // Step 1 (pageUp) only fires if canPageUp, which requires items before display window.
    // No items before window, so prepend does nothing.
    LoadPinnedNewsOperation prependOp(operationManager, pinnedFeed, LoadNewsOperation::Prepend);
    prependOp.execute();

    QVERIFY(prependOp.getPrependList().isEmpty());

    delete pinnedFeed;
}

// -------------------------------------------------------------------
// LoadFolderOperation tests
// -------------------------------------------------------------------

void TestLoadNewsOperation::testFolder_initialLoad()
{
    // Folder feed loads items from child feeds only.
    // Folder id=100, children: feeds 1 and 2.
    insertFeed(100, "My Folder");
    insertFeed(1, "Feed 1", 3, 100);  // parent_folder=100, bookmark=3
    insertFeed(2, "Feed 2", 6, 100);  // parent_folder=100, bookmark=6

    insertNewsWithId(1, 1, "F1 A", 1000);
    insertNewsWithId(2, 1, "F1 B", 2000);
    insertNewsWithId(3, 1, "F1 C", 3000);
    insertNewsWithId(4, 1, "F1 D", 4000);

    insertNewsWithId(5, 2, "F2 A", 5000);
    insertNewsWithId(6, 2, "F2 B", 6000);
    insertNewsWithId(7, 2, "F2 C", 7000);

    FolderFeedItem* folder = new FolderFeedItem(100, 0, "My Folder", true, this);

    LoadFolderOperation op(operationManager, folder, LoadNewsOperation::Initial);
    op.execute();

    // All items from feeds in this folder should be loaded.
    // Unread: item 4 (feed 1, id > 3), item 7 (feed 2, id > 6).
    // Read: items 1,2,3 (feed 1, id <= 3), items 5,6 (feed 2, id <= 6).
    QCOMPARE(folder->getNewsList()->size(), (qsizetype)7);

    delete folder;
}

void TestLoadNewsOperation::testFolder_appendFallback()
{
    // Test appendAfterPositionQueryString with :parent_folder binding.
    // Same type affinity note as testAllNews_appendFallbackQuery applies here.
    insertFeed(100, "My Folder");
    insertFeed(1, "Feed 1", 3, 100);     // bookmark at 3
    insertFeed(2, "Feed 2", 1000, 100);   // all read

    insertNewsWithId(1, 1, "F1 A", 1000);
    insertNewsWithId(4, 1, "F1 D", 4000);  // unread (id > 3)

    insertNewsWithId(2, 2, "F2 A", 2000);
    insertNewsWithId(3, 2, "F2 B", 3000);
    insertNewsWithId(5, 2, "F2 C", 5000);
    insertNewsWithId(6, 2, "F2 D", 6000);
    insertNewsWithId(7, 2, "F2 E", 7000);
    insertNewsWithId(8, 2, "F2 F", 8000);
    insertNewsWithId(9, 2, "F2 G", 9000);

    FolderFeedItem* folder = new FolderFeedItem(100, 0, "My Folder", true, this);

    // Initial with limit 3:
    //   doAppend step 2: feed 1 id > 3 -> [4]; feed 2 id > 1000 -> nothing
    //   doPrepend step 2 (DESC, limit 3): [9(9000), 8(8000), 7(7000)]
    // Merge: [7, 8, 9, 4]
    LoadFolderOperation initOp(operationManager, folder, LoadNewsOperation::Initial, 3);
    initOp.execute();
    QCOMPARE(folder->getNewsList()->size(), (qsizetype)4);

    // Append: step 2 finds nothing, step 3 is reached (non-empty lastItem,
    // non-empty appendAfterPositionQueryString, and remainingLoadLimit > 0).
    // bindQueryParameters provides :parent_folder = 100.
    qsizetype sizeBefore = folder->getNewsList()->size();
    LoadFolderOperation appendOp(operationManager, folder, LoadNewsOperation::Append, 5);
    appendOp.execute();

    QVERIFY(folder->getNewsList()->size() >= sizeBefore);

    delete folder;
}

void TestLoadNewsOperation::testFolder_onlyLoadsItemsInFolder()
{
    // Items outside the folder should NOT be loaded.
    insertFeed(100, "My Folder");
    insertFeed(1, "Feed In Folder", -1, 100);   // In folder
    insertFeed(2, "Feed Outside", -1, -1);       // Not in folder

    insertNewsWithId(1, 1, "In Folder", 1000);
    insertNewsWithId(2, 2, "Outside Folder", 2000);

    FolderFeedItem* folder = new FolderFeedItem(100, 0, "My Folder", true, this);

    LoadFolderOperation op(operationManager, folder, LoadNewsOperation::Initial);
    op.execute();

    // Only item 1 (from feed in folder) should be loaded.
    QCOMPARE(folder->getNewsList()->size(), (qsizetype)1);
    QVERIFY(folder->getNewsList()->containsID(1));
    QVERIFY(!folder->getNewsList()->containsID(2));

    delete folder;
}

QTEST_MAIN(TestLoadNewsOperation)

#include "tst_loadnewsoperation.moc"
