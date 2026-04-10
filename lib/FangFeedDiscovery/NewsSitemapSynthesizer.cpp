#include "NewsSitemapSynthesizer.h"
#include "NetworkDownloadCore.h"
#include "PageMetadataExtractor.h"
#include "WebPageGrabber.h"
#include "FeedDiscoveryLogging.h"

#include <algorithm>
#include <QSet>

static QString stripWww(const QString& host)
{
    if (host.startsWith("www.")) {
        return host.mid(4);
    }
    return host;
}

NewsSitemapSynthesizer::NewsSitemapSynthesizer(QObject* parent)
    : QObject(parent)
    , isRefresh(false)
    , state(IDLE)
    , _hasError(false)
    , _result(nullptr)
    , downloader(new NetworkDownloadCore({}, this, nullptr))
    , descriptionDownloader(nullptr)
{
    connect(downloader, &NetworkDownloadCore::finished,
            this, &NewsSitemapSynthesizer::onDownloadFinished);
    connect(downloader, &NetworkDownloadCore::error,
            this, &NewsSitemapSynthesizer::onDownloadError);
}

NewsSitemapSynthesizer::~NewsSitemapSynthesizer()
{
}

QStringList NewsSitemapSynthesizer::newsSitemapPaths()
{
    return {
        "/news-sitemap.xml",
        "/sitemap_news.xml",
        "/news-sitemap-content.xml"
    };
}

void NewsSitemapSynthesizer::synthesize(const QUrl& siteUrl, const QString& siteTitle)
{
    isRefresh = false;
    feedTitle = siteTitle;
    since = QDateTime();

    // Build base URL for probing.
    siteBaseUrl.setScheme(siteUrl.scheme());
    siteBaseUrl.setHost(siteUrl.host());

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: starting discovery for" << siteBaseUrl;

    // Start by fetching robots.txt to discover news sitemap URLs.
    fetchRobotsTxt();
}

void NewsSitemapSynthesizer::synthesize(const QUrl& sitemapUrl, const QString& feedTitle,
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

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: refreshing from" << sitemapUrl
                        << "since" << since;

    tryNextCandidate();
}

void NewsSitemapSynthesizer::fetchRobotsTxt()
{
    QUrl robotsUrl = siteBaseUrl;
    robotsUrl.setPath("/robots.txt");

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: fetching" << robotsUrl;

    state = FETCHING_ROBOTS_TXT;
    downloader->download(robotsUrl);
}

QList<QUrl> NewsSitemapSynthesizer::parseRobotsSitemaps(const QString& robotsTxt,
                                                         const QUrl& siteBaseUrl)
{
    QList<QUrl> newsSitemaps;
    QList<QUrl> genericSitemaps;
    QStringList lines = robotsTxt.split('\n');

    for (const QString& line : lines) {
        QString trimmed = line.trimmed();
        if (trimmed.startsWith("Sitemap:", Qt::CaseInsensitive)) {
            QString urlStr = trimmed.mid(8).trimmed();
            QUrl url(urlStr);
            if (url.isValid() && stripWww(url.host()) == stripWww(siteBaseUrl.host())) {
                if (url.path().contains("news", Qt::CaseInsensitive)) {
                    newsSitemaps.append(url);
                } else {
                    genericSitemaps.append(url);
                }
            }
        }
    }

    // News-specific sitemaps first, then generic ones (which may be sitemap
    // indexes that reference a news sitemap, e.g. ESPN's /sitemap.xml).
    newsSitemaps.append(genericSitemaps);
    return newsSitemaps;
}

void NewsSitemapSynthesizer::onDownloadFinished(const QUrl& url, const QByteArray& data)
{
    switch (state) {
    case FETCHING_ROBOTS_TXT:
        handleRobotsTxtResponse(url, data);
        break;
    case FETCHING_CANDIDATE:
        handleCandidateResponse(url, data);
        break;
    case FETCHING_SUB_SITEMAP:
        handleSubSitemapResponse(url, data);
        break;
    case IDLE:
    case FETCHING_DESCRIPTIONS:
        break;
    }
}

void NewsSitemapSynthesizer::onDownloadError(const QUrl& url, const QString& errorString)
{
    switch (state) {
    case FETCHING_ROBOTS_TXT:
        handleRobotsTxtError(url, errorString);
        break;
    case FETCHING_CANDIDATE:
        handleCandidateError(url, errorString);
        break;
    case FETCHING_SUB_SITEMAP:
        handleSubSitemapError(url, errorString);
        break;
    case IDLE:
    case FETCHING_DESCRIPTIONS:
        break;
    }
}

void NewsSitemapSynthesizer::handleRobotsTxtResponse(const QUrl& url, const QByteArray& data)
{
    Q_UNUSED(url);

    QString robotsTxt = QString::fromUtf8(data);
    QList<QUrl> robotsSitemaps = parseRobotsSitemaps(robotsTxt, siteBaseUrl);

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: found" << robotsSitemaps.size()
                        << "news sitemaps in robots.txt";

    buildCandidateUrls(robotsSitemaps);
    tryNextCandidate();
}

