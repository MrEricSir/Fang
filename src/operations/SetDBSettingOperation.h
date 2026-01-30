#ifndef SETDBSETTINGOPERATION_H
#define SETDBSETTINGOPERATION_H

#include <QString>

#include "DBOperation.h"

#include "../db/DBSettingsKey.h"

/*!
    \brief Sets a key-value pair for storing data in a special SQLite data.

    This should ONLY be used for data that configures the database, such as how much old news to keep around.
 */
class SetDBSettingOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit SetDBSettingOperation(OperationManager *parent, DBSettingsKey setting, const QString& value);

public slots:

    virtual void execute();

private:
    DBSettingsKey setting;
    QString value;
};

#endif // SETDBSETTINGOPERATION_H
