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
    parserUrls.clear();
    results.clear();

    // Clear feed map as the pointers are no longer valid (they were owned by parsers.)
    feeds.clear();

    // Set up parsers.
    for (const QUrl& url : urls) {
        // Skip this URL if we've already seen it.
        if (parsers.contains(url)) {
            continue;
        }

        auto parser = createParser();
        connect(parser.get(), &FeedSource::done, this, &BatchFeedFetcher::onParserDone);
        parserUrls.insert(parser.get(), url);
        parser->parse(url);
        parsers.insert(url, parser);
    }
}

std::shared_ptr<FeedSource> BatchFeedFetcher::createParser()
{
    return std::make_shared<FeedFetcher>();
}

void BatchFeedFetcher::onParserDone()
{
    FeedSource* parser = qobject_cast<FeedSource*>(sender());
    if (!parser) {
        qCWarning(logFeedDiscovery) << "BatchFeedFetcher: onParserDone called but sender is not a FeedSource";
        return;
    }

    // Look up the original request URL via the reverse index, since
    // parser->getURL() may differ from the request URL after redirects.
    QUrl requestUrl = parserUrls.value(parser);

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
        if (it.value()->getResult() == FeedFetchResult::InProgress) {
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
