#include "FeedFetcher.h"

#include <QFile>

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

FeedFetcher::FeedFetcher(QObject *parent)
    : FeedFetcher(nullptr, parent)
{}

FeedFetcher::FeedFetcher(QNetworkAccessManager* networkManager, QObject *parent) :
    FeedSource(parent),
    result(FeedFetchResult::OK), networkError(QNetworkReply::NetworkError::NoError),
    downloader(nullptr),
    permanentRedirect(false)
{
    Q_UNUSED(feedParseResultMetaType);

    NetworkDownloadConfig config;
    config.timeoutMs = 30000;
    config.maxRedirects = 10;
    config.useInactivityTimeout = false;

    downloader = new NetworkDownloadCore(config, this, networkManager);
    connect(downloader, &NetworkDownloadCore::finishedWithResult,
            this, &FeedFetcher::onDownloadResult);

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
}

void FeedFetcher::parse(const QUrl& url,
                       const QString& ifNoneMatch, const QString& ifModifiedSince)
{
    initParse(url);
    permanentRedirect = false;

    downloader->clearRequestHeaders();
    if (!ifNoneMatch.isEmpty()) {
        downloader->setRequestHeader("If-None-Match", ifNoneMatch.toUtf8());
    }
    if (!ifModifiedSince.isEmpty()) {
        downloader->setRequestHeader("If-Modified-Since", ifModifiedSince.toUtf8());
    }

    downloader->download(url);
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

void FeedFetcher::onDownloadResult(NetworkDownloadResult downloadResult)
{
    if (!downloadResult.ok()) {
        networkError = downloadResult.networkError;
        result = FeedFetchResult::NetworkError;
        emit done();
        return;
    }

    // 304 Not Modified: Content hasn't changed, nothing to do.
    if (downloadResult.statusCode == 304) {
        result = FeedFetchResult::NotModified;
        emit done();
        return;
    }

    // Success path.
    finalFeedURL = downloadResult.url;
    permanentRedirect = downloadResult.permanentRedirect;
    respEtag = QString::fromUtf8(downloadResult.responseHeader("ETag"));
    respLastModified = QString::fromUtf8(downloadResult.responseHeader("Last-Modified"));

    emit triggerParse(downloadResult.data);
}

FeedFetchResult FeedFetcher::getResult()
{
    return result;
}

std::shared_ptr<RawFeed> FeedFetcher::getFeed()
{
    return result == FeedFetchResult::OK ? feed : nullptr;
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
}

#include "FeedFetcher.moc"
