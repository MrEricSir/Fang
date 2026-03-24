#include "FeedParserRouter.h"

#include "ParserXMLWorker.h"
#include "JSONFeedParser.h"
#include "RawFeed.h"

FeedParserRouter::FeedParserRouter(QObject *parent) :
    FangObject(parent), xmlWorker(new ParserXMLWorker(this))
{
}

void FeedParserRouter::documentStart()
{
    buffer.clear();
}

void FeedParserRouter::addData(QByteArray data)
{
    buffer.append(data);
}

void FeedParserRouter::documentEnd()
{
    RawFeed* feed = nullptr;

    if (looksLikeJSON()) {
        feed = tryJSON();
        if (!isValidFeed(feed)) {
            delete feed;
            feed = tryXML();
        }
    } else {
        feed = tryXML();
        if (!isValidFeed(feed)) {
            delete feed;
            feed = tryJSON();
        }
    }

    emit done(feed);
}

bool FeedParserRouter::looksLikeJSON() const
{
    for (int i = 0; i < buffer.size(); ++i) {
        char ch = buffer.at(i);
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            continue;
        }
        return ch == '{';
    }
    return false;
}

RawFeed* FeedParserRouter::tryXML()
{
    xmlWorker->documentStart();
    xmlWorker->addXML(buffer);
    xmlWorker->documentEnd();

    RawFeed* feed = xmlWorker->takeFeed();
    return feed;
}

RawFeed* FeedParserRouter::tryJSON()
{
    return JSONFeedParser::parse(buffer);
}

bool FeedParserRouter::isValidFeed(RawFeed* feed)
{
    return feed && (feed->items.size() > 0 || !feed->title.isEmpty());
}
