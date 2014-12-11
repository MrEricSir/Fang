#include "DBSettings.h"

#include "../operations/SetDBSettingOperation.h"
#include "../operations/GetAllDBSettingsOperation.h"

DBSettings::DBSettings(OperationManager *manager) :
    QObject(manager),
    manager(manager)
{
    // Load all of our settings into the map.
    manager->add(new GetAllDBSettingsOperation(manager, &settings));
}

void DBSettings::set(DBSettingsKey key, const QString& value)
{
    if (value == get(key)) {
        return; // Nothing to do!
    }

    // Check it out, y'all.
    DBSettingsKeyAssert(key, value);

    // Lookin' good.  Save to our map and the database.
    settings[key] = value;
    manager->add(new SetDBSettingOperation(manager, key, value));
    emit settingChanged(key, value);
}

QString DBSettings::get(DBSettingsKey key)
{
    return settings.value(key, DBSettingsKeyDefaultValue(key));
}
