#ifndef DBSETTINGSINTERFACE_H
#define DBSETTINGSINTERFACE_H

#include <QObject>
#include <QString>
#include <QObject>
#include "DBSettingsKey.h"

/*!
    \brief Interface for DBSettings allowing mock implementations for testing.
 */
class DBSettingsInterface : public QObject
{
    Q_OBJECT
public:
    explicit DBSettingsInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~DBSettingsInterface() = default;

signals:
    void settingChanged(DBSettingsKey key, QString value);

public slots:
    virtual void set(DBSettingsKey key, const QString& value) = 0;
    virtual QString get(DBSettingsKey key) = 0;
};

#endif // DBSETTINGSINTERFACE_H
