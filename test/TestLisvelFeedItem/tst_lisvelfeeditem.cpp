#include <QTest>
#include "../../src/models/LisvelFeedItem.h"
#include "../../src/models/NewsItem.h"
#include "../../src/models/NewsList.h"
#include "../../src/models/NewsPosition.h"

/**
 * Test LisvelFeedItem bookmark behavior.
 *
 * LisvelFeedItem (used by AllNewsFeedItem and FolderFeedItem) uses index-based
 * comparison for canBookmark() rather than ID-based comparison. This is because
 * these feeds aggregate news from multiple sources, where DB IDs don't necessarily
 * correspond to chronological order in the view.
 */
class TestLisvelFeedItem : public QObject
{
    Q_OBJECT

public:
    TestLisvelFeedItem();

private slots:
    void cleanup();

    // canBookmark tests - index-based comparison
    void testCanBookmark_NoCurrentBookmark();
    void testCanBookmark_ProposedNotInList();
    void testCanBookmark_ForwardAllowed();
    void testCanBookmark_BackwardRejected();
    void testCanBookmark_AllowBackward();
    void testCanBookmark_SameBookmark();
    void testCanBookmark_InvalidID();

    // Fallback to ID comparison when current bookmark not in list
    void testCanBookmark_CurrentNotInList_ForwardAllowed();
    void testCanBookmark_CurrentNotInList_BackwardRejected();

    // Regression test: force bookmark backward, then scroll up more
    void testCanBookmark_AfterForceBackward_RejectsOlderItems();

    // Index shift scenario (prepending items)
    void testCanBookmark_AfterPrepend_IndicesShift();

    // Full scenario: force backward, scroll up more, trimming happens
    void testCanBookmark_ForceBackwardThenScrollUpWithTrimming();

    // Timestamp-based ordering (IDs don't match chronological order)
    void testCanBookmark_TimestampOrdering_IDsReversed();
    void testCanBookmark_TimestampOrdering_SameTimestamp();

    // ========== NewsPosition unit tests ==========
    void testNewsPosition_DefaultConstruction();
    void testNewsPosition_ValidConstruction();
    void testNewsPosition_IsValid();
    void testNewsPosition_IsAfter_BothValid();
    void testNewsPosition_IsAfter_InvalidPositions();
    void testNewsPosition_IsBefore_BothValid();
    void testNewsPosition_IsBefore_InvalidPositions();
    void testNewsPosition_Equality();
    void testNewsPosition_SameTimestampDifferentID();

    // ========== setBookmark and position capture ==========
    void testSetBookmark_CapturesPosition();
    void testSetBookmark_PreservesPositionWhenItemNotFound();
    void testSetBookmark_UpdatesPositionWhenItemFound();
    void testSetBookmark_ClearsPositionOnNegativeOne();
    void testSetBookmark_LazyInitialization();

    // ========== getBookmarkPosition ==========
    void testGetBookmarkPosition_InitiallyInvalid();
    void testGetBookmarkPosition_ValidAfterSetBookmark();
    void testGetBookmarkPosition_PreservedAfterTrim();

    // ========== Edge cases ==========
    void testCanBookmark_EmptyList();
    void testCanBookmark_SingleItemList();
    void testCanBookmark_BookmarkAtListStart();
    void testCanBookmark_BookmarkAtListEnd();
    void testCanBookmark_ProposedIDNegativeOne();
    void testCanBookmark_MultipleTrimCycles();
    void testCanBookmark_PositionPreservedAcrossMultipleSetBookmarks();

    // ========== Display window tests ==========
    void testSetBookmark_ItemOutsideDisplayWindow_PositionCaptured();

    // ========== Realistic multi-feed scenarios ==========
    void testCanBookmark_MultiFeed_InterleavedTimestamps();
    void testCanBookmark_MultiFeed_ScrollUpThenDown();
    void testCanBookmark_MultiFeed_RapidBookmarkUpdates();
    void testCanBookmark_MillisecondPrecisionTimestamps();

    // ========== Initiation and cleanup ==========
    void initTestCase();
    void cleanupTestCase();

private:
    LisvelFeedItem* createTestFeed();
    NewsItem* createNewsItem(LisvelFeedItem* feed, qint64 id);
    NewsItem* createNewsItemWithTimestamp(LisvelFeedItem* feed, qint64 id, const QDateTime& timestamp);
};

TestLisvelFeedItem::TestLisvelFeedItem()
{
}

void TestLisvelFeedItem::cleanup()
{
}

LisvelFeedItem* TestLisvelFeedItem::createTestFeed()
{
    return new LisvelFeedItem(
        FEED_ID_ALLNEWS,  // id (special feed)
        0,                // ordinal
        "All News",       // title
        this
    );
}

NewsItem* TestLisvelFeedItem::createNewsItem(LisvelFeedItem* feed, qint64 id)
{
    return createNewsItemWithTimestamp(feed, id, QDateTime::currentDateTime());
}

NewsItem* TestLisvelFeedItem::createNewsItemWithTimestamp(LisvelFeedItem* feed, qint64 id, const QDateTime& timestamp)
{
    return new NewsItem(
        feed,
        id,                                    // dbId
        1,                                     // feedId (doesn't matter for this test)
        QString("News %1").arg(id),            // title
        "Author",                              // author
        "Summary",                             // summary
        "Content",                             // content
        timestamp,                             // timestamp
        QUrl(QString("http://test.com/%1").arg(id)),  // url
        false                                  // pinned
    );
}

