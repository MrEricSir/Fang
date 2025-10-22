#ifndef UPDATEFEEDURL_H
#define UPDATEFEEDURL_H

#include <QString>
#include <QUrl>

#include "DBOperation.h"
#include "../models/FeedItem.h"

class UpdateFeedURLOperation : public DBOperation
{
    Q_OBJECT
public:
    /**
     * @brief UpdateFeedURLOperation
     * @param parent   Set this to the manager
     * @param feed     Feed to update
     * @param newURL   Updated URL of the feed
     */
    explicit UpdateFeedURLOperation(OperationManager *parent, FeedItem* feed, QUrl newURL);

public slots:
    virtual void execute();

private:
    FeedItem *feed;
    QUrl newURL;
};

#endif // UPDATEFEEDURL_H
