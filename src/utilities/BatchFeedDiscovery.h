#ifndef BATCHFEEDDISCOVERY_H
#define BATCHFEEDDISCOVERY_H

#include "../models/FeedItem.h"
#include "../models/ListModel.h"
#include "FeedDiscovery.h"
#include "../FangObject.h"

#include <QObject>
#include <QMap>
#include <QQueue>
#include <functional>

/**
 * @brief Calls FeedDiscovery on a bunch of feeds at once in a list.
 * 
 * Each FeedItem will have IsUpdating and HasError set:
 *   IsUpdating: The feed discovery is in progress
 *   IsError: The feed discovery completed with an error
 * 
 * If both are false at the time done() is emitted, you're hella
 * ready to rock and roll!
 * 
 * 
 * TODO: Need a way to safely cancel this operation since it
 *       can take a while.
 * 
 *       UNIT TEST!!
 */
class BatchFeedDiscovery : public FangObject
{
    Q_OBJECT
public:
    explicit BatchFeedDiscovery(QObject *parent = nullptr);
    
signals:
    
    /**
     * @brief Completion signal.
     */
    void done();
    
public slots:
    
    /**
     * @brief Checks an entire feed list.
     */
    void checkFeedList(ListModel* feedList, int maxConcurrent = 3);
    
    /**
     * @return The list of feeds you asked me to check?  Here they are.
     */
    ListModel* getFeedList() { return feedList; }
    
protected slots:

    void onFeedDiscoveryFinished(FeedDiscovery* discovery);

    void runDiscovery(FeedDiscovery* discovery, FeedItem* item);

protected:
    /**
     * @brief Creates a FeedDiscovery instance. Virtual to allow mocking in tests.
     */
    virtual FeedDiscovery* createFeedDiscovery();

    ListModel* feedList;
    QQueue<FeedItem*> queue;
    QMap<FeedDiscovery*, FeedItem*> lookup;
};

#endif // BATCHFEEDDISCOVERY_H
