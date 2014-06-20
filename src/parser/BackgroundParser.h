#ifndef BACKGROUNDPARSER_H
#define BACKGROUNDPARSER_H

#include <QThread>
#include "ParserInterface.h"
#include "Parser.h"
#include "BackgroundParserThread.h"

class BackgroundParser : public ParserInterface
{
    Q_OBJECT
    
public:
    explicit BackgroundParser(QObject *parent = 0);
    virtual ~BackgroundParser();
    
signals:
    
public slots:
    virtual void parse(const QUrl& url, bool noParseIfCached = false);
    
    virtual ParseResult getResult();
    virtual RawFeed* getFeed();
    virtual QUrl getURL();
    
    virtual bool isFromCache();
    
private slots:
    void onDone();
    
private:

    BackgroundParserThread workerThread;
};

#endif // BACKGROUNDPARSER_H
