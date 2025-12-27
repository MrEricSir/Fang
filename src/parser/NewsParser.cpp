#include "NewsParser.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include "ParserXMLWorker.h"

NewsParser::NewsParser(QObject *parent) :
    ParserInterface(parent),
    feed(nullptr), result(OK), networkError(QNetworkReply::NetworkError::NoError),
    currentReply(nullptr), redirectReply(nullptr),
    fromCache(false), noParseIfCached(false)
{
    // Connex0r teh siganls.
    connect(&manager, &FangNetworkAccessManager::finished,
            this, &NewsParser::netFinished);
    
    // Setup the worker object.
    ParserXMLWorker* worker = new ParserXMLWorker();
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &NewsParser::triggerDocStart, worker, &ParserXMLWorker::documentStart);
    connect(this, &NewsParser::triggerDocEnd, worker, &ParserXMLWorker::documentEnd);
    connect(this, &NewsParser::triggerAddXML, worker, &ParserXMLWorker::addXML);
    connect(worker, &ParserXMLWorker::done, this, &NewsParser::workerDone);
    
    workerThread.start();
}

NewsParser::~NewsParser()
{
    workerThread.quit();
    workerThread.wait();
    
    delete currentReply;
}

void NewsParser::parse(const QUrl& url, bool noParseIfCached)
{
    initParse(url);
    
    this->noParseIfCached = noParseIfCached;
    
    // in with the new
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    
    currentReply = manager.get(request);
    connect(currentReply, &QNetworkReply::readyRead, this, &NewsParser::readyRead);
    connect(currentReply, &QNetworkReply::metaDataChanged, this, &NewsParser::metaDataChanged);
    connect(currentReply, &QNetworkReply::errorOccurred, this, &NewsParser::error);
}


void NewsParser::parseFile(const QString &filename)
{
    initParse();
    
    QFile file(filename);
    
    Q_ASSERT(file.exists());
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Q_ASSERT(false);
        return;
    }
    
    QByteArray data = file.readAll();
    emit triggerAddXML(data);
    emit triggerDocEnd();
}

void NewsParser::error(QNetworkReply::NetworkError ne)
{
    Q_UNUSED(ne);
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
    
    result = NewsParser::NETWORK_ERROR;
    networkError = ne;
    emit done();
}


void NewsParser::readyRead()
{
    int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) {
        QByteArray data = currentReply->readAll();
        emit triggerAddXML(data);
    }
}

void NewsParser::metaDataChanged()
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
                
                result = NewsParser::OK;
                emit done();
                
                return;
            }
        }
    }
}

NewsParser::ParseResult NewsParser::getResult()
{
    return result;
}

RawFeed* NewsParser::getFeed()
{
    return result == NewsParser::OK ? feed : nullptr;
}

void NewsParser::netFinished(QNetworkReply *reply)
{
    if (redirectReply == reply) {
        return; // This was the previous redirect.
    }
    
    // Remember this URL.
    finalFeedURL = reply->url();
    
    // Tell the worker that we're done.
    emit triggerDocEnd();
}

void NewsParser::workerDone(RawFeed* rawFeed)
{
    if (result != NewsParser::IN_PROGRESS) {
        // Already emitted a finished signal.  Nothing to dooooo.
        return;
    }
    
    if (rawFeed) {
        feed = rawFeed;

        // This means we saw... something.  Do a sanity check here to
        // make sure what we found was an actual feed.
        if (feed->items.size() > 0 || feed->title != "") {
            feed->url = finalFeedURL;
            
            result = NewsParser::OK;
            emit done();
            
            return; // Early exit on SUCCESS!! (yay)
        }
    }
    
    // What we found must not have been an RSS/Atom feed.
    result = NewsParser::PARSE_ERROR;
    emit done();
}

void NewsParser::initParse(const QUrl& url)
{
    result = NewsParser::IN_PROGRESS;
    networkError = QNetworkReply::NetworkError::NoError;
    finalFeedURL = url;
    emit triggerDocStart();
}
