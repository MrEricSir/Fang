#ifndef SETBOOKMARKOPERATION_H
#define SETBOOKMARKOPERATION_H

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

class SetBookmarkOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit SetBookmarkOperation(QObject *parent, FeedItem* feed, NewsItem* bookmarkItem);
    virtual ~SetBookmarkOperation();
signals:
    
public slots:
    virtual void execute();
    
    inline FeedItem* getFeed() { return feed; }
    
    inline NewsItem* getBookmarkItem() { return bookmarkItem; }
    
private:
    FeedItem *feed;
    NewsItem* bookmarkItem;
};

#endif // SETBOOKMARKOPERATION_H
