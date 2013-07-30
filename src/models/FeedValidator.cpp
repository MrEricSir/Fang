#include "FeedValidator.h"
#include "../FangApp.h"

FeedValidator::FeedValidator(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    parser(),
    _validating(false),
    _url(""),
    _siteTitle(""),
    _siteImageURL("")
{
    QObject::connect(&parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
}

void FeedValidator::check()
{
    // Signal start.
    _validating = true;
    emit validatingChanged(_validating);
    
    // Parser the URL.  Will call onFeedFinished when complete.
    parser.parse(QUrl(_url));
}

void FeedValidator::addFeed()
{
    // Assume check passed.
    // TODO: add sanity check here.
    
    FangApp::instance()->addFeed(QUrl(_url), QUrl(_siteImageURL), _siteTitle);
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

void FeedValidator::onFeedFinished()
{
    // Signal completion.
    _validating = false;
    emit validatingChanged(_validating);
    
    // Get result.
    Parser::ParseResult result = parser.getResult();
    RawFeed* feed = parser.getFeed();
    
    // Figure out if we're good or not.
    if (result == Parser::OK) {
        // YAY!
        _siteTitle = feed->title;
        //_siteImageURL = feed-> // TODO: add this to the parser
        emit validationComplete(true, "");
    } else {
        // BOO!  Error.
        if (result == Parser::NETWORK_ERROR)
            emit validationComplete(false, "Could not access URL.");
        else if (result == Parser::PARSE_ERROR)
            emit validationComplete(false, "Error parsing feed.");
        else
            Q_ASSERT(false); // We added an error but forgot to handle it here.
    }
}
