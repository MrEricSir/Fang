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
#include "../operations/LoadPinnedNewsOperation.h"
#include "../operations/SetBookmarkOperation.h"
#include "../operations/SetPinOperation.h"
#include "../operations/UpdateOrdinalsOperation.h"

/**
 * @brief Passes news between the JavaScript and C++ layers, yo.
 */
class WebInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(WebInteractor)
    
    Q_PROPERTY(qint32 specialFeedCount READ specialFeedCount NOTIFY specialFeedCountChanged)


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


    // Returns the number of special feeds.
    qint32 specialFeedCount();
    
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
     * @param firstNewsID ID of the first news item in this feed.  Used for showing/hiding top bookmark.
     * @param jsonNews    The news list converted to a JSON object.
     */
    void add(bool append, qint64 firstNewsID, QString jsonNews);

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
     * @param id      ID of the element to jump to.
     */
    void jumpTo(qint64 newsID);
    
    /**
     * @brief Draws the bookmark at the given news item.
     * @param id   ID of the news item element to draw a bookmark at.
     */
    void drawBookmark(qint64 newsID);

    /**
     * @brief Tells the view to update the pin for the given ID.
     * @param newsID ID of the news item
     * @param pin    If true, set pin. If false, unset.
     */
    void updatePin(qint64 newsID, bool pin);
    
    /**
     * @brief Not only draws the bookmark, but also issues a jump.
     * @param id   ID of the news item blah blah see above.
     */
    void drawBookmarkAndJumpTo(qint64 newsID);
    
    /**
     * @brief The style has changed in FangSettings, so the news viewer needs to refresh its css.
     */
    void styleChanged();
    
    /**
     * @brief The font size has changed, so to a jump to bookmark.
     */
    void fontSizeChanged();

    /**
     * @brief The number of special feeds in the feed list has changed.
     */
    void specialFeedCountChanged();
    
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
    Q_INVOKABLE void setBookmark(qint64 sId, bool allowBackward = false);

    // Pin or unpins an item.
    Q_INVOKABLE void setPin(qint64 id, bool pin);
    
    // The web layer has to call this to lead us know we're good to go.
    Q_INVOKABLE void pageLoaded();
    
    // Opens a link in the external browser.
    Q_INVOKABLE void openLink(QString link);
    
    // Refreshes the current feed.
    Q_INVOKABLE void refreshCurrentFeed();
    
    // Removes news from the list from either the top or bottom.
    // This is used to prevent too many items from clogging up the news view.
    Q_INVOKABLE void removeNews(bool fromTop, int numberToRemove);
    
private slots:
    
    // Called when a load has completed.
    void onLoadNewsFinished(Operation* operation);
    
    // Called when a bookmark has been set.
    void onSetBookmarkFinished(Operation* operation);

    // Called when a pin has ben set or unset.
    void onSetPinFinished(Operation* operation);
    
    // Escapes non-ASCII Unicode characters.
    QString encodeEntities( const QString& src, const QString& force=QString() );
    
    // Escpaes a few special characters for us.
    QString escapeCharacters(const QString& string);
    
    // Adds an item to a list that y'er buildin' on up.
    void addNewsItem(NewsItem* item, QVariantList* newsList);
    
    // Creates and executes a LoadNews operation.
    void doLoadNews(LoadNews::LoadMode mode);
    
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
