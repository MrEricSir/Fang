#include <QNetworkReply>
#include <QTest>
#include "WebRetryPolicy.h"

class TestWebRetryPolicy : public QObject
{
    Q_OBJECT

public:
    TestWebRetryPolicy();

private slots:
    // Predefined policies.
    void testForFeedUpdate();
    void testForFavicon();
    void testForCritical();
    void testNoRetry();

    // Backoff strategies.
    void testLinearBackoff();
    void testExponentialBackoff();
    void testFibonacciBackoff();
    void testFixedBackoff();

    // Error categories.
    void testRetryableErrors();
    void testNonRetryableErrors();

    // Custom policies.
    void testCustomPolicy();
};

TestWebRetryPolicy::TestWebRetryPolicy() {}

void TestWebRetryPolicy::testForFeedUpdate()
{
    WebRetryPolicy policy = WebRetryPolicy::forFeedUpdate();

    QCOMPARE(policy.maxRetries(), 3);
    QVERIFY(policy.calculateDelay(0) > 0);

    // Should retry timeout errors
    QVERIFY(policy.isRetryable(QNetworkReply::TimeoutError));
    // Should not retry SSL errors
    QVERIFY(!policy.isRetryable(QNetworkReply::SslHandshakeFailedError));
}

void TestWebRetryPolicy::testForFavicon()
{
    WebRetryPolicy policy = WebRetryPolicy::forFavicon();

    QCOMPARE(policy.maxRetries(), 2);
    QVERIFY(policy.calculateDelay(0) > 0);
}

void TestWebRetryPolicy::testForCritical()
{
    WebRetryPolicy policy = WebRetryPolicy::forCritical();

    QCOMPARE(policy.maxRetries(), 5);
    QVERIFY(policy.calculateDelay(0) > 0);
}

void TestWebRetryPolicy::testNoRetry()
{
    WebRetryPolicy policy = WebRetryPolicy::noRetry();

    QCOMPARE(policy.maxRetries(), 0);
}

void TestWebRetryPolicy::testLinearBackoff()
{
    WebRetryPolicy policy(3, 1000, WebRetryPolicy::Linear);

    // Linear delay
    QCOMPARE(policy.calculateDelay(0), 1000);
    QCOMPARE(policy.calculateDelay(1), 2000);
    QCOMPARE(policy.calculateDelay(2), 3000);
}

void TestWebRetryPolicy::testExponentialBackoff()
{
    WebRetryPolicy policy(4, 1000, WebRetryPolicy::Exponential);

    // Exponential delay
    QCOMPARE(policy.calculateDelay(0), 1000);
    QCOMPARE(policy.calculateDelay(1), 2000);
    QCOMPARE(policy.calculateDelay(2), 4000);
    QCOMPARE(policy.calculateDelay(3), 8000);
}

void TestWebRetryPolicy::testFibonacciBackoff()
{
    WebRetryPolicy policy(5, 1000, WebRetryPolicy::Fibonacci);

    // Fibonacci sequence
    // Remember that Mathnet episode, The Case of the Willing Parrot?
    QCOMPARE(policy.calculateDelay(0), 1000);
    QCOMPARE(policy.calculateDelay(1), 2000);
    QCOMPARE(policy.calculateDelay(2), 3000);
    QCOMPARE(policy.calculateDelay(3), 5000);
    QCOMPARE(policy.calculateDelay(4), 8000);
}

void TestWebRetryPolicy::testFixedBackoff()
{
    WebRetryPolicy policy(3, 5000, WebRetryPolicy::Fixed);

    // Fixed delay (equal delay each time)
    QCOMPARE(policy.calculateDelay(0), 5000);
    QCOMPARE(policy.calculateDelay(1), 5000);
    QCOMPARE(policy.calculateDelay(2), 5000);
}

void TestWebRetryPolicy::testRetryableErrors()
{
    WebRetryPolicy policy = WebRetryPolicy::forFeedUpdate();

    // Should retry
    QVERIFY(policy.isRetryable(QNetworkReply::TimeoutError));
    QVERIFY(policy.isRetryable(QNetworkReply::ConnectionRefusedError));
    QVERIFY(policy.isRetryable(QNetworkReply::RemoteHostClosedError));
    QVERIFY(policy.isRetryable(QNetworkReply::HostNotFoundError));
    QVERIFY(policy.isRetryable(QNetworkReply::TemporaryNetworkFailureError));
    QVERIFY(policy.isRetryable(QNetworkReply::NetworkSessionFailedError));

    // Should retry for server errors
    QVERIFY(policy.isRetryable(QNetworkReply::InternalServerError));
    QVERIFY(policy.isRetryable(QNetworkReply::ServiceUnavailableError));
}

void TestWebRetryPolicy::testNonRetryableErrors()
{
    WebRetryPolicy policy = WebRetryPolicy::forFeedUpdate();

    // Don't retry for client errors (400's)
    QVERIFY(!policy.isRetryable(QNetworkReply::ContentAccessDenied));
    QVERIFY(!policy.isRetryable(QNetworkReply::ContentNotFoundError));
    QVERIFY(!policy.isRetryable(QNetworkReply::AuthenticationRequiredError));

    // Don't retry for security errors
    QVERIFY(!policy.isRetryable(QNetworkReply::SslHandshakeFailedError));

    // Also don't retry for protocol errors
    QVERIFY(!policy.isRetryable(QNetworkReply::ProtocolUnknownError));
    QVERIFY(!policy.isRetryable(QNetworkReply::ProtocolInvalidOperationError));
}

void TestWebRetryPolicy::testCustomPolicy()
{
    WebRetryPolicy policy(10, 500, WebRetryPolicy::Exponential);

    QCOMPARE(policy.maxRetries(), 10);
    QCOMPARE(policy.calculateDelay(0), 500);
    QCOMPARE(policy.calculateDelay(1), 1000);
}

QTEST_APPLESS_MAIN(TestWebRetryPolicy)

#include "tst_webretrypolicy.moc"
