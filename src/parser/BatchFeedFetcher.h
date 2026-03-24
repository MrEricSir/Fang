#ifndef BATCHFEEDFETCHER_H
#define BATCHFEEDFETCHER_H

#include <map>
#include <memory>

#include <QMap>
#include <QUrl>

#include "../FangObject.h"
#include "FeedSource.h"
#include "RawFeed.h"

/*!
 * \brief The BatchFeedFetcher is a wrapper for FeedFetcher that handles multiple feeds.
 */
class BatchFeedFetcher : public FangObject
{
    Q_OBJECT
public:
    explicit BatchFeedFetcher(QObject *parent = nullptr);

    // Parses a list of feed URLs and emits ready() when all are complete.
    virtual void parse(const QList<QUrl> &urls);

    // Map of parse results
    virtual QMap<QUrl, FeedSource::ParseResult> getResults() { return results; }

    // Get parsed feed for a specific URL (nullptr if parse failed)
    virtual RawFeed* getFeed(const QUrl& url);

signals:
    void ready();

protected:
    // Virtual method for creating parsers; can be overridden for unit tests.
    virtual std::unique_ptr<FeedSource> createParser();

    // Called whenever a parser is done.
    void onParserDone();

    // Parsers that are in flight.
    std::map<QUrl, std::unique_ptr<FeedSource>> parsers;

    // Results of parsing per-URL.
    QMap<QUrl, FeedSource::ParseResult> results;

    // Parsed feeds per-URL (references to feeds owned by parsers).
    QMap<QUrl, RawFeed*> feeds;
};

#endif // BATCHFEEDFETCHER_H
