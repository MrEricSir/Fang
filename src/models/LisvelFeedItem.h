#ifndef LISVELFEEDITEM_H
#define LISVELFEEDITEM_H

#include <QList>

#include "FeedItem.h"

/**
 * @brief LISVEL is Fang's secret sauce for keeping a stable order of news
 * items as you scroll through the view.
 *
 * LISVEL stands for:
 *   Limmited
 *   Infinite
 *   Scrolling
 *   Via
 *   Exclusion
 *   List
 */
class LisvelFeedItem : public FeedItem
{
    Q_OBJECT
public:
    explicit LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString &title, QObject *parent = nullptr);

    /**
     * @param item
     * @param allowBackward
     * @return True if this item can be bookmarked.
     */
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward);
};

#endif // LISVELFEEDITEM_H
