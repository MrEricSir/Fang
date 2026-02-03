#ifndef NEWSLIST_H
#define NEWSLIST_H

#include <QList>
#include <functional>

#include "../FangObject.h"
#include "NewsPosition.h"

class NewsItem;

/*!
    \brief Represents a slot in the news list that may or may not have a loaded NewsItem.

    The position (timestamp + ID) is always present for ordering purposes.
    The item pointer may be nullptr if the item has been unloaded to save memory.
 */
struct NewsSlot {
    NewsPosition position;  // Always present (timestamp + ID)
    NewsItem* item;         // nullptr when unloaded

    NewsSlot(NewsItem* newsItem);

    inline bool isLoaded() const { return item != nullptr; }
    inline qint64 id() const { return position.id(); }
};

/*!
    \brief Callback type for reloading unloaded news items from the database.
    Takes a list of news IDs and returns the corresponding NewsItem objects.
 */
using ReloadCallback = std::function<QList<NewsItem*>(const QList<qint64>&)>;

/*!
    \brief The NewsList class contains a custom list type that internally is also stored as a set.

    The list maintains ALL loaded items in memory, with a "display window" that tracks
    which items are currently visible to the UI. This allows paging through previously
    loaded items without re-fetching from the database.

    Public methods (size, first, last, at, indexOf) operate on the display window.
    Internal methods (fullSize, fullAt, etc.) operate on the complete list.
 */
class NewsList : public FangObject
{
public:
    explicit NewsList(FangObject *parent = nullptr);
    virtual ~NewsList();

    /*!
        \brief Delete everything in the list and clear it.
     */
    void clear();

    //////////////////////////////////////////
    // Display Window (reflects the web views)
    //////////////////////////////////////////

    qsizetype size() const;
    bool isEmpty() const;
    NewsItem* first() const;
    NewsItem* last() const;
    NewsItem* at(qsizetype i) const;
    bool contains(NewsItem* value) const;
    qsizetype indexOf(const NewsItem* value, qsizetype from = 0) const;

    ///////////////////////////////////////
    // Full List Methods (all loaded items)
    ///////////////////////////////////////

    /*!
        \brief Returns the total number of items loaded (including those outside display window).
     */
    qsizetype fullSize() const;

    /*!
        \brief Returns item at index in the full list.
     */
    NewsItem* fullAt(qsizetype i) const;

    /*!
        \brief Checks if an item with the given ID exists anywhere in the full list.
     */
    bool containsID(qint64 id) const;

    /*!
        \brief Returns the index in the full list for a given ID, or -1 if not found.
     */
    qsizetype fullIndexForItemID(qint64 id) const;

    ////////////////////////////
    // Display Window Navigation
    ////////////////////////////

    /*!
        \brief Returns true if there are loaded items before the display window.
     */
    bool canPageUp() const;

    /*!
        \brief Returns true if there are loaded items after the display window.
     */
    bool canPageDown() const;

    /*!
        \brief Expands the display window to include N more items at the start.
        \return The actual number of items added to the window.
     */
    qsizetype pageUp(qsizetype count);

    /*!
        \brief Expands the display window to include N more items at the end.
        \return The actual number of items added to the window.
     */
    qsizetype pageDown(qsizetype count);

    /*!
        \brief Gets the display window start index in the full list.
     */
    inline qsizetype getDisplayStart() const { return displayStart; }

    /*!
        \brief Gets the display window end index (exclusive) in the full list.
     */
    inline qsizetype getDisplayEnd() const { return displayEnd; }

    ///////////////////////
    // Modification Methods
    ///////////////////////

    void append(NewsItem* value);
    void prepend(NewsItem* value);

    /*!
        \brief Shrinks the display window from the start or end.

        Items are NOT deleted, they remain in the full list for potential paging.
        \param fromStart True to shrink from start, false to shrink from end.
        \param numberToRemove Number of items to remove from the display window.
     */
    void shrinkDisplayWindow(bool fromStart, qsizetype numberToRemove);

    /*!
        \brief Shrinks the display window. Items remain in memory for paging.
     */
    void removeAndDelete(bool fromStart, qsizetype numberToRemove);

    /*!
        \brief If loaded, returns the news item for a given ID (searches display window only).
        Linear time complexity.
     */
    NewsItem* newsItemForID(const qint64 id) const;

    /*!
        \brief Returns the news item for a given ID (searches FULL list, not just display window).
        Linear time complexity.
     */
    NewsItem* fullNewsItemForID(const qint64 id) const;

    /*!
        \brief Returns the index within the display window for a given ID, or -1 if not found.
        Linear time complexity.
     */
    qsizetype indexForItemID(const qint64 id) const;

    ////////////////////////////
    // Reload Callback
    ////////////////////////////

    /*!
        \brief Sets the callback function for reloading unloaded items from the database.
        \param callback Function that takes a list of IDs and returns NewsItem objects.
     */
    void setReloadCallback(ReloadCallback callback);

    ////////////////////////////
    // Slot Access
    ////////////////////////////

    /*!
        \brief Returns the NewsPosition for an item at the given full index.
        Works for both loaded and unloaded items since positions are always present.
        \param i Index in the full list (not display window)
        \return The position, or invalid NewsPosition if index is out of bounds
     */
    NewsPosition positionAt(qsizetype i) const;

    /*!
        \brief Returns the count of currently loaded items.
     */
    qsizetype loadedCount() const;

    // Iterator class for iterating over NewsItem* in the display window
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = NewsItem*;
        using difference_type = qsizetype;
        using pointer = NewsItem**;
        using reference = NewsItem*&;

        Iterator(QList<NewsSlot>* slotList, qsizetype index) : slotList(slotList), index(index) {}

        NewsItem* operator*() const { return slotList->at(index).item; }
        Iterator& operator++() { ++index; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++index; return tmp; }
        bool operator==(const Iterator& other) const { return index == other.index; }
        bool operator!=(const Iterator& other) const { return index != other.index; }

    private:
        QList<NewsSlot>* slotList;
        qsizetype index;
    };

    // For list iteration (iterates display window only).
    inline Iterator begin() { return Iterator(&slotList, displayStart); }
    inline Iterator end() { return Iterator(&slotList, displayEnd); }

private:
    // Ordered list of ALL news slots (items may be loaded or unloaded).
    QList<NewsSlot> slotList;

    // Set of LOADED news items for fast "contains" check.
    QSet<NewsItem*> loadedSet;

    // Callback for reloading items from database.
    ReloadCallback reloadCallback;

    // Display window: [displayStart, displayEnd) - indices into `slotList`
    qsizetype displayStart = 0;
    qsizetype displayEnd = 0;

    ////////////////////////////
    // Memory Management
    ////////////////////////////

    /*!
        \brief Checks if loaded item count exceeds threshold and unloads if needed.
        Called after append/prepend operations.
     */
    void checkMemoryBounds();

    /*!
        \brief Unloads items furthest from the display window.
        \param count Number of items to unload.
     */
    void unloadDistantItems(qsizetype count);

    /*!
        \brief Populates slotList with reloaded NewsItem objects.
        \param items The reloaded items (matched by ID to existing slotList).
     */
    void populateSlots(const QList<NewsItem*>& items);
};

#endif // NEWSLIST_H
