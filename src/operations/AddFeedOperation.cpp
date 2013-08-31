#include "AddFeedOperation.h"
#include "../models/FeedItem.h"
#include "../utilities/Utilities.h"

AddFeedOperation::AddFeedOperation(QObject *parent, ListModel *feedList, const QUrl &feedURL,
                                   const QUrl &imageURL, QString siteTitle) :
    DBOperation(parent),
    feedList(feedList),
    feedURL(feedURL),
    imageURL(imageURL),
    siteTitle(siteTitle),
    parser()
{
    QObject::connect(&parser, SIGNAL(done()), this, SLOT(onFeedFinished()));
}

void AddFeedOperation::execute()
{
    // Before we can do anything, we must parse the feed!
    parser.parse(feedURL);
}

void AddFeedOperation::onFeedFinished()
{
    // Ooh, data.
    RawFeed* rawFeed = parser.getFeed();
    if (rawFeed == NULL) {
        qDebug() << "Raw feed was null :(";
        
        emit finished(this);
        
        return;
    }
    
    // The user gave us this (right?)
    rawFeed->title = siteTitle;
    
    // We'll wrap this in a transaction.  (Not really necessary at the moment.)
    db().transaction();
    
    int ordinal = 0; // Gotta start somewhere.
    
    // Attempt to grab the highest ordinal from the DB.
    QSqlQuery queryOrdinal(db());
    if (!queryOrdinal.exec("SELECT ordinal FROM FeedItemTable ORDER BY ordinal desc LIMIT 1")) {
        db().rollback();
        qDebug() << "Could not select ordinal.";
        // TODO: error signal
        
        return;
    }
    
    if (queryOrdinal.next()) {
        // Our ordinal is the highest one, plus one.  Of course, no ordinal can be higher than 24.
        // I don't wanna hear no more arguments about it nowhere.
        ordinal = queryOrdinal.value("ordinal").toInt() + 1;
    }
    
    // Insert feed.
    QSqlQuery query(db());
    query.prepare("INSERT INTO FeedItemTable (title, subtitle, lastUpdated, minutesToUpdate, "
                  "url, siteURL, ordinal) VALUES (:title, :subtitle, :lastUpdated, "
                  ":minutesToUpdate, :url, :siteURL, :ordinal)");
    query.bindValue(":title", rawFeed->title);
    query.bindValue(":subtitle", rawFeed->subtitle);
    query.bindValue(":lastUpdated", rawFeed->lastUpdated.toMSecsSinceEpoch());
    query.bindValue(":minutesToUpdate", rawFeed->minutesToUpdate);
    query.bindValue(":url", rawFeed->url);
    query.bindValue(":siteURL", rawFeed->siteURL);
    query.bindValue(":ordinal", ordinal);
    
    if (!query.exec()) {
        db().rollback();
        qDebug() << "Could not add feed: " << query.lastError().text();
        
        // TODO : add error signal
        return;
    }
    
    qint64 insertID = query.lastInsertId().toLongLong();
    
    db().commit();
    
    qDebug() << "Insert ID: " << insertID;
    
    // Create our item.
    FeedItem* item = Utilities::feedItemFromRaw(rawFeed, insertID, feedList);
    
    // Finally, add item to the model and signal completion.
    feedList->appendRow(item);
    emit finished(this);
}
