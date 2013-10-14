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
    
    // Font size.  Values are "SMALL", "MEDIUM", and "LARGE" (default: MEDIUM)
    Q_PROPERTY(QString fontSize READ getFontSize WRITE setFontSize NOTIFY fontSizeChanged)
    
public:
    explicit FangSettings(QDeclarativeItem *parent = 0);
    
    QString getStyle();
    void setStyle(QString s);
    
    QString getFontSize();
    void setFontSize(QString s);
    
signals:
    void styleChanged(QString);
    void fontSizeChanged(QString);
    
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
    
private:
    QSettings settings;
};

#endif // FANGSETTINGS_H
