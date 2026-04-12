#include <QString>
#include <QTest>
#include <QSignalSpy>

#include "QWebDownload.h"
#include "../MockNetworkAccessManager.h"

class TestQWebDownload : public QObject
{
    Q_OBJECT

public:
    TestQWebDownload();

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

    // finishedWithResult tests
    void testRelativeURLEmitsFinishedWithResult();
    void testMaxRedirectsEmitsFinishedWithResult();

    // Retry tests
    void testNoRetryByDefault();
    void testRetryOnTransientError();
    void testRetryExhausted();
    void testRetrySignalEmitted();
    void testNonRetryableErrorNoRetry();
    void testRetryResetsRedirects();
    void testRetryOnTimeout();
};

TestQWebDownload::TestQWebDownload()
{
}

void TestQWebDownload::testConstructorWithProvidedManager()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    mockManager.addResponse(QUrl("http://example.com/test"), "test data");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
}

void TestQWebDownload::testConstructorCreatesOwnManager()
{
    QWebDownload downloader({}, nullptr, nullptr);
    // If no crash, it worked
    QVERIFY(true);
}

void TestQWebDownload::testConstructorWithConfig()
{
    WebDownloadConfig config;
    config.timeoutMs = 5000;
    config.maxRedirects = 5;
    config.useInactivityTimeout = false;

    QWebDownload downloader(config);
    // If no crash, config was accepted
    QVERIFY(true);
}

void TestQWebDownload::testSuccessfulDownload()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QByteArray expectedData = "Hello, World!";
    mockManager.addResponse(QUrl("http://example.com/test"), expectedData);

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    QSignalSpy errorSpy(&downloader, &QWebDownload::error);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(1).toByteArray(), expectedData);
}

void TestQWebDownload::testSuccessfulDownloadEmitsCorrectUrl()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QUrl testUrl("http://example.com/page.html");
    mockManager.addResponse(testUrl, "content");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    downloader.get(testUrl);

    QVERIFY(finishedSpy.wait(1000));
    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(0).toUrl(), testUrl);
}

void TestQWebDownload::testRelativeURLError()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);

    downloader.get(QUrl("/relative/path"));

    // Error should be emitted synchronously
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 0);

    QString errorMsg = errorSpy.takeFirst().at(1).toString();
    QVERIFY(errorMsg.contains("Relative"));
}

void TestQWebDownload::testNetworkError()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    mockManager.setNextError(QNetworkReply::HostNotFoundError);

    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);

    downloader.get(QUrl("http://nonexistent.example.com/"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 0);
}

void TestQWebDownload::testSingleRedirect()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QUrl originalUrl("http://example.com/old");
    QUrl redirectUrl("http://example.com/new");
    QByteArray finalData = "Final content";

    mockManager.addRedirect(originalUrl, redirectUrl);
    mockManager.addResponse(redirectUrl, finalData);

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    downloader.get(originalUrl);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(0).toUrl(), redirectUrl);  // Final URL
    QCOMPARE(args.at(1).toByteArray(), finalData);
}

void TestQWebDownload::testRedirectChain()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QUrl urlA("http://example.com/a");
    QUrl urlB("http://example.com/b");
    QUrl urlC("http://example.com/c");
    QByteArray finalData = "End of chain";

    mockManager.addRedirect(urlA, urlB);
    mockManager.addRedirect(urlB, urlC);
    mockManager.addResponse(urlC, finalData);

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    downloader.get(urlA);

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(0).toUrl(), urlC);
    QCOMPARE(args.at(1).toByteArray(), finalData);
}

void TestQWebDownload::testMaxRedirectsExceeded()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.maxRedirects = 3;
    QWebDownload downloader(config, nullptr, &mockManager);

    // Create redirect chain longer than maxRedirects
    QList<QUrl> urls;
    for (int i = 0; i <= 5; i++) {
        urls.append(QUrl(QString("http://example.com/redirect%1").arg(i)));
    }

    for (int i = 0; i < urls.size() - 1; i++) {
        mockManager.addRedirect(urls[i], urls[i + 1]);
    }

    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    downloader.get(urls.first());

    QVERIFY(errorSpy.wait(2000));
    QCOMPARE(errorSpy.count(), 1);

    QString errorMsg = errorSpy.takeFirst().at(1).toString();
    QVERIFY(errorMsg.contains("redirect"));
}

void TestQWebDownload::testRelativeRedirect()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QUrl originalUrl("http://example.com/dir/page");
    QUrl relativeRedirect("../other/page");  // Relative redirect
    QUrl resolvedUrl("http://example.com/other/page");
    QByteArray finalData = "Resolved content";

    mockManager.addRedirect(originalUrl, relativeRedirect);
    mockManager.addResponse(resolvedUrl, finalData);

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    downloader.get(originalUrl);

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(1).toByteArray(), finalData);
}

