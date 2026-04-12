#include "QBatchWebDownload.h"

#include <QNetworkAccessManager>
#include <QSet>

QBatchWebDownload::QBatchWebDownload(int timeoutMs,
                                     int maxRedirects,
                                     QObject* parent,
                                     QNetworkAccessManager* networkManager)
    : QObject(parent)
    , manager(networkManager ? networkManager : new QNetworkAccessManager(this))
    , totalCount(0)
{
    config.timeoutMs = timeoutMs;
    config.maxRedirects = maxRedirects;
}

QBatchWebDownload::~QBatchWebDownload()
{
    abort();
}

void QBatchWebDownload::get(const QList<QUrl>& urls)
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

    // Create a QWebDownload for each URL.
    for (const QUrl& url : uniqueUrls) {
        auto* downloader = new QWebDownload(config, nullptr, manager);

        connect(downloader, &QWebDownload::finished,
                this, &QBatchWebDownload::onDownloadFinished);
        connect(downloader, &QWebDownload::error,
                this, &QBatchWebDownload::onDownloadError);

        downloaders[downloader] = url;
        downloader->get(url);
    }
}

void QBatchWebDownload::abort()
{
    // STOP! and delete all downloaders.
    for (auto it = downloaders.begin(); it != downloaders.end(); ++it) {
        QWebDownload* downloader = it.key();
        downloader->abort();
        delete downloader;
    }

    downloaders.clear();
}

void QBatchWebDownload::onDownloadFinished(const QUrl& finalUrl, const QByteArray& data)
{
    auto* downloader = qobject_cast<QWebDownload*>(sender());
    if (!downloader || !downloaders.contains(downloader)) {
        return;
    }

    QUrl originalUrl = downloaders.take(downloader);
    downloader->deleteLater();

    BatchWebDownloadResult result;
    result.success = true;
    result.data = data;
    result.finalUrl = finalUrl;

    _results[originalUrl] = result;

    emit progress(_results.size(), totalCount);
    checkCompletion();
}

void QBatchWebDownload::onDownloadError(const QUrl& url, const QString& errorString)
{
    Q_UNUSED(url);

    auto* downloader = qobject_cast<QWebDownload*>(sender());
    if (!downloader || !downloaders.contains(downloader)) {
        return;
    }

    QUrl originalUrl = downloaders.take(downloader);
    downloader->deleteLater();

    BatchWebDownloadResult result;
    result.success = false;
    result.errorString = errorString;

    _results[originalUrl] = result;

    emit progress(_results.size(), totalCount);
    checkCompletion();
}

void QBatchWebDownload::checkCompletion()
{
    if (_results.size() == totalCount) {
        emit finished();
    }
}
