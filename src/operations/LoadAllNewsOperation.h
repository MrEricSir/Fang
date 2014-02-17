#ifndef LOADALLNEWSOPERATION_H
#define LOADALLNEWSOPERATION_H

#include "LoadNews.h"

#include <QString>

#include "../models/AllNewsFeedItem.h"

class LoadAllNewsOperation : public LoadNews
{
    Q_OBJECT
public:
    explicit LoadAllNewsOperation(OperationManager *parent, FeedItem* feedItem, LoadMode mode, int loadLimit = 15);
    
public slots:
    virtual void execute();
    
private slots:
    
    bool doPrepend();
    
    bool doAppend();
    
    // Returns a SQL string of all in-memory news item IDs as a SQL string.
    QString getLoadedIDString();
    
private:
    // The feed that we're using here has gotta be All News.  Like, duh.
    AllNewsFeedItem* allNews;
};

#endif // LOADALLNEWSOPERATION_H
