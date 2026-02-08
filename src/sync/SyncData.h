#ifndef SYNCDATA_H
#define SYNCDATA_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QSet>

/**
 * @brief Data structures for cloud synchronization.
 *
 * Approach:
 * - Each piece of data has a timestamp for last-write-wins conflict resolution
 * - Device IDs are used as tie-breakers when timestamps are equal
 * - Deleted items are tracked with tombstones to propagate deletions
 *
 * JSON Structure:
 * {
 *   "version": 1,
 *   "deviceId": "unique-device-id",
 *   "lastModified": 1234567890000,
 *   "feeds": { ... },
 *   "bookmarks": { ... },
 *   "pins": { ... },
 *   "settings": { ... }
 * }
 */

namespace SyncData {

// Current sync data format version
constexpr int SYNC_VERSION = 1;

/**
 * @brief A timestamped value for last-write-wins semantics.
 */
template<typename T>
struct LWWValue {
    T value;
    qint64 timestamp = 0;      // Milliseconds since epoch
    QString deviceId;          // Tie-breaker when timestamps equal

    bool operator<(const LWWValue<T>& other) const {
        if (timestamp != other.timestamp) {
            return timestamp < other.timestamp;
        }
        return deviceId < other.deviceId;
    }

    bool isNewerThan(const LWWValue<T>& other) const {
        return other < *this;
    }
};

/**
 * @brief Sync data for a single feed subscription.
 */
struct FeedData {
    QString uuid;              // Stable identifier across devices
    QString url;               // Feed URL (user-entered or discovered)
    QString title;             // Feed title
    QString siteUrl;           // Website URL
    qint32 ordinal = 0;        // Sort order
    QString parentFolderUuid;  // Parent folder UUID (empty = root)
    bool isFolder = false;     // True if this is a folder
    bool folderOpen = true;    // Folder expanded state
    qint32 minutesToUpdate = 0; // Update interval
    qint64 timestamp = 0;      // Last modification time
    QString deviceId;          // Device that made the change
    bool deleted = false;      // Tombstone for deletions

    QJsonObject toJson() const;
    static FeedData fromJson(const QJsonObject& json);
};

/**
 * @brief Sync data for a bookmark (reading position).
 */
struct BookmarkData {
    QString feedUuid;          // Which feed this bookmark belongs to
    QString newsGuid;          // GUID of the bookmarked news item
    qint64 newsTimestamp = 0;  // Timestamp of the bookmarked item (for ordering)
    qint64 timestamp = 0;      // When this bookmark was set
    QString deviceId;

    QJsonObject toJson() const;
    static BookmarkData fromJson(const QJsonObject& json);
};

/**
 * @brief Sync data for a pinned news item.
 */
struct PinData {
    QString feedUuid;          // Feed containing the pinned item
    QString newsGuid;          // GUID of the pinned news item
    bool pinned = true;        // False = unpinned (tombstone)
    qint64 timestamp = 0;
    QString deviceId;

    QJsonObject toJson() const;
    static PinData fromJson(const QJsonObject& json);
};

/**
 * @brief Application settings that sync across devices.
 */
struct SettingsData {
    QString style;             // "LIGHT", "DARK", "DEFAULT"
    QString fontSize;          // "SMALL", "MEDIUM", "LARGE"
    QString refreshInterval;   // "1MIN", "10MIN", "30MIN", "1HOUR"
    QString cacheLength;       // "2WEEK", "3MONTH", "6MONTH", "1YEAR"
    qint64 timestamp = 0;
    QString deviceId;

    QJsonObject toJson() const;
    static SettingsData fromJson(const QJsonObject& json);
};

/**
 * @brief Complete sync payload.
 */
class SyncPayload {
public:
    SyncPayload();

    // Metadata
    int version = SYNC_VERSION;
    QString deviceId;
    qint64 lastModified = 0;

    // Data collections (keyed by UUID)
    QMap<QString, FeedData> feeds;
    QMap<QString, BookmarkData> bookmarks;  // Keyed by feedUuid
    QMap<QString, PinData> pins;            // Keyed by feedUuid:newsGuid
    SettingsData settings;

    // Serialization
    QByteArray toJson() const;
    static SyncPayload fromJson(const QByteArray& json, bool* ok = nullptr);

    // Merge another payload into this one (last-write-wins)
    void merge(const SyncPayload& other);

    // Check if this payload has any data
    bool isEmpty() const;

private:
    static QString generateDeviceId();
};

/**
 * @brief Generates a stable UUID for a feed based on its URL.
 *
 * This ensures the same feed gets the same UUID across devices.
 */
QString feedUuidFromUrl(const QString& url);

/**
 * @brief Generates a composite key for pin data.
 */
QString pinKey(const QString& feedUuid, const QString& newsGuid);

} // namespace SyncData

#endif // SYNCDATA_H
