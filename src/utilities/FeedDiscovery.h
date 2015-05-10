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
 * This is done by massaging the URL, then attempting to parse it.  If that fails we 
 * treat it as a web page and look for a feed URL embedded in it, then try to parse that.
 * 
 * Both the feed and final URL are returned if the error flag is not set.
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
    explicit FeedDiscovery(QObject *parent = 0);
    
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
     * @return The raw feed or null if there was an error.
     */
    RawFeed* feedResult() { return _error ? NULL : _feedResult; }
    
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
    void onPageGrabberReady(QDomDocument* page);

    // Try to find RSS and Atom feed, if available.
    void traveseXML(const QDomNode& node);
    
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
