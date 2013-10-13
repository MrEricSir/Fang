#include "FangSettings.h"
#include <QDebug>

FangSettings::FangSettings(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
}

QString FangSettings::getStyle()
{
    QString ret = "LIGHT";
    settings.beginGroup("FangSettings");
    if (settings.contains("style"))
        ret = settings.value("style").toString();
        
    
    settings.endGroup();
    return ret;
}

void FangSettings::setStyle(QString s)
{
    if (s == getStyle())
        return; // Nothing to do!
    
    settings.beginGroup("FangSettings");
    settings.setValue("style", s);
    settings.endGroup();
    
    emit styleChanged(s);
}
