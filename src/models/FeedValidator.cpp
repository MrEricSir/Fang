#include "FeedValidator.h"
#include "../FangApp.h"

FeedValidator::FeedValidator(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    parser(NULL),
    _validating(false),
    webPage(NULL),
    _url(""),
    _siteTitle(""),
    _siteImageURL(""),
    result(Parser::IN_PROGRESS)
{
    connect(&pageGrabber, SIGNAL(ready(QWebPage*)), this, SLOT(onPageGrabberReady(QWebPage*)));
}

void FeedValidator::check()
{
    // Clear our state.
    result = Parser::IN_PROGRESS;
    webPage = NULL;
    embeddedFeedURL.clear();
    
    // Signal start.
    _validating = true;
    emit validatingChanged(_validating);
    
    QUrl location = QUrl(_url);
    
    // Make sure the location isn't a "relative" (and therefore severely invalid) path.
    if (location.isRelative() || location.scheme().isEmpty()) {
        // Try adjusting the scheme.
        if (location.scheme() == "")
            location.setScheme("http");
        
        //qDebug() << "Location is adjusted to: " << location;
        
        // Final check!  If it's not valid, we'll set an error and bail.
        if (location.isRelative()) {
            emit validationComplete(false, "Invalid URL.");
            
            return;
        }
    }
    
    // Parse the feed.
    doParse(location);
    
    // If it's an HTML page, we'll check for a newsfeed link.
    pageGrabber.load(location);
}

void FeedValidator::doParse(const QUrl& url)
{
    // If there's an existing parser, there won't be for long.
    delete parser;
    
    // Create a new one an' hook it up.
    parser = new Parser(this);
    connect(parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
    
    // Do the parse.
    parser->parse(url);
}

void FeedValidator::addFeed()
{
    // Assume check passed.
    // TODO: add sanity check here.
    
    FangApp::instance()->addFeed(QUrl(_url), QUrl(_siteImageURL), _siteTitle);
}

void FeedValidator::removeFeed(FeedItem *feed)
{
    FangApp::instance()->removeFeed(feed);
}


void FeedValidator::setUrl(QString url)
{
    if (url == _url)
        return;
    
    _url = url;
    emit urlChanged(_url);
}

void FeedValidator::setSiteTitle(QString title)
{
    if (title == _siteTitle)
        return;
    
    _siteTitle = title;
    emit siteTitleChanged(_siteTitle);
}

void FeedValidator::setSiteImageURL(QString url)
{
    if (url == _siteImageURL)
        return;
    
    _siteImageURL = url;
    emit siteImageURLChanged(_siteImageURL);
}

void FeedValidator::onFeedFinished()
{
    // Get result.
    result = parser->getResult();
    RawFeed* feed = parser->getFeed();
    qDebug() << "Feed finished! " << ((feed == NULL) ? "it was null. :(" : feed->title);
    
    // Figure out if we're good or not.
    if (result == Parser::OK) {
        // YAY!  Nothing more to do.
        _validating = false;
        emit validatingChanged(_validating);
        
        setUrl(parser->getURL().toString()); // set the REAL url
        _siteTitle = feed->title;
        emit validationComplete(true, "");
    } else {
        // We didn't find a feed, so wait for the page grabber.  Maybe it's HTML?
        handleCompletion();
    }
}

void FeedValidator::onPageGrabberReady(QWebPage* page)
{
    webPage = page;
    
    // Find the first feed URL.
    QWebElement doc = page->mainFrame()->documentElement();
    if (doc.isNull()) {
        handleCompletion();
        
        return;
    }
    
    // Look for feeds.
    QWebElement atomLink = doc.findFirst("link[type=application\\/atom\\+xml]"); // Escape \ and +
    QWebElement rssLink = doc.findFirst("link[type=application\\/rss\\+xml]");
    
    // If we got one, set it!
    if (!atomLink.isNull() && atomLink.hasAttribute("href"))
        embeddedFeedURL = QUrl(atomLink.attribute("href"));
    else if (!rssLink.isNull() && rssLink.hasAttribute("href"))
        embeddedFeedURL = QUrl(rssLink.attribute("href"));
    
    handleCompletion();
}

void FeedValidator::handleCompletion()
{
    if (!_validating)
        return; // Already sent signal.
    
    if (webPage == NULL)
        return; // Still waiting for web page.
    
    if (result == Parser::IN_PROGRESS)
        return; // Still waiting for parser.
    
    if (!embeddedFeedURL.isEmpty()) {
        // Try again with the new URL if it looks good.
        if (embeddedFeedURL.isValid() && !embeddedFeedURL.isRelative()) {
            qDebug() << "Parsing new URL" << embeddedFeedURL;
            doParse(embeddedFeedURL);
            embeddedFeedURL.clear(); // Remember that we did this!
            
            return;
        }
    }
    
    // Okay, nothing more we can do!
    _validating = false; // done
    emit validatingChanged(_validating);
    
    // Handle errors.
    if (result == Parser::NETWORK_ERROR)
        emit validationComplete(false, "Could not access URL.");
    else if (result == Parser::PARSE_ERROR)
        emit validationComplete(false, "Error parsing feed.");
    else
        Q_ASSERT(false); // We added an error but forgot to handle it here.
}
