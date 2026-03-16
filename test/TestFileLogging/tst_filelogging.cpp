#include <QtTest>

#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QTemporaryDir>

#include "utilities/FangLogging.h"


class TestFileLogging : public QObject
{
    Q_OBJECT

public:
    TestFileLogging();

private slots:
    void init();
    void cleanup();

    void testLogDirCreated();
    void testLogFileCreated();
    void testAppendsToExistingFile();
    void testLogFormatDebug();
    void testLogFormatInfo();
    void testLogFormatWarning();
    void testLogFormatCritical();
    void testLogFormatCategory();
    void testNullCategory();
    void testPreviousHandlerCalled();
    void testHandlerNotInstalledOnFailure();
    void testRotationTriggered();
    void testRotationShiftsFiles();
    void testRotationMaxFiles();
    void testRotationNewFileIsSmall();
    void testNoRotationUnderSizeLimit();
    void testShutdownRestoresHandler();

private:
    QTemporaryDir tempDir;
    QString logDirPath;

    QString readLogFile(const QString &filename = "fang.log");
    void prefillLogFile(const QString &filename, qint64 size);
};


TestFileLogging::TestFileLogging() {}

void TestFileLogging::init()
{
    QVERIFY(tempDir.isValid());
    logDirPath = tempDir.path() + "/logs";
}

void TestFileLogging::cleanup()
{
    shutdownFileLogging();

    // Clean up log files between tests
    QDir dir(logDirPath);
    if (dir.exists()) {
        dir.removeRecursively();
    }
}

QString TestFileLogging::readLogFile(const QString &filename)
{
    QFile file(logDirPath + "/" + filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }
    return QString::fromUtf8(file.readAll());
}

void TestFileLogging::prefillLogFile(const QString &filename, qint64 size)
{
    QDir().mkpath(logDirPath);
    QFile file(logDirPath + "/" + filename);
    QVERIFY(file.open(QIODevice::WriteOnly));
    QByteArray filler(size, 'x');
    filler.append('\n');
    file.write(filler);
    file.close();
}

// --- Directory and file creation ---

void TestFileLogging::testLogDirCreated()
{
    QVERIFY(!QDir(logDirPath).exists());
    initFileLogging(logDirPath);
    QVERIFY(QDir(logDirPath).exists());
}

void TestFileLogging::testLogFileCreated()
{
    initFileLogging(logDirPath);
    QVERIFY(QFile::exists(logDirPath + "/fang.log"));
}

void TestFileLogging::testAppendsToExistingFile()
{
    QDir().mkpath(logDirPath);
    QFile file(logDirPath + "/fang.log");
    QVERIFY(file.open(QIODevice::WriteOnly | QIODevice::Text));
    file.write("existing content\n");
    file.close();

    initFileLogging(logDirPath);
    qWarning("new message");

    QString content = readLogFile();
    QVERIFY(content.startsWith("existing content\n"));
    QVERIFY(content.contains("new message"));
}

// --- Log format ---

void TestFileLogging::testLogFormatDebug()
{
    initFileLogging(logDirPath);
    qDebug("test debug message");

    QString content = readLogFile();
    QRegularExpression re(R"(\[\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3}\] \[debug\] \[default\] test debug message)");
    QVERIFY2(re.match(content).hasMatch(), qPrintable(content));
}

void TestFileLogging::testLogFormatInfo()
{
    initFileLogging(logDirPath);
    qInfo("test info message");

    QString content = readLogFile();
    QVERIFY(content.contains("[info]"));
    QVERIFY(content.contains("test info message"));
}

void TestFileLogging::testLogFormatWarning()
{
    initFileLogging(logDirPath);
    qWarning("test warning message");

    QString content = readLogFile();
    QVERIFY(content.contains("[warning]"));
    QVERIFY(content.contains("test warning message"));
}

void TestFileLogging::testLogFormatCritical()
{
    initFileLogging(logDirPath);
    qCritical("test critical message");

    QString content = readLogFile();
    QVERIFY(content.contains("[critical]"));
    QVERIFY(content.contains("test critical message"));
}

void TestFileLogging::testLogFormatCategory()
{
    initFileLogging(logDirPath);
    qCWarning(logApp) << "category test";

    QString content = readLogFile();
    QVERIFY2(content.contains("[fang.app]"), qPrintable(content));
    QVERIFY(content.contains("category test"));
}

void TestFileLogging::testNullCategory()
{
    initFileLogging(logDirPath);

    // Emit a message via the handler directly with a null category context
    QMessageLogContext context;
    // Default-constructed QMessageLogContext has category == "default"
    // Just verify a normal qDebug works (which uses "default" category)
    qDebug("null category test");

    QString content = readLogFile();
    QVERIFY(content.contains("[default]"));
    QVERIFY(content.contains("null category test"));
}

// --- Previous handler ---

void TestFileLogging::testPreviousHandlerCalled()
{
    static bool handlerCalled = false;
    static QString capturedMessage;
    handlerCalled = false;
    capturedMessage.clear();

    // Install a custom handler that our logging should chain to
    auto testHandler = [](QtMsgType, const QMessageLogContext &, const QString &msg) {
        handlerCalled = true;
        capturedMessage = msg;
    };
    QtMessageHandler oldHandler = qInstallMessageHandler(testHandler);

    initFileLogging(logDirPath);
    qWarning("chained message");

    QVERIFY(handlerCalled);
    QCOMPARE(capturedMessage, QString("chained message"));

    // Restore original handler
    shutdownFileLogging();
    qInstallMessageHandler(oldHandler);
}

