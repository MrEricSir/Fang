#ifndef UPDATEFEEDOPERATION_H
#define UPDATEFEEDOPERATION_H

#include "DBOperation.h"
#include "../utilities/RawFeedImageSizeRewriter.h"
#include "../parser/BackgroundParser.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

/**
 * @brief Updates a feed.
 * If a feed has already been downloaded and parsed, it can be supplied
 * directly to the constructor.
 *
 * VERY IMPORTANT NOTE: When using this class, please note that it is non-reentrant on a per-feed basis.
 *                      In other words, it's safe to call on feed x and y simultaneously, but not on
 *                      feed x and feed x at the same time.  Bad shit will happen, man.  Don't blame me.
 */
class UpdateFeedOperation : public DBOperation
{
    Q_OBJECT
public:
    /**
     * @brief UpdateFeedOperation
     * @param parent  Set this to the manager
     * @param feed    Feed to update
     * @param rawFeed Optional: include this if you've already downloaded the feed and parsed it.
     */
    explicit UpdateFeedOperation(QObject *parent, FeedItem* feed, RawFeed* rawFeed = NULL);
    virtual ~UpdateFeedOperation();
    
    
signals:
    
public slots:
    /**
     * @brief VERY IMPORTANT NOTE: Non re-entrant per-feed (see above.)
     */
    virtual void execute();
    
private slots:
    /**
     * @brief Finished downloading and parsing our news feed, time to save to DB.
     */
    void onFeedFinished();
    
    /**
     * @brief Feed was destroyed before update could complete.
     */
    void onFeedDestroyed();
    
    /**
     * @brief When the rewriter is done with the feed
     */
    void onRewriterFinished();
    
private:
    BackgroundParser parser;
    FeedItem *feed;
    RawFeed* rawFeed;
    bool wasDestroyed;
    RawFeedImageSizeRewriter rewriter;
    QList<RawNews*> newsList;
};

#endif // UPDATEFEEDOPERATION_H
