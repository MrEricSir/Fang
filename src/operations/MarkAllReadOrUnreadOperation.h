#ifndef MARKALLREADORUNREADOPERATION_H
#define MARKALLREADORUNREADOPERATION_H

#include <QObject>

#include "DBOperation.h"
#include "../models/FeedItem.h"

class MarkAllReadOrUnreadOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit MarkAllReadOrUnreadOperation(OperationManager *parent, FeedItem* feed, bool markAsRead = true);

public slots:
    virtual void execute();

private:
    FeedItem *feed;
    bool markAsRead;
};

#endif // MARKALLREADORUNREADOPERATION_H
