#ifndef ADDFEEDOPERATION_H
#define ADDFEEDOPERATION_H

#include "DBOperation.h"

#include <QUrl>
#include <QString>
#include <QDebug>

#include "../models/ListModel.h"
#include "../parser/BackgroundParser.h"

class AddFeedOperation : public DBOperation
{
    Q_OBJECT
public:
    // Attempts to add a feed based on an RSS/Atom URL.
    explicit AddFeedOperation(OperationManager *parent, ListModel *feedList, const QUrl &feedURL);
    
    // Adds a feed that's already been parsed.
    explicit AddFeedOperation(OperationManager *parent, ListModel *feedList, const QUrl &feedURL,
                              const RawFeed* rawFeed);
    
signals:
    
public slots:
    virtual void execute();
    
private slots:
    void onFeedFinished();
    
    // Commits whatever's in rawFeed.
    void commitRawFeed();
    
private:
    ListModel *feedList;
    QUrl feedURL;
    const RawFeed* rawFeed;
    
    BackgroundParser parser;
};

#endif // ADDFEEDOPERATION_H
