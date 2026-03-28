#ifndef MOCKFEEDSOURCE_H
#define MOCKFEEDSOURCE_H

#include <memory>

#include <QObject>
#include <QTimer>
#include <QUrl>
#include "FeedSource.h"
#include "RawFeed.h"

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
    void setResult(FeedFetchResult result);
    void setFeed(std::shared_ptr<RawFeed> feed);
    void setURL(const QUrl& url);

    // Reset state
    void reset();

    // FeedSource implementation
    virtual void parse(const QUrl& url,
                       const QString& ifNoneMatch = QString(),
                       const QString& ifModifiedSince = QString()) override;
    virtual FeedFetchResult getResult() override;
    virtual std::shared_ptr<RawFeed> getFeed() override;
    virtual QUrl getURL() override;

private:
    FeedFetchResult result;
    std::shared_ptr<RawFeed> feed;
    QUrl url;
};

#endif // MOCKFEEDSOURCE_H
