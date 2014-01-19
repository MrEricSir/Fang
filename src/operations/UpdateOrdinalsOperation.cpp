#include "UpdateOrdinalsOperation.h"
#include "../models/FeedItem.h"
#include "../models/ListModel.h"

#include <QDebug>

UpdateOrdinalsOperation::UpdateOrdinalsOperation(QObject *parent, ListModel *feedList) :
    DBOperation(IMMEDIATE, parent),
    feedList(feedList)
{
}

void UpdateOrdinalsOperation::execute()
{
    db().transaction();
    
    for (int i = 1; i < feedList->count(); i++) {
        QSqlQuery update(db());
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        
        update.prepare("UPDATE FeedItemTable SET ordinal = :ordinal WHERE id = "
                       ":feed_id");
        update.bindValue(":ordinal", feedItem->getOrdinal());
        update.bindValue(":feed_id", feedItem->getDbId());
        
        if (!update.exec()) {
            db().rollback();
            
            qDebug() << "Unable to update ordinal for feed id " << feedItem->getDbId();
            qDebug() << "SQL error: " << update.lastError().text();
            
            // TODO error signal.
            emit finished(this);
            return;
        }
    }
    
    // And we're done!
    db().commit();
    emit finished(this);
}
