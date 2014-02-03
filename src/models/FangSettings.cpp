#include "FangSettings.h"
#include <QDebug>
#include <QDesktopServices>

FangSettings::FangSettings(QQuickItem *parent) :
    QQuickItem(parent)
{
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

void FangSettings::openLink(QString link)
{
    QDesktopServices::openUrl(QUrl(link));
}
