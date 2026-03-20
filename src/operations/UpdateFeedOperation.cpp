#include "UpdateFeedOperation.h"
#include <QtAlgorithms>
#include <QDateTime>
#include <QSet>

#include "UpdateFeedURLOperation.h"
#include "../models/AllNewsFeedItem.h"
#include "../utilities/UnreadCountReader.h"
#include "../utilities/ErrorHandling.h"
#include "../utilities/FangLogging.h"
#include "../FangApp.h"

UpdateFeedOperation::UpdateFeedOperation(OperationManager *parent, FeedItem *feed, RawFeed* rawFeed, bool useCache) :
    AsyncOperation(BACKGROUND, parent),
    parser(),
    feed(feed),
    rawFeed(rawFeed),
    rewriter(),
    timestamp(),
    useCache(useCache),
    newsSitemapSynthesizer(nullptr)
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

    if (!feed) {
        qCCritical(logOperation) << "UpdateFeedOperation::execute: feed is null, cannot execute";
        emit finished(this);
        return;
    }

    if (feed->isSpecialFeed()) {
        qCDebug(logOperation) <<  "Cannot update special feed";
        emit finished(this);
        return;
    }

    if (feed->isFolder()) {
        qCDebug(logOperation) <<  "Cannot update folder";
        emit finished(this);
        return;
    }
    
    // Setup.
    feed->setIsUpdating(true);
    timestamp = QDateTime::currentDateTime();
    
    
    if (feed->getFeedType() == FeedTypeGoogleNewsSitemap) {
        // Google News sitemap feeds use the synthesizer *busts out a keytar* to simulate
        // feeds based on sitemap XML data.
        newsSitemapSynthesizer = new GoogleNewsSitemapSynthesizer(this);
        connect(newsSitemapSynthesizer, &GoogleNewsSitemapSynthesizer::done,
                this, &UpdateFeedOperation::onNewsSitemapRefreshDone);
        newsSitemapSynthesizer->synthesize(feed->getURL(), feed->getTitle(),
                                       feed->getLastUpdated());
    } else if (rawFeed == nullptr) {
        // Send network request with conditional headers if available.
        parser.parse(feed->getURL(), useCache, feed->getEtag(), feed->getLastModified());
    } else {
        onFeedFinished();
    }
}

