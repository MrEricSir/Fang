#include "AddFeedOperation.h"
#include "../utilities/Utilities.h"
#include "../utilities/FangLogging.h"

AddFeedOperation::AddFeedOperation(OperationManager *parent, ListModel *feedList,
                                   const QString userURL, QString title) :
    AsyncOperation(IMMEDIATE, parent),
    feedList(feedList),
    userURL(userURL),
    rawFeed(nullptr),
    parser(),
    title(title)
{
    QObject::connect(&parser, &NewsParser::done, this, &AddFeedOperation::onFeedFinished);
}

AddFeedOperation::AddFeedOperation(OperationManager *parent, ListModel *feedList, const QString userURL,
                                   const RawFeed* rawFeed) :
    AsyncOperation(IMMEDIATE, parent),
    feedList(feedList),
    userURL(userURL),
    rawFeed(rawFeed),
    parser()
{
}

void AddFeedOperation::execute()
{
    if (rawFeed != nullptr) {
        commitRawFeed();
    } else {
        // Need to fetch the feed first.
        parser.parse(userURL);
    }
}

void AddFeedOperation::onFeedFinished()
{
    // Ooh, data.
    rawFeed = parser.getFeed();
    if (rawFeed == nullptr) {
        reportError("Parse error");
        
        return;
    }
    
    commitRawFeed();
}

void AddFeedOperation::commitRawFeed() {
    if (rawFeed == nullptr) {
        reportError("RawFeed not provided");
        
        return;
    }

    // qDebug() << "Commit raw feed for feed URL: " << rawFeed->url << " and site URL: " << rawFeed->siteURL;
    // qDebug() << "  - User URL:" << userURL;
    
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
                  "url, siteURL, user_url, ordinal) VALUES (:title, :subtitle, :lastUpdated, "
                  ":minutesToUpdate, :url, :siteURL, :user_url, :ordinal)");
    query.bindValue(":title", !title.isEmpty() ? title : rawFeed->title);
    query.bindValue(":subtitle", rawFeed->subtitle);
    query.bindValue(":lastUpdated", rawFeed->lastUpdated.toMSecsSinceEpoch());
    query.bindValue(":minutesToUpdate", rawFeed->minutesToUpdate);
    query.bindValue(":url", rawFeed->url);
    query.bindValue(":siteURL", rawFeed->siteURL);
    query.bindValue(":user_url", userURL);
    query.bindValue(":ordinal", ordinal);

    if (!query.exec()) {
        reportSQLError(query, "Could not add feed");
        db().rollback();
        
        return;
    }
    
    qint64 insertID = query.lastInsertId().toLongLong();
    
    db().commit();
    
    qCDebug(logOperation) << "Insert new feed with ID: " << insertID;
    
    // Create our item.
    item = Utilities::feedItemFromRaw(rawFeed, insertID, userURL, feedList);
    
    // Finally, add item to the model and signal completion.
    feedList->appendRow(item);
    emit finished(this);
}
