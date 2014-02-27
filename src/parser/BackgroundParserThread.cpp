#include "BackgroundParserThread.h"
#include <QApplication>

#include "../utilities/Utilities.h"

BackgroundParserThread::BackgroundParserThread(QObject *parent) :
    QThread(parent)
{
}

BackgroundParserThread::~BackgroundParserThread()
{
    //delete parser; // Why can't we do this?
}



void BackgroundParserThread::setUrl(const QUrl& url)
{
    this->url = url;
}

void BackgroundParserThread::run()
{
    parser = new Parser();
    connect(parser, SIGNAL(done()), this, SLOT(onDone()));
    parser->parse(url);
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
