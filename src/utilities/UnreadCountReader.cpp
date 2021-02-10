#include "UnreadCountReader.h"

#include <QDebug>

UnreadCountReader::UnreadCountReader()
{
}

void UnreadCountReader::update(QSqlDatabase db, FeedItem *feed)
{
    if (feed->isSpecialFeed()) {
        switch (feed->getDbId()) {
        case FEED_ID_ALLNEWS:
            feed->setUnreadCount(forAllNews(db));
            break;

        case FEED_ID_PINNED:
            feed->setUnreadCount(forPinned(db));
            break;

        default:
            Q_ASSERT(false); // You forgot to handle a new special feed type here.
        }
        return;
    }

    // All other feed types.
    feed->setUnreadCount(forFeed(db, feed->getDbId()));
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

qint32 UnreadCountReader::forPinned(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("SELECT count(id) FROM NewsItemTable WHERE pinned");

    if (!query.exec() || !query.next()) {
       qDebug() << "Could not update unread count for pinned news feed";
       qDebug() << query.lastError();

       return -1;
    }

    int ret = query.value(0).toInt();
    //qDebug() << "Unread count for pinned: " << ret;
    return ret;
}

qint32 UnreadCountReader::forFolder(QSqlDatabase db, qint64 folderID)
{
    QSqlQuery query(db);
    query.prepare("SELECT count(id) FROM NewsItemTable N WHERE "
                  "(SELECT parent_folder FROM FeedItemTable WHERE id = N.feed_id) = :folder_id "
                  "AND id > "
                  "(SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id)");
    query.bindValue(":folder_id", folderID);

    if (!query.exec() || !query.next()) {
       qDebug() << "Could not update unread count for folder";
       qDebug() << query.lastError();

       return -1;
    }

    return query.value(0).toInt();;
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
