#ifndef DBSETTINGSKEY_H
#define DBSETTINGSKEY_H

#include <QString>
#include <QDateTime>

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
        Q_ASSERT(false); // You forgot to handle your new key here, bozo.
        return "";
    }
}

/**
 * @brief Asserts if the value isn't valid for this key.
 * @param key
 * @param value
 */
inline void DBSettingsKeyAssert(DBSettingsKey key, const QString& value) {
    Q_UNUSED(value); // TODO: Will this param ever be used?

    switch (key) {
    case CACHE_LENGTH:
         Q_ASSERT(value == TWO_WEEKS || value == THREE_MONTH ||
                  value == SIX_MONTH || value == ONE_YEAR);
        break;

    default:
        Q_ASSERT(false); // You forgot to handle your new key here, moran.
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
        Q_ASSERT(false); // You forgot to handle your new key here, stupidz.
        return QDateTime::fromMSecsSinceEpoch(0); // Hella old so we don't delete anything.
    }
}

#endif // DBSETTINGSKEY_H

