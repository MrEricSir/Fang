#include "LoadFolderOperation.h"


LoadFolderOperation::LoadFolderOperation(OperationManager *parent, FolderFeedItem *feedItem, LoadNews::LoadMode mode, int loadLimit)
    : LisvelLoadNewsOperation(parent, feedItem, mode, loadLimit, true)
{
    qDebug() << "=== LoadFolderOperation ===";
}

LoadFolderOperation::~LoadFolderOperation()
{

}

qint64 LoadFolderOperation::getFirstNewsID()
{
    return -1;
}

QString LoadFolderOperation::appendNewQueryString()
{
    // TODO: Implement
    return "ERROR WILL ROBINSON";
}

QString LoadFolderOperation::prependNewQueryString()
{
    // TODO: Implement
    return "ERROR WILL ROBINSON";
}