void TestLisvelFeedItem::testCanBookmark_NoCurrentBookmark()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Add some news items
    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));

    // No bookmark set (-1), any valid ID in the list should work
    QVERIFY(feed->canBookmark(100, false));
    QVERIFY(feed->canBookmark(101, false));
    QVERIFY(feed->canBookmark(102, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_ProposedNotInList()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    feed->setBookmark(100);

    // ID 999 is not in the list - should be rejected
    QVERIFY(!feed->canBookmark(999, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_ForwardAllowed()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Items at indices: 0=100, 1=101, 2=102
    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));
    feed->setBookmark(100);  // Current bookmark ID 100

    // Forward bookmark (higher ID) should be allowed
    QVERIFY(feed->canBookmark(101, false));  // 101 > 100
    QVERIFY(feed->canBookmark(102, false));  // 102 > 100

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_BackwardRejected()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Items at indices: 0=100, 1=101, 2=102
    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));
    feed->setBookmark(102);  // Current bookmark ID 102

    // Backward bookmark (lower ID) should be rejected
    QVERIFY(!feed->canBookmark(100, false));  // 100 < 102
    QVERIFY(!feed->canBookmark(101, false));  // 101 < 102

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_AllowBackward()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));
    feed->setBookmark(102);  // Current bookmark at index 2

    // With allowBackward=true, backward should be allowed
    QVERIFY(feed->canBookmark(100, true));
    QVERIFY(feed->canBookmark(101, true));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_SameBookmark()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));
    feed->setBookmark(100);

    // Same bookmark should return false (no-op)
    QVERIFY(!feed->canBookmark(100, false));
    QVERIFY(!feed->canBookmark(100, true));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_InvalidID()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));

    // IDs less than -1 should be rejected
    QVERIFY(!feed->canBookmark(-2, false));
    QVERIFY(!feed->canBookmark(-100, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_CurrentNotInList_ForwardAllowed()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Use explicit timestamps to control ordering
    QDateTime baseTime = QDateTime::currentDateTime();
    QDateTime t50 = baseTime.addSecs(-300);   // Item 50: oldest
    QDateTime t100 = baseTime.addSecs(-200);  // Item 100: middle
    QDateTime t101 = baseTime.addSecs(-100);  // Item 101: newest

    // Add item 50 first, set bookmark to capture its NewsPosition
    newsList->append(createNewsItemWithTimestamp(feed, 50, t50));
    feed->setBookmark(50);  // Captures NewsPosition(50, t50)

    // Now "trim" item 50 and add newer items
    newsList->removeAndDelete(true, 1);  // Remove item 50 from start
    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    newsList->append(createNewsItemWithTimestamp(feed, 101, t101));

    // Forward bookmarks should be allowed via NewsPosition comparison
    QVERIFY(feed->canBookmark(100, false));  // t100 > t50
    QVERIFY(feed->canBookmark(101, false));  // t101 > t50

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_CurrentNotInList_BackwardRejected()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Use explicit timestamps to control ordering
    QDateTime baseTime = QDateTime::currentDateTime();
    QDateTime t40 = baseTime.addSecs(-400);   // Item 40: oldest
    QDateTime t50 = baseTime.addSecs(-300);   // Item 50
    QDateTime t60 = baseTime.addSecs(-200);   // Item 60
    QDateTime t100 = baseTime.addSecs(-100);  // Item 100: newest (bookmark)

    // Add item 100 first, set bookmark to capture its NewsPosition
    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    feed->setBookmark(100);  // Captures NewsPosition(100, t100)

    // LISVEL change: removeAndDelete only shrinks the display window, items stay in memory.
    // To test the "current bookmark not in list" scenario, we need to completely clear
    // the list and add different items. This simulates the case where the bookmark item
    // was never loaded (e.g., user is viewing a different part of a very long feed).
    newsList->clear();

    // Add older items - item 100 is now completely gone from the list
    newsList->append(createNewsItemWithTimestamp(feed, 40, t40));
    newsList->append(createNewsItemWithTimestamp(feed, 50, t50));
    newsList->append(createNewsItemWithTimestamp(feed, 60, t60));

    // Verify item 100 is not in the list
    QVERIFY(newsList->fullIndexForItemID(100) < 0);

    // Backward bookmarks should be rejected via NewsPosition comparison
    QVERIFY(!feed->canBookmark(40, false));  // t40 < t100
    QVERIFY(!feed->canBookmark(50, false));  // t50 < t100
    QVERIFY(!feed->canBookmark(60, false));  // t60 < t100

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_AfterForceBackward_RejectsOlderItems()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Initial state: items 100, 101, 102 in list, bookmark at 102
    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));
    feed->setBookmark(102);

    // User force-bookmarks backward to 100
    QVERIFY(feed->canBookmark(100, true));  // allowBackward=true
    feed->setBookmark(100);

    // Now user scrolls up more, older items (40-60) prepended
    // Simulate prepend by inserting at front
    newsList->prepend(createNewsItem(feed, 60));
    newsList->prepend(createNewsItem(feed, 50));
    newsList->prepend(createNewsItem(feed, 40));

    // Bookmark is on ID 100

    // Items with lower IDs (40, 50, 60) should be rejected
    QVERIFY(!feed->canBookmark(40, false));  // 40 < 100
    QVERIFY(!feed->canBookmark(50, false));  // 50 < 100
    QVERIFY(!feed->canBookmark(60, false));  // 60 < 100

    // Items with higher IDs should be allowed
    QVERIFY(feed->canBookmark(101, false));  // 101 > 100
    QVERIFY(feed->canBookmark(102, false));  // 102 > 100

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_AfterPrepend_IndicesShift()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Initial: items 100, 101, 102
    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));
    feed->setBookmark(101);  // Bookmark ID 101

    // Prepend older items - indices shift but ID comparison is unaffected
    newsList->prepend(createNewsItem(feed, 99));
    newsList->prepend(createNewsItem(feed, 98));

    // Bookmark is still ID 101 - ID comparison used

    // Items with lower IDs should be rejected
    QVERIFY(!feed->canBookmark(98, false));   // 98 < 101
    QVERIFY(!feed->canBookmark(99, false));   // 99 < 101
    QVERIFY(!feed->canBookmark(100, false));  // 100 < 101

    // Item with higher ID should be allowed
    QVERIFY(feed->canBookmark(102, false));   // 102 > 101

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_ForceBackwardThenScrollUpWithTrimming()
{
    // This test simulates the full user scenario:
    // 1. Scroll up, view older items
    // 2. Force bookmark backward
    // 3. Scroll up more, items trimmed from bottom
    // 4. Verify older items cannot be bookmarked
    //
    // Uses explicit timestamps to match logical ordering:
    // ID maps to timestamp: ID N -> baseTime + N minutes

    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime baseTime = QDateTime(QDate(2024, 1, 1), QTime(0, 0, 0));

    // Helper lambda to create items with timestamp = baseTime + id minutes
    auto createItem = [&](qint64 id) {
        return createNewsItemWithTimestamp(feed, id, baseTime.addSecs(id * 60));
    };

    // Initial state: items 60-100 loaded (simulating "All News" view)
    for (qint64 id = 60; id <= 100; id++) {
        newsList->append(createItem(id));
    }
    feed->setBookmark(100);  // Bookmark at newest item

    // User scrolls up, views items around 70-80
    // User force-bookmarks item 75
    QVERIFY(feed->canBookmark(75, true));  // allowBackward=true for force
    feed->setBookmark(75);
    QCOMPARE(feed->getBookmarkID(), 75LL);

    // User scrolls up more, items 40-59 prepended (older items)
    for (qint64 id = 59; id >= 40; id--) {
        newsList->prepend(createItem(id));
    }
    // List now has 61 items: 40-100

    // To maintain 60-item limit, remove items from bottom (newest)
    // Remove items 81-100 (20 items)
    newsList->removeAndDelete(false, 20);
    // List now has 41 items: 40-80
    // Bookmark (75) is still in the list at some index

    // Verify: items 40-74 should be rejected (older than bookmark)
    QVERIFY(!feed->canBookmark(40, false));
    QVERIFY(!feed->canBookmark(50, false));
    QVERIFY(!feed->canBookmark(60, false));
    QVERIFY(!feed->canBookmark(74, false));

    // Items 76-80 should be allowed (newer than bookmark)
    QVERIFY(feed->canBookmark(76, false));
    QVERIFY(feed->canBookmark(80, false));

    // Now scroll up even more - bookmark item 75 gets trimmed
    // Prepend items 20-39 (even older items)
    for (qint64 id = 39; id >= 20; id--) {
        newsList->prepend(createItem(id));
    }
    // Remove from bottom to maintain limit
    newsList->removeAndDelete(false, 20);
    // List now has items 20-60 (approximately)
    // Bookmark (75) is NO LONGER in the list!

    // Verify: items in list (20-60) should all be rejected
    // because they're all older than bookmark 75 (by timestamp)
    QVERIFY(!feed->canBookmark(20, false));  // t20 < t75
    QVERIFY(!feed->canBookmark(40, false));  // t40 < t75
    QVERIFY(!feed->canBookmark(60, false));  // t60 < t75

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_TimestampOrdering_IDsReversed()
{
    // This test verifies that (timestamp, id) comparison is used, not just ID.
    // Scenario: Feed A fetched later (higher ID) but has older content (earlier timestamp).
    //
    // Reading order (by timestamp ASC): itemA (8:00) -> itemB (9:00) -> itemC (10:00)
    // ID order: itemC (100) < itemA (200) < itemB (300)
    //
    // If we only compared IDs, bookmarking would be wrong.

    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime time8am = QDateTime(QDate(2024, 1, 1), QTime(8, 0, 0));
    QDateTime time9am = QDateTime(QDate(2024, 1, 1), QTime(9, 0, 0));
    QDateTime time10am = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));

    // Items sorted by (timestamp, id) as they would be in "All News":
    // Index 0: itemA - timestamp 8:00, id 200 (older content, fetched later)
    // Index 1: itemB - timestamp 9:00, id 300 (middle content, fetched last)
    // Index 2: itemC - timestamp 10:00, id 100 (newest content, fetched first)
    NewsItem* itemA = createNewsItemWithTimestamp(feed, 200, time8am);
    NewsItem* itemB = createNewsItemWithTimestamp(feed, 300, time9am);
    NewsItem* itemC = createNewsItemWithTimestamp(feed, 100, time10am);

    newsList->append(itemA);  // index 0, timestamp 8:00
    newsList->append(itemB);  // index 1, timestamp 9:00
    newsList->append(itemC);  // index 2, timestamp 10:00

    // Set bookmark to itemA (earliest in reading order)
    feed->setBookmark(200);  // itemA
    QCOMPARE(feed->getBookmarkID(), 200LL);

    // Forward in reading order = later timestamp -> should be allowed
    QVERIFY(feed->canBookmark(300, false));  // itemB (9:00 > 8:00) - ALLOWED
    QVERIFY(feed->canBookmark(100, false));  // itemC (10:00 > 8:00) - ALLOWED

    // Now set bookmark to itemB (middle)
    feed->setBookmark(300);  // itemB
    QCOMPARE(feed->getBookmarkID(), 300LL);

    // Backward in reading order = earlier timestamp -> should be rejected
    QVERIFY(!feed->canBookmark(200, false));  // itemA (8:00 < 9:00) - REJECTED

    // Forward in reading order -> allowed
    QVERIFY(feed->canBookmark(100, false));  // itemC (10:00 > 9:00) - ALLOWED

    // Set bookmark to itemC (latest in reading order)
    feed->setBookmark(100);  // itemC
    QCOMPARE(feed->getBookmarkID(), 100LL);

    // Both itemA and itemB are earlier in reading order -> rejected
    // (even though their IDs are higher than itemC's ID!)
    QVERIFY(!feed->canBookmark(200, false));  // itemA (8:00 < 10:00) - REJECTED
    QVERIFY(!feed->canBookmark(300, false));  // itemB (9:00 < 10:00) - REJECTED

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_TimestampOrdering_SameTimestamp()
{
    // When timestamps are equal, fall back to ID comparison.
    // This matches the SQL ordering: ORDER BY timestamp ASC, id ASC

    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime sameTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    // Items with same timestamp, different IDs
    NewsItem* item100 = createNewsItemWithTimestamp(feed, 100, sameTime);
    NewsItem* item200 = createNewsItemWithTimestamp(feed, 200, sameTime);
    NewsItem* item300 = createNewsItemWithTimestamp(feed, 300, sameTime);

    newsList->append(item100);  // index 0
    newsList->append(item200);  // index 1
    newsList->append(item300);  // index 2

    // Set bookmark to item200
    feed->setBookmark(200);

    // Same timestamp: use ID comparison
    QVERIFY(!feed->canBookmark(100, false));  // 100 < 200 - REJECTED
    QVERIFY(feed->canBookmark(300, false));   // 300 > 200 - ALLOWED

    delete feed;
}

