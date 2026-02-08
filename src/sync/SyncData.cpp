#include "SyncData.h"

#include <QCryptographicHash>
#include <QUuid>
#include <QSettings>

namespace SyncData {

// -----------------------------------------------------------------------------
// FeedData
// -----------------------------------------------------------------------------

QJsonObject FeedData::toJson() const
{
    QJsonObject obj;
    obj["uuid"] = uuid;
    obj["url"] = url;
    obj["title"] = title;
    obj["siteUrl"] = siteUrl;
    obj["ordinal"] = ordinal;
    obj["parentFolderUuid"] = parentFolderUuid;
    obj["isFolder"] = isFolder;
    obj["folderOpen"] = folderOpen;
    obj["minutesToUpdate"] = minutesToUpdate;
    obj["timestamp"] = timestamp;
    obj["deviceId"] = deviceId;
    obj["deleted"] = deleted;
    return obj;
}

FeedData FeedData::fromJson(const QJsonObject& json)
{
    FeedData data;
    data.uuid = json["uuid"].toString();
    data.url = json["url"].toString();
    data.title = json["title"].toString();
    data.siteUrl = json["siteUrl"].toString();
    data.ordinal = json["ordinal"].toInt();
    data.parentFolderUuid = json["parentFolderUuid"].toString();
    data.isFolder = json["isFolder"].toBool();
    data.folderOpen = json["folderOpen"].toBool(true);
    data.minutesToUpdate = json["minutesToUpdate"].toInt();
    data.timestamp = json["timestamp"].toVariant().toLongLong();
    data.deviceId = json["deviceId"].toString();
    data.deleted = json["deleted"].toBool();
    return data;
}

// -----------------------------------------------------------------------------
// BookmarkData
// -----------------------------------------------------------------------------

QJsonObject BookmarkData::toJson() const
{
    QJsonObject obj;
    obj["feedUuid"] = feedUuid;
    obj["newsGuid"] = newsGuid;
    obj["newsTimestamp"] = newsTimestamp;
    obj["timestamp"] = timestamp;
    obj["deviceId"] = deviceId;
    return obj;
}

BookmarkData BookmarkData::fromJson(const QJsonObject& json)
{
    BookmarkData data;
    data.feedUuid = json["feedUuid"].toString();
    data.newsGuid = json["newsGuid"].toString();
    data.newsTimestamp = json["newsTimestamp"].toVariant().toLongLong();
    data.timestamp = json["timestamp"].toVariant().toLongLong();
    data.deviceId = json["deviceId"].toString();
    return data;
}

// -----------------------------------------------------------------------------
// PinData
// -----------------------------------------------------------------------------

QJsonObject PinData::toJson() const
{
    QJsonObject obj;
    obj["feedUuid"] = feedUuid;
    obj["newsGuid"] = newsGuid;
    obj["pinned"] = pinned;
    obj["timestamp"] = timestamp;
    obj["deviceId"] = deviceId;
    return obj;
}

PinData PinData::fromJson(const QJsonObject& json)
{
    PinData data;
    data.feedUuid = json["feedUuid"].toString();
    data.newsGuid = json["newsGuid"].toString();
    data.pinned = json["pinned"].toBool(true);
    data.timestamp = json["timestamp"].toVariant().toLongLong();
    data.deviceId = json["deviceId"].toString();
    return data;
}

// -----------------------------------------------------------------------------
// SettingsData
// -----------------------------------------------------------------------------

QJsonObject SettingsData::toJson() const
{
    QJsonObject obj;
    obj["style"] = style;
    obj["fontSize"] = fontSize;
    obj["refreshInterval"] = refreshInterval;
    obj["cacheLength"] = cacheLength;
    obj["timestamp"] = timestamp;
    obj["deviceId"] = deviceId;
    return obj;
}

SettingsData SettingsData::fromJson(const QJsonObject& json)
{
    SettingsData data;
    data.style = json["style"].toString();
    data.fontSize = json["fontSize"].toString();
    data.refreshInterval = json["refreshInterval"].toString();
    data.cacheLength = json["cacheLength"].toString();
    data.timestamp = json["timestamp"].toVariant().toLongLong();
    data.deviceId = json["deviceId"].toString();
    return data;
}

// -----------------------------------------------------------------------------
// SyncPayload
// -----------------------------------------------------------------------------

SyncPayload::SyncPayload()
{
    deviceId = generateDeviceId();
}

QByteArray SyncPayload::toJson() const
{
    QJsonObject root;
    root["version"] = version;
    root["deviceId"] = deviceId;
    root["lastModified"] = lastModified;

    // Feeds
    QJsonObject feedsObj;
    for (auto it = feeds.constBegin(); it != feeds.constEnd(); ++it) {
        feedsObj[it.key()] = it.value().toJson();
    }
    root["feeds"] = feedsObj;

    // Bookmarks
    QJsonObject bookmarksObj;
    for (auto it = bookmarks.constBegin(); it != bookmarks.constEnd(); ++it) {
        bookmarksObj[it.key()] = it.value().toJson();
    }
    root["bookmarks"] = bookmarksObj;

    // Pins
    QJsonObject pinsObj;
    for (auto it = pins.constBegin(); it != pins.constEnd(); ++it) {
        pinsObj[it.key()] = it.value().toJson();
    }
    root["pins"] = pinsObj;

    // Settings
    root["settings"] = settings.toJson();

    return QJsonDocument(root).toJson(QJsonDocument::Compact);
}

SyncPayload SyncPayload::fromJson(const QByteArray& json, bool* ok)
{
    SyncPayload payload;

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(json, &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        if (ok) *ok = false;
        return payload;
    }

    QJsonObject root = doc.object();

    payload.version = root["version"].toInt(SYNC_VERSION);
    payload.deviceId = root["deviceId"].toString();
    payload.lastModified = root["lastModified"].toVariant().toLongLong();

    // Feeds
    QJsonObject feedsObj = root["feeds"].toObject();
    for (auto it = feedsObj.constBegin(); it != feedsObj.constEnd(); ++it) {
        payload.feeds[it.key()] = FeedData::fromJson(it.value().toObject());
    }

    // Bookmarks
    QJsonObject bookmarksObj = root["bookmarks"].toObject();
    for (auto it = bookmarksObj.constBegin(); it != bookmarksObj.constEnd(); ++it) {
        payload.bookmarks[it.key()] = BookmarkData::fromJson(it.value().toObject());
    }

    // Pins
    QJsonObject pinsObj = root["pins"].toObject();
    for (auto it = pinsObj.constBegin(); it != pinsObj.constEnd(); ++it) {
        payload.pins[it.key()] = PinData::fromJson(it.value().toObject());
    }

    // Settings
    payload.settings = SettingsData::fromJson(root["settings"].toObject());

    if (ok) *ok = true;
    return payload;
}

void SyncPayload::merge(const SyncPayload& other)
{
    // Merge feeds (last-write-wins by timestamp)
    for (auto it = other.feeds.constBegin(); it != other.feeds.constEnd(); ++it) {
        const QString& uuid = it.key();
        const FeedData& otherFeed = it.value();

        if (!feeds.contains(uuid)) {
            feeds[uuid] = otherFeed;
        } else {
            FeedData& localFeed = feeds[uuid];
            // Compare timestamps, use deviceId as tie-breaker
            if (otherFeed.timestamp > localFeed.timestamp ||
                (otherFeed.timestamp == localFeed.timestamp &&
                 otherFeed.deviceId > localFeed.deviceId)) {
                feeds[uuid] = otherFeed;
            }
        }
    }

    // Merge bookmarks
    for (auto it = other.bookmarks.constBegin(); it != other.bookmarks.constEnd(); ++it) {
        const QString& feedUuid = it.key();
        const BookmarkData& otherBookmark = it.value();

        if (!bookmarks.contains(feedUuid)) {
            bookmarks[feedUuid] = otherBookmark;
        } else {
            BookmarkData& localBookmark = bookmarks[feedUuid];
            if (otherBookmark.timestamp > localBookmark.timestamp ||
                (otherBookmark.timestamp == localBookmark.timestamp &&
                 otherBookmark.deviceId > localBookmark.deviceId)) {
                bookmarks[feedUuid] = otherBookmark;
            }
        }
    }

    // Merge pins
    for (auto it = other.pins.constBegin(); it != other.pins.constEnd(); ++it) {
        const QString& key = it.key();
        const PinData& otherPin = it.value();

        if (!pins.contains(key)) {
            pins[key] = otherPin;
        } else {
            PinData& localPin = pins[key];
            if (otherPin.timestamp > localPin.timestamp ||
                (otherPin.timestamp == localPin.timestamp &&
                 otherPin.deviceId > localPin.deviceId)) {
                pins[key] = otherPin;
            }
        }
    }

    // Merge settings
    if (other.settings.timestamp > settings.timestamp ||
        (other.settings.timestamp == settings.timestamp &&
         other.settings.deviceId > settings.deviceId)) {
        settings = other.settings;
    }

    // Update lastModified to the latest
    lastModified = qMax(lastModified, other.lastModified);
}

bool SyncPayload::isEmpty() const
{
    return feeds.isEmpty() && bookmarks.isEmpty() && pins.isEmpty() &&
           settings.timestamp == 0;
}

QString SyncPayload::generateDeviceId()
{
    // Try to get a stable device ID from settings, or generate a new one
    QSettings settings;
    QString id = settings.value("sync/deviceId").toString();

    if (id.isEmpty()) {
        id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        settings.setValue("sync/deviceId", id);
    }

    return id;
}

// -----------------------------------------------------------------------------
// Helper functions
// -----------------------------------------------------------------------------

QString feedUuidFromUrl(const QString& url)
{
    // Generate a deterministic UUID from the feed URL
    // This ensures the same feed gets the same UUID across devices
    QByteArray hash = QCryptographicHash::hash(
        url.toUtf8(),
        QCryptographicHash::Sha256
    );

    // Take first 16 bytes and format as UUID
    QByteArray uuidBytes = hash.left(16);
    QUuid uuid = QUuid::fromRfc4122(uuidBytes);
    return uuid.toString(QUuid::WithoutBraces);
}

QString pinKey(const QString& feedUuid, const QString& newsGuid)
{
    return feedUuid + ":" + newsGuid;
}

} // namespace SyncData
