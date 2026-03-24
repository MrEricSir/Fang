#ifndef FEEDPARSERROUTER_H
#define FEEDPARSERROUTER_H

#include <QByteArray>

#include "../FangObject.h"

class RawFeed;
class ParserXMLWorker;

/*!
    \brief Routes feed data to the correct format-specific parser.

    Buffers all incoming data, then on documentEnd() sniffs the format
    and dispatches to either ParserXMLWorker or JSONFeedParser. The caller
    (NewsParser) stays format-agnostic.
 */
class FeedParserRouter : public FangObject
{
    Q_OBJECT
public:
    explicit FeedParserRouter(QObject *parent = nullptr);

signals:
    void done(RawFeed* feed);

public slots:
    void documentStart();
    void addData(QByteArray data);
    void documentEnd();

private:
    bool looksLikeJSON() const;
    RawFeed* tryXML();
    RawFeed* tryJSON();
    static bool isValidFeed(RawFeed* feed);

    QByteArray buffer;
    ParserXMLWorker* xmlWorker;
};

#endif // FEEDPARSERROUTER_H
