#include "NewsWeb.h"

#include "../utilities/Utilities.h"

#include <QDeclarativeItem>

NewsWeb::NewsWeb(QObject *parent) :
    QObject(parent),
    webView(NULL),
    currentFeed(NULL),
    items(),
    webPage(NULL),
    document(),
    templateContainer(),
    _isReady(false),
    scroll(NULL),
    bookmarkedItem(NULL),
    scrollReadTimer(),
    jumpToBookmarkTimer(),
    jumpItem(NULL),
    forceRefreshTimer()
{
}

void NewsWeb::init(QDeclarativeWebView *webView, ScrollReader* scroll)
{
    this->webView = webView;
    this->scroll = scroll;
    
    // Enable HTTP cache.
    Utilities::addNetworkAccessManagerCache(webView->page()->networkAccessManager());
    
    // Settings.
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks); // Intercept links.
    webView->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, false); // No scripts.
    
    // Connect signals.
    connect(webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    connect(webView->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(onLinkClicked(QUrl)));
    connect(webView, SIGNAL(heightChanged()), this, SLOT(onGeometryChangeRequested()));
    connect(&scrollReadTimer, SIGNAL(timeout()), this, SLOT(onScrollReadTimeout()));
    connect(&jumpToBookmarkTimer, SIGNAL(timeout()), this, SLOT(onJumpTimeout()));
    connect(&forceRefreshTimer, SIGNAL(timeout()), this, SLOT(onForceRefreshTimeout()));
    connect(scroll, SIGNAL(contentYChanged(qreal)), this, SLOT(onContentYChanged(qreal)));
    connect(scroll, SIGNAL(jumpToBookmarkRequested()), this, SLOT(jumpToBookmark()));
    connect(scroll, SIGNAL(forceRefreshRequested()), this, SLOT(forceRefresh()));
    
    // Load the news page template.
    webView->setUrl(QUrl("qrc:html/NewsPage.html"));
    
    // Run the scroll read timer every 1/2 second.
    scrollReadTimer.start(500);
    
    forceRefreshTimer.setSingleShot(true);
}

void NewsWeb::clear()
{
    Q_ASSERT(_isReady);
    
    // Delete the bookmark.
    removeBookmark();
    
    // Remove all items in the view.
    // TODO: Use a find all selector.
    NewsItem* n = NULL;
    foreach(n, items)
        remove(n);
    
    // Clear the internal list.
    items.clear();
    
    // Jump the view back up to the tippy-top.
    scroll->setJumpY(0);
}

void NewsWeb::setFeed(FeedItem *feed)
{
    // Unset current signals.
    if (currentFeed != NULL) {
        disconnect(currentFeed, SIGNAL(appended(NewsItem*)), this, SLOT(append(NewsItem*)));
        disconnect(currentFeed, SIGNAL(removed(NewsItem*)), this, SLOT(remove(NewsItem*)));
        disconnect(currentFeed, SIGNAL(bookmarkChanged(NewsItem*)),
                   this, SLOT(setBookmark(NewsItem*)));
    }
    
    // Clear the view and set the new feed.
    clear();
    currentFeed = feed;
    scroll->setBottomSpacer(-1); // Signifies that the spacer hasn't bet set yet.
    
    // Connect signals.
    if (currentFeed != NULL) {
        // Append all exising items to the feed.
        QList<NewsItem*>* list = currentFeed->getNewsList();
        for (int i = 0; i < list->size(); i++) {
            NewsItem* item = list->at(i);
            append(item);
        }
        
        // Set current bookmark and jump to it.
        if (currentFeed->getBookmark() != NULL) {
            qDebug() << "(setfeed) This here feed's bookmark is: " << currentFeed->getBookmark()->getTitle();
            setBookmark(currentFeed->getBookmark());
            jumpToBookmark();
        }
        
        // Connect the feed's signals.
        connect(currentFeed, SIGNAL(appended(NewsItem*)), this, SLOT(append(NewsItem*)));
        connect(currentFeed, SIGNAL(removed(NewsItem*)), this, SLOT(remove(NewsItem*)));
        connect(currentFeed, SIGNAL(bookmarkChanged(NewsItem*)),
                   this, SLOT(setBookmark(NewsItem*)));
        
    }
}