// ============================================================================
// NewsPosition unit tests
// ============================================================================

void TestLisvelFeedItem::testNewsPosition_DefaultConstruction()
{
    NewsPosition pos;
    QCOMPARE(pos.id(), -1LL);
    QVERIFY(!pos.timestamp().isValid());
    QVERIFY(!pos.isValid());
}

void TestLisvelFeedItem::testNewsPosition_ValidConstruction()
{
    QDateTime time = QDateTime(QDate(2024, 1, 15), QTime(10, 30, 0));
    NewsPosition pos(12345, time);

    QCOMPARE(pos.id(), 12345LL);
    QCOMPARE(pos.timestamp(), time);
    QVERIFY(pos.isValid());
}

void TestLisvelFeedItem::testNewsPosition_IsValid()
{
    QDateTime validTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));
    QDateTime invalidTime;  // Default-constructed QDateTime is invalid

    // Valid: positive ID and valid timestamp
    QVERIFY(NewsPosition(0, validTime).isValid());
    QVERIFY(NewsPosition(100, validTime).isValid());
    QVERIFY(NewsPosition(999999, validTime).isValid());

    // Invalid: negative ID
    QVERIFY(!NewsPosition(-1, validTime).isValid());
    QVERIFY(!NewsPosition(-100, validTime).isValid());

    // Invalid: invalid timestamp
    QVERIFY(!NewsPosition(100, invalidTime).isValid());

    // Invalid: both negative ID and invalid timestamp
    QVERIFY(!NewsPosition(-1, invalidTime).isValid());
}

