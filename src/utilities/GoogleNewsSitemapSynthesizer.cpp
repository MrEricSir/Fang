#include "GoogleNewsSitemapSynthesizer.h"
#include "FangLogging.h"

#include <algorithm>
#include <QSet>

static QString stripWww(const QString& host)
{
    if (host.startsWith("www.")) {
        return host.mid(4);
    }
    return host;
}

GoogleNewsSitemapSynthesizer::GoogleNewsSitemapSynthesizer(QObject* parent)
    : FangObject(parent)
    , isRefresh(false)
    , _hasError(false)
    , _result(nullptr)
    , downloader(nullptr)
{
}

GoogleNewsSitemapSynthesizer::~GoogleNewsSitemapSynthesizer()
{
}

QStringList GoogleNewsSitemapSynthesizer::newsSitemapPaths()
{
    return {
        "/news-sitemap.xml",
        "/sitemap_news.xml",
        "/news-sitemap-content.xml"
    };
}

void GoogleNewsSitemapSynthesizer::synthesize(const QUrl& siteUrl, const QString& siteTitle)
{
    isRefresh = false;
    feedTitle = siteTitle;
    since = QDateTime();

    // Build base URL for probing.
    siteBaseUrl.setScheme(siteUrl.scheme());
    siteBaseUrl.setHost(siteUrl.host());

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: starting discovery for" << siteBaseUrl;

    // Start by fetching robots.txt to discover news sitemap URLs.
    fetchRobotsTxt();
}

void GoogleNewsSitemapSynthesizer::synthesize(const QUrl& sitemapUrl, const QString& feedTitle,
                                        const QDateTime& since)
{
    isRefresh = true;
    this->feedTitle = feedTitle;
    this->since = since;

    // For refresh, we already know the exact sitemap URL.
    candidateUrls.clear();
    candidateUrls.append(sitemapUrl);

    siteBaseUrl.setScheme(sitemapUrl.scheme());
    siteBaseUrl.setHost(sitemapUrl.host());

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: refreshing from" << sitemapUrl
                        << "since" << since;

    tryNextCandidate();
}

void GoogleNewsSitemapSynthesizer::fetchRobotsTxt()
{
    QUrl robotsUrl = siteBaseUrl;
    robotsUrl.setPath("/robots.txt");

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: fetching" << robotsUrl;

    downloader = new NetworkDownloadCore({}, this, nullptr);
    connect(downloader, &NetworkDownloadCore::finished,
            this, &GoogleNewsSitemapSynthesizer::onRobotsTxtDownloaded);
    connect(downloader, &NetworkDownloadCore::error,
            this, &GoogleNewsSitemapSynthesizer::onRobotsTxtDownloadError);
    downloader->download(robotsUrl);
}

QList<QUrl> GoogleNewsSitemapSynthesizer::parseRobotsSitemaps(const QString& robotsTxt,
                                                         const QUrl& siteBaseUrl)
{
    QList<QUrl> newsSitemaps;
    QStringList lines = robotsTxt.split('\n');

    for (const QString& line : lines) {
        QString trimmed = line.trimmed();
        if (trimmed.startsWith("Sitemap:", Qt::CaseInsensitive)) {
            QString urlStr = trimmed.mid(8).trimmed();
            QUrl url(urlStr);
            if (url.isValid() && stripWww(url.host()) == stripWww(siteBaseUrl.host())
                && url.path().contains("news", Qt::CaseInsensitive)) {
                newsSitemaps.append(url);
            }
        }
    }

    return newsSitemaps;
}

void GoogleNewsSitemapSynthesizer::onRobotsTxtDownloaded(const QUrl& url, const QByteArray& data)
{
    Q_UNUSED(url);

    QString robotsTxt = QString::fromUtf8(data);
    QList<QUrl> robotsSitemaps = parseRobotsSitemaps(robotsTxt, siteBaseUrl);

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: found" << robotsSitemaps.size()
                        << "news sitemaps in robots.txt";

    buildCandidateUrls(robotsSitemaps);
    tryNextCandidate();
}

void GoogleNewsSitemapSynthesizer::onRobotsTxtDownloadError(const QUrl& url, const QString& errorString)
{
    Q_UNUSED(url);
    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: robots.txt fetch failed:" << errorString
                        << ", trying well-known paths";

    buildCandidateUrls({});
    tryNextCandidate();
}

