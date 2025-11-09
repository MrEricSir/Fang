#include "UpdateFeedOperation.h"
#include <QtAlgorithms>
#include <QDateTime>

#include "UpdateFeedURLOperation.h"
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
    connect(&parser, &NewsParser::done, this, &UpdateFeedOperation::onFeedFinished);
    connect(&rewriter, &RawFeedRewriter::finished, this, &UpdateFeedOperation::onRewriterFinished);
    connect(&discovery, &FeedDiscovery::done, this, &UpdateFeedOperation::onDiscoveryDone);
    
    requireObject(feed);
}

UpdateFeedOperation::~UpdateFeedOperation()
{
}

void UpdateFeedOperation::execute()
{
    FANG_BACKGROUND_CHECK;
    Q_ASSERT(feed);
    
    if (feed->isSpecialFeed()) {
        qDebug() <<  "Cannot update special feed";
        emit finished(this);
        return;
    }

    if (feed->isFolder()) {
        qDebug() <<  "Cannot update folder";
        emit finished(this);
        return;
    }
    
    //qDebug() << "Updating feed: " << feed->getTitle();
    
    // Setup.
    feed->setIsUpdating(true);
    timestamp = QDateTime::currentDateTime();
    
    
    if (rawFeed == nullptr) {
        // Send network request.
        parser.parse(feed->getURL(), useCache);
    } else {
        onFeedFinished();
    }
}

void UpdateFeedOperation::onFeedFinished()
{
    FANG_BACKGROUND_CHECK;

    // Try feed rediscovery if needed. This will update the URL and refresh.
    if (parser.getResult() == ParserInterface::NETWORK_ERROR &&
        parser.getNetworkError() == QNetworkReply::NetworkError::ContentNotFoundError) {
        qDebug() << "UpdateFeedOperation: Feed not found. Attempting to rediscover feed.";
        discovery.checkFeed(feed->getUserURL());

        return;
    }
    
    feed->setIsUpdating(false);
    
    if (rawFeed == nullptr) {
        rawFeed = parser.getFeed();
    }
    
    if (rawFeed == nullptr) {
        // This is often the result of the feed not having been updated, and thus
        // it was already cached.  We return null in that case to save time.
        
        //qDebug() << "Raw feed was null!";
        
        emit finished(this);
        
        return;
    }
    
    if (rawFeed->items.size() == 0) {
        qDebug() << "Feed list was empty! (Could be cache.)";
        emit finished(this);
        
        return;
    }
    
    // Sort the list oldest to newest.
    std::sort(rawFeed->items.begin(), rawFeed->items.end(), RawNews::LessThan);
    
    // Check for the newest news item that we know about.
    QDateTime newestLocalNews = QDateTime::fromMSecsSinceEpoch(0); // default to epoch
    QSqlQuery query(db());
    query.prepare("SELECT timestamp FROM NewsItemTable WHERE feed_id = :feed_id ORDER BY timestamp DESC LIMIT 1");
    query.bindValue(":feed_id", feed->getDbID());
    if (!query.exec()) {
        reportSQLError(query, "Error: Could not read news timestamp");
        
        return;
    }
    
    if (query.next()) {
        newestLocalNews = QDateTime::fromMSecsSinceEpoch(query.value("timestamp").toLongLong());
    }
    
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
        if (rawFeed->items.at(i)->timestamp > newestLocalNews) {
            newIndex = i;
        }
    }
    
    // Check should be a duplicate of the one above, but just in case...
    if (newIndex < 0) {
        emit finished(this);
        qDebug() << "New index was negative, all feeds must be up to date!";
        
        return;
    }
    
    // Add all new items to our list.
    newsList.clear();
    for (int i = newIndex; i < rawFeed->items.size(); i++) {
        newsList.append(rawFeed->items.at(i));
    }
    
    // Start the rewriter!  (See the next method below.)
    rewriter.rewrite(&newsList);
}

void UpdateFeedOperation::onRewriterFinished()
{
    FANG_BACKGROUND_CHECK;

    feed->setIsUpdating(false);
    
    // Add all new items to DB.
    db().transaction(); // Prevent getting out of sync on error.
    for (RawNews* rawNews : newsList) {
        QSqlQuery query(db());
        query.prepare("INSERT INTO NewsItemTable (feed_id, guid, title, author, summary, content, "
                      "timestamp, url) VALUES (:feed_id, :guid, :title, :author, :summary, :content, "
                      ":timestamp, :url)");
        query.bindValue(":feed_id", feed->getDbID());
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
    query.bindValue(":feed_id", feed->getDbID());
    query.bindValue(":lastUpdated", timestamp.toMSecsSinceEpoch());
    
    if (!query.exec()) {
        reportSQLError(query, "Unable to update the feed's timestamp.");
        db().rollback();
        
        return;
    }
    
    // Update unread count, All News's unread count, and folder (if applicable);
    UnreadCountReader::update(db(), feed);
    UnreadCountReader::update(db(), FangApp::instance()->getFeed(0));
    if (feed->getParentFolderID() > 0) {
        UnreadCountReader::update(db(), FangApp::instance()->feedForId(feed->getParentFolderID()));
    }
    
    db().commit(); // Done with db!
    
    emit finished(this);
}

void UpdateFeedOperation::onDiscoveryDone(FeedDiscovery* feedDiscovery)
{
    Q_UNUSED(feedDiscovery);

    if (discovery.error() || // Error trying to find feed.
        (feed->getURL() == discovery.feedURL()) // No change to URL, so nothing to do.
        ) {
        qDebug() << "UpdateFeedOperation: Could not rediscover URL for feed: "
                 << feed->getTitle() << " -- " << feed->getUserURL();

        feed->setIsUpdating(false);
        emit finished(this);
        return;
    }

    qDebug() << "UpdateFeedOperation: For feed: " << feed->getUserURL();
    qDebug() << "                     Updated URL is: " << discovery.feedURL();

    // Update DB. Note that this will also update the feed object's URL.
    UpdateFeedURLOperation* op = new UpdateFeedURLOperation(getOperationManager(), feed, discovery.feedURL());
    connect(op, &UpdateFeedURLOperation::finished, this, &UpdateFeedOperation::onUpdateFeedURLFinished);
    getOperationManager()->add(op);
}

void UpdateFeedOperation::onUpdateFeedURLFinished(Operation * op)
{
    Q_UNUSED(op);

    // Send network request.
    qDebug() << "Finished updating feed URL, updating feed " << feed->getURL();
    parser.parse(feed->getURL(), useCache);
}
