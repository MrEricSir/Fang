#ifndef FANGSETTINGS_H
#define FANGSETTINGS_H

#include <QQuickItem>
#include <QString>
#include <QSettings>
#include <QStyleHints>

#include "../db/DBSettings.h"
#include "../utilities/SettingsInterface.h"

class FangSettings : public QQuickItem, public SettingsInterface
{
    Q_OBJECT
    Q_DISABLE_COPY(FangSettings)
    
    // Style.  Values are "LIGHT", "DARK", or "DEFAULT" (default: DEFAULT)
    Q_PROPERTY(QString style READ getStyle WRITE setStyle NOTIFY styleChanged)

    // Read-only property that only returns "LIGHT" or "DARK", handling the default scenario.
    Q_PROPERTY(QString currentStyle READ getCurrentStyle NOTIFY currentStyleChanged)
    
    // Font size.  Values are "SMALL", "MEDIUM", and "LARGE" (default: MEDIUM)
    Q_PROPERTY(QString fontSize READ getFontSize WRITE setFontSize NOTIFY fontSizeChanged)

    // Length of cache size
    Q_PROPERTY(QString cacheLength READ getCacheLength WRITE setCacheLength NOTIFY cacheLengthChanged)

    // Refresh timer.  Values are "1MIN", "10MIN", "30MIN", and "1HOUR" (default: 10MIN)
    Q_PROPERTY(QString refresh READ getRefresh WRITE setRefresh NOTIFY refreshChanged)

    // Last update version displayed to the user.
    Q_PROPERTY(QString lastSeenVersion READ getLastSeenVersion WRITE setLastSeenVersion NOTIFY lastSeenVersionChanged)

    // (Windows only) Display tray icon.
    Q_PROPERTY(bool showTrayIcon READ getShowTrayIcon WRITE setShowTrayIcon NOTIFY showTrayIconChanged)
    
public:
    explicit FangSettings(QQuickItem *parent = nullptr);

    /*!
        \brief The stuff the settings object needs to do its job properly.
        \param manager
     */
    void init(DBSettings* dbSettings);
    
    QString getStyle();
    void setStyle(QString s);

    QString getCurrentStyle();
    
    QString getFontSize();
    void setFontSize(QString s);

    QString getCacheLength();
    void setCacheLength(QString s);

    QString getRefresh();
    void setRefresh(QString s);

    QString getLastSeenVersion() override;
    void setLastSeenVersion(QString s);

    bool getShowTrayIcon();
    void setShowTrayIcon(bool b);
    
signals:
    void styleChanged(QString);
    void currentStyleChanged(QString);
    void fontSizeChanged(QString);
    void cacheLengthChanged(QString);
    void refreshChanged(QString);
    void lastSeenVersionChanged(QString);
    void showTrayIconChanged(bool);

    /*!
        \brief Emitted when a newer version of Fang is available.
        \param newVersion The version string of the available update.
     */
    void updateAvailable(const QString& newVersion);
    
private slots:
    /*!
        \brief Gets a string value or its default if not present
        \param name
        \param defaultValue
        \return
     */
    QString getStringSetting(const QString& name, const QString& defaultValue);
    
    /*!
        \brief Sets a string value
        \param name
        \param newValue
     */
    void setStringSetting(const QString& name, const QString& newValue);

    /*!
        \brief Gets a bool value or its default if not present
        \param name
        \param defaultValue
        \return
     */
    bool getBoolSetting(const QString& name, bool defaultValue);

    /*!
        \brief Sets a bool value
        \param name
        \param newValue
     */
    void setBoolSetting(const QString& name, bool newValue);

    /*!
        \brief Called when a DB setting has changed.
        \param key
        \param value
     */
    void onDBSettingChanged(DBSettingsKey key, QString value);

    /*!
        \brief Called when the system color scheme has changed.
        \param colorScheme
     */
    void onSystemColorSchemeChanged(Qt::ColorScheme colorScheme);

    /*!
        \brief Converts a Qt color scheme into either "LIGHT" or "DARK" (LIGHT is default)
        \param colorScheme
        \return
     */
    QString colorSchemeToString(Qt::ColorScheme colorScheme);
    
private:
    QSettings settings;
    DBSettings* dbSettings;
    QStyleHints* styleHints;
};

#endif // FANGSETTINGS_H