void TestLisvelFeedItem::testNewsPosition_IsAfter_BothValid()
{
    QDateTime t1 = QDateTime(QDate(2024, 1, 1), QTime(8, 0, 0));
    QDateTime t2 = QDateTime(QDate(2024, 1, 1), QTime(9, 0, 0));
    QDateTime t3 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));

    NewsPosition pos1(100, t1);
    NewsPosition pos2(200, t2);
    NewsPosition pos3(300, t3);

    // Later timestamp is after
    QVERIFY(pos2.isAfter(pos1));  // 9:00 > 8:00
    QVERIFY(pos3.isAfter(pos1));  // 10:00 > 8:00
    QVERIFY(pos3.isAfter(pos2));  // 10:00 > 9:00

    // Earlier timestamp is not after
    QVERIFY(!pos1.isAfter(pos2));  // 8:00 < 9:00
    QVERIFY(!pos1.isAfter(pos3));  // 8:00 < 10:00
    QVERIFY(!pos2.isAfter(pos3));  // 9:00 < 10:00

    // Same position is not after itself
    QVERIFY(!pos1.isAfter(pos1));
    QVERIFY(!pos2.isAfter(pos2));
}

void TestLisvelFeedItem::testNewsPosition_IsAfter_InvalidPositions()
{
    QDateTime validTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));
    NewsPosition valid(100, validTime);
    NewsPosition invalidId(-1, validTime);
    NewsPosition invalidTime(100, QDateTime());
    NewsPosition bothInvalid;

    // Invalid positions always return false
    QVERIFY(!invalidId.isAfter(valid));
    QVERIFY(!invalidTime.isAfter(valid));
    QVERIFY(!bothInvalid.isAfter(valid));

    // Valid position against invalid also returns false
    QVERIFY(!valid.isAfter(invalidId));
    QVERIFY(!valid.isAfter(invalidTime));
    QVERIFY(!valid.isAfter(bothInvalid));

    // Two invalid positions
    QVERIFY(!invalidId.isAfter(invalidTime));
    QVERIFY(!bothInvalid.isAfter(bothInvalid));
}

