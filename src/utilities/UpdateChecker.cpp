#include "UpdateChecker.h"
#include "FangLogging.h"

#include <QRegularExpression>
#include <QVersionNumber>

// Only include FangApp.h when instance() is needed (not in tests)
#ifndef UPDATECHECKER_NO_FANGAPP
#include "../FangApp.h"
#endif

const QUrl UpdateChecker::UPDATE_FEED_URL = QUrl("https://getfang.com/feed.xml");
const int UpdateChecker::CHECK_INTERVAL_MS = 24 * 60 * 60 * 1000; // 24 hours

UpdateChecker::UpdateChecker(QObject *parent, ParserInterface* injectedParser, SettingsInterface* injectedSettings) :
    FangObject(parent),
    parser(injectedParser ? injectedParser : new NewsParser(this)),
    settingsInterface(injectedSettings),
    timer(this),
    _latestVersion(""),
    _updateAvailable(false)
{
    connect(parser, &ParserInterface::done, this, &UpdateChecker::onParserDone);
    connect(&timer, &QTimer::timeout, this, &UpdateChecker::checkNow);

    timer.setInterval(CHECK_INTERVAL_MS);
}

void UpdateChecker::start()
{
    // Perform immediate check
    checkNow();

    // Start periodic checking
    timer.start();
}

void UpdateChecker::checkNow()
{
    qCDebug(logUtility) << "UpdateChecker: Checking for updates...";
    parser->parse(UPDATE_FEED_URL);
}

void UpdateChecker::onParserDone()
{
    if (parser->getResult() != ParserInterface::OK) {
        qCWarning(logUtility) << "UpdateChecker: Failed to fetch update feed:"
                              << parser->getResult();
        return;
    }

    RawFeed* feed = parser->getFeed();
    if (!feed || feed->items.isEmpty()) {
        qCWarning(logUtility) << "UpdateChecker: No items in update feed";
        return;
    }

    // Get the latest release (first item in feed)
    RawNews* latestRelease = feed->items.first();
    QString version = extractVersion(latestRelease->title);

    if (version.isEmpty()) {
        qCWarning(logUtility) << "UpdateChecker: Could not extract version from title:"
                              << latestRelease->title;
        return;
    }

    _latestVersion = version;
    qCDebug(logUtility) << "UpdateChecker: Latest version:" << _latestVersion
                        << "Current version:" << APP_VERSION;

    // Compare versions
    if (isNewerVersion(APP_VERSION, _latestVersion)) {
        _updateAvailable = true;

        // Check if we've already shown the dialog for this version
        SettingsInterface* settings = settingsInterface;
#ifndef UPDATECHECKER_NO_FANGAPP
        if (!settings) {
            settings = FangApp::instance()->getSettings();
        }
#endif
        if (!settings) {
            qCWarning(logUtility) << "UpdateChecker: No settings available";
            return;
        }
        QString lastShown = settings->getLastSeenVersion();
        if (lastShown == _latestVersion) {
            qCDebug(logUtility) << "UpdateChecker: Update available but already shown for version:"
                                << _latestVersion;
            return;
        }

        qCInfo(logUtility) << "UpdateChecker: Update available! New version:" << _latestVersion;
        emit updateAvailable(_latestVersion);
    } else {
        qCDebug(logUtility) << "UpdateChecker: No update available";
        _updateAvailable = false;
    }
}

QString UpdateChecker::extractVersion(const QString& title)
{
    // Expected format: "Fang X.Y.Z" or "Fang X.Y.Z-beta" or "Fang X.Y.Z-beta.N"
    // Match version pattern after "Fang "
    static QRegularExpression versionPattern(R"(Fang\s+(\d+\.\d+\.\d+(?:-[a-zA-Z0-9.]+)?))");

    QRegularExpressionMatch match = versionPattern.match(title);
    if (match.hasMatch()) {
        return match.captured(1);
    }

    return QString();
}

bool UpdateChecker::isNewerVersion(const QString& currentVersion, const QString& newVersion)
{
    // Parse version strings of format: X.Y.Z or X.Y.Z-suffix
    auto parseVersion = [](const QString& version) -> QPair<QVersionNumber, QString> {
        QString numericPart = version;
        QString suffix;

        int dashIndex = version.indexOf('-');
        if (dashIndex != -1) {
            numericPart = version.left(dashIndex);
            suffix = version.mid(dashIndex + 1);
        }

        return qMakePair(QVersionNumber::fromString(numericPart), suffix);
    };

    auto [currentNum, currentSuffix] = parseVersion(currentVersion);
    auto [newNum, newSuffix] = parseVersion(newVersion);

    // Compare numeric part of version string.
    int comparison = QVersionNumber::compare(newNum, currentNum);
    if (comparison > 0) {
        // New version has higher number.
        return true;
    } else if (comparison < 0) {
        // New version has lower number.
        return false;
    }

    // No suffix > any suffix (beta, alpha, etc.)
    if (newSuffix.isEmpty() && !currentSuffix.isEmpty()) {
        // New is release, current is pre-release.
        return true;
    } else if (!newSuffix.isEmpty() && currentSuffix.isEmpty()) {
        // New is pre-release, current is release.
        return false;
    }

    // Both have suffixes or both don't, so just compare strings at this point.
    return newSuffix > currentSuffix;
}
