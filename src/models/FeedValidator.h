#ifndef FEEDVALIDATOR_H
#define FEEDVALIDATOR_H

#include <QQuickItem>
#include <QObject>
#include <QUrl>

#include "FeedItem.h"
#include "../utilities/FeedDiscovery.h"

/**
 * @brief Initially this class was for validating feed URLs, but has now outgrown that to handle
 *        adding and removing feeds and folders.
 */
class FeedValidator : public QQuickItem 
{
    Q_OBJECT
    Q_DISABLE_COPY(FeedValidator)
    
    Q_PROPERTY(bool validating READ validating NOTIFY validatingChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString siteTitle READ siteTitle WRITE setSiteTitle NOTIFY siteTitleChanged)
    Q_PROPERTY(QString siteImageURL READ siteImageURL WRITE setSiteImageURL NOTIFY siteImageURLChanged)
    
public:
    explicit FeedValidator(QQuickItem *parent = nullptr);
    virtual ~FeedValidator() {}
    
    inline bool validating() { return _validating; }
    inline QString url() { return _url; }
    inline QString siteTitle() { return _siteTitle; }
    inline QString siteImageURL() { return _siteImageURL; }
    void setUrl(QString url);
    void setSiteTitle(QString title);
    void setSiteImageURL(QString url);

public slots:
    // Performs the URL check.
    // Set the URL, then call this and wait for validationComplete().
    void check();

    // If check was OK, call this to add the feed!
    void addFeed();

    // Remove an existing feed.
    void removeFeed(FeedItem* feed);

    // Insert a folder at the given index and reparent the next two items.
    int insertFolder(int newIndex);
    
signals:
    void urlChanged(QString url);
    void validatingChanged(bool validating);
    void siteTitleChanged(QString title);
    void siteImageURLChanged(QString url);
    void validationComplete(bool result, QString errorString);
    
public slots:
    
private slots:
    // Feed discovered!  Yay!
    void onFeedDiscoveryDone(FeedDiscovery *discovery);
    
private:
    bool _validating;
    QString _url;
    QString _siteTitle;
    QString _siteImageURL;
    
    FeedDiscovery feedDiscovery;
};

QML_DECLARE_TYPE(FeedValidator)

#endif // FEEDVALIDATOR_H
