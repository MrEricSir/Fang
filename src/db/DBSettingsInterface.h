#ifndef DBSETTINGSINTERFACE_H
#define DBSETTINGSINTERFACE_H

#include <QObject>
#include <QString>
#include "../FangObject.h"
#include "DBSettingsKey.h"

/*!
    \brief Interface for DBSettings allowing mock implementations for testing.
 */
class DBSettingsInterface : public FangObject
{
    Q_OBJECT
public:
    explicit DBSettingsInterface(FangObject *parent = nullptr) : FangObject(parent) {}
    virtual ~DBSettingsInterface() = default;

signals:
    void settingChanged(DBSettingsKey key, QString value);

public slots:
    virtual void set(DBSettingsKey key, const QString& value) = 0;
    virtual QString get(DBSettingsKey key) = 0;
};

#endif // DBSETTINGSINTERFACE_H
