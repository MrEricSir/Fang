#include "LoadAllNewsOperation.h"

LoadAllNewsOperation::LoadAllNewsOperation(OperationManager *parent, FeedItem* feedItem, LoadMode mode, int loadLimit) :
    LoadNews(parent, feedItem, mode, loadLimit),
    allNews(NULL)
{
    // Ensure we have All News!
    allNews = qobject_cast<AllNewsFeedItem*>(feedItem);
    Q_ASSERT(allNews != NULL);
}

void LoadAllNewsOperation::execute()
{
    // For an initial load, make sure the feed isn't populated yet.
    if (getMode() == LoadNews::Initial)
        Q_ASSERT(feedItem->getNewsList() != NULL || feedItem->getNewsList()->isEmpty());
    
    // DB query/ies.
    bool dbResult = true;
    switch (getMode()) {
    case Initial:
    {
        dbResult &= doAppend();  // First load everything after bookmark.
        dbResult &= doPrepend(); // Now the stuff on top
        
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
        reportError("DB error in LoadAllNewsOperation");
        
        return;
    }
    
    
    if (getMode() == Initial) {
        // For the initial load, set the bookmark if we have one.
        NewsItem* bookmark = NULL;
        
        // Bookmark is prepended item.
        if (listPrepend != NULL)
            bookmark = listPrepend->first();
        
        // Set the bookmark -- or set it to -1 if there isn't one.
        feedItem->setBookmarkID(bookmark ? bookmark->getDbID() : -1);
        
        // As an optimization, we only want to present *one* list -- an append list.
        // So we rewind our prepend list on top of it, then delete the prepend list.
        if (listPrepend != NULL) {
            if (listAppend == NULL) {
                listAppend = new QList<NewsItem*>();
            }
            
            foreach (NewsItem* newsItem, *listPrepend) {
                // News item list.
                listAppend->prepend(newsItem);
            }
            
            delete listPrepend;
            listPrepend = NULL;
        }
    }
    
    // Append/prepend items from our lists.
    if (listAppend != NULL)
        foreach (NewsItem* newsItem, *listAppend) {
            // News item list.
            feedItem->getNewsList()->append(newsItem);
            
            // News ID list.
            if (!allNews->newsIDs()->contains(newsItem->getDbID())) {
                allNews->newsIDs()->append(newsItem->getDbID());
            }
        }
    
    if (listPrepend != NULL)
        foreach (NewsItem* newsItem, *listPrepend) {
            // News item list.
            feedItem->getNewsList()->prepend(newsItem);
            
            // News ID list.
            if (!allNews->newsIDs()->contains(newsItem->getDbID())) {
                allNews->newsIDs()->prepend(newsItem->getDbID());
            }
        }
    
    // we r dun lol
    emit finished(this);
}

bool LoadAllNewsOperation::doPrepend()
{
    // Create our list.  This will be deleted at the end if it's empty.
    listPrepend = new QList<NewsItem*>();
    
    // Remaining items to load.
    int remainingLoadLimit = getLoadLimit();
    
    //
    // STEP ONE: Page up/down the ID list.
    //
    qint64 firstId = allNews->getNewsList()->size() ?
                         allNews->getNewsList()->first()->getDbID() : -1;
    
    // Assuming we even got a valid ID, only continue if the items isn't the first
    // one on the list.  If it is, we're already at the top and can skip over this.
    if (firstId > 0 && allNews->newsIDs()->indexOf(firstId) > 0) {
        // Get the initial and previous list positions.
        int initial = allNews->newsIDs()->indexOf(firstId) - 1; // Remember that it's > 0!
        int previous = qMax(0, initial - remainingLoadLimit);
        
        QString idString;   // List of IDs
        QString whenString; // List if WHEN statements for ordering switch statement.
        int index = 0;
        for(int i = initial; i >= previous; i--, index++) {
            if (index != 0)
                idString += ", ";
            
            QString currentID = QString::number(allNews->newsIDs()->at(i));
            idString += currentID;
            whenString += "WHEN " + currentID + " THEN " + QString::number(index) + " ";
        }
        
        // Load the items.
        QString queryString = "SELECT * FROM NewsItemTable N where id IN (" + idString + 
                              ") ORDER BY CASE id " + whenString + " END LIMIT :load_limit";
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);
        
        if (!query.exec()) {
            qDebug() << "Could not load news for all news!";
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
    if (remainingLoadLimit > 0) {
        QString queryString = "SELECT * FROM NewsItemTable N where id <= (SELECT bookmark_id from "
                              "FeedItemTable WHERE id = N.feed_id) AND id NOT IN (" + getLoadedIDString() +
                              ") ORDER BY timestamp DESC, id DESC LIMIT :load_limit";
        
        //qDebug() << "Query: " << queryString;
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);
        
        if (!query.exec()) {
            qDebug() << "Could not load news for all news!";
            qDebug() << query.lastError();
            
            return false;
        }
        
        // Extract the query into our news list.
        queryToNewsList(query, listPrepend);
    }
    
    // Delete our list if it's empty.
    if (listPrepend->size() == 0) {
        delete listPrepend;
        listPrepend = NULL;
    }
    
    return true;
}

bool LoadAllNewsOperation::doAppend()
{
    // Create our list.  This will be deleted at the end if it's empty.
    listAppend = new QList<NewsItem*>();
    
    // Remaining items to load.
    int remainingLoadLimit = 10;//getLoadLimit();
    
    //
    // STEP ONE: Page down the ID list.
    //
    qint64 lastId = allNews->getNewsList()->size() ?
                         allNews->getNewsList()->last()->getDbID() : -1;
    
    // Assuming we even got a valid ID, only continue if the items isn't the last
    // one on the list.  If it is, we're already at the bottom and can skip over this.
    if (lastId > 0 && allNews->newsIDs()->indexOf(lastId) < allNews->newsIDs()->size() - 1) {
        // Get the initial and next list positions.
        int initial = allNews->newsIDs()->indexOf(lastId) + 1; // Remember that it's not at the end!
        int next = qMin(allNews->newsIDs()->size() - 1, initial + remainingLoadLimit);
        
        QString idString;   // List of IDs
        QString whenString; // List if WHEN statements for ordering switch statement.
        int index = 0;
        for(int i = initial; i <= next; i++, index++) {
            if (index != 0)
                idString += ", ";
            
            QString currentID = QString::number(allNews->newsIDs()->at(i));
            idString += currentID;
            whenString += "WHEN " + currentID + " THEN " + QString::number(index) + " ";
        }
        
        // Load the items.
        QString queryString = "SELECT * FROM NewsItemTable N where id IN (" + idString + 
                              ") ORDER BY CASE id " + whenString + " END LIMIT :load_limit";
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);
        
        if (!query.exec()) {
            qDebug() << "Could not load news for all news!";
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
        QString queryString = "SELECT * FROM NewsItemTable N where id > (SELECT bookmark_id from "
                              "FeedItemTable WHERE id = N.feed_id) AND id NOT IN (" + getLoadedIDString() +
                              ") ORDER BY timestamp ASC, id ASC LIMIT :load_limit";
        QSqlQuery query(db());
        query.prepare(queryString);
        query.bindValue(":load_limit", remainingLoadLimit);
        
        if (!query.exec()) {
            qDebug() << "Could not load news for all news!";
            qDebug() << query.lastError();
            
            return false;
        }
        
        // Extract the query into our news list.
        queryToNewsList(query, listAppend);
    }
    
    // Delete our list if it's empty.
    if (listAppend->size() == 0) {
        delete listAppend;
        listAppend = NULL;
    }
    
    return true;
}

QString LoadAllNewsOperation::getLoadedIDString()
{
    QString ret = "";
    
    int i = 0;
    foreach(qint64 id, *allNews->newsIDs()) {
        ret += QString::number(id);
        i++;
        
        if (allNews->newsIDs()->size() != i)
            ret += ", ";
    }
    
    return ret;
}
