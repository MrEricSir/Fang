#include "LoadAllFeedsOperation.h"

#include <QDebug>
#include <QMap>

#include "../models/AllNewsFeedItem.h"
#include "../models/PinnedFeedItem.h"
#include "../models/FolderFeedItem.h"
#include "../utilities/UnreadCountReader.h"

LoadAllFeedsOperation::LoadAllFeedsOperation(OperationManager *parent, ListModel *feedList) :
    DBOperation(parent),
    feedList(feedList)
{
}

void LoadAllFeedsOperation::execute()
{
    // Setup our pseudo-feeds.
    AllNewsFeedItem* allNews = new AllNewsFeedItem(feedList);
    PinnedFeedItem* pinnedNews = new PinnedFeedItem(feedList);

    // Kindly ask the database for the rest.
    QSqlQuery query(db());
    if (!query.exec("SELECT * FROM FeedItemTable ORDER BY ordinal ASC")) {
        reportError("Could not load feeds. :(");
        return;
    }

    QList<ListItem*> tempFeedItemList; // Use ListItem so we can do an appendAll later.
    while (query.next()) {
        FeedItem* item = nullptr;
        bool isFolder = query.value("is_folder").toBool();
        if (isFolder) {
            item = new FolderFeedItem(
                        query.value("id").toULongLong(),
                        query.value("ordinal").toInt(),
                        query.value("title").toString(),
                        query.value("folder_open").toBool(),
                        nullptr
                        );
        } else {
            item = new FeedItem(
                        query.value("id").toULongLong(),
                        query.value("ordinal").toInt(),
                        query.value("title").toString(),
                        query.value("subtitle").toString(),
                        QDateTime::fromMSecsSinceEpoch(query.value("lastUpdated").toLongLong()),
                        query.value("minutesToUpdate").toUInt(),
                        query.value("url").toString(),
                        query.value("siteURL").toString(),
                        query.value("user_url").toString(),
                        query.value("imageURL").toString(),
                        QDateTime::fromMSecsSinceEpoch(query.value("lastIconUpdate").toLongLong()),
                        query.value("parent_folder").toULongLong(),
                        query.value("folder_open").toBool(),
                        nullptr
                        );
        }

        tempFeedItemList.append(item);
    }

    // Set the initial unread counts.
    allNews->setUnreadCount(UnreadCountReader::forAllNews(db()));
    pinnedNews->setUnreadCount(UnreadCountReader::forPinned(db()));
    for (ListItem* li : tempFeedItemList) {
        FeedItem* item = qobject_cast<FeedItem*>(li);
        if (item->isFolder()) {
            item->setUnreadCount(UnreadCountReader::forFolder(db(), item->getDbID()));
        } else {
            item->setUnreadCount(UnreadCountReader::forFeed(db(), item->getDbID()));
        }
    }

    // Finally, put special items at the front (in reverse order, since we're prepending.)
    tempFeedItemList.prepend(pinnedNews);
    tempFeedItemList.prepend(allNews);

    // Add 'em all!
    feedList->appendRows(tempFeedItemList);
}
