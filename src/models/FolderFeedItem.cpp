#include "FolderFeedItem.h"

FolderFeedItem::FolderFeedItem(const qint64 id, const qint32 ordinal, const QString &title, bool folder_open, QObject *parent)
    : LisvelFeedItem(id, ordinal, title, parent)
{
    setFolderOpen(folder_open);
}

FolderFeedItem::~FolderFeedItem()
{
    // Nothing to do here, yet.
}
