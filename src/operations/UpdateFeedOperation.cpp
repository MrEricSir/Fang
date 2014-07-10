#include "UpdateFeedOperation.h"
#include <QtAlgorithms>
#include <QDateTime>

#include "../utilities/Utilities.h"
#include "../models/AllNewsFeedItem.h"
#include "../utilities/UnreadCountReader.h"
#include "../FangApp.h"

UpdateFeedOperation::UpdateFeedOperation(OperationManager *parent, FeedItem *feed, RawFeed* rawFeed, bool useCache) :
    DBOperation(BACKGROUND, parent),
    parser(),
    feed(feed),
    rawFeed(rawFeed),
    rewriter(),
    timestamp(),
    useCache(useCache)
{
    connect(&parser, SIGNAL(done()), this, SLOT(onFeedFinished()));
    connect(&rewriter, SIGNAL(finished()), this, SLOT(onRewriterFinished()));
    
    requireObject(feed);
}

UpdateFeedOperation::~UpdateFeedOperation()
{
}

void UpdateFeedOperation::execute()
{
    FANG_BACKGROUND_CHECK;
    
    if (feed->metaObject() == &AllNewsFeedItem::staticMetaObject) {
        qDebug() <<  "Cannot update all news";
        emit finished(this);
        return;
    }
    
    //qDebug() << "Updating feed: " << feed->getTitle();
    
    // Setup.
    feed->setIsUpdating(true);
    timestamp = QDateTime::currentDateTime();
    
    
    if (rawFeed == NULL) {
        // Send network request.
        parser.parse(feed->getURL(), useCache);
    } else {
        onFeedFinished();
    }
}

void UpdateFeedOperation::onFeedFinished()
{
    FANG_BACKGROUND_CHECK;
    
    feed->setIsUpdating(false);
    
    if (rawFeed == NULL)
        rawFeed = parser.getFeed();
    
    if (rawFeed == NULL) {
        qDebug() << "Raw feed was null :(";
        
        emit finished(this);
        
        return;
    }
    
    if (rawFeed->items.size() == 0) {
        qDebug() << "Feed list was empty! (Could be cache.)";
        emit finished(this);
        
        return;
    }
    
    // Sort the list oldest to newest.
    qSort(rawFeed->items.begin(), rawFeed->items.end(), RawNews::LessThan);
    
    // Check for the newest news item that we know about.
    QDateTime newestLocalNews = QDateTime::fromMSecsSinceEpoch(0); // default to epoch
    QSqlQuery query(db());
    query.prepare("SELECT timestamp FROM NewsItemTable WHERE feed_id = :feed_id ORDER BY timestamp DESC LIMIT 1");
    query.bindValue(":feed_id", feed->getDbId());
    if (!query.exec()) {
        reportSQLError(query, "Error: Could not read news timestamp");
        
        return;
    }
    
    if (query.next())
        newestLocalNews = QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong());
    
    // Check if we really need to update by comparing the dates of the most recent news items.
    QDateTime newestNewNews = rawFeed->items.last()->timestamp;
    if (newestNewNews <= newestLocalNews) {
        emit finished(this);
        //qDebug() << "Feed already up to date!";
        //qDebug() << "Newest new: " << newestNewNews.toString() << " Newest local: " << newestLocalNews.toString();
        
        return;
    }
    
    // Look for newest unseen news.  The news items from newIndex to items.size()-1 should be added.
    // IMPORTANT NOTE: 0 means that all news items must be added.
    // If newIndex remains at -1, no new news items were found.
    int newIndex = -1;
    for (int i = rawFeed->items.size() - 1; i >= 0; i--) {
        if (rawFeed->items.at(i)->timestamp > newestLocalNews)
            newIndex = i;
    }
    
    // Check should be a duplicate of the one above, but just in case...
    if (newIndex < 0) {
        emit finished(this);
        qDebug() << "New index was negative, all feeds must be up to date!";
        
        return;
    }
    
    // Add all new items to our list.
    newsList.clear();
    for (int i = newIndex; i < rawFeed->items.size(); i++)
        newsList.append(rawFeed->items.at(i));
    
    // Start the rewriter!  (See the next method below.)
    rewriter.rewrite(&newsList);
}

void UpdateFeedOperation::onRewriterFinished()
{
    FANG_BACKGROUND_CHECK;
    
    // Add all new items to DB.
    db().transaction(); // Prevent getting out of sync on error.
    foreach (RawNews* rawNews, newsList) {
        QSqlQuery query(db());
        query.prepare("INSERT INTO NewsItemTable (feed_id, guid, title, author, summary, content, "
                      "timestamp, url) VALUES (:feed_id, :guid, :title, :author, :summary, :content, "
                      ":timestamp, :url)");
        query.bindValue(":feed_id", feed->getDbId());
        query.bindValue(":guid", rawNews->guid);
        query.bindValue(":title", rawNews->title);
        query.bindValue(":author", rawNews->author);
        query.bindValue(":summary", rawNews->description);
        query.bindValue(":content", rawNews->content);
        query.bindValue(":timestamp", rawNews->timestamp.toMSecsSinceEpoch());
        query.bindValue(":url", rawNews->url);
        
        if (!query.exec()) {
            reportSQLError(query, "Unable to add news item.");
            db().rollback();
            
            return;
        }
        
        // Store the DB id for the next loop.
        rawNews->dbId = query.lastInsertId().toLongLong();
    }
    
    // Update feed update timestamp.
    QSqlQuery query(db());
    query.prepare("UPDATE FeedItemTable SET lastUpdated = :lastUpdated WHERE id = :feed_id");
    query.bindValue(":feed_id", feed->getDbId());
    query.bindValue(":lastUpdated", timestamp.toMSecsSinceEpoch());
    
    if (!query.exec()) {
        reportSQLError(query, "Unable to update the feed's timestamp.");
        db().rollback();
        
        return;
    }
    
    // Update unread count & All News's unread count.
    UnreadCountReader::update(db(), feed);
    UnreadCountReader::update(db(), FangApp::instance()->getFeed(0));
    
    db().commit(); // Done with db!
    
    // TODO: update unread count
    
    emit finished(this);
}
