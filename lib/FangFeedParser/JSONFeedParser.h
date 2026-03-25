#ifndef JSONFEEDPARSER_H
#define JSONFEEDPARSER_H

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
    // Caller takes ownership of the returned RawFeed.
    static RawFeed* parse(const QByteArray& data);
};

#endif // JSONFEEDPARSER_H
