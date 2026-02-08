#include "SyncService.h"
#include "../FangApp.h"
#include "../models/FeedItem.h"
#include "../models/FangSettings.h"
#include "../db/DB.h"

#include <QLocale>
#include <QSqlQuery>
#include <QSqlError>

Q_LOGGING_CATEGORY(logSync, "fang.sync")

SyncService::SyncService(FangApp* app, FangObject *parent)
    : FangObject(parent)
    , app(app)
    , syncTimer(new QTimer(this))
{
    connect(syncTimer, &QTimer::timeout, this, &SyncService::onSyncTimer);
}

SyncService::~SyncService()
{
    if (_provider) {
        delete _provider;
    }
}

void SyncService::setProvider(CloudStorageProvider* provider)
{
    if (_provider) {
        disconnectProvider();
        delete _provider;
    }

    provider = provider;

    if (_provider) {
        _provider->setParent(this);
        connectProvider();
    }
}

void SyncService::connectProvider()
{
    if (!_provider) {
        return;
    }

    connect(_provider, &CloudStorageProvider::authenticated,
            this, &SyncService::onAuthenticated);
    connect(_provider, &CloudStorageProvider::authenticationFailed,
            this, &SyncService::onAuthenticationFailed);
    connect(_provider, &CloudStorageProvider::fileDownloaded,
            this, &SyncService::onFileDownloaded);
    connect(_provider, &CloudStorageProvider::fileUploaded,
            this, &SyncService::onFileUploaded);
    connect(_provider, &CloudStorageProvider::conflictDetected,
            this, &SyncService::onConflictDetected);
}

void SyncService::disconnectProvider()
{
    if (!_provider) {
        return;
    }

    disconnect(_provider, nullptr, this, nullptr);
}

void SyncService::setEnabled(bool enabled)
{
    if (this->enabled == enabled) {
        return;
    }

    this->enabled = enabled;
    emit enabledChanged();

    if (this->enabled) {
        syncTimer->start(intervalMinutes * 60 * 1000);
        // Trigger initial sync
        sync();
    } else {
        syncTimer->stop();
    }
}

QString SyncService::lastSyncTimeString() const
{
    if (!lastSyncAt.isValid()) {
        return tr("Never");
    }
    return QLocale().toString(lastSyncAt, QLocale::ShortFormat);
}

void SyncService::setSyncInterval(int minutes)
{
    intervalMinutes = qMax(1, minutes);
    if (syncTimer->isActive()) {
        syncTimer->setInterval(intervalMinutes * 60 * 1000);
    }
}

void SyncService::sync()
{
    if (syncing) {
        qCDebug(logSync) << "Sync already in progress, ignoring request";
        return;
    }

    if (!_provider) {
        setLastError(tr("No sync provider configured"));
        emit syncFailed(_lastError);
        return;
    }

    if (!_provider->isAuthenticated()) {
        qCDebug(logSync) << "Not authenticated, requesting authentication";
        emit authenticationRequired();
        return;
    }

    qCInfo(logSync) << "Starting sync...";
    setSyncing(true);
    emit syncStarted();

    startDownload();
}

void SyncService::authenticate()
{
    if (!_provider) {
        setLastError(tr("No sync provider configured"));
        return;
    }

    _provider->authenticate();
}

void SyncService::signOut()
{
    if (_provider) {
        _provider->signOut();
    }

    setEnabled(false);
    emit signedOut();
}

void SyncService::onAuthenticated()
{
    qCInfo(logSync) << "Authentication successful";
    emit authenticated();

    // If sync was pending, start it now
    if (enabled) {
        sync();
    }
}

void SyncService::onAuthenticationFailed(const QString& error)
{
    qCWarning(logSync) << "Authentication failed:" << error;
    setLastError(error);
    emit syncFailed(error);
}

