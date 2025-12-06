#include "LisvelLoadNewsOperation.h"
#include "src/models/NewsList.h"


LisvelLoadNewsOperation::LisvelLoadNewsOperation(OperationManager *parent, LisvelFeedItem *feedItem, LoadMode mode, int loadLimit, bool prependOnInit) :
    LoadNewsOperation(parent, feedItem, mode, loadLimit),
    lisvelNews(feedItem),
    prependOnInit(prependOnInit)
{
}

void LisvelLoadNewsOperation::executeSynchronous()
{
    qDebug() << "LisvelLoadNewsOperation::execute load for feed: " << lisvelNews->getDbID();
    // For an initial load, make sure the feed isn't populated yet.
    if (getMode() == LoadNewsOperation::Initial) {
        Q_ASSERT(feedItem->getNewsList() != nullptr || feedItem->getNewsList()->isEmpty());
    }

    // DB query/ies.
    bool dbResult = true;
    switch (getMode()) {
    case Initial:
    {
        dbResult &= doAppend();  // First load everything after bookmark.

        if (prependOnInit) {
            dbResult &= doPrepend(); // Now the stuff on top
        }

        break;
    }

    case Append:
    {
        dbResult &= doAppend();

        break;
    }

    case Prepend:
    {
        dbResult &= doPrepend();

        break;
    }

    default:
        // This means you added a new mode, but didn't add it to this switch.  Jerk.
        Q_ASSERT(false);
    }

    // Check if we done goofed.
    if (!dbResult) {
        reportError("DB error in LisvelLoadNewsOperation");

        return;
    }


    if (getMode() == Initial) {
        // For the initial load, set the bookmark to the first prepended item.
         // It's okay for the FeedItem not to have a bookmark.
        if (!listPrepend.isEmpty()) {
            feedItem->setBookmark(listPrepend.first()->getDbID());

        }

        // As an optimization, we only want to present *one* list -- an append list.
        // So we rewind our prepend list on top of it, then delete the prepend list.
        if (!listPrepend.isEmpty()) {
            for (NewsItem* newsItem: std::as_const(listPrepend)) {
                // News item list.
                listAppend.prepend(newsItem);
            }

            listPrepend.clear();
        }
    }

    // Append/prepend items from our lists.
    if (!listAppend.isEmpty()) {
        for (NewsItem* newsItem: std::as_const(listAppend)) {
            // News item list.
            feedItem->getNewsList()->append(newsItem);

            // News ID list.
            if (!lisvelNews->getNewsList()->contains(newsItem)) {
                lisvelNews->getNewsList()->append(newsItem);
            }
        }
    }

    if (!listPrepend.isEmpty()) {
        for (NewsItem* newsItem: std::as_const(listPrepend)) {
            // News item list.
            feedItem->getNewsList()->prepend(newsItem);

            // News ID list.
            if (!lisvelNews->getNewsList()->contains(newsItem)) {
                lisvelNews->getNewsList()->prepend(newsItem);
            }
        }
    }

    // Set the first possible ID for that top bookmark display action.
    lisvelNews->setFirstNewsID(getFirstNewsID());
}

