#include "FangSettings.h"
#include "../utilities/ErrorHandling.h"
#include <QAutoStart.h>
#include <QCoreApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QPalette>

#ifdef Q_OS_WIN
#include <QSettings>
#endif

#ifdef Q_OS_LINUX
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#endif

FangSettings::FangSettings(FangObject *parent) :
    FangObject(parent),
    dbSettings(nullptr),
    styleHints(nullptr)
{
}

void FangSettings::init(DBSettingsInterface *dbSettings)
{
    // Database
    this->dbSettings = dbSettings;
    connect(this->dbSettings, &DBSettingsInterface::settingChanged, this, &FangSettings::onDBSettingChanged);

    // System default color scheme.
    styleHints = QGuiApplication::styleHints();
    connect(styleHints, &QStyleHints::colorSchemeChanged, this, &FangSettings::onSystemColorSchemeChanged);

    // Manually apply the color scheme if not set to the system default.
    QString style = getStyle();
    if (style == "LIGHT") {
        styleHints->setColorScheme(Qt::ColorScheme::Light);
    } else if (style == "DARK") {
        styleHints->setColorScheme(Qt::ColorScheme::Dark);
    }
}

QString FangSettings::getStringSetting(const QString& name, const QString& defaultValue)
{
    QString ret = defaultValue;
    settings.beginGroup("FangSettings");
    if (settings.contains(name)) {
        ret = settings.value(name).toString();
    }
    
    settings.endGroup();
    return ret;
}

void FangSettings::setStringSetting(const QString& name, const QString& newValue)
{
    settings.beginGroup("FangSettings");
    settings.setValue(name, newValue);
    settings.endGroup();
}

bool FangSettings::getBoolSetting(const QString& name, bool defaultValue)
{
    bool ret = defaultValue;
    settings.beginGroup("FangSettings");
    if (settings.contains(name)) {
        ret = settings.value(name).toBool();
    }

    settings.endGroup();
    return ret;
}

void FangSettings::setBoolSetting(const QString& name, bool newValue)
{
    settings.beginGroup("FangSettings");
    settings.setValue(name, newValue);
    settings.endGroup();
}

void FangSettings::onDBSettingChanged(DBSettingsKey key, QString value)
{
    switch (key) {
    case CACHE_LENGTH:
        emit cacheLengthChanged(value);
        break;

    default:
        FANG_UNREACHABLE("Unknown settings key in FangSettings");
        break;
    }
}

bool FangSettings::event(QEvent *event)
{
    if (event->type() == QEvent::ApplicationPaletteChange) {
        if (getStyle() == "DEFAULT" &&
            QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Unknown) {
            emit currentStyleChanged(getCurrentStyle());
        }
    }
    return QObject::event(event);
}

void FangSettings::onSystemColorSchemeChanged(Qt::ColorScheme colorScheme)
{
    if (getStyle() == "DEFAULT") {
        emit currentStyleChanged(colorSchemeToString(colorScheme));
    }
}

QString FangSettings::colorSchemeToString(Qt::ColorScheme colorScheme)
{
    if (colorScheme == Qt::ColorScheme::Dark) {
        return "DARK";
    } else {
        return "LIGHT";
    }
}

QString FangSettings::getStyle()
{
    return getStringSetting("style", "DEFAULT");
}

void FangSettings::setStyle(QString s)
{
    if (s == getStyle()) {
        return; // Nothing to do!
    }

    setStringSetting("style", s);

    // Set the color scheme.
    if (s == "LIGHT") {
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);
    } else if (s == "DARK") {
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Dark);
    } else {
        // This clears the override and goes with the OS default.
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Unknown);
    }

    emit styleChanged(s);
    emit currentStyleChanged(getCurrentStyle());
}

QString FangSettings::getCurrentStyle()
{
    QString ret = getStyle();
    if (ret == "DEFAULT") {
        Qt::ColorScheme scheme = QGuiApplication::styleHints()->colorScheme();
        if (scheme != Qt::ColorScheme::Unknown) {
            // Convert Qt's color scheme to our string-based color scheme.
            ret = colorSchemeToString(scheme);
        } else {
            // Essentially the same as above, but for older versions of Linux desktops.
            QColor windowColor = QGuiApplication::palette().color(QPalette::Window);
            ret = (windowColor.lightnessF() < 0.5) ? "DARK" : "LIGHT";
        }
    }

    return ret;
}

QString FangSettings::getFontSize()
{
    return getStringSetting("fontSize", "MEDIUM");
}

void FangSettings::setFontSize(QString s)
{
    if (s == getFontSize()) {
        return; // Nothing to do!
    }
    
    setStringSetting("fontSize", s);
    emit fontSizeChanged(s);
}

QString FangSettings::getCacheLength()
{
    return dbSettings->get(CACHE_LENGTH);
}

void FangSettings::setCacheLength(QString s)
{
    dbSettings->set(CACHE_LENGTH, s);
}

QString FangSettings::getRefresh()
{
    return getStringSetting("refresh", "10MIN");
}

void FangSettings::setRefresh(QString s)
{
    if (s == getRefresh()) {
        return; // Nothing to do!
    }

    setStringSetting("refresh", s);
    emit refreshChanged(s);
}

QString FangSettings::getLastSeenVersion()
{
    return getStringSetting("lastSeenVersion", "");
}

void FangSettings::setLastSeenVersion(QString s)
{
    if (s == getLastSeenVersion()) {
        return; // Nothing to do!
    }

    setStringSetting("lastSeenVersion", s);
    emit lastSeenVersionChanged(s);
}

bool FangSettings::getShowTrayIcon()
{
    bool defaultValue = false;
    return getBoolSetting("showTrayIcon", defaultValue);
}

void FangSettings::setShowTrayIcon(bool b)
{
    if (b == getShowTrayIcon()) {
        return; // Nothing to do!
    }

    setBoolSetting("showTrayIcon", b);
    emit showTrayIconChanged(b);
}

bool FangSettings::getStartAtLogin()
{
    return QAutoStart::Get().isEnabled();
}

void FangSettings::setStartAtLogin(bool b)
{
    if (b == getStartAtLogin()) {
        return; // Nothing to do!
    }

    QAutoStart::Get().setEnabled(b);

    // Append --minimized so the app starts hidden in the system tray.
    if (b) {
#ifdef Q_OS_WIN
        QSettings reg("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                       QSettings::NativeFormat);
        QString appPath = QCoreApplication::applicationFilePath();
        appPath.replace('/', '\\');
        reg.setValue(QCoreApplication::applicationName(),
                     "\"" + appPath + "\" --minimized");
        reg.sync();
#endif

#ifdef Q_OS_LINUX
        QString configDir = QStandardPaths::writableLocation(
            QStandardPaths::GenericConfigLocation);
        QString desktopPath = configDir + "/autostart/"
            + QCoreApplication::organizationDomain() + "."
            + QCoreApplication::applicationName() + ".desktop";

        QFile file(desktopPath);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QString content = QTextStream(&file).readAll();
            content.replace(
                "Exec=" + QCoreApplication::applicationFilePath(),
                "Exec=" + QCoreApplication::applicationFilePath() + " --minimized");
            file.resize(0);
            QTextStream(&file) << content;
        }
#endif
    }

    emit startAtLoginChanged(b);
}
