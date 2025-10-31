#include "LisvelLoadNewsOperation.h"


LisvelLoadNewsOperation::LisvelLoadNewsOperation(OperationManager *parent, LisvelFeedItem *feedItem, LoadMode mode, int loadLimit, bool prependOnInit) :
    LoadNews(parent, feedItem, mode, loadLimit),
    lisvelNews(feedItem),
    prependOnInit(prependOnInit)
{
}

void LisvelLoadNewsOperation::execute()
{
    // For an initial load, make sure the feed isn't populated yet.
    if (getMode() == LoadNews::Initial) {
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
        // For the initial load, set the bookmark if we have one.
        NewsItem* bookmark = nullptr;

        // Bookmark is prepended item.
        if (listPrepend != nullptr) {
            bookmark = listPrepend->first();
        }

        // Set the bookmark -- or set it to -1 if there isn't one.
        feedItem->setBookmarkID(bookmark ? bookmark->getDbID() : -1);

        // As an optimization, we only want to present *one* list -- an append list.
        // So we rewind our prepend list on top of it, then delete the prepend list.
        if (listPrepend != nullptr) {
            if (listAppend == nullptr) {
                listAppend = new QList<NewsItem*>();
            }

            foreach (NewsItem* newsItem, *listPrepend) {
                // News item list.
                listAppend->prepend(newsItem);
            }

            delete listPrepend;
            listPrepend = nullptr;
        }
    }

    // Append/prepend items from our lists.
    if (listAppend != nullptr) {
        for (NewsItem* newsItem: *listAppend) {
            // News item list.
            feedItem->getNewsList()->append(newsItem);

            // News ID list.
            if (!lisvelNews->newsIDs()->contains(newsItem->getDbID())) {
                lisvelNews->newsIDs()->append(newsItem->getDbID());
            }
        }
    }

    if (listPrepend != nullptr) {
        for (NewsItem* newsItem: *listPrepend) {
            // News item list.
            feedItem->getNewsList()->prepend(newsItem);

            // News ID list.
            if (!lisvelNews->newsIDs()->contains(newsItem->getDbID())) {
                lisvelNews->newsIDs()->prepend(newsItem->getDbID());
            }
        }
    }

    // Set the first possible ID for that top bookmark display action.
    lisvelNews->setFirstNewsID(getFirstNewsID());

    // we r dun lol
    emit finished(this);
}

bool LisvelLoadNewsOperation::doPrepend()
{
    // Create our list.  This will be deleted at the end if it's empty.
    listPrepend = new QList<NewsItem*>();

    // Remaining items to load.
    int remainingLoadLimit = getLoadLimit();

    //
    // STEP ONE: Page up the ID list.
    //
    qint64 firstId = lisvelNews->getNewsList()->size() ?
                         lisvelNews->getNewsList()->first()->getDbID() : -1;

    // Assuming we even got a valid ID, only continue if the items isn't the first
    // one on the list.  If it is, we're already at the top and can skip over this.
    if (firstId > 0 && lisvelNews->newsIDs()->indexOf(firstId) > 0) {
        // Get the initial and previous list positions.
        int initial = lisvelNews->newsIDs()->indexOf(firstId) - 1; // Remember that it's > 0!
        int previous = qMax(0, initial - remainingLoadLimit);

        QString idString;   // List of IDs
        QString whenString; // List if WHEN statements for ordering switch statement.
        int index = 0;
        for(int i = initial; i >= previous; i--, index++) {
            if (index != 0) {
                idString += ", ";
            }

            QString currentID = QString::number(lisvelNews->newsIDs()->at(i));
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
        queryToNewsList(query, listPrepend);

        // Keep track of our load limit.
        remainingLoadLimit -= listPrepend->size();
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
        queryToNewsList(query, listPrepend);
    }

    // Delete our list if it's empty.
    if (listPrepend->size() == 0) {
        delete listPrepend;
        listPrepend = nullptr;
    }

    return true;
}

bool LisvelLoadNewsOperation::doAppend()
{
    // Create our list.  This will be deleted at the end if it's empty.
    listAppend = new QList<NewsItem*>();

    // Remaining items to load.
    int remainingLoadLimit = 10;//getLoadLimit();

    //
    // STEP ONE: Page down the ID list.
    //
    qint64 lastId = lisvelNews->getNewsList()->size() ?
                         lisvelNews->getNewsList()->last()->getDbID() : -1;

    // Assuming we even got a valid ID, only continue if the items isn't the last
    // one on the list.  If it is, we're already at the bottom and can skip over this.
    if (lastId > 0 && lisvelNews->newsIDs()->indexOf(lastId) < lisvelNews->newsIDs()->size() - 1) {
        // Get the initial and next list positions.
        int initial = lisvelNews->newsIDs()->indexOf(lastId) + 1; // Remember that it's not at the end!
        int next = qMin(lisvelNews->newsIDs()->size() - 1, initial + remainingLoadLimit);

        QString idString;   // List of IDs
        QString whenString; // List if WHEN statements for ordering switch statement.
        int index = 0;
        for(int i = initial; i <= next; i++, index++) {
            if (index != 0) {
                idString += ", ";
            }

            QString currentID = QString::number(lisvelNews->newsIDs()->at(i));
            idString += currentID;
            whenString += "WHEN " + currentID + " THEN " + QString::number(index) + " ";
        }

        // Load the items.
        QString queryString = "SELECT * FROM NewsItemTable N WHERE id IN (" + idString +
                              ") ORDER BY CASE id " + whenString + " END LIMIT :load_limit";
        // qDebug() << " ===== doAppend query: " << queryString;
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);

        if (!query.exec()) {
            qDebug() << "Could not load news! (lisvel append step 1)";
            qDebug() << query.lastError();

            return false;
        }

        // Extract the query.
        queryToNewsList(query, listAppend);

        // Keep track of our load limit.
        remainingLoadLimit -= listAppend->size();
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
        queryToNewsList(query, listAppend);
    }

    // Delete our list if it's empty.
    if (listAppend->size() == 0) {
        delete listAppend;
        listAppend = nullptr;
    }

    return true;
}

QString LisvelLoadNewsOperation::getLoadedIDString()
{
    QString ret = "";

    int i = 0;
    foreach(qint64 id, *lisvelNews->newsIDs()) {
        ret += QString::number(id);
        i++;

        if (lisvelNews->newsIDs()->size() != i)
            ret += ", ";
    }

    return ret;
}