bool LisvelLoadNewsOperation::doPrepend()
{
    // Remaining items to load.
    int remainingLoadLimit = getLoadLimit();

    //
    // STEP ONE: Page up the ID list.
    //
    NewsItem* firstItem = lisvelNews->getNewsList()->isEmpty() ? nullptr :
                             lisvelNews->getNewsList()->first();

    // Assuming we even got a valid ID, only continue if the items isn't the first
    // one on the list.  If it is, we're already at the top and can skip over this.
    if (firstItem && lisvelNews->getNewsList()->indexOf(firstItem) > 0) {
        // Get the initial and previous list positions.
        int initial = lisvelNews->getNewsList()->indexOf(firstItem) - 1; // Remember that it's > 0!
        int previous = qMax(0, initial - remainingLoadLimit);

        QString idString;   // List of IDs
        QString whenString; // List if WHEN statements for ordering switch statement.
        int index = 0;
        for(int i = initial; i >= previous; i--, index++) {
            if (index != 0) {
                idString += ", ";
            }

            QString currentID = QString::number(lisvelNews->getNewsList()->at(i)->getDbID());
            idString += currentID;
            whenString += "WHEN " + currentID + " THEN " + QString::number(index) + " ";
        }

        // Load the items.
        QString queryString = "SELECT * FROM NewsItemTable N WHERE id IN (" + idString +
                              ") ORDER BY CASE id " + whenString + " END LIMIT :load_limit";
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);

        if (!query.exec()) {
            qDebug() << "Could not load news! (lisvel prepend step 1)";
            qDebug() << query.lastError();

            return false;
        }

        // Extract the query.
        queryToNewsList(query, &listPrepend);

        // Keep track of our load limit.
        remainingLoadLimit -= listPrepend.size();
    }

    //
    // STEP TWO: Load new items.
    //

    // Do we still have items to load?  If so, load 'em now.
    QString prependQuery = prependNewQueryString();
    if (remainingLoadLimit > 0 && !prependQuery.isEmpty()) {
        QSqlQuery query(db());
        query.prepare(prependQuery);
        query.bindValue(":load_limit", remainingLoadLimit);

        if (!query.exec()) {
            qDebug() << "Could not load news! (lisvel prepend step 2)";
            qDebug() << query.lastError();

            return false;
        }

        // Extract the query into our news list.
        queryToNewsList(query, &listPrepend);
    }

    return true;
}

bool LisvelLoadNewsOperation::doAppend()
{
    // Remaining items to load.
    int remainingLoadLimit = getLoadLimit();

    //
    // STEP ONE: Page down the ID list.
    //
    NewsItem* lastItem = lisvelNews->getNewsList()->isEmpty() ? nullptr :
                             lisvelNews->getNewsList()->last();


    // Assuming we even got a valid ID, only continue if the items isn't the last
    // one on the list.  If it is, we're already at the bottom and can skip over this.
    if (lastItem && lisvelNews->getNewsList()->indexOf(lastItem) < lisvelNews->getNewsList()->size() - 1) {
        // Get the initial and next list positions.
        int initial = lisvelNews->getNewsList()->indexOf(lastItem) + 1; // Remember that it's not at the end!
        int next = qMin(lisvelNews->getNewsList()->size() - 1, initial + remainingLoadLimit);

        QString idString;   // List of IDs
        QString whenString; // List if WHEN statements for ordering switch statement.
        int index = 0;
        for(int i = initial; i <= next; i++, index++) {
            if (index != 0) {
                idString += ", ";
            }

            QString currentID = QString::number(lisvelNews->getNewsList()->at(i)->getDbID());
            idString += currentID;
            whenString += "WHEN " + currentID + " THEN " + QString::number(index) + " ";
        }

        // Load the items.
        QString queryString = "SELECT * FROM NewsItemTable N WHERE id IN (" + idString +
                              ") ORDER BY CASE id " + whenString + " END LIMIT :load_limit";
        qDebug() << " ===== doAppend query: " << queryString;
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);

        if (!query.exec()) {
            // qDebug() << "Could not load news! (lisvel append step 1)";
            qDebug() << query.lastError();

            return false;
        }

        // Extract the query.
        queryToNewsList(query, &listAppend);

        // Keep track of our load limit.
        remainingLoadLimit -= listAppend.size();
    }

    //
    // STEP TWO: Load new items.
    //

    // Do we still have items to load?  If so, load 'em now.
    if (remainingLoadLimit > 0) {
        QSqlQuery query(db());
        // qDebug() << " ===== doAppend new query: " << appendNewQueryString();
        query.prepare(appendNewQueryString());
        query.bindValue(":load_limit", remainingLoadLimit);

        if (!query.exec()) {
            qDebug() << "Could not load news! (lisvel append step 2)";
            qDebug() << query.lastError();

            return false;
        }

        // Extract the query into our news list.
        queryToNewsList(query, &listAppend);
    }

    return true;
}

QString LisvelLoadNewsOperation::getLoadedIDString()
{
    QString ret = "";

    qsizetype i = 0;
    qsizetype lastIndex = lisvelNews->getNewsList()->size();

    for (NewsItem* item : *feedItem->getNewsList()) {
        ret += QString::number(item->getDbID());
        i++;

        if (lastIndex != i) {
            ret += ", ";
        }
    }

    return ret;
}
