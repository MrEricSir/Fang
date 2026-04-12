#ifndef FEEDFETCHER_H
#define FEEDFETCHER_H

#include <memory>

#include <QObject>
#include <QString>
#include <QNetworkReply>
#include <QFutureWatcher>

#include "FeedSource.h"
#include "FeedParseResult.h"
#include "QWebDownload.h"

/*!
    PaRSSes RSS/Atom feeds into RawFeed/RawNews objects.
 */
class FeedFetcher : public FeedSource
{
    Q_OBJECT

public:
    explicit FeedFetcher(QObject *parent = nullptr);
    explicit FeedFetcher(QNetworkAccessManager* networkManager, QObject *parent = nullptr);
    virtual ~FeedFetcher();

public slots:
    void parse(const QUrl& url,
               const QString& ifNoneMatch = QString(),
               const QString& ifModifiedSince = QString()) override;

    FeedFetchResult getResult() override;
    QNetworkReply::NetworkError getNetworkError() { return networkError; }
    std::shared_ptr<RawFeed> getFeed() override;
    QUrl getURL() override { return finalFeedURL; }

    QString responseEtag() override { return respEtag; }
    QString responseLastModified() override { return respLastModified; }
    bool wasPermanentRedirect() const { return permanentRedirect; }

private slots:
    // When the download completes (success or error).
    void onDownloadResult(WebDownloadResult downloadResult);

private:
    // When parsing completes on the thread pool.
    void workerDone(FeedParseResult parseResult);

    void initParse(const QUrl& url = QUrl("")); // called prior to parse.

    std::shared_ptr<RawFeed> feed;
    FeedFetchResult result;
    QNetworkReply::NetworkError networkError;

    QWebDownload* downloader;
    QUrl finalFeedURL;

    QString respEtag;
    QString respLastModified;

    bool permanentRedirect;

    QFutureWatcher<FeedParseResult> parseWatcher;
};

#endif // FEEDFETCHER_H
