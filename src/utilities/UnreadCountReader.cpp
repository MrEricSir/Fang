#include "UnreadCountReader.h"
#include "FangLogging.h"
#include "ErrorHandling.h"

UnreadCountReader::UnreadCountReader()
{
}

void UnreadCountReader::update(QSqlDatabase db, FeedItem *feed)
{
    if (feed->isSpecialFeed()) {
        switch (feed->getDbID()) {
        case FEED_ID_ALLNEWS:
            feed->setUnreadCount(forAllNews(db));
            break;

        case FEED_ID_PINNED:
            feed->setUnreadCount(forPinned(db));
            break;

        default:
            FANG_UNREACHABLE("UnreadCountReader: Invalid special feed type");
            break;
        }
        return;
    }

    // All other feed types.
    if (feed->isFolder()) {
        feed->setUnreadCount(forFolder(db, feed->getDbID()));
    } else {
        feed->setUnreadCount(forFeed(db, feed->getDbID()));
    }
}

qint32 UnreadCountReader::forAllNews(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("SELECT count(id) FROM NewsItemTable N where id > "
                  "(SELECT bookmark_id from FeedItemTable WHERE id = N.feed_id)");
    
    if (!query.exec() || !query.next()) {
       qCDebug(logUtility) << "Could not update unread count for all news feed";
       qCDebug(logUtility) << query.lastError();
       
       return -1;
    }
    
    int ret = query.value(0).toInt();
    return ret;
}

qint32 UnreadCountReader::forPinned(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("SELECT count(id) FROM NewsItemTable WHERE pinned");

    if (!query.exec() || !query.next()) {
       qCDebug(logUtility) << "Could not update unread count for pinned news feed";
       qCDebug(logUtility) << query.lastError();

       return -1;
    }

    int ret = query.value(0).toInt();
    //qCDebug(logUtility) << "Unread count for pinned: " << ret;
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
       qCDebug(logUtility) << "Could not update unread count for folder";
       qCDebug(logUtility) << query.lastError();

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
       qCDebug(logUtility) << "Could not update unread count for feed id: " << id;
       qCDebug(logUtility) << query.lastError();
       
       return -1;
    }
    
    int ret = query.value(0).toInt();
    return ret;
}
