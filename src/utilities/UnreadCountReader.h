#ifndef UNREADCOUNTREADER_H
#define UNREADCOUNTREADER_H

#include <QObject>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "../models/FeedItem.h"

/**
 * @brief Reads unread counts from the database.
 */
class UnreadCountReader
{
public:
    UnreadCountReader();
    
    /**
     * @brief Updates the unread count of a given feed (and/or related feeds.)
     *        NOTE: Must be called from within a DBOperation.
     * @param db   DBOperation's database object
     * @param feed The feed in question.
     */
    static void update(QSqlDatabase db, FeedItem* feed);
    
    static qint32 forAllNews(QSqlDatabase db);

    static qint32 forPinned(QSqlDatabase db);

    static qint32 forFolder(QSqlDatabase db, qint64 folderID);
    
    static qint32 forFeed(QSqlDatabase db, quint64 id);
};

#endif // UNREADCOUNTREADER_H
