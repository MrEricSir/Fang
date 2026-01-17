#include "BatchNewsParser.h"
#include "NewsParser.h"
#include <QDebug>

BatchNewsParser::BatchNewsParser(QObject *parent)
    : FangObject{parent}
{}

void BatchNewsParser::parse(const QList<QUrl> &urls)
{
    // Clear any existing parsers and results, in case this object is being reused.
    parsers.clear();
    results.clear();

    // Clean up old feeds
    for (RawFeed* feed : feeds.values()) {
        delete feed;
    }
    feeds.clear();

    // Set up parsers.
    for (const QUrl& url : urls) {
        // Skip this URL if we've already seen it.
        if (parsers.keys().contains(url)) {
            continue;
        }

        ParserInterface *parser = new NewsParser(this);
        connect(parser, &ParserInterface::done, this, &BatchNewsParser::onParserDone);
        parser->parse(url);
        parsers[url] = parser;
    }
}

void BatchNewsParser::onParserDone()
{
    ParserInterface* parser = qobject_cast<ParserInterface*>(sender());
    if (!parser) {
        qWarning() << "BatchNewsParser: onParserDone called but sender is not a ParserInterface";
        return;
    }

    QUrl url = parser->getURL();
    if (!parsers.keys().contains(url)) {
        qWarning() << "BatchNewsParser: URL returned but not found:" << url;
        return;
    }

    // Store result
    results[url] = parser->getResult();

    // Store feed if parsing succeeded
    if (parser->getResult() == ParserInterface::OK) {
        RawFeed* feed = parser->getFeed();
        if (feed) {
            // Create a copy of the feed for storage
            // The parser owns the original, we need our own copy
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
