#ifndef UPDATEFEEDOPERATION_H
#define UPDATEFEEDOPERATION_H

#include "Operation.h"
#include "../parser/Parser.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

class UpdateFeedOperation : public Operation
{
    Q_OBJECT
public:
    explicit UpdateFeedOperation(QObject *parent, FeedItem* feed);
    virtual ~UpdateFeedOperation();
    
signals:
    //void finished(Operation* myself);
    
public slots:
    virtual void execute();
    
private slots:
    void onFeedFinished();
    
private:
    Parser parser;
    FeedItem *feed;
    RawFeed* rawFeed;
};

#endif // UPDATEFEEDOPERATION_H