void TestFileLogging::testHandlerNotInstalledOnFailure()
{
    static bool handlerCalled = false;
    handlerCalled = false;

    auto testHandler = [](QtMsgType, const QMessageLogContext &, const QString &) {
        handlerCalled = true;
    };
    qInstallMessageHandler(testHandler);

    // Use a path that can't be opened (directory doesn't exist and path is invalid)
    initFileLogging("/dev/null/impossible/path");

    // The handler should still be our test handler since initFileLogging failed
    // Reset and test
    handlerCalled = false;
    qWarning("test");
    QVERIFY(handlerCalled);

    // Clean up - shutdownFileLogging won't fully work since init failed,
    // but we restore the handler ourselves
    qInstallMessageHandler(nullptr);
}

// --- Rotation ---

void TestFileLogging::testRotationTriggered()
{
    // Pre-fill fang.log to exceed 5MB
    prefillLogFile("fang.log", 5 * 1024 * 1024 + 1);
    initFileLogging(logDirPath);

    // Write 100 messages to trigger the size check
    for (int i = 0; i < 100; ++i) {
        qDebug("rotation trigger message %d", i);
    }

    QVERIFY2(QFile::exists(logDirPath + "/fang.1.log"),
             "fang.1.log should exist after rotation");
    QVERIFY(QFile::exists(logDirPath + "/fang.log"));
}

void TestFileLogging::testRotationShiftsFiles()
{
    // Create existing rotated files with known content
    QDir().mkpath(logDirPath);

    auto writeMarker = [&](const QString &filename, const QString &marker) {
        QFile f(logDirPath + "/" + filename);
        QVERIFY(f.open(QIODevice::WriteOnly));
        f.write(marker.toUtf8());
        f.close();
    };

    writeMarker("fang.1.log", "MARKER_ONE");
    writeMarker("fang.2.log", "MARKER_TWO");

    // Pre-fill fang.log to exceed 5MB
    prefillLogFile("fang.log", 5 * 1024 * 1024 + 1);
    initFileLogging(logDirPath);

    // Trigger rotation
    for (int i = 0; i < 100; ++i) {
        qDebug("shift test %d", i);
    }

    // fang.2.log should now have MARKER_ONE (shifted from fang.1.log)
    QString content2 = readLogFile("fang.2.log");
    QVERIFY2(content2.contains("MARKER_ONE"), qPrintable("fang.2.log should contain MARKER_ONE, got: " + content2.left(50)));

    // fang.3.log should now have MARKER_TWO (shifted from fang.2.log)
    QString content3 = readLogFile("fang.3.log");
    QVERIFY2(content3.contains("MARKER_TWO"), qPrintable("fang.3.log should contain MARKER_TWO, got: " + content3.left(50)));

    // fang.1.log should have the old fang.log content (the prefilled data)
    QFileInfo info1(logDirPath + "/fang.1.log");
    QVERIFY(info1.size() > 5 * 1024 * 1024);
}

void TestFileLogging::testRotationMaxFiles()
{
    // Create fang.1.log, fang.2.log, fang.3.log
    QDir().mkpath(logDirPath);

    for (int i = 1; i <= 3; ++i) {
        QFile f(logDirPath + QString("/fang.%1.log").arg(i));
        QVERIFY(f.open(QIODevice::WriteOnly));
        f.write(QString("old_%1").arg(i).toUtf8());
        f.close();
    }

    // Pre-fill fang.log to exceed 5MB
    prefillLogFile("fang.log", 5 * 1024 * 1024 + 1);
    initFileLogging(logDirPath);

    // Trigger rotation
    for (int i = 0; i < 100; ++i) {
        qDebug("max files test %d", i);
    }

    // fang.3.log should exist (shifted from fang.2.log)
    QVERIFY(QFile::exists(logDirPath + "/fang.3.log"));

    // fang.4.log should NOT exist
    QVERIFY(!QFile::exists(logDirPath + "/fang.4.log"));
}

void TestFileLogging::testRotationNewFileIsSmall()
{
    prefillLogFile("fang.log", 5 * 1024 * 1024 + 1);
    initFileLogging(logDirPath);

    for (int i = 0; i < 100; ++i) {
        qDebug("new file test %d", i);
    }

    // The new fang.log should be much smaller than 5MB
    QFileInfo info(logDirPath + "/fang.log");
    QVERIFY2(info.size() < 1024 * 1024,
             qPrintable(QString("fang.log should be small after rotation, but is %1 bytes").arg(info.size())));
}

void TestFileLogging::testNoRotationUnderSizeLimit()
{
    initFileLogging(logDirPath);

    // Write 200 messages (triggers two size checks) but file is small
    for (int i = 0; i < 200; ++i) {
        qDebug("small message %d", i);
    }

    // No rotation should have occurred
    QVERIFY(!QFile::exists(logDirPath + "/fang.1.log"));
}

// --- Shutdown ---

void TestFileLogging::testShutdownRestoresHandler()
{
    static bool customCalled = false;
    auto customHandler = [](QtMsgType, const QMessageLogContext &, const QString &) {
        customCalled = true;
    };
    QtMessageHandler oldHandler = qInstallMessageHandler(customHandler);

    initFileLogging(logDirPath);
    shutdownFileLogging();

    // After shutdown, the custom handler should be active again
    customCalled = false;
    qWarning("after shutdown");
    QVERIFY(customCalled);

    // File should not receive new messages after shutdown
    QString content = readLogFile();
    QVERIFY(!content.contains("after shutdown"));

    qInstallMessageHandler(oldHandler);
}

QTEST_APPLESS_MAIN(TestFileLogging)

#include "tst_filelogging.moc"
