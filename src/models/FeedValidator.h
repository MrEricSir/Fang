#ifndef FEEDVALIDATOR_H
#define FEEDVALIDATOR_H

#include <QDeclarativeItem>
#include <QObject>
#include <QUrl>
#include <QWebPage>

#include "../parser/Parser.h"
#include "FeedItem.h"
#include "../utilities/WebPageGrabber.h"

class FeedValidator : public QDeclarativeItem 
{
    Q_OBJECT
    Q_DISABLE_COPY(FeedValidator)
    
    Q_PROPERTY(bool validating READ validating NOTIFY validatingChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString siteTitle READ siteTitle WRITE setSiteTitle NOTIFY siteTitleChanged)
    Q_PROPERTY(QString siteImageURL READ siteImageURL WRITE setSiteImageURL NOTIFY siteImageURLChanged)
    
public:
    explicit FeedValidator(QDeclarativeItem *parent = 0);
    virtual ~FeedValidator() {}
    
    // Performs the URL check.
    // Set the URL, then call this and wait for validationComplete().
    Q_INVOKABLE void check();
    
    // If check was OK, call this to add the feed!
    Q_INVOKABLE void addFeed();
    
    // HAHA this class has a "secret" property; it can also remove feeds. :)
    Q_INVOKABLE void removeFeed(FeedItem* feed);
    
    inline bool validating() { return _validating; }
    inline QString url() { return _url; }
    inline QString siteTitle() { return _siteTitle; }
    inline QString siteImageURL() { return _siteImageURL; }
    void setUrl(QString url);
    void setSiteTitle(QString title);
    void setSiteImageURL(QString url);
    
signals:
    void urlChanged(QString url);
    void validatingChanged(bool validating);
    void siteTitleChanged(QString title);
    void siteImageURLChanged(QString url);
    void validationComplete(bool result, QString errorString);
    
public slots:
    
private slots:
    void doParse(const QUrl& url);
    
    void onFeedFinished();
    void onPageGrabberReady(QWebPage* page);
    void handleCompletion();
    
private:
    Parser* parser;
    bool _validating;
    QWebPage* webPage;
    QUrl embeddedFeedURL;
    QString _url;
    QString _siteTitle;
    QString _siteImageURL;
    WebPageGrabber pageGrabber;
    Parser::ParseResult result;
    QUrl location;
    bool pageGrabberDone;
};

QML_DECLARE_TYPE(FeedValidator)

#endif // FEEDVALIDATOR_H
