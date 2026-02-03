#ifndef LISVELLOADNEWSOPERATION_H
#define LISVELLOADNEWSOPERATION_H

#include "LoadNewsOperation.h"

#include <QString>
#include <QSqlQuery>

#include "../models/LisvelFeedItem.h"

class LisvelLoadNewsOperation : public LoadNewsOperation
{
    Q_OBJECT
public:
    explicit LisvelLoadNewsOperation(OperationManager *parent, LisvelFeedItem* feedItem,
                                     LoadMode mode, int loadLimit = 15, bool prependOnInit = true);

public slots:
    virtual void executeSynchronous();

private slots:

    bool doPrepend();

    bool doAppend();

protected slots:

    // Returns a SQL string of all in-memory news item IDs as a SQL string.
    QString getLoadedIDString();

    /*!
        \brief Finds the very first item available in this feed, loaded or not. This is
               used to determine whether or not to display the top bookmark.
        \return id of the first item in the entire feed.
     */
    virtual qint64 getFirstNewsID() =0;

    /*!
        \return The query string used by the append new operation.
     */
    virtual QString appendNewQueryString() = 0;

    /*!
        \return The query string used by the prepend new operation, or the empty string
                if prepend is not supported.
     */
    virtual QString prependNewQueryString() = 0;

    /*!
        \return Query string to load items chronologically after a given position.
                Used as a fallback when append finds nothing but trimmed items need reloading.
                The query should use :last_timestamp, :last_id, and :load_limit parameters.
                Return empty string if not supported.
     */
    virtual QString appendAfterPositionQueryString();

    /*!
        \brief Bind additional parameters to query string.

        Not used here, but can be used by subclasses.
     */
    virtual void bindQueryParameters(QSqlQuery& query);

private:
    // Lisvel feed.
    LisvelFeedItem* lisvelNews;

    // If true, run a prepend when initializing the feed.
    bool prependOnInit;

};

#endif // LISVELLOADNEWSOPERATION_H
