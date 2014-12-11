#include "FangSettings.h"
#include <QDebug>

FangSettings::FangSettings(QQuickItem *parent) :
    QQuickItem(parent),
    dbSettings(NULL)
{
}

void FangSettings::init(DBSettings *dbSettings)
{
    this->dbSettings = dbSettings;
    connect(this->dbSettings, SIGNAL(settingChanged(DBSettingsKey,QString)), this, SLOT(onDBSettingChanged(DBSettingsKey,QString)));
}

QString FangSettings::getStringSetting(const QString& name, const QString& defaultValue)
{
    QString ret = defaultValue;
    settings.beginGroup("FangSettings");
    if (settings.contains(name))
        ret = settings.value(name).toString();
    
    settings.endGroup();
    return ret;
}

void FangSettings::setStringSetting(const QString& name, const QString& newValue)
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
        Q_ASSERT(false); // You forgot to handle your new key here, dumas.
    }
}

QString FangSettings::getStyle()
{
    return getStringSetting("style", "LIGHT");
}

void FangSettings::setStyle(QString s)
{
    if (s == getStyle())
        return; // Nothing to do!
    
    setStringSetting("style", s);
    emit styleChanged(s);
}

QString FangSettings::getFontSize()
{
    return getStringSetting("fontSize", "MEDIUM");
}

void FangSettings::setFontSize(QString s)
{
    if (s == getFontSize())
        return; // Nothing to do!
    
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
