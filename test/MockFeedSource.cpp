#include "MockFeedSource.h"
#include <QTimer>

MockFeedSource::MockFeedSource(QObject *parent)
    : FeedSource(parent),
      result(IN_PROGRESS),
      feed(nullptr),
      url(),
      romCache(false)
{
}

MockFeedSource::~MockFeedSource()
{
    delete feed;
}

void MockFeedSource::setResult(ParseResult result)
{
    this->result = result;
}

void MockFeedSource::setFeed(RawFeed* feed)
{
    if (this->feed != feed) {
        delete this->feed;
    }
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
    result = OK;
    delete feed;
    feed = nullptr;
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

FeedSource::ParseResult MockFeedSource::getResult()
{
    return result;
}

RawFeed* MockFeedSource::getFeed()
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
