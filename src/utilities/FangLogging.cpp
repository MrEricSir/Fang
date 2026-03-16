#include "FangLogging.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QStandardPaths>
#include <QTextStream>

static constexpr qint64 MaxFileSize = 5 * 1024 * 1024; // 5 MB
static constexpr int MaxRotatedFiles = 3;
static constexpr int WriteCheckInterval = 100;

static QFile logFile;
static QMutex logMutex;
static int writeCount = 0;
static QString logFilePath;
static QtMessageHandler previousHandler = nullptr;

static QString logDir()
{
#if defined(Q_OS_MACOS)
    return QDir::homePath() + QStringLiteral("/Library/Logs/Fang");
#elif defined(Q_OS_WIN)
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
           + QStringLiteral("/logs");
#else
    return QStandardPaths::writableLocation(QStandardPaths::StateLocation);
#endif
}

static void rotateIfNeeded()
{
    if (logFile.size() < MaxFileSize) {
        return;
    }

    logFile.close();

    const QString base = logFilePath;
    const QDir dir = QFileInfo(base).absoluteDir();
    const QString stem = QFileInfo(base).completeBaseName();
    const QString suffix = QFileInfo(base).suffix();

    for (int i = MaxRotatedFiles; i >= 1; --i) {
        const QString src = (i == 1)
            ? base
            : dir.filePath(QStringLiteral("%1.%2.%3").arg(stem, QString::number(i - 1), suffix));
        const QString dst = dir.filePath(QStringLiteral("%1.%2.%3").arg(stem, QString::number(i), suffix));

        QFile::remove(dst);
        QFile::rename(src, dst);
    }

    logFile.setFileName(base);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning("Failed to reopen log file after rotation: %s", qPrintable(base));
    }
}

// Log level to string literal
static const char *levelString(QtMsgType type)
{
    switch (type) {
    case QtDebugMsg:
        return "debug";
    case QtInfoMsg:
        return "info";
    case QtWarningMsg:
        return "warning";
    case QtCriticalMsg:
        return "critical";
    case QtFatalMsg:
        return "fatal";
    }
    return "unknown";
}

static void fileMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    const QString category = context.category ? QString::fromUtf8(context.category) : QString();
    const QString line = QStringLiteral("[%1] [%2] [%3] %4\n")
                             .arg(timestamp, QLatin1String(levelString(type)), category, msg);

    {
        QMutexLocker locker(&logMutex);
        if (logFile.isOpen()) {
            logFile.write(line.toUtf8());
            logFile.flush();

            if (++writeCount >= WriteCheckInterval) {
                writeCount = 0;
                rotateIfNeeded();
            }
        }
    }

    if (previousHandler) {
        previousHandler(type, context, msg);
    }
}

void initFileLogging(const QString &logDirOverride)
{
    const QString dir = logDirOverride.isEmpty() ? logDir() : logDirOverride;
    QDir().mkpath(dir);

    logFilePath = dir + QStringLiteral("/fang.log");
    logFile.setFileName(logFilePath);

    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning("Failed to open log file: %s", qPrintable(logFilePath));
        return;
    }

    previousHandler = qInstallMessageHandler(fileMessageHandler);
}

void shutdownFileLogging()
{
    if (previousHandler) {
        qInstallMessageHandler(previousHandler);
        previousHandler = nullptr;
    }
    logFile.close();
    logFilePath.clear();
    writeCount = 0;
}

// Define logging categories
// In debug builds, these output at QtDebugMsg level
// In release builds, they're disabled except for warnings/critical

#ifdef QT_DEBUG
Q_LOGGING_CATEGORY(logApp, "fang.app", QtDebugMsg)
Q_LOGGING_CATEGORY(logDb, "fang.db", QtDebugMsg)
Q_LOGGING_CATEGORY(logModel, "fang.model", QtDebugMsg)
Q_LOGGING_CATEGORY(logOperation, "fang.operation", QtDebugMsg)
Q_LOGGING_CATEGORY(logParser, "fang.parser", QtDebugMsg)
Q_LOGGING_CATEGORY(logNetwork, "fang.network", QtDebugMsg)
Q_LOGGING_CATEGORY(logRewriter, "fang.rewriter", QtDebugMsg)
Q_LOGGING_CATEGORY(logServer, "fang.server", QtDebugMsg)
Q_LOGGING_CATEGORY(logUtility, "fang.utility", QtDebugMsg)
Q_LOGGING_CATEGORY(logFavicon, "fang.favicon", QtDebugMsg)
Q_LOGGING_CATEGORY(logWebPage, "fang.webpage", QtDebugMsg)
Q_LOGGING_CATEGORY(logMock, "fang.mock", QtDebugMsg)
#else
Q_LOGGING_CATEGORY(logApp, "fang.app", QtWarningMsg)
Q_LOGGING_CATEGORY(logDb, "fang.db", QtWarningMsg)
Q_LOGGING_CATEGORY(logModel, "fang.model", QtWarningMsg)
Q_LOGGING_CATEGORY(logOperation, "fang.operation", QtWarningMsg)
Q_LOGGING_CATEGORY(logParser, "fang.parser", QtWarningMsg)
Q_LOGGING_CATEGORY(logNetwork, "fang.network", QtWarningMsg)
Q_LOGGING_CATEGORY(logRewriter, "fang.rewriter", QtWarningMsg)
Q_LOGGING_CATEGORY(logServer, "fang.server", QtWarningMsg)
Q_LOGGING_CATEGORY(logUtility, "fang.utility", QtWarningMsg)
Q_LOGGING_CATEGORY(logFavicon, "fang.favicon", QtWarningMsg)
Q_LOGGING_CATEGORY(logWebPage, "fang.webpage", QtWarningMsg)
Q_LOGGING_CATEGORY(logMock, "fang.mock", QtWarningMsg)
#endif