void SyncService::onFileDownloaded(const QString& fileName,
                                   const CloudStorageProvider::OperationResult& result)
{
    if (fileName != SYNC_FILE_NAME) {
        return;
    }

    if (state != SyncState::Downloading && state != SyncState::ResolvingConflict) {
        return;
    }

    if (!result.success) {
        if (result.errorMessage.contains("not found", Qt::CaseInsensitive)) {
            // No remote file yet - this is fine, we'll create it
            qCDebug(logSync) << "No remote sync file found, will create new";
            payloadRemote = SyncData::SyncPayload();
            currentEtag.clear();
        } else {
            finishSync(false, result.errorMessage);
            return;
        }
    } else {
        currentEtag = result.metadata.etag;
        processDownloadedData(result.data);
    }

    uploadMergedData();
}

void SyncService::onFileUploaded(const QString& fileName,
                                 const CloudStorageProvider::OperationResult& result)
{
    if (fileName != SYNC_FILE_NAME) return;
    if (state != SyncState::Uploading) return;

    if (!result.success) {
        finishSync(false, result.errorMessage);
        return;
    }

    currentEtag = result.metadata.etag;
    finishSync(true);
}

void SyncService::onConflictDetected(const QString& fileName,
                                     const CloudStorageProvider::FileMetadata& serverMeta)
{
    Q_UNUSED(serverMeta);
    if (fileName != SYNC_FILE_NAME) return;

    qCInfo(logSync) << "Conflict detected, re-downloading and merging";

    // Re-download and merge
    state = SyncState::ResolvingConflict;
    _provider->downloadFile(SYNC_FILE_NAME);
}

void SyncService::onSyncTimer()
{
    if (enabled && !syncing) {
        sync();
    }
}

void SyncService::setSyncing(bool syncing)
{
    if (this->syncing == syncing) {
        return;
    }

    this->syncing = syncing;
    emit syncingChanged();
}

void SyncService::setLastError(const QString& error)
{
    if (_lastError == error) {
        return;
    }

    _lastError = error;
    emit lastErrorChanged();
}

void SyncService::startDownload()
{
    state = SyncState::Downloading;
    payloadLocal = buildLocalPayload();
    _provider->downloadFile(SYNC_FILE_NAME);
}

void SyncService::processDownloadedData(const QByteArray& data)
{
    bool ok = false;
    payloadRemote = SyncData::SyncPayload::fromJson(data, &ok);

    if (!ok) {
        qCWarning(logSync) << "Failed to parse remote sync data";
        // Treat as empty - our local data will be uploaded
        payloadRemote = SyncData::SyncPayload();
    }

    // Merge: remote into local (local wins ties due to our deviceId)
    payloadMerged = payloadLocal;
    payloadMerged.merge(payloadRemote);

    // Apply any changes from remote to local database
    applyPayloadToLocal(payloadMerged);
}

void SyncService::uploadMergedData()
{
    state = SyncState::Uploading;

    // Update timestamp
    payloadMerged.lastModified = QDateTime::currentMSecsSinceEpoch();

    QByteArray data = payloadMerged.toJson();
    _provider->uploadFile(SYNC_FILE_NAME, data, currentEtag);
}

void SyncService::finishSync(bool success, const QString& error)
{
    state = SyncState::Idle;
    setSyncing(false);

    if (success) {
        lastSyncAt = QDateTime::currentDateTime();
        emit lastSyncTimeChanged();
        setLastError(QString());
        qCInfo(logSync) << "Sync completed successfully";
        emit syncCompleted();
    } else {
        setLastError(error);
        qCWarning(logSync) << "Sync failed:" << error;
        emit syncFailed(error);
    }
}

