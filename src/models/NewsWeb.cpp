#include "NewsWeb.h"

#include "../utilities/Utilities.h"

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
    bookmarkTimer(),
    jumpToBookmarkTimer(),
    jumpItem(NULL)
{
    jumpToBookmarkTimer.setSingleShot(true);
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
    connect(&bookmarkTimer, SIGNAL(timeout()), this, SLOT(onBookmarkTimeout()));
    connect(&jumpToBookmarkTimer, SIGNAL(timeout()), this, SLOT(onJumpTimeout()));
    connect(scroll, SIGNAL(contentYChanged(qreal)), this, SLOT(onContentYChanged(qreal)));
    
    // Load the news page template.
    webView->setUrl(QUrl("qrc:html/NewsPage.html"));
    
    // Run the bookmark timer every 1.5 seconds.
    bookmarkTimer.start(1500);
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
    }
    
    // Clear the view and set the new feed.
    clear();
    currentFeed = feed;
    
    // Connect signals.
    if (currentFeed != NULL) {
        // Append all exising items to the feed.
        QList<NewsItem*>* list = currentFeed->getNewsList();
        for (int i = 0; i < list->size(); i++) {
            NewsItem* item = list->at(i);
            append(item);
        }
        
        connect(currentFeed, SIGNAL(appended(NewsItem*)), this, SLOT(append(NewsItem*)));
        connect(currentFeed, SIGNAL(removed(NewsItem*)), this, SLOT(remove(NewsItem*)));
        
        // Set current bookmark and jump to it.
        if (currentFeed->getBookmark() != NULL) {
            setBookmark(currentFeed->getBookmark());
            jumpToItem(currentFeed->getBookmark());
        }
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

void NewsWeb::onLoadFinished(bool ok)
{
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
    qDebug() << "Geom change: ";// << rect;
    
    // If we're preparing to jump to a bookmark, delay the timer very slightly.
    if (jumpToBookmarkTimer.isActive())
        jumpToBookmarkTimer.start(10);
}

void NewsWeb::onContentYChanged(qreal contentY)
{
    Q_UNUSED(contentY);
    // TODO: somehow fire timer immediately if the user scrolls up, but only sometimes.
    
  //  qDebug() << "Content y: " << contentY;
}

void NewsWeb::onBookmarkTimeout()
{
    qreal contentY = scroll->contentY();
    
    int halfWidth = webView->width() / 2;
    int fivePercentOfHeight = webView->parentItem()->parentItem()->height() / 5;
    int yStart = fivePercentOfHeight;
    NewsItem* item = NULL;
    
    //qDebug() << "Y " << contentY << " half width: " << halfWidth << " negativeHeight: " << negativeHeight;
    
    // Look at coordinates (halfWidth, yStart) to try to find an item.
    // Failing that, move a couple notches down.
    for (int i = 0; i < 2; i++) {
        QWebHitTestResult hitTest = document.webFrame()->hitTestContent(QPoint(halfWidth, contentY + yStart));
        item = itemForElement(hitTest.element());
        if (item != NULL) {
            break;
        }
        
        yStart += fivePercentOfHeight; // Move down a little moar.
    }
    
    // Try to bookmark the PREVIOUS item in the list, if there is one.
    // (Otherwise, this one will do.)
    int index = items.indexOf(item);
    if (index > 0)
        item = items.at(index - 1);
    
    // Only bookmark this one if it's newer than the current bookmark.
    if (item != NULL && item != bookmarkedItem &&
            (bookmarkedItem == NULL || item->getTimestamp() > bookmarkedItem->getTimestamp())) {
        setBookmark(item);
        emit newsItemBookmarked(item);
    }
}

void NewsWeb::onJumpTimeout()
{
    if (jumpItem == NULL)
        return;
    
    int y = document.findFirst(".newsContainer#" + idForItem(jumpItem)).geometry().y();
    //qDebug() << "Jumping to y: " << y << "  " << document.geometry().height();
    
    // Don't exceed max scroll.
    int maxY = document.geometry().height() - webView->parentItem()->parentItem()->height();
    if (y > maxY)
        y = maxY;
    
    // Just do it.
    scroll->setJumpY(y);
    
    jumpItem = NULL;
}

void NewsWeb::jumpToItem(NewsItem *item)
{
    jumpItem = item;
    
    // Set jump in 150 ms.
    jumpToBookmarkTimer.start(150);
}

QWebElement NewsWeb::createNewElementForItem(NewsItem *item)
{
    QWebElement newsContainer = templateContainer.clone();
    newsContainer.setAttribute("id", idForItem(item));
    
    newsContainer.findFirst(".link").setAttribute("href", item->getURL().toString());
    newsContainer.findFirst(".link").setPlainText(item->getTitle());
    newsContainer.findFirst(".jumpTarget").setAttribute("id", idForItem(item));
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

void NewsWeb::cleanConatiner(QWebElement& newsContainer)
{
    // Remove stuff that I really hate.
    removeAll("script", newsContainer); // Javascript
    removeAll("style", newsContainer); // Custom styles.
    removeAll("iframe", newsContainer); // Iframes!
    removeAll(".feedflare", newsContainer); // Feedburger's 37 pieces of flare
    removeAll(".mf-viral", newsContainer); // Motherfucking viral?
    
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
            if (width <= 3 || height <= 3)
                removeElement = true;
        }
        
        // Known trackers.
        if (src.contains("feedsportal.com/", Qt::CaseInsensitive))
            removeElement = true;
        
        // Delete social media icons.
        if (!parentHref.isEmpty()) {
            if (parentHref.contains("twitter.com/home?status", Qt::CaseInsensitive) ||
                    parentHref.contains("plus.google.com/shar", Qt::CaseInsensitive) ||
                    parentHref.contains("facebook.com/shar", Qt::CaseInsensitive) ||
                    parentHref.contains("da.feedsportal.com/r", Qt::CaseInsensitive) ||
                    parentHref.contains("share.feedsportal.com/share", Qt::CaseInsensitive)) {
                // Social media buttons.
                removeParent = true;
            } else if (parentHref.contains("feedsportal.com/", Qt::CaseInsensitive)) {
                // Known trackers.
                removeParent = true;
            } else if (parentHref.length() > 200) {
                // Big links are suspiciously re-directy, look for keywords.
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

