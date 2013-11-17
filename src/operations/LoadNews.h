#ifndef LOADNEWS_H
#define LOADNEWS_H

#include <QObject>
#include <QList>

#include "DBOperation.h"
#include "../models/FeedItem.h"
#include "../models/NewsItem.h"

/**
 * @brief Loads a batch of NewsItems.
 */
class LoadNews : public DBOperation
{
    Q_OBJECT
public:
    
    /**
     * @param parent    The manager
     * @param feedItem  The feed item to grab
     * @param append    If true, add items to the end of the list. If false, add 'em to the start.
     * @param loadLimit Max number of news items to load
     */
    explicit LoadNews(QObject *parent, FeedItem* feedItem, bool append, int loadLimit = 15);
    
public slots:
    virtual void execute();
    
    /**
     * @return The Feed associated with this load.
     */
    inline FeedItem* getFeedItem() { return feedItem; }
    
    /**
     * @return True if append mode, false if prepend.
     */
    inline bool getAppend() { return append; }
    
    /**
     * @return List of items that this load appended or prepended.
     */
    inline QList<NewsItem*>* getNewsList() { return newsList; }
    
private:
    // Feed we're adding to.
    FeedItem* feedItem;
    
    // True if we're appending.
    bool append;
    
    // Max # of news items to add.
    int loadLimit;
    
    // List of items we added.
    QList<NewsItem*>* newsList;
};

#endif // LOADNEWS_H
