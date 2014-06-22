#include "Parser.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include "../utilities/NetworkUtilities.h"

Parser::Parser(QObject *parent) :
    ParserInterface(parent),
    feed(NULL), result(OK),
    currentReply(NULL), redirectReply(NULL),
    fromCache(false), noParseIfCached(false)
{
    NetworkUtilities::addCache(&manager);
    
    // Connex0r teh siganls.
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(netFinished(QNetworkReply*)));
    
    // Setup the worker object.
    ParserXMLWorker* worker = new ParserXMLWorker();
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Parser::triggerDocStart, worker, &ParserXMLWorker::documentStart);
    connect(this, &Parser::triggerDocEnd, worker, &ParserXMLWorker::documentEnd);
    connect(this, &Parser::triggerAddXML, worker, &ParserXMLWorker::addXML);
    connect(worker, SIGNAL(done(RawFeed*)),
            this, SLOT(workerDone(RawFeed*)));
    
    workerThread.start();
}

Parser::~Parser()
{
    workerThread.quit();
    workerThread.wait();
    
    delete currentReply;
}

void Parser::parse(const QUrl& url, bool noParseIfCached)
{
    initParse(url);
    
    this->noParseIfCached = noParseIfCached;
    
    // in with the new
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
    // Use the cache, luke.
    NetworkUtilities::useCache(&request);
    
    currentReply = manager.get(request);
    connect(currentReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void Parser::parseFile(const QString &filename)
{
    initParse();
    
    QFile file(filename);
    
    //QFileInfo fileInfo(filename);
    //qDebug() << "Filename: " << fileInfo.absoluteFilePath();
    
    Q_ASSERT(file.exists());
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Q_ASSERT(false);
        return;
    }
    
    QByteArray data = file.readAll();
    emit triggerAddXML(data);
    emit triggerDocEnd();
}

void Parser::error(QNetworkReply::NetworkError ne)
{
    Q_UNUSED(ne);
    //qDebug() << "Error!!!!! " << ne << " " << currentReply->errorString();
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
    
    result = Parser::NETWORK_ERROR;
    emit done();
}


void Parser::readyRead()
{
    int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) {
        QByteArray data = currentReply->readAll();
        emit triggerAddXML(data);
    }
}

void Parser::metaDataChanged()
{
    QUrl redirectionTarget = currentReply->attribute(
                QNetworkRequest::RedirectionTargetAttribute).toUrl();
    
    // TODO: prevent endless loooooping!!!
    if (redirectionTarget.isValid()) {
        qDebug() << "Redirect: " << redirectionTarget.toString();
        redirectReply = currentReply;
        parse(redirectionTarget, noParseIfCached);
    }
    
    if (currentReply->attribute(
                QNetworkRequest::SourceIsFromCacheAttribute).isValid()) {
        if (currentReply->attribute(
                    QNetworkRequest::SourceIsFromCacheAttribute).toBool()) {
            if (noParseIfCached) {
                // Early exit for cache.
                currentReply->disconnect(this);
                currentReply->deleteLater();
                currentReply = 0;
                
                result = Parser::OK;
                emit done();
                
                return;
            }
        }
    }
}

Parser::ParseResult Parser::getResult()
{
    return result;
}

RawFeed* Parser::getFeed()
{
    return result == Parser::OK ? feed : NULL;
}

void Parser::netFinished(QNetworkReply *reply)
{
    if (redirectReply == reply)
        return; // This was the previous redirect.
    
    // Remember this URL.
    finalFeedURL = reply->url();
    
    // Tell the worker that we're done.
    emit triggerDocEnd();
}

void Parser::workerDone(RawFeed* rawFeed)
{
    if (result != Parser::IN_PROGRESS) {
        // Already emitted a finished signal.  Nothing to dooooo.
        return;
    }
    
    if (rawFeed) {
        feed = rawFeed;
        
        // This means we saw... something.  Do a sanity check here to
        // make sure what we found was an actual feed.
        if (feed->items.size() > 0 || feed->title != "") {
            feed->url = finalFeedURL;
            
            result = Parser::OK;
            //qDebug() << "Here, done is emitted.";
            emit done();
            
            return; // Early exit on SUCCESS!! (yay)
        }
    }
    
    // What we found must not have been an RSS/Atom feed.
    result = Parser::PARSE_ERROR;
    emit done();
}

void Parser::initParse(const QUrl& url)
{
    result = Parser::IN_PROGRESS;
    finalFeedURL = url;
    emit triggerDocStart();
}
