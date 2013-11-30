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
    
    enum LoadMode {
        Initial = 0,  // Loads loadLimit items from the bookmark, plus loadlimit items above bookmark
        Append,       // Appends loadLimit items (load next)
        Prepend       // Prepends loadLimit items (load previous)
    };
    
    /**
     * @param parent    The manager
     * @param feedItem  The feed item to grab
     * @param mode      Type of load operation (see above)
     * @param loadLimit Max number of news items to load
     */
    explicit LoadNews(QObject *parent, FeedItem* feedItem, LoadMode mode, int loadLimit = 15);
    
    
public slots:
    virtual void execute();
    
    /**
     * @return The Feed associated with this load.
     */
    inline FeedItem* getFeedItem() { return feedItem; }
    
    /**
     * @return Returns the operational mode.
     */
    inline LoadMode getMode() { return mode; }
    
    /**
     * @return List of items that this load appended or prepended.
     */
    inline QList<NewsItem*>* getNewsList() { return newsList; }
    
private slots:
    
    /**
     * @brief Extracts news items from a database query.
     * @param query  Database query containing zero or more News Items.
     */
    void queryToNewsList(QSqlQuery& query);
    
    bool doAppend(qint64 startId);
    
    bool doPrepend(qint64 startId);
    
    bool executeLoadQuery(qint64 startId, bool append);
    
private:
    // Feed we're adding to.
    FeedItem* feedItem;
    
    // True if we're appending.
    LoadMode mode;
    
    // Max # of news items to add.
    int loadLimit;
    
    // List of items we added.
    QList<NewsItem*>* newsList;
    
    // Used to set bookmark during load.
    NewsItem* bookmark;
};

#endif // LOADNEWS_H
