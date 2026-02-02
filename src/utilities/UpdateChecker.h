#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QSettings>

#include "../FangObject.h"
#include "../parser/NewsParser.h"
#include "SettingsInterface.h"

/*!
    \brief Checks for application updates by fetching a release feed.

    On application start and every 24 hours, fetches the Fang release feed
    and compares the latest version to the current application version.
    Emits updateAvailable() if a newer version is found.
 */
class UpdateChecker : public FangObject
{
    Q_OBJECT

public:
    /*!
        \param parent Parent QObject.
        \param parser Optional parser for dependency injection (used for testing).
                      If this is provided the caller is responsible for its lifecycle.
        \param settings Optional settings for dependency injection (used for testing).
                        If null, uses FangApp::instance()->getSettings().
     */
    explicit UpdateChecker(QObject *parent = nullptr,
                           ParserInterface* parser = nullptr,
                           SettingsInterface* settings = nullptr);
    inline virtual ~UpdateChecker() = default;

    /*!
        \brief Starts the update checker.
        Performs an immediate check and sets up periodic checking.
     */
    void start();

    /*!
        \brief Performs an update check now.
     */
    void checkNow();

    /*!
        \brief Returns the latest version found, or empty string if none.
     */
    QString latestVersion() const { return _latestVersion; }

    /*!
        \brief Returns true if an update is available.
     */
    bool isUpdateAvailable() const { return _updateAvailable; }

signals:
    /*!
        \brief Emitted when a newer version is available.
        \param newVersion The version string of the new release.
     */
    void updateAvailable(const QString& newVersion);

private slots:
    void onParserDone();

protected:
    /*!
        \brief Extracts version string from a feed item title.
        Expected format: "Fang X.Y.Z" or "Fang X.Y.Z-beta"
        \param title The feed item title.
        \return The version string, or empty if not found.
     */
    QString extractVersion(const QString& title);

    /*!
        \brief Compares two version strings.
        \return true if newVersion is greater than currentVersion.
     */
    bool isNewerVersion(const QString& currentVersion, const QString& newVersion);

private:

    static const QUrl UPDATE_FEED_URL;
    static const int CHECK_INTERVAL_MS; // 24 hours in milliseconds

    ParserInterface* parser;
    SettingsInterface* settingsInterface;  // Injected or from FangApp
    QTimer timer;
    QString _latestVersion;
    bool _updateAvailable;
};

#endif // UPDATECHECKER_H
