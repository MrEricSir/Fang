#include "FeedDiscovery.h"
#include <QXmlStreamReader>

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
    
    machine.addStateChange(-1, FEED_ERROR, SLOT(onError())); // All errors.
    
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

void FeedDiscovery::onPageGrabberReady(QString *document)
{
    if (NULL == document || document->isEmpty()) {
        reportError("No page found");
        
        return;
    }

    // Scan the XML looking for an RSS and/or Atom feed.
    findFeeds(*document);
    
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

void FeedDiscovery::findFeeds(const QString& document)
{
    atomURL = "";
    rssURL = "";

    // Examples of what we're looking for:
    // <link rel="alternate" href="http://www.fark.com/fark.rss" type="application/rss+xml" title="FARK.com Fark RSS Feed">
    // <link rel="alternate" type="application/rss+xml" title="MrEricSir.com RSS Feed" href="http://www.mrericsir.com/blog/feed/" />
    // <link rel="alternate" type="application/atom+xml" title="MrEricSir.com Atom Feed" href="http://www.mrericsir.com/blog/feed/atom/" />
    const QString S_REL = "rel";
    const QString S_HREF = "href";
    const QString S_TYPE = "type";

    QXmlStreamReader xml;
    xml.addData(document);

    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();

        if (xml.isStartElement()) {
            QString tagName = xml.name().toString().toLower();
            if (tagName == "body") {
                // We're done with the header, so bail.
                return;
            }

            if (tagName == "link") {
                // This could be a feed...
                QXmlStreamAttributes attributes = xml.attributes();

                if (attributes.hasAttribute(S_REL) && attributes.hasAttribute(S_HREF) &&
                        attributes.value("", S_REL).toString().toLower() == "alternate" &&
                        attributes.hasAttribute(S_TYPE)) {
                    QString type = attributes.value("", S_TYPE).toString().toLower();
                    if (type == "application/atom+xml" && !atomURL.size()) {
                        atomURL = attributes.value("", S_HREF).toString();
                    } else if (type == "application/rss+xml" && !rssURL.size()) {
                        rssURL = attributes.value("", S_HREF).toString();
                    }
                }
            }
        }
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
