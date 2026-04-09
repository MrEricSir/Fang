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
        auto feed = JSONFeedParser::parse(data);
        if (feed) {
            return FeedParseResult::success(std::move(feed));
        }

        // Couldn't parse JSON, maybe it's RSS/Atom?
        return parseXML(data);
    }

    FeedParseResult xmlResult = parseXML(data);
    if (xmlResult.ok()) {
        return xmlResult;
    }

    // RSS/Atom parser failed, try JSON parser as fallback.
    auto feed = JSONFeedParser::parse(data);
    if (feed) {
        return FeedParseResult::success(std::move(feed));
    }

    // We tried. *shrugs*
    return xmlResult;
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
    auto feed = RSSAtomParser::parse(data);
    if (feed) {
        return FeedParseResult::success(std::move(feed));
    }
    return FeedParseResult::failure(FeedParseError::MalformedXML);
}
