#ifndef NEWSFEEDINTERACTOR_H
#define NEWSFEEDINTERACTOR_H

#include <QQuickItem>
#include <QString>

#include "FeedItem.h"
#include "../operations/OperationManager.h"
#include "../operations/Operation.h"

/**
 * @brief Interacts with the QML layer of the news view.
 */
class NewsFeedInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(NewsFeedInteractor)
    
    Q_PROPERTY(qint32 specialFeedCount READ specialFeedCount NOTIFY specialFeedCountChanged)

public:
    explicit NewsFeedInteractor(QQuickItem *parent = nullptr);
    virtual ~NewsFeedInteractor() {}

    // Returns the number of special feeds.
    qint32 specialFeedCount();

signals:

    /**
     * @brief The number of special feeds in the feed list has changed.
     */
    void specialFeedCountChanged();

public slots:

    // Remove an existing feed.
    void removeFeed(FeedItem* feed);

    // Insert a folder at the given index and reparent the next two items.
    int insertFolder(int newIndex);

    // The order of the feed list changed!  Better record that.
    void orderChanged();
    
    // Refreshes the current feed.
    void refreshCurrentFeed();

    // Refreshes any feed.
    void refreshFeed(FeedItem* feed);

    // Refreshes all feeds.
    void refreshAllFeeds();

    // Marks all news items in a feed as read or unread.
    void markAllAsRead(FeedItem* feed);
    void markAllAsUnread(FeedItem* feed);

    // User wants to jump to the bookmark!
    void jumpToBookmark();

    // User wants to jump to the next news item!
    void jumpNext();

    // User wants to jump to the previous news item!!!1
    void jumpPrevious();

    // Show the news view.
    void showNews();

    // Show the welcome/help view.
    void showWelcome();
    
private:
    // Op man!
    OperationManager* manager;
    
    // Pointer to the global feed list.
    ListModel *feedList;
};

#endif // NEWSFEEDINTERACTOR_H
