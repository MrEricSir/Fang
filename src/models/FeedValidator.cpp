#include "FeedValidator.h"
#include "../FangApp.h"
#include "../utilities/Utilities.h"

FeedValidator::FeedValidator(QQuickItem *parent) :
    QQuickItem(parent),
    _validating(false),
    _url(""),
    _siteTitle(""),
    _siteImageURL("")
{
    connect(&feedDiscovery, &FeedDiscovery::done, this, &FeedValidator::onFeedDiscoveryDone);
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
    RawFeed* feed = feedDiscovery.feedResult();
    feed->title = siteTitle();
    FangApp::instance()->addFeed(feedDiscovery.feedURL(), feed, true);
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

int FeedValidator::insertFolder(int newIndex)
{
    // qDebug() << "FeedValidator::insertFolder at: " << newIndex;
    return FangApp::instance()->insertFolder(newIndex);
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
    
    // Set the TITLE.
    if (feedDiscovery.feedResult()) {
        setSiteTitle(feedDiscovery.feedResult()->title);
    }
    
    // Completion!
    emit validationComplete(!feedDiscovery.error(), feedDiscovery.errorString());
}

