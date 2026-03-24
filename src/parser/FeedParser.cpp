#include "FeedParser.h"

#include "RSSAtomParser.h"
#include "JSONFeedParser.h"

RawFeed* FeedParser::parse(const QByteArray& data)
{
    if (looksLikeJSON(data)) {
        return JSONFeedParser::parse(data);
    }
    return parseXML(data);
}

bool FeedParser::looksLikeJSON(const QByteArray& data)
{
    for (int i = 0; i < data.size(); ++i) {
        char ch = data.at(i);
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            continue;
        }
        return ch == '{';
    }
    return false;
}

RawFeed* FeedParser::parseXML(const QByteArray& data)
{
    return RSSAtomParser::parse(data);
}

