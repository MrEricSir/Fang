#include <QTest>
#include <QSignalSpy>
#include "../../src/models/FeedItem.h"
#include "../../src/models/NewsItem.h"

/**
 * Verify FeedItem model
 */
class TestFeedItem : public QObject
{
    Q_OBJECT

public:
    TestFeedItem();

private slots:
    void initTestCase();
    void cleanup();

    // Constructor
    void testDefaultConstructor();
    void testParameterizedConstructor();

    // Role names
    void testRoleNames();

    // Data
    void testDataMethodAllRoles();
    void testSetDataMethod();

    // Getters
    void testGetters();

    // Setters & signals
    void testSetIsUpdating();
    void testSetImageURL();
    void testSetTitle();
    void testSetDropTarget();
    void testSetIsSelected();
    void testSetParentFolder();
    void testSetFolderOpen();
    void testSetUnreadCount();
    void testSetOrdinal();
    void testSetErrorFlag();
    void testSetURL();

    // Bookmark
    void testBookmarkInitialState();
    void testSetBookmark();
    void testCanBookmark_NoCurrentBookmark();
    void testCanBookmark_SameBookmark();
    void testCanBookmark_ForwardOnly();
    void testCanBookmark_AllowBackward();
    void testCanBookmark_InvalidID();
    void testBookmarksEnabled();

    // Special feed
    void testIsSpecialFeed();

    // Ordinal comparison
    void testOrdinalComparison();

    // News list integration
    void testClearNews();
    void testFirstNewsID();

    // Flags test
    void testFlags();

private:
    FeedItem* createTestFeed();
};

TestFeedItem::TestFeedItem()
{
}

void TestFeedItem::initTestCase()
{
}

void TestFeedItem::cleanup()
{
}

FeedItem* TestFeedItem::createTestFeed()
{
    return new FeedItem(
        1,                                          // id
        0,                                          // ordinal
        "Test Feed",                                // title
        "Test Subtitle",                            // subtitle
        QDateTime::currentDateTime(),               // lastUpdated
        60,                                         // minutesToUpdate
        QUrl("http://example.com/feed.xml"),        // url
        QUrl("http://example.com"),                 // siteURL
        "http://example.com/feed.xml",              // userURL
        QUrl("http://example.com/icon.png"),        // imageURL
        QDateTime::currentDateTime(),               // lastIconUpdate
        -1,                                         // parentFolder
        true,                                       // folderOpen
        this
    );
}

void TestFeedItem::testDefaultConstructor()
{
    FeedItem* feed = new FeedItem(this);

    QCOMPARE(feed->getDbID(), 0LL);
    QCOMPARE(feed->getOrdinal(), -1);
    QCOMPARE(feed->getTitle(), QString(""));
    QCOMPARE(feed->getSubtitle(), QString(""));
    QCOMPARE(feed->getMinutesToUpdate(), 0u);
    QCOMPARE(feed->getIsUpdating(), 0);
    QCOMPARE(feed->getUnreadCount(), 0u);
    QCOMPARE(feed->getDropTarget(), QString("none"));
    QCOMPARE(feed->getErrorFlag(), false);
    QCOMPARE(feed->getIsSelected(), false);
    QCOMPARE(feed->getBookmarkID(), -1LL);
    QCOMPARE(feed->getFirstNewsID(), -1LL);
    QCOMPARE(feed->getParentFolderID(), -1LL);

    delete feed;
}

