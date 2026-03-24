#ifndef FEEDPARSER_H
#define FEEDPARSER_H

#include <QByteArray>

class RawFeed;

/*!
    \brief Synchronous feed parser API.

    Sniffs the format of the given data (RSS/Atom XML or JSON Feed)
    and dispatches to the appropriate parser. Returns a RawFeed on
    success, or nullptr on failure. Caller takes ownership.
 */
class FeedParser
{
public:
    // Parses raw bytes as RSS, Atom, or JSON Feed.
    // Returns RawFeed* on success (caller owns), nullptr on failure.
    static RawFeed* parse(const QByteArray& data);

private:
    static bool looksLikeJSON(const QByteArray& data);
    static RawFeed* parseXML(const QByteArray& data);
};

#endif // FEEDPARSER_H