void UpdateFeedOperation::onFeedFinished()
{
    FANG_BACKGROUND_CHECK;

    // 304 Not Modified: Fed hasn't changed, nothing to do.
    if (parser.getResult() == ParserInterface::NOT_MODIFIED) {
        feed->setErrorFlag(false);
        feed->setIsUpdating(false);
        emit finished(this);
        return;
    }

    // Try feed rediscovery if needed. This will update the URL and refresh.
    if (parser.getResult() == ParserInterface::NETWORK_ERROR &&
        parser.getNetworkError() == QNetworkReply::NetworkError::ContentNotFoundError) {
        qCDebug(logOperation) << "UpdateFeedOperation: Feed not found. Attempting to rediscover feed.";
        discovery.checkFeed(feed->getUserURL());

        return;
    }

    // Set error flag for network errors (server unreachable, etc.)
    if (parser.getResult() == ParserInterface::NETWORK_ERROR) {
        qCDebug(logOperation) << "UpdateFeedOperation: Network error for feed:" << feed->getTitle();
        feed->setErrorFlag(true);
        feed->setIsUpdating(false);
        emit finished(this);

        return;
    }

    feed->setIsUpdating(false);

    if (rawFeed == nullptr) {
        rawFeed = parser.getFeed();
    }

    if (rawFeed == nullptr) {
        // This is often the result of the feed not having been updated, and thus
        // it was already cached.  We return null in that case to save time.
        feed->setErrorFlag(false); // Clear error flag, if set.
        emit finished(this);

        return;
    }

    if (rawFeed->items.size() == 0) {
        qCDebug(logOperation) << "Feed list was empty! (Could be cache.)";
        feed->setErrorFlag(false);
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
        feed->setErrorFlag(false);
        emit finished(this);

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
        feed->setErrorFlag(false);
        emit finished(this);
        qCDebug(logOperation) << "New index was negative, all feeds must be up to date!";

        return;
    }
    
    // Collect candidate GUIDs so we can skip items already in the DB.
    QStringList candidateGuids;
    for (int i = newIndex; i < rawFeed->items.size(); i++) {
        candidateGuids.append(rawFeed->items.at(i)->guid);
    }

    // Query existing GUIDs for this feed in one batch.
    QSet<QString> existingGuids;
    {
        QSqlQuery guidQuery(db());
        // SQLite supports up to 999 bound parameters, but using IN with
        // a built string is simpler for a variable-length list.
        QString placeholders;
        for (int i = 0; i < candidateGuids.size(); i++) {
            if (i > 0) {
                placeholders += ",";
            }
            placeholders += "?";
        }
        guidQuery.prepare(QString("SELECT guid FROM NewsItemTable WHERE feed_id = ? AND guid IN (%1)")
                          .arg(placeholders));
        guidQuery.addBindValue(feed->getDbID());
        for (const QString& g : candidateGuids) {
            guidQuery.addBindValue(g);
        }
        if (guidQuery.exec()) {
            while (guidQuery.next()) {
                existingGuids.insert(guidQuery.value(0).toString());
            }
        }
    }

    // Add new items, skipping any whose GUID already exists for this feed.
    newsList.clear();
    for (int i = newIndex; i < rawFeed->items.size(); i++) {
        if (!existingGuids.contains(rawFeed->items.at(i)->guid)) {
            newsList.append(rawFeed->items.at(i));
        }
    }

    if (newsList.isEmpty()) {
        feed->setErrorFlag(false);
        emit finished(this);
        return;
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
                      "timestamp, url, media_image_url) VALUES (:feed_id, :guid, :title, :author, :summary, :content, "
                      ":timestamp, :url, :media_image_url)");
        query.bindValue(":feed_id", feed->getDbID());
        query.bindValue(":guid", rawNews->guid);
        query.bindValue(":title", rawNews->title);
        query.bindValue(":author", rawNews->author);
        query.bindValue(":summary", rawNews->description);
        query.bindValue(":content", rawNews->content);
        query.bindValue(":timestamp", rawNews->timestamp.toMSecsSinceEpoch());
        query.bindValue(":url", rawNews->url);
        query.bindValue(":media_image_url", rawNews->mediaImageURL);
        
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

    // Save ETag and Last-Modified response headers for conditional refresh.
    {
        QSqlQuery etagQuery(db());
        etagQuery.prepare("UPDATE FeedItemTable SET etag = :etag, last_modified = :last_modified WHERE id = :feed_id");
        etagQuery.bindValue(":etag", parser.responseEtag());
        etagQuery.bindValue(":last_modified", parser.responseLastModified());
        etagQuery.bindValue(":feed_id", feed->getDbID());
        if (!etagQuery.exec()) {
            reportSQLError(etagQuery, "Unable to update ETag/Last-Modified.");
            db().rollback();
            return;
        }
        feed->setEtag(parser.responseEtag());
        feed->setLastModified(parser.responseLastModified());
    }

    // Update unread count, All News's unread count, and folder (if applicable);
    UnreadCountReader::update(db(), feed);
    UnreadCountReader::update(db(), FangApp::instance()->getAllNewsFeed());
    if (feed->getParentFolderID() > 0) {
        UnreadCountReader::update(db(), FangApp::instance()->feedForId(feed->getParentFolderID()));
    }
    
    db().commit(); // Done with db!

    // Clear any previous error flag since update succeeded.
    feed->setErrorFlag(false);

    emit finished(this);
}

void UpdateFeedOperation::onNewsSitemapRefreshDone()
{
    FANG_BACKGROUND_CHECK;

    if (newsSitemapSynthesizer->hasError()) {
        qCDebug(logOperation) << "UpdateFeedOperation: Google News sitemap refresh error:"
                              << newsSitemapSynthesizer->errorString();
        feed->setErrorFlag(true);
        feed->setIsUpdating(false);
        emit finished(this);
        return;
    }

    // Use our the synthesized feed as though it were an RSS/Atom feed.
    rawFeed = newsSitemapSynthesizer->result();
    onFeedFinished();
}

void UpdateFeedOperation::onDiscoveryDone(FeedDiscovery* feedDiscovery)
{
    Q_UNUSED(feedDiscovery);

    if (discovery.error() || // Error trying to find feed.
        (feed->getURL() == discovery.feedURL()) // No change to URL, so nothing to do.
        ) {
        qCDebug(logOperation) << "UpdateFeedOperation: Could not rediscover URL for feed: "
                 << feed->getTitle() << " -- " << feed->getUserURL();

        // Set error flag since we couldn't recover from the 404.
        feed->setErrorFlag(true);
        feed->setIsUpdating(false);
        emit finished(this);
        return;
    }

    qCDebug(logOperation) << "UpdateFeedOperation: For feed: " << feed->getUserURL();
    qCDebug(logOperation) << "                     Updated URL is: " << discovery.feedURL();

    // Update DB synchronously. This also updates the feed object's URL.
    UpdateFeedURLOperation updateURLOp(getOperationManager(), feed, discovery.feedURL());
    getOperationManager()->run(&updateURLOp);

    // Send network request with the updated URL and conditional headers.
    qCDebug(logOperation) << "Finished updating feed URL, updating feed " << feed->getURL();
    parser.parse(feed->getURL(), useCache, feed->getEtag(), feed->getLastModified());
}
