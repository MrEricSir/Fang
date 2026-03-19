#include "FeedDiscovery.h"
#include "FangLogging.h"
#include "PageMetadataExtractor.h"
#include <QXmlStreamReader>
#include <QSet>
#include <algorithm>
#include "NetworkUtilities.h"
#include "ErrorHandling.h"
#include "../parser/NewsParser.h"
#include "../parser/BatchNewsParser.h"
#include "WebPageGrabber.h"

FeedDiscovery::FeedDiscovery(QObject *parent,
                           ParserInterface* firstParser,
                           ParserInterface* secondParser,
                           WebPageGrabber* pageGrabber,
                           BatchNewsParser* feedParser,
                           GoogleNewsSitemapSynthesizer* sitemapSynthesizer) :
    FangObject(parent),
    machine(),
    _error(false),
    _errorString(""),
    _feedResult(nullptr),
    _probingCommonPaths(false),
    newsSitemapSynthesizer(sitemapSynthesizer)
{
    // Handle secondParser: no longer used, but we need to clean it up if provided
    if (secondParser) {
        if (!secondParser->parent()) {
            secondParser->setParent(this);  // Take ownership so it gets cleaned up
        }
    }

    // Create default implementations if not provided (with this as parent for auto-cleanup)
    parserFirstTry = firstParser ? firstParser : new NewsParser(this);
    this->pageGrabber = pageGrabber ? pageGrabber : new WebPageGrabber(this);
    this->feedParser = feedParser ? feedParser : new BatchNewsParser(this);

    // Take ownership of injected dependencies by setting parent
    if (parserFirstTry && !parserFirstTry->parent()) {
        parserFirstTry->setParent(this);
    }
    if (this->pageGrabber && !this->pageGrabber->parent()) {
        this->pageGrabber->setParent(this);
    }
    if (this->feedParser && !this->feedParser->parent()) {
        this->feedParser->setParent(this);
    }
    if (newsSitemapSynthesizer && !newsSitemapSynthesizer->parent()) {
        newsSitemapSynthesizer->setParent(this);
    }

    // Set up our state machine.
    machine.addStateChange(CHECK_FEED, TRY_FEED, [this]() { onTryFeed(); });
    machine.addStateChange(TRY_FEED, FEED_FOUND, [this]() { onFeedFound(); });
    machine.addStateChange(TRY_FEED, WEB_GRABBER, [this]() { onWebGrabber(); });
    machine.addStateChange(WEB_GRABBER, VALIDATE_FEEDS, [this]() { onValidateFeeds(); });
    machine.addStateChange(VALIDATE_FEEDS, FEED_FOUND, [this]() { onFeedFound(); });
    machine.addStateChange(WEB_GRABBER, TRY_COMMON_PATHS, [this]() { onTryCommonPaths(); });
    machine.addStateChange(VALIDATE_FEEDS, TRY_COMMON_PATHS, [this]() { onTryCommonPaths(); });
    machine.addStateChange(TRY_COMMON_PATHS, FEED_FOUND, [this]() { onFeedFound(); });
    machine.addStateChange(TRY_COMMON_PATHS, TRY_GOOGLE_NEWS_SITEMAP, [this]() { onTryGoogleNewsSitemap(); });
    machine.addStateChange(TRY_GOOGLE_NEWS_SITEMAP, FEED_FOUND, [this]() { onFeedFound(); });

    machine.addStateChange(-1, FEED_ERROR, [this]() { onError(); }); // All errors.

    // Overall discovery timeout.
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(30000);
    connect(&timeoutTimer, &QTimer::timeout, this, &FeedDiscovery::onTimeout);

    // Parser signals.
    connect(parserFirstTry, &ParserInterface::done, this, &FeedDiscovery::onFirstParseDone);

    // Web page grabber signals.
    connect(this->pageGrabber, &WebPageGrabber::ready, this, &FeedDiscovery::onPageGrabberReady);
    connect(this->feedParser, &BatchNewsParser::ready, this, &FeedDiscovery::onFeedParserReady);
}

FeedDiscovery::~FeedDiscovery()
{
    // Qt parent/child hierarchy handles cleanup automatically
}

