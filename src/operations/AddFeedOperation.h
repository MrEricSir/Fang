#ifndef ADDFEEDOPERATION_H
#define ADDFEEDOPERATION_H

#include "DBOperation.h"

#include <QUrl>
#include <QString>
#include <QDebug>

#include "../models/ListModel.h"
#include "../models/FeedItem.h"
#include "../parser/NewsParser.h"

class AddFeedOperation : public DBOperation
{
    Q_OBJECT
public:
    // Attempts to add a feed based on an RSS/Atom URL.
    explicit AddFeedOperation(OperationManager *parent, ListModel *feedList, const QString userURL,
                              QString title = "");
    
    // Adds a feed that's already been parsed.
    explicit AddFeedOperation(OperationManager *parent, ListModel *feedList, const QString userURL,
                              const RawFeed* rawFeed);
    
signals:
    
public slots:
    virtual void execute();
    
    FeedItem* getFeedItem() { return item; }
    
private slots:
    void onFeedFinished();
    
    // Commits whatever's in rawFeed.
    void commitRawFeed();
    
private:
    ListModel *feedList;
    QString userURL;
    const RawFeed* rawFeed;
    
    NewsParser parser;
    
    QString title;
    
    // The resulting item;
    FeedItem* item;
};

#endif // ADDFEEDOPERATION_H
