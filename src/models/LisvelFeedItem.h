#ifndef LISVELFEEDITEM_H
#define LISVELFEEDITEM_H

#include <QSet>

#include "FeedItem.h"
#include "NewsPosition.h"

/*!
    \brief LISVEL is Fang's secret sauce for keeping a stable order of news
    items as you scroll through the view.

    LISVEL stands for:
      Limmited
      Infinite
      Scrolling
      Via
      Exclusion
      List

    The exclusion list tracks all news item IDs that have been loaded this session,
    even after items are trimmed from the display list. This prevents the same
    item from being loaded multiple times, which would cause ordering issues.
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

    /*!
        \brief Adds an ID to the exclusion list. Used when loading news.
     */
    inline void addToExclusionList(qint64 id) { exclusionList.insert(id); }

    /*!
        \brief Gets all IDs in the exclusion list.
     */
    inline const QSet<qint64>& getExclusionList() const { return exclusionList; }

    /*!
        \brief Clears the exclusion list.
     */
    inline void clearExclusionList() { exclusionList.clear(); }

private:
    // Set of all news item IDs loaded this session (persists even after trimming)
    QSet<qint64> exclusionList;

    // Position of current bookmark (timestamp, id) for proper ordering comparison
    NewsPosition _bookmarkPosition;
};

#endif // LISVELFEEDITEM_H
