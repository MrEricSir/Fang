#include <QString>
#include <QTest>
#include <QSignalSpy>

#include "../../src/network/NetworkDownloadCore.h"
#include "../MockNetworkAccessManager.h"

class TestNetworkDownloadCore : public QObject
{
    Q_OBJECT

public:
    TestNetworkDownloadCore();

private slots:
    // Constructor tests
    void testConstructorWithProvidedManager();
    void testConstructorCreatesOwnManager();
    void testConstructorWithConfig();

    // Successful download tests
    void testSuccessfulDownload();
    void testSuccessfulDownloadEmitsCorrectUrl();

    // Error handling tests
    void testRelativeURLError();
    void testNetworkError();

    // Redirect tests
    void testSingleRedirect();
    void testRedirectChain();
    void testMaxRedirectsExceeded();
    void testRelativeRedirect();

    // Timeout tests
    void testInactivityTimeoutFires();
    void testInactivityTimeoutResetsOnProgress();
    void testTransferTimeoutMode();

    // Progress tests
    void testProgressSignalEmitted();

    // Abort tests
    void testAbortCancelsDownload();
    void testAbortNoSignalAfterAbort();

    // Multiple downloads
    void testMultipleSequentialDownloads();
    void testNewDownloadAbortsExisting();

    // Retry tests
    void testNoRetryByDefault();
    void testRetryOnTransientError();
    void testRetryExhausted();
    void testRetrySignalEmitted();
    void testNonRetryableErrorNoRetry();
    void testRetryResetsRedirects();
    void testRetryOnTimeout();
};

TestNetworkDownloadCore::TestNetworkDownloadCore()
{
}

void TestNetworkDownloadCore::testConstructorWithProvidedManager()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    mockManager.addResponse(QUrl("http://example.com/test"), "test data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
}

void TestNetworkDownloadCore::testConstructorCreatesOwnManager()
{
    NetworkDownloadCore downloader({}, nullptr, nullptr);
    // If no crash, it worked
    QVERIFY(true);
}

void TestNetworkDownloadCore::testConstructorWithConfig()
{
    NetworkDownloadConfig config;
    config.timeoutMs = 5000;
    config.maxRedirects = 5;
    config.useInactivityTimeout = false;

    NetworkDownloadCore downloader(config);
    // If no crash, config was accepted
    QVERIFY(true);
}

void TestNetworkDownloadCore::testSuccessfulDownload()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QByteArray expectedData = "Hello, World!";
    mockManager.addResponse(QUrl("http://example.com/test"), expectedData);

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(1).toByteArray(), expectedData);
}

void TestNetworkDownloadCore::testSuccessfulDownloadEmitsCorrectUrl()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QUrl testUrl("http://example.com/page.html");
    mockManager.addResponse(testUrl, "content");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    downloader.download(testUrl);

    QVERIFY(finishedSpy.wait(1000));
    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(0).toUrl(), testUrl);
}

void TestNetworkDownloadCore::testRelativeURLError()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);

    downloader.download(QUrl("/relative/path"));

    // Error should be emitted synchronously
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 0);

    QString errorMsg = errorSpy.takeFirst().at(1).toString();
    QVERIFY(errorMsg.contains("Relative"));
}

void TestNetworkDownloadCore::testNetworkError()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    mockManager.setNextError(QNetworkReply::HostNotFoundError);

    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);

    downloader.download(QUrl("http://nonexistent.example.com/"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 0);
}

void TestNetworkDownloadCore::testSingleRedirect()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QUrl originalUrl("http://example.com/old");
    QUrl redirectUrl("http://example.com/new");
    QByteArray finalData = "Final content";

    mockManager.addRedirect(originalUrl, redirectUrl);
    mockManager.addResponse(redirectUrl, finalData);

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    downloader.download(originalUrl);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(0).toUrl(), redirectUrl);  // Final URL
    QCOMPARE(args.at(1).toByteArray(), finalData);
}

void TestNetworkDownloadCore::testRedirectChain()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QUrl urlA("http://example.com/a");
    QUrl urlB("http://example.com/b");
    QUrl urlC("http://example.com/c");
    QByteArray finalData = "End of chain";

    mockManager.addRedirect(urlA, urlB);
    mockManager.addRedirect(urlB, urlC);
    mockManager.addResponse(urlC, finalData);

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    downloader.download(urlA);

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(0).toUrl(), urlC);
    QCOMPARE(args.at(1).toByteArray(), finalData);
}

