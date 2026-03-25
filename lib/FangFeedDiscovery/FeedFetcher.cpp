#include "FeedFetcher.h"

#include <QFile>
#include <QFileInfo>

#include "FeedDiscoveryLogging.h"

#include "FeedParser.h"

// Thin QObject wrapper so FeedParser::parse() runs on the worker thread.
class ParseWorker : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
public slots:
    void parse(QByteArray data)
    {
        emit done(FeedParser::parse(data));
    }
signals:
    void done(FeedParseResult result);
};

static const int feedParseResultMetaType = qRegisterMetaType<FeedParseResult>();

FeedFetcher::FeedFetcher(QObject *parent) :
    FeedSource(parent),
    result(FeedFetchResult::OK), networkError(QNetworkReply::NetworkError::NoError),
    activeManager(&manager),
    currentReply(nullptr), redirectReply(nullptr),
    fromCache(false), noParseIfCached(false),
    redirectAttempts(0),
    permanentRedirect(false)
{
    Q_UNUSED(feedParseResultMetaType);
    connect(activeManager, &QNetworkAccessManager::finished,
            this, &FeedFetcher::netFinished);

    // Setup the worker object on the worker thread.
    ParseWorker* worker = new ParseWorker();
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &FeedFetcher::triggerParse, worker, &ParseWorker::parse);
    connect(worker, &ParseWorker::done, this, &FeedFetcher::workerDone);

    workerThread.start();
}

FeedFetcher::FeedFetcher(QNetworkAccessManager* networkManager, QObject *parent) :
    FeedSource(parent),
    result(FeedFetchResult::OK), networkError(QNetworkReply::NetworkError::NoError),
    activeManager(networkManager ? networkManager : &manager),
    currentReply(nullptr), redirectReply(nullptr),
    fromCache(false), noParseIfCached(false),
    redirectAttempts(0),
    permanentRedirect(false)
{
    connect(activeManager, &QNetworkAccessManager::finished,
            this, &FeedFetcher::netFinished);

    ParseWorker* worker = new ParseWorker();
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &FeedFetcher::triggerParse, worker, &ParseWorker::parse);
    connect(worker, &ParseWorker::done, this, &FeedFetcher::workerDone);

    workerThread.start();
}

FeedFetcher::~FeedFetcher()
{
    workerThread.quit();
    workerThread.wait();
    
    delete currentReply;
}

void FeedFetcher::parse(const QUrl& url, bool noParseIfCached,
                       const QString& ifNoneMatch, const QString& ifModifiedSince)
{
    // Reset redirect counter.
    redirectAttempts = 0;
    permanentRedirect = false;

    parseInternal(url, noParseIfCached, ifNoneMatch, ifModifiedSince);
}

void FeedFetcher::parseInternal(const QUrl& url, bool noParseIfCached,
                               const QString& ifNoneMatch, const QString& ifModifiedSince)
{
    initParse(url);

    this->noParseIfCached = noParseIfCached;
    this->condIfNoneMatch = ifNoneMatch;
    this->condIfModifiedSince = ifModifiedSince;

    // in with the new
    QNetworkRequest request(url);

    // Sets a 30 second timeout in case the connection is lost or screwy.
    request.setTransferTimeout(30000);

    // Conditional request headers for ETag/Last-Modified support.
    if (!ifNoneMatch.isEmpty()) {
        request.setRawHeader("If-None-Match", ifNoneMatch.toUtf8());
    }
    if (!ifModifiedSince.isEmpty()) {
        request.setRawHeader("If-Modified-Since", ifModifiedSince.toUtf8());
    }

    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }

    currentReply = activeManager->get(request);
    connect(currentReply, &QNetworkReply::readyRead, this, &FeedFetcher::readyRead);
    connect(currentReply, &QNetworkReply::metaDataChanged, this, &FeedFetcher::metaDataChanged);
    connect(currentReply, &QNetworkReply::errorOccurred, this, &FeedFetcher::error);
}