void TestLisvelFeedItem::testNewsPosition_IsBefore_BothValid()
{
    QDateTime t1 = QDateTime(QDate(2024, 1, 1), QTime(8, 0, 0));
    QDateTime t2 = QDateTime(QDate(2024, 1, 1), QTime(9, 0, 0));
    QDateTime t3 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));

    NewsPosition pos1(100, t1);
    NewsPosition pos2(200, t2);
    NewsPosition pos3(300, t3);

    // Earlier timestamp is before
    QVERIFY(pos1.isBefore(pos2));  // 8:00 < 9:00
    QVERIFY(pos1.isBefore(pos3));  // 8:00 < 10:00
    QVERIFY(pos2.isBefore(pos3));  // 9:00 < 10:00

    // Later timestamp is not before
    QVERIFY(!pos2.isBefore(pos1));  // 9:00 > 8:00
    QVERIFY(!pos3.isBefore(pos1));  // 10:00 > 8:00
    QVERIFY(!pos3.isBefore(pos2));  // 10:00 > 9:00

    // Same position is not before itself
    QVERIFY(!pos1.isBefore(pos1));
    QVERIFY(!pos2.isBefore(pos2));
}

void TestLisvelFeedItem::testNewsPosition_IsBefore_InvalidPositions()
{
    QDateTime validTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));
    NewsPosition valid(100, validTime);
    NewsPosition invalid;

    // Invalid positions always return false
    QVERIFY(!invalid.isBefore(valid));
    QVERIFY(!valid.isBefore(invalid));
    QVERIFY(!invalid.isBefore(invalid));
}

void TestLisvelFeedItem::testNewsPosition_Equality()
{
    QDateTime time1 = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));
    QDateTime time2 = QDateTime(QDate(2024, 1, 1), QTime(13, 0, 0));

    NewsPosition pos1(100, time1);
    NewsPosition pos2(100, time1);  // Same as pos1
    NewsPosition pos3(100, time2);  // Same ID, different timestamp
    NewsPosition pos4(200, time1);  // Different ID, same timestamp
    NewsPosition pos5(200, time2);  // Both different

    // Equality
    QVERIFY(pos1 == pos2);
    QVERIFY(!(pos1 != pos2));

    // Inequality - different timestamp
    QVERIFY(pos1 != pos3);
    QVERIFY(!(pos1 == pos3));

    // Inequality - different ID
    QVERIFY(pos1 != pos4);

    // Inequality - both different
    QVERIFY(pos1 != pos5);

    // Default-constructed positions are equal
    NewsPosition defaultPos1, defaultPos2;
    QVERIFY(defaultPos1 == defaultPos2);
}

void TestLisvelFeedItem::testNewsPosition_SameTimestampDifferentID()
{
    // When timestamps are equal, ID breaks the tie
    QDateTime sameTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    NewsPosition pos100(100, sameTime);
    NewsPosition pos200(200, sameTime);
    NewsPosition pos300(300, sameTime);

    // Higher ID is "after" when timestamps match
    QVERIFY(pos200.isAfter(pos100));
    QVERIFY(pos300.isAfter(pos100));
    QVERIFY(pos300.isAfter(pos200));

    // Lower ID is "before" when timestamps match
    QVERIFY(pos100.isBefore(pos200));
    QVERIFY(pos100.isBefore(pos300));
    QVERIFY(pos200.isBefore(pos300));

    // Equal positions
    QVERIFY(!pos100.isAfter(pos100));
    QVERIFY(!pos100.isBefore(pos100));
}

// ============================================================================
// setBookmark and position capture tests
// ============================================================================

void TestLisvelFeedItem::testSetBookmark_CapturesPosition()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime timestamp = QDateTime(QDate(2024, 1, 15), QTime(14, 30, 0));
    newsList->append(createNewsItemWithTimestamp(feed, 500, timestamp));

    feed->setBookmark(500);

    // Position should be captured
    QVERIFY(feed->getBookmarkPosition().isValid());
    QCOMPARE(feed->getBookmarkPosition().id(), 500LL);
    QCOMPARE(feed->getBookmarkPosition().timestamp(), timestamp);

    delete feed;
}

void TestLisvelFeedItem::testSetBookmark_PreservesPositionWhenItemNotFound()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime t100 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));

    // Add item 100, set bookmark to capture position
    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    feed->setBookmark(100);

    NewsPosition originalPosition = feed->getBookmarkPosition();
    QVERIFY(originalPosition.isValid());
    QCOMPARE(originalPosition.id(), 100LL);
    QCOMPARE(originalPosition.timestamp(), t100);

    // Now set bookmark to item 200 which is NOT in the list
    // Position should be CLEARED (not preserved) to allow proper lazy init
    // with the correct bookmark ID later
    feed->setBookmark(200);

    // Bookmark ID changes, position is cleared
    QCOMPARE(feed->getBookmarkID(), 200LL);
    QVERIFY(!feed->getBookmarkPosition().isValid());

    delete feed;
}

void TestLisvelFeedItem::testSetBookmark_UpdatesPositionWhenItemFound()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime t100 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));
    QDateTime t200 = QDateTime(QDate(2024, 1, 1), QTime(11, 0, 0));

    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    newsList->append(createNewsItemWithTimestamp(feed, 200, t200));

    feed->setBookmark(100);
    QCOMPARE(feed->getBookmarkPosition().id(), 100LL);
    QCOMPARE(feed->getBookmarkPosition().timestamp(), t100);

    // Update to item 200 which IS in the list
    feed->setBookmark(200);
    QCOMPARE(feed->getBookmarkPosition().id(), 200LL);
    QCOMPARE(feed->getBookmarkPosition().timestamp(), t200);

    delete feed;
}

void TestLisvelFeedItem::testSetBookmark_ClearsPositionOnNegativeOne()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime timestamp = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));
    newsList->append(createNewsItemWithTimestamp(feed, 100, timestamp));

    feed->setBookmark(100);
    QVERIFY(feed->getBookmarkPosition().isValid());

    // Clear bookmark with -1
    feed->setBookmark(-1);
    QCOMPARE(feed->getBookmarkID(), -1LL);
    QVERIFY(!feed->getBookmarkPosition().isValid());

    delete feed;
}