void GoogleNewsSitemapSynthesizer::buildCandidateUrls(const QList<QUrl>& robotsSitemaps)
{
    candidateUrls.clear();

    // Robots.txt sitemaps first (most reliable).
    for (const QUrl& url : robotsSitemaps) {
        candidateUrls.append(url);
    }

    // Then well-known paths as fallback.
    for (const QString& path : newsSitemapPaths()) {
        QUrl candidate = siteBaseUrl;
        candidate.setPath(path);
        // Avoid duplicates from robots.txt.
        if (!candidateUrls.contains(candidate)) {
            candidateUrls.append(candidate);
        }
    }

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: probing" << candidateUrls.size()
                        << "candidate URLs";
}

void GoogleNewsSitemapSynthesizer::tryNextCandidate()
{
    if (candidateUrls.isEmpty()) {
        reportError("No feed found");
        return;
    }

    QUrl url = candidateUrls.takeFirst();
    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: trying" << url;

    downloader = new NetworkDownloadCore({}, this, nullptr);
    connect(downloader, &NetworkDownloadCore::finished,
            this, &GoogleNewsSitemapSynthesizer::onCandidateDownloaded);
    connect(downloader, &NetworkDownloadCore::error,
            this, &GoogleNewsSitemapSynthesizer::onCandidateDownloadError);
    downloader->download(url);
}

void GoogleNewsSitemapSynthesizer::onCandidateDownloaded(const QUrl& url, const QByteArray& data)
{
    QString xml = QString::fromUtf8(data);
    SitemapParser parser(this);
    SitemapParser::SitemapType type = parser.parse(xml);

    if (type == SitemapParser::Invalid) {
        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: invalid XML from" << url
                            << ", trying next candidate";
        tryNextCandidate();
        return;
    }

    if (type == SitemapParser::SitemapIndex) {
        // Store sub-sitemaps sorted by lastmod descending (most recent first).
        sitemapIndexUrl = url;
        accumulatedEntries.clear();
        pendingSubSitemaps = parser.subSitemaps();
        if (pendingSubSitemaps.isEmpty()) {
            qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: empty sitemap index from" << url;
            tryNextCandidate();
            return;
        }

        std::sort(pendingSubSitemaps.begin(), pendingSubSitemaps.end(),
            [](const SubSitemap& a, const SubSitemap& b) {
                bool aValid = a.lastmod.isValid();
                bool bValid = b.lastmod.isValid();
                if (aValid && bValid) {
                    return a.lastmod > b.lastmod;
                }
                return aValid && !bValid;
            });

        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: sitemap index with"
                            << pendingSubSitemaps.size() << "sub-sitemaps";

        tryNextSubSitemap();
        return;
    }

    // UrlSet - check for Google News entries.
    if (!parser.hasNewsEntries()) {
        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: urlset without news entries from" << url;
        tryNextCandidate();
        return;
    }

    processParsedEntries(parser.entries(), url);
}

void GoogleNewsSitemapSynthesizer::onCandidateDownloadError(const QUrl& url, const QString& errorString)
{
    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: download error for" << url
                        << ":" << errorString;
    tryNextCandidate();
}

void GoogleNewsSitemapSynthesizer::tryNextSubSitemap()
{
    if (pendingSubSitemaps.isEmpty()) {
        if (!accumulatedEntries.isEmpty()) {
            // Deduplicate repetitive wire content, then process.
            QList<SitemapEntry> deduped = deduplicateRepetitiveTitles(accumulatedEntries);
            qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: accumulated"
                                << accumulatedEntries.size() << "entries from sub-sitemaps,"
                                << deduped.size() << "after dedup";
            processParsedEntries(deduped, sitemapIndexUrl);
            return;
        }
        // None of the sub-sitemaps had news entries.
        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: no sub-sitemaps with news entries";
        tryNextCandidate();
        return;
    }

    SubSitemap sub = pendingSubSitemaps.takeFirst();
    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: trying sub-sitemap" << sub.url;

    downloader = new NetworkDownloadCore({}, this, nullptr);
    connect(downloader, &NetworkDownloadCore::finished,
            this, &GoogleNewsSitemapSynthesizer::onSubSitemapDownloaded);
    connect(downloader, &NetworkDownloadCore::error,
            this, &GoogleNewsSitemapSynthesizer::onSubSitemapDownloadError);
    downloader->download(sub.url);
}

