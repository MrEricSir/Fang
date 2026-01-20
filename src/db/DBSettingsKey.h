#ifndef DBSETTINGSKEY_H
#define DBSETTINGSKEY_H

#include <QString>
#include <QDateTime>
#include "../utilities/ErrorHandling.h"

const QString TWO_WEEKS = "2WEEK";
const QString THREE_MONTH = "3MONTH";
const QString SIX_MONTH = "6MONTH";
const QString ONE_YEAR = "1YEAR";

enum DBSettingsKey
{
    CACHE_LENGTH
};

inline QString DBSettingsKeyDefaultValue(DBSettingsKey key) {
    switch (key) {
    case CACHE_LENGTH:
        return TWO_WEEKS;
    default:
        FANG_UNREACHABLE("Unknown DBSettingsKey");
        return "";
    }
}

/**
 * @brief Asserts if the value isn't valid for this key.
 * @param key
 * @param value
 */
inline void DBSettingsKeyAssert(DBSettingsKey key, const QString& value) {
    switch (key) {
    case CACHE_LENGTH:
        FANG_CHECK(value == TWO_WEEKS || value == THREE_MONTH ||
                   value == SIX_MONTH || value == ONE_YEAR,
                   "DBSettingsKeyAssert: Invalid CACHE_LENGTH value");
        break;

    default:
        FANG_UNREACHABLE("Unknown DBSettingsKey");
        break;
    }
}

inline QDateTime DBSettingsCacheLengthToDateTime(const QString& value) {
    if (TWO_WEEKS == value) {
        return QDateTime::currentDateTime().addDays(-14);
    } else if (THREE_MONTH == value) {
        return QDateTime::currentDateTime().addMonths(-3);
    } else if (SIX_MONTH == value) {
        return QDateTime::currentDateTime().addMonths(-6);
    } else if (ONE_YEAR == value) {
        return QDateTime::currentDateTime().addYears(-1);
    } else {
        FANG_UNREACHABLE("Unknown cache length value");
        return QDateTime::fromMSecsSinceEpoch(0); // Hella old so we don't delete anything.
    }
}

#endif // DBSETTINGSKEY_H

