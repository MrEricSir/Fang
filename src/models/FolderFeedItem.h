#ifndef FOLDERFEEDITEM_H
#define FOLDERFEEDITEM_H

#include <QObject>
#include "LisvelFeedItem.h"

class FolderFeedItem : public LisvelFeedItem
{
    Q_OBJECT
public:
    explicit FolderFeedItem(const qint64 id, const qint32 ordinal, const QString &title, bool folder_open, QObject *parent = nullptr);

public slots:

    // Yup, it's a folder!
    virtual bool isFolder() const { return true; }

private:

};

#endif // FOLDERFEEDITEM_H
