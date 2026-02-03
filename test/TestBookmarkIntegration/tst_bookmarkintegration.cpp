#include <QTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDateTime>
#include <QDebug>

#include "../../src/models/AllNewsFeedItem.h"
#include "../../src/models/FeedItem.h"
#include "../../src/models/NewsList.h"
#include "../../src/models/NewsItem.h"
#include "../../src/models/ListModel.h"

/**
 * Integration test for bookmark functionality in Fang.
 *
 * This test validates the complete bookmark flow:
 * 1. Loading news items in timestamp order (simulating "All News" view)
 * 2. Bookmark advancement during scroll down
 * 3. Force-bookmark backward functionality
 * 4. Display window trimming and paging
 * 5. Bookmark position preservation when items are outside display window
 *
 * This test uses an in-memory database for test data but directly
 * populates the NewsList to simulate what LoadAllNewsOperation does.
 */
class TestBookmarkIntegration : public QObject
{
    Q_OBJECT

public:
    TestBookmarkIntegration();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    // Basic bookmark tests
    void testBookmarkAdvancesOnScrollDown();
    void testBookmarkDoesNotRegressOnScrollUp();

    // Force bookmark tests
    void testForceBookmarkBackward();
    void testForceBookmarkThenScrollDown();

    // Display window tests
    void testDisplayWindowTrimming();
    void testPageUpThroughTrimmedItems();
    void testFullNewsItemForID_OutsideWindow();

    // CRITICAL: The bug scenario we're fixing
    void testScrollUpForceBookmarkScrollDown();

    // Additional edge cases
    void testBookmarkPositionPreservedAfterTrim();
    void testCanBookmarkUsesPositionWhenOutsideWindow();

    // NEW: Tests to replicate exact bug scenario
    void testPrependThenForceBookmarkThenScrollDown();
    void testExactLogScenario();
    void testBookmarkNotOverwrittenByAutoAdvance();
    void testIndexComparisonAfterPrepend();

    // NEW: More focused tests for the exact bug
    void testRaceConditionForceBookmarkThenAutoBookmark();
    void testAutoBookmarkOnOlderItemAfterScrollUp();

    // BUG TEST: SetBookmarkOperation uses indexOf which only searches display window
    void testBugSetBookmarkOperationIndexOfDisplayWindow();

    // CRITICAL: Test prepend ordering
    void testPrependMaintainsChronologicalOrder();
    void testPrependWithMultipleFeedsOrdering();
    void testPrependWithNonCorrelatingIDsAndTimestamps();

    // EXACT BUG REPRODUCTION from user logs
    void testExactBugScenario_ScrollUpForceBookmarkScrollDown();
    void testForceBookmarkItemOutsideDisplayWindow();

    // NEW: Test multiple force-bookmarks while scrolling up
    void testMultipleForceBookmarksWhileScrollingUp();
    void testVerifyPrependOrderInRealScenario();

    // BUG REPRODUCTION: Non-correlating IDs and timestamps
    void testBookmarkIterationWithNonCorrelatingIDs();

    // Paging tests - verify items outside display window can be paged back
    void testPageDownAfterScrollUp();
    void testPageUpAfterScrollDown();
    void testPagedItemsAreInCorrectOrder();

    // WebServer/JavaScript integration tests
    // These test the data format that would be sent to JavaScript
    void testPrependListReversalForJS();
    void testAppendListOrderForJS();
    void testMixedPrependAppendOrdering();

private:
    NewsItem* createNewsItem(qint64 id, const QDateTime& timestamp, const QString& title = "");
    void populateNewsList(int startId, int count, const QDateTime& baseTime);

    QSqlDatabase db;
    QString connectionName;
    ListModel* feedList;
    AllNewsFeedItem* allNewsFeed;
    QDateTime baseTime;
};

TestBookmarkIntegration::TestBookmarkIntegration()
    : connectionName("testdb_integration"),
      feedList(nullptr),
      allNewsFeed(nullptr),
      baseTime(QDate(2024, 1, 1), QTime(12, 0, 0))
{
}

void TestBookmarkIntegration::initTestCase()
{
    // Create in-memory DB for any queries we might need
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");
    QVERIFY2(db.open(), qPrintable(db.lastError().text()));
}

void TestBookmarkIntegration::init()
{
    // Create feed list model
    feedList = new ListModel(new FeedItem, this);

    // Create All News feed
    allNewsFeed = new AllNewsFeedItem(feedList);
}

void TestBookmarkIntegration::cleanup()
{
    delete allNewsFeed;
    allNewsFeed = nullptr;

    delete feedList;
    feedList = nullptr;
}

void TestBookmarkIntegration::cleanupTestCase()
{
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

NewsItem* TestBookmarkIntegration::createNewsItem(qint64 id, const QDateTime& timestamp, const QString& title)
{
    QString newsTitle = title.isEmpty() ? QString("News Item %1").arg(id) : title;

    return new NewsItem(
        allNewsFeed,
        id,              // dbId
        1,               // feedId (doesn't matter for All News)
        newsTitle,
        "Author",
        "Summary",
        "Content",
        timestamp,
        QUrl(QString("http://example.com/%1").arg(id)),
        false            // pinned
    );
}

void TestBookmarkIntegration::populateNewsList(int startId, int count, const QDateTime& baseTime)
{
    // Populate in timestamp order (ORDER BY timestamp ASC, id ASC)
    for (int i = 0; i < count; i++) {
        qint64 id = startId + i;
        QDateTime timestamp = baseTime.addSecs(i * 60);  // 1 minute apart
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }
}

// ============================================================================
// TEST CASES
// ============================================================================

void TestBookmarkIntegration::testBookmarkAdvancesOnScrollDown()
{
    // Setup: 30 news items
    populateNewsList(100, 30, baseTime);

    QCOMPARE(allNewsFeed->getNewsList()->size(), 30);

    // Set initial bookmark
    allNewsFeed->setBookmark(100);
    QCOMPARE(allNewsFeed->getBookmarkID(), 100LL);

    // Should be able to advance forward
    QVERIFY2(allNewsFeed->canBookmark(101, false), "Should advance from 100 to 101");
    QVERIFY2(allNewsFeed->canBookmark(110, false), "Should advance from 100 to 110");
    QVERIFY2(allNewsFeed->canBookmark(129, false), "Should advance from 100 to 129");

    // Set bookmark forward
    allNewsFeed->setBookmark(115);
    QCOMPARE(allNewsFeed->getBookmarkID(), 115LL);

    // Now can advance past 115
    QVERIFY2(allNewsFeed->canBookmark(116, false), "Should advance from 115 to 116");
    QVERIFY2(allNewsFeed->canBookmark(120, false), "Should advance from 115 to 120");
}

void TestBookmarkIntegration::testBookmarkDoesNotRegressOnScrollUp()
{
    // Setup
    populateNewsList(100, 30, baseTime);

    // Set bookmark to item 115
    allNewsFeed->setBookmark(115);

    // Should NOT be able to go backward without allowBackward
    QVERIFY2(!allNewsFeed->canBookmark(114, false), "Should NOT regress from 115 to 114");
    QVERIFY2(!allNewsFeed->canBookmark(100, false), "Should NOT regress from 115 to 100");
    QVERIFY2(!allNewsFeed->canBookmark(110, false), "Should NOT regress from 115 to 110");

    // Bookmark should not have changed
    QCOMPARE(allNewsFeed->getBookmarkID(), 115LL);
}

void TestBookmarkIntegration::testForceBookmarkBackward()
{
    // Setup
    populateNewsList(100, 30, baseTime);

    // Set bookmark to item 120
    allNewsFeed->setBookmark(120);
    QCOMPARE(allNewsFeed->getBookmarkID(), 120LL);

    // With allowBackward=true, should be able to go backward
    QVERIFY2(allNewsFeed->canBookmark(110, true), "Should allow backward with allowBackward=true");
    QVERIFY2(allNewsFeed->canBookmark(100, true), "Should allow backward to first item");

    // Actually set it backward
    allNewsFeed->setBookmark(105);
    QCOMPARE(allNewsFeed->getBookmarkID(), 105LL);

    // Position should be captured
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());
    QCOMPARE(allNewsFeed->getBookmarkPosition().id(), 105LL);
}

void TestBookmarkIntegration::testForceBookmarkThenScrollDown()
{
    // Setup: 50 items
    populateNewsList(100, 50, baseTime);

    // Start with bookmark at 140
    allNewsFeed->setBookmark(140);

    // Force bookmark backward to 110
    QVERIFY(allNewsFeed->canBookmark(110, true));
    allNewsFeed->setBookmark(110);
    QCOMPARE(allNewsFeed->getBookmarkID(), 110LL);

    // Now, items AFTER 110 should be allowed
    QVERIFY2(allNewsFeed->canBookmark(111, false), "111 > 110 should be allowed");
    QVERIFY2(allNewsFeed->canBookmark(120, false), "120 > 110 should be allowed");
    QVERIFY2(allNewsFeed->canBookmark(149, false), "149 > 110 should be allowed");

    // Items AT or BEFORE 110 should be rejected
    QVERIFY2(!allNewsFeed->canBookmark(110, false), "Same ID should be rejected");
    QVERIFY2(!allNewsFeed->canBookmark(109, false), "109 < 110 should be rejected");
    QVERIFY2(!allNewsFeed->canBookmark(100, false), "100 < 110 should be rejected");
}

void TestBookmarkIntegration::testDisplayWindowTrimming()
{
    // Setup: 60 items
    populateNewsList(100, 60, baseTime);

    QCOMPARE(allNewsFeed->getNewsList()->size(), 60);
    QCOMPARE(allNewsFeed->getNewsList()->fullSize(), 60);

    // Trim 20 from start (simulating scroll down)
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 20);

    // Display window should be smaller
    QCOMPARE(allNewsFeed->getNewsList()->size(), 40);

    // Full size should be unchanged (items in memory)
    QCOMPARE(allNewsFeed->getNewsList()->fullSize(), 60);

    // First visible item should now be ID 120 (100 + 20)
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 120LL);

    // Items 100-119 are outside display window but in full list
    QVERIFY(allNewsFeed->getNewsList()->newsItemForID(100) == nullptr);
    QVERIFY(allNewsFeed->getNewsList()->fullNewsItemForID(100) != nullptr);
}

void TestBookmarkIntegration::testPageUpThroughTrimmedItems()
{
    // Setup
    populateNewsList(100, 60, baseTime);

    // Trim 30 from start
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 30);
    QCOMPARE(allNewsFeed->getNewsList()->size(), 30);
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 130LL);

    // Can page up?
    QVERIFY(allNewsFeed->getNewsList()->canPageUp());

    // Page up 10 items
    qsizetype paged = allNewsFeed->getNewsList()->pageUp(10);
    QCOMPARE(paged, 10);
    QCOMPARE(allNewsFeed->getNewsList()->size(), 40);
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 120LL);

    // Page up remaining 20
    paged = allNewsFeed->getNewsList()->pageUp(20);
    QCOMPARE(paged, 20);
    QCOMPARE(allNewsFeed->getNewsList()->size(), 60);
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 100LL);

    // Can't page up anymore
    QVERIFY(!allNewsFeed->getNewsList()->canPageUp());
}

