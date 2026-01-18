#ifndef MOCKBATCHNEWSPARSER_H
#define MOCKBATCHNEWSPARSER_H

#include "../src/parser/BatchNewsParser.h"
#include "../src/parser/RawFeed.h"
#include <QTimer>
#include <QMap>

/**
 * @brief Mock BatchNewsParser for testing without making actual network requests
 */
class MockBatchNewsParser : public BatchNewsParser
{
    Q_OBJECT

public:
    explicit MockBatchNewsParser(QObject* parent = nullptr)
        : BatchNewsParser(parent)
    {
    }

    void addResponse(const QUrl& url, ParserInterface::ParseResult result, RawFeed* feed = nullptr)
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
                cachedResults[url] = ParserInterface::NETWORK_ERROR;
            }
        }

        // Emit ready signal asynchronously to simulate real behavior
        QTimer::singleShot(0, this, &MockBatchNewsParser::ready);
    }

    QMap<QUrl, ParserInterface::ParseResult> getResults() override
    {
        return cachedResults;
    }

    RawFeed* getFeed(const QUrl& url) override
    {
        return mockFeeds.value(url, nullptr);
    }

private:
    QMap<QUrl, ParserInterface::ParseResult> mockResults;
    QMap<QUrl, RawFeed*> mockFeeds;
    QMap<QUrl, ParserInterface::ParseResult> cachedResults;
};

#endif // MOCKBATCHNEWSPARSER_H
