#include "FeedDiscovery.h"

FeedDiscovery::FeedDiscovery(QObject *parent) :
    FangObject(parent),
    machine(),
    _error(false),
    _errorString(""),
    pageGrabber(true),
    _feedResult(NULL)
{
    // Set up our state machine.
    machine.setReceiver(this);
    
    machine.addStateChange(CHECK_FEED, TRY_FEED, SLOT(onTryFeed()));
    machine.addStateChange(TRY_FEED, FEED_FOUND, SLOT(onFeedFound()));
    machine.addStateChange(TRY_FEED, WEB_GRABBER, SLOT(onWebGrabber()));
    machine.addStateChange(WEB_GRABBER, TRY_FEED_AGAIN, SLOT(onTryFeedAgain()));
    machine.addStateChange(TRY_FEED_AGAIN, FEED_FOUND, SLOT(onFeedFound()));
    
    machine.addStateChange(-1, FEED_ERROR, SLOT(onError())); // Many errors, one slot.
    
    // Parser signals.
    connect(&parserFirstTry, SIGNAL(done()), this, SLOT(onFirstParseDone()));
    connect(&parserSecondTry, SIGNAL(done()), this, SLOT(onSecondParseDone()));
    
    // Web page grabber signals.
    connect(&pageGrabber, &WebPageGrabber::ready, this, &FeedDiscovery::onPageGrabberReady);
}

void FeedDiscovery::checkFeed(QString sURL)
{
    // Reset.
    _error = false;
    _errorString = "";
    machine.start(CHECK_FEED);

    QUrl url = urlFixup(sURL);
    
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
        _feedResult = parserFirstTry.getFeed();
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
        _feedResult = parserSecondTry.getFeed();
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

void FeedDiscovery::onPageGrabberReady(QDomDocument *page)
{
    if (NULL == page || page->isNull()) {
        reportError("No page found");
        
        return;
    }

    // Recursively walk the DOM looking for an RSS and/or Atom feed.
    rssURL = "";
    atomURL = "";
    traveseXML(*page);
    
    // Check if the page contains a URL.
    QString newUrl = "";
    if (atomURL.size()) {
        newUrl = urlFixup(atomURL);
    } else if (rssURL.size()) {
        newUrl = urlFixup(rssURL);
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

void FeedDiscovery::traveseXML(const QDomNode &node)
{
    // Stop condition.
    if (rssURL.size() && atomURL.size()) {
        return;
    }

    QDomNode domNode = node;
    QDomElement domElement;

    // Loop sibblings at this level.
    while(!(domNode.isNull()))
    {
        QString nodeName = domNode.nodeName();
        //qDebug() << "Node: " << nodeName;

        // Stop condition.
        if (nodeName == "body") {
            // Given that we're only intersted in headers, we can stop when we get to the body node.

            return;
        }

        // Examples of what we're looking for:
        // <link rel="alternate" href="http://www.fark.com/fark.rss" type="application/rss+xml" title="FARK.com Fark RSS Feed">
        // <link rel="alternate" type="application/rss+xml" title="MrEricSir.com RSS Feed" href="http://www.mrericsir.com/blog/feed/" />
        // <link rel="alternate" type="application/atom+xml" title="MrEricSir.com Atom Feed" href="http://www.mrericsir.com/blog/feed/atom/" />
        if (domNode.isElement())
        {
            domElement = domNode.toElement();
            if(!(domElement.isNull()))
            {
                if (nodeName == "link" && domElement.attribute("rel").toLower() == "alternate") {
                    // RSS check.
                    if (!rssURL.size() && domElement.attribute("type").toLower() == "application/rss+xml"
                            && domElement.hasAttribute("href")) {
                        rssURL = domElement.attribute("href");
                    }

                    // Atom check.
                    if (!atomURL.size() && domElement.attribute("type").toLower() == "application/atom+xml"
                            && domElement.hasAttribute("href")) {
                        atomURL = domElement.attribute("href");
                    }
                }
            }
        }

        // Recurse children.
        QDomNode child = domNode.firstChild();
        while(!child.isNull()) {
            // Recurse!
            traveseXML(child);
            child = child.nextSibling();
        }

        // Continue outter loop.
        domNode = domNode.nextSibling();
    }
}

QString FeedDiscovery::urlFixup(const QString &url) const
{
    if (url.startsWith("//")) {
        // Just assume it's http.
        return "http:" + url;
    }

    if (!url.contains(':') && url.size() && url.at(0).isLetterOrNumber()) {
        // Also assume it's http.
        return "http://" + url;
    }

    // Hopefully it's correct!
    return url;
}

void FeedDiscovery::reportError(QString errorString)
{
    _error = true;
    _errorString = errorString;
    
    machine.setState(FEED_ERROR);
}
