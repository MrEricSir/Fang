#ifndef WEBINTERACTOR_H
#define WEBINTERACTOR_H

#include <QQuickItem>
#include <QString>

#include "FeedItem.h"
#include "NewsItem.h"
#include "FangSettings.h"
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
    
    /**
     * @brief The stuff the interactor needs to do its job properly.
     * @param manager
     * @param feedList
     * @param fangSettings
     */
    void init(OperationManager* manager, ListModel *feedList, FangSettings *fangSettings);
    
signals:
    
    /**
     * @brief This is called before and after a batch of append/prepends.
     * 
     * @param started    True if this is the start, false if it's the end.
     * @param operation  Name of the operation (initial, append, prepend)
     */
    void addInProgress(bool started, QString operation);
    
    /**
     * @brief Add a little something to the web page.
     * 
     * @param append      True for appending, false for prepending.
     * @param jsonNews    The news list converted to a JSON object.
     */
    void add(bool append, QString jsonNews);

    /**
     * @brief If you loaded a feed with no news items, this will be called instead of the above.
     */
    void nothingToAdd();
    
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
    
    /**
     * @brief Not only draws the bookmark, but also issues a jump.
     * @param id   HTML ID of the news item blah blah see above.  Or "" if we just want to indicate that we're ready to go!
     */
    void drawBookmarkAndJumpTo(QString id);
    
    /**
     * @brief The style has changed in FangSettings, so the news viewer needs to refresh its css.
     */
    void styleChanged();
    
    /**
     * @brief The font size has changed, so to a jump to bookmark.
     */
    void fontSizeChanged();
    
public slots:
    
    // Call this when the feed changes, g-dawg.
    void setFeed(FeedItem* feed);
    
    // This says, like, ok we're ready for the next batch of news.
    Q_INVOKABLE void loadNext();
    
    // Beep beep beep! http://www.youtube.com/watch?v=B_H7WZGsIjM
    Q_INVOKABLE void loadPrevious();
    
    // The order changed!  Better record that.
    Q_INVOKABLE void orderChanged();
    
    // Sets the bookmark, and fires a draw event.
    Q_INVOKABLE void setBookmark(QString sId);
    
    // The web layer has to call this to lead us know we're good to go.
    Q_INVOKABLE void pageLoaded();
    
    // Opens a link in the external browser.
    Q_INVOKABLE void openLink(QString link);
    
    // Refresh a single feed.
    void refreshFeed(FeedItem* feed);
    
    // Refresh ALL feeds.
    void refreshAllFeeds();
    
    // Refreshes a given feed.
    Q_INVOKABLE void refreshFeed(const qint64 id);
    
    // Refreshes the current feed.
    Q_INVOKABLE void refreshCurrentFeed();
    
    // Removes news from the list from either the top or bottom.
    Q_INVOKABLE void removeNews(bool fromTop, int numberToRemove);
    
private slots:
    
    // Called when a load has completed.
    void onLoadNewsFinished(Operation* operation);
    
    // Called when a bookmark has been set.
    void onSetBookmarkFinished(Operation* operation);
    
    QString escapeCharacters(const QString& string);
    
    // Adds an item to a list that y'er buildin' on up.
    void addNewsItem(NewsItem* item, QVariantList* newsList);
    
    // Creates and executes a LoadNews operation.
    void doLoadNews(LoadNews::LoadMode mode);
    
    // Fetches the feed with the given ID.
    FeedItem* feedForId(const qint64 id);
    
    void onFeedRemoved(ListItem* listItem);
    
    // Alert us to style changes.
    void onStyleChanged(QString style);
    
    // Alert us to font size changes.
    void onFontSizeChanged(QString font);
    
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
    
    // Pointer to the global settings object.
    FangSettings *fangSettings;
};

#endif // WEBINTERACTOR_H