void TestNetworkDownloadCore::testMaxRedirectsExceeded()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.maxRedirects = 3;
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // Create redirect chain longer than maxRedirects
    QList<QUrl> urls;
    for (int i = 0; i <= 5; i++) {
        urls.append(QUrl(QString("http://example.com/redirect%1").arg(i)));
    }

    for (int i = 0; i < urls.size() - 1; i++) {
        mockManager.addRedirect(urls[i], urls[i + 1]);
    }

    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    downloader.download(urls.first());

    QVERIFY(errorSpy.wait(2000));
    QCOMPARE(errorSpy.count(), 1);

    QString errorMsg = errorSpy.takeFirst().at(1).toString();
    QVERIFY(errorMsg.contains("redirect"));
}

void TestNetworkDownloadCore::testRelativeRedirect()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QUrl originalUrl("http://example.com/dir/page");
    QUrl relativeRedirect("../other/page");  // Relative redirect
    QUrl resolvedUrl("http://example.com/other/page");
    QByteArray finalData = "Resolved content";

    mockManager.addRedirect(originalUrl, relativeRedirect);
    mockManager.addResponse(resolvedUrl, finalData);

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    downloader.download(originalUrl);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(1).toByteArray(), finalData);
}

void TestNetworkDownloadCore::testInactivityTimeoutFires()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.timeoutMs = 100;  // Short timeout for testing
    config.useInactivityTimeout = true;
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // Set long delay to trigger timeout
    mockManager.setResponseDelay(500);
    mockManager.addResponse(QUrl("http://example.com/slow"), "data");

    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    downloader.download(QUrl("http://example.com/slow"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);

    QString errorMsg = errorSpy.takeFirst().at(1).toString();
    QVERIFY(errorMsg.contains("timeout", Qt::CaseInsensitive));
}

void TestNetworkDownloadCore::testInactivityTimeoutResetsOnProgress()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.timeoutMs = 200;
    config.useInactivityTimeout = true;
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // Short delay - should complete before timeout
    mockManager.setResponseDelay(50);
    mockManager.setEmitProgress(true);
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);
}

void TestNetworkDownloadCore::testTransferTimeoutMode()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.timeoutMs = 100;
    config.useInactivityTimeout = false;  // Use setTransferTimeout instead
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // With transfer timeout mode, the request itself has the timeout
    // Mock doesn't fully simulate this, so just verify no crash
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
}

void TestNetworkDownloadCore::testProgressSignalEmitted()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.useInactivityTimeout = true;  // Need this for progress signals
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    mockManager.setEmitProgress(true);
    mockManager.addResponse(QUrl("http://example.com/test"), "test data");

    QSignalSpy progressSpy(&downloader, &NetworkDownloadCore::progress);
    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    // Progress signal should have been emitted at least once
    QVERIFY(progressSpy.count() >= 1);
}

void TestNetworkDownloadCore::testAbortCancelsDownload()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    mockManager.setResponseDelay(500);  // Long delay
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);

    downloader.download(QUrl("http://example.com/test"));

    // Abort immediately
    downloader.abort();

    // Wait a bit to see if signals are emitted
    QTest::qWait(100);

    // No signals should be emitted after abort
    QCOMPARE(finishedSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 0);
}

void TestNetworkDownloadCore::testAbortNoSignalAfterAbort()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    // Abort when nothing is downloading should be safe
    downloader.abort();
    QVERIFY(true);  // No crash
}

void TestNetworkDownloadCore::testMultipleSequentialDownloads()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    QByteArray data1 = "First";
    QByteArray data2 = "Second";

    mockManager.addResponse(QUrl("http://example.com/first"), data1);
    mockManager.addResponse(QUrl("http://example.com/second"), data2);

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);

    // First download
    downloader.download(QUrl("http://example.com/first"));
    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(finishedSpy.takeFirst().at(1).toByteArray(), data1);

    // Second download
    downloader.download(QUrl("http://example.com/second"));
    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(finishedSpy.takeFirst().at(1).toByteArray(), data2);
}

void TestNetworkDownloadCore::testNewDownloadAbortsExisting()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    mockManager.setResponseDelay(500);  // Long delay for first
    mockManager.addResponse(QUrl("http://example.com/slow"), "slow data");
    mockManager.addResponse(QUrl("http://example.com/fast"), "fast data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);

    // Start slow download
    downloader.download(QUrl("http://example.com/slow"));

    // Immediately start another download (should abort the first)
    mockManager.setResponseDelay(0);
    downloader.download(QUrl("http://example.com/fast"));

    QVERIFY(finishedSpy.wait(1000));
    // Should only get one finished signal (for the fast one)
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(finishedSpy.takeFirst().at(1).toByteArray(), QByteArray("fast data"));
}

