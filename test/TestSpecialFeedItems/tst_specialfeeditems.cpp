#include <QTest>
#include <QSignalSpy>
#include "../../src/models/PinnedFeedItem.h"
#include "../../src/models/AllNewsFeedItem.h"
#include "../../src/models/SearchFeedItem.h"
#include "../../src/models/FolderFeedItem.h"
#include "../../src/models/ListModel.h"

/**
 * Verify PinnedFeedItem, AllNewsFeedItem, SearchFeedItem, and FolderFeedItem.
 */
class TestSpecialFeedItems : public QObject
{
    Q_OBJECT

public:
    TestSpecialFeedItems();

private slots:
    void initTestCase();
    void cleanup();

    // PinnedFeedItem
    void testPinned_constructor();
    void testPinned_canBookmark_alwaysFalse();
    void testPinned_bookmarksEnabled_false();

    // AllNewsFeedItem
    void testAllNews_constructor();
    void testAllNews_bookmarksEnabled();

    // SearchFeedItem
    void testSearch_constructor();
    void testSearch_setSearchQuery();
    void testSearch_setSearchQuery_whitespace();
    void testSearch_setSearchQuery_empty();
    void testSearch_hasSearchQuery();
    void testSearch_setScope_global();
    void testSearch_setScope_feed();
    void testSearch_setScope_folder();
    void testSearch_canBookmark_alwaysFalse();
    void testSearch_bookmarksEnabled_false();
    void testSearch_isSearchFeed();

    // FolderFeedItem
    void testFolder_constructor();
    void testFolder_isFolder();
    void testFolder_folderOpen_initialTrue();
    void testFolder_folderOpen_initialFalse();
    void testFolder_isSpecialFeed();
};

TestSpecialFeedItems::TestSpecialFeedItems()
{
}

void TestSpecialFeedItems::initTestCase()
{
}

void TestSpecialFeedItems::cleanup()
{
}

// PinnedFeedItem

void TestSpecialFeedItems::testPinned_constructor()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    PinnedFeedItem* pinned = new PinnedFeedItem(feedList);

    QCOMPARE(pinned->getDbID(), static_cast<qint64>(FEED_ID_PINNED));
    QCOMPARE(pinned->getTitle(), QString("Pinned"));
    QVERIFY(pinned->isSpecialFeed());

    delete feedList;
}

void TestSpecialFeedItems::testPinned_canBookmark_alwaysFalse()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    PinnedFeedItem* pinned = new PinnedFeedItem(feedList);

    QVERIFY(!pinned->canBookmark(0, false));
    QVERIFY(!pinned->canBookmark(100, false));
    QVERIFY(!pinned->canBookmark(0, true));
    QVERIFY(!pinned->canBookmark(100, true));

    delete feedList;
}

void TestSpecialFeedItems::testPinned_bookmarksEnabled_false()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    PinnedFeedItem* pinned = new PinnedFeedItem(feedList);

    QVERIFY(!pinned->bookmarksEnabled());

    delete feedList;
}

// AllNewsFeedItem

void TestSpecialFeedItems::testAllNews_constructor()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    QCOMPARE(allNews->getDbID(), static_cast<qint64>(FEED_ID_ALLNEWS));
    QCOMPARE(allNews->getTitle(), QString("All News"));
    QVERIFY(allNews->isSpecialFeed());

    delete feedList;
}

void TestSpecialFeedItems::testAllNews_bookmarksEnabled()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);

    // AllNewsFeedItem inherits FeedItem::bookmarksEnabled() which returns true
    QVERIFY(allNews->bookmarksEnabled());

    delete feedList;
}

// SearchFeedItem

void TestSpecialFeedItems::testSearch_constructor()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    QCOMPARE(search->getDbID(), static_cast<qint64>(FEED_ID_SEARCH));
    QCOMPARE(search->getTitle(), QString("Search Results"));
    QVERIFY(search->isSpecialFeed());

    delete feedList;
}

void TestSpecialFeedItems::testSearch_setSearchQuery()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    search->setSearchQuery("test query");
    QCOMPARE(search->getSearchQuery(), QString("test query"));
    QCOMPARE(search->getTitle(), QString("Search Results"));

    delete feedList;
}

