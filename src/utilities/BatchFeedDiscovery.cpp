#include "BatchFeedDiscovery.h"

BatchFeedDiscovery::BatchFeedDiscovery(QObject *parent) :
    FangObject(parent),
    feedList(nullptr)
{
}

void BatchFeedDiscovery::checkFeedList(ListModel* feedList, int maxConcurrent)
{
    this->feedList = feedList;
    
    for(int i = 0; i < feedList->count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(feedList->row(i));
        if (i < maxConcurrent) {
            // Run the first few concurrently.
            FeedDiscovery* discovery = new FeedDiscovery();
            connect(discovery, &FeedDiscovery::done, this, &BatchFeedDiscovery::onFeedDiscoveryFinished);
            
            runDiscovery(discovery, item);
        } else {
            // Queue up the reset.
            queue.enqueue(item);
        }
    }
}

void BatchFeedDiscovery::onFeedDiscoveryFinished(FeedDiscovery* discovery)
{
    FeedItem* item = lookup.take(discovery);
    item->setIsUpdating(false);
    
    // See what we got.
    if (discovery->error()) {
        item->setErrorFlag(true);
    } else {
        // Yay, we got one!  Copy over the corrected URL.
        item->setURL(discovery->feedURL());
        
        // Now select it.
        item->setIsSelected(true);
    }
    
    // Last-item check.
    if (queue.isEmpty()) {
        if (lookup.isEmpty()) {
            // That's all, folks!
            emit done();
        }
        
        delete discovery;
        return;
    }
    
    // Grab the next one and DISOVERYize it!!11
    runDiscovery(discovery, queue.dequeue());
}

void BatchFeedDiscovery::runDiscovery(FeedDiscovery* discovery, FeedItem* item)
{
    lookup.insert(discovery, item);
    item->setIsUpdating(true);
    discovery->checkFeed(item->getURL().toString());
}
