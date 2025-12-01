#ifndef UPDATETITLEOPERATION_H
#define UPDATETITLEOPERATION_H

#include "DBOperationSynchronous.h"

#include <QObject>
#include <QString>

#include "../models/FeedItem.h"

class UpdateTitleOperation : public DBOperationSynchronous
{
    Q_OBJECT
public:
    explicit UpdateTitleOperation(OperationManager *parent, FeedItem* feed);
    
signals:
    
public slots:
    virtual void executeSynchronous();
    
private:
    FeedItem* feed;
};

#endif // UPDATETITLEOPERATION_H