void TestLisvelFeedItem::testSetBookmark_LazyInitialization()
{
    // Tests lazy initialization of bookmark position.
    // Scenario: Bookmark was set to an item that later gets trimmed.
    // When we need to compare against it, and the item reappears in the list,
    // the position should be lazy-initialized.

    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime t50 = QDateTime(QDate(2024, 1, 1), QTime(8, 0, 0));
    QDateTime t100 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));
    QDateTime t200 = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    // Add item 50, set bookmark (captures position)
    newsList->append(createNewsItemWithTimestamp(feed, 50, t50));
    feed->setBookmark(50);
    QVERIFY(feed->getBookmarkPosition().isValid());

    // Trim item 50, add items 100, 200
    newsList->removeAndDelete(true, 1);
    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    newsList->append(createNewsItemWithTimestamp(feed, 200, t200));

    // Bookmark (50) not in list, but position preserved
    // canBookmark uses NewsPosition comparison
    QVERIFY(feed->canBookmark(100, false));  // t100 > t50
    QVERIFY(feed->canBookmark(200, false));  // t200 > t50

    // Now simulate item 50 reappearing (e.g., user scrolled back)
    newsList->prepend(createNewsItemWithTimestamp(feed, 50, t50));

    // Bookmark IS in list now, so index comparison is used
    // Item 100 is at index > item 50's index, so allowed
    QVERIFY(feed->canBookmark(100, false));
    QVERIFY(feed->canBookmark(200, false));

    delete feed;
}

// ============================================================================
// getBookmarkPosition tests
// ============================================================================

void TestLisvelFeedItem::testGetBookmarkPosition_InitiallyInvalid()
{
    LisvelFeedItem* feed = createTestFeed();

    // Initially, no bookmark, position should be invalid
    QCOMPARE(feed->getBookmarkID(), -1LL);
    QVERIFY(!feed->getBookmarkPosition().isValid());

    delete feed;
}

void TestLisvelFeedItem::testGetBookmarkPosition_ValidAfterSetBookmark()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime timestamp = QDateTime(QDate(2024, 6, 15), QTime(9, 45, 30));
    newsList->append(createNewsItemWithTimestamp(feed, 777, timestamp));

    feed->setBookmark(777);

    const NewsPosition& pos = feed->getBookmarkPosition();
    QVERIFY(pos.isValid());
    QCOMPARE(pos.id(), 777LL);
    QCOMPARE(pos.timestamp(), timestamp);

    delete feed;
}

void TestLisvelFeedItem::testGetBookmarkPosition_PreservedAfterTrim()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime t100 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));
    QDateTime t200 = QDateTime(QDate(2024, 1, 1), QTime(11, 0, 0));
    QDateTime t300 = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    newsList->append(createNewsItemWithTimestamp(feed, 200, t200));
    newsList->append(createNewsItemWithTimestamp(feed, 300, t300));

    feed->setBookmark(200);
    NewsPosition originalPosition = feed->getBookmarkPosition();

    // Trim from both ends, removing the bookmark item
    newsList->removeAndDelete(true, 1);   // Remove item 100
    newsList->removeAndDelete(false, 1);  // Remove item 300
    // Only item 200 remains... then remove it too
    newsList->removeAndDelete(true, 1);

    // List is now empty, but position should be preserved
    QCOMPARE(newsList->size(), 0LL);
    QCOMPARE(feed->getBookmarkPosition(), originalPosition);
    QVERIFY(feed->getBookmarkPosition().isValid());

    delete feed;
}

// ============================================================================
// Edge cases
// ============================================================================

