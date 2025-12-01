#ifndef MARKALLREADORUNREADOPERATION_H
#define MARKALLREADORUNREADOPERATION_H

#include <QObject>

#include "BookmarkOperation.h"
#include "../models/FeedItem.h"

class MarkAllReadOrUnreadOperation : public BookmarkOperation
{
    Q_OBJECT
public:
    explicit MarkAllReadOrUnreadOperation(OperationManager *parent, FeedItem* feed, bool markAsRead = true);
    virtual ~MarkAllReadOrUnreadOperation() = default;

public slots:
    virtual void executeSynchronous();

private:
    bool markAsRead;
};

#endif // MARKALLREADORUNREADOPERATION_H
