#include "FangSettings.h"
#include "../utilities/ErrorHandling.h"
#include <QDebug>

FangSettings::FangSettings(QQuickItem *parent) :
    QQuickItem(parent),
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
        // Attempt to get system color scheme.
        ret = colorSchemeToString(QGuiApplication::styleHints()->colorScheme());
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
#if defined(Q_OS_WIN)
    defaultValue = true;
#endif
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
