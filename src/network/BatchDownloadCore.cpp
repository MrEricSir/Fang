#include "BatchDownloadCore.h"
#include "FangNetworkAccessManager.h"

#include <QSet>

BatchDownloadCore::BatchDownloadCore(int timeoutMs,
                                     int maxRedirects,
                                     QObject* parent,
                                     QNetworkAccessManager* networkManager)
    : FangObject(parent)
    , manager(networkManager ? networkManager : new FangNetworkAccessManager(this))
    , ownsManager(networkManager == nullptr)
    , totalCount(0)
{
    config.timeoutMs = timeoutMs;
    config.maxRedirects = maxRedirects;
}

BatchDownloadCore::~BatchDownloadCore()
{
    abort();
}

void BatchDownloadCore::download(const QList<QUrl>& urls)
{
    // Clear previous.
    abort();
    _results.clear();

    // Handle empty list.
    if (urls.isEmpty()) {
        totalCount = 0;
        emit finished();
        return;
    }

    // Deduplicate URL list.
    QList<QUrl> uniqueUrls;
    QSet<QUrl> seen;
    for (const QUrl& url : urls) {
        if (!seen.contains(url)) {
            seen.insert(url);
            uniqueUrls.append(url);
        }
    }

    totalCount = uniqueUrls.size();

    // Create a NetworkDownloadCore for each URL.
    for (const QUrl& url : uniqueUrls) {
        auto* downloader = new NetworkDownloadCore(config, nullptr, manager);

        connect(downloader, &NetworkDownloadCore::finished,
                this, &BatchDownloadCore::onDownloadFinished);
        connect(downloader, &NetworkDownloadCore::error,
                this, &BatchDownloadCore::onDownloadError);

        downloaders[downloader] = url;
        downloader->download(url);
    }
}

void BatchDownloadCore::abort()
{
    // STOP! and delete all downloaders.
    for (auto it = downloaders.begin(); it != downloaders.end(); ++it) {
        NetworkDownloadCore* downloader = it.key();
        downloader->abort();
        delete downloader;
    }

    downloaders.clear();
}

void BatchDownloadCore::onDownloadFinished(const QUrl& finalUrl, const QByteArray& data)
{
    auto* downloader = qobject_cast<NetworkDownloadCore*>(sender());
    if (!downloader || !downloaders.contains(downloader)) {
        return;
    }

    QUrl originalUrl = downloaders.take(downloader);
    downloader->deleteLater();

    BatchDownloadResult result;
    result.success = true;
    result.data = data;
    result.finalUrl = finalUrl;

    _results[originalUrl] = result;

    emit progress(_results.size(), totalCount);
    checkCompletion();
}

void BatchDownloadCore::onDownloadError(const QUrl& url, const QString& errorString)
{
    Q_UNUSED(url);

    auto* downloader = qobject_cast<NetworkDownloadCore*>(sender());
    if (!downloader || !downloaders.contains(downloader)) {
        return;
    }

    QUrl originalUrl = downloaders.take(downloader);
    downloader->deleteLater();

    BatchDownloadResult result;
    result.success = false;
    result.errorString = errorString;

    _results[originalUrl] = result;

    emit progress(_results.size(), totalCount);
    checkCompletion();
}

void BatchDownloadCore::checkCompletion()
{
    if (_results.size() == totalCount) {
        emit finished();
    }
}
