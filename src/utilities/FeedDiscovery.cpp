#include "FeedDiscovery.h"

#include <QWebPage>
#include <QWebElement>
#include <QWebFrame>

FeedDiscovery::FeedDiscovery(QObject *parent) :
    QObject(parent),
    machine(),
    _error(false),
    _errorString("")
{
    // Set up our state machine.
    machine.setReceiver(this);
    
    machine.addStateChange(CHECK_FEED, TRY_FEED, SLOT(onTryFeed()));
    machine.addStateChange(TRY_FEED, FEED_FOUND, SLOT(onFeedFound()));
    machine.addStateChange(TRY_FEED, WEB_GRABBER, SLOT(onWebGrabber()));
    machine.addStateChange(WEB_GRABBER, TRY_FEED_AGAIN, SLOT(onTryFeedAgain()));
    machine.addStateChange(TRY_FEED_AGAIN, FEED_FOUND, SLOT(onFeedFound()));
    
    machine.addStateChange(-1, ERROR, SLOT(onError())); // Many errors, one slot.
    
    // Parser signals.
    connect(&parserFirstTry, SIGNAL(done()), this, SLOT(onFirstParseDone()));
    connect(&parserSecondTry, SIGNAL(done()), this, SLOT(onSecondParseDone()));
    
    // Web page grabber signals.
    connect(&pageGrabber, SIGNAL(ready(QWebPage*)), this, SLOT(onPageGrabberReady(QWebPage*)));
}

void FeedDiscovery::checkFeed(QUrl url)
{
    // Reset.
    _error = false;
    _errorString = "";
    machine.start(CHECK_FEED);
    
    // Make sure the location isn't a "relative" (and therefore severely invalid) path.
    if (url.isRelative() || url.scheme().isEmpty()) {
        // Try adjusting the scheme.
        if (url.scheme() == "")
            url.setScheme("http");
        
        //qDebug() << "Location is adjusted to: " << location;
        
        // Final check!  If it's not valid, we'll set an error and bail.
        if (url.isRelative()) {
            reportError("Invalid URL");
            
            return;
        }
    }
    
    // Okay, we have a potential URL! Let's check it.
    _feedURL = url;
    machine.setState(TRY_FEED);
}

void FeedDiscovery::onTryFeed()
{
    parserFirstTry.parse(_feedURL);
}

void FeedDiscovery::onFeedFound()
{
    Q_ASSERT(!_error);
    Q_ASSERT(!_feedURL.isEmpty());
    
    emit done(this);
}

void FeedDiscovery::onWebGrabber()
{
    pageGrabber.load(_feedURL);
}

void FeedDiscovery::onTryFeedAgain()
{
    parserSecondTry.parse(_feedURL);
}

void FeedDiscovery::onError()
{
    Q_ASSERT(_error);
    Q_ASSERT(!_errorString.isEmpty());
    
    emit done(this);
}

void FeedDiscovery::onFirstParseDone()
{
    int res = parserFirstTry.getResult();
    switch (res) {
    case ParserInterface::OK:
        // We got it on the first try!
        _feedURL = parserFirstTry.getURL();
        machine.setState(FEED_FOUND);
        
        break;
    case ParserInterface::NETWORK_ERROR:
    case ParserInterface::FILE_ERROR:
    case ParserInterface::EMPTY_DOCUMENT:
    case ParserInterface::PARSE_ERROR:
        // Continue to the web grabber stage.
        machine.setState(WEB_GRABBER);
        
        break;
        
    case ParserInterface::IN_PROGRESS:
    default:
        Q_ASSERT(false); // Either we didn't add a new case, or the parser yarfed on us.
    }
}

void FeedDiscovery::onSecondParseDone()
{
    int res = parserSecondTry.getResult();
    switch (res) {
    case ParserInterface::OK:
        // We got it!
        _feedURL = parserSecondTry.getURL();
        machine.setState(FEED_FOUND);
        
        break;
    case ParserInterface::NETWORK_ERROR:
        reportError("Could not reach URL");
        
        break;
    case ParserInterface::FILE_ERROR:
        reportError("Could not load file");
        
        break;
    case ParserInterface::EMPTY_DOCUMENT:
    case ParserInterface::PARSE_ERROR:
        reportError("Error parsing feed");
        
        break;
    case ParserInterface::IN_PROGRESS:
    default:
        Q_ASSERT(false); // Either we didn't add a new case, or the parser yarfed on us.
    }
}

void FeedDiscovery::onPageGrabberReady(QWebPage *page)
{
    // Find the first feed URL.
    QWebElement doc = page->mainFrame()->documentElement();
    if (doc.isNull()) {
        reportError("Error reading page");
        
        return;
    }
    
    // Look for feeds.
    QWebElement atomLink = doc.findFirst("link[type=application\\/atom\\+xml]"); // Escape \ and +
    QWebElement rssLink = doc.findFirst("link[type=application\\/rss\\+xml]");
    
    // Check if the page contains a URL.
    QString newUrl = "";
    if (!atomLink.isNull() && atomLink.hasAttribute("href")) {
        newUrl = atomLink.attribute("href");
    } else if (!rssLink.isNull() && rssLink.hasAttribute("href")) {
        newUrl = rssLink.attribute("href");
    }
    
    // If we got one, set it and try again!
    if (newUrl != "") {
        QUrl url(newUrl);
        if (url.isRelative()) {
            // Relative path case.
            _feedURL.setPath(url.path());
        } else {
            // Absolute path case.
            _feedURL = url;
        }
        
        machine.setState(TRY_FEED_AGAIN);
        return;
    }
    
    reportError("No feed found");
}

void FeedDiscovery::reportError(QString errorString)
{
    _error = true;
    _errorString = errorString;
    
    machine.setState(ERROR);
}