SyncData::SyncPayload SyncService::buildLocalPayload()
{
    SyncData::SyncPayload payload;
    qint64 now = QDateTime::currentMSecsSinceEpoch();

    if (!app) {
        qCWarning(logSync) << "No FangApp available, returning empty payload";
        return payload;
    }

    QSqlDatabase db = DB::instance()->db();

    // -------------------------------------------------------------------------
    // 1. Load all feeds
    // -------------------------------------------------------------------------
    QSqlQuery feedQuery(db);
    feedQuery.prepare(R"(
        SELECT id, title, url, siteURL, user_url, ordinal,
               is_folder, folder_open, parent_folder, minutesToUpdate
        FROM FeedItemTable
    )");

    if (!feedQuery.exec()) {
        qCWarning(logSync) << "Failed to query feeds:" << feedQuery.lastError().text();
        return payload;
    }

    // Map local feed IDs to UUIDs for bookmark/pin lookups
    QMap<qint64, QString> feedIdToUuid;
    // Map folder IDs to UUIDs for parent folder mapping
    QMap<qint64, QString> folderIdToUuid;

    while (feedQuery.next()) {
        qint64 feedId = feedQuery.value("id").toLongLong();
        bool isFolder = feedQuery.value("is_folder").toBool();

        SyncData::FeedData feed;

        // Use user_url if available, otherwise fall back to url
        QString userUrl = feedQuery.value("user_url").toString();
        QString parsedUrl = feedQuery.value("url").toString();
        feed.url = userUrl.isEmpty() ? parsedUrl : userUrl;

        // Generate UUID from URL (or title for folders)
        if (isFolder) {
            QString title = feedQuery.value("title").toString();
            feed.uuid = SyncData::feedUuidFromUrl("folder:" + title + ":" + QString::number(feedId));
            folderIdToUuid[feedId] = feed.uuid;
        } else {
            feed.uuid = SyncData::feedUuidFromUrl(feed.url);
        }

        feedIdToUuid[feedId] = feed.uuid;

        feed.title = feedQuery.value("title").toString();
        feed.siteUrl = feedQuery.value("siteURL").toString();
        feed.ordinal = feedQuery.value("ordinal").toInt();
        feed.isFolder = isFolder;
        feed.folderOpen = feedQuery.value("folder_open").toBool();
        feed.minutesToUpdate = feedQuery.value("minutesToUpdate").toInt();
        feed.timestamp = now;  // We don't track per-feed modification time, use now
        feed.deviceId = payload.deviceId;
        feed.deleted = false;

        // Parent folder will be resolved after we have all folders
        qint64 parentFolderId = feedQuery.value("parent_folder").toLongLong();
        if (parentFolderId >= 0) {
            feed.parentFolderUuid = QString::number(parentFolderId);  // Temporary, resolved below
        }

        payload.feeds[feed.uuid] = feed;
    }

    // Resolve parent folder UUIDs
    for (auto& feed : payload.feeds) {
        if (!feed.parentFolderUuid.isEmpty()) {
            qint64 parentId = feed.parentFolderUuid.toLongLong();
            if (folderIdToUuid.contains(parentId)) {
                feed.parentFolderUuid = folderIdToUuid[parentId];
            } else {
                feed.parentFolderUuid.clear();  // Parent doesn't exist
            }
        }
    }

    qCDebug(logSync) << "Built" << payload.feeds.size() << "feeds for sync";

    // -------------------------------------------------------------------------
    // 2. Load bookmarks (bookmark_id in FeedItemTable points to a NewsItem)
    // -------------------------------------------------------------------------
    QSqlQuery bookmarkQuery(db);
    bookmarkQuery.prepare(R"(
        SELECT f.id as feed_id, f.bookmark_id, n.guid, n.timestamp
        FROM FeedItemTable f
        LEFT JOIN NewsItemTable n ON f.bookmark_id = n.id
        WHERE f.bookmark_id >= 0 AND n.id IS NOT NULL
    )");

    if (!bookmarkQuery.exec()) {
        qCWarning(logSync) << "Failed to query bookmarks:" << bookmarkQuery.lastError().text();
    } else {
        while (bookmarkQuery.next()) {
            qint64 feedId = bookmarkQuery.value("feed_id").toLongLong();
            QString feedUuid = feedIdToUuid.value(feedId);

            if (feedUuid.isEmpty()) continue;

            SyncData::BookmarkData bookmark;
            bookmark.feedUuid = feedUuid;
            bookmark.newsGuid = bookmarkQuery.value("guid").toString();
            bookmark.newsTimestamp = bookmarkQuery.value("timestamp").toLongLong() * 1000;  // Convert to ms
            bookmark.timestamp = now;
            bookmark.deviceId = payload.deviceId;

            payload.bookmarks[feedUuid] = bookmark;
        }
    }

    qCDebug(logSync) << "Built" << payload.bookmarks.size() << "bookmarks for sync";

    // -------------------------------------------------------------------------
    // 3. Load pinned items
    // -------------------------------------------------------------------------
    QSqlQuery pinQuery(db);
    pinQuery.prepare(R"(
        SELECT feed_id, guid FROM NewsItemTable WHERE pinned = 1
    )");

    if (!pinQuery.exec()) {
        qCWarning(logSync) << "Failed to query pins:" << pinQuery.lastError().text();
    } else {
        while (pinQuery.next()) {
            qint64 feedId = pinQuery.value("feed_id").toLongLong();
            QString feedUuid = feedIdToUuid.value(feedId);
            QString newsGuid = pinQuery.value("guid").toString();

            if (feedUuid.isEmpty()) continue;

            SyncData::PinData pin;
            pin.feedUuid = feedUuid;
            pin.newsGuid = newsGuid;
            pin.pinned = true;
            pin.timestamp = now;
            pin.deviceId = payload.deviceId;

            QString key = SyncData::pinKey(feedUuid, newsGuid);
            payload.pins[key] = pin;
        }
    }

    qCDebug(logSync) << "Built" << payload.pins.size() << "pins for sync";

    // -------------------------------------------------------------------------
    // 4. Load settings
    // -------------------------------------------------------------------------
    FangSettings* settings = app->getSettings();
    if (settings) {
        payload.settings.style = settings->getStyle();
        payload.settings.fontSize = settings->getFontSize();
        payload.settings.refreshInterval = settings->getRefresh();
        payload.settings.cacheLength = settings->getCacheLength();
        payload.settings.timestamp = now;
        payload.settings.deviceId = payload.deviceId;
    }

    qCDebug(logSync) << "Built settings for sync";

    return payload;
}


