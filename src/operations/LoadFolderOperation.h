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

    virtual qint64 getFirstNewsID() override;
    virtual QString appendNewQueryString() override;
    virtual QString prependNewQueryString() override;
    virtual QString appendAfterPositionQueryString() override;
    virtual void bindQueryParameters(QSqlQuery& query) override;
};

#endif // LOADFOLDEROPERATION_H
