#include "SetPinOperation.h"
#include <QDebug>


SetPinOperation::SetPinOperation(OperationManager *parent, qint64 newsID, bool pin) :
    DBOperation(IMMEDIATE, parent), newsID(newsID), pin(pin)
{
}

void SetPinOperation::execute()
{
    db().transaction();

    // SQLITE HULK HOGAN IS GUNNA DRIVE A BODY SLAM STRAIGHT INTO THAT PINNED COLUMN, OH YEAH!
    QSqlQuery update(db());
    update.prepare("UPDATE NewsItemTable SET pinned = :pin WHERE id = :news_id");
    update.bindValue(":pin", pin);
    update.bindValue(":news_id", newsID);

    if (!update.exec()) {
        reportSQLError(update, "Unable to set/unset pin on " + QString::number(newsID));
        db().rollback();

        return;
    }

    db().commit();

    // MOST GLORIOUS TODO: update the unread count of the artificial pinned feed

    emit finished(this);
}