void TestSpecialFeedItems::testSearch_setSearchQuery_whitespace()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    search->setSearchQuery("  hello world  ");
    QCOMPARE(search->getSearchQuery(), QString("hello world"));

    delete feedList;
}

void TestSpecialFeedItems::testSearch_setSearchQuery_empty()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    search->setSearchQuery("");
    QVERIFY(!search->hasSearchQuery());

    delete feedList;
}

void TestSpecialFeedItems::testSearch_hasSearchQuery()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    QVERIFY(!search->hasSearchQuery());

    search->setSearchQuery("something");
    QVERIFY(search->hasSearchQuery());

    search->setSearchQuery("");
    QVERIFY(!search->hasSearchQuery());

    delete feedList;
}

void TestSpecialFeedItems::testSearch_setScope_global()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    // Default scope is Global
    QCOMPARE(search->getScope(), SearchFeedItem::Scope::Global);
    QCOMPARE(search->getScopeId(), -1LL);

    delete feedList;
}

void TestSpecialFeedItems::testSearch_setScope_feed()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    search->setScope(SearchFeedItem::Scope::Feed, 42);
    QCOMPARE(search->getScope(), SearchFeedItem::Scope::Feed);
    QCOMPARE(search->getScopeId(), 42LL);

    delete feedList;
}

void TestSpecialFeedItems::testSearch_setScope_folder()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    search->setScope(SearchFeedItem::Scope::Folder, 10);
    QCOMPARE(search->getScope(), SearchFeedItem::Scope::Folder);
    QCOMPARE(search->getScopeId(), 10LL);

    delete feedList;
}

void TestSpecialFeedItems::testSearch_canBookmark_alwaysFalse()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    QVERIFY(!search->canBookmark(0, false));
    QVERIFY(!search->canBookmark(100, true));

    delete feedList;
}

void TestSpecialFeedItems::testSearch_bookmarksEnabled_false()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    QVERIFY(!search->bookmarksEnabled());

    delete feedList;
}

void TestSpecialFeedItems::testSearch_isSearchFeed()
{
    ListModel* feedList = new ListModel(new FeedItem(), nullptr);
    SearchFeedItem* search = new SearchFeedItem(feedList);

    QCOMPARE(search->data(FeedItem::IsSearchFeedRole).toBool(), true);

    delete feedList;
}

// FolderFeedItem

void TestSpecialFeedItems::testFolder_constructor()
{
    FolderFeedItem* folder = new FolderFeedItem(100, 5, "My Folder", true, nullptr);

    QCOMPARE(folder->getDbID(), 100LL);
    QCOMPARE(folder->getOrdinal(), 5);
    QCOMPARE(folder->getTitle(), QString("My Folder"));

    delete folder;
}

void TestSpecialFeedItems::testFolder_isFolder()
{
    FolderFeedItem* folder = new FolderFeedItem(1, 0, "Folder", true, nullptr);

    QVERIFY(folder->isFolder());

    delete folder;
}

void TestSpecialFeedItems::testFolder_folderOpen_initialTrue()
{
    FolderFeedItem* folder = new FolderFeedItem(1, 0, "Folder", true, nullptr);

    QCOMPARE(folder->data(FeedItem::FolderOpenRole).toBool(), true);

    delete folder;
}

void TestSpecialFeedItems::testFolder_folderOpen_initialFalse()
{
    FolderFeedItem* folder = new FolderFeedItem(1, 0, "Folder", false, nullptr);

    QCOMPARE(folder->data(FeedItem::FolderOpenRole).toBool(), false);

    delete folder;
}

void TestSpecialFeedItems::testFolder_isSpecialFeed()
{
    // Positive ID - not a special feed
    FolderFeedItem* normalFolder = new FolderFeedItem(1, 0, "Normal", true, nullptr);
    QVERIFY(!normalFolder->isSpecialFeed());
    delete normalFolder;

    // Negative ID - is a special feed
    FolderFeedItem* specialFolder = new FolderFeedItem(-5, 0, "Special", true, nullptr);
    QVERIFY(specialFolder->isSpecialFeed());
    delete specialFolder;
}

QTEST_MAIN(TestSpecialFeedItems)

#include "tst_specialfeeditems.moc"
