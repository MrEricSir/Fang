#include "BatchFeedFetcher.h"
#include "FeedFetcher.h"
#include "FeedDiscoveryLogging.h"

BatchFeedFetcher::BatchFeedFetcher(QObject *parent)
    : QObject{parent}
{}

void BatchFeedFetcher::parse(const QList<QUrl> &urls)
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
        connect(parser.get(), &FeedSource::done, this, &BatchFeedFetcher::onParserDone);
        parser->parse(url);
        parsers[url] = std::move(parser);
    }
}

std::unique_ptr<FeedSource> BatchFeedFetcher::createParser()
{
    return std::make_unique<FeedFetcher>();
}

void BatchFeedFetcher::onParserDone()
{
    FeedSource* parser = qobject_cast<FeedSource*>(sender());
    if (!parser) {
        qCWarning(logFeedDiscovery) << "BatchFeedFetcher: onParserDone called but sender is not a FeedSource";
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
        qCWarning(logFeedDiscovery) << "BatchFeedFetcher: parser finished but not found in map:" << parser->getURL();
        return;
    }

    // Store result under the original request URL.
    results[requestUrl] = parser->getResult();

    // Store feed if parser succeeded.
    if (parser->getResult() == FeedFetchResult::OK) {
        auto feed = parser->getFeed();
        if (feed) {
            feeds[requestUrl] = feed;
        }
    }

    // Check if we're done.
    for (auto it = parsers.cbegin(); it != parsers.cend(); ++it) {
        if (it->second->getResult() == FeedFetchResult::InProgress) {
            // Not done yet!
            return;
        }
    }

    // We're done!
    emit ready();
}

std::shared_ptr<RawFeed> BatchFeedFetcher::getFeed(const QUrl& url)
{
    return feeds.value(url, nullptr);
}