void NewsWeb::append(NewsItem *item)
{
    Q_ASSERT(_isReady);
    if (items.contains(item))
        return; // Already seen this.
    
    QWebElement newsContainer = createNewElementForItem(item);
    
    //qDebug();
    //qDebug() << content;
    
    // Scrub content.
    QWebElement content = newsContainer.findFirst(".content");
    cleanConatiner(content);
    
//    qDebug();
//    qDebug() << content.toInnerXml();
    
    // Add to HTML.
    if (items.size() > 0)
        elementForItem(items.last()).appendOutside(newsContainer); // Append after last
    else
        templateContainer.appendOutside(newsContainer); // For first item
    
    // Add to our internal list.
    items.append(item);
}

void NewsWeb::remove(NewsItem *item)
{
    Q_ASSERT(_isReady);
    
    // If this is bookmarked, remove the bookmark.
    if (item == this->bookmarkedItem) {
        removeBookmark();
    }
    
    elementForItem(item).removeFromDocument();
    
    // Remove from the list.
    items.removeAll(item);
}

void NewsWeb::updateBottomSpacer()
{
    if (scroll == NULL)
        return; // Can't continue.
    
    if (webView->status() != QDeclarativeWebView::Ready)
        return; // Not ready.
    
    qreal spacer = 0;
    
    if (items.size() > 0) {
        // Adjust spacer height to the difference between the last item height and the view height,
        // plus ten percent of the view height.
        QWebElement lastElement = elementForItem(items.last());
        qreal viewHeight = getViewHeight();
        
        spacer = viewHeight - lastElement.geometry().height() + (viewHeight * 0.1);
    }
    
    if (spacer < 0)
        spacer = 0;
    
    scroll->setBottomSpacer(spacer);
}

void NewsWeb::onLoadFinished(bool ok)
{
    bumpScrollReadTimer();
    
    if (!ok)
        return; // This happens, just ignore it.
    
    // Initialize (or re-initialize) our vars.
    webPage = webView->page();
    document = webPage->mainFrame()->documentElement();
    templateContainer = document.findFirst("#model");
    
    //QSize size = webView->page()->viewportSize();
    //qDebug() << "Viewport size" << size;
    //qDebug() << "View " << webView->page()->view();
    
    // Ready for action!
    _isReady = true;
    emit ready();
}

void NewsWeb::onLinkClicked(const QUrl& url)
{
    // Open all links externally.
    QDesktopServices::openUrl(url);
}

void NewsWeb::onGeometryChangeRequested()
{
    //qDebug() << "Geometry change requested " << QDateTime::currentMSecsSinceEpoch();
    
    // If the size of the view changed, we may need to change the size of the bottom spacer.
    updateBottomSpacer();
    
    // If the scroll timer is on, delay it.
    bumpScrollReadTimer();
}

void NewsWeb::onContentYChanged(qreal contentY)
{
    Q_UNUSED(contentY);
    // TODO: somehow fire timer immediately if the user scrolls up, but only sometimes.
    
  //  qDebug() << "Content y: " << contentY;
}

