#include "SetPinOperation.h"
#include <QDebug>

#include "../utilities/UnreadCountReader.h"

SetPinOperation::SetPinOperation(OperationManager *parent, PinnedFeedItem *pinnedNews, qint64 newsID, bool pin) :
    DBOperationSynchronous(parent), pinnedNews(pinnedNews), newsID(newsID), pin(pin)
{
}

void SetPinOperation::executeSynchronous()
{
    db().transaction();

    // SQLITE HULK HOGAN IS GUNNA DRIVE A BODY SLAM STRAIGHT INTO THAT PINNED COLUMN, OH YEAH!
    QSqlQuery update(db());
    update.prepare("UPDATE NewsItemTable SET pinned = :pin WHERE id = :news_id");
    update.bindValue(":pin", (int) pin);
    update.bindValue(":news_id", newsID);

    if (!update.exec()) {
        reportSQLError(update, "Unable to set/unset pin on " + QString::number(newsID));
        db().rollback();

        return;
    }

    db().commit();

    // Update the unread count of the special pinned feed.
    pinnedNews->setUnreadCount(UnreadCountReader::forPinned(db()));
}
