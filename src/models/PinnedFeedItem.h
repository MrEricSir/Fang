#ifndef PINNEDFEEDITEM_H
#define PINNEDFEEDITEM_H

#include "FeedItem.h"

#include <QObject>

#include "ListModel.h"
#include "NewsItem.h"

/**
 * @brief A pseudo-feed of all pinned news items.
 */
class PinnedFeedItem : public FeedItem
{
    Q_OBJECT
public:
    explicit PinnedFeedItem(QObject *parent = 0);

    // No bookmarks allowed, sir.
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward);

signals:

public slots:

};

#endif // PINNEDFEEDITEM_H
