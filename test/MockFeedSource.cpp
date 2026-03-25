#include "MockFeedSource.h"
#include <QTimer>

MockFeedSource::MockFeedSource(QObject *parent)
    : FeedSource(parent),
      result(FeedFetchResult::InProgress),
      feed(nullptr),
      url(),
      romCache(false)
{
}

MockFeedSource::~MockFeedSource()
{
}

void MockFeedSource::setResult(FeedFetchResult result)
{
    this->result = result;
}

void MockFeedSource::setFeed(std::shared_ptr<RawFeed> feed)
{
    this->feed = feed;
}

void MockFeedSource::setURL(const QUrl& url)
{
    this->url = url;
}

void MockFeedSource::setFromCache(bool cached)
{
    romCache = cached;
}

void MockFeedSource::reset()
{
    result = FeedFetchResult::OK;
    feed.reset();
    url = QUrl();
    romCache = false;
}

void MockFeedSource::parse(const QUrl& url, bool noParseIfCached,
                           const QString& ifNoneMatch, const QString& ifModifiedSince)
{
    Q_UNUSED(noParseIfCached);
    Q_UNUSED(ifNoneMatch);
    Q_UNUSED(ifModifiedSince);

    // If URL wasn't pre-configured, use the one passed in
    if (this->url.isEmpty()) {
        this->url = url;
    }

    // Emit done() signal asynchronously to simulate real parser behavior
    QTimer::singleShot(0, this, &MockFeedSource::done);
}

FeedFetchResult MockFeedSource::getResult()
{
    return result;
}

std::shared_ptr<RawFeed> MockFeedSource::getFeed()
{
    return feed;
}

QUrl MockFeedSource::getURL()
{
    return url;
}

bool MockFeedSource::isFromCache()
{
    return romCache;
}
