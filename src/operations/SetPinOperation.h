#ifndef SETPINOPERATION_H
#define SETPINOPERATION_H

#include "DBOperation.h"
#include "../models/PinnedFeedItem.h"

/*!
    \brief Sets or unsets a pin on a news item.
 */
class SetPinOperation : public DBOperation
{
    Q_OBJECT
public:
    /*!
        \brief SetPinOperation Sets or unsets a pin on a news item
        \param parent
        \param pinnedNews The pinned feed, so we can update its "unread" count.
        \param newsID NewsItem database ID to pin/unpin
        \param pin If true the pin is set, if it's false it's unset
     */
    explicit SetPinOperation(OperationManager *parent, PinnedFeedItem* pinnedNews, qint64 newsID, bool pin);

signals:

public slots:

    virtual void execute();

    // Returns the item ID.
    inline qint64 getNewsID() { return newsID; }

    // If true it was pinned, false unpinned
    inline bool getPin() { return pin; }

private:
    PinnedFeedItem *pinnedNews;
    qint64 newsID;
    bool pin;

};

#endif // SETPINOPERATION_H
