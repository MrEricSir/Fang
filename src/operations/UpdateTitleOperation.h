#ifndef UPDATETITLEOPERATION_H
#define UPDATETITLEOPERATION_H

#include "DBOperation.h"

#include <QObject>
#include <QString>

#include "../models/FeedItem.h"

class UpdateTitleOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit UpdateTitleOperation(OperationManager *parent, FeedItem* feed);
    
signals:
    
public slots:
    virtual void execute();
    
private:
    FeedItem* feed;
};

#endif // UPDATETITLEOPERATION_H
