#ifndef LISVELLOADNEWSOPERATION_H
#define LISVELLOADNEWSOPERATION_H

#include "LoadNews.h"

#include <QString>

#include "../models/LisvelFeedItem.h"

class LisvelLoadNewsOperation : public LoadNews
{
    Q_OBJECT
public:
    explicit LisvelLoadNewsOperation(OperationManager *parent, LisvelFeedItem* feedItem, LoadMode mode, int loadLimit = 15);

public slots:
    virtual void execute();

private slots:

    bool doPrepend();

    bool doAppend();

protected slots:

    // Returns a SQL string of all in-memory news item IDs as a SQL string.
    QString getLoadedIDString();

    /**
     * @brief Finds the very first item available in this feed, loaded or not. This is
     *        used to determine whether or not to display the top bookmark.
     * @return id of the first item in the entire feed.
     */
    virtual qint64 getFirstNewsID() =0;

    /**
     * @return The query string used by the append new operation.
     */
    virtual QString appendNewQueryString() = 0;

    /**
     * @return The query string used by the prepend new operation.
     */
    virtual QString prependNewQueryString() = 0;

private:
    // Lisvel feed.
    LisvelFeedItem* lisvelNews;

};

#endif // LISVELLOADNEWSOPERATION_H
