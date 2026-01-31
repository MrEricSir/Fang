#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QSettings>

#include "../../src/utilities/UpdateChecker.h"
#include "../MockNewsParser.h"
#include "../MockFangSettings.h"

/*!
    \brief Testable subclass that exposes private methods for unit testing.
 */
class TestableUpdateChecker : public UpdateChecker
{
public:
    explicit TestableUpdateChecker(QObject *parent = nullptr,
                                   ParserInterface* parser = nullptr,
                                   SettingsInterface* settings = nullptr)
        : UpdateChecker(parent, parser, settings) {}

    // Expose private methods for testing
    QString testExtractVersion(const QString& title) {
        return extractVersion(title);
    }

    bool testIsNewerVersion(const QString& currentVersion, const QString& newVersion) {
        return isNewerVersion(currentVersion, newVersion);
    }
};

class TestUpdateChecker : public QObject
{
    Q_OBJECT

public:
    TestUpdateChecker();

private slots:
    void init();
    void cleanup();

    // extractVersion tests
    void testExtractVersion_standardFormat();
    void testExtractVersion_betaFormat();
    void testExtractVersion_betaWithNumber();
    void testExtractVersion_releaseCandidate();
    void testExtractVersion_noVersion();
    void testExtractVersion_differentPrefix();

    // isNewerVersion tests
    void testIsNewerVersion_majorHigher();
    void testIsNewerVersion_minorHigher();
    void testIsNewerVersion_patchHigher();
    void testIsNewerVersion_sameVersion();
    void testIsNewerVersion_olderVersion();
    void testIsNewerVersion_releaseVsBeta();
    void testIsNewerVersion_betaVsRelease();
    void testIsNewerVersion_betaVersions();
    void testIsNewerVersion_sameBeta();

    // Integration tests with mock parser
    void testUpdateAvailable_emitsSignal();
    void testUpdateAvailable_noSignalIfSameVersion();
    void testUpdateAvailable_noSignalIfOlderVersion();
    void testUpdateAvailable_noSignalIfAlreadyShown();
    void testUpdateAvailable_parserError();
    void testUpdateAvailable_emptyFeed();
    void testUpdateAvailable_invalidTitle();

private:
    TestableUpdateChecker* checker;
    MockFangSettings* mockSettings;
};

TestUpdateChecker::TestUpdateChecker()
    : checker(nullptr),
      mockSettings(nullptr)
{
}

void TestUpdateChecker::init()
{
    // Create a MockFangSettings instance for tests that need it
    mockSettings = new MockFangSettings();
}

void TestUpdateChecker::cleanup()
{
    if (checker) {
        delete checker;
        checker = nullptr;
    }

    if (mockSettings) {
        delete mockSettings;
        mockSettings = nullptr;
    }
}

// ============================================================================
// extractVersion tests
// ============================================================================

void TestUpdateChecker::testExtractVersion_standardFormat()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QCOMPARE(checker->testExtractVersion("Fang 1.2.3"), QString("1.2.3"));
}

void TestUpdateChecker::testExtractVersion_betaFormat()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QCOMPARE(checker->testExtractVersion("Fang 0.2.9-beta"), QString("0.2.9-beta"));
}

void TestUpdateChecker::testExtractVersion_betaWithNumber()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QCOMPARE(checker->testExtractVersion("Fang 0.2.10-beta.1"), QString("0.2.10-beta.1"));
}

void TestUpdateChecker::testExtractVersion_releaseCandidate()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QCOMPARE(checker->testExtractVersion("Fang 1.0.0-rc.2"), QString("1.0.0-rc.2"));
}

void TestUpdateChecker::testExtractVersion_noVersion()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QCOMPARE(checker->testExtractVersion("Some random title"), QString(""));
}

void TestUpdateChecker::testExtractVersion_differentPrefix()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    // Should not match different app names
    QCOMPARE(checker->testExtractVersion("OtherApp 1.2.3"), QString(""));
}

// ============================================================================
// isNewerVersion tests
// ============================================================================

void TestUpdateChecker::testIsNewerVersion_majorHigher()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QVERIFY(checker->testIsNewerVersion("1.0.0", "2.0.0"));
}

void TestUpdateChecker::testIsNewerVersion_minorHigher()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QVERIFY(checker->testIsNewerVersion("1.0.0", "1.1.0"));
}

void TestUpdateChecker::testIsNewerVersion_patchHigher()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QVERIFY(checker->testIsNewerVersion("1.0.0", "1.0.1"));
}

void TestUpdateChecker::testIsNewerVersion_sameVersion()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QVERIFY(!checker->testIsNewerVersion("1.0.0", "1.0.0"));
}

void TestUpdateChecker::testIsNewerVersion_olderVersion()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QVERIFY(!checker->testIsNewerVersion("2.0.0", "1.0.0"));
}

