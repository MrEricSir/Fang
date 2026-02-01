#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QSettings>
#include <QGuiApplication>
#include <QStyleHints>

#include "../../src/models/FangSettings.h"
#include "../MockDBSettings.h"

class TestFangSettings : public QObject
{
    Q_OBJECT

public:
    TestFangSettings();

private slots:
    void init();
    void cleanup();

    // Constructor tests
    void testConstructor_defaultState();

    // Style property tests
    void testGetStyle_defaultValue();
    void testSetStyle_changesValue();
    void testSetStyle_emitsSignal();
    void testSetStyle_sameValueNoSignal();
    void testSetStyle_emitsCurrentStyleChanged();

    // CurrentStyle property tests
    void testGetCurrentStyle_whenLight();
    void testGetCurrentStyle_whenDark();
    void testGetCurrentStyle_whenDefault();

    // FontSize property tests
    void testGetFontSize_defaultValue();
    void testSetFontSize_changesValue();
    void testSetFontSize_emitsSignal();
    void testSetFontSize_sameValueNoSignal();

    // CacheLength property tests
    void testGetCacheLength_delegatesToDBSettings();
    void testSetCacheLength_delegatesToDBSettings();
    void testCacheLength_dbSettingChangedEmitsSignal();

    // Refresh property tests
    void testGetRefresh_defaultValue();
    void testSetRefresh_changesValue();
    void testSetRefresh_emitsSignal();
    void testSetRefresh_sameValueNoSignal();

    // LastSeenVersion property tests
    void testGetLastSeenVersion_defaultValue();
    void testSetLastSeenVersion_changesValue();
    void testSetLastSeenVersion_emitsSignal();
    void testSetLastSeenVersion_sameValueNoSignal();

    // ShowTrayIcon property tests
    void testGetShowTrayIcon_defaultValue();
    void testSetShowTrayIcon_changesValue();
    void testSetShowTrayIcon_emitsSignal();
    void testSetShowTrayIcon_sameValueNoSignal();

    // colorSchemeToString tests
    void testColorSchemeToString_dark();
    void testColorSchemeToString_light();
    void testColorSchemeToString_unknown();

    // init tests
    void testInit_connectsDBSettings();

private:
    FangSettings* settings;
    MockDBSettings* mockDBSettings;

    void clearTestSettings();
};

TestFangSettings::TestFangSettings()
    : settings(nullptr),
      mockDBSettings(nullptr)
{
}

void TestFangSettings::clearTestSettings()
{
    // Clear any persisted settings from previous test runs
    QSettings qsettings;
    qsettings.beginGroup("FangSettings");
    qsettings.remove("");
    qsettings.endGroup();
}

void TestFangSettings::init()
{
    clearTestSettings();
    mockDBSettings = new MockDBSettings();
    settings = new FangSettings();
    settings->init(mockDBSettings);
}

void TestFangSettings::cleanup()
{
    if (settings) {
        delete settings;
        settings = nullptr;
    }

    if (mockDBSettings) {
        delete mockDBSettings;
        mockDBSettings = nullptr;
    }

    clearTestSettings();
}

// ============================================================================
// Constructor tests
// ============================================================================

void TestFangSettings::testConstructor_defaultState()
{
    // Verify FangSettings can be constructed without crashing
    FangSettings* s = new FangSettings();
    QVERIFY(s != nullptr);
    delete s;
}

// ============================================================================
// Style property tests
// ============================================================================

void TestFangSettings::testGetStyle_defaultValue()
{
    QCOMPARE(settings->getStyle(), QString("DEFAULT"));
}

void TestFangSettings::testSetStyle_changesValue()
{
    settings->setStyle("DARK");
    QCOMPARE(settings->getStyle(), QString("DARK"));
}

void TestFangSettings::testSetStyle_emitsSignal()
{
    QSignalSpy spy(settings, &FangSettings::styleChanged);

    settings->setStyle("LIGHT");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("LIGHT"));
}

