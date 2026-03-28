#ifndef JSONFEEDPARSER_H
#define JSONFEEDPARSER_H

#include <memory>

#include <QByteArray>

class RawFeed;

/**
    \brief The JSONFeedParser class attempts to parse a news feed in the JSON Feed format
    into a RawFeed object.
 */
class JSONFeedParser
{
public:
    // Returns a parsed RawFeed, or nullptr if not valid JSON Feed.
    static std::unique_ptr<RawFeed> parse(const QByteArray& data);
};

#endif // JSONFEEDPARSER_H