void FeedFetcher::parseFile(const QString &filename)
{
    initParse();

    QFile file(filename);

    if (!file.exists()) {
        qCCritical(logFeedDiscovery) << "FeedFetcher::parseFile: File does not exist:" << filename;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCCritical(logFeedDiscovery) << "FeedFetcher::parseFile: Cannot open file:" << filename;
        return;
    }

    QByteArray data = file.readAll();
    emit triggerParse(data);
}

void FeedFetcher::error(QNetworkReply::NetworkError ne)
{
    Q_UNUSED(ne);
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
    
    result = FeedFetchResult::NetworkError;
    networkError = ne;
    emit done();
}


void FeedFetcher::readyRead()
{
    int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // 304 Not Modified: Content hasn't changed, nothing to do.
    if (statusCode == 304) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
        currentReply = nullptr;

        result = FeedFetchResult::NotModified;
        emit done();
        return;
    }

    if (statusCode >= 200 && statusCode < 300) {
        rawData.append(currentReply->readAll());
    }
}

void FeedFetcher::metaDataChanged()
{
    // Capture ETag and Last-Modified response headers.
    if (currentReply->hasRawHeader("ETag")) {
        respEtag = QString::fromUtf8(currentReply->rawHeader("ETag"));
    }
    if (currentReply->hasRawHeader("Last-Modified")) {
        respLastModified = QString::fromUtf8(currentReply->rawHeader("Last-Modified"));
    }

    QUrl redirectionTarget = currentReply->attribute(
                QNetworkRequest::RedirectionTargetAttribute).toUrl();

    if (redirectionTarget.isValid()) {
        // Guard against unlimited redirects.
        if (redirectAttempts >= MAX_PARSER_REDIRECTS) {
            qCDebug(logFeedDiscovery) << "FeedFetcher: Maximum redirects reached, aborting";
            currentReply->disconnect(this);
            currentReply->deleteLater();
            currentReply = nullptr;

            result = FeedFetchResult::NetworkError;
            networkError = QNetworkReply::TooManyRedirectsError;
            emit done();
            return;
        }

        int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 301 || statusCode == 308) {
            permanentRedirect = true;
        }

        qCDebug(logFeedDiscovery) << "Redirect:" << redirectionTarget.toString();
        redirectAttempts++;
        redirectReply = currentReply;
        // Don't send conditional headers on redirect -- the new URL may be different.
        parseInternal(redirectionTarget, noParseIfCached);
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
                
                result = FeedFetchResult::OK;
                emit done();
                
                return;
            }
        }
    }
}

FeedFetchResult FeedFetcher::getResult()
{
    return result;
}

std::shared_ptr<RawFeed> FeedFetcher::getFeed()
{
    return result == FeedFetchResult::OK ? feed : nullptr;
}

void FeedFetcher::netFinished(QNetworkReply *reply)
{
    if (redirectReply == reply) {
        return; // This was the previous redirect.
    }
    
    // Remember this URL.
    finalFeedURL = reply->url();
    
    // Send buffered data to the worker thread for parsing.
    emit triggerParse(rawData);
}

void FeedFetcher::workerDone(FeedParseResult parseResult)
{
    if (result != FeedFetchResult::InProgress) {
        // Already emitted a finished signal.  Nothing to dooooo.
        return;
    }

    if (parseResult.ok()) {
        feed = parseResult.feed();
        feed->url = finalFeedURL;
        result = FeedFetchResult::OK;
    } else {
        result = FeedFetchResult::ParseError;
    }

    emit done();
}

void FeedFetcher::initParse(const QUrl& url)
{
    result = FeedFetchResult::InProgress;
    networkError = QNetworkReply::NetworkError::NoError;
    finalFeedURL = url;
    respEtag = QString();
    respLastModified = QString();
    rawData.clear();
}

#include "FeedFetcher.moc"