void GoogleNewsSitemapSynthesizer::onSubSitemapDownloaded(const QUrl& url, const QByteArray& data)
{
    QString xml = QString::fromUtf8(data);
    SitemapParser parser(this);
    SitemapParser::SitemapType type = parser.parse(xml);

    if (type == SitemapParser::UrlSet && parser.hasNewsEntries()) {
        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: sub-sitemap" << url
                            << "has" << parser.entries().size() << "news entries, accumulating";
        accumulatedEntries.append(parser.entries());
    } else {
        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: sub-sitemap" << url
                            << "has no news entries, skipping";
    }

    tryNextSubSitemap();
}

void GoogleNewsSitemapSynthesizer::onSubSitemapDownloadError(const QUrl& url, const QString& errorString)
{
    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: sub-sitemap download error for" << url
                        << ":" << errorString;
    tryNextSubSitemap();
}

QString GoogleNewsSitemapSynthesizer::normalizeLanguage(const QString& lang)
{
    // Normalize ISO 639-3 codes to ISO 639-1. Sites use both:
    // AP News uses "eng"/"spa", BBC uses "en"/"bn"/"hi".
    static const QMap<QString, QString> iso639_3to1 = {
        {"eng", "en"}, {"spa", "es"}, {"fra", "fr"}, {"deu", "de"},
        {"por", "pt"}, {"ita", "it"}, {"jpn", "ja"}, {"zho", "zh"},
        {"kor", "ko"}, {"ara", "ar"}, {"hin", "hi"}, {"rus", "ru"}
    };

    QString normalized = lang.toLower().section('-', 0, 0);
    if (iso639_3to1.contains(normalized)) {
        return iso639_3to1.value(normalized);
    }
    return normalized;
}

void GoogleNewsSitemapSynthesizer::processParsedEntries(const QList<SitemapEntry>& entries,
                                                   const QUrl& sourceUrl)
{
    feedSourceUrl = sourceUrl;

    // Filter to only entries with news:title.
    QList<SitemapEntry> newsEntries;
    for (const SitemapEntry& entry : entries) {
        if (!entry.newsTitle.isEmpty()) {
            newsEntries.append(entry);
        }
    }

    if (newsEntries.isEmpty()) {
        reportError("No feed found");
        return;
    }

    // Use the publication name as the feed title if we don't have a better one.
    if (!newsEntries.first().publicationName.isEmpty()) {
        QString pubName = newsEntries.first().publicationName;
        // Only override generic/empty titles (host names, etc.)
        if (feedTitle.isEmpty() || feedTitle == siteBaseUrl.host()) {
            feedTitle = pubName;
        }
    }

    // Filter by language: find the majority language and keep only matching entries.
    QMap<QString, int> langCounts;
    for (const SitemapEntry& entry : newsEntries) {
        if (!entry.language.isEmpty()) {
            langCounts[normalizeLanguage(entry.language)]++;
        }
    }

    if (!langCounts.isEmpty()) {
        QString majorityLang;
        int maxCount = 0;
        for (auto it = langCounts.cbegin(); it != langCounts.cend(); ++it) {
            if (it.value() > maxCount) {
                maxCount = it.value();
                majorityLang = it.key();
            }
        }

        QList<SitemapEntry> filtered;
        for (const SitemapEntry& entry : newsEntries) {
            if (entry.language.isEmpty()
                || normalizeLanguage(entry.language) == majorityLang) {
                filtered.append(entry);
            }
        }
        newsEntries = filtered;

        qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: filtered to language"
                            << majorityLang << "(" << newsEntries.size() << "entries)";
    }

    // Sort by publication date descending.
    std::sort(newsEntries.begin(), newsEntries.end(),
        [](const SitemapEntry& a, const SitemapEntry& b) {
            // Prefer publicationDate, fall back to lastmod.
            QDateTime dateA = a.publicationDate.isValid() ? a.publicationDate : a.lastmod;
            QDateTime dateB = b.publicationDate.isValid() ? b.publicationDate : b.lastmod;
            bool aValid = dateA.isValid();
            bool bValid = dateB.isValid();
            if (aValid && bValid) {
                return dateA > dateB;
            }
            return aValid && !bValid;
        });

    // Filter by since date for refresh.
    if (isRefresh && since.isValid()) {
        QList<SitemapEntry> recent;
        for (const SitemapEntry& entry : newsEntries) {
            QDateTime date = entry.publicationDate.isValid()
                ? entry.publicationDate : entry.lastmod;
            if (date.isValid() && date > since) {
                recent.append(entry);
            }
        }

        if (recent.isEmpty()) {
            // No new entries since last refresh - emit empty feed.
            _result = new RawFeed(this);
            _result->feedType = RawFeed::GoogleNewsSitemap;
            _result->title = feedTitle;
            _result->url = feedSourceUrl;
            emit done();
            return;
        }

        newsEntries = recent;
    }

    // Limit to MAX_ENTRIES.
    if (newsEntries.size() > MAX_ENTRIES) {
        newsEntries = newsEntries.mid(0, MAX_ENTRIES);
    }

    feedEntries = newsEntries;

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: selected" << feedEntries.size()
                        << "entries from" << feedSourceUrl;

    buildRawFeed();
    emit done();
}

