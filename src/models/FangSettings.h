#ifndef FANGSETTINGS_H
#define FANGSETTINGS_H

#include <QQuickItem>
#include <QString>
#include <QSettings>

#include "../db/DBSettings.h"

class FangSettings : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(FangSettings)
    
    // Style.  Values are "LIGHT" and "DARK" (default: LIGHT)
    Q_PROPERTY(QString style READ getStyle WRITE setStyle NOTIFY styleChanged)
    
    // Font size.  Values are "SMALL", "MEDIUM", and "LARGE" (default: MEDIUM)
    Q_PROPERTY(QString fontSize READ getFontSize WRITE setFontSize NOTIFY fontSizeChanged)

    // Length of cache size
    Q_PROPERTY(QString cacheLength READ getCacheLength WRITE setCacheLength NOTIFY cacheLengthChanged)

    // Refresh timer.  Values are "1MIN", "10MIN", "30MIN", and "1HOUR" (default: 10MIN)
    Q_PROPERTY(QString refresh READ getRefresh WRITE setRefresh NOTIFY refreshChanged)
    
public:
    explicit FangSettings(QQuickItem *parent = nullptr);

    /**
     * @brief The stuff the settings object needs to do its job properly.
     * @param manager
     */
    void init(DBSettings* dbSettings);
    
    QString getStyle();
    void setStyle(QString s);
    
    QString getFontSize();
    void setFontSize(QString s);

    QString getCacheLength();
    void setCacheLength(QString s);

    QString getRefresh();
    void setRefresh(QString s);
    
signals:
    void styleChanged(QString);
    void fontSizeChanged(QString);
    void cacheLengthChanged(QString);
    void refreshChanged(QString);
    
private slots:
    /**
     * @brief Gets a string value or its default if not present
     * @param name
     * @param defaultValue
     * @return 
     */
    QString getStringSetting(const QString& name, const QString& defaultValue);
    
    /**
     * @brief Sets a string value
     * @param name
     * @param newValue
     */
    void setStringSetting(const QString& name, const QString& newValue);

    /**
     * @brief Called when a DB setting has changed.
     * @param key
     * @param value
     */
    void onDBSettingChanged(DBSettingsKey key, QString value);
    
private:
    QSettings settings;
    DBSettings *dbSettings;
};

#endif // FANGSETTINGS_H
