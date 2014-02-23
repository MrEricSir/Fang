#include "BackgroundParserThread.h"
#include <QApplication>

#include "../utilities/Utilities.h"

BackgroundParserThread::BackgroundParserThread(QObject *parent) :
    QThread(parent), manager()
{
    // Enble cache.
    Utilities::addNetworkAccessManagerCache(&manager);
}

void BackgroundParserThread::setUrl(const QUrl& url)
{
    this->url = url;
}

void BackgroundParserThread::run()
{
    parser = new Parser(this, &manager);
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
