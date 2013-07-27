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
    qSort(rawFeed->items.begin(), rawFeed->items.end(), RawNews::GreaterThan);
    
    // TODO: Check what actually needs updating in data model.
    
    // Update data model.
    foreach(RawNews* rawNews, rawFeed->items) {
        feed->append(
                    new NewsItem(feed,
                                 0,
                                 rawNews->title,
                                 rawNews->author,
                                 rawNews->description,
                                 rawNews->content,
                                 rawNews->timestamp,
                                 rawNews->url
                                 ));
    }
    
    
    // TODO: Update DB.
    qDebug() << "Operation finished";
    emit finished(this);
}
