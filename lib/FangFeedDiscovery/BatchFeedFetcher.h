#ifndef BATCHFEEDFETCHER_H
#define BATCHFEEDFETCHER_H

#include <memory>

#include <QHash>
#include <QMap>
#include <QUrl>

#include "FeedSource.h"
#include "RawFeed.h"

/*!
 * \brief The BatchFeedFetcher is a wrapper for FeedFetcher that handles multiple feeds.
 */
class BatchFeedFetcher : public QObject
{
    Q_OBJECT
public:
    explicit BatchFeedFetcher(QObject *parent = nullptr);

    // Parses a list of feed URLs and emits ready() when all are complete.
    virtual void parse(const QList<QUrl> &urls);

    // Map of parse results
    virtual QMap<QUrl, FeedFetchResult> getResults() { return results; }

    // Get parsed feed for a specific URL (nullptr if parse failed)
    virtual std::shared_ptr<RawFeed> getFeed(const QUrl& url);

signals:
    void ready();

protected:
    // Virtual method for creating parsers; can be overridden for unit tests.
    virtual std::shared_ptr<FeedSource> createParser();

    // Called whenever a parser is done.
    void onParserDone();

    // Parsers that are in flight.
    QMap<QUrl, std::shared_ptr<FeedSource>> parsers;

    // Reverse index: parser pointer -> original request URL.
    QHash<FeedSource*, QUrl> parserUrls;

    // Results of parsing per-URL.
    QMap<QUrl, FeedFetchResult> results;

    // Parsed feeds per-URL.
    QMap<QUrl, std::shared_ptr<RawFeed>> feeds;
};

#endif // BATCHFEEDFETCHER_H