void TestFeedItem::testParameterizedConstructor()
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime iconUpdate = now.addDays(-1);

    FeedItem* feed = new FeedItem(
        42,                                         // id
        5,                                          // ordinal
        "My Feed",                                  // title
        "Feed Description",                         // subtitle
        now,                                        // lastUpdated
        120,                                        // minutesToUpdate
        QUrl("http://test.com/rss"),                // url
        QUrl("http://test.com"),                    // siteURL
        "http://test.com/rss",                      // userURL
        QUrl("http://test.com/favicon.ico"),        // imageURL
        iconUpdate,                                 // lastIconUpdate
        10,                                         // parentFolder
        false,                                      // folderOpen
        this
    );

    QCOMPARE(feed->getDbID(), 42LL);
    QCOMPARE(feed->getOrdinal(), 5);
    QCOMPARE(feed->getTitle(), QString("My Feed"));
    QCOMPARE(feed->getSubtitle(), QString("Feed Description"));
    QCOMPARE(feed->getLastUpdated(), now);
    QCOMPARE(feed->getMinutesToUpdate(), 120u);
    QCOMPARE(feed->getURL(), QUrl("http://test.com/rss"));
    QCOMPARE(feed->getSiteURL(), QUrl("http://test.com"));
    QCOMPARE(feed->getUserURL(), QString("http://test.com/rss"));
    QCOMPARE(feed->getImageURL(), QUrl("http://test.com/favicon.ico"));
    QCOMPARE(feed->getLastIconUpdate(), iconUpdate);
    QCOMPARE(feed->getParentFolderID(), 10LL);
    QVERIFY(!feed->data(FeedItem::FolderOpenRole).toBool());

    delete feed;
}

void TestFeedItem::testRoleNames()
{
    FeedItem* feed = createTestFeed();
    QHash<int, QByteArray> roles = feed->roleNames();

    QCOMPARE(roles[FeedItem::TitleRole], QByteArray("title"));
    QCOMPARE(roles[FeedItem::SubtitleRole], QByteArray("subtitle"));
    QCOMPARE(roles[FeedItem::LastUpdatedRole], QByteArray("lastUpdated"));
    QCOMPARE(roles[FeedItem::MinutesToUpdateRole], QByteArray("minutesToUpdate"));
    QCOMPARE(roles[FeedItem::UrlRole], QByteArray("url"));
    QCOMPARE(roles[FeedItem::SiteURLRole], QByteArray("siteURL"));
    QCOMPARE(roles[FeedItem::ImageURLRole], QByteArray("imageURL"));
    QCOMPARE(roles[FeedItem::IsUpdatingRole], QByteArray("isUpdating"));
    QCOMPARE(roles[FeedItem::SelfRole], QByteArray("self"));
    QCOMPARE(roles[FeedItem::UnreadCountRole], QByteArray("unreadCount"));
    QCOMPARE(roles[FeedItem::DropTargetRole], QByteArray("dropTarget"));
    QCOMPARE(roles[FeedItem::ErrorFlagRole], QByteArray("errorFlag"));
    QCOMPARE(roles[FeedItem::IsSelectedRole], QByteArray("isSelected"));
    QCOMPARE(roles[FeedItem::IsSpecialFeedRole], QByteArray("isSpecialFeed"));
    QCOMPARE(roles[FeedItem::IsFolderRole], QByteArray("isFolder"));
    QCOMPARE(roles[FeedItem::ParentFolderRole], QByteArray("parentFolder"));
    QCOMPARE(roles[FeedItem::FolderOpenRole], QByteArray("folderOpen"));
    QCOMPARE(roles[FeedItem::BookmarksEnabledRole], QByteArray("bookmarksEnabled"));
    QCOMPARE(roles[FeedItem::UIDRole], QByteArray("uid"));

    delete feed;
}