void NewsSitemapSynthesizer::handleRobotsTxtError(const QUrl& url, const QString& errorString)
{
    Q_UNUSED(url);
    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: robots.txt fetch failed:" << errorString
                        << ", trying well-known paths";

    buildCandidateUrls({});
    tryNextCandidate();
}

void NewsSitemapSynthesizer::buildCandidateUrls(const QList<QUrl>& robotsSitemaps)
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

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: probing" << candidateUrls.size()
                        << "candidate URLs";
}

void NewsSitemapSynthesizer::tryNextCandidate()
{
    if (candidateUrls.isEmpty()) {
        reportError("No feed found");
        return;
    }

    QUrl url = candidateUrls.takeFirst();
    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: trying" << url;

    state = FETCHING_CANDIDATE;
    downloader->download(url);
}

void NewsSitemapSynthesizer::handleCandidateResponse(const QUrl& url, const QByteArray& data)
{
    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(data);

    if (type == SitemapParser::Invalid) {
        qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: invalid XML from" << url
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
            qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: empty sitemap index from" << url;
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

        qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: sitemap index with"
                            << pendingSubSitemaps.size() << "sub-sitemaps";

        tryNextSubSitemap();
        return;
    }

    // UrlSet - check for news entries.
    if (!parser.hasNewsEntries()) {
        qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: urlset without news entries from" << url;
        tryNextCandidate();
        return;
    }

    processParsedEntries(parser.entries(), url);
}

void NewsSitemapSynthesizer::handleCandidateError(const QUrl& url, const QString& errorString)
{
    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: download error for" << url
                        << ":" << errorString;
    tryNextCandidate();
}

void NewsSitemapSynthesizer::tryNextSubSitemap()
{
    if (pendingSubSitemaps.isEmpty()) {
        if (!accumulatedEntries.isEmpty()) {
            // Deduplicate repetitive wire content, then process.
            QList<SitemapEntry> deduped = deduplicateRepetitiveTitles(accumulatedEntries);
            qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: accumulated"
                                << accumulatedEntries.size() << "entries from sub-sitemaps,"
                                << deduped.size() << "after dedup";
            processParsedEntries(deduped, sitemapIndexUrl);
            return;
        }
        // None of the sub-sitemaps had news entries.
        qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: no sub-sitemaps with news entries";
        tryNextCandidate();
        return;
    }

    SubSitemap sub = pendingSubSitemaps.takeFirst();
    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: trying sub-sitemap" << sub.url;

    state = FETCHING_SUB_SITEMAP;
    downloader->download(sub.url);
}

void NewsSitemapSynthesizer::handleSubSitemapResponse(const QUrl& url, const QByteArray& data)
{
    SitemapParser parser;
    SitemapParser::SitemapType type = parser.parse(data);

    if (type == SitemapParser::UrlSet && parser.hasNewsEntries()) {
        qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: sub-sitemap" << url
                            << "has" << parser.entries().size() << "news entries, accumulating";
        accumulatedEntries.append(parser.entries());
    } else {
        qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: sub-sitemap" << url
                            << "has no news entries, skipping";
    }

    tryNextSubSitemap();
}

void NewsSitemapSynthesizer::handleSubSitemapError(const QUrl& url, const QString& errorString)
{
    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: sub-sitemap download error for" << url
                        << ":" << errorString;
    tryNextSubSitemap();
}

QString NewsSitemapSynthesizer::normalizeLanguage(const QString& lang)
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

void NewsSitemapSynthesizer::filterByLanguage(QList<SitemapEntry>& entries)
{
    QMap<QString, int> langCounts;
    for (const SitemapEntry& entry : entries) {
        if (!entry.language.isEmpty()) {
            langCounts[normalizeLanguage(entry.language)]++;
        }
    }

    if (langCounts.isEmpty()) {
        return;
    }

    QString majorityLang;
    int maxCount = 0;
    for (auto it = langCounts.cbegin(); it != langCounts.cend(); ++it) {
        if (it.value() > maxCount) {
            maxCount = it.value();
            majorityLang = it.key();
        }
    }

    QList<SitemapEntry> filtered;
    for (const SitemapEntry& entry : entries) {
        if (entry.language.isEmpty()
            || normalizeLanguage(entry.language) == majorityLang) {
            filtered.append(entry);
        }
    }
    entries = filtered;

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: filtered to language"
                        << majorityLang << "(" << entries.size() << "entries)";
}

bool NewsSitemapSynthesizer::filterBySinceDate(QList<SitemapEntry>& entries)
{
    if (!isRefresh || !since.isValid()) {
        return false;
    }

    QList<SitemapEntry> recent;
    for (const SitemapEntry& entry : entries) {
        QDateTime date = entry.publicationDate.isValid()
            ? entry.publicationDate : entry.lastmod;
        if (date.isValid() && date > since) {
            recent.append(entry);
        }
    }
    entries = recent;
    return true;
}

