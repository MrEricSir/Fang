#include "SetDBSettingOperation.h"

#include <QDebug>

SetDBSettingOperation::SetDBSettingOperation(OperationManager *parent, DBSettingsKey setting, const QString &value) :
    DBOperation(parent), setting(setting), value(value)
{

}

void SetDBSettingOperation::execute()
{
    db().transaction();

    QSqlQuery update(db());
    update.prepare("INSERT OR REPLACE INTO DBSettings (id, value) VALUES (:setting, :value)");
    update.bindValue(":setting", setting);
    update.bindValue(":value", value);

    if (!update.exec()) {
        reportSQLError(update, "Unable to set DBSetting: " + QString::number(setting));
        db().rollback();

        return;
    }

    db().commit();
}
