#include "RawNews.h"

RawNews::RawNews(QObject *parent) :
    QObject(parent),
    title(""),
    author(""),
    description(""),
    timestamp(),
    url()
{
}

bool RawNews::operator<(const RawNews& rhs) {
    // Use title if dates are equal.
    if (timestamp == rhs.timestamp)
        return title < rhs.title;
    
    // Sort on timestamp.
    return timestamp < rhs.timestamp;
}
