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
    explicit LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString &title, QObject *parent = 0);

    /**
     * @brief When the feed changes away from all news, this kills the view.
     */
    virtual void clearNews();

    /**
     * @brief List of all news IDs that have been in the view.
     *
     * @return
     */
    QList<qint64>* newsIDs() { return &_newsIDs; }

    /**
     * @param item
     * @param allowBackward
     * @return True if this item can be bookmarked.
     */
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward);

private:
    // Though the news items are shown temporarily, the view is inifinite.  This
    // ever-growing list of db IDs ensures that by containing a temporary view.
    QList<qint64> _newsIDs;

};

#endif // LISVELFEEDITEM_H
