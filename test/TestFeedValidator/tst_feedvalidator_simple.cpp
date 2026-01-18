#include <QtTest>
#include <QSignalSpy>
#include <QVariantList>
#include <QVariantMap>

// Standalone test class that mimics FeedValidator's data management logic
// This allows us to test the core logic without pulling in FeedDiscovery,
// network stack, or FangApp dependencies.
class SimpleFeedValidator : public QObject
{
    Q_OBJECT

public:
    SimpleFeedValidator() {}

    struct FeedInfo {
        QString url;
        QString title;
        bool selected;
        int discoveryIndex;
    };

    // Public interface matching FeedValidator
    QString url() const { return _url; }
    void setUrl(const QString& url) {
        if (url != _url) {
            _url = url;
            emit urlChanged(_url);
        }
    }

    int feedCount() const { return _feeds.count(); }

    int feedsToAddCount() const {
        int count = 0;
        for (const FeedInfo& feedInfo : _feeds) {
            if (feedInfo.selected && !feedInfo.title.isEmpty()) {
                count++;
            }
        }
        return count;
    }

    QVariantList discoveredFeeds() const {
        QVariantList result;
        for (int i = 0; i < _feeds.count(); i++) {
            const FeedInfo& info = _feeds[i];
            QVariantMap feedMap;
            feedMap["url"] = info.url;
            feedMap["title"] = info.title;
            feedMap["selected"] = info.selected;
            feedMap["index"] = i;
            result.append(feedMap);
        }
        return result;
    }

    void setFeedSelected(int index, bool selected) {
        if (index >= 0 && index < _feeds.count()) {
            _feeds[index].selected = selected;
            emit feedsToAddCountChanged();
        }
    }

    void setFeedTitle(int index, const QString& title) {
        if (index >= 0 && index < _feeds.count()) {
            _feeds[index].title = title;
            emit feedsToAddCountChanged();
        }
    }

    // Test helper
    void addTestFeed(const QString& url, const QString& title, bool selected, int discoveryIndex = 0) {
        FeedInfo info;
        info.url = url;
        info.title = title;
        info.selected = selected;
        info.discoveryIndex = discoveryIndex;
        _feeds.append(info);
        emit feedCountChanged();
    }

signals:
    void urlChanged(QString url);
    void feedCountChanged();
    void feedsToAddCountChanged();

private:
    QString _url;
    QList<FeedInfo> _feeds;
};

class TestFeedValidatorSimple : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    // Test cases
    void testInitialState();
    void testSetUrl();
    void testSetUrlNoChange();
    void testFeedCountEmpty();
    void testFeedCountMultiple();
    void testSetFeedSelectedValid();
    void testSetFeedSelectedInvalid();
    void testSetFeedTitleValid();
    void testSetFeedTitleInvalid();
    void testFeedsToAddCountNoneSelected();
    void testFeedsToAddCountAllSelected();
    void testFeedsToAddCountEmptyTitle();
    void testDiscoveredFeedsEmpty();
    void testDiscoveredFeedsMultiple();
    void testDiscoveredFeedsStructure();

private:
    SimpleFeedValidator* validator;
};

void TestFeedValidatorSimple::init()
{
    validator = new SimpleFeedValidator();
}

void TestFeedValidatorSimple::cleanup()
{
    delete validator;
    validator = nullptr;
}

void TestFeedValidatorSimple::testInitialState()
{
    QCOMPARE(validator->url(), QString(""));
    QCOMPARE(validator->feedCount(), 0);
    QCOMPARE(validator->feedsToAddCount(), 0);
    QCOMPARE(validator->discoveredFeeds().count(), 0);
}

void TestFeedValidatorSimple::testSetUrl()
{
    QSignalSpy spy(validator, &SimpleFeedValidator::urlChanged);

    validator->setUrl("http://example.com/feed");

    QCOMPARE(validator->url(), QString("http://example.com/feed"));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QString("http://example.com/feed"));
}

void TestFeedValidatorSimple::testSetUrlNoChange()
{
    validator->setUrl("http://example.com");
    QSignalSpy spy(validator, &SimpleFeedValidator::urlChanged);

    // Set same URL again
    validator->setUrl("http://example.com");

    // Should not emit signal
    QCOMPARE(spy.count(), 0);
}

void TestFeedValidatorSimple::testFeedCountEmpty()
{
    QCOMPARE(validator->feedCount(), 0);
}

void TestFeedValidatorSimple::testFeedCountMultiple()
{
    validator->addTestFeed("http://example.com/feed1", "Feed 1", true, 0);
    validator->addTestFeed("http://example.com/feed2", "Feed 2", true, 1);
    validator->addTestFeed("http://example.com/feed3", "Feed 3", false, 2);

    QCOMPARE(validator->feedCount(), 3);
}

