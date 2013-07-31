#ifndef NEWSWEB_H
#define NEWSWEB_H

#include <QObject>
#include <QList>
#include <QWebElement>
#include <QWebFrame>
#include <QDesktopServices>

#include "FangWebView.h"
#include "NewsItem.h"

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
     */
    void init(QDeclarativeWebView *webView);
    
signals:
    
    /**
     * @brief Fired when NewsWeb is cocked, rocked, and ready to roll.
     */
    void ready();
    
public slots:
    
    /**
     * @brief Clears the current feed.
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
     * @return True if the page has loaded.
     */
    inline bool isReady() { return _isReady; }
    
private slots:
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
     * @param item
     * @return HTML element ID for the given item.
     */
    QString idForItem(NewsItem* item);
    
    /**
     * @brief Cleans RSS junk out of an element.
     * @param newsContainer
     */
    void cleanConatiner(QWebElement &newsContainer);
    
    void removeAll(const QString &selector, QWebElement element);
    
private:
    // The WebView used to display this feed.
    QDeclarativeWebView *webView;
    
    // List that corresponds to the items in the view.
    QList<NewsItem*> items;
    
    // The actual Qt WebKit instance.
    QWebPage* webPage;
    
    // Root DOM document object.
    QWebElement document;
    
    // Template container for a news item.
    QWebElement templateContainer;
    
    bool _isReady;
};

#endif // NEWSWEB_H