void NewsWeb::onScrollReadTimeout()
{
    if (webView->status() != QDeclarativeWebView::Ready)
        return; // Web view isn't in the right state.
    
    if (currentFeed == NULL || currentFeed->getNewsList()->size() <= 0)
        return;  // Nothing to do.
    
    if (elementForItem(currentFeed->getNewsList()->last()).geometry().height() <= 0)
        return; // Geometry hasn't been computed yet.
    
    
    //qDebug() << "Scroll timeout, status is: " << webView->status() << " "  << QDateTime::currentMSecsSinceEpoch();
    
    // This method figures out which items are visible
    int halfWidth = getViewWidth() / 2;
    int viewHeight = getViewHeight();
    int fivePercentOfHeight = viewHeight / 5;
    qreal contentY = scroll->contentY();
    
    // We're at the bottom if there's not much more to scroll.
    bool atBottom = contentY >= getMaxScroll() - (scroll->bottomSpacer() / 10);
    
//    if (atBottom)
//        qDebug() << "At BOTTOM!";
    
    if (currentFeed->getNewsList()->size() == 1) {
        qDebug() << "First item is the only one!";
        // First item is the only one!
        currentFeed->setVisibleItems(NULL,
                                     currentFeed->getNewsList()->first(),
                                     atBottom);
        
        return;
    }
    
    // Stop any jumps in progress.
    jumpItem = NULL;
    
    // "Visible" items.
    // Despite the name, the top item is always just above the viewport, and the bottom item
    // may be in it or just under it.
    NewsItem* topVisibleItem = NULL;
    NewsItem* bottomVisibleItem = NULL;
    
    if (contentY == 0) {
        // At the top!
        topVisibleItem = NULL;
    } else {
        // Somewhere other than the top.
        // Start from y = contentY, move up a few notches to grab the first item just off the screen.
        int yStart = contentY;
        QWebElement topItemElement;
        for (int i = 0; i < 3; i++) {
            if (yStart < 0)
                break; // She can't take anymore, captain.
            
            QWebHitTestResult hitTest = document.webFrame()->hitTestContent(QPoint(halfWidth, yStart));
            topItemElement = hitTest.element();
            topVisibleItem = itemForElement(topItemElement);
            if (topVisibleItem != NULL) {
                // Get the "REAL" element (This is important for geometry computations.)
                topItemElement = elementForItem(topVisibleItem);
                
                break;
            }
            
            yStart -= fivePercentOfHeight; // Move up a little moar.
        }
        
        // Ensure the top item is entirely outside the viewport.
        if (topVisibleItem != NULL && topItemElement.geometry().y() +
                topItemElement.geometry().height() > contentY) {
            int index = currentFeed->getNewsList()->indexOf(topVisibleItem);
            if (index > 0) {
                topVisibleItem = currentFeed->getNewsList()->at(index - 1);
            } else {
                // No previous item.
                topVisibleItem = NULL;
            }
        }
    }
    
    if (contentY >= getMaxScroll() - scroll->bottomSpacer()) {
        // At the bottom!
        // Just grab the first item.
        bottomVisibleItem = currentFeed->getNewsList()->last();
    } else {
        // Not at the bottom (yet!)
        // Start at the bottom of the viewport and look a few notches down.
        int yStart = contentY + viewHeight;
        for (int i = 0; i < 3; i++) {
            QWebHitTestResult hitTest = document.webFrame()->hitTestContent(QPoint(halfWidth, yStart));
            bottomVisibleItem = itemForElement(hitTest.element());
            if (bottomVisibleItem != NULL) {
                break;
            }
            
            yStart += fivePercentOfHeight; // Move DOWN a couple spots.
        }
    }
    
    // Set 'em!
    currentFeed->setVisibleItems(topVisibleItem, bottomVisibleItem, atBottom);
}

void NewsWeb::onJumpTimeout()
{
    if (jumpItem == NULL)
        return;
    
    if (webView->status() != QDeclarativeWebView::Ready)
        return; // Web view isn't in the right state.
    
    QWebElement element = document.findFirst(".newsContainer#" + idForItem(jumpItem) + ">.bookmark");
    if (element.isNull() || element.geometry().height() <= 0)
        return;
    
    int y = element.geometry().y();
    
    // Don't exceed max scroll.
    int maxY = getMaxScroll();
    if (y > maxY)
        y = maxY;
    
    //qDebug() << "Jump to y: " << y;
    
    // Just do it.
    //qDebug() << "Jump to!";
    scroll->setJumpY(y);
    
    // Cool, we're done now.
    jumpToBookmarkTimer.stop();
    jumpItem = NULL;
}

void NewsWeb::jumpToItem(NewsItem *item)
{
    jumpItem = item;
    
    // Set jump in 150 ms.
    jumpToBookmarkTimer.start(150);
}