void TestQWebDownload::testInactivityTimeoutFires()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.timeoutMs = 100;  // Short timeout for testing
    config.useInactivityTimeout = true;
    QWebDownload downloader(config, nullptr, &mockManager);

    // Set long delay to trigger timeout
    mockManager.setResponseDelay(500);
    mockManager.addResponse(QUrl("http://example.com/slow"), "data");

    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    downloader.get(QUrl("http://example.com/slow"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);

    QString errorMsg = errorSpy.takeFirst().at(1).toString();
    QVERIFY(errorMsg.contains("timeout", Qt::CaseInsensitive));
}

void TestQWebDownload::testInactivityTimeoutResetsOnProgress()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.timeoutMs = 200;
    config.useInactivityTimeout = true;
    QWebDownload downloader(config, nullptr, &mockManager);

    // Short delay - should complete before timeout
    mockManager.setResponseDelay(50);
    mockManager.setEmitProgress(true);
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    QSignalSpy errorSpy(&downloader, &QWebDownload::error);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);
}

void TestQWebDownload::testTransferTimeoutMode()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.timeoutMs = 100;
    config.useInactivityTimeout = false;  // Use setTransferTimeout instead
    QWebDownload downloader(config, nullptr, &mockManager);

    // With transfer timeout mode, the request itself has the timeout
    // Mock doesn't fully simulate this, so just verify no crash
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
}

void TestQWebDownload::testProgressSignalEmitted()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.useInactivityTimeout = true;  // Need this for progress signals
    QWebDownload downloader(config, nullptr, &mockManager);

    mockManager.setEmitProgress(true);
    mockManager.addResponse(QUrl("http://example.com/test"), "test data");

    QSignalSpy progressSpy(&downloader, &QWebDownload::progress);
    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(1000));
    // Progress signal should have been emitted at least once
    QVERIFY(progressSpy.count() >= 1);
}

void TestQWebDownload::testAbortCancelsDownload()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    mockManager.setResponseDelay(500);  // Long delay
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    QSignalSpy errorSpy(&downloader, &QWebDownload::error);

    downloader.get(QUrl("http://example.com/test"));

    // Abort immediately
    downloader.abort();

    // Wait a bit to see if signals are emitted
    QTest::qWait(100);

    // No signals should be emitted after abort
    QCOMPARE(finishedSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 0);
}

void TestQWebDownload::testAbortNoSignalAfterAbort()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    // Abort when nothing is downloading should be safe
    downloader.abort();
    QVERIFY(true);  // No crash
}

void TestQWebDownload::testMultipleSequentialDownloads()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QByteArray data1 = "First";
    QByteArray data2 = "Second";

    mockManager.addResponse(QUrl("http://example.com/first"), data1);
    mockManager.addResponse(QUrl("http://example.com/second"), data2);

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);

    // First download
    downloader.get(QUrl("http://example.com/first"));
    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(finishedSpy.takeFirst().at(1).toByteArray(), data1);

    // Second download
    downloader.get(QUrl("http://example.com/second"));
    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(finishedSpy.takeFirst().at(1).toByteArray(), data2);
}

void TestQWebDownload::testNewDownloadAbortsExisting()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    mockManager.setResponseDelay(500);  // Long delay for first
    mockManager.addResponse(QUrl("http://example.com/slow"), "slow data");
    mockManager.addResponse(QUrl("http://example.com/fast"), "fast data");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);

    // Start slow download
    downloader.get(QUrl("http://example.com/slow"));

    // Immediately start another download (should abort the first)
    mockManager.setResponseDelay(0);
    downloader.get(QUrl("http://example.com/fast"));

    QVERIFY(finishedSpy.wait(1000));
    // Should only get one finished signal (for the fast one)
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(finishedSpy.takeFirst().at(1).toByteArray(), QByteArray("fast data"));
}

void TestQWebDownload::testRelativeURLEmitsFinishedWithResult()
{
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    QSignalSpy resultSpy(&downloader, &QWebDownload::finishedWithResult);

    downloader.get(QUrl("/relative/path"));

    // finishedWithResult should be emitted synchronously
    QCOMPARE(resultSpy.count(), 1);

    WebDownloadResult result = resultSpy.takeFirst().at(0).value<WebDownloadResult>();
    QCOMPARE(result.networkError, QNetworkReply::ProtocolInvalidOperationError);
    QVERIFY(!result.ok());
    QVERIFY(result.errorString.contains("Relative"));
}

void TestQWebDownload::testMaxRedirectsEmitsFinishedWithResult()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.maxRedirects = 2;
    QWebDownload downloader(config, nullptr, &mockManager);

    // Create redirect chain longer than maxRedirects
    QUrl url0("http://example.com/r0");
    QUrl url1("http://example.com/r1");
    QUrl url2("http://example.com/r2");
    QUrl url3("http://example.com/r3");

    mockManager.addRedirect(url0, url1);
    mockManager.addRedirect(url1, url2);
    mockManager.addRedirect(url2, url3);

    QSignalSpy resultSpy(&downloader, &QWebDownload::finishedWithResult);
    downloader.get(url0);

    QVERIFY(resultSpy.wait(2000));
    QCOMPARE(resultSpy.count(), 1);

    WebDownloadResult result = resultSpy.takeFirst().at(0).value<WebDownloadResult>();
    QCOMPARE(result.networkError, QNetworkReply::TooManyRedirectsError);
    QVERIFY(!result.ok());
    QVERIFY(result.errorString.contains("redirect"));
}

