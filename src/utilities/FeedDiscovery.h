#ifndef FEEDDISCOVERY_H
#define FEEDDISCOVERY_H

#include <QObject>
#include <QString>
#include <QUrl>

#include "SimpleStateMachine.h"
#include "../parser/NewsParser.h"
#include "../parser/RawFeed.h"
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
        TRY_FEED_AGAIN,
        FEED_FOUND,
        FEED_ERROR
    };
    
public:
    explicit FeedDiscovery(QObject *parent = nullptr);
    
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
     */
    QUrl feedURL() { return _error ? QUrl("") : _feedURL; }
    
    /**
     * @return The raw feed or nullptr if there was an error.
     */
    RawFeed* feedResult() { return _error ? nullptr : _feedResult; }

    /**
     * @return String representation of RSS URL, if found.
     */
    QString getRssURL() { return rssURL; }

    /**
     * @return String representation of Atom URL, if found.
     */
    QString getAtomURL() { return atomURL; }
    
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
    void checkFeed(QString sURL);

    /**
     * @brief Try to find RSS and Atom feed, if available.
     *        External use: Intended for use in unit tests.
     * @param document
     */
    void findFeeds(const QString& document);
    
private slots:
    
    // State change slots:
    void onTryFeed();
    void onFeedFound();
    void onWebGrabber();
    void onTryFeedAgain();
    void onError();
    
    // Parser slots:
    void onFirstParseDone();
    void onSecondParseDone();
    
    // WebPageGrabber slots.
    void onPageGrabberReady(QString* document);
    
private:
    // Sets the error flag, error string, and triggers the ERROR state.
    void reportError(QString errorString);
    
    SimpleStateMachine machine;
    
    QUrl _feedURL;
    bool _error;
    QString _errorString;

    QString rssURL;
    QString atomURL;
    
    NewsParser parserFirstTry;
    NewsParser parserSecondTry;
    
    WebPageGrabber pageGrabber;
    
    RawFeed* _feedResult;
};

#endif // FEEDDISCOVERY_H
