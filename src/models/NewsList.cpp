#include "NewsItem.h"
#include "NewsList.h"
#include "../utilities/FangLogging.h"
#include "../utilities/ErrorHandling.h"

// NewsSlot implementation
NewsSlot::NewsSlot(NewsItem* newsItem)
    : position(newsItem->getDbID(), newsItem->getTimestamp())
    , item(newsItem)
{}

// NewsList implementation
NewsList::NewsList(FangObject *parent)
    : FangObject{parent}
{}

NewsList::~NewsList()
{
    clear();
}

void NewsList::clear()
{
    // Delete each loaded news item.
    for (NewsSlot& slot : slotList) {
        if (slot.item) {
            slot.item->deleteLater();
        }
    }

    slotList.clear();
    loadedSet.clear();
    displayStart = 0;
    displayEnd = 0;
}

qsizetype NewsList::size() const
{
    return displayEnd - displayStart;
}

bool NewsList::isEmpty() const
{
    return size() == 0;
}

NewsItem *NewsList::first() const
{
    if (isEmpty()) {
        return nullptr;
    }
    return slotList.at(displayStart).item;
}

NewsItem *NewsList::last() const
{
    if (isEmpty()) {
        return nullptr;
    }
    return slotList.at(displayEnd - 1).item;
}

NewsItem *NewsList::at(qsizetype i) const
{
    qsizetype fullIndex = displayStart + i;
    if (fullIndex < displayStart || fullIndex >= displayEnd) {
        qCCritical(logModel) << "NewsList::at: Index" << i << "out of display window bounds [0," << size() << ")";
        return nullptr;
    }
    return slotList.at(fullIndex).item;
}

bool NewsList::contains(NewsItem* value) const
{
    if (!loadedSet.contains(value)) {
        return false;
    }
    // Check if it's in the display window
    for (qsizetype i = displayStart; i < displayEnd; ++i) {
        if (slotList.at(i).item == value) {
            return true;
        }
    }
    return false;
}

qsizetype NewsList::indexOf(const NewsItem *value, qsizetype from) const
{
    // Search within display window only
    for (qsizetype i = displayStart + from; i < displayEnd; ++i) {
        if (slotList.at(i).item == value) {
            return i - displayStart;  // Return index relative to display window
        }
    }
    return -1;
}

qsizetype NewsList::fullSize() const
{
    return slotList.size();
}

NewsItem* NewsList::fullAt(qsizetype i) const
{
    if (i < 0 || i >= slotList.size()) {
        return nullptr;
    }
    return slotList.at(i).item;  // May be nullptr if unloaded
}

bool NewsList::containsID(qint64 id) const
{
    return fullIndexForItemID(id) >= 0;
}

qsizetype NewsList::fullIndexForItemID(qint64 id) const
{
    for (qsizetype i = 0; i < slotList.size(); ++i) {
        if (slotList.at(i).id() == id) {
            return i;
        }
    }
    return -1;
}

bool NewsList::canPageUp() const
{
    return displayStart > 0;
}

bool NewsList::canPageDown() const
{
    return displayEnd < slotList.size();
}

qsizetype NewsList::pageUp(qsizetype count)
{
    qsizetype available = displayStart;  // Items before display window
    qsizetype toAdd = qMin(count, available);

    if (toAdd > 0) {
        // Check if any items in the range need reloading
        QList<qint64> toReload;
        for (qsizetype i = displayStart - toAdd; i < displayStart; ++i) {
            if (!slotList[i].isLoaded()) {
                toReload.append(slotList[i].id());
            }
        }

        // Reload if needed
        if (!toReload.isEmpty()) {
            FANG_CHECK(reloadCallback, "NewsList::pageUp: Reload callback not set");
            if (reloadCallback) {
                QList<NewsItem*> reloaded = reloadCallback(toReload);
                populateSlots(reloaded);

                // Verify all items were reloaded
                for (qsizetype i = displayStart - toAdd; i < displayStart; ++i) {
                    FANG_CHECK(slotList[i].isLoaded(),
                               "NewsList::pageUp: Item not loaded after reload callback");
                }
            }
        }

        displayStart -= toAdd;
        qCDebug(logModel) << "NewsList::pageUp: Expanded window by" << toAdd
                          << "items, new window [" << displayStart << "," << displayEnd << ")";

        // Last step: Verify integrity.
        verifyDisplayWindowIntegrity();
    }

    return toAdd;
}

