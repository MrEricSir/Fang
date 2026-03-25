#ifndef FEEDPARSERESULT_H
#define FEEDPARSERESULT_H

#include <memory>

#include <QString>

#include "FeedParseError.h"

class RawFeed;

class FeedParseResult {
public:
    static FeedParseResult success(std::shared_ptr<RawFeed> feed);
    static FeedParseResult failure(FeedParseError error, const QString& detail = {});

    bool ok() const { return _error == FeedParseError::None; }
    FeedParseError error() const { return _error; }
    QString errorDetail() const { return _errorDetail; }
    std::shared_ptr<RawFeed> feed() const { return _feed; }
    explicit operator bool() const { return ok(); }

private:
    FeedParseResult() = default;

    FeedParseError _error = FeedParseError::None;
    QString _errorDetail;
    std::shared_ptr<RawFeed> _feed;
};

#endif // FEEDPARSERESULT_H
