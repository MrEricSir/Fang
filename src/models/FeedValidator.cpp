#include "FeedValidator.h"
#include "../FangApp.h"
#include "../utilities/Utilities.h"
#include "../utilities/NetworkUtilities.h"

FeedValidator::FeedValidator(QQuickItem *parent) :
    QQuickItem(parent),
    _url(""),
    _siteTitle(""),
    _siteImageURL("")
{
    connect(&feedDiscovery, SIGNAL(done(FeedDiscovery*)), this, SLOT(onFeedDiscoveryDone(FeedDiscovery*)));
}

void FeedValidator::check()
{
    // Signal start.
    _validating = true;
    emit validatingChanged(_validating);
    
    // DO IT.
    feedDiscovery.checkFeed(_url);
}

void FeedValidator::addFeed()
{
    FangApp::instance()->addFeed(feedDiscovery.feedURL(), feedDiscovery.feedResult());
}

void FeedValidator::removeFeed(FeedItem *feed)
{
    FangApp::instance()->removeFeed(feed);
}

void FeedValidator::setUrl(QString url)
{
    if (url == _url)
        return;
    
    _url = url;
    emit urlChanged(_url);
}

void FeedValidator::setSiteTitle(QString title)
{
    if (title == _siteTitle)
        return;
    
    _siteTitle = title;
    emit siteTitleChanged(_siteTitle);
}

void FeedValidator::setSiteImageURL(QString url)
{
    if (url == _siteImageURL)
        return;
    
    _siteImageURL = url;
    emit siteImageURLChanged(_siteImageURL);
}

void FeedValidator::onFeedDiscoveryDone(FeedDiscovery* discovery)
{
    Q_UNUSED(discovery);
    
    // Validation is done.
    _validating = false;
    emit validatingChanged(_validating);
    
    // Completion!
    emit validationComplete(!feedDiscovery.error(), feedDiscovery.errorString());
}