void NewsWeb::jumpToBookmark()
{
    if (bookmarkedItem == NULL)
        scroll->setJumpY(0);
    else
        jumpToItem(bookmarkedItem);
}

QWebElement NewsWeb::createNewElementForItem(NewsItem *item)
{
    QWebElement newsContainer = templateContainer.clone();
    newsContainer.setAttribute("id", idForItem(item));
    
    newsContainer.findFirst(".link").setAttribute("href", item->getURL().toString());
    newsContainer.findFirst(".link").setPlainText(item->getTitle());
    newsContainer.findFirst(".siteTitle").setPlainText(item->getFeed()->getTitle());
    newsContainer.findFirst(".date").setPlainText(item->getTimestamp().toString());
    
    // Use HTML content if available, otherwise use the summary.
    QString content = item->getContent() != "" ? item->getContent() : item->getSummary();
    QWebElement contentElement = newsContainer.findFirst(".content");
    contentElement.setInnerXml(content);
    
    return newsContainer;
}

bool NewsWeb::eventFilter(QObject *watched, QEvent* event)
{
    if (watched != NULL && event != NULL)
        qDebug() << "Event: " << event->type() << " from " << watched;
    
    return QObject::eventFilter(watched, event);
}

QString NewsWeb::idForItem(NewsItem *item)
{
    return item->id();
}

QWebElement NewsWeb::elementForItem(NewsItem *item)
{
    return document.findFirst("#" + idForItem(item));
}

NewsItem* NewsWeb::itemForElement(const QWebElement& element)
{
    if (element.isNull())
        return NULL; // Quick escape hatch.
    
    QWebElement currentElement = element;
    QString idString = "";
    while (!currentElement.isNull()) {
        if (currentElement.attribute("id").startsWith(NEWS_ITEM_ID_PREIX, Qt::CaseInsensitive)) {
            // WE FOUND IT!
            idString = currentElement.attribute("id");
            
            break;
        }
        
        // Climb up the DOM tree.
        currentElement = currentElement.parent();
    }
    
    if (idString == "")
        return NULL; // We didn't find anything. :(
    
    // Just iterate for it!  We should probably have it at this point, so no biggie.
    NewsItem* ret = NULL;
    foreach(NewsItem* item, items) {
        if (item->id().compare(idString, Qt::CaseInsensitive) == 0)
            ret = item;
    }
    
    return ret;
}

void NewsWeb::removeAll(const QString& selector, QWebElement element) {
    QWebElementCollection collection = element.findAll(selector);
    foreach (QWebElement e, collection)
        e.removeFromDocument();
}

void NewsWeb::setBookmark(NewsItem *item)
{
    qDebug() << "News web, set bookmark to: "<< item->getTitle();
    removeBookmark();
    
    QWebElement stripe = document.findFirst(newsItemToBookmarkSelector(item));
    stripe.setStyleProperty("visibility", "visible !important");
    bookmarkedItem = item;
}

void NewsWeb::removeBookmark()
{
    if (bookmarkedItem == NULL)
        return;
    
    QWebElement stripe = document.findFirst(newsItemToBookmarkSelector(bookmarkedItem));
    stripe.setStyleProperty("visibility", "hidden !important");
    
    bookmarkedItem = NULL;
}

QString NewsWeb::newsItemToBookmarkSelector(NewsItem *item)
{
    return ".newsContainer#" + idForItem(item) + " > .bookmark > .stripe";
}

qreal NewsWeb::getViewWidth()
{
    return webView->width();
}