void TestBookmarkIntegration::testFullNewsItemForID_OutsideWindow()
{
    // Setup
    populateNewsList(100, 50, baseTime);

    // Trim 25 from start
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 25);

    // Items 100-124 are outside window
    for (qint64 id = 100; id < 125; id++) {
        QVERIFY2(allNewsFeed->getNewsList()->newsItemForID(id) == nullptr,
                 qPrintable(QString("ID %1 should NOT be in display window").arg(id)));
        QVERIFY2(allNewsFeed->getNewsList()->fullNewsItemForID(id) != nullptr,
                 qPrintable(QString("ID %1 SHOULD be in full list").arg(id)));
    }

    // Items 125-149 are in window
    for (qint64 id = 125; id < 150; id++) {
        QVERIFY2(allNewsFeed->getNewsList()->newsItemForID(id) != nullptr,
                 qPrintable(QString("ID %1 SHOULD be in display window").arg(id)));
        QVERIFY2(allNewsFeed->getNewsList()->fullNewsItemForID(id) != nullptr,
                 qPrintable(QString("ID %1 SHOULD be in full list").arg(id)));
    }
}

void TestBookmarkIntegration::testScrollUpForceBookmarkScrollDown()
{
    // CRITICAL TEST: This replicates the bug scenario
    //
    // 1. User starts with bookmark at a newer item (150)
    // 2. User scrolls up (older items become visible)
    // 3. User force-bookmarks an old item (say, 110)
    // 4. User scrolls down - older items get trimmed from display window
    // 5. The force-bookmarked item (110) is now OUTSIDE the display window
    // 6. As new items become visible, they should be ACCEPTED if they're newer than 110

    qDebug() << "\n=== testScrollUpForceBookmarkScrollDown ===";

    // Setup: 100 items (100-199)
    populateNewsList(100, 100, baseTime);
    qDebug() << "Created 100 items, IDs 100-199";

    // Step 1: Set initial bookmark to a newer item (like item 150)
    allNewsFeed->setBookmark(150);
    QCOMPARE(allNewsFeed->getBookmarkID(), 150LL);
    qDebug() << "Initial bookmark: 150";

    // Step 2: User scrolls up - in real app, older items would be prepended
    // For this test, all items are already loaded
    // Verify we can see old items
    QVERIFY(allNewsFeed->getNewsList()->newsItemForID(110) != nullptr);

    // Step 3: Force bookmark backward to item 110
    qDebug() << "Force-bookmarking to 110...";
    QVERIFY2(allNewsFeed->canBookmark(110, true), "Should be able to force-bookmark backward");
    allNewsFeed->setBookmark(110);
    QCOMPARE(allNewsFeed->getBookmarkID(), 110LL);

    // Verify position captured
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());
    QCOMPARE(allNewsFeed->getBookmarkPosition().id(), 110LL);
    QDateTime bookmarkTime = allNewsFeed->getBookmarkPosition().timestamp();
    qDebug() << "Bookmark position captured: ID=110, timestamp=" << bookmarkTime.toString(Qt::ISODate);

    // Step 4: User scrolls down - trim older items from display window
    // This simulates items 100-129 being scrolled off the top
    qDebug() << "Trimming 30 items from start (simulating scroll down)...";
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 30);

    qDebug() << "After trim: displaySize=" << allNewsFeed->getNewsList()->size()
             << "fullSize=" << allNewsFeed->getNewsList()->fullSize()
             << "first=" << allNewsFeed->getNewsList()->first()->getDbID();

    // Step 5: Verify the bookmark item (110) is now OUTSIDE the display window
    NewsItem* bookmarkInWindow = allNewsFeed->getNewsList()->newsItemForID(110);
    NewsItem* bookmarkInFull = allNewsFeed->getNewsList()->fullNewsItemForID(110);

    QVERIFY2(bookmarkInWindow == nullptr,
             "Bookmark item 110 should be OUTSIDE display window");
    QVERIFY2(bookmarkInFull != nullptr,
             "Bookmark item 110 should still be in full list");
    qDebug() << "Bookmark 110 is outside display window but in full list - CORRECT";

    // Step 6: KEY TEST - Items newer than the bookmark should be ACCEPTED
    // The first visible item is now 130 (130 > 110, so should be accepted)
    qint64 firstVisibleId = allNewsFeed->getNewsList()->first()->getDbID();
    qDebug() << "First visible item: " << firstVisibleId;

    // This is the critical assertion that was failing before the fix:
    // canBookmark should use the captured NewsPosition to compare, even though
    // the bookmark item (110) is outside the display window
    QVERIFY2(allNewsFeed->canBookmark(firstVisibleId, false),
             qPrintable(QString("Item %1 (> bookmark 110) should be ALLOWED").arg(firstVisibleId)));

    // Test several more items
    QVERIFY2(allNewsFeed->canBookmark(140, false), "Item 140 > 110 should be allowed");
    QVERIFY2(allNewsFeed->canBookmark(150, false), "Item 150 > 110 should be allowed");
    QVERIFY2(allNewsFeed->canBookmark(199, false), "Item 199 > 110 should be allowed");

    // Items older than 110 would be rejected if they were visible
    // (but they're not in the display window now, so canBookmark would return false
    // because they're not found)

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testBookmarkPositionPreservedAfterTrim()
{
    // Verify that bookmark position is preserved even when the item is trimmed

    populateNewsList(100, 50, baseTime);

    // Set bookmark
    allNewsFeed->setBookmark(115);
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());
    QCOMPARE(allNewsFeed->getBookmarkPosition().id(), 115LL);

    QDateTime originalTimestamp = allNewsFeed->getBookmarkPosition().timestamp();

    // Trim the bookmark item out of display window
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 20);

    // Bookmark ID should be unchanged
    QCOMPARE(allNewsFeed->getBookmarkID(), 115LL);

    // Position should still be valid (captured before trim)
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());
    QCOMPARE(allNewsFeed->getBookmarkPosition().id(), 115LL);
    QCOMPARE(allNewsFeed->getBookmarkPosition().timestamp(), originalTimestamp);
}

void TestBookmarkIntegration::testCanBookmarkUsesPositionWhenOutsideWindow()
{
    // Verify that canBookmark uses NewsPosition comparison when
    // the current bookmark is outside the display window

    populateNewsList(100, 60, baseTime);

    // Set bookmark to 110
    allNewsFeed->setBookmark(110);
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());

    // Trim so 110 is outside display window
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 15);

    // Verify 110 is outside window
    QVERIFY(allNewsFeed->getNewsList()->newsItemForID(110) == nullptr);

    // First visible is now 115
    qint64 firstVisible = allNewsFeed->getNewsList()->first()->getDbID();
    QCOMPARE(firstVisible, 115LL);

    // 115 > 110 by both timestamp and ID, so should be allowed
    // This tests that canBookmark falls back to NewsPosition comparison
    QVERIFY2(allNewsFeed->canBookmark(115, false),
             "Should use NewsPosition comparison when bookmark outside window");

    QVERIFY2(allNewsFeed->canBookmark(130, false),
             "Items after bookmark should be allowed");
}

void TestBookmarkIntegration::testPrependThenForceBookmarkThenScrollDown()
{
    // This replicates the EXACT user scenario:
    // 1. Start with some news items
    // 2. Prepend older items (simulating scroll up / load more)
    // 3. Force-bookmark one of the older items
    // 4. Scroll down (trim from start)
    // 5. Try to advance bookmark - should work

    qDebug() << "\n=== testPrependThenForceBookmarkThenScrollDown ===";

    // Step 1: Start with 30 items (IDs 12850-12879, newer items)
    QDateTime newerTime = baseTime.addDays(1);
    for (int i = 0; i < 30; i++) {
        qint64 id = 12850 + i;
        QDateTime timestamp = newerTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }
    qDebug() << "Initial load: 30 items, IDs 12850-12879";
    QCOMPARE(allNewsFeed->getNewsList()->size(), 30);

    // Set initial bookmark to newest item
    allNewsFeed->setBookmark(12870);
    qDebug() << "Initial bookmark: 12870";

    // Step 2: PREPEND older items (simulating scroll up to load more)
    // Prepend 30 older items (IDs 12820-12849)
    QDateTime olderTime = baseTime;  // Earlier than newerTime
    for (int i = 29; i >= 0; i--) {  // Prepend in reverse to maintain order
        qint64 id = 12820 + i;
        QDateTime timestamp = olderTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->prepend(item);
    }
    qDebug() << "After prepend: " << allNewsFeed->getNewsList()->fullSize() << " items total";
    qDebug() << "First item ID: " << allNewsFeed->getNewsList()->first()->getDbID();
    qDebug() << "Last item ID: " << allNewsFeed->getNewsList()->last()->getDbID();

    QCOMPARE(allNewsFeed->getNewsList()->fullSize(), 60);
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 12820LL);
    QCOMPARE(allNewsFeed->getNewsList()->last()->getDbID(), 12879LL);

    // Step 3: Force-bookmark an OLD item (12866 from original log)
    qDebug() << "Force-bookmarking to 12866...";
    QVERIFY2(allNewsFeed->canBookmark(12866, true), "Force-bookmark to 12866 should be allowed");
    allNewsFeed->setBookmark(12866);
    QCOMPARE(allNewsFeed->getBookmarkID(), 12866LL);
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());
    qDebug() << "Bookmark set to 12866, position valid";

    // Step 4: Scroll down - trim from start
    // In the real app, as user scrolls down, older items are trimmed
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 20);
    qDebug() << "After trim: displaySize=" << allNewsFeed->getNewsList()->size()
             << " first=" << allNewsFeed->getNewsList()->first()->getDbID();

    // Step 5: Now check if 12870 can be bookmarked (it's AFTER 12866)
    // This is the CRITICAL test - should be ALLOWED
    qint64 proposedId = 12870;
    qsizetype proposedIdx = allNewsFeed->getNewsList()->indexForItemID(proposedId);
    qsizetype currentIdx = allNewsFeed->getNewsList()->indexForItemID(12866);

    qDebug() << "Checking canBookmark:"
             << "proposed=" << proposedId << "idx=" << proposedIdx
             << "current=" << allNewsFeed->getBookmarkID() << "idx=" << currentIdx
             << "listSize=" << allNewsFeed->getNewsList()->size();

    bool canAdvance = allNewsFeed->canBookmark(12870, false);
    QVERIFY2(canAdvance,
             qPrintable(QString("Item 12870 (newer than bookmark 12866) should be ALLOWED, but was REJECTED")));

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testExactLogScenario()
{
    // Replicate the EXACT numbers from the user's log:
    // proposed= 12866 idx= 43 current= 12870 idx= 44 listSize= 60
    // REJECTED - index 43 <= 44

    qDebug() << "\n=== testExactLogScenario ===";

    // Create 60 items where:
    // - ID 12866 ends up at index 43
    // - ID 12870 ends up at index 44
    // For this, we need IDs starting from 12823 (12866 - 43 = 12823)

    QDateTime startTime = baseTime;
    for (int i = 0; i < 60; i++) {
        qint64 id = 12823 + i;  // IDs 12823-12882
        QDateTime timestamp = startTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }

    // Verify indices
    QCOMPARE(allNewsFeed->getNewsList()->indexForItemID(12866), 43);  // 12866 - 12823 = 43
    QCOMPARE(allNewsFeed->getNewsList()->indexForItemID(12870), 47);  // 12870 - 12823 = 47

    // Wait - that doesn't match the log. Let me recalculate...
    // If idx=43 for 12866 and idx=44 for 12870, that's a difference of 1
    // But 12870 - 12866 = 4, so there should be 4 indices between them
    // UNLESS the display window has been shifted!

    qDebug() << "Initial indices: 12866=" << allNewsFeed->getNewsList()->indexForItemID(12866)
             << " 12870=" << allNewsFeed->getNewsList()->indexForItemID(12870);

    // The log scenario can only happen if items between 12866 and 12870 were removed
    // OR if IDs don't directly correspond to positions (different timestamps)

    // Let me create a scenario where 12866 and 12870 are adjacent:
    allNewsFeed->getNewsList()->clear();

    // Create items with specific IDs where 12866 and 12870 are adjacent
    // due to items 12867, 12868, 12869 having earlier timestamps
    QList<QPair<qint64, QDateTime>> items;

    // First, add items with IDs before 12866 (timestamps in order)
    for (int i = 0; i < 43; i++) {
        items.append({12800 + i, startTime.addSecs(i * 60)});  // IDs 12800-12842
    }

    // Then ID 12866 at timestamp for index 43
    items.append({12866, startTime.addSecs(43 * 60)});

    // Then ID 12870 at timestamp for index 44
    items.append({12870, startTime.addSecs(44 * 60)});

    // Fill remaining items
    for (int i = 45; i < 60; i++) {
        items.append({12900 + i, startTime.addSecs(i * 60)});
    }

    for (const auto& item : items) {
        NewsItem* newsItem = createNewsItem(item.first, item.second);
        allNewsFeed->getNewsList()->append(newsItem);
    }

    QCOMPARE(allNewsFeed->getNewsList()->size(), 60);
    QCOMPARE(allNewsFeed->getNewsList()->indexForItemID(12866), 43);
    QCOMPARE(allNewsFeed->getNewsList()->indexForItemID(12870), 44);

    qDebug() << "Recreated scenario: 12866 at idx 43, 12870 at idx 44, size 60";

    // Set current bookmark to 12870
    allNewsFeed->setBookmark(12870);
    qDebug() << "Bookmark set to 12870 (the NEWER item)";

    // Now try to set bookmark to 12866 (the OLDER item) WITHOUT allowBackward
    bool allowed = allNewsFeed->canBookmark(12866, false);
    qDebug() << "canBookmark(12866, false) = " << allowed;

    // This SHOULD be rejected because 12866 is BEFORE 12870
    QVERIFY2(!allowed, "Going backward from 12870 to 12866 should be REJECTED");

    // Now the question is: WHY is the bookmark at 12870 when user thought they set it to 12866?
    // This test shows the log output is CORRECT behavior - the real bug is elsewhere

    qDebug() << "=== TEST PASSED (log behavior is correct) ===\n";
}

