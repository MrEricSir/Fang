#include "BatchNewsParser.h"
#include "NewsParser.h"
#include "../utilities/FangLogging.h"

BatchNewsParser::BatchNewsParser(QObject *parent)
    : FangObject{parent}
{}

void BatchNewsParser::parse(const QList<QUrl> &urls)
{
    // Clear any existing parsers and results, in case this object is being reused.
    parsers.clear();
    results.clear();

    // Clear feed map as the pointers are no longer valid (they were owned by parsers.)
    feeds.clear();

    // Set up parsers.
    for (const QUrl& url : urls) {
        // Skip this URL if we've already seen it.
        if (parsers.count(url) > 0) {
            continue;
        }

        auto parser = createParser();
        connect(parser.get(), &ParserInterface::done, this, &BatchNewsParser::onParserDone);
        parser->parse(url);
        parsers[url] = std::move(parser);
    }
}

std::unique_ptr<ParserInterface> BatchNewsParser::createParser()
{
    return std::make_unique<NewsParser>();
}

void BatchNewsParser::onParserDone()
{
    ParserInterface* parser = qobject_cast<ParserInterface*>(sender());
    if (!parser) {
        qCWarning(logParser) << "BatchNewsParser: onParserDone called but sender is not a ParserInterface";
        return;
    }

    // Find the original request URL by matching the parser pointer, since
    // parser->getURL() may differ from the request URL after redirects.
    QUrl requestUrl;
    for (auto it = parsers.cbegin(); it != parsers.cend(); ++it) {
        if (it->second.get() == parser) {
            requestUrl = it->first;
            break;
        }
    }

    if (requestUrl.isEmpty()) {
        qCWarning(logParser) << "BatchNewsParser: parser finished but not found in map:" << parser->getURL();
        return;
    }

    // Store result under the original request URL.
    results[requestUrl] = parser->getResult();

    // Store feed if parser succeeded.
    if (parser->getResult() == ParserInterface::OK) {
        RawFeed* feed = parser->getFeed();
        if (feed) {
            // Store reference to the feed (owned by the parser)
            feeds[requestUrl] = feed;
        }
    }

    // Check if we're done.
    for (auto it = parsers.cbegin(); it != parsers.cend(); ++it) {
        if (it->second->getResult() == ParserInterface::IN_PROGRESS) {
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