void FeedDiscovery::checkFeed(QString sURL)
{
    // Reset state
    _error = false;
    _errorString = "";
    _probingCommonPaths = false;
    _discoveredFeeds.clear();
    _sortedFeedURLs.clear();
    machine.start(CHECK_FEED);

    QUrl url = NetworkUtilities::urlFixup(sURL);
    
    // Make sure the location isn't a "relative" (and therefore severely invalid) path.
    if (url.isRelative() || url.scheme().isEmpty()) {
        // Try adjusting the scheme.
        if (url.scheme() == "") {
            url.setScheme("http");
        }
        
        //qCDebug(logUtility) << "Location is adjusted to: " << location;
        
        // Final check!  If it's not valid, we'll set an error and bail.
        if (url.isRelative()) {
            reportError("Invalid URL");
            
            return;
        }
    }
    
    // Okay, we have a potential URL! Let's check it.
    _feedURL = url;
    machine.setState(TRY_FEED);
    timeoutTimer.start();
}

void FeedDiscovery::onTryFeed()
{
    parserFirstTry->parse(_feedURL);
}

void FeedDiscovery::onFeedFound()
{
    timeoutTimer.stop();
    FANG_CHECK(!_error, "FeedDiscovery::onFeedFound called with _error set");
    FANG_CHECK(!_feedURL.isEmpty(), "FeedDiscovery::onFeedFound called with empty _feedURL");

    emit done(this);
}

void FeedDiscovery::onWebGrabber()
{
    pageGrabber->load(_feedURL);
}

void FeedDiscovery::onError()
{
    timeoutTimer.stop();
    FANG_CHECK(_error, "FeedDiscovery::onError called without _error set");
    FANG_CHECK(!_errorString.isEmpty(), "FeedDiscovery::onError called with empty _errorString");

    emit done(this);
}

void FeedDiscovery::onTimeout()
{
    reportError("Feed discovery timed out");
}

void FeedDiscovery::onFirstParseDone()
{
    int res = parserFirstTry->getResult();
    switch (res) {
    case ParserInterface::OK:
    {
        // User directly entered a feed URL! Add it to discovered feeds
        _feedURL = parserFirstTry->getURL();
        _feedResult = parserFirstTry->getFeed();

        // Reject empty feeds - a feed that parses OK but has no items is useless.
        if (!_feedResult || _feedResult->items.isEmpty()) {
            qCDebug(logUtility) << "Feed parsed OK but has no items, trying web grabber";
            machine.setState(WEB_GRABBER);
            break;
        }

        // Add to discovered feeds list
        DiscoveredFeed discovered;
        discovered.url = _feedURL;
        discovered.feed = _feedResult;
        discovered.title = _feedResult->title.isEmpty() ? _feedURL.toString() : _feedResult->title;
        discovered.validated = true;
        _discoveredFeeds.clear();
        _discoveredFeeds.append(discovered);

        machine.setState(FEED_FOUND);
        break;
    }

    case ParserInterface::NETWORK_ERROR:
    case ParserInterface::FILE_ERROR:
    case ParserInterface::EMPTY_DOCUMENT:
    case ParserInterface::PARSE_ERROR:
        // Not a feed, probably HTML. Continue to the web grabber stage.
        machine.setState(WEB_GRABBER);
        break;

    case ParserInterface::IN_PROGRESS:
    default:
        FANG_UNREACHABLE("Unexpected parser result in onFirstParseDone");
        // Treat as error and continue to web grabber
        machine.setState(WEB_GRABBER);
        break;
    }
}

void FeedDiscovery::onPageGrabberReady(WebPageGrabber* grabber, QString* document)
{
    Q_UNUSED(grabber);

    // If we didn't get a document, try common paths before giving up.
    if (!document || document->isEmpty()) {
        qCDebug(logUtility) << "No page found, trying common paths";
        machine.setState(TRY_COMMON_PATHS);
        return;
    }

    // Parse feed URLs from the HTML document
    QList<QString> feedURLs = parseFeedsFromXHTML(*document);
    qCDebug(logUtility) << "Parsed" << feedURLs.count() << "feed URLs from HTML";

    if (feedURLs.isEmpty()) {
        qCDebug(logUtility) << "No feeds found in HTML, trying common paths";
        _pageXHTML = *document;
        machine.setState(TRY_COMMON_PATHS);
        return;
    }

    qCDebug(logUtility) << "Total feed URLs found:" << feedURLs.count();

    // Sort by path length (longer paths first = more specific)
    QList<QString> feedURLStrings = feedURLs;
    std::sort(feedURLStrings.begin(), feedURLStrings.end(),
        [](const QString& a, const QString& b) {
            QUrl urlA(a);
            QUrl urlB(b);
            return urlA.path().length() > urlB.path().length();
        });

    // Convert to QUrl list and store for validation
    _sortedFeedURLs.clear();
    for (const QString& urlString : feedURLStrings) {
        QUrl feedUrl(urlString);

        // Fix relative URLs.
        if (feedUrl.isRelative()) {
            feedUrl = _feedURL.resolved(feedUrl);
        }
        _sortedFeedURLs.append(feedUrl);
    }

    // Trigger bulk feed validation
    machine.setState(VALIDATE_FEEDS);
}

