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
    
protected slots:

    virtual qint64 getFirstNewsID() override;
    virtual QString appendNewQueryString() override;
    virtual QString prependNewQueryString() override;
    virtual QString appendAfterPositionQueryString() override;
};

#endif // LOADALLNEWSOPERATION_H
