#ifndef FEEDDISCOVERY_H
#define FEEDDISCOVERY_H

#include <QObject>
#include <QString>
#include <QUrl>

#include "SimpleStateMachine.h"
#include "../parser/BackgroundParser.h"
#include "../utilities/WebPageGrabber.h"

/**
 * @brief Checks a feed.
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
class FeedDiscovery : public QObject
{
    Q_OBJECT
    
private:
    
    enum FeedDiscoveryState {
        CHECK_FEED,
        TRY_FEED,
        WEB_GRABBER,
        TRY_FEED_AGAIN,
        FEED_FOUND,
        ERROR
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
    
    QUrl feedURL() { return _error ? QUrl("") : _feedURL; }
    
signals:
    
    /**
     * @brief Completion signal. Check for error; if false, get feedURL()
     * @param feedDiscovery
     */
    void done(FeedDiscovery* feedDiscovery);
    
public slots:
    
    /**
     * @brief Call this with a feed URL to check to get started!  Wait for done()
     * @param url
     */
    void checkFeed(QUrl url);
    
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
    void onPageGrabberReady(QWebPage* page);
    
private:
    // Sets the error flag, error string, and triggers the ERROR state.
    void reportError(QString errorString);
    
    SimpleStateMachine machine;
    
    QUrl _feedURL;
    bool _error;
    QString _errorString;
    
    BackgroundParser parserFirstTry;
    BackgroundParser parserSecondTry;
    
    WebPageGrabber pageGrabber;
};

#endif // FEEDDISCOVERY_H
