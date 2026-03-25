#ifndef FEEDPARSER_H
#define FEEDPARSER_H

#include <QByteArray>

#include "FeedParseResult.h"

/*!
    \brief Synchronous feed parser API.

    Sniffs the format of the given data (RSS/Atom XML or JSON Feed)
    and dispatches to the appropriate parser. Returns a FeedParseResult
    indicating success or failure with error details.
 */
class FeedParser
{
public:
    static FeedParseResult parse(const QByteArray& data);

private:
    static bool looksLikeJSON(const QByteArray& data);
    static FeedParseResult parseXML(const QByteArray& data);
};

#endif // FEEDPARSER_H
