#ifndef MOCKDBSETTINGS_H
#define MOCKDBSETTINGS_H

#include "../src/FangObject.h"
#include "../src/db/DBSettingsInterface.h"

/*!
    \brief Mock implementation of DBSettingsInterface for unit testing.
    Does not require OperationManager or database access.
 */
class MockDBSettings : public DBSettingsInterface
{
    Q_OBJECT
public:
    explicit MockDBSettings(FangObject *parent = nullptr)
        : DBSettingsInterface(parent)
    {
    }

public slots:
    void set(DBSettingsKey key, const QString& value) override
    {
        if (value == get(key)) {
            return; // Nothing to do!
        }

        settings[key] = value;
        emit settingChanged(key, value);
    }

    QString get(DBSettingsKey key) override
    {
        return settings.value(key, DBSettingsKeyDefaultValue(key));
    }

private:
    QMap<DBSettingsKey, QString> settings;
};

#endif // MOCKDBSETTINGS_H