void TestQWebDownload::testNoRetryByDefault()
{
    // Default config should not retry - backward compatibility
    MockNetworkAccessManager mockManager;
    QWebDownload downloader({}, nullptr, &mockManager);

    mockManager.setNextError(QNetworkReply::HostNotFoundError);

    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 0);  // No retry signal
}

void TestQWebDownload::testRetryOnTransientError()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.retryPolicy = WebRetryPolicy(3, 10, WebRetryPolicy::Fixed);  // 3 retries, 10ms delay
    QWebDownload downloader(config, nullptr, &mockManager);

    // Fail first request, succeed on retry
    mockManager.setFailureCount(1, QNetworkReply::TemporaryNetworkFailureError);
    mockManager.addResponse(QUrl("http://example.com/test"), "success data");

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(retryingSpy.count(), 1);  // One retry was scheduled

    // Verify data
    QList<QVariant> args = finishedSpy.takeFirst();
    QCOMPARE(args.at(1).toByteArray(), QByteArray("success data"));
}

void TestQWebDownload::testRetryExhausted()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    // maxRetries=3 means: attempt 1, retry (attempt 2), retry (attempt 3) = 2 retries total
    config.retryPolicy = WebRetryPolicy(3, 10, WebRetryPolicy::Fixed);
    QWebDownload downloader(config, nullptr, &mockManager);

    // All requests fail
    mockManager.setFailureCount(10, QNetworkReply::TemporaryNetworkFailureError);

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(errorSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 2);  // Two retries attempted
}

void TestQWebDownload::testRetrySignalEmitted()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.retryPolicy = WebRetryPolicy(3, 50, WebRetryPolicy::Fixed);  // 50ms delay
    QWebDownload downloader(config, nullptr, &mockManager);

    mockManager.setFailureCount(1, QNetworkReply::TemporaryNetworkFailureError);
    mockManager.addResponse(QUrl("http://example.com/test"), "data");

    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);
    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);

    downloader.get(QUrl("http://example.com/test"));

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(retryingSpy.count(), 1);

    // Verify retry signal arguments
    QList<QVariant> args = retryingSpy.takeFirst();
    QCOMPARE(args.at(0).toInt(), 2);   // Attempt number 2 (first retry)
    QCOMPARE(args.at(1).toInt(), 50);  // 50ms delay
}

void TestQWebDownload::testNonRetryableErrorNoRetry()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.retryPolicy = WebRetryPolicy(3, 10, WebRetryPolicy::Fixed);
    QWebDownload downloader(config, nullptr, &mockManager);

    // 404 is not retryable by default
    mockManager.addErrorResponse(QUrl("http://example.com/missing"), QNetworkReply::ContentNotFoundError);

    QSignalSpy errorSpy(&downloader, &QWebDownload::error);
    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);

    downloader.get(QUrl("http://example.com/missing"));

    QVERIFY(errorSpy.wait(1000));
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 0);  // No retry for 404
}

void TestQWebDownload::testRetryResetsRedirects()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.maxRedirects = 2;
    config.retryPolicy = WebRetryPolicy(2, 10, WebRetryPolicy::Fixed);
    QWebDownload downloader(config, nullptr, &mockManager);

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

    QSignalSpy finishedSpy(&downloader, &QWebDownload::finished);
    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);

    downloader.get(startUrl);

    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(finishedSpy.count(), 1);
    QCOMPARE(retryingSpy.count(), 1);  // One retry
}

void TestQWebDownload::testRetryOnTimeout()
{
    MockNetworkAccessManager mockManager;
    WebDownloadConfig config;
    config.timeoutMs = 50;  // Very short timeout
    config.useInactivityTimeout = true;
    config.retryPolicy = WebRetryPolicy(2, 10, WebRetryPolicy::Fixed);
    config.retryPolicy.setRetryOnTimeout(true);
    QWebDownload downloader(config, nullptr, &mockManager);

    // First request times out, second succeeds
    mockManager.setResponseDelay(200);  // Longer than timeout
    mockManager.addResponse(QUrl("http://example.com/test"), "success");

    QSignalSpy retryingSpy(&downloader, &QWebDownload::retrying);
    QSignalSpy errorSpy(&downloader, &QWebDownload::error);

    downloader.get(QUrl("http://example.com/test"));

    // Should retry on timeout, then eventually fail (all attempts timeout)
    QVERIFY(errorSpy.wait(2000));
    QVERIFY(retryingSpy.count() >= 1);  // At least one retry
}

QTEST_MAIN(TestQWebDownload)

#include "tst_qwebdownload.moc"
