#include "MarkAllReadOrUnreadOperation.h"

MarkAllReadOrUnreadOperation::MarkAllReadOrUnreadOperation(OperationManager *parent, FeedItem* feed, bool markAsRead) :
    DBOperation(IMMEDIATE, parent),
    feed(feed),
    markAsRead(markAsRead)
{

}

void MarkAllReadOrUnreadOperation::execute()
{
    // TODO
    Q_ASSERT(false);
    //
}

