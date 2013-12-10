#include "UnreadCountReader.h"

#include <QDebug>

UnreadCountReader::UnreadCountReader()
{
}

void UnreadCountReader::update(QSqlDatabase db, FeedItem *feed)
{
    if (feed->getDbId())
        feed->setUnreadCount(forFeed(db, feed->getDbId()));
    else
        feed->setUnreadCount(forAllNews(db));
}

qint32 UnreadCountReader::forAllNews(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("SELECT count(id) FROM NewsItemTable N where id > "
                  "(SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id)");
    
    if (!query.exec() || !query.next()) {
       qDebug() << "Could not update unread count for all news feed";
       qDebug() << query.lastError();
       
       return -1;
    }
    
    int ret = query.value(0).toInt();
    //qDebug() << "UC: " << ret;
    return ret;
}

qint32 UnreadCountReader::forFeed(QSqlDatabase db, quint64 id)
{
    QSqlQuery query(db);
    query.prepare("SELECT count(id) FROM NewsItemTable WHERE feed_id = :id1 AND "
                  "id > (SELECT bookmark_id FROM FeedItemTable WHERE id = :id2)");
    query.bindValue(":id1", id);
    query.bindValue(":id2", id);
    
    if (!query.exec() || !query.next()) {
       qDebug() << "Could not update unread count for feed id: " << id;
       qDebug() << query.lastError();
       
       return -1;
    }
    
    int ret = query.value(0).toInt();
    //qDebug() << id << "UC: " << ret;
    return ret;
}
