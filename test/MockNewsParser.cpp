#include "MockNewsParser.h"
#include <QTimer>

MockNewsParser::MockNewsParser(QObject *parent)
    : ParserInterface(parent),
      result(IN_PROGRESS),
      feed(nullptr),
      url(),
      romCache(false)
{
}

MockNewsParser::~MockNewsParser()
{
    delete feed;
}

void MockNewsParser::setResult(ParseResult result)
{
    this->result = result;
}

void MockNewsParser::setFeed(RawFeed* feed)
{
    if (this->feed != feed) {
        delete this->feed;
    }
    this->feed = feed;
}

void MockNewsParser::setURL(const QUrl& url)
{
    this->url = url;
}

void MockNewsParser::setFromCache(bool cached)
{
    romCache = cached;
}

void MockNewsParser::reset()
{
    result = OK;
    delete feed;
    feed = nullptr;
    url = QUrl();
    romCache = false;
}

void MockNewsParser::parse(const QUrl& url, bool noParseIfCached)
{
    Q_UNUSED(noParseIfCached);

    // If URL wasn't pre-configured, use the one passed in
    if (this->url.isEmpty()) {
        this->url = url;
    }

    // Emit done() signal asynchronously to simulate real parser behavior
    QTimer::singleShot(0, this, &MockNewsParser::done);
}

ParserInterface::ParseResult MockNewsParser::getResult()
{
    return result;
}

RawFeed* MockNewsParser::getFeed()
{
    return feed;
}

QUrl MockNewsParser::getURL()
{
    return url;
}

bool MockNewsParser::isFromCache()
{
    return romCache;
}
