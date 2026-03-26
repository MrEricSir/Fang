#ifndef FEEDFETCHER_H
#define FEEDFETCHER_H

#include <memory>

#include <QObject>
#include <QString>
#include <QNetworkReply>
#include <QThread>

#include "FeedSource.h"
#include "FeedParseResult.h"
#include "NetworkDownloadCore.h"

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

    // For testing purposes.
    void parseFile(const QString& filename);

    FeedFetchResult getResult() override;
    QNetworkReply::NetworkError getNetworkError() { return networkError; }
    std::shared_ptr<RawFeed> getFeed() override;
    QUrl getURL() override { return finalFeedURL; }

    QString responseEtag() override { return respEtag; }
    QString responseLastModified() override { return respLastModified; }
    bool wasPermanentRedirect() const { return permanentRedirect; }

    // These are used internally.
signals:

    // Send buffered data to the worker thread for parsing.
    void triggerParse(QByteArray data);

private slots:
    // When the download completes (success or error).
    void onDownloadResult(NetworkDownloadResult downloadResult);

    // When the worker thread thinks the document is complete, or an error occurred.
    void workerDone(FeedParseResult parseResult);

private:
    void initParse(const QUrl& url = QUrl("")); // called prior to parse.

    std::shared_ptr<RawFeed> feed;
    FeedFetchResult result;
    QNetworkReply::NetworkError networkError;

    NetworkDownloadCore* downloader;
    QUrl finalFeedURL;

    QString respEtag;
    QString respLastModified;

    bool permanentRedirect;

    QThread workerThread;
};

#endif // FEEDFETCHER_H