void TestFangSettings::testSetStyle_sameValueNoSignal()
{
    // First set to a known value
    settings->setStyle("DARK");

    QSignalSpy spy(settings, &FangSettings::styleChanged);

    // Set to same value again
    settings->setStyle("DARK");

    QCOMPARE(spy.count(), 0);
}

void TestFangSettings::testSetStyle_emitsCurrentStyleChanged()
{
    QSignalSpy spy(settings, &FangSettings::currentStyleChanged);

    settings->setStyle("DARK");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("DARK"));
}

// ============================================================================
// CurrentStyle property tests
// ============================================================================

void TestFangSettings::testGetCurrentStyle_whenLight()
{
    settings->setStyle("LIGHT");
    QCOMPARE(settings->getCurrentStyle(), QString("LIGHT"));
}

void TestFangSettings::testGetCurrentStyle_whenDark()
{
    settings->setStyle("DARK");
    QCOMPARE(settings->getCurrentStyle(), QString("DARK"));
}

void TestFangSettings::testGetCurrentStyle_whenDefault()
{
    settings->setStyle("DEFAULT");
    // getCurrentStyle should return either "LIGHT" or "DARK" based on system
    QString current = settings->getCurrentStyle();
    QVERIFY(current == "LIGHT" || current == "DARK");
}

// ============================================================================
// FontSize property tests
// ============================================================================

void TestFangSettings::testGetFontSize_defaultValue()
{
    QCOMPARE(settings->getFontSize(), QString("MEDIUM"));
}

void TestFangSettings::testSetFontSize_changesValue()
{
    settings->setFontSize("LARGE");
    QCOMPARE(settings->getFontSize(), QString("LARGE"));
}

void TestFangSettings::testSetFontSize_emitsSignal()
{
    QSignalSpy spy(settings, &FangSettings::fontSizeChanged);

    settings->setFontSize("SMALL");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("SMALL"));
}

void TestFangSettings::testSetFontSize_sameValueNoSignal()
{
    settings->setFontSize("LARGE");

    QSignalSpy spy(settings, &FangSettings::fontSizeChanged);

    settings->setFontSize("LARGE");

    QCOMPARE(spy.count(), 0);
}

// ============================================================================
// CacheLength property tests
// ============================================================================

void TestFangSettings::testGetCacheLength_delegatesToDBSettings()
{
    // Set value in mock DB
    mockDBSettings->set(CACHE_LENGTH, "1WEEK");

    QCOMPARE(settings->getCacheLength(), QString("1WEEK"));
}

void TestFangSettings::testSetCacheLength_delegatesToDBSettings()
{
    settings->setCacheLength("1MONTH");

    QCOMPARE(mockDBSettings->get(CACHE_LENGTH), QString("1MONTH"));
}

void TestFangSettings::testCacheLength_dbSettingChangedEmitsSignal()
{
    QSignalSpy spy(settings, &FangSettings::cacheLengthChanged);

    // Simulate DB setting change (e.g., from another source)
    mockDBSettings->set(CACHE_LENGTH, "3MONTHS");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("3MONTHS"));
}

// ============================================================================
// Refresh property tests
// ============================================================================

void TestFangSettings::testGetRefresh_defaultValue()
{
    QCOMPARE(settings->getRefresh(), QString("10MIN"));
}

void TestFangSettings::testSetRefresh_changesValue()
{
    settings->setRefresh("1HOUR");
    QCOMPARE(settings->getRefresh(), QString("1HOUR"));
}

void TestFangSettings::testSetRefresh_emitsSignal()
{
    QSignalSpy spy(settings, &FangSettings::refreshChanged);

    settings->setRefresh("30MIN");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("30MIN"));
}

void TestFangSettings::testSetRefresh_sameValueNoSignal()
{
    settings->setRefresh("1MIN");

    QSignalSpy spy(settings, &FangSettings::refreshChanged);

    settings->setRefresh("1MIN");

    QCOMPARE(spy.count(), 0);
}

// ============================================================================
// LastSeenVersion property tests
// ============================================================================

void TestFangSettings::testGetLastSeenVersion_defaultValue()
{
    QCOMPARE(settings->getLastSeenVersion(), QString(""));
}