qsizetype NewsList::pageDown(qsizetype count)
{
    qsizetype available = slotList.size() - displayEnd;  // Items after display window
    qsizetype toAdd = qMin(count, available);

    if (toAdd > 0) {
        // Check if any items in the range need reloading
        QList<qint64> toReload;
        for (qsizetype i = displayEnd; i < displayEnd + toAdd; ++i) {
            if (!slotList[i].isLoaded()) {
                toReload.append(slotList[i].id());
            }
        }

        // Reload if needed
        if (!toReload.isEmpty()) {
            FANG_CHECK(reloadCallback, "NewsList::pageDown: Reload callback not set");
            if (reloadCallback) {
                QList<NewsItem*> reloaded = reloadCallback(toReload);
                populateSlots(reloaded);

                // Verify all items were reloaded
                for (qsizetype i = displayEnd; i < displayEnd + toAdd; ++i) {
                    FANG_CHECK(slotList[i].isLoaded(),
                               "NewsList::pageDown: Item not loaded after reload callback");
                }
            }
        }

        displayEnd += toAdd;
        qCDebug(logModel) << "NewsList::pageDown: Expanded window by" << toAdd
                          << "items, new window [" << displayStart << "," << displayEnd << ")";

        // Last step: Verify integrity.
        verifyDisplayWindowIntegrity();
    }

    return toAdd;
}

void NewsList::append(NewsItem *value)
{
    if (loadedSet.contains(value)) {
        qCCritical(logModel) << "NewsList::append: Attempting to add duplicate item with ID" << value->getDbID();
        return;
    }

    loadedSet.insert(value);
    slotList.append(NewsSlot(value));
    // Expand display window to include the new item
    displayEnd = slotList.size();

    // Check if we need to unload distant items
    checkMemoryBounds();
}

void NewsList::prepend(NewsItem *value)
{
    if (loadedSet.contains(value)) {
        qCCritical(logModel) << "NewsList::prepend: Attempting to add duplicate item with ID" << value->getDbID();
        return;
    }

    loadedSet.insert(value);
    slotList.prepend(NewsSlot(value));
    // Shift display window indices to account for the new item at the front
    // and keep the same items visible (plus the new one)
    displayEnd++;
    // displayStart stays at 0 to include the new item

    // Check if we need to unload distant items
    checkMemoryBounds();
}

void NewsList::shrinkDisplayWindow(bool fromStart, qsizetype numberToRemove)
{
    qsizetype toRemove = qMin(numberToRemove, size());

    if (fromStart) {
        displayStart += toRemove;
    } else {
        displayEnd -= toRemove;
    }

    qCDebug(logModel) << "NewsList::shrinkDisplayWindow: Removed" << toRemove
                      << "from" << (fromStart ? "start" : "end")
                      << ", new window [" << displayStart << "," << displayEnd << ")"
                      << ", full list size" << slotList.size();
}

void NewsList::removeAndDelete(bool fromStart, qsizetype numberToRemove)
{
    // Now just shrinks the display window - items stay in memory for paging
    shrinkDisplayWindow(fromStart, numberToRemove);
}

NewsItem *NewsList::newsItemForID(const qint64 id) const
{
    if (id < 0) {
        // Invalid ID.
        qCCritical(logModel) << "NewsList::newsItemForID: Invalid news ID" << id;
        return nullptr;
    }

    qsizetype index = indexForItemID(id);
    return index < 0 ? nullptr : at(index);
}

