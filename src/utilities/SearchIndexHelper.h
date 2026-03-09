#ifndef SEARCHINDEXHELPER_H
#define SEARCHINDEXHELPER_H

#include <QList>

#include "../parser/RawNews.h"
#include "../models/FeedItem.h"
#include "../models/ListModel.h"

/*!
   \class SearchIndexHelper
   \brief Adds and removes items from the native platform search.
 */
class SearchIndexHelper
{
public:
    static void indexNewsItems(const QList<RawNews*>& items, FeedItem* feed);
    static void indexFeed(FeedItem* feed);
    static void indexAllFeeds(ListModel* feedList);
    static void removeNewsItems(const QList<qint64>& dbIds);
    static void removeFeed(qint64 feedId);
};

#endif // SEARCHINDEXHELPER_H
