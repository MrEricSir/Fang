#include "ImageCache.h"
#include "FangLogging.h"

#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

QString ImageCache::cacheDir()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/imagecache";
    QDir().mkpath(path);
    return path;
}

QString ImageCache::saveImage(const QUrl& url, const ImageData& imageData)
{
    if (!imageData.isValid()) {
        return "";
    }

    QString hash = hashUrl(url);
    QString ext = extensionForMimeType(imageData.mimeType);
    QString filename = hash + "." + ext;
    QString filePath = cacheDir() + "/" + filename;

    // Skip write if file already exists.
    if (QFile::exists(filePath)) {
        return "/images/" + filename;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return "";
    }

    file.write(imageData.rawData);
    file.close();

    return "/images/" + filename;
}

int ImageCache::evictOlderThan(const QDateTime& cutoff)
{
    QDir dir(cacheDir());
    if (!dir.exists()) {
        return 0;
    }

    int deleted = 0;
    QFileInfoList files = dir.entryInfoList(QDir::Files);
    for (const QFileInfo& info : files) {
        if (info.lastModified() < cutoff) {
            if (QFile::remove(info.absoluteFilePath())) {
                deleted++;
            }
        }
    }

    if (deleted > 0) {
        qCInfo(logUtility) << "Image cache: evicted" << deleted << "expired files";
    }

    return deleted;
}

QString ImageCache::hashUrl(const QUrl& url)
{
    QByteArray hash = QCryptographicHash::hash(url.toEncoded(), QCryptographicHash::Sha256);
    return QString::fromLatin1(hash.toHex().left(16));
}

QString ImageCache::extensionForMimeType(const QString& mimeType)
{
    if (mimeType == "image/jpeg") {
        return "jpeg";
    } else if (mimeType == "image/png") {
        return "png";
    } else if (mimeType == "image/gif") {
        return "gif";
    } else if (mimeType == "image/webp") {
        return "webp";
    } else if (mimeType == "image/svg+xml") {
        return "svg";
    }
    return "bin";
}
