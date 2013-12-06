#ifndef LOADALLNEWSOPERATION_H
#define LOADALLNEWSOPERATION_H

#include "LoadNews.h"
#include "../models/AllNewsFeedItem.h"

class LoadAllNewsOperation : public LoadNews
{
    Q_OBJECT
public:
    explicit LoadAllNewsOperation(QObject *parent, FeedItem* feedItem, LoadMode mode, int loadLimit = 15);
    
public slots:
    virtual void execute();
    
private slots:
    bool doInitial();
    
    bool doPrepend();
    
private:
    AllNewsFeedItem* allNews;
};

#endif // LOADALLNEWSOPERATION_H