NewsItem *NewsList::fullNewsItemForID(const qint64 id) const
{
    if (id < 0) {
        qCCritical(logModel) << "NewsList::fullNewsItemForID: Invalid news ID" << id;
        return nullptr;
    }

    qsizetype index = fullIndexForItemID(id);
    return index < 0 ? nullptr : slotList.at(index).item;  // May be nullptr if unloaded
}

qsizetype NewsList::indexForItemID(const qint64 id) const
{
    // Search within display window only
    for (qsizetype i = displayStart; i < displayEnd; ++i) {
        if (slotList.at(i).id() == id) {
            return i - displayStart;  // Return index relative to display window
        }
    }
    return -1;
}

void NewsList::setReloadCallback(ReloadCallback callback)
{
    reloadCallback = callback;
}

NewsPosition NewsList::positionAt(qsizetype i) const
{
    if (i < 0 || i >= slotList.size()) {
        return NewsPosition();  // Invalid
    }
    return slotList.at(i).position;
}

qsizetype NewsList::loadedCount() const
{
    return loadedSet.size();
}

void NewsList::checkMemoryBounds()
{
    // Keep at most 2x the display window size loaded in memory
    qsizetype windowSize = displayEnd - displayStart;
    qsizetype maxLoaded = windowSize * 2;

    // Ensure minimum threshold to avoid thrashing
    if (maxLoaded < 30) {
        maxLoaded = 30;
    }

    qsizetype currentLoaded = loadedCount();
    if (currentLoaded > maxLoaded) {
        unloadDistantItems(currentLoaded - maxLoaded);
    }
}

void NewsList::unloadDistantItems(qsizetype count)
{
    qsizetype unloaded = 0;

    // Prefer unloading from the start if user has scrolled down
    if (displayStart > 0) {
        // Unload from the beginning (oldest items, furthest from display)
        for (qsizetype i = 0; i < displayStart && unloaded < count; ++i) {
            if (slotList[i].isLoaded()) {
                loadedSet.remove(slotList[i].item);
                slotList[i].item->deleteLater();
                slotList[i].item = nullptr;
                unloaded++;
            }
        }
    }

    // If we still need to unload more, unload from the end
    if (unloaded < count) {
        for (qsizetype i = slotList.size() - 1; i >= displayEnd && unloaded < count; --i) {
            if (slotList[i].isLoaded()) {
                loadedSet.remove(slotList[i].item);
                slotList[i].item->deleteLater();
                slotList[i].item = nullptr;
                unloaded++;
            }
        }
    }

    if (unloaded > 0) {
        qCDebug(logModel) << "NewsList::unloadDistantItems: Unloaded" << unloaded
                          << "items, loaded count now" << loadedCount();
    }
}

void NewsList::populateSlots(const QList<NewsItem*>& items)
{
    // Match reloaded items to their slotList by ID
    for (NewsItem* item : items) {
        qint64 id = item->getDbID();
        qsizetype index = fullIndexForItemID(id);

        if (index >= 0 && !slotList[index].isLoaded()) {
            slotList[index].item = item;
            loadedSet.insert(item);
            qCDebug(logModel) << "NewsList::populateSlots: Reloaded item ID" << id
                              << "at index" << index;
        } else if (index < 0) {
            qCWarning(logModel) << "NewsList::populateSlots: Item ID" << id
                                << "not found in slotList, deleting";
            item->deleteLater();
        } else {
            qCWarning(logModel) << "NewsList::populateSlots: Item ID" << id
                                << "already loaded, deleting duplicate";
            item->deleteLater();
        }
    }
}

bool NewsList::verifyDisplayWindowIntegrity() const
{
    bool allLoaded = true;
    for (qsizetype i = displayStart; i < displayEnd; ++i) {
        if (!slotList[i].isLoaded()) {
            qCCritical(logModel) << "NewsList::verifyDisplayWindowIntegrity: Unloaded item at index"
                                 << i << "(ID:" << slotList[i].id() << ") within display window ["
                                 << displayStart << "," << displayEnd << ")";
            allLoaded = false;
        }
    }
    return allLoaded;
}
