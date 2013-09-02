#include "BackgroundParserThread.h"
#include <QApplication>

BackgroundParserThread::BackgroundParserThread(QObject *parent) :
    QThread(parent)
{
    
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
