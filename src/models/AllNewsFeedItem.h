#ifndef ALLNEWSFEEDITEM_H
#define ALLNEWSFEEDITEM_H

#include "LisvelFeedItem.h"

#include <QObject>
#include <QList>

#include "ListModel.h"

class AllNewsFeedItem : public LisvelFeedItem
{
    Q_OBJECT
public:
    explicit AllNewsFeedItem(ListModel *feedList);
};

#endif // ALLNEWSFEEDITEM_H
