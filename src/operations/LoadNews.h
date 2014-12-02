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
    explicit LoadNews(OperationManager *parent, FeedItem* feedItem, LoadMode mode, int loadLimit = 15);
    
    virtual ~LoadNews();
    
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
     * @return List of items that this load appended.
     */
    inline QList<NewsItem*>* getAppendList() { return listAppend; }
    
    /**
     * @return List of items that this load prepended.
     */
    inline QList<NewsItem*>* getPrependList() { return listPrepend; }
    
    /**
     * @return Max number of items to load (specified as loadLimit in constructor.)
     */
    inline int getLoadLimit() { return loadLimit; }
    
protected slots:
    
    /**
     * @brief Extracts news items from a database query.
     * @param query  Database query containing zero or more News Items.
     * @param list   The list of items items we just created.
     */
    void queryToNewsList(QSqlQuery& query, QList<NewsItem*>* list);
    
    /**
     * @brief Call this during the initial load of a feed.
     *@ return id of feed's bookmark.
     */
    qint64 getBookmarkID();
    
    /**
     * @brief Finds the very first item available in this feed, loaded or not. This is
     *        used to determine whether or not to display the top bookmark.
     * @return id of the first item in the entire feed.
     */
    virtual qint64 getFirstNewsID();
    
    bool doAppend(qint64 startId);
    
    bool doPrepend(qint64 startId);
    
    /**
     * @brief Performs the actual query and loads the results into the appropriate list
     * @param startId ID to start with
     * @param append Which direction and which list to load into
     * @return True if successful, false on an error
     */
    virtual bool executeLoadQuery(qint64 startId, bool append);

    // Returns the next ID after the last item in the feed's news list, or -1
    qint64 getStartIDForAppend();

    // Returns the first ID in the feed's news list, or -1
    qint64 getStartIDForPrepend();
    
protected:

    // Feed we're adding to.
    FeedItem* feedItem;
    
    // List of items we appended.
    QList<NewsItem*>* listAppend;
    
    // List of items we prepended.
    QList<NewsItem*>* listPrepend;
    
    // True if we're appending.
    LoadMode mode;
    
    // Max # of news items to add.
    int loadLimit;
    
};

#endif // LOADNEWS_H