void TestFeedItem::testDataMethodAllRoles()
{
    FeedItem* feed = createTestFeed();

    QCOMPARE(feed->data(FeedItem::TitleRole).toString(), QString("Test Feed"));
    QCOMPARE(feed->data(FeedItem::SubtitleRole).toString(), QString("Test Subtitle"));
    QVERIFY(feed->data(FeedItem::LastUpdatedRole).toDateTime().isValid());
    QCOMPARE(feed->data(FeedItem::MinutesToUpdateRole).toUInt(), 60u);
    QCOMPARE(feed->data(FeedItem::UrlRole).toUrl(), QUrl("http://example.com/feed.xml"));
    QCOMPARE(feed->data(FeedItem::SiteURLRole).toUrl(), QUrl("http://example.com"));
    QCOMPARE(feed->data(FeedItem::ImageURLRole).toUrl(), QUrl("http://example.com/icon.png"));
    QCOMPARE(feed->data(FeedItem::IsUpdatingRole).toInt(), 0);
    QCOMPARE(feed->data(FeedItem::UnreadCountRole).toUInt(), 0u);
    QCOMPARE(feed->data(FeedItem::DropTargetRole).toString(), QString("none"));
    QCOMPARE(feed->data(FeedItem::ErrorFlagRole).toBool(), false);
    QCOMPARE(feed->data(FeedItem::IsSelectedRole).toBool(), false);
    QCOMPARE(feed->data(FeedItem::IsSpecialFeedRole).toBool(), false);
    QCOMPARE(feed->data(FeedItem::IsFolderRole).toBool(), false);
    QCOMPARE(feed->data(FeedItem::ParentFolderRole).toLongLong(), -1LL);
    QCOMPARE(feed->data(FeedItem::FolderOpenRole).toBool(), true);
    QCOMPARE(feed->data(FeedItem::BookmarksEnabledRole).toBool(), true);
    QCOMPARE(feed->data(FeedItem::UIDRole).toLongLong(), 1LL);

    // Self should be pointed back to itself.
    FeedItem* self = qvariant_cast<FeedItem*>(feed->data(FeedItem::SelfRole));
    QCOMPARE(self, feed);

    delete feed;
}

void TestFeedItem::testSetDataMethod()
{
    FeedItem* feed = createTestFeed();

    // DropTargetRole
    QVERIFY(feed->setData(QVariant("testTarget"), FeedItem::DropTargetRole));
    QCOMPARE(feed->getDropTarget(), QString("testTarget"));

    // IsSelectedRole
    QVERIFY(feed->setData(QVariant(true), FeedItem::IsSelectedRole));
    QCOMPARE(feed->getIsSelected(), true);

    // ParentFolderRole
    QVERIFY(feed->setData(QVariant(5LL), FeedItem::ParentFolderRole));
    QCOMPARE(feed->getParentFolderID(), 5LL);

    // FolderOpenRole
    QVERIFY(feed->setData(QVariant(false), FeedItem::FolderOpenRole));
    QCOMPARE(feed->data(FeedItem::FolderOpenRole).toBool(), false);

    // Test invalid role
    QVERIFY(!feed->setData(QVariant("test"), FeedItem::TitleRole));

    delete feed;
}

void TestFeedItem::testGetters()
{
    FeedItem* feed = createTestFeed();

    QCOMPARE(feed->getTitle(), QString("Test Feed"));
    QCOMPARE(feed->getSubtitle(), QString("Test Subtitle"));
    QVERIFY(feed->getLastUpdated().isValid());
    QCOMPARE(feed->getMinutesToUpdate(), 60u);
    QCOMPARE(feed->getURL(), QUrl("http://example.com/feed.xml"));
    QCOMPARE(feed->getSiteURL(), QUrl("http://example.com"));
    QCOMPARE(feed->getUserURL(), QString("http://example.com/feed.xml"));
    QCOMPARE(feed->getImageURL(), QUrl("http://example.com/icon.png"));
    QCOMPARE(feed->getIsUpdating(), 0);
    QCOMPARE(feed->getUnreadCount(), 0u);
    QCOMPARE(feed->getDropTarget(), QString("none"));
    QCOMPARE(feed->getSelf(), feed);
    QCOMPARE(feed->getDbID(), 1LL);
    QVERIFY(!feed->isFolder());

    delete feed;
}

