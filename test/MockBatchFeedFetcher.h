#ifndef MOCKBATCHFEEDFETCHER_H
#define MOCKBATCHFEEDFETCHER_H

#include "../src/parser/BatchFeedFetcher.h"
#include "../src/parser/RawFeed.h"
#include <QTimer>
#include <QMap>

/**
 * @brief Mock BatchFeedFetcher for testing without making actual network requests
 */
class MockBatchFeedFetcher : public BatchFeedFetcher
{
    Q_OBJECT

public:
    explicit MockBatchFeedFetcher(QObject* parent = nullptr)
        : BatchFeedFetcher(parent)
    {
    }

    void addResponse(const QUrl& url, FeedSource::ParseResult result, RawFeed* feed = nullptr)
    {
        mockResults[url] = result;
        if (feed) {
            mockFeeds[url] = feed;
        }
    }

    void parse(const QList<QUrl> &urls) override
    {
        cachedResults.clear();

        // Populate results based on mock data
        for (const QUrl& url : urls) {
            if (mockResults.contains(url)) {
                cachedResults[url] = mockResults[url];
            } else {
                // Default to network error if not configured
                cachedResults[url] = FeedSource::NETWORK_ERROR;
            }
        }

        // Emit ready signal asynchronously to simulate real behavior
        QTimer::singleShot(0, this, &MockBatchFeedFetcher::ready);
    }

    QMap<QUrl, FeedSource::ParseResult> getResults() override
    {
        return cachedResults;
    }

    RawFeed* getFeed(const QUrl& url) override
    {
        return mockFeeds.value(url, nullptr);
    }

private:
    QMap<QUrl, FeedSource::ParseResult> mockResults;
    QMap<QUrl, RawFeed*> mockFeeds;
    QMap<QUrl, FeedSource::ParseResult> cachedResults;
};

#endif // MOCKBATCHFEEDFETCHER_H
