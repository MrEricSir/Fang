#ifndef MOCKNEWSPARSER_H
#define MOCKNEWSPARSER_H

#include <QObject>
#include <QTimer>
#include <QUrl>
#include "../src/parser/ParserInterface.h"
#include "../src/parser/RawFeed.h"

/**
 * @brief Mock version of ParserInterface
 *
 * Allows pre-configuring the parse result, feed data, and URL to test code that depends
 * on NewsParser without network access.
 */
class MockNewsParser : public ParserInterface
{
    Q_OBJECT

public:
    explicit MockNewsParser(QObject *parent = nullptr);
    virtual ~MockNewsParser() override;

    // Mock behavior
    void setResult(ParseResult result);
    void setFeed(RawFeed* feed);  // Takes ownership
    void setURL(const QUrl& url);
    void setFromCache(bool cached);

    // Reset state
    void reset();

    // ParserInterface implementation
    virtual void parse(const QUrl& url, bool noParseIfCached = false) override;
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

#endif // MOCKNEWSPARSER_H
