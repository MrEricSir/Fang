#include "SearchFeedItem.h"

SearchFeedItem::SearchFeedItem(ListModel *feedList) :
    LisvelFeedItem(FEED_ID_SEARCH, -3, "Search Results", feedList),
    searchScope(Scope::Global),
    scopeId(-1)
{
}

void SearchFeedItem::setScope(Scope scope, qint64 id)
{
    searchScope = scope;
    scopeId = id;
}

void SearchFeedItem::setSearchQuery(const QString& query)
{
    searchQuery = query.trimmed();

    // Clear any existing results when starting a new search.
    clearNews();

    // Update title to show what we're searching for.
    if (!searchQuery.isEmpty()) {
        setTitle("Search: " + searchQuery);
    } else {
        setTitle("Search Results");
    }
}

bool SearchFeedItem::canBookmark(qint64 bookmarkID, bool allowBackward)
{
    Q_UNUSED(bookmarkID);
    Q_UNUSED(allowBackward);

    // Search results are relevance-ordered, not chronological.
    // Bookmarking doesn't make sense in this context.
    return false;
}

bool SearchFeedItem::bookmarksEnabled() const
{
    return false;
}
