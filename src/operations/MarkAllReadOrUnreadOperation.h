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

public slots:
    virtual void execute();

private:
    bool markAsRead;
};

#endif // MARKALLREADORUNREADOPERATION_H
