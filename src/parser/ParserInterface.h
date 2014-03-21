#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

#include <QObject>
#include <QUrl>

#include "RawFeed.h"
#include "RawNews.h"

/**
 * @brief Interface for RSS/Atom parser.
 */
class ParserInterface : public QObject
{
    Q_OBJECT
    
public:
    enum ParseResult { OK, NETWORK_ERROR, FILE_ERROR, PARSE_ERROR, EMPTY_DOCUMENT, IN_PROGRESS };
    
    explicit ParserInterface(QObject *parent = 0);
    
signals:
    // Call getResult() and getFeed() now, yo!
    void done();
    
public slots:
    virtual void parse(const QUrl& url) =0;
    
    virtual ParseResult getResult() =0;
    virtual RawFeed* getFeed() =0;
    virtual QUrl getURL() =0;
    
};

#endif // PARSERINTERFACE_H
