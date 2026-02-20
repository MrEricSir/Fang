#include "DBSettings.h"

#include "../operations/SetDBSettingOperation.h"
#include "../operations/GetAllDBSettingsOperation.h"

DBSettings::DBSettings(OperationManager *manager) :
    DBSettingsInterface(manager),
    manager(manager)
{
    // Load all of our settings into the map.
    GetAllDBSettingsOperation loadSettingsOp(manager, &settings);
    manager->run(&loadSettingsOp);
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
    SetDBSettingOperation setOp(manager, key, value);
    manager->run(&setOp);
    emit settingChanged(key, value);
}

QString DBSettings::get(DBSettingsKey key)
{
    return settings.value(key, DBSettingsKeyDefaultValue(key));
}