void TestFeedItem::testSetIsUpdating()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setIsUpdating(true);

    QCOMPARE(feed->getIsUpdating(), 1);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetImageURL()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    QUrl newURL("http://newsite.com/icon.png");
    feed->setImageURL(newURL);

    QCOMPARE(feed->getImageURL(), newURL);
    QCOMPARE(spy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setImageURL(newURL);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetTitle()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy dataChangedSpy(feed, &FeedItem::dataChanged);
    QSignalSpy titleChangedSpy(feed, &FeedItem::titleChanged);

    feed->setTitle("New Title");

    QCOMPARE(feed->getTitle(), QString("New Title"));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(titleChangedSpy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setTitle("New Title");
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(titleChangedSpy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetDropTarget()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setDropTarget("newTarget");

    QCOMPARE(feed->getDropTarget(), QString("newTarget"));
    QCOMPARE(spy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setDropTarget("newTarget");
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetIsSelected()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setIsSelected(true);

    QCOMPARE(feed->getIsSelected(), true);
    QCOMPARE(spy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setIsSelected(true);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetParentFolder()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setParentFolder(5);

    QCOMPARE(feed->getParentFolderID(), 5LL);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetFolderOpen()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setFolderOpen(false);

    QCOMPARE(feed->data(FeedItem::FolderOpenRole).toBool(), false);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetUnreadCount()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy dataChangedSpy(feed, &FeedItem::dataChanged);
    QSignalSpy unreadCountChangedSpy(feed, &FeedItem::unreadCountChanged);

    feed->setUnreadCount(42);

    QCOMPARE(feed->getUnreadCount(), 42u);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(unreadCountChangedSpy.count(), 1);
    QCOMPARE(unreadCountChangedSpy.at(0).at(0).toUInt(), 42u);

    // Setting to same value shouldn't repeat changed signal.
    feed->setUnreadCount(42);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(unreadCountChangedSpy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetOrdinal()
{
    FeedItem* feed = createTestFeed();

    feed->setOrdinal(10);

    QCOMPARE(feed->getOrdinal(), 10);

    delete feed;
}

void TestFeedItem::testSetErrorFlag()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setErrorFlag(true);

    QCOMPARE(feed->getErrorFlag(), true);
    QCOMPARE(spy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setErrorFlag(true);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testSetURL()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    QUrl newURL("http://exampletwo.com/feed.xml");
    feed->setURL(newURL);

    QCOMPARE(feed->getURL(), newURL);
    QCOMPARE(spy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setURL(newURL);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testBookmarkInitialState()
{
    FeedItem* feed = createTestFeed();

    QCOMPARE(feed->getBookmarkID(), -1LL);

    delete feed;
}

void TestFeedItem::testSetBookmark()
{
    FeedItem* feed = createTestFeed();
    QSignalSpy spy(feed, &FeedItem::dataChanged);

    feed->setBookmark(100);

    QCOMPARE(feed->getBookmarkID(), 100LL);
    QCOMPARE(spy.count(), 1);

    // Setting to same value shouldn't repeat changed signal.
    feed->setBookmark(100);
    QCOMPARE(spy.count(), 1);

    delete feed;
}

void TestFeedItem::testCanBookmark_NoCurrentBookmark()
{
    FeedItem* feed = createTestFeed();

    // With no current bookmark, any valid ID should work.
    QVERIFY(feed->canBookmark(0, false));
    QVERIFY(feed->canBookmark(100, false));
    QVERIFY(feed->canBookmark(1000, true));

    delete feed;
}

void TestFeedItem::testCanBookmark_SameBookmark()
{
    FeedItem* feed = createTestFeed();
    feed->setBookmark(100);

    // Setting the same bookmark should return false.
    QVERIFY(!feed->canBookmark(100, false));
    QVERIFY(!feed->canBookmark(100, true));

    delete feed;
}

void TestFeedItem::testCanBookmark_ForwardOnly()
{
    FeedItem* feed = createTestFeed();
    feed->setBookmark(100);

    // Only allow increasing IDs.
    QVERIFY(feed->canBookmark(101, false));
    QVERIFY(feed->canBookmark(200, false));
    QVERIFY(!feed->canBookmark(99, false));
    QVERIFY(!feed->canBookmark(50, false));

    delete feed;
}

void TestFeedItem::testCanBookmark_AllowBackward()
{
    FeedItem* feed = createTestFeed();
    feed->setBookmark(100);

    // Allow backward mode; allow any IDs.
    QVERIFY(feed->canBookmark(101, true));
    QVERIFY(feed->canBookmark(99, true));
    QVERIFY(feed->canBookmark(50, true));
    QVERIFY(feed->canBookmark(200, true));

    delete feed;
}

void TestFeedItem::testCanBookmark_InvalidID()
{
    FeedItem* feed = createTestFeed();

    // IDs less than -1 should be rejected
    QVERIFY(!feed->canBookmark(-2, false));
    QVERIFY(!feed->canBookmark(-100, false));
    QVERIFY(!feed->canBookmark(-2, true));

    // -1 is valid (clear bookmark)
    QVERIFY(feed->canBookmark(-1, false));

    delete feed;
}

void TestFeedItem::testBookmarksEnabled()
{
    FeedItem* feed = createTestFeed();

    // Default implementation should return true
    QVERIFY(feed->bookmarksEnabled());

    delete feed;
}

void TestFeedItem::testIsSpecialFeed()
{
    // Normal feed (positive ID)
    FeedItem* normalFeed = new FeedItem(1, 0, "Normal", "", QDateTime::currentDateTime(), 60,
                                        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
                                        -1, true, this);
    QVERIFY(!normalFeed->isSpecialFeed());
    delete normalFeed;

    // AllNews feed (negative ID)
    FeedItem* allNewsFeed = new FeedItem(FEED_ID_ALLNEWS, 0, "All News", "", QDateTime::currentDateTime(), 60,
                                         QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
                                         -1, true, this);
    QVERIFY(allNewsFeed->isSpecialFeed());
    delete allNewsFeed;

    // Pinned feed (negative ID)
    FeedItem* pinnedFeed = new FeedItem(FEED_ID_PINNED, 0, "Pinned", "", QDateTime::currentDateTime(), 60,
                                        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
                                        -1, true, this);
    QVERIFY(pinnedFeed->isSpecialFeed());
    delete pinnedFeed;
}

void TestFeedItem::testOrdinalComparison()
{
    FeedItem* feed1 = new FeedItem(1, 5, "Feed 1", "", QDateTime::currentDateTime(), 60,
                                   QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
                                   -1, true, this);
    FeedItem* feed2 = new FeedItem(2, 10, "Feed 2", "", QDateTime::currentDateTime(), 60,
                                   QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
                                   -1, true, this);
    FeedItem* feed3 = new FeedItem(3, 3, "Feed 3", "", QDateTime::currentDateTime(), 60,
                                   QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(),
                                   -1, true, this);

    // Test ordinal-based comparison
    QVERIFY(*feed1 < *feed2);    // 5 < 10
    QVERIFY(*feed3 < *feed1);    // 3 < 5
    QVERIFY(!(*feed2 < *feed1)); // !(10 < 5)

    delete feed1;
    delete feed2;
    delete feed3;
}

void TestFeedItem::testClearNews()
{
    FeedItem* feed = createTestFeed();
    NewsList* newsList = feed->getNewsList();

    // Add some news items
    NewsItem* news1 = new NewsItem(feed, 1, feed->getDbID(), "News 1", "Author", "Summary", "Content",
                                   QDateTime::currentDateTime(), QUrl("http://test.com/1"), false);
    NewsItem* news2 = new NewsItem(feed, 2, feed->getDbID(), "News 2", "Author", "Summary", "Content",
                                   QDateTime::currentDateTime(), QUrl("http://test.com/2"), false);
    newsList->append(news1);
    newsList->append(news2);

    QCOMPARE(newsList->size(), 2);

    // Clear news
    feed->clearNews();

    QCOMPARE(newsList->size(), 0);
    QVERIFY(newsList->isEmpty());

    delete feed;
}

void TestFeedItem::testFirstNewsID()
{
    FeedItem* feed = createTestFeed();

    QCOMPARE(feed->getFirstNewsID(), -1LL);

    feed->setFirstNewsID(42);
    QCOMPARE(feed->getFirstNewsID(), 42LL);

    delete feed;
}

void TestFeedItem::testFlags()
{
    FeedItem* feed = createTestFeed();

    Qt::ItemFlags flags = feed->flags();

    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);
    QVERIFY(flags & Qt::ItemIsEditable);

    delete feed;
}

QTEST_MAIN(TestFeedItem)

#include "tst_feeditem.moc"
