#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

#include <QObject>
#include <QUrl>

#include "RawFeed.h"

#include "../FangObject.h"

/*!
    \brief Interface for RSS/Atom parser.
 */
class ParserInterface : public FangObject
{
    Q_OBJECT
    
public:
    enum ParseResult { OK, NETWORK_ERROR, FILE_ERROR, PARSE_ERROR, EMPTY_DOCUMENT, IN_PROGRESS };
    Q_ENUM(ParseResult)
    
    explicit ParserInterface(QObject *parent = nullptr);
    virtual ~ParserInterface() {}
    
signals:
    // Call getResult() and getFeed() now, yo!
    void done();
    
public slots:

    /*!
        \brief Contacts URL and parses the RSS/Atom feed, if it exists.
        \param url               The URL
        \param noParseIfCached   If true, this won't bother with the
                                 parse if the content was cached.
     */
    virtual void parse(const QUrl& url, bool noParseIfCached = false) =0;
    
    virtual ParserInterface::ParseResult getResult() =0;
    virtual RawFeed* getFeed() =0;
    virtual QUrl getURL() =0;
    
    // Whether or not the response was cached.
    virtual bool isFromCache() =0;
    
};

#endif // PARSERINTERFACE_H