void GoogleNewsSitemapSynthesizer::buildRawFeed()
{
    _result = new RawFeed(this);
    _result->feedType = RawFeed::GoogleNewsSitemap;
    _result->title = feedTitle;
    _result->url = feedSourceUrl;
    _result->siteURL = QUrl(siteBaseUrl.scheme() + "://" + siteBaseUrl.host());

    for (const SitemapEntry& entry : feedEntries) {
        auto* item = new RawNews(_result);
        item->guid = entry.url.toString();
        item->title = entry.newsTitle;
        item->description = QString("");
        item->content = QString("");
        item->url = entry.url;
        item->author = QString("");
        item->timestamp = entry.publicationDate.isValid()
            ? entry.publicationDate
            : (entry.lastmod.isValid() ? entry.lastmod : QDateTime::currentDateTime());

        _result->items.append(item);
    }

    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer: built feed with"
                        << _result->items.size() << "items";
}

void GoogleNewsSitemapSynthesizer::setResultState(RawFeed* result, bool hasError,
                                                   const QString& errorString)
{
    _result = result;
    _hasError = hasError;
    _errorString = errorString;
}

QList<SitemapEntry> GoogleNewsSitemapSynthesizer::deduplicateRepetitiveTitles(
    const QList<SitemapEntry>& entries, int prefixWordCount, int repetitionThreshold)
{
    // Group entries by their first N words (lowercased).
    QMap<QString, QList<int>> prefixGroups;
    for (int i = 0; i < entries.size(); ++i) {
        QStringList words = entries[i].newsTitle.toLower().split(' ', Qt::SkipEmptyParts);
        QString key;
        if (words.size() >= prefixWordCount) {
            key = QStringList(words.mid(0, prefixWordCount)).join(' ');
        } else {
            key = words.join(' ');
        }
        prefixGroups[key].append(i);
    }

    // Build a set of indices to exclude (all but the most recent in large groups).
    QSet<int> excluded;
    for (auto it = prefixGroups.cbegin(); it != prefixGroups.cend(); ++it) {
        const QList<int>& indices = it.value();
        if (indices.size() <= repetitionThreshold) {
            continue;
        }

        // Find the most recent entry in this group.
        int bestIdx = indices.first();
        QDateTime bestDate;
        for (int idx : indices) {
            QDateTime date = entries[idx].publicationDate.isValid()
                ? entries[idx].publicationDate : entries[idx].lastmod;
            if (!bestDate.isValid() || (date.isValid() && date > bestDate)) {
                bestDate = date;
                bestIdx = idx;
            }
        }

        // Exclude all but the best.
        for (int idx : indices) {
            if (idx != bestIdx) {
                excluded.insert(idx);
            }
        }
    }

    // Build filtered list preserving original order.
    QList<SitemapEntry> result;
    for (int i = 0; i < entries.size(); ++i) {
        if (!excluded.contains(i)) {
            result.append(entries[i]);
        }
    }
    return result;
}

void GoogleNewsSitemapSynthesizer::reportError(const QString& error)
{
    _hasError = true;
    _errorString = error;
    qCDebug(logUtility) << "GoogleNewsSitemapSynthesizer error:" << error;
    emit done();
}
