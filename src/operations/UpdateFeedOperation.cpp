#include "UpdateFeedOperation.h"
#include <QtAlgorithms>
#include <QDateTime>
#include <QSqlError>

#include "../utilities/Utilities.h"
#include "../models/AllNewsFeedItem.h"

UpdateFeedOperation::UpdateFeedOperation(QObject *parent, FeedItem *feed, RawFeed* rawFeed) :
    DBOperation(parent),
    parser(),
    feed(feed),
    rawFeed(rawFeed),
    wasDestroyed(false),
    rewriter()
{
    connect(&parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
    connect(feed, SIGNAL(destroyed()), this, SLOT(onFeedDestroyed()));
    connect(&rewriter, SIGNAL(finished()), this, SLOT(onRewriterFinished()));
}

UpdateFeedOperation::~UpdateFeedOperation()
{
    if (rawFeed != NULL)
        delete rawFeed;
}


void UpdateFeedOperation::execute()
{
    if (feed->metaObject() == &AllNewsFeedItem::staticMetaObject) {
        qDebug() <<  "Cannot update all news";
        emit finished(this);
        return;
    }
    
    feed->setIsUpdating(true);
    
    // Send network request.
    if (rawFeed == NULL)
        parser.parse(feed->getURL());
    else
        onFeedFinished();
}

void UpdateFeedOperation::onFeedFinished()
{
    feed->setIsUpdating(false);
    
    if (rawFeed == NULL)
        rawFeed = parser.getFeed();
    
    if (rawFeed == NULL) {
        qDebug() << "Raw feed was null :(";
        
        emit finished(this);
        
        return;
    }
    
    if (rawFeed->items.size() == 0) {
        // TODO: error signal.
        emit finished(this);
        qDebug() << "Feed list was empty!";
        
        return;
    }
    
    if (wasDestroyed || feed->getDbId() < 0) {
        qDebug() << "Couldn't update feed (may have been removed)";
        emit finished(this);
        
        return;
    }
    
    // Sort the list oldest to newest.
    qSort(rawFeed->items.begin(), rawFeed->items.end(), RawNews::LessThan);
    
    // Look for the newest feed we know about.
    QDateTime newestLocalNews = QDateTime::fromMSecsSinceEpoch(0);
    if (feed->getNewsList()->size() > 0)
        newestLocalNews = feed->getNewsList()->last()->getTimestamp();
    
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
    
    rewriter.rewrite(&newsList);
}

void UpdateFeedOperation::onRewriterFinished()
{
    // Add all new items to DB.
    db().transaction(); // Prevent getting out of sync on error.
    foreach (RawNews* rawNews, newsList) {
        QSqlQuery query(db());
        query.prepare("INSERT INTO NewsItemTable (feed_id, title, author, summary, content, "
                      "timestamp, url) VALUES (:feed_id, :title, :author, :summary, :content, "
                      ":timestamp, :url)");
        query.bindValue(":feed_id", feed->getDbId());
        query.bindValue(":title", rawNews->title);
        query.bindValue(":author", rawNews->author);
        query.bindValue(":summary", rawNews->description);
        query.bindValue(":content", rawNews->content);
        query.bindValue(":timestamp", rawNews->timestamp.toMSecsSinceEpoch());
        query.bindValue(":url", rawNews->url);
        
        if (!query.exec()) {
            qDebug() << "Unable to add news item.";
            qDebug() << "SQL error: " << query.lastError().text();
            db().rollback();
            
            // TODO error signal.
            emit finished(this);
            return;
        }
        
        // Store the DB id for the next loop.
        rawNews->dbId = query.lastInsertId().toLongLong();
    }
    
    db().commit(); // Done with db!
    
    // Update data model.
    foreach (RawNews* rawNews, newsList) {
        feed->append(
                    new NewsItem(feed,
                                 rawNews->dbId,
                                 rawNews->title,
                                 rawNews->author,
                                 rawNews->description,
                                 rawNews->content,
                                 rawNews->timestamp,
                                 rawNews->url
                                 ));
    }
    
    // TODO: Update DB.
    emit finished(this);
}

void UpdateFeedOperation::onFeedDestroyed()
{
    wasDestroyed = true;
}
