#ifndef FANGSETTINGS_H
#define FANGSETTINGS_H

#include <QDeclarativeItem>
#include <QString>
#include <QSettings>

class FangSettings : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(FangSettings)
    
    // Style.  Values are "LIGHT" and "DARK" (default: LIGHT)
    Q_PROPERTY(QString style READ getStyle WRITE setStyle NOTIFY styleChanged)
    
public:
    explicit FangSettings(QDeclarativeItem *parent = 0);
    
    QString getStyle();
    void setStyle(QString s);
    
signals:
    void styleChanged(QString);
    
public slots:
    
private:
    QSettings settings;
};

#endif // FANGSETTINGS_H
