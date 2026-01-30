#ifndef LOADPINNEDNEWSOPERATION_H
#define LOADPINNEDNEWSOPERATION_H

#include "LisvelLoadNewsOperation.h"
#include "../models/PinnedFeedItem.h"

/*!
    \brief Loads news items that are pinned.
 */
class LoadPinnedNewsOperation : public LisvelLoadNewsOperation
{
    Q_OBJECT
public:
    explicit LoadPinnedNewsOperation(OperationManager *parent, PinnedFeedItem* feedItem, LoadMode mode, int loadLimit = 15);

protected slots:

    virtual qint64 getFirstNewsID();
    virtual QString appendNewQueryString();
    virtual QString prependNewQueryString();

};

#endif // LOADPINNEDNEWSOPERATION_H