QList<QString> FeedDiscovery::parseFeedsFromXHTML(const QString& document)
{
    QList<QString> feedsFound;

    // Examples of what we're looking for:
    // <link rel="alternate" href="http://www.fark.com/fark.rss" type="application/rss+xml" title="FARK.com Fark RSS Feed">
    // <link rel="alternate" type="application/rss+xml" title="MrEricSir.com RSS Feed" href="http://www.mrericsir.com/blog/feed/" />
    // <link rel="alternate" type="application/atom+xml" title="MrEricSir.com Atom Feed" href="http://www.mrericsir.com/blog/feed/atom/" />
    const QString S_REL = "rel";
    const QString S_HREF = "href";
    const QString S_TYPE = "type";
    const QString S_TITLE = "title";
    const QString S_WORDPRESS_COMMENTS_URL_SUFFIX = "/comments/feed/";

    QXmlStreamReader xml;
    xml.addData(document);

    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();

        if (xml.isStartElement()) {
            QString tagName = xml.name().toString().toLower();
            if (tagName == "body") {
                // We're done with the header, so bail.
                return feedsFound;
            }

            if (tagName == "link") {
                QXmlStreamAttributes attributes = xml.attributes();

                // Is this a feed?
                if (attributes.hasAttribute(S_REL) && attributes.hasAttribute(S_HREF) &&
                    attributes.value("", S_REL).toString().toLower() == "alternate" &&
                    attributes.hasAttribute(S_TYPE) &&
                    (attributes.value("", S_TYPE).toString().toLower() == "application/rss+xml" ||
                     attributes.value("", S_TYPE).toString().toLower() == "application/atom+xml")) {
                    // Run some checks and then add our feed if it seems reasonable to do so.
                    QString url = attributes.value("", S_HREF).toString();

                    // Avoid comments feeds as they tend to get added by accident.
                    if (url.endsWith(S_WORDPRESS_COMMENTS_URL_SUFFIX)) {
                        continue;
                    }

                    // Strip trailing slash from feed paths. Some servers (e.g. cbsnews.com)
                    // return 404 for trailing-slash feed URLs but 200 without.
                    if (url.endsWith("/") && !url.endsWith("://")) {
                        url.chop(1);
                    }

                    feedsFound << url;
                }
            }
        }
    }

    return feedsFound;
}

void FeedDiscovery::onValidateFeeds()
{
    // Use the sorted feed URLs from onPageGrabberReady
    if (_sortedFeedURLs.isEmpty()) {
        reportError("No feeds to validate");
        return;
    }

    // Bulk parse all feed URLs
    feedParser->parse(_sortedFeedURLs);
}

