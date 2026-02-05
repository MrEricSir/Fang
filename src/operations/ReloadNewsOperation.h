#ifndef RELOADNEWSOPERATION_H
#define RELOADNEWSOPERATION_H

#include <QList>

#include "DBOperationSynchronous.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

/*!
    \brief Reloads specific NewsItems from the database by their IDs.

    This operation is used when items have been unloaded from memory
    to save resources, and need to be reloaded when the user scrolls
    back to view them.
 */
class ReloadNewsOperation : public DBOperationSynchronous
{
    Q_OBJECT
public:
    /*!
        \param parent    The operation manager
        \param feedItem  The feed item that owns these news items
        \param ids       List of news item IDs to reload
     */
    explicit ReloadNewsOperation(OperationManager *parent, FeedItem* feedItem, const QList<qint64>& ids);

    virtual ~ReloadNewsOperation() = default;

public slots:
    virtual void executeSynchronous() override;

    /*!
        \return List of reloaded NewsItem objects.
     */
    inline QList<NewsItem*>& getReloadedItems() { return reloadedItems; }

private:
    FeedItem* feedItem;
    QList<qint64> idsToReload;
    QList<NewsItem*> reloadedItems;
};

#endif // RELOADNEWSOPERATION_H