void TestFeedValidatorSimple::testSetFeedSelectedValid()
{
    validator->addTestFeed("http://example.com/feed", "Test Feed", false, 0);

    QSignalSpy spy(validator, &SimpleFeedValidator::feedsToAddCountChanged);

    // Select the feed
    validator->setFeedSelected(0, true);

    QCOMPARE(spy.count(), 1);

    // Deselect the feed
    validator->setFeedSelected(0, false);
    QCOMPARE(spy.count(), 2);
}

void TestFeedValidatorSimple::testSetFeedSelectedInvalid()
{
    QSignalSpy spy(validator, &SimpleFeedValidator::feedsToAddCountChanged);

    validator->setFeedSelected(-1, true);
    QCOMPARE(spy.count(), 0);

    validator->setFeedSelected(100, true);
    QCOMPARE(spy.count(), 0);
}

void TestFeedValidatorSimple::testSetFeedTitleValid()
{
    validator->addTestFeed("http://example.com/feed", "Original Title", true, 0);

    QSignalSpy spy(validator, &SimpleFeedValidator::feedsToAddCountChanged);

    validator->setFeedTitle(0, "New Title");

    QCOMPARE(spy.count(), 1);
}

void TestFeedValidatorSimple::testSetFeedTitleInvalid()
{
    QSignalSpy spy(validator, &SimpleFeedValidator::feedsToAddCountChanged);

    validator->setFeedTitle(-1, "Test");
    QCOMPARE(spy.count(), 0);

    validator->setFeedTitle(100, "Test");
    QCOMPARE(spy.count(), 0);
}

void TestFeedValidatorSimple::testFeedsToAddCountNoneSelected()
{
    validator->addTestFeed("http://example.com/feed1", "Feed 1", false, 0);
    validator->addTestFeed("http://example.com/feed2", "Feed 2", false, 1);

    QCOMPARE(validator->feedsToAddCount(), 0);
}

void TestFeedValidatorSimple::testFeedsToAddCountAllSelected()
{
    validator->addTestFeed("http://example.com/feed1", "Feed 1", true, 0);
    validator->addTestFeed("http://example.com/feed2", "Feed 2", true, 1);
    validator->addTestFeed("http://example.com/feed3", "Feed 3", true, 2);

    QCOMPARE(validator->feedsToAddCount(), 3);
}

void TestFeedValidatorSimple::testFeedsToAddCountEmptyTitle()
{
    // This is the bug we fixed - empty titles should not be counted
    validator->addTestFeed("http://example.com/feed1", "Feed 1", true, 0);
    validator->addTestFeed("http://example.com/feed2", "", true, 1);  // Empty title
    validator->addTestFeed("http://example.com/feed3", "Feed 3", false, 2);

    // Only Feed 1 should be counted (selected AND has title)
    QCOMPARE(validator->feedsToAddCount(), 1);
}

void TestFeedValidatorSimple::testDiscoveredFeedsEmpty()
{
    QVariantList feeds = validator->discoveredFeeds();
    QCOMPARE(feeds.count(), 0);
}

void TestFeedValidatorSimple::testDiscoveredFeedsMultiple()
{
    validator->addTestFeed("http://example.com/feed1", "Feed 1", true, 0);
    validator->addTestFeed("http://example.com/feed2", "Feed 2", false, 1);

    QVariantList feeds = validator->discoveredFeeds();
    QCOMPARE(feeds.count(), 2);
}

void TestFeedValidatorSimple::testDiscoveredFeedsStructure()
{
    // Test that QVariantList is structured correctly for QML
    validator->addTestFeed("http://example.com/feed1", "Feed 1", true, 0);
    validator->addTestFeed("http://example.com/feed2", "Feed 2", false, 1);

    QVariantList feeds = validator->discoveredFeeds();

    // Verify first feed
    QVariantMap feed1 = feeds[0].toMap();
    QCOMPARE(feed1["url"].toString(), QString("http://example.com/feed1"));
    QCOMPARE(feed1["title"].toString(), QString("Feed 1"));
    QCOMPARE(feed1["selected"].toBool(), true);
    QCOMPARE(feed1["index"].toInt(), 0);

    // Verify second feed
    QVariantMap feed2 = feeds[1].toMap();
    QCOMPARE(feed2["url"].toString(), QString("http://example.com/feed2"));
    QCOMPARE(feed2["title"].toString(), QString("Feed 2"));
    QCOMPARE(feed2["selected"].toBool(), false);
    QCOMPARE(feed2["index"].toInt(), 1);
}

QTEST_MAIN(TestFeedValidatorSimple)
#include "tst_feedvalidator_simple.moc"
