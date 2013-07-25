#include "UpdateFeedOperation.h"
#include <QtAlgorithms>

#include "../utilities/Utilities.h"

UpdateFeedOperation::UpdateFeedOperation(QObject *parent, FeedItem *feed) :
    Operation(parent),
    parser(),
    feed(feed),
    rawFeed(NULL)
{
    QObject::connect(&parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
}

UpdateFeedOperation::~UpdateFeedOperation()
{
    qDebug() << "Well, Bye!";
    if (rawFeed != NULL)
        delete rawFeed;
}


void UpdateFeedOperation::execute()
{
    // TODO: 
    
    // Send network request.
    parser.parse(feed->getURL());
}

void UpdateFeedOperation::onFeedFinished()
{
    rawFeed = parser.getFeed();
    if (rawFeed == NULL) {
        qDebug() << "Raw feed was null :(";
        
        emit finished(this);
        
        return;
    }
    
    // Sort the list oldest to newest.
    //qSort(rawFeed->items.end(), rawFeed->items.begin());
    
    // TODO: Check what actually needs updating in data model.
    
    RawNews* rawNews;
    foreach(rawNews, rawFeed->items) {
        feed->getNewsList()->appendRow(
                    new NewsItem(feed, rawNews->title,
                                 rawNews->author,
                                 Utilities::htmlify(rawNews->content != "" ? rawNews->content : rawNews->description),
                                 rawNews->timestamp,
                                 rawNews->url,
                                 feed->getNewsList()
                                 ));
    }
    
    
    
    // TODO: Update DB.
    qDebug() << "Operation finished";
    emit finished(this);
}