void TestUpdateChecker::testIsNewerVersion_releaseVsBeta()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    // Release (no suffix) should be newer than beta with same version number
    QVERIFY(checker->testIsNewerVersion("1.0.0-beta", "1.0.0"));
}

void TestUpdateChecker::testIsNewerVersion_betaVsRelease()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    // Beta should NOT be newer than release with same version number
    QVERIFY(!checker->testIsNewerVersion("1.0.0", "1.0.0-beta"));
}

void TestUpdateChecker::testIsNewerVersion_betaVersions()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    // beta.2 should be newer than beta.1
    QVERIFY(checker->testIsNewerVersion("1.0.0-beta.1", "1.0.0-beta.2"));
}

void TestUpdateChecker::testIsNewerVersion_sameBeta()
{
    MockNewsParser* mockParser = new MockNewsParser();
    checker = new TestableUpdateChecker(nullptr, mockParser);
    QVERIFY(!checker->testIsNewerVersion("1.0.0-beta.1", "1.0.0-beta.1"));
}

// ============================================================================
// Integration tests with mock parser
// ============================================================================

void TestUpdateChecker::testUpdateAvailable_emitsSignal()
{
    MockNewsParser* mockParser = new MockNewsParser();

    // Create feed with newer version
    RawFeed* feed = new RawFeed();
    RawNews* news = new RawNews(feed);
    news->title = "Fang 99.0.0"; // Much higher than any real version
    feed->items.append(news);

    mockParser->setResult(ParserInterface::OK);
    mockParser->setFeed(feed);

    // Pass mockSettings so update check can proceed
    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    // Wait for async signal
    QVERIFY(spy.wait(1000));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("99.0.0"));
}

void TestUpdateChecker::testUpdateAvailable_noSignalIfSameVersion()
{
    MockNewsParser* mockParser = new MockNewsParser();

    RawFeed* feed = new RawFeed();
    RawNews* news = new RawNews(feed);
    news->title = QString("Fang ") + APP_VERSION; // Same as current
    feed->items.append(news);

    mockParser->setResult(ParserInterface::OK);
    mockParser->setFeed(feed);

    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    // Give it time to process, but signal should not be emitted
    QTest::qWait(500);
    QCOMPARE(spy.count(), 0);
}

void TestUpdateChecker::testUpdateAvailable_noSignalIfOlderVersion()
{
    MockNewsParser* mockParser = new MockNewsParser();

    RawFeed* feed = new RawFeed();
    RawNews* news = new RawNews(feed);
    news->title = "Fang 0.0.1"; // Very old version
    feed->items.append(news);

    mockParser->setResult(ParserInterface::OK);
    mockParser->setFeed(feed);

    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    QTest::qWait(500);
    QCOMPARE(spy.count(), 0);
}

void TestUpdateChecker::testUpdateAvailable_noSignalIfAlreadyShown()
{
    // Pre-mark version as shown via MockFangSettings
    mockSettings->setLastSeenVersion("99.0.0");

    MockNewsParser* mockParser = new MockNewsParser();

    RawFeed* feed = new RawFeed();
    RawNews* news = new RawNews(feed);
    news->title = "Fang 99.0.0";
    feed->items.append(news);

    mockParser->setResult(ParserInterface::OK);
    mockParser->setFeed(feed);

    // Pass mockSettings to UpdateChecker
    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    QTest::qWait(500);
    QCOMPARE(spy.count(), 0); // Should not emit since already shown
}

void TestUpdateChecker::testUpdateAvailable_parserError()
{
    MockNewsParser* mockParser = new MockNewsParser();
    mockParser->setResult(ParserInterface::NETWORK_ERROR);

    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    QTest::qWait(500);
    QCOMPARE(spy.count(), 0);
}

void TestUpdateChecker::testUpdateAvailable_emptyFeed()
{
    MockNewsParser* mockParser = new MockNewsParser();

    RawFeed* feed = new RawFeed();
    // No items in feed

    mockParser->setResult(ParserInterface::OK);
    mockParser->setFeed(feed);

    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    QTest::qWait(500);
    QCOMPARE(spy.count(), 0);
}

void TestUpdateChecker::testUpdateAvailable_invalidTitle()
{
    MockNewsParser* mockParser = new MockNewsParser();

    RawFeed* feed = new RawFeed();
    RawNews* news = new RawNews(feed);
    news->title = "Some random title without version"; // No parseable version
    feed->items.append(news);

    mockParser->setResult(ParserInterface::OK);
    mockParser->setFeed(feed);

    checker = new TestableUpdateChecker(nullptr, mockParser, mockSettings);
    QSignalSpy spy(checker, &UpdateChecker::updateAvailable);

    checker->checkNow();

    QTest::qWait(500);
    QCOMPARE(spy.count(), 0);
}

QTEST_MAIN(TestUpdateChecker)

#include "tst_updatechecker.moc"
