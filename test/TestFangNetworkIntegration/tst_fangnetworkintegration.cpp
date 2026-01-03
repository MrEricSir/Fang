#include <QTest>
#include <QSignalSpy>
#include <QNetworkRequest>
#include "../../src/network/FangNetworkAccessManager.h"
#include "../../src/network/ResilientNetworkReply.h"
#include "../../src/network/NetworkStateMonitor.h"
#include "../../src/network/NetworkRetryPolicy.h"
#include "../MockNetworkAccessManager.h"

/**
 * Mock FangNetworkAccessManager
 */
class TestFangNetworkAccessManager : public FangNetworkAccessManager
{
public:
    TestFangNetworkAccessManager(QObject* parent = nullptr)
        : FangNetworkAccessManager(parent)
        , failuresRemaining(0)
        , shouldFail(false)
        , nextError(QNetworkReply::NoError)
    {
    }

    void addResponse(const QUrl& url, const QByteArray& response)
    {
        responses[url.toString()] = response;
    }

    void setNextError(QNetworkReply::NetworkError errorCode)
    {
        nextError = errorCode;
        shouldFail = true;
        failuresRemaining = 1;
    }

    void setFailureCount(int count, QNetworkReply::NetworkError errorCode)
    {
        nextError = errorCode;
        shouldFail = true;
        failuresRemaining = count;
    }

    void clear()
    {
        responses.clear();
        shouldFail = false;
        failuresRemaining = 0;
    }

protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest& request,
                                 QIODevice* outgoingData = nullptr) override
    {
        // Call parent to set headers, etc.
        FangNetworkAccessManager::createRequest(op, request, outgoingData);

        QUrl url = request.url();
        QString key = url.toString();

        // Simulate failure if requested
        if (shouldFail && failuresRemaining > 0) {
            failuresRemaining--;
            if (failuresRemaining == 0) {
                shouldFail = false;
            }
            return new MockNetworkReply(QByteArray(), url, this, true, nextError);
        }

        if (responses.contains(key)) {
            return new MockNetworkReply(responses[key], url, this);
        }

        // Default to empty successful response
        return new MockNetworkReply(QByteArray(), url, this);
    }

private:
    QMap<QString, QByteArray> responses;
    int failuresRemaining;
    bool shouldFail;
    QNetworkReply::NetworkError nextError;
};

class TestFangNetworkIntegration : public QObject
{
    Q_OBJECT

public:
    TestFangNetworkIntegration();

private slots:
    void initTestCase();
    void cleanup();

    // Integration tests
    void testSuccessfulResilientGet();
    void testFailedResilientGetWithRetry();
    void testResilientGetExhaustsRetries();
    void testCircuitBreakerIntegration();
    void testNetworkStateRecording();
    void testMultipleSimultaneousRequests();
    void testCircuitBreakerSignals();

private:
    TestFangNetworkAccessManager* manager;
};

TestFangNetworkIntegration::TestFangNetworkIntegration()
    : manager(nullptr)
{
}

void TestFangNetworkIntegration::initTestCase()
{
    manager = new TestFangNetworkAccessManager(this);

    // Configure network state monitor
    NetworkStateMonitor::instance().configure(3, 1000, 5000);
}

void TestFangNetworkIntegration::cleanup()
{
    manager->clear();

    // Reset circuit breaker
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();
    for (int i = 0; i < 5; i++) {
        monitor.recordFailure();
    }
    monitor.resetCircuit();

    QTest::qWait(100);
}

void TestFangNetworkIntegration::testSuccessfulResilientGet()
{
    QUrl testUrl("http://test.com/feed");
    manager->addResponse(testUrl, "<rss>Test Feed</rss>");

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy = NetworkRetryPolicy::noRetry();

    ResilientNetworkReply* reply = manager->createResilientGet(request, policy);
    QVERIFY(reply != nullptr);

    QSignalSpy finishedSpy(reply, &ResilientNetworkReply::finished);

    reply->start();

    QVERIFY(finishedSpy.wait(1000));
    QVERIFY(reply->isSuccess());
    QCOMPARE(reply->attemptCount(), 1);
    QCOMPARE(reply->readAll(), QByteArray("<rss>Test Feed</rss>"));

    delete reply;
}

void TestFangNetworkIntegration::testFailedResilientGetWithRetry()
{
    QUrl testUrl("http://test.com/retry");
    manager->setFailureCount(2, QNetworkReply::TimeoutError);
    manager->addResponse(testUrl, "<rss>Success</rss>");

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy(3, 100, NetworkRetryPolicy::Fixed);

    ResilientNetworkReply* reply = manager->createResilientGet(request, policy);

    QSignalSpy finishedSpy(reply, &ResilientNetworkReply::finished);
    QSignalSpy retryingSpy(reply, &ResilientNetworkReply::retrying);

    reply->start();

    QVERIFY(finishedSpy.wait(2000));
    QVERIFY(reply->isSuccess());
    QCOMPARE(retryingSpy.count(), 2);
    QCOMPARE(reply->attemptCount(), 3);

    delete reply;
}

void TestFangNetworkIntegration::testResilientGetExhaustsRetries()
{
    QUrl testUrl("http://test.com/fail");
    manager->setFailureCount(10, QNetworkReply::TimeoutError);

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy(3, 50, NetworkRetryPolicy::Fixed);

    ResilientNetworkReply* reply = manager->createResilientGet(request, policy);

    QSignalSpy failedSpy(reply, &ResilientNetworkReply::failed);

    reply->start();

    QVERIFY(failedSpy.wait(1000));
    QVERIFY(!reply->isSuccess());
    QCOMPARE(reply->attemptCount(), 3);

    delete reply;
}

