#include "BackgroundParserThread.h"
#include <QApplication>

#include "../utilities/Utilities.h"

BackgroundParserThread::BackgroundParserThread(QObject *parent) :
    QThread(parent),
    parser(NULL)
{
}

BackgroundParserThread::~BackgroundParserThread()
{
    //delete parser; // Why can't we do this?
}



void BackgroundParserThread::setVars(const QUrl& url, bool noParseIfCached)
{
    this->url = url;
    this->noParseIfCached = noParseIfCached;
}

void BackgroundParserThread::run()
{
    parser = new Parser();
    connect(parser, SIGNAL(done()), this, SLOT(onDone()));
    parser->parse(url, noParseIfCached);
    exec();
    parser->moveToThread(QApplication::instance()->thread());
    //qDebug() << "Parser started!";
}


void BackgroundParserThread::onDone()
{
    //qDebug() << "parser done";
    quit();
    wait();
    
    emit parserDone();
}
