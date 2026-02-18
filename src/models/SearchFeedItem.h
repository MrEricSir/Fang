#ifndef SEARCHFEEDITEM_H
#define SEARCHFEEDITEM_H

#include "LisvelFeedItem.h"

#include <QObject>

#include "ListModel.h"

/*!
    \brief A pseudo-feed containing search results.

    Unlike other special feeds (AllNews, Pinned), the search feed is not
    shown in the sidebar. It's created on-demand when a search is performed
    and displays results in the main news view.

    Search results are relevance-ordered using FTS5's BM25 ranking, with
    matching terms highlighted using <mark> tags.

    Search can be scoped to:
    - Global (all feeds) - default
    - A specific feed (by feed_id)
    - A folder (all feeds within the folder)
 */
class SearchFeedItem : public LisvelFeedItem
{
    Q_OBJECT
public:
    /*!
        \brief Search scope enumeration.
     */
    enum class Scope {
        Global,   //!< Search all feeds (default)
        Feed,     //!< Search within a specific feed
        Folder    //!< Search within all feeds in a folder
    };

    explicit SearchFeedItem(ListModel *feedList);

    /*!
        \brief Sets the search query and clears any existing results.
        \param query The FTS5 search query string.
     */
    void setSearchQuery(const QString& query);

    /*!
        \brief Sets the search scope.
        \param scope The scope (Global, Feed, or Folder).
        \param scopeId The feed ID or folder ID when scope is Feed or Folder.
     */
    void setScope(Scope scope, qint64 scopeId = -1);

    /*!
        \return The current search query.
     */
    QString getSearchQuery() const { return searchQuery; }

    /*!
        \return True if a search query is set.
     */
    bool hasSearchQuery() const { return !searchQuery.isEmpty(); }

    /*!
        \return The current search scope.
     */
    Scope getScope() const { return searchScope; }

    /*!
        \return The scope ID (feed or folder ID).
     */
    qint64 getScopeId() const { return scopeId; }

    // Search doesn't support bookmarks (relevance-ordered, not chronological).
    virtual bool canBookmark(qint64 bookmarkID, bool allowBackward) override;
    virtual bool bookmarksEnabled() const override;

private:
    QString searchQuery;
    Scope searchScope;
    qint64 scopeId;
};

#endif // SEARCHFEEDITEM_H
