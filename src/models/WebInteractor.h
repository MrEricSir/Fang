#ifndef WEBINTERACTOR_H
#define WEBINTERACTOR_H

#include <QQuickItem>
#include <QString>

#include "FeedItem.h"
#include "NewsItem.h"
#include "../operations/OperationManager.h"
#include "../operations/Operation.h"
#include "../operations/LoadNews.h"
#include "../operations/LoadAllNewsOperation.h"
#include "../operations/SetBookmarkOperation.h"
#include "../operations/UpdateOrdinalsOperation.h"
#include "../operations/UpdateFeedOperation.h"

/**
 * @brief Passes news between the JavaScript and C++ layers, yo.
 */
class WebInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(WebInteractor)
    
public:
    explicit WebInteractor(QQuickItem *parent = 0);
    virtual ~WebInteractor() {}
    
    void init(OperationManager* manager, ListModel *feedList);
    
signals:
    
    /**
     * @brief This is called before and after a batch of adds.
     * 
     * @param started    True if this is the start, false if it's the end.
     * @param operation  Name of the operation (initial, append, prepend)
     */
    void addInProgress(bool started, QString operation);
    
    /**
     * @brief Add a little something to the web page.
     * 
     * @param append      True for appending, false for prepending.
     * @param id          The string ID for the HTML element.
     * @param title       Title of the news item
     * @param url         URL of the story
     * @param feedTitle   Feed's title
     * @param timestamp   String timestamp
     * @param content     HTML content
     */
    void add(bool append, QString id, QString title, QString url, QString feedTitle, QString timestamp, QString content);

    
    /**
     * @brief Clear the current news.
     */
    void clear();
    
    /**
     * @brief Jumps to a given news item by its ID.
     * @param id      HTML ID of the element to jump to.
     */
    void jumpTo(QString id);
    
    /**
     * @brief Draws the bookmark at the given news item.
     * @param id   HTML ID of the news item element to draw a bookmark at.
     */
    void drawBookmark(QString id);
    
public slots:
    
    // Call this when the feed changes, g-dawg.
    void setFeed(FeedItem* feed);
    
    // This says, like, ok we're ready for the next batch of news.
    Q_INVOKABLE void loadNext();
    
    // Beep beep beep! http://www.youtube.com/watch?v=B_H7WZGsIjM
    Q_INVOKABLE void loadPrevious();
    
    // Gets the current bookmark and invokes a jump to it.
    Q_INVOKABLE void jumpToBookmark();
    
    // The order changed!  Better record that.
    Q_INVOKABLE void orderChanged();
    
    // Sets the bookmark, and fires a draw event.
    Q_INVOKABLE void setBookmark(QString sId);
    
    // The web layer has to call this to lead us know we're good to go.
    Q_INVOKABLE void pageLoaded();
    
    // Opens a link in the external browser.
    Q_INVOKABLE void openLink(QString link);
    
    void refreshFeed(FeedItem* item);
    
    // Refreshes a given feed.
    Q_INVOKABLE void refreshFeed(const qint64 id);
    
    // Refreshes the current feed.
    Q_INVOKABLE void refreshCurrentFeed();
    
private slots:
    
    // Called when a load has completed.
    void onLoadNewsFinished(Operation* operation);
    
    // Called when a bookmark has been set.
    void onSetBookmarkFinished(Operation* operation);
    
    QString escapeCharacters(const QString& string);
    
    // Emits the add signal for an item.
    void addNewsItem(bool append, NewsItem* item);
    
    // Creates and executes a LoadNews operation.
    void doLoadNews(LoadNews::LoadMode mode);
    
    // Fetches the feed with the given ID.
    FeedItem* feedForId(const qint64 id);
    
    void onFeedRemoved(ListItem* listItem);
    
private:
    // The currently selected news feed.
    FeedItem* currentFeed;
    
    // Op man!
    OperationManager* manager;
    
    // Reentrancy guards.
    bool isLoading;
    bool isSettingBookmark;
    
    // Once we've loaded, we're READY!
    bool isReady;
    
    // Pointer to the global feed list.
    ListModel *feedList;
};

#endif // WEBINTERACTOR_H
