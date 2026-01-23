#ifndef FEEDDISCOVERY_H
#define FEEDDISCOVERY_H

#include <QList>
#include <QObject>
#include <QString>
#include <QUrl>

#include "QSimpleStateMachine.h"
#include "../parser/ParserInterface.h"
#include "../parser/RawFeed.h"
#include "../parser/BatchNewsParser.h"
#include "../utilities/WebPageGrabber.h"
#include "../FangObject.h"

/**
 * @brief Attempts to match a user-submitted, URL like "bob.com" to an actual news feed.
 * This is done by massaging the URL so that Qt can fetch a document.  If that document is
 * a web page, we search for a link to the RSS or Atom feed in the HTML.  Then we check
 * that document to see if it's an RSS feed.
 *
 * HTTP and HTML redirects are handled.
 * 
 * State machine diagram:
 * 
 * CHECK_FEED
 *     |  \- ERROR
 *     |
 *  TRY_FEED
 *     |  \- FEED_FOUND
 *     |
 * WEB_GRABBER
 *     |  \- ERROR
 *     |
 * TRY_FEED_AGAIN
 *     |  \- ERROR
 *     |
 *  FEED_FOUND
 */
class FeedDiscovery : public FangObject
{
    Q_OBJECT
    
private:

    enum FeedDiscoveryState {
        CHECK_FEED,
        TRY_FEED,
        WEB_GRABBER,
        VALIDATE_FEEDS,  // Bulk feed validation
        FEED_FOUND,
        FEED_ERROR
    };
    
public:
    /**
     * @brief Structure to hold a discovered feed with metadata
     */
    struct DiscoveredFeed {
        QUrl url;              // Feed URL
        QString title;         // Feed title (from parsed feed or URL)
        QString content;       // Downloaded feed content (for lazy parsing)
        RawFeed* feed;         // Parsed feed (nullptr if not yet parsed)
        bool validated;        // Has this feed been successfully parsed?

        DiscoveredFeed() : feed(nullptr), validated(false) {}
    };

    explicit FeedDiscovery(QObject *parent = nullptr,
                          ParserInterface* firstParser = nullptr,
                          ParserInterface* secondParser = nullptr,
                          WebPageGrabber* pageGrabber = nullptr,
                          BatchNewsParser* feedParser = nullptr);
    virtual ~FeedDiscovery();

    /**
     * @return After done(), this returns true if there was an error.
     */
    bool error() { return _error; }

    /**
     * @return After done(), this returns the error string, if there was an error.
     */
    QString errorString() { return _errorString; }

    /**
     * @return The feed URL, or an empty URL if there was an error.
     *         For backward compatibility: returns first validated feed.
     */
    QUrl feedURL() { return _error ? QUrl("") : _feedURL; }

    /**
     * @return The raw feed or nullptr if there was an error.
     *         For backward compatibility: returns first validated feed.
     */
    RawFeed* feedResult() { return _error ? nullptr : _feedResult; }

    /**
     * @return List of all discovered feeds (may be empty if error or single-feed mode)
     */
    QList<DiscoveredFeed> discoveredFeeds() const { return _discoveredFeeds; }

    /**
     * @return Number of feeds discovered (0 = error or single-feed mode, 1+ = multi-feed)
     */
    int feedCount() const { return _discoveredFeeds.count(); }
    
signals:
    
    /**
     * @brief Completion signal. Check for error; if false, get feedURL()
     * @param feedDiscovery
     */
    void done(FeedDiscovery* feedDiscovery);
    
public slots:

    /**
     * @brief Call this with a feed URL to check to get started!  Wait for done()
     * @param sURL
     */
    virtual void checkFeed(QString sURL);

    /**
     * @brief Try to find RSS and Atom feed(s), if available.
     *        External use: Intended for use in unit tests.
     * @param document
     */
    QList<QString> parseFeedsFromXHTML(const QString& document);
    
private slots:

    // State change slots:
    void onTryFeed();
    void onFeedFound();
    void onWebGrabber();
    void onValidateFeeds();  // Bulk feed validation
    void onError();

    // Parser/BulkParser slots:
    void onFirstParseDone();
    void onFeedParserReady();

    // WebPageGrabber slots:
    void onPageGrabberReady(WebPageGrabber* grabber, QString* document);

protected:
    ParserInterface* parserFirstTry;
    WebPageGrabber* pageGrabber;            // For fetching HTML pages
    BatchNewsParser* feedParser;            // For bulk feed parsing

private:
    // Sets the error flag, error string, and triggers the ERROR state.
    void reportError(QString errorString);

    QSimpleStateMachine machine;

    QUrl _feedURL;
    bool _error;
    QString _errorString;

    RawFeed* _feedResult;

    // Multi-feed discovery state
    QList<DiscoveredFeed> _discoveredFeeds;  // All discovered feeds
    QList<QUrl> _sortedFeedURLs;             // Feed URLs to validate (sorted by path length)
};

#endif // FEEDDISCOVERY_H
