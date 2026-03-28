#include "FeedParseResult.h"
#include "RawFeed.h"

FeedParseResult FeedParseResult::success(std::shared_ptr<RawFeed> feed)
{
    FeedParseResult result;
    result._feed = std::move(feed);
    return result;
}

FeedParseResult FeedParseResult::failure(FeedParseError error, const QString& detail)
{
    FeedParseResult result;
    result._error = error;
    result._errorDetail = detail;
    return result;
}
