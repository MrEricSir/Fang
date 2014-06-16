#include "AddFeedOperation.h"
#include "../utilities/Utilities.h"

AddFeedOperation::AddFeedOperation(OperationManager *parent, ListModel *feedList,
                                   const QUrl &feedURL, QString title) :
    DBOperation(IMMEDIATE, parent),
    feedList(feedList),
    feedURL(feedURL),
    rawFeed(NULL),
    parser(),
    title(title)
{
    QObject::connect(&parser, SIGNAL(done()), this, SLOT(onFeedFinished()));
}

AddFeedOperation::AddFeedOperation(OperationManager *parent, ListModel *feedList, const QUrl &feedURL,
                                   const RawFeed* rawFeed) :
    DBOperation(IMMEDIATE, parent),
    feedList(feedList),
    feedURL(feedURL),
    rawFeed(rawFeed),
    parser()
{
}

void AddFeedOperation::execute()
{
    if (rawFeed != NULL) {
        commitRawFeed();
    } else {
        // Need to fetch the feed first.
        parser.parse(feedURL);
    }
}

void AddFeedOperation::onFeedFinished()
{
    // Ooh, data.
    rawFeed = parser.getFeed();
    if (rawFeed == NULL) {
        reportError("Parse error");
        
        return;
    }
    
    commitRawFeed();
}

void AddFeedOperation::commitRawFeed() {
    if (rawFeed == NULL) {
        reportError("RawFeed not provided");
        
        return;
    }
    
    // We'll wrap this in a transaction.  (Not really necessary at the moment.)
    db().transaction();
    
    int ordinal = 0; // Gotta start somewhere.
    
    // Attempt to grab the highest ordinal from the DB.
    QSqlQuery queryOrdinal(db());
    if (!queryOrdinal.exec("SELECT ordinal FROM FeedItemTable ORDER BY ordinal desc LIMIT 1")) {
        reportSQLError(queryOrdinal,"Could not select ordinal.");
        db().rollback();
        
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
    query.bindValue(":title", !title.isEmpty() ? title : rawFeed->title);
    query.bindValue(":subtitle", rawFeed->subtitle);
    query.bindValue(":lastUpdated", rawFeed->lastUpdated.toMSecsSinceEpoch());
    query.bindValue(":minutesToUpdate", rawFeed->minutesToUpdate);
    query.bindValue(":url", rawFeed->url);
    query.bindValue(":siteURL", rawFeed->siteURL);
    query.bindValue(":ordinal", ordinal);
    
    if (!query.exec()) {
        reportSQLError(query, "Could not add feed");
        db().rollback();
        
        return;
    }
    
    qint64 insertID = query.lastInsertId().toLongLong();
    
    db().commit();
    
    qDebug() << "Insert ID: " << insertID;
    
    // Create our item.
    item = Utilities::feedItemFromRaw(rawFeed, insertID, feedList);
    
    // Finally, add item to the model and signal completion.
    feedList->appendRow(item);
    emit finished(this);
}
