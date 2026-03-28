#ifndef MOCKBATCHFEEDFETCHER_H
#define MOCKBATCHFEEDFETCHER_H

#include "BatchFeedFetcher.h"
#include "RawFeed.h"
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

    void addResponse(const QUrl& url, FeedFetchResult result, std::shared_ptr<RawFeed> feed = nullptr)
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
                cachedResults[url] = FeedFetchResult::NetworkError;
            }
        }

        // Emit ready signal asynchronously to simulate real behavior
        QTimer::singleShot(0, this, &MockBatchFeedFetcher::ready);
    }

    QMap<QUrl, FeedFetchResult> getResults() override
    {
        return cachedResults;
    }

    std::shared_ptr<RawFeed> getFeed(const QUrl& url) override
    {
        return mockFeeds.value(url, nullptr);
    }

private:
    QMap<QUrl, FeedFetchResult> mockResults;
    QMap<QUrl, std::shared_ptr<RawFeed>> mockFeeds;
    QMap<QUrl, FeedFetchResult> cachedResults;
};

#endif // MOCKBATCHFEEDFETCHER_H