void TestLisvelFeedItem::testCanBookmark_EmptyList()
{
    LisvelFeedItem* feed = createTestFeed();

    // Empty list, no bookmark (-1)
    // When there's no bookmark, canBookmark returns true for any valid ID
    // (this allows setting the initial bookmark)
    QVERIFY(feed->canBookmark(100, false));  // Allowed - no existing bookmark

    // Set a bookmark (won't capture position since item not in list)
    feed->setBookmark(50);

    // Now there IS a bookmark (50), and proposed (100) is not in list
    QVERIFY(!feed->canBookmark(100, false));  // Rejected - not in list

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_SingleItemList()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));

    // No bookmark yet
    QVERIFY(feed->canBookmark(100, false));

    // Set bookmark to only item
    feed->setBookmark(100);

    // Same item should be rejected
    QVERIFY(!feed->canBookmark(100, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_BookmarkAtListStart()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));

    feed->setBookmark(100);  // Bookmark at start (index 0)

    // All items after should be allowed
    QVERIFY(feed->canBookmark(101, false));
    QVERIFY(feed->canBookmark(102, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_BookmarkAtListEnd()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));
    newsList->append(createNewsItem(feed, 101));
    newsList->append(createNewsItem(feed, 102));

    feed->setBookmark(102);  // Bookmark at end (index 2)

    // All items before should be rejected
    QVERIFY(!feed->canBookmark(100, false));
    QVERIFY(!feed->canBookmark(101, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_ProposedIDNegativeOne()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    newsList->append(createNewsItem(feed, 100));
    feed->setBookmark(100);

    // -1 is valid (clears bookmark) and should be allowed
    // Actually, checking the implementation: -1 is >= -1, so it passes that check
    // But it won't be in the list, so it should be rejected
    QVERIFY(!feed->canBookmark(-1, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_MultipleTrimCycles()
{
    // Simulate multiple scroll-up cycles with trimming
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime baseTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    // Initial load: items 50-59
    for (int i = 50; i < 60; i++) {
        newsList->append(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }
    feed->setBookmark(55);

    // First scroll up: prepend 40-49, trim 55-59
    for (int i = 49; i >= 40; i--) {
        newsList->prepend(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }
    newsList->removeAndDelete(false, 5);  // Remove 55-59

    // Bookmark (55) is now trimmed
    QCOMPARE(feed->getBookmarkID(), 55LL);
    QVERIFY(feed->getBookmarkPosition().isValid());

    // Items 40-54 should all be rejected (before bookmark position)
    for (int i = 40; i < 55; i++) {
        QVERIFY2(!feed->canBookmark(i, false),
                 qPrintable(QString("ID %1 should be rejected").arg(i)));
    }

    // Second scroll up: prepend 30-39, trim 50-54
    for (int i = 39; i >= 30; i--) {
        newsList->prepend(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }
    newsList->removeAndDelete(false, 5);  // Remove 50-54

    // Items 30-49 should still be rejected
    for (int i = 30; i < 50; i++) {
        QVERIFY2(!feed->canBookmark(i, false),
                 qPrintable(QString("ID %1 should be rejected after second trim").arg(i)));
    }

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_PositionPreservedAcrossMultipleSetBookmarks()
{
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime t100 = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));
    QDateTime t200 = QDateTime(QDate(2024, 1, 1), QTime(11, 0, 0));

    newsList->append(createNewsItemWithTimestamp(feed, 100, t100));
    newsList->append(createNewsItemWithTimestamp(feed, 200, t200));

    // Set bookmark to 200
    feed->setBookmark(200);
    QCOMPARE(feed->getBookmarkPosition().timestamp(), t200);

    // Trim item 200
    newsList->removeAndDelete(false, 1);

    // Try to set bookmark to 300 (not in list)
    // Position should be CLEARED (not preserved) to avoid stale data with wrong ID
    feed->setBookmark(300);
    QCOMPARE(feed->getBookmarkID(), 300LL);
    QVERIFY(!feed->getBookmarkPosition().isValid());  // Position cleared

    // Item 100 should still be rejected (no valid position for comparison,
    // and bookmark item 300 can't be found for lazy init, so fall through to reject)
    QVERIFY(!feed->canBookmark(100, false));

    delete feed;
}

void TestLisvelFeedItem::testSetBookmark_ItemOutsideDisplayWindow_PositionCaptured()
{
    // This test verifies that setBookmark can capture the position for items
    // that have been trimmed from the display window but still exist in the
    // full NewsList memory. This is critical for force-bookmark functionality.
    //
    // Scenario:
    // 1. User scrolls way up, items are prepended
    // 2. User force-bookmarks an old item (which is in display window)
    // 3. User scrolls back down, old items get trimmed from display window
    // 4. Bookmark item is now outside display window but still in memory
    // 5. Regular bookmark proposals should be rejected because they're newer

    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime baseTime = QDateTime(QDate(2024, 1, 1), QTime(0, 0, 0));

    // Add items 100-109 (timestamps are ID minutes from baseTime)
    for (int i = 100; i < 110; i++) {
        newsList->append(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }

    // Set bookmark to item 103 (index 3)
    feed->setBookmark(103);
    QCOMPARE(feed->getBookmarkID(), 103LL);
    QVERIFY(feed->getBookmarkPosition().isValid());
    QCOMPARE(feed->getBookmarkPosition().id(), 103LL);

    // Shrink display window from start (simulating scroll down - old items trimmed)
    // Items 100-104 are now outside display window but still in memory
    newsList->shrinkDisplayWindow(true, 5);

    // Display window is now [5, 10) meaning items 105-109 are visible
    QCOMPARE(newsList->size(), 5);
    QCOMPARE(newsList->fullSize(), 10);

    // The bookmark item (103) is now OUTSIDE the display window
    QVERIFY(newsList->newsItemForID(103) == nullptr);  // Not in display window
    QVERIFY(newsList->fullNewsItemForID(103) != nullptr);  // But in full list

    // Critical: the position should still be valid because it was captured
    // when the bookmark was set (the item was in memory)
    QVERIFY(feed->getBookmarkPosition().isValid());
    QCOMPARE(feed->getBookmarkPosition().id(), 103LL);

    // Now try to re-set the bookmark to item 103 (simulating force-bookmark
    // when the item is outside display window but in memory)
    feed->setBookmark(103);

    // The position should STILL be captured from the full list
    QVERIFY(feed->getBookmarkPosition().isValid());
    QCOMPARE(feed->getBookmarkPosition().id(), 103LL);
    QCOMPARE(feed->getBookmarkPosition().timestamp(), baseTime.addSecs(103 * 60));

    // Items in display window (105-109) are all newer than bookmark (103)
    // and should be allowed to advance the bookmark
    QVERIFY(feed->canBookmark(105, false));  // 105 > 103
    QVERIFY(feed->canBookmark(109, false));  // 109 > 103

    // If we had an item older than 103 in the display window, it would be rejected
    // But items 100-104 are outside display window, so canBookmark won't find them

    delete feed;
}

// ============================================================================
// Realistic multi-feed scenarios
// ============================================================================

void TestLisvelFeedItem::testCanBookmark_MultiFeed_InterleavedTimestamps()
{
    // Simulates "All News" with items from multiple feeds interleaved by timestamp
    // Feed A: tech blog updated twice daily
    // Feed B: news site updated hourly
    // Feed C: rarely updated blog
    //
    // IDs are assigned in fetch order, not publication order

    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Publication timestamps
    QDateTime jan1_8am = QDateTime(QDate(2024, 1, 1), QTime(8, 0, 0));
    QDateTime jan1_9am = QDateTime(QDate(2024, 1, 1), QTime(9, 0, 0));
    QDateTime jan1_10am = QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0));
    QDateTime jan1_11am = QDateTime(QDate(2024, 1, 1), QTime(11, 0, 0));
    QDateTime jan1_12pm = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    // Items fetched in this order (IDs assigned sequentially):
    // ID 1000: Feed A post from 10am (fetched first)
    // ID 1001: Feed B post from 8am (fetched second - older content!)
    // ID 1002: Feed B post from 9am (fetched third)
    // ID 1003: Feed C post from 12pm (fetched fourth - newest content)
    // ID 1004: Feed A post from 11am (fetched last)

    // Sorted by (timestamp, id) for "All News" view:
    newsList->append(createNewsItemWithTimestamp(feed, 1001, jan1_8am));   // index 0
    newsList->append(createNewsItemWithTimestamp(feed, 1002, jan1_9am));   // index 1
    newsList->append(createNewsItemWithTimestamp(feed, 1000, jan1_10am));  // index 2
    newsList->append(createNewsItemWithTimestamp(feed, 1004, jan1_11am));  // index 3
    newsList->append(createNewsItemWithTimestamp(feed, 1003, jan1_12pm));  // index 4

    // User reads up to 10am item (ID 1000)
    feed->setBookmark(1000);

    // ID-only comparison would be WRONG here:
    // - ID 1001 > 1000 would be allowed (but it's 8am, before 10am!)
    // - ID 1002 > 1000 would be allowed (but it's 9am, before 10am!)

    // With timestamp comparison:
    QVERIFY(!feed->canBookmark(1001, false));  // 8am < 10am - REJECTED
    QVERIFY(!feed->canBookmark(1002, false));  // 9am < 10am - REJECTED
    QVERIFY(feed->canBookmark(1004, false));   // 11am > 10am - ALLOWED
    QVERIFY(feed->canBookmark(1003, false));   // 12pm > 10am - ALLOWED

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_MultiFeed_ScrollUpThenDown()
{
    // User scrolls up to read older items, then scrolls back down
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime baseTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    // Initial load: items 50-70
    for (int i = 50; i <= 70; i++) {
        newsList->append(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }
    feed->setBookmark(60);

    // User scrolls up - prepend 30-49, trim 60-70
    for (int i = 49; i >= 30; i--) {
        newsList->prepend(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }
    newsList->removeAndDelete(false, 11);  // Remove 60-70

    // Bookmark 60 is now trimmed, position preserved

    // All visible items (30-59) should be rejected
    QVERIFY(!feed->canBookmark(30, false));
    QVERIFY(!feed->canBookmark(45, false));
    QVERIFY(!feed->canBookmark(59, false));

    // User scrolls back down - trim 30-39, append 60-80
    newsList->removeAndDelete(true, 10);  // Remove 30-39
    for (int i = 60; i <= 80; i++) {
        newsList->append(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }

    // Items >= 61 should be allowed (after bookmark timestamp)
    QVERIFY(feed->canBookmark(61, false));
    QVERIFY(feed->canBookmark(70, false));
    QVERIFY(feed->canBookmark(80, false));

    // Items < 60 should still be rejected
    QVERIFY(!feed->canBookmark(40, false));
    QVERIFY(!feed->canBookmark(59, false));

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_MultiFeed_RapidBookmarkUpdates()
{
    // Simulates rapid scrolling where bookmarks update frequently
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime baseTime = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0));

    // Load items 1-100
    for (int i = 1; i <= 100; i++) {
        newsList->append(createNewsItemWithTimestamp(feed, i, baseTime.addSecs(i * 60)));
    }

    // Rapid scrolling down: 10, 20, 30, ..., 90
    for (int bookmark = 10; bookmark <= 90; bookmark += 10) {
        QVERIFY(feed->canBookmark(bookmark, false));
        feed->setBookmark(bookmark);

        // Verify position was captured
        QCOMPARE(feed->getBookmarkPosition().id(), (qint64)bookmark);

        // All items before should be rejected
        QVERIFY(!feed->canBookmark(bookmark - 5, false));

        // All items after should be allowed
        QVERIFY(feed->canBookmark(bookmark + 5, false));
    }

    delete feed;
}

void TestLisvelFeedItem::testCanBookmark_MillisecondPrecisionTimestamps()
{
    // Test that millisecond differences are handled correctly
    LisvelFeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    QDateTime t1 = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0, 0));
    QDateTime t2 = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0, 1));    // 1ms later
    QDateTime t3 = QDateTime(QDate(2024, 1, 1), QTime(12, 0, 0, 999));  // 999ms later

    newsList->append(createNewsItemWithTimestamp(feed, 100, t1));
    newsList->append(createNewsItemWithTimestamp(feed, 200, t2));
    newsList->append(createNewsItemWithTimestamp(feed, 300, t3));

    feed->setBookmark(200);  // 1ms mark

    // 0ms should be rejected (before 1ms)
    QVERIFY(!feed->canBookmark(100, false));

    // 999ms should be allowed (after 1ms)
    QVERIFY(feed->canBookmark(300, false));

    delete feed;
}

// ============================================================================
// Test setup and teardown
// ============================================================================

void TestLisvelFeedItem::initTestCase()
{
    // Called before first test
}

void TestLisvelFeedItem::cleanupTestCase()
{
    // Called after last test
}

QTEST_MAIN(TestLisvelFeedItem)

#include "tst_lisvelfeeditem.moc"
