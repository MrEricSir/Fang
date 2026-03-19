#ifndef GOOGLENEWSSITEMAPSYNTHESIZER_H
#define GOOGLENEWSSITEMAPSYNTHESIZER_H

#include <QDateTime>
#include <QList>
#include <QStringList>
#include <QUrl>

#include "../FangObject.h"
#include "../parser/RawFeed.h"
#include "../parser/SitemapParser.h"
#include "../network/NetworkDownloadCore.h"

class GoogleNewsSitemapSynthesizer : public FangObject
{
    Q_OBJECT
public:
    explicit GoogleNewsSitemapSynthesizer(QObject* parent = nullptr);
    virtual ~GoogleNewsSitemapSynthesizer();

    /*!
        \brief For initial discovery (FeedDiscovery). Probes news sitemap URLs.
        \param siteUrl The site's base URL (scheme + host).
        \param siteTitle Title extracted from the homepage.
     */
    virtual void synthesize(const QUrl& siteUrl, const QString& siteTitle);

    /*!
        \brief For refresh (UpdateFeedOperation). Fetches the stored sitemap URL.
        \param sitemapUrl The news sitemap URL to fetch.
        \param feedTitle The feed's stored title.
        \param since Only include entries newer than this date.
     */
    virtual void synthesize(const QUrl& sitemapUrl, const QString& feedTitle,
                            const QDateTime& since);

    bool hasError() const { return _hasError; }
    QString errorString() const { return _errorString; }
    RawFeed* result() const { return _result; }

signals:
    void done();

private slots:
    void onRobotsTxtDownloaded(const QUrl& url, const QByteArray& data);
    void onRobotsTxtDownloadError(const QUrl& url, const QString& errorString);
    void onCandidateDownloaded(const QUrl& url, const QByteArray& data);
    void onCandidateDownloadError(const QUrl& url, const QString& errorString);
    void onSubSitemapDownloaded(const QUrl& url, const QByteArray& data);
    void onSubSitemapDownloadError(const QUrl& url, const QString& errorString);

private:
    static const int MAX_ENTRIES = 30;

    void reportError(const QString& error);
    void fetchRobotsTxt();
    void buildCandidateUrls(const QList<QUrl>& robotsSitemaps);
    void tryNextCandidate();
    void tryNextSubSitemap();
    void processParsedEntries(const QList<SitemapEntry>& entries, const QUrl& sourceUrl);
    void buildRawFeed();
    static QString normalizeLanguage(const QString& lang);

protected:
    void setResultState(RawFeed* result, bool hasError, const QString& errorString);

public:
    // Public for unit testing.
    static QList<QUrl> parseRobotsSitemaps(const QString& robotsTxt, const QUrl& siteBaseUrl);
    static QStringList newsSitemapPaths();
    static QList<SitemapEntry> deduplicateRepetitiveTitles(
        const QList<SitemapEntry>& entries,
        int prefixWordCount = 4,
        int repetitionThreshold = 3);

private:

    // Config
    QUrl siteBaseUrl;
    QString feedTitle;
    QDateTime since;
    bool isRefresh;

    // State
    bool _hasError;
    QString _errorString;
    RawFeed* _result;

    // Candidate probing
    QList<QUrl> candidateUrls;
    NetworkDownloadCore* downloader;

    // Sub-sitemap iteration (for sitemapindex responses)
    QList<SubSitemap> pendingSubSitemaps;
    QList<SitemapEntry> accumulatedEntries;
    QUrl sitemapIndexUrl;

    // Filtered entries ready for feed building
    QList<SitemapEntry> feedEntries;
    QUrl feedSourceUrl; // The actual sitemap URL that provided the entries
};

#endif // GOOGLENEWSSITEMAPSYNTHESIZER_H
