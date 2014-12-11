#include "GetAllDBSettingsOperation.h"
#include <QVariant>

GetAllDBSettingsOperation::GetAllDBSettingsOperation(OperationManager *parent, QMap<DBSettingsKey, QString>* settings) :
     DBOperation(IMMEDIATE, parent),
     settings(settings)
{

}

void GetAllDBSettingsOperation::execute()
{
    // Kindly ask the database for the rest.
    QSqlQuery query(db());
    if (!query.exec("SELECT * FROM DBSettings")) {
        reportError("Could not load all db settings. :(");
        return;
    }

    while (query.next()) {
        settings->insert( (DBSettingsKey)query.value("id").toInt(),
                         query.value("value").toString());
    }

    // That's all folks.
    emit finished(this);
}