void TestFangSettings::testSetLastSeenVersion_changesValue()
{
    settings->setLastSeenVersion("1.2.3");
    QCOMPARE(settings->getLastSeenVersion(), QString("1.2.3"));
}

void TestFangSettings::testSetLastSeenVersion_emitsSignal()
{
    QSignalSpy spy(settings, &FangSettings::lastSeenVersionChanged);

    settings->setLastSeenVersion("2.0.0");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toString(), QString("2.0.0"));
}

void TestFangSettings::testSetLastSeenVersion_sameValueNoSignal()
{
    settings->setLastSeenVersion("1.0.0");

    QSignalSpy spy(settings, &FangSettings::lastSeenVersionChanged);

    settings->setLastSeenVersion("1.0.0");

    QCOMPARE(spy.count(), 0);
}

// ============================================================================
// ShowTrayIcon property tests
// ============================================================================

void TestFangSettings::testGetShowTrayIcon_defaultValue()
{
#if defined(Q_OS_WIN)
    QCOMPARE(settings->getShowTrayIcon(), true);
#else
    QCOMPARE(settings->getShowTrayIcon(), false);
#endif
}

void TestFangSettings::testSetShowTrayIcon_changesValue()
{
    bool newValue = !settings->getShowTrayIcon();
    settings->setShowTrayIcon(newValue);
    QCOMPARE(settings->getShowTrayIcon(), newValue);
}

void TestFangSettings::testSetShowTrayIcon_emitsSignal()
{
    bool newValue = !settings->getShowTrayIcon();
    QSignalSpy spy(settings, &FangSettings::showTrayIconChanged);

    settings->setShowTrayIcon(newValue);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toBool(), newValue);
}

void TestFangSettings::testSetShowTrayIcon_sameValueNoSignal()
{
    bool currentValue = settings->getShowTrayIcon();

    QSignalSpy spy(settings, &FangSettings::showTrayIconChanged);

    settings->setShowTrayIcon(currentValue);

    QCOMPARE(spy.count(), 0);
}

// ============================================================================
// colorSchemeToString tests
// ============================================================================

// Helper class to access private method
class TestableFangSettings : public FangSettings
{
public:
    QString testColorSchemeToString(Qt::ColorScheme scheme) {
        // Call the private slot via QMetaObject
        QString result;
        QMetaObject::invokeMethod(this, "colorSchemeToString",
                                  Qt::DirectConnection,
                                  Q_RETURN_ARG(QString, result),
                                  Q_ARG(Qt::ColorScheme, scheme));
        return result;
    }
};

void TestFangSettings::testColorSchemeToString_dark()
{
    TestableFangSettings testable;
    QCOMPARE(testable.testColorSchemeToString(Qt::ColorScheme::Dark), QString("DARK"));
}

void TestFangSettings::testColorSchemeToString_light()
{
    TestableFangSettings testable;
    QCOMPARE(testable.testColorSchemeToString(Qt::ColorScheme::Light), QString("LIGHT"));
}

void TestFangSettings::testColorSchemeToString_unknown()
{
    TestableFangSettings testable;
    // Unknown scheme should default to LIGHT
    QCOMPARE(testable.testColorSchemeToString(Qt::ColorScheme::Unknown), QString("LIGHT"));
}

// ============================================================================
// init tests
// ============================================================================

void TestFangSettings::testInit_connectsDBSettings()
{
    // Create fresh instances without init called
    FangSettings* uninitSettings = new FangSettings();
    MockDBSettings* mockDB = new MockDBSettings();

    QSignalSpy spy(uninitSettings, &FangSettings::cacheLengthChanged);

    // Before init, DB changes should not propagate
    mockDB->set(CACHE_LENGTH, "1WEEK");
    QCOMPARE(spy.count(), 0);

    // Call init
    uninitSettings->init(mockDB);

    // After init, DB changes should propagate
    mockDB->set(CACHE_LENGTH, "1MONTH");
    QCOMPARE(spy.count(), 1);

    delete uninitSettings;
    delete mockDB;
}

QTEST_MAIN(TestFangSettings)

#include "tst_fangsettings.moc"
