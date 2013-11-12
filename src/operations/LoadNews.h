#ifndef LOADNEWS_H
#define LOADNEWS_H

#include <QObject>

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

class LoadNews : public DBOperation
{
    Q_OBJECT
public:
    explicit LoadNews(QObject *parent, FeedItem* feedItem);
    
public slots:
    virtual void execute();
    
    inline FeedItem* getFeedItem() { return feedItem; }
    
public slots:
    
private:
    FeedItem* feedItem;
};

#endif // LOADNEWS_H
