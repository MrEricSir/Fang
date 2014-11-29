#ifndef LOADPINNEDNEWSOPERATION_H
#define LOADPINNEDNEWSOPERATION_H

#include "LoadNews.h"
#include "../models/PinnedFeedItem.h"

/**
 * @brief Loads news items that are pinned.
 */
class LoadPinnedNewsOperation : public LoadNews
{
    Q_OBJECT
public:
    explicit LoadPinnedNewsOperation(OperationManager *parent, PinnedFeedItem* feedItem, LoadMode mode, int loadLimit = 15);

public slots:
    virtual void execute();

protected slots:

     virtual bool executeLoadQuery(qint64 startId, bool append);

private:

    PinnedFeedItem* pinnedNews;

};

#endif // LOADPINNEDNEWSOPERATION_H