void SyncService::applyPayloadToLocal(const SyncData::SyncPayload& payload)
{
    if (!app) {
        qCWarning(logSync) << "No FangApp available, cannot apply payload";
        return;
    }

    QSqlDatabase db = DB::instance()->db();

    // Build a map of existing feeds by URL for matching
    QMap<QString, qint64> urlToFeedId;
    QSqlQuery existingQuery(db);
    existingQuery.prepare("SELECT id, url, user_url FROM FeedItemTable WHERE is_folder = 0");
    if (existingQuery.exec()) {
        while (existingQuery.next()) {
            qint64 id = existingQuery.value("id").toLongLong();
            QString userUrl = existingQuery.value("user_url").toString();
            QString url = existingQuery.value("url").toString();

            QString key = userUrl.isEmpty() ? url : userUrl;
            if (!key.isEmpty()) {
                urlToFeedId[SyncData::feedUuidFromUrl(key)] = id;
            }
        }
    }

    int feedsAdded = 0;
    int feedsUpdated = 0;
    int bookmarksUpdated = 0;
    int pinsUpdated = 0;

    // -------------------------------------------------------------------------
    // 1. Apply feed changes
    // -------------------------------------------------------------------------
    for (const auto& feed : payload.feeds) {
        if (feed.deleted) {
            // TODO: Handle feed deletion
            // This is complex because we'd need to remove the feed from the UI
            // For now, skip deleted feeds
            continue;
        }

        if (feed.isFolder) {
            // TODO: Handle folder sync
            // Folders are more complex because they don't have URLs
            continue;
        }

        qint64 existingId = urlToFeedId.value(feed.uuid, -1);

        if (existingId < 0) {
            // New feed - would need to add it
            // This requires the full AddFeedOperation which validates the feed
            // For now, log that we found a new feed
            qCInfo(logSync) << "New feed from sync:" << feed.url << feed.title;
            feedsAdded++;

            // TODO: Trigger AddFeedOperation for new feeds
            // This is complex because:
            // 1. We need to validate the feed URL
            // 2. We need to fetch and parse the feed
            // 3. We need to handle duplicates
            // For a first implementation, we might skip auto-adding feeds
            // and just sync bookmarks/pins/settings for existing feeds
        } else {
            // Existing feed - update if needed
            // For now, we only update the ordinal and folder assignment
            // Title updates are tricky because the user may have customized it

            // Check if this is newer than what we had locally
            // (We don't have per-feed timestamps locally, so we trust the sync data)

            qCDebug(logSync) << "Existing feed matched:" << feed.url;
            feedsUpdated++;
        }
    }

    // -------------------------------------------------------------------------
    // 2. Apply bookmark changes
    // -------------------------------------------------------------------------
    for (const auto& bookmark : payload.bookmarks) {
        qint64 feedId = urlToFeedId.value(bookmark.feedUuid, -1);
        if (feedId < 0) {
            // Feed doesn't exist locally, skip
            continue;
        }

        // Find the news item by GUID
        QSqlQuery newsQuery(db);
        newsQuery.prepare(R"(
            SELECT id FROM NewsItemTable
            WHERE feed_id = :feed_id AND guid = :guid
        )");
        newsQuery.bindValue(":feed_id", feedId);
        newsQuery.bindValue(":guid", bookmark.newsGuid);

        if (newsQuery.exec() && newsQuery.next()) {
            qint64 newsId = newsQuery.value("id").toLongLong();

            // Update the bookmark
            QSqlQuery updateQuery(db);
            updateQuery.prepare("UPDATE FeedItemTable SET bookmark_id = :news_id WHERE id = :feed_id");
            updateQuery.bindValue(":news_id", newsId);
            updateQuery.bindValue(":feed_id", feedId);

            if (updateQuery.exec()) {
                qCDebug(logSync) << "Updated bookmark for feed" << feedId << "to news" << newsId;
                bookmarksUpdated++;

                // Update the in-memory FeedItem if it exists
                FeedItem* feedItem = app->feedForId(feedId);
                if (feedItem) {
                    feedItem->setBookmark(newsId);
                }
            }
        } else {
            qCDebug(logSync) << "Bookmark news item not found locally:" << bookmark.newsGuid;
        }
    }

    // -------------------------------------------------------------------------
    // 3. Apply pin changes
    // -------------------------------------------------------------------------
    for (const auto& pin : payload.pins) {
        qint64 feedId = urlToFeedId.value(pin.feedUuid, -1);
        if (feedId < 0) {
            continue;
        }

        // Find and update the news item
        QSqlQuery updateQuery(db);
        updateQuery.prepare(R"(
            UPDATE NewsItemTable SET pinned = :pinned
            WHERE feed_id = :feed_id AND guid = :guid
        )");
        updateQuery.bindValue(":pinned", pin.pinned ? 1 : 0);
        updateQuery.bindValue(":feed_id", feedId);
        updateQuery.bindValue(":guid", pin.newsGuid);

        if (updateQuery.exec() && updateQuery.numRowsAffected() > 0) {
            qCDebug(logSync) << "Updated pin for" << pin.newsGuid << "to" << pin.pinned;
            pinsUpdated++;
        }
    }

    // -------------------------------------------------------------------------
    // 4. Apply settings changes
    // -------------------------------------------------------------------------
    FangSettings* settings = app->getSettings();
    if (settings && payload.settings.timestamp > 0) {
        // Only apply settings if they're from a different device and newer
        // For now, we'll apply them if they differ
        bool settingsChanged = false;

        if (!payload.settings.style.isEmpty() &&
            payload.settings.style != settings->getStyle()) {
            settings->setStyle(payload.settings.style);
            settingsChanged = true;
        }

        if (!payload.settings.fontSize.isEmpty() &&
            payload.settings.fontSize != settings->getFontSize()) {
            settings->setFontSize(payload.settings.fontSize);
            settingsChanged = true;
        }

        if (!payload.settings.refreshInterval.isEmpty() &&
            payload.settings.refreshInterval != settings->getRefresh()) {
            settings->setRefresh(payload.settings.refreshInterval);
            settingsChanged = true;
        }

        if (!payload.settings.cacheLength.isEmpty() &&
            payload.settings.cacheLength != settings->getCacheLength()) {
            settings->setCacheLength(payload.settings.cacheLength);
            settingsChanged = true;
        }

        if (settingsChanged) {
            qCInfo(logSync) << "Applied settings from sync";
        }
    }

    qCInfo(logSync) << "Applied payload:"
                    << feedsAdded << "feeds added,"
                    << feedsUpdated << "feeds matched,"
                    << bookmarksUpdated << "bookmarks updated,"
                    << pinsUpdated << "pins updated";
}