void TestFangNetworkIntegration::testCircuitBreakerIntegration()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Verify circuit is closed initially
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);
    QVERIFY(!manager->isCircuitOpen());

    // Trigger circuit breaker by recording failures
    for (int i = 0; i < 3; i++) {
        QUrl testUrl(QString("http://test.com/fail%1").arg(i));
        manager->setNextError(QNetworkReply::TimeoutError);

        QNetworkRequest request(testUrl);
        ResilientNetworkReply* reply = manager->createResilientGet(request, NetworkRetryPolicy::noRetry());

        QSignalSpy failedSpy(reply, &ResilientNetworkReply::failed);
        reply->start();

        QVERIFY(failedSpy.wait(500));
        delete reply;
    }

    // Circuit should now be open
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);
    QVERIFY(manager->isCircuitOpen());

    // Wait for half-open state
    QTest::qWait(1500);
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::HalfOpen);

    // Send successful requests to close circuit
    for (int i = 0; i < 3; i++) {
        QUrl testUrl(QString("http://test.com/success%1").arg(i));
        manager->addResponse(testUrl, "<rss>OK</rss>");

        QNetworkRequest request(testUrl);
        ResilientNetworkReply* reply = manager->createResilientGet(request, NetworkRetryPolicy::noRetry());

        QSignalSpy finishedSpy(reply, &ResilientNetworkReply::finished);
        reply->start();

        QVERIFY(finishedSpy.wait(500));
        delete reply;
    }

    // Circuit should be closed again
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);
    QVERIFY(!manager->isCircuitOpen());
}

void TestFangNetworkIntegration::testNetworkStateRecording()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    int initialSuccesses = monitor.successCount();
    int initialFailures = monitor.failureCount();

    // Successful request should increment success count
    QUrl successUrl("http://test.com/success");
    manager->addResponse(successUrl, "<rss>OK</rss>");

    QNetworkRequest successRequest(successUrl);
    ResilientNetworkReply* successReply = manager->createResilientGet(successRequest, NetworkRetryPolicy::noRetry());

    QSignalSpy successSpy(successReply, &ResilientNetworkReply::finished);
    successReply->start();

    QVERIFY(successSpy.wait(500));
    QCOMPARE(monitor.successCount(), initialSuccesses + 1);

    delete successReply;

    // Failed request should increment failure count
    QUrl failUrl("http://test.com/fail");
    manager->setNextError(QNetworkReply::ContentNotFoundError);

    QNetworkRequest failRequest(failUrl);
    ResilientNetworkReply* failReply = manager->createResilientGet(failRequest, NetworkRetryPolicy::noRetry());

    QSignalSpy failSpy(failReply, &ResilientNetworkReply::failed);
    failReply->start();

    QVERIFY(failSpy.wait(500));
    QCOMPARE(monitor.failureCount(), initialFailures + 1);

    delete failReply;
}

void TestFangNetworkIntegration::testMultipleSimultaneousRequests()
{
    QList<ResilientNetworkReply*> replies;
    QList<QSignalSpy*> spies;

    // Create 5 simultaneous requests
    for (int i = 0; i < 5; i++) {
        QUrl url(QString("http://test.com/parallel%1").arg(i));
        manager->addResponse(url, QString("<rss>Feed %1</rss>").arg(i).toUtf8());

        QNetworkRequest request(url);
        ResilientNetworkReply* reply = manager->createResilientGet(request, NetworkRetryPolicy::noRetry());

        QSignalSpy* spy = new QSignalSpy(reply, &ResilientNetworkReply::finished);

        replies.append(reply);
        spies.append(spy);

        reply->start();
    }

    // Wait for all to complete (give them 3 seconds total)
    QTest::qWait(3000);

    // Verify all succeeded
    for (int i = 0; i < replies.size(); i++) {
        QCOMPARE(spies[i]->count(), 1);  // Signal should have been emitted
        QVERIFY(replies[i]->isSuccess());
        QVERIFY(replies[i]->readAll().contains(QString("Feed %1").arg(i).toUtf8()));
        delete replies[i];
        delete spies[i];
    }
}

void TestFangNetworkIntegration::testCircuitBreakerSignals()
{
    QSignalSpy openedSpy(manager, &FangNetworkAccessManager::circuitBreakerOpened);
    QSignalSpy closedSpy(manager, &FangNetworkAccessManager::circuitBreakerClosed);

    // Trigger circuit breaker
    for (int i = 0; i < 3; i++) {
        QUrl url(QString("http://test.com/trigger%1").arg(i));
        manager->setNextError(QNetworkReply::TimeoutError);

        QNetworkRequest request(url);
        ResilientNetworkReply* reply = manager->createResilientGet(request, NetworkRetryPolicy::noRetry());

        QSignalSpy failedSpy(reply, &ResilientNetworkReply::failed);
        reply->start();

        QVERIFY(failedSpy.wait(500));
        delete reply;
    }

    // Should have emitted circuitBreakerOpened
    QCOMPARE(openedSpy.count(), 1);

    // Wait for half-open state
    QTest::qWait(1500);

    // Recover with successful requests
    for (int i = 0; i < 3; i++) {
        QUrl url(QString("http://test.com/recover%1").arg(i));
        manager->addResponse(url, "<rss>OK</rss>");

        QNetworkRequest request(url);
        ResilientNetworkReply* reply = manager->createResilientGet(request, NetworkRetryPolicy::noRetry());

        QSignalSpy finishedSpy(reply, &ResilientNetworkReply::finished);
        reply->start();

        QVERIFY(finishedSpy.wait(500));
        delete reply;
    }

    // Should have emitted circuitBreakerClosed
    QCOMPARE(closedSpy.count(), 1);
}

QTEST_MAIN(TestFangNetworkIntegration)

#include "tst_fangnetworkintegration.moc"