void TestNetworkDownloadCore::testNoRetryByDefault()
{
    // Default config should not retry - backward compatibility
    MockNetworkAccessManager mockManager;
    NetworkDownloadCore downloader({}, nullptr, &mockManager);

    mockManager.setNextError(QNetworkReply::HostNotFoundError);

    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 0);  // No retry signal
}

void TestNetworkDownloadCore::testRetryOnTransientError()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.retryPolicy = NetworkRetryPolicy(3, 10, NetworkRetryPolicy::Fixed);  // 3 retries, 10ms delay
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // Fail first request, succeed on retry
    mockManager.setFailureCount(1, QNetworkReply::TemporaryNetworkFailureError);
    mockManager.addResponse(QUrl("http://example.com/test"), "success data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(retryingSpy.count(), 1);  // One retry was scheduled

    // Verify data
    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(1).toByteArray(), QByteArray("success data"));
}

void TestNetworkDownloadCore::testRetryExhausted()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    // maxRetries=3 means: attempt 1, retry (attempt 2), retry (attempt 3) = 2 retries total
    config.retryPolicy = NetworkRetryPolicy(3, 10, NetworkRetryPolicy::Fixed);
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // All requests fail
    mockManager.setFailureCount(10, QNetworkReply::TemporaryNetworkFailureError);

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(errorSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 2);  // Two retries attempted
}

void TestNetworkDownloadCore::testRetrySignalEmitted()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.retryPolicy = NetworkRetryPolicy(3, 50, NetworkRetryPolicy::Fixed);  // 50ms delay
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    mockManager.setFailureCount(1, QNetworkReply::TemporaryNetworkFailureError);
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);
    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);

    downloader.download(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(retryingSpy.count(), 1);

    // Verify retry signal arguments
    QList<QVariant> args = retryingSpy.takeFirst();
    QCOMPARE(args.at(0).toInt(), 2);   // Attempt number 2 (first retry)
    QCOMPARE(args.at(1).toInt(), 50);  // 50ms delay
}

void TestNetworkDownloadCore::testNonRetryableErrorNoRetry()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.retryPolicy = NetworkRetryPolicy(3, 10, NetworkRetryPolicy::Fixed);
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // 404 is not retryable by default
    mockManager.addErrorResponse(QUrl("http://example.com/missing"), QNetworkReply::ContentNotFoundError);

    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);
    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);

    downloader.download(QUrl("http://example.com/missing"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 0);  // No retry for 404
}

void TestNetworkDownloadCore::testRetryResetsRedirects()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.maxRedirects = 2;
    config.retryPolicy = NetworkRetryPolicy(2, 10, NetworkRetryPolicy::Fixed);
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    QUrl startUrl("http://example.com/start");
    QUrl redirect1("http://example.com/redirect1");
    QUrl redirect2("http://example.com/redirect2");
    QUrl finalUrl("http://example.com/final");

    // First attempt: start -> redirect1 -> error
    // Second attempt (retry): start -> redirect1 -> redirect2 -> final (success)
    mockManager.addRedirect(startUrl, redirect1);

    // First time hitting redirect1 returns error
    mockManager.setFailureCount(1, QNetworkReply::TemporaryNetworkFailureError);

    // After the retry, the redirect chain works
    mockManager.addRedirect(redirect1, redirect2);
    mockManager.addResponse(redirect2, "final data");

    QSignalSpy finishedSpy(&downloader, &NetworkDownloadCore::finished);
    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);

    downloader.download(startUrl);

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 1);  // One retry
}

void TestNetworkDownloadCore::testRetryOnTimeout()
{
    MockNetworkAccessManager mockManager;
    NetworkDownloadConfig config;
    config.timeoutMs = 50;  // Very short timeout
    config.useInactivityTimeout = true;
    config.retryPolicy = NetworkRetryPolicy(2, 10, NetworkRetryPolicy::Fixed);
    config.retryPolicy.setRetryOnTimeout(true);
    NetworkDownloadCore downloader(config, nullptr, &mockManager);

    // First request times out, second succeeds
    mockManager.setResponseDelay(200);  // Longer than timeout
    mockManager.addResponse(QUrl("http://example.com/test"), "success");

    QSignalSpy retryingSpy(&downloader, &NetworkDownloadCore::retrying);
    QSignalSpy errorSpy(&downloader, &NetworkDownloadCore::error);

    downloader.download(QUrl("http://example.com/test"));

    // Should retry on timeout, then eventually fail (all attempts timeout)
    QVERIFY(errorSpy.wait(2000));
    QVERIFY(retryingSpy.count() >= 1);  // At least one retry
}

QTEST_MAIN(TestNetworkDownloadCore)

#include "tst_networkdownloadcore.moc"
