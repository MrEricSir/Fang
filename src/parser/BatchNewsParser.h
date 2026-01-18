#ifndef BATCHNEWSPARSER_H
#define BATCHNEWSPARSER_H

#include <QMap>
#include <QUrl>

#include "../FangObject.h"
#include "ParserInterface.h"
#include "RawFeed.h"

/*!
 * \brief The BatchNewsParser is a wrapper for NewsParser that handles multiple feeds.
 */
class BatchNewsParser : public FangObject
{
    Q_OBJECT
public:
    explicit BatchNewsParser(QObject *parent = nullptr);

    // Parses a list of feed URLs and emits ready() when all are complete.
    virtual void parse(const QList<QUrl> &urls);

    // Map of parse results
    virtual QMap<QUrl, ParserInterface::ParseResult> getResults() { return results; }

    // Get parsed feed for a specific URL (nullptr if parse failed)
    virtual RawFeed* getFeed(const QUrl& url);

signals:
    void ready();

protected:
    // Virtual method for creating parsers; can be overridden for unit tests.
    virtual ParserInterface* createParser();

    // Called whenever a parser is done.
    void onParserDone();

    // Parsers that are in flight.
    QMap<QUrl, ParserInterface*> parsers;

    // Results of parsing per-URL.
    QMap<QUrl, ParserInterface::ParseResult> results;

    // Parsed feeds per-URL (owned by this object).
    QMap<QUrl, RawFeed*> feeds;
};

#endif // BATCHNEWSPARSER_H
