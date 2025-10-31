#ifndef PINNEDFEEDITEM_H
#define PINNEDFEEDITEM_H

#include "LisvelFeedItem.h"

#include <QObject>

#include "ListModel.h"

/**
 * @brief A pseudo-feed of all pinned news items.
 */
class PinnedFeedItem : public LisvelFeedItem
{
    Q_OBJECT
public:
    explicit PinnedFeedItem(ListModel *feedList);

    // No bookmarks allowed, sir.
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward);

    // No bookmarks! No! Not for you!
    virtual bool bookmarksEnabled() const;

signals:

public slots:

};

#endif // PINNEDFEEDITEM_H
