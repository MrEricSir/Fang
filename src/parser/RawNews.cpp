#include "RawNews.h"

RawNews::RawNews(QObject *parent) :
    QObject(parent),
    title(""),
    author(""),
    description(""),
    timestamp(),
    url(),
    dbId(-1)
{
}

bool RawNews::operator<(const RawNews& right) {
    return LessThan(this, &right);
}

bool RawNews::LessThan(const RawNews *left, const RawNews *right)
{
    // Use title if dates are equal.
    if (left->timestamp == right->timestamp)
        return left->title < right->title;
    
    // Sort on timestamp.
    return left->timestamp < right->timestamp;
}

bool RawNews::GreaterThan(const RawNews *left, const RawNews *right)
{
    return !LessThan(left, right);
}
