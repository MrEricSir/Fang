#ifndef LOADFOLDEROPERATION_H
#define LOADFOLDEROPERATION_H

#include "LisvelLoadNewsOperation.h"
#include "../models/FolderFeedItem.h"

class LoadFolderOperation : public LisvelLoadNewsOperation
{
    Q_OBJECT

public:
    explicit LoadFolderOperation(OperationManager *parent, FolderFeedItem* feedItem,
                                 LoadMode mode, int loadLimit = 15);
    virtual ~LoadFolderOperation();

protected slots:

    virtual qint64 getFirstNewsID();
    virtual QString appendNewQueryString();
    virtual QString prependNewQueryString();
};

#endif // LOADFOLDEROPERATION_H
