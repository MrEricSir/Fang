#include <QNetworkReply>
#include <QTest>
#include "../../src/network/NetworkRetryPolicy.h"

class TestNetworkRetryPolicy : public QObject
{
    Q_OBJECT

public:
    TestNetworkRetryPolicy();

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

TestNetworkRetryPolicy::TestNetworkRetryPolicy() {}

void TestNetworkRetryPolicy::testForFeedUpdate()
{
    NetworkRetryPolicy policy = NetworkRetryPolicy::forFeedUpdate();

    QCOMPARE(policy.maxRetries(), 3);
    QVERIFY(policy.calculateDelay(0) > 0);

    // Should retry timeout errors
    QVERIFY(policy.isRetryable(QNetworkReply::TimeoutError));
    // Should not retry SSL errors
    QVERIFY(!policy.isRetryable(QNetworkReply::SslHandshakeFailedError));
}

void TestNetworkRetryPolicy::testForFavicon()
{
    NetworkRetryPolicy policy = NetworkRetryPolicy::forFavicon();

    QCOMPARE(policy.maxRetries(), 2);
    QVERIFY(policy.calculateDelay(0) > 0);
}

void TestNetworkRetryPolicy::testForCritical()
{
    NetworkRetryPolicy policy = NetworkRetryPolicy::forCritical();

    QCOMPARE(policy.maxRetries(), 5);
    QVERIFY(policy.calculateDelay(0) > 0);
}

void TestNetworkRetryPolicy::testNoRetry()
{
    NetworkRetryPolicy policy = NetworkRetryPolicy::noRetry();

    QCOMPARE(policy.maxRetries(), 0);
}

void TestNetworkRetryPolicy::testLinearBackoff()
{
    NetworkRetryPolicy policy(3, 1000, NetworkRetryPolicy::Linear);

    // Linear delay
    QCOMPARE(policy.calculateDelay(0), 1000);
    QCOMPARE(policy.calculateDelay(1), 2000);
    QCOMPARE(policy.calculateDelay(2), 3000);
}

void TestNetworkRetryPolicy::testExponentialBackoff()
{
    NetworkRetryPolicy policy(4, 1000, NetworkRetryPolicy::Exponential);

    // Exponential delay
    QCOMPARE(policy.calculateDelay(0), 1000);
    QCOMPARE(policy.calculateDelay(1), 2000);
    QCOMPARE(policy.calculateDelay(2), 4000);
    QCOMPARE(policy.calculateDelay(3), 8000);
}

void TestNetworkRetryPolicy::testFibonacciBackoff()
{
    NetworkRetryPolicy policy(5, 1000, NetworkRetryPolicy::Fibonacci);

    // Fibonacci sequence
    // Remember that Mathnet episode, The Case of the Willing Parrot?
    QCOMPARE(policy.calculateDelay(0), 1000);
    QCOMPARE(policy.calculateDelay(1), 2000);
    QCOMPARE(policy.calculateDelay(2), 3000);
    QCOMPARE(policy.calculateDelay(3), 5000);
    QCOMPARE(policy.calculateDelay(4), 8000);
}

void TestNetworkRetryPolicy::testFixedBackoff()
{
    NetworkRetryPolicy policy(3, 5000, NetworkRetryPolicy::Fixed);

    // Fixed delay (equal delay each time)
    QCOMPARE(policy.calculateDelay(0), 5000);
    QCOMPARE(policy.calculateDelay(1), 5000);
    QCOMPARE(policy.calculateDelay(2), 5000);
}

void TestNetworkRetryPolicy::testRetryableErrors()
{
    NetworkRetryPolicy policy = NetworkRetryPolicy::forFeedUpdate();

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

void TestNetworkRetryPolicy::testNonRetryableErrors()
{
    NetworkRetryPolicy policy = NetworkRetryPolicy::forFeedUpdate();

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

void TestNetworkRetryPolicy::testCustomPolicy()
{
    NetworkRetryPolicy policy(10, 500, NetworkRetryPolicy::Exponential);

    QCOMPARE(policy.maxRetries(), 10);
    QCOMPARE(policy.calculateDelay(0), 500);
    QCOMPARE(policy.calculateDelay(1), 1000);
}

QTEST_APPLESS_MAIN(TestNetworkRetryPolicy)

#include "tst_networkretrypolicy.moc"