void NewsWeb::cleanConatiner(QWebElement& newsContainer)
{
    // Remove stuff that I really hate.
    removeAll("script", newsContainer); // Javascript
    removeAll("style", newsContainer); // Custom styles.
    removeAll("iframe", newsContainer); // Iframes!
    removeAll(".feedflare", newsContainer); // Feedburger's 37 pieces of flare
    removeAll(".mf-viral", newsContainer); // Motherfucking viral?
    removeAll(".service-links-stumbleupon", newsContainer); // StubbleUponYourFace
    
    // Delete annoying images.
    QWebElementCollection collection = newsContainer.findAll("img");
    foreach (QWebElement e, collection) {
        QString parentHref = e.parent().tagName().toLower() == "a" ? e.parent().attribute("href") : "";
        QString src = e.attribute("src");
        QString sWidth = e.attribute("width");
        QString sHeight = e.attribute("height");
        
        bool removeElement = false;
        bool removeParent = false;
        
        // Remove tracking images.
        if (!sWidth.isEmpty() || !sHeight.isEmpty()) {
            int width = sWidth.toInt();
            int height = sWidth.toInt();
            if (width <= 3 && height <= 3)
                removeElement = true;
        }
        
        // Known trackers.
        if (src.contains("feedsportal.com/", Qt::CaseInsensitive))
            removeElement = true;
        
        // Delete social media icons.
        if (!parentHref.isEmpty()) {
            // Social media buttons and trackers.
            if (parentHref.contains("twitter.com/home?status", Qt::CaseInsensitive) ||
                    parentHref.contains("plus.google.com/shar", Qt::CaseInsensitive) ||
                    parentHref.contains("facebook.com/shar", Qt::CaseInsensitive) ||
                    parentHref.contains("feedsportal.com/", Qt::CaseInsensitive) ||
                    parentHref.contains("api.tweetmeme.com/", Qt::CaseInsensitive) ||
                    parentHref.contains("stumbleupon.com/submit", Qt::CaseInsensitive) ||
                    parentHref.contains("share.feedsportal.com/share", Qt::CaseInsensitive)) {
                // Social media buttons.
                removeParent = true;
            } else if (parentHref.length() > 200) {
                // Big links are suspiciously re-direct-y, look for keywords.
                if (parentHref.contains("twitter", Qt::CaseInsensitive) ||
                        parentHref.contains("facebook", Qt::CaseInsensitive) ||
                        parentHref.contains("linkedin", Qt::CaseInsensitive) ||
                        parentHref.contains("plus", Qt::CaseInsensitive) ||
                        parentHref.contains("twitter", Qt::CaseInsensitive) ||
                        parentHref.contains("mail", Qt::CaseInsensitive) ||
                        parentHref.contains("digg", Qt::CaseInsensitive) ||
                        parentHref.contains("social", Qt::CaseInsensitive) ||
                        parentHref.contains("yahoo", Qt::CaseInsensitive)) {
                    removeParent = true;
                }
            }
        }
        
        // Do the deed.
        if (removeParent)
            e.parent().removeFromDocument();
        else if (removeElement)
            e.removeFromDocument();
    }
    
    // Sometimes they throw line breaks at the bottom.  Screw 'em.
    while (true) {
        QWebElement last = newsContainer.lastChild();
        QString tag = last.tagName().toLower();
        if (tag == "br" || tag == "hr") {
            last.removeFromDocument();
        } else {
            break; // exit loop
        }
    }
}


qreal NewsWeb::getViewHeight()
{
    return webView->parentItem()->parentItem()->height();
}

qreal NewsWeb::getMaxScroll()
{
    return document.geometry().height() - (getViewHeight() - scroll->bottomSpacer());
}

void NewsWeb::bumpScrollReadTimer()
{
    if (scrollReadTimer.isActive()) {
        //qDebug() << "Pushing back scroll timer." << QDateTime::currentMSecsSinceEpoch();
        scrollReadTimer.start(300);
    }
}

void NewsWeb::onForceRefreshTimeout()
{
    // Make the parent flickable redraw itself.
    QDeclarativeItem* flickable = qobject_cast<QDeclarativeItem*>(webView->parent());
    Q_ASSERT(flickable != NULL);
    flickable->update(flickable->boundingRect());
}

void NewsWeb::forceRefresh()
{
    // Delay until event loop clears.
    forceRefreshTimer.start(1);
    
    // After the refresh, we'll need to jump to the bookmark.  Also bump the scroll read
    // timer so that we don't end up setting a bookmark.
    jumpToBookmark();
    bumpScrollReadTimer();
}
