#ifndef NEWSWEB_H
#define NEWSWEB_H

#include <QObject>
#include <QList>
#include <QWebElement>
#include <QWebFrame>
#include <QDesktopServices>
#include <QTimer>

#include "FangWebView.h"
#include "NewsItem.h"
#include "FeedItem.h"
#include "ScrollReader.h"
#include "FangSettings.h"

/**
 * @brief Wraps a QtWebKit WebView with functions for managing the news feed.
 */
class NewsWeb : public QObject
{
    Q_OBJECT
public:
    explicit NewsWeb(QObject *parent = 0);
    
    /**
     * @brief Starts the NewsWeb interface.
     * @param webView
     * @param scroll
     * @param settings
     */
    void init(QDeclarativeWebView *webView, ScrollReader* scroll, FangSettings* settings,
              const QString& platform);
    
    
    virtual bool eventFilter(QObject *watched, QEvent *e);
    
    
signals:
    
    /**
     * @brief Fired when NewsWeb is cocked, rocked, and ready to roll.
     */
    void ready();
    
public slots:
    
    /**
     * @brief Sets the feed displayed in the reader.  It will automatically
     * update if news items are added/removed.
     * @param feed The feed to display, or null if none.
     */
    void setFeed(FeedItem* feed);
    
    /**
     * @return True if the page has loaded.
     */
    inline bool isReady() { return _isReady; }
    
    inline FeedItem* getCurrentFeed() { return currentFeed; }
    
    /**
     * @brief Forces a qml repaint.
     */
    void forceRefresh();
    
    /**
     * @brief Called when the style has changed.
     */
    void styleChanged();
    
private slots:
    
    /**
     * @brief Unsets and clears the current feed.
     */
    void clear();
    
    /**
     * @brief Appends an item to the end of the current feed.
     * @param item
     */
    void append(NewsItem* item);
    
    /**
     * @brief Removes an item from the feed.  Can be at any location.
     * @param item
     */
    void remove(NewsItem* item);
    
    /**
     * @brief Updates the bottom spacer that lets the user scroll all the way up to the last item.
     */
    void updateBottomSpacer();
    
    /**
     * @brief Called when web view is loaded.  This initializes
     * the page, document and template objects.
     * @param ok
     */
    void onLoadFinished(bool ok);
    
    /**
     * @brief Link handler. Opens links in external browser.
     * @param url
     */
    void onLinkClicked(const QUrl &url);
    
    /**
     * @brief When size of web document has hanged.
     */
    void onGeometryChangeRequested();
    
    /**
     * @brief Handler for our ScrollReader instance
     * @param contentY
     */
    void onContentYChanged(qreal contentY);
    
    /**
     * @brief Scroll read timer.
     */
    void onScrollReadTimeout();
    
    /**
     * @brief Timer for jumping (see below.)
     */
    void onJumpTimeout();
    
    /**
     * @brief Jumps the view to the given item.  May not happen instantly.
     * @param item
     */
    void jumpToItem(NewsItem* item);
    
    /**
     * @brief Same as jumpToItem(), but jumps to the current bookmark (or the top.)
     */
    void jumpToBookmark();
    
    /**
     * @brief Creates a new element for the given item, ready to be inserted.
     * @param item
     * @return 
     */
    QWebElement createNewElementForItem(NewsItem *item);
    
    /**
     * @param item
     * @return HTML element ID for the given item.
     */
    QString idForItem(NewsItem* item);
    
    /**
     * @brief Returns the element for a given item.
     * @param item
     * @return 
     */
    QWebElement elementForItem(NewsItem* item);
    
    /**
     * @brief Finds the item associated with a given element OR ITS PARENTS!!
     * This function is expensive.  Use it sparingly or I'll take it away, young lady.
     * @param element
     * @return The news item associated with the element or its parent nodes, or NULL if none.
     */
    NewsItem *itemForElement(const QWebElement &element);
    
    /**
     * @brief Cleans RSS junk out of an element.
     * @param newsContainer
     */
    void cleanConatiner(QWebElement &newsContainer);
    
    /**
     * @brief Removes a branch of the DOM tree.
     * @param selector CSS-style selector to remove
     * @param element Element to examine and modify
     */
    void removeAll(const QString &selector, QWebElement element);
    
    /**
     * @brief Sets the bookmark at the given item. Existing bookmark will be removed.
     * @param item
     */
    void setBookmark(NewsItem* item);
    
    /**
     * @brief If any item is bookmarked, this removes the bookmark.
     */
    void removeBookmark();
    
    /**
     * @brief Returns the selector for a given item (used by remove/set bookmark)
     * @param item
     * @return 
     */
    QString newsItemToBookmarkSelector(NewsItem* item);
    
    /**
     * @return Width of the web view.
     */
    qreal getViewWidth();
    
    /**
     * @return Height of the web view.
     */
    qreal getViewHeight();
    
    /**
     * @brief The maximum scroll amount of the document.
     * @return 
     */
    qreal getMaxScroll();
    
    /**
     * @brief Briefly delays scroll read timer.
     */
    void bumpScrollReadTimer();
    
    /**
     * @brief Time to force refresh.
     */
    void onForceRefreshTimeout();
    
private:
    // The WebView used to display this feed.
    QDeclarativeWebView *webView;
    
    // The current feed being displayed.
    FeedItem* currentFeed;
    
    // List that corresponds to the items in the view.
    QList<NewsItem*> items;
    
    // The actual Qt WebKit instance.
    QWebPage* webPage;
    
    // Root DOM document object.
    QWebElement document;
    
    // Template container for a news item.
    QWebElement templateContainer;
    
    // Set to true when the view has initialized.
    bool _isReady;
    
    // Our QML element for figuring out what's up (and down) with the C++ unfriendly Flickable
    ScrollReader* scroll;
    
    // The most recently bookmarked item.
    NewsItem* bookmarkedItem;
    
    // Used to poll page to advance bookmark.
    QTimer scrollReadTimer;
    
    // Used to jump to bookmark after adding the feed.
    QTimer jumpToBookmarkTimer;
    
    // Item we're jumping to.
    NewsItem* jumpItem;
    
    QTimer forceRefreshTimer;
    
    // User-configurable settings.
    FangSettings* settings;
    
    // Platform identifier.
    QString platform;
};

#endif // NEWSWEB_H
