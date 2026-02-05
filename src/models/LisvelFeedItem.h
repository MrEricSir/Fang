#ifndef LISVELFEEDITEM_H
#define LISVELFEEDITEM_H

#include "FeedItem.h"
#include "NewsPosition.h"

/*!
    \brief LISVEL is Fang's secret sauce for keeping a stable order of news
    items as you scroll through the view.

    LISVEL stands for:
      Limited
      Infinite
      Scrolling
      Via
      Exclusion
      List

    The NewsList maintains all loaded items in memory with a display window,
    allowing paging through previously loaded content without re-fetching
    from the database.
 */
class LisvelFeedItem : public FeedItem
{
    Q_OBJECT
public:
    explicit LisvelFeedItem(const qint64 id, const qint32 ordinal, const QString &title, QObject *parent = nullptr);

    /*!
        \param proposedBookmarkID
        \param allowBackward
        \return True if this item can be bookmarked.
     */
    virtual bool canBookmark(qint64 proposedBookmarkID, bool allowBackward) override;

    /*!
        \brief Overrides setBookmark to capture the timestamp for proper ordering.
     */
    virtual void setBookmark(qint64 toBookmarkID) override;

    /*!
        \brief Gets the current bookmark position (timestamp, id tuple).
     */
    inline const NewsPosition& getBookmarkPosition() const { return _bookmarkPosition; }

private:
    // Position of current bookmark (timestamp, id) for proper ordering comparison
    NewsPosition _bookmarkPosition;
};

#endif // LISVELFEEDITEM_H
