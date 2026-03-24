#ifndef MOCKFEEDSOURCE_H
#define MOCKFEEDSOURCE_H

#include <QObject>
#include <QTimer>
#include <QUrl>
#include "../src/parser/FeedSource.h"
#include "../src/parser/RawFeed.h"

/**
 * @brief Mock version of FeedSource
 *
 * Allows pre-configuring the parse result, feed data, and URL to test code that depends
 * on FeedSource without network access.
 */
class MockFeedSource : public FeedSource
{
    Q_OBJECT

public:
    explicit MockFeedSource(QObject *parent = nullptr);
    virtual ~MockFeedSource() override;

    // Mock behavior
    void setResult(ParseResult result);
    void setFeed(RawFeed* feed);  // Takes ownership
    void setURL(const QUrl& url);
    void setFromCache(bool cached);

    // Reset state
    void reset();

    // FeedSource implementation
    virtual void parse(const QUrl& url, bool noParseIfCached = false,
                       const QString& ifNoneMatch = QString(),
                       const QString& ifModifiedSince = QString()) override;
    virtual ParseResult getResult() override;
    virtual RawFeed* getFeed() override;
    virtual QUrl getURL() override;
    virtual bool isFromCache() override;

private:
    ParseResult result;
    RawFeed* feed;
    QUrl url;
    bool romCache;
};

#endif // MOCKFEEDSOURCE_H
