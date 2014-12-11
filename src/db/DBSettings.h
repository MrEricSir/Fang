#ifndef DBSETTINGS_H
#define DBSETTINGS_H

#include <QObject>
#include <QString>
#include <QMap>

#include "DBSettingsKey.h"

#include "../operations/OperationManager.h"

/**
 * @brief A key/value store for saving special settings in the database.
 */
class DBSettings : public QObject
{
    Q_OBJECT
public:
    explicit DBSettings(OperationManager *manager);

signals:
    void settingChanged(DBSettingsKey key, QString value);

public slots:
    // Set a key to a new value.
    void set(DBSettingsKey key, const QString& value);

    // Get an existing key.  Returns the default value if never set.
    QString get(DBSettingsKey key);

private:

    QMap<DBSettingsKey, QString> settings;

    OperationManager *manager;

};

#endif // DBSETTINGS_H