void TestBookmarkIntegration::testBookmarkNotOverwrittenByAutoAdvance()
{
    // Test that a force-bookmark is not overwritten by subsequent canBookmark checks
    // that return false

    qDebug() << "\n=== testBookmarkNotOverwrittenByAutoAdvance ===";

    populateNewsList(12800, 60, baseTime);

    // Set initial bookmark to 12850
    allNewsFeed->setBookmark(12850);
    qDebug() << "Initial bookmark: 12850";

    // Force-bookmark backward to 12830
    allNewsFeed->setBookmark(12830);
    QCOMPARE(allNewsFeed->getBookmarkID(), 12830LL);
    qDebug() << "Force-bookmarked to 12830";

    // Simulate what might happen during scrolling:
    // Multiple canBookmark calls that return false should NOT change the bookmark
    for (int i = 0; i < 10; i++) {
        qint64 olderId = 12820 + i;  // Items BEFORE the bookmark
        bool result = allNewsFeed->canBookmark(olderId, false);
        QVERIFY2(!result, qPrintable(QString("canBookmark(%1) should return false").arg(olderId)));
    }

    // Bookmark should still be 12830
    QCOMPARE(allNewsFeed->getBookmarkID(), 12830LL);
    qDebug() << "Bookmark still at 12830 after canBookmark checks";

    // Items AFTER bookmark should be allowed
    QVERIFY2(allNewsFeed->canBookmark(12831, false), "12831 > 12830 should be allowed");
    QVERIFY2(allNewsFeed->canBookmark(12850, false), "12850 > 12830 should be allowed");

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testIndexComparisonAfterPrepend()
{
    // Test that index comparison works correctly after prepending items
    // This checks if prepending causes index calculation issues

    qDebug() << "\n=== testIndexComparisonAfterPrepend ===";

    // Start with items 12850-12879 (30 items)
    QDateTime newerTime = baseTime.addDays(1);
    for (int i = 0; i < 30; i++) {
        qint64 id = 12850 + i;
        QDateTime timestamp = newerTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }

    qDebug() << "Initial: 30 items (12850-12879)";
    qDebug() << "Index of 12866: " << allNewsFeed->getNewsList()->indexForItemID(12866);
    qDebug() << "Index of 12870: " << allNewsFeed->getNewsList()->indexForItemID(12870);

    // Set bookmark to 12866
    allNewsFeed->setBookmark(12866);
    QCOMPARE(allNewsFeed->getBookmarkID(), 12866LL);

    // 12870 should be allowed (it's after 12866)
    QVERIFY2(allNewsFeed->canBookmark(12870, false),
             "Before prepend: 12870 > 12866 should be allowed");

    // Now PREPEND 30 older items (12820-12849)
    QDateTime olderTime = baseTime;
    for (int i = 29; i >= 0; i--) {
        qint64 id = 12820 + i;
        QDateTime timestamp = olderTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->prepend(item);
    }

    qDebug() << "After prepend: " << allNewsFeed->getNewsList()->size() << " items";
    qDebug() << "Index of 12866: " << allNewsFeed->getNewsList()->indexForItemID(12866);
    qDebug() << "Index of 12870: " << allNewsFeed->getNewsList()->indexForItemID(12870);
    qDebug() << "Index of 12820: " << allNewsFeed->getNewsList()->indexForItemID(12820);

    // Verify bookmark is still 12866
    QCOMPARE(allNewsFeed->getBookmarkID(), 12866LL);

    // CRITICAL: 12870 should STILL be allowed after prepend
    // The prepend shouldn't affect the relative ordering of 12866 and 12870
    bool canAdvance = allNewsFeed->canBookmark(12870, false);

    qsizetype idx12866 = allNewsFeed->getNewsList()->indexForItemID(12866);
    qsizetype idx12870 = allNewsFeed->getNewsList()->indexForItemID(12870);
    qDebug() << "After prepend: idx(12866)=" << idx12866 << " idx(12870)=" << idx12870;
    qDebug() << "canBookmark(12870, false) = " << canAdvance;

    QVERIFY2(canAdvance,
             qPrintable(QString("After prepend: 12870 (idx %1) > 12866 (idx %2) should be allowed")
                        .arg(idx12870).arg(idx12866)));

    // Also verify the indices make sense
    // 12870 should have a HIGHER index than 12866 because it's newer
    QVERIFY2(idx12870 > idx12866,
             qPrintable(QString("12870 should have higher index than 12866: %1 vs %2")
                        .arg(idx12870).arg(idx12866)));

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testRaceConditionForceBookmarkThenAutoBookmark()
{
    // Test what happens if:
    // 1. User force-bookmarks an old item
    // 2. Auto-bookmark immediately fires with a newer item
    // The force-bookmark should "stick" and the auto-bookmark should advance

    qDebug() << "\n=== testRaceConditionForceBookmarkThenAutoBookmark ===";

    populateNewsList(12800, 100, baseTime);

    // Start with bookmark at 12870 (newer item)
    allNewsFeed->setBookmark(12870);
    QCOMPARE(allNewsFeed->getBookmarkID(), 12870LL);
    qDebug() << "Initial bookmark: 12870";

    // Force-bookmark to 12866 (older item)
    qDebug() << "Force-bookmarking to 12866...";
    QVERIFY2(allNewsFeed->canBookmark(12866, true),
             "Force-bookmark to 12866 should be allowed");
    allNewsFeed->setBookmark(12866);
    QCOMPARE(allNewsFeed->getBookmarkID(), 12866LL);
    qDebug() << "Bookmark is now: " << allNewsFeed->getBookmarkID();

    // Immediately after, auto-bookmark fires with 12868 (between 12866 and 12870)
    // This should be ALLOWED because 12868 > 12866
    qDebug() << "Auto-bookmark fires with 12868...";
    bool canAdvanceTo12868 = allNewsFeed->canBookmark(12868, false);
    QVERIFY2(canAdvanceTo12868,
             "Auto-bookmark to 12868 (> 12866) should be ALLOWED");

    // Set the bookmark to 12868
    allNewsFeed->setBookmark(12868);
    QCOMPARE(allNewsFeed->getBookmarkID(), 12868LL);
    qDebug() << "Bookmark advanced to: " << allNewsFeed->getBookmarkID();

    // Continue advancing
    QVERIFY2(allNewsFeed->canBookmark(12870, false),
             "Can advance from 12868 to 12870");

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testBugSetBookmarkOperationIndexOfDisplayWindow()
{
    // BUG TEST: SetBookmarkOperation uses indexOf() which only searches the display window.
    // If force-bookmarking to an item outside the display window, indexOf returns -1,
    // which causes incorrect behavior.
    //
    // This test verifies that NewsList::indexOf() returns -1 for items outside the window.

    qDebug() << "\n=== testBugSetBookmarkOperationIndexOfDisplayWindow ===";

    populateNewsList(12800, 60, baseTime);

    // Set initial bookmark to 12850
    allNewsFeed->setBookmark(12850);

    // Trim 20 items from start - items 12800-12819 are now outside display window
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 20);

    qDebug() << "After trim: displaySize=" << allNewsFeed->getNewsList()->size()
             << " first=" << allNewsFeed->getNewsList()->first()->getDbID();

    // Get the item for ID 12810 (outside display window)
    NewsItem* itemOutsideWindow = allNewsFeed->getNewsList()->fullNewsItemForID(12810);
    QVERIFY2(itemOutsideWindow != nullptr, "Item 12810 should be in full list");

    // indexOf() searches the display window - should return -1 for items outside
    qsizetype idx = allNewsFeed->getNewsList()->indexOf(itemOutsideWindow);
    qDebug() << "indexOf(item 12810 outside window) = " << idx;

    // THIS IS THE BUG: indexOf returns -1 for items outside the display window
    // If SetBookmarkOperation uses indexOf(), it will get -1 for the proposed item
    QCOMPARE(idx, -1);  // Confirms the bug exists

    // Get an item inside the display window
    NewsItem* itemInsideWindow = allNewsFeed->getNewsList()->fullNewsItemForID(12830);
    QVERIFY2(itemInsideWindow != nullptr, "Item 12830 should be in full list");

    qsizetype idx2 = allNewsFeed->getNewsList()->indexOf(itemInsideWindow);
    qDebug() << "indexOf(item 12830 inside window) = " << idx2;

    // Items inside the window should have a valid index
    QVERIFY2(idx2 >= 0, "indexOf should return valid index for items in display window");

    qDebug() << "=== BUG CONFIRMED: indexOf returns -1 for items outside display window ===\n";
    qDebug() << "FIX NEEDED: SetBookmarkOperation should use fullIndexForItemID instead of indexOf";
}

void TestBookmarkIntegration::testAutoBookmarkOnOlderItemAfterScrollUp()
{
    // This replicates the EXACT scenario from the user's log:
    // 1. Bookmark is at 12870
    // 2. User scrolls up to view 12866
    // 3. Auto-bookmark tries to set 12866 (but it's older than 12870!)
    // 4. This should be REJECTED

    qDebug() << "\n=== testAutoBookmarkOnOlderItemAfterScrollUp ===";

    // Create items matching the user's log:
    // proposed= 12866 idx= 43 current= 12870 idx= 44 listSize= 60

    // For IDs 12866 at idx 43 and 12870 at idx 44 to be adjacent,
    // we need items with IDs: ..., 12866, 12870, ...
    // where 12867, 12868, 12869 are NOT in the list or are at different positions

    QDateTime startTime = baseTime;

    // Create items before 12866
    for (int i = 0; i < 43; i++) {
        qint64 id = 12800 + i;  // IDs 12800-12842
        QDateTime timestamp = startTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }

    // Add 12866 at index 43
    NewsItem* item12866 = createNewsItem(12866, startTime.addSecs(43 * 60));
    allNewsFeed->getNewsList()->append(item12866);

    // Add 12870 at index 44 (right after 12866)
    NewsItem* item12870 = createNewsItem(12870, startTime.addSecs(44 * 60));
    allNewsFeed->getNewsList()->append(item12870);

    // Add remaining items
    for (int i = 45; i < 60; i++) {
        qint64 id = 12900 + i;
        QDateTime timestamp = startTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }

    QCOMPARE(allNewsFeed->getNewsList()->size(), 60);
    QCOMPARE(allNewsFeed->getNewsList()->indexForItemID(12866), 43);
    QCOMPARE(allNewsFeed->getNewsList()->indexForItemID(12870), 44);

    qDebug() << "Setup complete: 12866 at idx 43, 12870 at idx 44, size 60";

    // Set bookmark to 12870 (the CURRENT bookmark from the log)
    allNewsFeed->setBookmark(12870);
    qDebug() << "Bookmark set to 12870";

    // User scrolls up and views 12866
    // Auto-bookmark tries to set to 12866
    qDebug() << "Auto-bookmark tries to set 12866...";

    qsizetype proposedIdx = allNewsFeed->getNewsList()->indexForItemID(12866);
    qsizetype currentIdx = allNewsFeed->getNewsList()->indexForItemID(12870);

    qDebug() << "canBookmark check:"
             << "proposed= 12866 idx=" << proposedIdx
             << "current= 12870 idx=" << currentIdx
             << "listSize=" << allNewsFeed->getNewsList()->size();

    bool allowed = allNewsFeed->canBookmark(12866, false);
    qDebug() << "canBookmark(12866, false) =" << allowed;

    // This SHOULD be rejected because 12866 < 12870 (going backward)
    QVERIFY2(!allowed, "Auto-bookmark to 12866 (older than 12870) should be REJECTED");

    // The log shows: "REJECTED - index 43 <= 44"
    // This is CORRECT behavior - you can't auto-advance backward

    // The QUESTION is: why is the bookmark at 12870 when the user thought they
    // force-bookmarked 12866? This test confirms the log output is correct,
    // but the bug is that the force-bookmark never happened.

    qDebug() << "=== TEST PASSED (log behavior is correct - auto-bookmark correctly rejected) ===\n";
    qDebug() << "CONCLUSION: The user's log shows correct rejection of backward auto-bookmark.";
    qDebug() << "            The bug is that the force-bookmark to 12866 never happened,";
    qDebug() << "            so the current bookmark is still at the newer item (12870).";
}

void TestBookmarkIntegration::testExactBugScenario_ScrollUpForceBookmarkScrollDown()
{
    // EXACT REPRODUCTION of the bug from user logs:
    //
    // fang.app: setBookmark: canBookmark REJECTED id 13023 allowBackward= false currentBookmark= 13027
    // fang.model: canBookmark: proposed= 13022 idx= 20 current= 13027 idx= 29 listSize= 75
    // fang.model: canBookmark: REJECTED - index 20 <= 29
    //
    // The user scenario:
    // 1. User reads news, bookmark advances to 13027 (index 29 in a list of 75)
    // 2. User scrolls UP (prepends older items, or views older items)
    // 3. User FORCE-BOOKMARKS an older item (let's say 13023)
    // 4. User scrolls DOWN
    // 5. Auto-bookmark tries to advance but is REJECTED
    //
    // The question: WHY is currentBookmark still 13027 after force-bookmarking to 13023?

    qDebug() << "\n=== testExactBugScenario_ScrollUpForceBookmarkScrollDown ===";

    // Create 75 items to match the log (IDs 13000-13074)
    // Item 13022 should be at index 20 -> startID = 13022 - 20 = 13002
    // Item 13027 should be at index 29 -> startID = 13027 - 29 = 12998
    // Let's use startID = 13000, so:
    //   ID 13020 = index 20
    //   ID 13029 = index 29
    // Actually, let's match the exact IDs from the log
    // If ID 13022 is at index 20, then first ID = 13022 - 20 = 13002
    // If ID 13027 is at index 29, then first ID = 13027 - 29 = 12998
    // These don't match! So IDs don't correlate directly with indices.
    //
    // Let me just create a list where:
    // - 75 items total
    // - ID 13022 is at index 20
    // - ID 13027 is at index 29
    // This means there are gaps or non-sequential IDs

    // For simplicity, let's create items with IDs that match the positions
    // Actually, let's create sequential IDs starting from 13000
    // ID 13000 at index 0, ID 13020 at index 20, ID 13027 at index 27 (not 29!)
    //
    // The log shows 13027 at index 29, which means there are 2 items between
    // 13022 (idx 20) and 13027 (idx 29) that have IDs in between, plus
    // 13022 and 13027 are 7 apart in index (29-20=9 items including both ends)
    // but 5 apart in ID (13027-13022=5)
    //
    // This suggests there are items from OTHER feeds interleaved!
    // Or items with non-sequential IDs.

    // Let me create a simpler scenario that still reproduces the bug pattern:
    // - 75 items
    // - Bookmark at newer item (higher index)
    // - Force-bookmark to older item (lower index)
    // - Auto-bookmark to even older item should be rejected

    populateNewsList(13000, 75, baseTime);  // IDs 13000-13074

    qDebug() << "Created 75 items, IDs 13000-13074";
    qDebug() << "First item: ID=" << allNewsFeed->getNewsList()->first()->getDbID()
             << " Last item: ID=" << allNewsFeed->getNewsList()->last()->getDbID();

    // Step 1: Set initial bookmark to a "newer" item (simulating user reading forward)
    // Let's use ID 13050 (index 50) as the initial position
    allNewsFeed->setBookmark(13050);
    QCOMPARE(allNewsFeed->getBookmarkID(), 13050LL);
    qDebug() << "Step 1: Initial bookmark set to 13050 (index 50)";

    // Step 2: User scrolls up to view older items
    // (In the real app, this might prepend items, but for this test the items are already loaded)
    // User is now viewing items around index 20-30

    // Step 3: User FORCE-BOOKMARKS to an older item (13025, index 25)
    qDebug() << "Step 3: Force-bookmark to 13025...";
    bool canForce = allNewsFeed->canBookmark(13025, true);  // allowBackward=true
    QVERIFY2(canForce, "Force-bookmark (allowBackward=true) should ALWAYS be allowed");

    allNewsFeed->setBookmark(13025);

    // CRITICAL CHECK: After force-bookmark, the bookmark should be 13025
    qDebug() << "After force-bookmark: bookmarkID=" << allNewsFeed->getBookmarkID();
    QCOMPARE(allNewsFeed->getBookmarkID(), 13025LL);

    // Verify the bookmark position was captured
    QVERIFY2(allNewsFeed->getBookmarkPosition().isValid(),
             "Bookmark position should be valid after setBookmark");
    QCOMPARE(allNewsFeed->getBookmarkPosition().id(), 13025LL);

    // Step 4: User scrolls down - simulate by trimming from start
    // (Items 13000-13019 scrolled off the top)
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 20);
    qDebug() << "Step 4: Trimmed 20 items from start, simulating scroll down";
    qDebug() << "Display window size: " << allNewsFeed->getNewsList()->size()
             << " First visible: " << allNewsFeed->getNewsList()->first()->getDbID();

    // Step 5: Auto-bookmark tries to advance to items AFTER the bookmark
    // Items 13026, 13027, etc. should be ALLOWED
    // Items 13024, 13023, etc. should be REJECTED (they're before the bookmark)

    qDebug() << "Step 5: Testing auto-bookmark behavior...";

    // Test: items AFTER bookmark should be allowed
    bool can13026 = allNewsFeed->canBookmark(13026, false);
    bool can13030 = allNewsFeed->canBookmark(13030, false);
    bool can13050 = allNewsFeed->canBookmark(13050, false);

    qDebug() << "canBookmark(13026, false) = " << can13026 << " (should be true)";
    qDebug() << "canBookmark(13030, false) = " << can13030 << " (should be true)";
    qDebug() << "canBookmark(13050, false) = " << can13050 << " (should be true)";

    QVERIFY2(can13026, "13026 > 13025, should be allowed");
    QVERIFY2(can13030, "13030 > 13025, should be allowed");
    QVERIFY2(can13050, "13050 > 13025, should be allowed");

    // Test: items BEFORE bookmark should be rejected
    bool can13024 = allNewsFeed->canBookmark(13024, false);
    bool can13020 = allNewsFeed->canBookmark(13020, false);

    qDebug() << "canBookmark(13024, false) = " << can13024 << " (should be false)";
    qDebug() << "canBookmark(13020, false) = " << can13020 << " (should be false)";

    QVERIFY2(!can13024, "13024 < 13025, should be rejected");
    QVERIFY2(!can13020, "13020 < 13025, should be rejected");

    // Verify bookmark hasn't changed
    QCOMPARE(allNewsFeed->getBookmarkID(), 13025LL);

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testPrependMaintainsChronologicalOrder()
{
    // Test that after prepending, the list is still in chronological order
    // (timestamp ASC, id ASC)

    qDebug() << "\n=== testPrependMaintainsChronologicalOrder ===";

    // Create initial items (IDs 100-109, timestamps T+100 to T+109)
    QDateTime startTime = baseTime.addSecs(100 * 60);  // Start at T+100 minutes
    for (int i = 0; i < 10; i++) {
        qint64 id = 100 + i;
        QDateTime timestamp = startTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }

    qDebug() << "Initial list:";
    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->size(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->at(i);
        qDebug() << "  [" << i << "] id=" << item->getDbID()
                 << "timestamp=" << item->getTimestamp().toString(Qt::ISODate);
    }

    // Now simulate prepending older items (IDs 90-99, timestamps T+90 to T+99)
    // The prepend query would return these in timestamp DESC order: [99, 98, ..., 90]
    // We need to prepend them in that order to get correct final order

    QDateTime prependTime = baseTime.addSecs(90 * 60);  // Start at T+90 minutes
    QList<NewsItem*> itemsToPrepend;
    for (int i = 9; i >= 0; i--) {  // Create in DESC order (99, 98, ..., 90)
        qint64 id = 90 + i;
        QDateTime timestamp = prependTime.addSecs(i * 60);
        itemsToPrepend.append(createNewsItem(id, timestamp));
    }

    qDebug() << "Items to prepend (in query order, DESC):";
    for (int i = 0; i < itemsToPrepend.size(); i++) {
        NewsItem* item = itemsToPrepend.at(i);
        qDebug() << "  [" << i << "] id=" << item->getDbID()
                 << "timestamp=" << item->getTimestamp().toString(Qt::ISODate);
    }

    // Prepend them one by one (simulating the loop in LisvelLoadNewsOperation)
    for (NewsItem* item : itemsToPrepend) {
        allNewsFeed->getNewsList()->prepend(item);
    }

    qDebug() << "After prepend:";
    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->size(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->at(i);
        qDebug() << "  [" << i << "] id=" << item->getDbID()
                 << "timestamp=" << item->getTimestamp().toString(Qt::ISODate);
    }

    // Verify the list is in chronological order (timestamp ASC)
    QDateTime prevTimestamp;
    qint64 prevId = -1;
    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->size(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->at(i);
        if (i > 0) {
            bool correctOrder = (item->getTimestamp() > prevTimestamp) ||
                               (item->getTimestamp() == prevTimestamp && item->getDbID() > prevId);
            QVERIFY2(correctOrder,
                     qPrintable(QString("Order violation at index %1: id=%2 timestamp=%3 should be after id=%4 timestamp=%5")
                                .arg(i).arg(item->getDbID()).arg(item->getTimestamp().toString(Qt::ISODate))
                                .arg(prevId).arg(prevTimestamp.toString(Qt::ISODate))));
        }
        prevTimestamp = item->getTimestamp();
        prevId = item->getDbID();
    }

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testForceBookmarkItemOutsideDisplayWindow()
{
    // BUG REPRODUCTION: Force-bookmark to an item outside the display window
    //
    // Scenario:
    // 1. User has 75 items, bookmark at item 50
    // 2. User scrolls down - items 0-29 are trimmed from display window
    // 3. User scrolls back up (items 0-29 are still in memory via pageUp)
    // 4. User views item 10 and force-bookmarks it
    // 5. Item 10 is in the FULL list but outside the current DISPLAY WINDOW
    //
    // The bug: SetBookmarkOperation uses indexOf() which only searches display window,
    // returning -1 for the proposed item, causing incorrect behavior.

    qDebug() << "\n=== testForceBookmarkItemOutsideDisplayWindow ===";

    populateNewsList(100, 75, baseTime);  // IDs 100-174

    // Set initial bookmark to item 150
    allNewsFeed->setBookmark(150);
    QCOMPARE(allNewsFeed->getBookmarkID(), 150LL);
    qDebug() << "Initial bookmark: 150";

    // Trim 30 items from start - simulates scrolling down
    // Items 100-129 are now outside the display window but still in memory
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 30);

    qDebug() << "After trim: displaySize=" << allNewsFeed->getNewsList()->size()
             << " fullSize=" << allNewsFeed->getNewsList()->fullSize()
             << " first visible=" << allNewsFeed->getNewsList()->first()->getDbID();

    // Verify item 110 is outside display window but in full list
    NewsItem* item110_window = allNewsFeed->getNewsList()->newsItemForID(110);
    NewsItem* item110_full = allNewsFeed->getNewsList()->fullNewsItemForID(110);

    QVERIFY2(item110_window == nullptr, "Item 110 should NOT be in display window");
    QVERIFY2(item110_full != nullptr, "Item 110 SHOULD be in full list");

    qDebug() << "Item 110: in window=" << (item110_window != nullptr)
             << " in full=" << (item110_full != nullptr);

    // Check indexOf for an item outside display window
    qsizetype idx_window = allNewsFeed->getNewsList()->indexOf(item110_full);
    qsizetype idx_full = allNewsFeed->getNewsList()->fullIndexForItemID(110);

    qDebug() << "indexOf(item110) = " << idx_window << " (should be -1)";
    qDebug() << "fullIndexForItemID(110) = " << idx_full << " (should be 10)";

    QCOMPARE(idx_window, -1);  // indexOf only searches display window
    QCOMPARE(idx_full, 10);    // fullIndex searches entire list

    // Now try to force-bookmark to item 110 (outside display window)
    qDebug() << "Force-bookmarking to 110 (outside display window)...";

    // canBookmark should allow it with allowBackward=true
    bool canForce = allNewsFeed->canBookmark(110, true);
    QVERIFY2(canForce, "Force-bookmark should always be allowed");

    // Set the bookmark
    allNewsFeed->setBookmark(110);

    // THIS IS THE KEY TEST: Did the bookmark actually change?
    qDebug() << "After force-bookmark: bookmarkID=" << allNewsFeed->getBookmarkID()
             << " (expected: 110)";

    // If SetBookmarkOperation uses indexOf which returns -1, the bookmark might not change correctly
    QCOMPARE(allNewsFeed->getBookmarkID(), 110LL);

    // Also check the position was captured
    QVERIFY(allNewsFeed->getBookmarkPosition().isValid());
    QCOMPARE(allNewsFeed->getBookmarkPosition().id(), 110LL);

    // Now verify canBookmark works correctly for items after the bookmark
    bool can111 = allNewsFeed->canBookmark(111, false);
    bool can130 = allNewsFeed->canBookmark(130, false);

    qDebug() << "canBookmark(111, false) = " << can111 << " (should be true)";
    qDebug() << "canBookmark(130, false) = " << can130 << " (should be true)";

    QVERIFY2(can111, "111 > 110, should be allowed");
    QVERIFY2(can130, "130 > 110, should be allowed");

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testPrependWithNonCorrelatingIDsAndTimestamps()
{
    // BUG SCENARIO: IDs don't correlate with timestamps across feeds
    //
    // This can happen when:
    // - Feed A adds items at times T1, T3, T5 with IDs 1, 3, 5
    // - Feed B adds items at times T2, T4, T6 with IDs 10, 11, 12
    //
    // If bookmark for Feed A is at ID 3, and bookmark for Feed B is at ID 11:
    // - Prepend query for Feed A gets: ID <= 3 → items 1, 3 (at T1, T3)
    // - Prepend query for Feed B gets: ID <= 11 → items 10, 11 (at T2, T4)
    //
    // All News list should show: T1, T2, T3, T4 (chronological)
    // But the ID-based bookmark filter works correctly here!
    //
    // The REAL issue occurs when items from SAME FEED have non-correlating IDs:
    // - If feed items are imported/synced out of order, an item with lower ID
    //   could have a NEWER timestamp than an item with higher ID.

    qDebug() << "\n=== testPrependWithNonCorrelatingIDsAndTimestamps ===";

    // Simulate a scenario where within a single feed, IDs don't correlate with timestamps
    // This could happen if items are imported from an external source out of order
    //
    // Feed items:
    // ID 50, timestamp T+5 (added later, newer timestamp)
    // ID 100, timestamp T+2 (added first, older timestamp but higher ID)
    // ID 150, timestamp T+8 (added later, newest)
    //
    // If sorted by timestamp: T+2 (ID 100), T+5 (ID 50), T+8 (ID 150)
    // If sorted by ID: ID 50, ID 100, ID 150

    // This is a problematic scenario that the current code might not handle

    QList<QPair<qint64, QDateTime>> items = {
        {100, baseTime.addSecs(2 * 60)},  // ID 100, timestamp T+2
        {50, baseTime.addSecs(5 * 60)},   // ID 50, timestamp T+5 (lower ID but newer!)
        {150, baseTime.addSecs(8 * 60)},  // ID 150, timestamp T+8
    };

    // Add them in timestamp order (which is how they should appear in All News)
    // Sort by timestamp first
    std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;  // Sort by timestamp ASC
    });

    qDebug() << "Items sorted by timestamp:";
    for (const auto& p : items) {
        qDebug() << "  id=" << p.first << "timestamp=" << p.second.toString(Qt::ISODate);
    }

    for (const auto& p : items) {
        allNewsFeed->getNewsList()->append(createNewsItem(p.first, p.second));
    }

    // Verify the list is in timestamp order
    QCOMPARE(allNewsFeed->getNewsList()->at(0)->getDbID(), 100LL);  // T+2
    QCOMPARE(allNewsFeed->getNewsList()->at(1)->getDbID(), 50LL);   // T+5
    QCOMPARE(allNewsFeed->getNewsList()->at(2)->getDbID(), 150LL);  // T+8

    qDebug() << "List is in correct timestamp order despite non-correlating IDs";

    // Now set bookmark to ID 50 (middle item by timestamp, but LOWEST ID)
    allNewsFeed->setBookmark(50);

    // If we prepend items with ID <= bookmark (50):
    // - We would get NO items! Because 100 > 50 and 150 > 50
    // - But the item at T+2 (ID 100) is BEFORE the bookmark by timestamp!
    //
    // This is the bug: the bookmark is based on ID, but the display order is by timestamp.
    // When IDs don't correlate with timestamps, the prepend filter is wrong.

    qDebug() << "Bookmark set to ID 50 (timestamp T+5)";
    qDebug() << "Items with ID <= 50: none (but ID 100 at T+2 is chronologically before!)";

    // Check which items would pass the ID <= bookmark filter
    int countWithIdLessOrEqual = 0;
    int countChronologicallyBefore = 0;
    QDateTime bookmarkTimestamp = baseTime.addSecs(5 * 60);

    for (const auto& p : items) {
        if (p.first <= 50) countWithIdLessOrEqual++;
        if (p.second < bookmarkTimestamp) countChronologicallyBefore++;
    }

    qDebug() << "Count with ID <= 50:" << countWithIdLessOrEqual;
    qDebug() << "Count chronologically before bookmark:" << countChronologicallyBefore;

    // This demonstrates the bug: 1 item is chronologically before the bookmark,
    // but 0 items have ID <= bookmark
    QCOMPARE(countWithIdLessOrEqual, 1);  // Only ID 50 itself
    QCOMPARE(countChronologicallyBefore, 1);  // ID 100 at T+2

    qDebug() << "=== BUG DEMONSTRATED: ID-based filter doesn't match timestamp order ===\n";
    qDebug() << "HOWEVER: This requires items to be added with non-correlating IDs,";
    qDebug() << "which shouldn't happen in normal operation where IDs are auto-increment.";
}

void TestBookmarkIntegration::testPrependWithMultipleFeedsOrdering()
{
    // Test prepend ordering when items come from multiple feeds
    // with interleaved timestamps

    qDebug() << "\n=== testPrependWithMultipleFeedsOrdering ===";

    // Create items from two feeds with interleaved timestamps
    // Feed 1: IDs 100, 102, 104 at T+0, T+2, T+4
    // Feed 2: IDs 101, 103, 105 at T+1, T+3, T+5

    QList<QPair<qint64, QDateTime>> initialItems = {
        {100, baseTime.addSecs(0 * 60)},   // Feed 1, T+0
        {101, baseTime.addSecs(1 * 60)},   // Feed 2, T+1
        {102, baseTime.addSecs(2 * 60)},   // Feed 1, T+2
        {103, baseTime.addSecs(3 * 60)},   // Feed 2, T+3
        {104, baseTime.addSecs(4 * 60)},   // Feed 1, T+4
        {105, baseTime.addSecs(5 * 60)},   // Feed 2, T+5
    };

    for (const auto& p : initialItems) {
        allNewsFeed->getNewsList()->append(createNewsItem(p.first, p.second));
    }

    qDebug() << "Initial list (chronological):";
    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->size(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->at(i);
        qDebug() << "  [" << i << "] id=" << item->getDbID()
                 << "timestamp=" << item->getTimestamp().toString(Qt::ISODate);
    }

    // Now simulate prepending OLDER items from both feeds
    // These would come from DB in timestamp DESC order
    // Feed 1: IDs 90, 92, 94 at T-10, T-8, T-6
    // Feed 2: IDs 91, 93, 95 at T-9, T-7, T-5
    // Combined DESC order: 95(T-5), 94(T-6), 93(T-7), 92(T-8), 91(T-9), 90(T-10)

    QList<QPair<qint64, QDateTime>> prependItems = {
        {95, baseTime.addSecs(-5 * 60)},   // Newest to prepend
        {94, baseTime.addSecs(-6 * 60)},
        {93, baseTime.addSecs(-7 * 60)},
        {92, baseTime.addSecs(-8 * 60)},
        {91, baseTime.addSecs(-9 * 60)},
        {90, baseTime.addSecs(-10 * 60)},  // Oldest to prepend
    };

    qDebug() << "Items to prepend (in DESC order as from query):";
    for (const auto& p : prependItems) {
        qDebug() << "  id=" << p.first << "timestamp=" << p.second.toString(Qt::ISODate);
    }

    // Prepend them in query order (DESC)
    for (const auto& p : prependItems) {
        allNewsFeed->getNewsList()->prepend(createNewsItem(p.first, p.second));
    }

    qDebug() << "After prepend:";
    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->size(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->at(i);
        qDebug() << "  [" << i << "] id=" << item->getDbID()
                 << "timestamp=" << item->getTimestamp().toString(Qt::ISODate);
    }

    // Verify chronological order
    QDateTime prevTimestamp;
    qint64 prevId = -1;
    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->size(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->at(i);
        if (i > 0) {
            bool correctOrder = (item->getTimestamp() > prevTimestamp) ||
                               (item->getTimestamp() == prevTimestamp && item->getDbID() > prevId);
            QVERIFY2(correctOrder,
                     qPrintable(QString("Order violation at index %1: id=%2 timestamp=%3 should be after id=%4 timestamp=%5")
                                .arg(i).arg(item->getDbID()).arg(item->getTimestamp().toString(Qt::ISODate))
                                .arg(prevId).arg(prevTimestamp.toString(Qt::ISODate))));
        }
        prevTimestamp = item->getTimestamp();
        prevId = item->getDbID();
    }

    // Also verify the boundary: last prepended item should be before first original item
    NewsItem* lastPrepended = allNewsFeed->getNewsList()->at(5);  // Index 5 = 95 (last prepended, newest of old)
    NewsItem* firstOriginal = allNewsFeed->getNewsList()->at(6);  // Index 6 = 100 (first original)

    qDebug() << "Boundary check: lastPrepended id=" << lastPrepended->getDbID()
             << "timestamp=" << lastPrepended->getTimestamp().toString(Qt::ISODate)
             << " firstOriginal id=" << firstOriginal->getDbID()
             << "timestamp=" << firstOriginal->getTimestamp().toString(Qt::ISODate);

    QVERIFY2(lastPrepended->getTimestamp() < firstOriginal->getTimestamp(),
             "Last prepended item should have timestamp before first original item");

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testMultipleForceBookmarksWhileScrollingUp()
{
    // BUG REPRODUCTION: User reports unread count DECREASES when force-bookmarking
    // backward multiple times while scrolling up.
    //
    // Expected behavior:
    // - Each force-bookmark backward should INCREASE the unread count
    //   (more items are now "after" the bookmark = unread)
    //
    // Scenario:
    // 1. Start with 100 items, bookmark at position 80
    // 2. Scroll up, force-bookmark to position 60 - unread should INCREASE
    // 3. Scroll up more, force-bookmark to position 40 - unread should INCREASE more
    // 4. Scroll up more, force-bookmark to position 20 - unread should INCREASE more

    qDebug() << "\n=== testMultipleForceBookmarksWhileScrollingUp ===";

    populateNewsList(100, 100, baseTime);  // IDs 100-199

    // Initial bookmark at position 80 (ID 180)
    allNewsFeed->setBookmark(180);
    QCOMPARE(allNewsFeed->getBookmarkID(), 180LL);

    qsizetype initialBookmarkIdx = allNewsFeed->getNewsList()->fullIndexForItemID(180);
    qDebug() << "Initial bookmark: ID 180, index" << initialBookmarkIdx;

    // Simulate "unread count" = items after bookmark
    // This is items from bookmark+1 to end
    qsizetype unreadCount1 = allNewsFeed->getNewsList()->fullSize() - initialBookmarkIdx - 1;
    qDebug() << "Initial unread count:" << unreadCount1 << "(items after index" << initialBookmarkIdx << ")";

    // Step 1: Scroll up, force-bookmark to position 60 (ID 160)
    qDebug() << "\nStep 1: Force-bookmark to ID 160...";
    QVERIFY(allNewsFeed->canBookmark(160, true));
    allNewsFeed->setBookmark(160);
    QCOMPARE(allNewsFeed->getBookmarkID(), 160LL);

    qsizetype idx2 = allNewsFeed->getNewsList()->fullIndexForItemID(160);
    qsizetype unreadCount2 = allNewsFeed->getNewsList()->fullSize() - idx2 - 1;
    qDebug() << "After bookmark 160: index" << idx2 << ", unread count:" << unreadCount2;

    // Unread count should have INCREASED (we moved bookmark backward)
    QVERIFY2(unreadCount2 > unreadCount1,
             qPrintable(QString("Unread should INCREASE: was %1, now %2").arg(unreadCount1).arg(unreadCount2)));

    // Step 2: Force-bookmark to position 40 (ID 140)
    qDebug() << "\nStep 2: Force-bookmark to ID 140...";
    QVERIFY(allNewsFeed->canBookmark(140, true));
    allNewsFeed->setBookmark(140);
    QCOMPARE(allNewsFeed->getBookmarkID(), 140LL);

    qsizetype idx3 = allNewsFeed->getNewsList()->fullIndexForItemID(140);
    qsizetype unreadCount3 = allNewsFeed->getNewsList()->fullSize() - idx3 - 1;
    qDebug() << "After bookmark 140: index" << idx3 << ", unread count:" << unreadCount3;

    // Unread count should have INCREASED again
    QVERIFY2(unreadCount3 > unreadCount2,
             qPrintable(QString("Unread should INCREASE: was %1, now %2").arg(unreadCount2).arg(unreadCount3)));

    // Step 3: Force-bookmark to position 20 (ID 120)
    qDebug() << "\nStep 3: Force-bookmark to ID 120...";
    QVERIFY(allNewsFeed->canBookmark(120, true));
    allNewsFeed->setBookmark(120);
    QCOMPARE(allNewsFeed->getBookmarkID(), 120LL);

    qsizetype idx4 = allNewsFeed->getNewsList()->fullIndexForItemID(120);
    qsizetype unreadCount4 = allNewsFeed->getNewsList()->fullSize() - idx4 - 1;
    qDebug() << "After bookmark 120: index" << idx4 << ", unread count:" << unreadCount4;

    // Unread count should have INCREASED again
    QVERIFY2(unreadCount4 > unreadCount3,
             qPrintable(QString("Unread should INCREASE: was %1, now %2").arg(unreadCount3).arg(unreadCount4)));

    // Now verify indices are correct for canBookmark
    // Items AFTER 120 should be allowed
    qDebug() << "\nVerifying canBookmark after multiple force-bookmarks...";

    bool can121 = allNewsFeed->canBookmark(121, false);
    bool can130 = allNewsFeed->canBookmark(130, false);
    bool can180 = allNewsFeed->canBookmark(180, false);

    qDebug() << "canBookmark(121, false) = " << can121 << " (should be true)";
    qDebug() << "canBookmark(130, false) = " << can130 << " (should be true)";
    qDebug() << "canBookmark(180, false) = " << can180 << " (should be true)";

    QVERIFY2(can121, "121 > 120, should be allowed");
    QVERIFY2(can130, "130 > 120, should be allowed");
    QVERIFY2(can180, "180 > 120, should be allowed");

    // Items AT or BEFORE 120 should be rejected
    bool can120 = allNewsFeed->canBookmark(120, false);
    bool can119 = allNewsFeed->canBookmark(119, false);
    bool can100 = allNewsFeed->canBookmark(100, false);

    qDebug() << "canBookmark(120, false) = " << can120 << " (should be false)";
    qDebug() << "canBookmark(119, false) = " << can119 << " (should be false)";
    qDebug() << "canBookmark(100, false) = " << can100 << " (should be false)";

    QVERIFY2(!can120, "Same ID should be rejected");
    QVERIFY2(!can119, "119 < 120, should be rejected");
    QVERIFY2(!can100, "100 < 120, should be rejected");

    qDebug() << "\n=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testBookmarkIterationWithNonCorrelatingIDs()
{
    // BUG REPRODUCTION: Test what happens when IDs don't correlate with timestamps.
    //
    // This can happen when items are imported from external sources with pre-assigned
    // IDs, or when items are added to a feed out of chronological order.
    //
    // The SetBookmarkOperation::bookmarkAllNewsFeed backward query uses:
    //   "id < :bookmark_id ORDER BY id DESC LIMIT 1"
    // This finds the item with the HIGHEST ID that is LESS than the current item's ID.
    //
    // But if IDs don't correlate with timestamps, "previous by ID" might not match
    // "previous by timestamp position in the list".
    //
    // Example scenario:
    // - Feed A has items: #100 (T+10), #50 (T+20), #150 (T+30)
    // - List sorted by timestamp: [#100 T+10, #50 T+20, #150 T+30] (positions 0, 1, 2)
    // - When we process position 1 (#50), "id < 50" finds items with ID < 50, not #100!

    qDebug() << "\n=== testBookmarkIterationWithNonCorrelatingIDs ===";

    // Create items from a single feed with NON-CORRELATING IDs and timestamps
    // Lower ID (#50) has a LATER timestamp than higher ID (#100)
    QList<QPair<qint64, QDateTime>> items = {
        {100, baseTime.addSecs(10 * 60)},  // ID 100, timestamp T+10
        {50, baseTime.addSecs(20 * 60)},   // ID 50, timestamp T+20 (lower ID, LATER timestamp!)
        {150, baseTime.addSecs(30 * 60)},  // ID 150, timestamp T+30
    };

    // Sort by timestamp (as the list would be)
    std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    qDebug() << "Items sorted by timestamp:";
    for (int i = 0; i < items.size(); i++) {
        qDebug() << "  [" << i << "] id=" << items[i].first
                 << "timestamp=" << items[i].second.toString(Qt::ISODate);
    }
    // Expected: [100 T+10, 50 T+20, 150 T+30]

    for (const auto& p : items) {
        allNewsFeed->getNewsList()->append(createNewsItem(p.first, p.second));
    }

    // Verify list order
    QCOMPARE(allNewsFeed->getNewsList()->at(0)->getDbID(), 100LL);  // Position 0: T+10, ID 100
    QCOMPARE(allNewsFeed->getNewsList()->at(1)->getDbID(), 50LL);   // Position 1: T+20, ID 50
    QCOMPARE(allNewsFeed->getNewsList()->at(2)->getDbID(), 150LL);  // Position 2: T+30, ID 150

    qDebug() << "List correctly ordered by timestamp: [100, 50, 150]";
    qDebug() << "Note: ID 50 is at position 1, AFTER ID 100 at position 0";

    // Set initial bookmark to position 2 (ID 150, newest)
    allNewsFeed->setBookmark(150);
    QCOMPARE(allNewsFeed->getBookmarkID(), 150LL);

    // Now simulate the backward iteration logic that SetBookmarkOperation would do:
    // Going from position 2 to position 0
    //
    // Position 2: ID 150 -> "id < 150" = max(100, 50) = 100
    // Position 1: ID 50 -> "id < 50" = ??? (there's no item with id < 50!)
    //
    // If the backward query at position 1 returns -1 (no item with id < 50),
    // the bookmark would be set to -1, meaning ALL items are unread.
    //
    // But what we WANTED was to stop at position 0 (ID 100), not go to -1!

    // Let's verify the index lookups are correct
    qsizetype idx100 = allNewsFeed->getNewsList()->fullIndexForItemID(100);
    qsizetype idx50 = allNewsFeed->getNewsList()->fullIndexForItemID(50);
    qsizetype idx150 = allNewsFeed->getNewsList()->fullIndexForItemID(150);

    qDebug() << "Index lookups: 100->" << idx100 << ", 50->" << idx50 << ", 150->" << idx150;

    QCOMPARE(idx100, 0);  // ID 100 is at position 0 (earliest timestamp)
    QCOMPARE(idx50, 1);   // ID 50 is at position 1 (middle timestamp)
    QCOMPARE(idx150, 2);  // ID 150 is at position 2 (latest timestamp)

    // Now let's simulate what canBookmark would do after a backward force-bookmark
    // If bookmark is incorrectly set due to non-correlating IDs, canBookmark might
    // give wrong results

    // Force-bookmark to position 0 (ID 100)
    qDebug() << "\nForce-bookmarking to ID 100 (position 0)...";
    QVERIFY(allNewsFeed->canBookmark(100, true));
    allNewsFeed->setBookmark(100);
    QCOMPARE(allNewsFeed->getBookmarkID(), 100LL);

    // Items AFTER position 0 should be allowed
    // Position 1 (ID 50) and Position 2 (ID 150) are after position 0
    bool can50 = allNewsFeed->canBookmark(50, false);
    bool can150 = allNewsFeed->canBookmark(150, false);

    qDebug() << "canBookmark(50, false) = " << can50 << " (position 1 > position 0, should be TRUE)";
    qDebug() << "canBookmark(150, false) = " << can150 << " (position 2 > position 0, should be TRUE)";

    QVERIFY2(can50, "ID 50 is at position 1 > position 0 (bookmark), should be allowed");
    QVERIFY2(can150, "ID 150 is at position 2 > position 0 (bookmark), should be allowed");

    // This test verifies that canBookmark uses position/timestamp comparison correctly,
    // NOT ID comparison. The bug in SetBookmarkOperation is that the backward SQL query
    // uses ID comparison ("id < :bookmark_id") instead of timestamp/position comparison.

    qDebug() << "\n=== TEST DEMONSTRATES THE BUG ===";
    qDebug() << "If SetBookmarkOperation iterates backward from position 2 to position 0:";
    qDebug() << "  Position 2 (ID 150): SQL finds 'id < 150' = 100, sets bookmark to 100 ✓";
    qDebug() << "  Position 1 (ID 50): SQL finds 'id < 50' = NOTHING OR WRONG ITEM ✗";
    qDebug() << "The backward iteration would OVERSHOOT position 0 because ID 50 < ID 100";
    qDebug() << "but position 1 > position 0 in the timestamp-sorted list!";
    qDebug() << "\n=== TEST PASSED (in-memory model works correctly) ===\n";
}

void TestBookmarkIntegration::testVerifyPrependOrderInRealScenario()
{
    // This test simulates the EXACT prepend flow that happens in the app:
    // 1. Initial load: append items after bookmark
    // 2. Prepend: add items before bookmark
    // 3. Verify the ENTIRE list is in chronological order
    //
    // The prepend query returns items in DESC order (newest first among old items).
    // These items must be prepended such that the final list is ASC order.

    qDebug() << "\n=== testVerifyPrependOrderInRealScenario ===";

    // Simulate initial APPEND: Items 50-99 (after bookmark at 49)
    // These are the "unread" items loaded first
    QDateTime appendTime = baseTime.addSecs(50 * 60);  // T+50 minutes
    for (int i = 0; i < 50; i++) {
        qint64 id = 50 + i;  // IDs 50-99
        QDateTime timestamp = appendTime.addSecs(i * 60);
        NewsItem* item = createNewsItem(id, timestamp);
        allNewsFeed->getNewsList()->append(item);
    }

    qDebug() << "After append: " << allNewsFeed->getNewsList()->size() << " items";
    qDebug() << "First: ID" << allNewsFeed->getNewsList()->first()->getDbID()
             << "ts" << allNewsFeed->getNewsList()->first()->getTimestamp().toString(Qt::ISODate);
    qDebug() << "Last: ID" << allNewsFeed->getNewsList()->last()->getDbID()
             << "ts" << allNewsFeed->getNewsList()->last()->getTimestamp().toString(Qt::ISODate);

    // Simulate PREPEND: Items 0-49 (at/before bookmark)
    // The prepend query would return these in DESC order: [49, 48, ..., 0]
    QDateTime prependTime = baseTime;  // T+0 minutes
    QList<NewsItem*> prependList;
    for (int i = 49; i >= 0; i--) {  // Create in DESC order like the query would
        qint64 id = i;  // IDs 49, 48, ..., 0
        QDateTime timestamp = prependTime.addSecs(i * 60);
        prependList.append(createNewsItem(id, timestamp));
    }

    qDebug() << "Prepend list (DESC order as from query):";
    for (int i = 0; i < 5; i++) {  // Just show first 5
        qDebug() << "  [" << i << "] ID" << prependList.at(i)->getDbID()
                 << "ts" << prependList.at(i)->getTimestamp().toString(Qt::ISODate);
    }
    qDebug() << "  ...";

    // Now prepend these items (simulating LisvelLoadNewsOperation loop)
    for (NewsItem* item : prependList) {
        allNewsFeed->getNewsList()->prepend(item);
    }

    qDebug() << "After prepend: " << allNewsFeed->getNewsList()->size() << " items";
    qDebug() << "First: ID" << allNewsFeed->getNewsList()->first()->getDbID()
             << "ts" << allNewsFeed->getNewsList()->first()->getTimestamp().toString(Qt::ISODate);
    qDebug() << "Last: ID" << allNewsFeed->getNewsList()->last()->getDbID()
             << "ts" << allNewsFeed->getNewsList()->last()->getTimestamp().toString(Qt::ISODate);

    // CRITICAL: Verify the ENTIRE list is in chronological order
    qDebug() << "\nVerifying chronological order...";
    QDateTime prevTimestamp;
    qint64 prevId = -1;
    int violations = 0;

    for (qsizetype i = 0; i < allNewsFeed->getNewsList()->fullSize(); i++) {
        NewsItem* item = allNewsFeed->getNewsList()->fullAt(i);
        if (i > 0) {
            bool correctOrder = (item->getTimestamp() > prevTimestamp) ||
                               (item->getTimestamp() == prevTimestamp && item->getDbID() > prevId);
            if (!correctOrder) {
                violations++;
                if (violations <= 5) {  // Only show first 5 violations
                    qDebug() << "ORDER VIOLATION at index" << i
                             << ": ID" << item->getDbID() << "ts" << item->getTimestamp().toString(Qt::ISODate)
                             << "should be after ID" << prevId << "ts" << prevTimestamp.toString(Qt::ISODate);
                }
            }
        }
        prevTimestamp = item->getTimestamp();
        prevId = item->getDbID();
    }

    if (violations > 0) {
        QFAIL(qPrintable(QString("Found %1 order violations!").arg(violations)));
    }

    // Also verify boundary: item 49 should be before item 50
    NewsItem* item49 = allNewsFeed->getNewsList()->fullNewsItemForID(49);
    NewsItem* item50 = allNewsFeed->getNewsList()->fullNewsItemForID(50);
    QVERIFY(item49 != nullptr);
    QVERIFY(item50 != nullptr);

    qsizetype idx49 = allNewsFeed->getNewsList()->fullIndexForItemID(49);
    qsizetype idx50 = allNewsFeed->getNewsList()->fullIndexForItemID(50);

    qDebug() << "Boundary: ID 49 at index" << idx49 << ", ID 50 at index" << idx50;
    QVERIFY2(idx49 < idx50, "ID 49 should be at lower index than ID 50");
    QVERIFY2(item49->getTimestamp() < item50->getTimestamp(),
             "ID 49 should have earlier timestamp than ID 50");

    qDebug() << "\n=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testPageDownAfterScrollUp()
{
    // BUG FIX VERIFICATION:
    // After scrolling up (which trims items from the end), scrolling back down
    // should page through items already in memory. These paged items must be
    // correctly identified so they can be sent to JavaScript.
    //
    // The bug was: pageDown() expanded the display window, but the newly-visible
    // items weren't being tracked for the JS response.

    qDebug() << "\n=== testPageDownAfterScrollUp ===";

    populateNewsList(100, 50, baseTime);  // IDs 100-149

    QCOMPARE(allNewsFeed->getNewsList()->size(), 50);
    QCOMPARE(allNewsFeed->getNewsList()->fullSize(), 50);

    // Set bookmark to middle
    allNewsFeed->setBookmark(125);

    // Simulate scroll up: trim 20 items from the end
    allNewsFeed->getNewsList()->shrinkDisplayWindow(false, 20);

    qDebug() << "After trim from end: displaySize=" << allNewsFeed->getNewsList()->size()
             << " fullSize=" << allNewsFeed->getNewsList()->fullSize()
             << " lastVisible=" << allNewsFeed->getNewsList()->last()->getDbID();

    QCOMPARE(allNewsFeed->getNewsList()->size(), 30);      // Items 100-129 visible
    QCOMPARE(allNewsFeed->getNewsList()->fullSize(), 50);  // All 50 still in memory
    QCOMPARE(allNewsFeed->getNewsList()->last()->getDbID(), 129LL);

    // Should be able to page down
    QVERIFY(allNewsFeed->getNewsList()->canPageDown());

    // Record the old display end before paging
    qsizetype oldDisplayEnd = allNewsFeed->getNewsList()->getDisplayEnd();

    // Page down 10 items
    qsizetype paged = allNewsFeed->getNewsList()->pageDown(10);
    QCOMPARE(paged, 10);

    qsizetype newDisplayEnd = allNewsFeed->getNewsList()->getDisplayEnd();

    qDebug() << "After pageDown(10): oldEnd=" << oldDisplayEnd
             << " newEnd=" << newDisplayEnd
             << " lastVisible=" << allNewsFeed->getNewsList()->last()->getDbID();

    QCOMPARE(allNewsFeed->getNewsList()->size(), 40);  // Items 100-139 visible
    QCOMPARE(allNewsFeed->getNewsList()->last()->getDbID(), 139LL);

    // Verify the newly-visible items are the correct ones
    // Items at indices [oldDisplayEnd, newDisplayEnd) should be IDs 130-139
    QList<qint64> pagedItemIds;
    for (qsizetype i = oldDisplayEnd; i < newDisplayEnd; ++i) {
        pagedItemIds.append(allNewsFeed->getNewsList()->fullAt(i)->getDbID());
    }

    qDebug() << "Paged item IDs:" << pagedItemIds;

    QCOMPARE(pagedItemIds.size(), 10);
    for (int i = 0; i < 10; ++i) {
        QCOMPARE(pagedItemIds.at(i), 130LL + i);
    }

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testPageUpAfterScrollDown()
{
    // After scrolling down (which trims items from the start), scrolling back up
    // should page through items already in memory.

    qDebug() << "\n=== testPageUpAfterScrollDown ===";

    populateNewsList(100, 50, baseTime);  // IDs 100-149

    // Set bookmark
    allNewsFeed->setBookmark(125);

    // Simulate scroll down: trim 20 items from the start
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 20);

    qDebug() << "After trim from start: displaySize=" << allNewsFeed->getNewsList()->size()
             << " firstVisible=" << allNewsFeed->getNewsList()->first()->getDbID();

    QCOMPARE(allNewsFeed->getNewsList()->size(), 30);      // Items 120-149 visible
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 120LL);

    // Should be able to page up
    QVERIFY(allNewsFeed->getNewsList()->canPageUp());

    // Record the old display start before paging
    qsizetype oldDisplayStart = allNewsFeed->getNewsList()->getDisplayStart();

    // Page up 10 items
    qsizetype paged = allNewsFeed->getNewsList()->pageUp(10);
    QCOMPARE(paged, 10);

    qsizetype newDisplayStart = allNewsFeed->getNewsList()->getDisplayStart();

    qDebug() << "After pageUp(10): oldStart=" << oldDisplayStart
             << " newStart=" << newDisplayStart
             << " firstVisible=" << allNewsFeed->getNewsList()->first()->getDbID();

    QCOMPARE(allNewsFeed->getNewsList()->size(), 40);  // Items 110-149 visible
    QCOMPARE(allNewsFeed->getNewsList()->first()->getDbID(), 110LL);

    // Verify the newly-visible items are the correct ones
    // Items at indices [newDisplayStart, oldDisplayStart) should be IDs 110-119
    QList<qint64> pagedItemIds;
    for (qsizetype i = newDisplayStart; i < oldDisplayStart; ++i) {
        pagedItemIds.append(allNewsFeed->getNewsList()->fullAt(i)->getDbID());
    }

    qDebug() << "Paged item IDs:" << pagedItemIds;

    QCOMPARE(pagedItemIds.size(), 10);
    for (int i = 0; i < 10; ++i) {
        QCOMPARE(pagedItemIds.at(i), 110LL + i);
    }

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testPagedItemsAreInCorrectOrder()
{
    // Verify that when items are paged (from memory) they're in chronological order.
    // This is critical for the JavaScript to display them correctly.

    qDebug() << "\n=== testPagedItemsAreInCorrectOrder ===";

    populateNewsList(100, 100, baseTime);  // IDs 100-199

    // Trim from both ends to simulate scrolling to middle
    allNewsFeed->getNewsList()->shrinkDisplayWindow(true, 30);   // Trim first 30
    allNewsFeed->getNewsList()->shrinkDisplayWindow(false, 30);  // Trim last 30

    qDebug() << "After trimming: displaySize=" << allNewsFeed->getNewsList()->size()
             << " first=" << allNewsFeed->getNewsList()->first()->getDbID()
             << " last=" << allNewsFeed->getNewsList()->last()->getDbID();

    QCOMPARE(allNewsFeed->getNewsList()->size(), 40);  // Items 130-169 visible
    QVERIFY(allNewsFeed->getNewsList()->canPageUp());
    QVERIFY(allNewsFeed->getNewsList()->canPageDown());

    // Page up 15 items
    qsizetype oldStart = allNewsFeed->getNewsList()->getDisplayStart();
    allNewsFeed->getNewsList()->pageUp(15);
    qsizetype newStart = allNewsFeed->getNewsList()->getDisplayStart();

    // Collect paged items in the order they would be prepended
    QList<NewsItem*> pagedUpItems;
    for (qsizetype i = oldStart - 1; i >= newStart; --i) {
        pagedUpItems.append(allNewsFeed->getNewsList()->fullAt(i));
    }

    qDebug() << "PageUp items (DESC order for prepend):";
    for (int i = 0; i < pagedUpItems.size(); ++i) {
        qDebug() << "  [" << i << "] id=" << pagedUpItems.at(i)->getDbID()
                 << " ts=" << pagedUpItems.at(i)->getTimestamp().toString(Qt::ISODate);
    }

    // Verify they're in DESC order (newest first among paged items)
    // This matches how prepend works - items come from DB in DESC order
    for (int i = 1; i < pagedUpItems.size(); ++i) {
        QVERIFY2(pagedUpItems.at(i)->getTimestamp() < pagedUpItems.at(i-1)->getTimestamp(),
                 "PageUp items should be in DESC order (newest first)");
    }

    // Page down 15 items
    qsizetype oldEnd = allNewsFeed->getNewsList()->getDisplayEnd();
    allNewsFeed->getNewsList()->pageDown(15);
    qsizetype newEnd = allNewsFeed->getNewsList()->getDisplayEnd();

    // Collect paged items in the order they would be appended
    QList<NewsItem*> pagedDownItems;
    for (qsizetype i = oldEnd; i < newEnd; ++i) {
        pagedDownItems.append(allNewsFeed->getNewsList()->fullAt(i));
    }

    qDebug() << "PageDown items (ASC order for append):";
    for (int i = 0; i < pagedDownItems.size(); ++i) {
        qDebug() << "  [" << i << "] id=" << pagedDownItems.at(i)->getDbID()
                 << " ts=" << pagedDownItems.at(i)->getTimestamp().toString(Qt::ISODate);
    }

    // Verify they're in ASC order (oldest first among paged items)
    // This matches how append works
    for (int i = 1; i < pagedDownItems.size(); ++i) {
        QVERIFY2(pagedDownItems.at(i)->getTimestamp() > pagedDownItems.at(i-1)->getTimestamp(),
                 "PageDown items should be in ASC order (oldest first)");
    }

    qDebug() << "=== TEST PASSED ===\n";
}

// ============================================================================
// WEBSERVER / JAVASCRIPT INTEGRATION TESTS
// ============================================================================
//
// These tests verify the data format that WebServer sends to fang.js.
// While we can't easily test the full WebServer (it depends on FangApp),
// we can test the ordering logic that WebServer applies.
//
// The key insight is:
// - The prepend query returns items in timestamp DESC order (newest first)
// - WebServer MUST reverse these before sending to JS
// - JS expects items in timestamp ASC order (oldest first)
//
// For full JS integration testing without the UI, consider:
// 1. Node.js with jsdom - Run fang.js through Node with a mock DOM
// 2. Qt's QML testing framework for WebView integration
// 3. Headless browser testing with Playwright/Puppeteer
// ============================================================================

void TestBookmarkIntegration::testPrependListReversalForJS()
{
    // BUG FIX VERIFICATION:
    // WebServer.cpp must reverse the prepend list before sending to JavaScript.
    // The prepend query returns items in DESC order (newest first among read items),
    // but JavaScript expects ASC order (oldest first).
    //
    // This test simulates what WebServer does with the prepend list.

    qDebug() << "\n=== testPrependListReversalForJS ===";

    // Simulate a prepend list as it would come from the database query
    // Query: ORDER BY timestamp DESC, id DESC
    QList<NewsItem*> prependListFromDB;
    for (int i = 9; i >= 0; --i) {  // Descending: 9, 8, 7, ..., 0
        prependListFromDB.append(createNewsItem(100 + i, baseTime.addSecs(i * 60)));
    }

    qDebug() << "Prepend list from DB (DESC order):";
    for (int i = 0; i < prependListFromDB.size(); ++i) {
        qDebug() << "  [" << i << "] id=" << prependListFromDB.at(i)->getDbID();
    }

    // Verify it's in DESC order
    QCOMPARE(prependListFromDB.first()->getDbID(), 109LL);  // Newest
    QCOMPARE(prependListFromDB.last()->getDbID(), 100LL);   // Oldest

    // WebServer reverses the list before sending to JS:
    // for (qsizetype i = loader->getPrependList().size() - 1; i >= 0; i--) { ... }
    QList<NewsItem*> prependListForJS;
    for (qsizetype i = prependListFromDB.size() - 1; i >= 0; --i) {
        prependListForJS.append(prependListFromDB.at(i));
    }

    qDebug() << "Prepend list for JS (reversed to ASC order):";
    for (int i = 0; i < prependListForJS.size(); ++i) {
        qDebug() << "  [" << i << "] id=" << prependListForJS.at(i)->getDbID();
    }

    // Verify it's now in ASC order (oldest first)
    QCOMPARE(prependListForJS.first()->getDbID(), 100LL);  // Oldest
    QCOMPARE(prependListForJS.last()->getDbID(), 109LL);   // Newest

    // Verify chronological order
    for (int i = 1; i < prependListForJS.size(); ++i) {
        QVERIFY2(prependListForJS.at(i)->getTimestamp() > prependListForJS.at(i-1)->getTimestamp(),
                 "Reversed list should be in ASC order (oldest first)");
    }

    // Cleanup
    qDeleteAll(prependListFromDB);

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testAppendListOrderForJS()
{
    // Append list comes from DB in ASC order and should be sent to JS as-is.
    // Query: ORDER BY timestamp ASC, id ASC

    qDebug() << "\n=== testAppendListOrderForJS ===";

    // Simulate an append list as it would come from the database query
    QList<NewsItem*> appendListFromDB;
    for (int i = 0; i < 10; ++i) {  // Ascending: 0, 1, 2, ..., 9
        appendListFromDB.append(createNewsItem(200 + i, baseTime.addSecs(i * 60)));
    }

    qDebug() << "Append list from DB (ASC order):";
    for (int i = 0; i < appendListFromDB.size(); ++i) {
        qDebug() << "  [" << i << "] id=" << appendListFromDB.at(i)->getDbID();
    }

    // Verify it's in ASC order (oldest first)
    QCOMPARE(appendListFromDB.first()->getDbID(), 200LL);  // Oldest
    QCOMPARE(appendListFromDB.last()->getDbID(), 209LL);   // Newest

    // WebServer sends append list directly to JS (no reversal needed)
    // for (NewsItem* item : std::as_const(loader->getAppendList())) { ... }

    // Verify chronological order
    for (int i = 1; i < appendListFromDB.size(); ++i) {
        QVERIFY2(appendListFromDB.at(i)->getTimestamp() > appendListFromDB.at(i-1)->getTimestamp(),
                 "Append list should be in ASC order (oldest first)");
    }

    // Cleanup
    qDeleteAll(appendListFromDB);

    qDebug() << "=== TEST PASSED ===\n";
}

void TestBookmarkIntegration::testMixedPrependAppendOrdering()
{
    // Test the combined scenario: prepend followed by append.
    // This simulates what happens during initial load:
    // 1. Append unread items (items after bookmark)
    // 2. Prepend read items (items before bookmark)
    //
    // The final list sent to JS should be in chronological order:
    // [prepended items (oldest)] ... [appended items (newest)]

    qDebug() << "\n=== testMixedPrependAppendOrdering ===";

    // Append list: items 50-59 (after bookmark at 49)
    QList<NewsItem*> appendList;
    for (int i = 0; i < 10; ++i) {
        appendList.append(createNewsItem(50 + i, baseTime.addSecs((50 + i) * 60)));
    }

    // Prepend list from DB: items 40-49 in DESC order
    QList<NewsItem*> prependListFromDB;
    for (int i = 9; i >= 0; --i) {
        prependListFromDB.append(createNewsItem(40 + i, baseTime.addSecs((40 + i) * 60)));
    }

    // Build the final list as WebServer would for Initial load:
    // First, reverse prepend list and add
    QList<NewsItem*> finalListForJS;
    for (qsizetype i = prependListFromDB.size() - 1; i >= 0; --i) {
        finalListForJS.append(prependListFromDB.at(i));
    }

    // Then add append list as-is
    for (NewsItem* item : appendList) {
        finalListForJS.append(item);
    }

    qDebug() << "Final list for JS:";
    for (int i = 0; i < finalListForJS.size(); ++i) {
        qDebug() << "  [" << i << "] id=" << finalListForJS.at(i)->getDbID();
    }

    // Verify: should be 40, 41, 42, ..., 59 (all in ASC order)
    QCOMPARE(finalListForJS.size(), 20);
    QCOMPARE(finalListForJS.first()->getDbID(), 40LL);
    QCOMPARE(finalListForJS.last()->getDbID(), 59LL);

    // Verify strict chronological order
    for (int i = 1; i < finalListForJS.size(); ++i) {
        QVERIFY2(finalListForJS.at(i)->getTimestamp() > finalListForJS.at(i-1)->getTimestamp(),
                 qPrintable(QString("Order violation at index %1: id %2 should be after id %3")
                            .arg(i)
                            .arg(finalListForJS.at(i)->getDbID())
                            .arg(finalListForJS.at(i-1)->getDbID())));
    }

    // Cleanup
    qDeleteAll(appendList);
    qDeleteAll(prependListFromDB);

    qDebug() << "=== TEST PASSED ===\n";
}

QTEST_MAIN(TestBookmarkIntegration)

#include "tst_bookmarkintegration.moc"
