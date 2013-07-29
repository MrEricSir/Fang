#include "AddFeedOperation.h"
#include "../models/FeedItem.h"
#include "../utilities/Utilities.h"

#include <QSqlError>

AddFeedOperation::AddFeedOperation(QObject *parent, ListModel *feedList, const QUrl &feedURL,
                                   const QUrl &imageURL, QString siteTitle) :
    DBOperation(parent),
    feedList(feedList),
    feedURL(feedURL),
    imageURL(imageURL),
    siteTitle(siteTitle),
    parser()
{
    QObject::connect(&parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
}


void AddFeedOperation::execute()
{
    parser.parse(feedURL);
}

void AddFeedOperation::onFeedFinished()
{
    RawFeed* rawFeed = parser.getFeed();
    if (rawFeed == NULL) {
        qDebug() << "Raw feed was null :(";
        
        emit finished(this);
        
        return;
    }
    
    rawFeed->title = siteTitle;
    
    db().transaction();
    
    int ordinal = 0;
    
    // Attempt to grab the highest ordinal from the DB.
    QSqlQuery queryOrdinal(db());
    if (!queryOrdinal.exec("SELECT ordinal FROM FeedItemTable ORDER BY ordinal desc LIMIT 1")) {
        qDebug() << "Could not select ordinal.";
        // TODO: error signal
        return;
    }
    
    if (queryOrdinal.next()) {
        ordinal = queryOrdinal.value("ordinal").toInt() + 1; // Our ordinal is the highest one, plus one.
    }
    
    // Insert feed.
    QSqlQuery query(db());
    query.prepare("INSERT INTO FeedItemTable (title, subtitle, lastUpdated, minutesToUpdate, "
                  "url, imageURL, ordinal) VALUES (:title, :subtitle, :lastUpdated, :minutesToUpdate, "
                  ":url, :imageURL, :ordinal)");
    query.bindValue(":title", rawFeed->title);
    query.bindValue(":subtitle", rawFeed->subtitle);
    query.bindValue(":lastUpdated", rawFeed->lastUpdated);
    query.bindValue(":minutesToUpdate", rawFeed->minutesToUpdate);
    query.bindValue(":url", rawFeed->url);
    query.bindValue(":imageURL", rawFeed->imageURL);
    query.bindValue(":ordinal", ordinal);
    
    if (!query.exec()) {
        qDebug() << "Could not add feed: " << query.lastError().text();
        // TODO : add error signal
        return;
    }
    
    db().commit();
    
    // Create our item.
    FeedItem* item = Utilities::feedItemFromRaw(rawFeed, query.lastInsertId().toLongLong(), feedList);
    
    // Finally, add item to the model and signal completion.
    feedList->appendRow(item);
    emit finished(this);
}