void NewsSitemapSynthesizer::processParsedEntries(const QList<SitemapEntry>& entries,
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
        if (feedTitle.isEmpty() || feedTitle == siteBaseUrl.host()) {
            feedTitle = pubName;
        }
    }

    filterByLanguage(newsEntries);

    // Sort by publication date descending.
    std::sort(newsEntries.begin(), newsEntries.end(),
        [](const SitemapEntry& a, const SitemapEntry& b) {
            QDateTime dateA = a.publicationDate.isValid() ? a.publicationDate : a.lastmod;
            QDateTime dateB = b.publicationDate.isValid() ? b.publicationDate : b.lastmod;
            bool aValid = dateA.isValid();
            bool bValid = dateB.isValid();
            if (aValid && bValid) {
                return dateA > dateB;
            }
            return aValid && !bValid;
        });

    if (filterBySinceDate(newsEntries) && newsEntries.isEmpty()) {
        // No new entries since last refresh - emit empty feed.
        state = IDLE;
        _result = std::make_shared<RawFeed>();
        _result->feedType = RawFeed::GoogleNewsSitemap;
        _result->title = feedTitle;
        _result->url = feedSourceUrl;
        emit done();
        return;
    }

    // Limit to MAX_ENTRIES.
    if (newsEntries.size() > MAX_ENTRIES) {
        newsEntries = newsEntries.mid(0, MAX_ENTRIES);
    }

    feedEntries = newsEntries;

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: selected" << feedEntries.size()
                        << "entries from" << feedSourceUrl;

    fetchDescriptions();
}

void NewsSitemapSynthesizer::fetchDescriptions()
{
    state = FETCHING_DESCRIPTIONS;
    fetchedDescriptions.clear();

    QList<QUrl> urls;
    for (const SitemapEntry& entry : feedEntries) {
        urls.append(entry.url);
    }

    descriptionDownloader = new BatchDownloadCore(10000, 5, this);
    connect(descriptionDownloader, &BatchDownloadCore::finished,
            this, &NewsSitemapSynthesizer::onDescriptionsReady);
    descriptionDownloader->download(urls);
}

void NewsSitemapSynthesizer::onDescriptionsReady()
{
    auto results = descriptionDownloader->results();
    descriptionDownloader->deleteLater();
    descriptionDownloader = nullptr;

    for (auto it = results.constBegin(); it != results.constEnd(); ++it) {
        if (!it.value().success) {
            continue;
        }

        QString xhtml = WebPageGrabber::htmlToXhtml(it.value().data);
        if (xhtml.isEmpty()) {
            continue;
        }

        PageMetadata meta = PageMetadataExtractor::extract(xhtml);
        if (!meta.description.isEmpty()) {
            fetchedDescriptions[it.key()] = meta.description;
        }
    }

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: fetched" << fetchedDescriptions.size()
                        << "descriptions from" << results.size() << "articles";

    state = IDLE;
    buildRawFeed();
    emit done();
}

void NewsSitemapSynthesizer::buildRawFeed()
{
    _result = std::make_shared<RawFeed>();
    _result->feedType = RawFeed::GoogleNewsSitemap;
    _result->title = feedTitle;
    _result->subtitle = "";
    _result->url = feedSourceUrl;
    _result->siteURL = QUrl(siteBaseUrl.scheme() + "://" + siteBaseUrl.host());

    for (const SitemapEntry& entry : feedEntries) {
        auto item = std::make_shared<RawNews>();
        item->guid = entry.url.toString();
        item->title = entry.newsTitle;
        item->author = entry.publicationName;
        item->url = entry.url;
        item->timestamp = entry.publicationDate.isValid()
            ? entry.publicationDate
            : (entry.lastmod.isValid() ? entry.lastmod : QDateTime::currentDateTime());

        if (fetchedDescriptions.contains(entry.url)) {
            item->description = fetchedDescriptions.value(entry.url);
        }

        // Embed the sitemap thumbnail image in the content so it flows
        // through the normal HTML sanitizer and image pipeline.
        if (entry.imageUrl.isValid()) {
            item->content = "<img src=\"" + entry.imageUrl.toString() + "\"/>";
        }

        _result->items.append(item);
    }

    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer: built feed with"
                        << _result->items.size() << "items";
}

void NewsSitemapSynthesizer::setResultState(std::shared_ptr<RawFeed> result, bool hasError,
                                                   const QString& errorString)
{
    _result = result;
    _hasError = hasError;
    _errorString = errorString;
}

QList<SitemapEntry> NewsSitemapSynthesizer::deduplicateRepetitiveTitles(
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

void NewsSitemapSynthesizer::reportError(const QString& error)
{
    state = IDLE;
    _hasError = true;
    _errorString = error;
    qCDebug(logFeedDiscovery) << "NewsSitemapSynthesizer error:" << error;
    emit done();
}
