#ifndef LOADALLNEWSOPERATION_H
#define LOADALLNEWSOPERATION_H

#include "LisvelLoadNewsOperation.h"

#include <QString>

#include "../models/AllNewsFeedItem.h"

class LoadAllNewsOperation : public LisvelLoadNewsOperation
{
    Q_OBJECT
public:
    explicit LoadAllNewsOperation(OperationManager *parent, AllNewsFeedItem* feedItem, LoadMode mode, int loadLimit = 15);
    
private slots:
    
    virtual qint64 getFirstNewsID();
    virtual QString appendNewQueryString();
    virtual QString prependNewQueryString();
    
private:
    // The feed that we're using here has gotta be All News.  Like, duh.
    AllNewsFeedItem* allNews;
};

#endif // LOADALLNEWSOPERATION_H
