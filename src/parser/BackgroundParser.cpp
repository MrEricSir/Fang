#include "BackgroundParser.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

BackgroundParser::BackgroundParser(QObject *parent) :
    ParserInterface(parent), workerThread()
{
    connect(&workerThread, SIGNAL(parserDone()), this, SLOT(onDone()));
}

BackgroundParser::~BackgroundParser()
{
  
}

void BackgroundParser::parse(const QUrl &url)
{
    workerThread.setUrl(url);
    workerThread.start();
}

ParserInterface::ParseResult BackgroundParser::getResult()
{
    Parser* parser = workerThread.getParser();
    return parser != NULL ? parser->getResult() : ParserInterface::IN_PROGRESS;
}

RawFeed *BackgroundParser::getFeed()
{
    Parser* parser = workerThread.getParser();
    if (parser == NULL)
        return NULL;
    
    RawFeed* feed = parser->getFeed();
    return feed;
    //return parser != NULL ? parser->getFeed() : NULL;
}

QUrl BackgroundParser::getURL()
{
    Parser* parser = workerThread.getParser();
    return parser != NULL ? parser->getURL() : QUrl();
}

void BackgroundParser::onDone()
{
    qDebug() << "Bg parser done!";
    emit done();
}
