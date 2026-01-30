#ifndef GETALLDBSETTINGSOPERATION_H
#define GETALLDBSETTINGSOPERATION_H

#include "DBOperation.h"

#include "../db/DBSettingsKey.h"

#include <QString>
#include <QMap>

/*!
    \brief Loads every setting stored in the database into a key/value pair map.
 */
class GetAllDBSettingsOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit GetAllDBSettingsOperation(OperationManager *parent, QMap<DBSettingsKey, QString> *settings);

public slots:

    virtual void execute();

private:
    QMap<DBSettingsKey, QString> *settings;

};

#endif // GETALLDBSETTINGSOPERATION_H
