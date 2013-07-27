#include "NewsWeb.h"

NewsWeb::NewsWeb(QObject *parent) :
    QObject(parent),
    webView(NULL),
    items(),
    webPage(NULL),
    document(),
    templateContainer(),
    _isReady(false)
{
}

void NewsWeb::init(QDeclarativeWebView *webView)
{
    this->webView = webView;
    
    // Connect signals.
    QObject::connect(webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    
    // Load the news page template.
    webView->setUrl(QUrl("qrc:html/NewsPage.html"));
}


void NewsWeb::clear()
{
    Q_ASSERT(_isReady);
    
    // Remove all items in the view.
    // TODO: Use a find all selector.
    NewsItem* n = NULL;
    foreach(n, items)
        remove(n);
    
    // Clear the internal list.
    items.clear();
}

void NewsWeb::append(NewsItem *item)
{
    Q_ASSERT(_isReady);
    
    // Add to our list.
    items.append(item);
    
    QWebElement newsContainer = templateContainer.clone();
    newsContainer.setAttribute("id", idForItem(item));
    
    newsContainer.findFirst(".link").setAttribute("href", item->getURL().toString());
    newsContainer.findFirst(".link").setPlainText(item->getTitle());
    newsContainer.findFirst(".siteTitle").setPlainText(item->getFeed()->getTitle());
    newsContainer.findFirst(".date").setPlainText(item->getTimestamp().toString());
    
    QString content = item->getContent() != "" ? item->getContent() : item->getSummary();
    newsContainer.findFirst(".content").setInnerXml(content);
    
    qDebug();
    qDebug() << content;
    cleanConatiner(newsContainer);
    
    // Add to HTML.
    // TODO: add after last item (need ids first)
    templateContainer.appendOutside(newsContainer);
}

void NewsWeb::remove(NewsItem *item)
{
    Q_ASSERT(_isReady);
    
    document.findFirst("#" + idForItem(item)).removeFromDocument();
    
    // Remove from the list.
    items.removeAll(item);
}

void NewsWeb::onLoadFinished(bool ok)
{
    if (!ok) {
        qDebug() << "Could not load web page.";
        
        return;
    }
    
    // Initialize our vars.
    webPage = webView->page();
    document = webPage->mainFrame()->documentElement();
    templateContainer = document.findFirst("#model");
    
    // Ready for action!
    _isReady = true;
    emit ready();
}

QString NewsWeb::idForItem(NewsItem *item)
{
    return item->id();
}

void NewsWeb::removeAll(const QString& selector, QWebElement element) {
    QWebElementCollection collection = element.findAll(selector);
    foreach (QWebElement e, collection)
        e.removeFromDocument();
}

void NewsWeb::cleanConatiner(QWebElement& newsContainer)
{
    // Remove stuff that I really hate.
    removeAll("script", newsContainer); // Javascript
    removeAll("style", newsContainer); // Custom styles.
    removeAll("iframe", newsContainer); // Iframes!
    removeAll(".feedflare", newsContainer); // Feedburger's 37 pieces of flare
    
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
                    parentHref.contains("facebook.com/shar", Qt::CaseInsensitive)) {
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
}

                    
