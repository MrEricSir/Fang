#include "BatchNewsParser.h"
#include "NewsParser.h"
#include "../utilities/FangLogging.h"

BatchNewsParser::BatchNewsParser(QObject *parent)
    : FangObject{parent}
{}

void BatchNewsParser::parse(const QList<QUrl> &urls)
{
    // Clear any existing parsers and results, in case this object is being reused. This will
    // also remove the feed data owned by these objects.
    for (ParserInterface* parser : parsers.values()) {
        delete parser;
    }
    parsers.clear();
    results.clear();

    // Clear feed map as the pointers are no longer valid (they were deleted above.)
    feeds.clear();

    // Set up parsers.
    for (const QUrl& url : urls) {
        // Skip this URL if we've already seen it.
        if (parsers.keys().contains(url)) {
            continue;
        }

        ParserInterface *parser = createParser();
        connect(parser, &ParserInterface::done, this, &BatchNewsParser::onParserDone);
        parser->parse(url);
        parsers[url] = parser;
    }
}

ParserInterface* BatchNewsParser::createParser()
{
    return new NewsParser(this);
}

void BatchNewsParser::onParserDone()
{
    ParserInterface* parser = qobject_cast<ParserInterface*>(sender());
    if (!parser) {
        qCWarning(logParser) << "BatchNewsParser: onParserDone called but sender is not a ParserInterface";
        return;
    }

    QUrl url = parser->getURL();
    if (!parsers.keys().contains(url)) {
        qCWarning(logParser) << "BatchNewsParser: URL returned but not found:" << url;
        return;
    }

    // Store result in our map.
    results[url] = parser->getResult();

    // Store feed if parser succeeded.
    if (parser->getResult() == ParserInterface::OK) {
        RawFeed* feed = parser->getFeed();
        if (feed) {
            // Store reference to the feed (owned by the parser)
            feeds[url] = feed;
        }
    }

    // Check if we're done.
    for (ParserInterface* p : parsers.values()) {
        if (p->getResult() == ParserInterface::IN_PROGRESS) {
            // Not done yet!
            return;
        }
    }

    // We're done!
    emit ready();
}

RawFeed* BatchNewsParser::getFeed(const QUrl& url)
{
    return feeds.value(url, nullptr);
}