void FeedDiscovery::onFeedParserReady()
{
    // Process all parsed feeds
    _discoveredFeeds.clear();

    QMap<QUrl, ParserInterface::ParseResult> results = feedParser->getResults();
    for (auto it = results.constBegin(); it != results.constEnd(); ++it) {
        QUrl feedURL = it.key();
        ParserInterface::ParseResult result = it.value();

        // Only include successfully parsed feeds that have items.
        if (result == ParserInterface::OK) {
            RawFeed* feed = feedParser->getFeed(feedURL);
            if (feed && !feed->items.isEmpty()) {
                DiscoveredFeed discovered;
                discovered.url = feedURL;
                discovered.feed = feed;  // Feed is owned by feedParser
                discovered.title = feed->title.isEmpty() ? feedURL.toString() : feed->title;
                discovered.content = "";  // Not storing raw content anymore
                discovered.validated = true;
                _discoveredFeeds.append(discovered);
            }
        }
    }

    // Check if we found any valid feeds.
    if (_discoveredFeeds.isEmpty()) {
        if (_probingCommonPaths) {
            // Common paths didn't turn up anything.
            qCDebug(logUtility) << "No valid feeds at common paths, trying sitemap";
            _probingCommonPaths = false;
            machine.setState(TRY_GOOGLE_NEWS_SITEMAP);
        } else {
            // Validation of HTML-discovered feeds failed.
            qCDebug(logUtility) << "No valid feeds found, trying common paths";
            machine.setState(TRY_COMMON_PATHS);
        }
        return;
    }

    _probingCommonPaths = false;

    // Set the first valid feed as the primary one (for backward compatibility)
    _feedURL = _discoveredFeeds.first().url;
    _feedResult = _discoveredFeeds.first().feed;

    // Emit done signal
    machine.setState(FEED_FOUND);
}

QStringList FeedDiscovery::commonFeedPaths()
{
    return {
        "/feed",
        "/rss",
        "/feed.xml",
        "/rss.xml",
        "/rss2.0.xml",
        "/atom.xml",
        "/index.xml",
        "/blog/feed"
    };
}

void FeedDiscovery::onTryCommonPaths()
{
    QUrl rootUrl;
    rootUrl.setScheme(_feedURL.scheme());
    rootUrl.setHost(_feedURL.host());
    if (_feedURL.port() != -1) {
        rootUrl.setPort(_feedURL.port());
    }

    QList<QUrl> probeURLs;
    for (const QString& path : commonFeedPaths()) {
        QUrl probeUrl = rootUrl;
        probeUrl.setPath(path);
        probeURLs.append(probeUrl);
    }

    qCDebug(logUtility) << "Probing" << probeURLs.count() << "common feed paths";
    _probingCommonPaths = true;
    feedParser->parse(probeURLs);
}

void FeedDiscovery::onTryGoogleNewsSitemap()
{
    // Extract site title from the already-fetched XHTML (if available).
    // The page content may be a redirect or error page, so validate the title.
    QString siteTitle;
    if (!_pageXHTML.isEmpty()) {
        PageMetadata meta = PageMetadataExtractor::extract(_pageXHTML);
        // Reject titles that look like HTTP status messages.
        if (!meta.title.isEmpty()
            && !meta.title.contains("Moved", Qt::CaseInsensitive)
            && !meta.title.contains("Forbidden", Qt::CaseInsensitive)
            && !meta.title.contains("Not Found", Qt::CaseInsensitive)
            && !meta.title.contains("Error", Qt::CaseInsensitive)) {
            siteTitle = meta.title;
        }
    }
    if (siteTitle.isEmpty()) {
        siteTitle = _feedURL.host();
    }

    qCDebug(logUtility) << "FeedDiscovery: trying sitemap for" << _feedURL
                        << "with title" << siteTitle;

    if (!newsSitemapSynthesizer) {
        newsSitemapSynthesizer = new GoogleNewsSitemapSynthesizer(this);
    }
    connect(newsSitemapSynthesizer, &GoogleNewsSitemapSynthesizer::done,
            this, &FeedDiscovery::onNewsSitemapDone, Qt::UniqueConnection);
    newsSitemapSynthesizer->synthesize(_feedURL, siteTitle);
}

void FeedDiscovery::onNewsSitemapDone()
{
    if (newsSitemapSynthesizer->hasError()) {
        reportError(newsSitemapSynthesizer->errorString());
        return;
    }

    RawFeed* synthFeed = newsSitemapSynthesizer->result();
    if (!synthFeed || synthFeed->items.isEmpty()) {
        reportError("No feed found");
        return;
    }

    // Set the primary feed result.
    _feedURL = synthFeed->url;
    _feedResult = synthFeed;

    // Add to discovered feeds list.
    DiscoveredFeed discovered;
    discovered.url = synthFeed->url;
    discovered.feed = synthFeed;
    discovered.title = synthFeed->title;
    discovered.validated = true;
    _discoveredFeeds.clear();
    _discoveredFeeds.append(discovered);

    machine.setState(FEED_FOUND);
}

void FeedDiscovery::reportError(QString errorString)
{
    _error = true;
    _errorString = errorString;

    machine.setState(FEED_ERROR);
}
