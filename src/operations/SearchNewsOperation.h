#ifndef SEARCHNEWSOPERATION_H
#define SEARCHNEWSOPERATION_H

#include "LisvelLoadNewsOperation.h"

#include <QString>

class LisvelFeedItem;

/*!
    \brief Loads news items matching a full-text search query using FTS5 ordered by relevance.

    Can search in:
    - Global (all feeds)
    - A single feed
    - A folder
 */
class SearchNewsOperation : public LisvelLoadNewsOperation
{
    Q_OBJECT
public:
    /*!
        \brief Search scope enumeration.
     */
    enum class Scope {
        Global, // Default
        Feed,
        Folder
    };

    /*!
        \param parent
        \param feedItem     Search feed item
        \param mode         Load mode (Initial or Append, Prepend is not supported)
        \param searchQuery  FTS5 search query string
        \param scope        Search scope (Global, Feed, or Folder)
        \param scopeId      Feed ID or Folder ID when scope is Feed or Folder
        \param loadLimit    Max number of items to load
     */
    explicit SearchNewsOperation(OperationManager *parent, LisvelFeedItem* feedItem,
                                  LoadMode mode, const QString& searchQuery,
                                  Scope scope = Scope::Global, qint64 scopeId = -1,
                                  int loadLimit = 15);

protected slots:
    virtual qint64 getFirstNewsID() override;
    virtual QString appendNewQueryString() override;
    virtual QString prependNewQueryString() override;
    virtual void bindQueryParameters(QSqlQuery& query) override;

    /*!
        \brief Custom query-to-list that uses highlighted title.
     */
    void queryToNewsListWithHighlights(QSqlQuery& query, QList<NewsItem*>* list);

public slots:
    virtual void execute() override;

private:
    QString searchQuery;
    Scope scope;
    qint64 scopeId;

    /*!
        \brief Sanitizes the search query for safe use in FTS5 MATCH.
        \return Sanitized query string safe for FTS5 MATCH clause.
     */
    QString sanitizeSearchQuery(const QString& query) const;
};

#endif // SEARCHNEWSOPERATION_H
