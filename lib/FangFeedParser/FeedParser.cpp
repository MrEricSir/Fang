#include "FeedParser.h"

#include "RawFeed.h"
#include "RSSAtomParser.h"
#include "JSONFeedParser.h"

FeedParseResult FeedParser::parse(const QByteArray& data)
{
    if (data.trimmed().isEmpty()) {
        return FeedParseResult::failure(FeedParseError::EmptyInput);
    }

    if (looksLikeJSON(data)) {
        RawFeed* feed = JSONFeedParser::parse(data);
        if (feed) {
            return FeedParseResult::success(std::shared_ptr<RawFeed>(feed));
        }
        return FeedParseResult::failure(FeedParseError::MalformedJSON);
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

FeedParseResult FeedParser::parseXML(const QByteArray& data)
{
    RawFeed* feed = RSSAtomParser::parse(data);
    if (feed) {
        return FeedParseResult::success(std::shared_ptr<RawFeed>(feed));
    }
    return FeedParseResult::failure(FeedParseError::MalformedXML);
}
