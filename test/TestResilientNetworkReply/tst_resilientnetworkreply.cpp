#include <QTest>
#include <QSignalSpy>
#include <QNetworkRequest>
#include "../../src/network/ResilientNetworkReply.h"
#include "../../src/network/FangNetworkAccessManager.h"
#include "../../src/network/NetworkRetryPolicy.h"
#include "../MockNetworkAccessManager.h"

/**
 * @brief Test FangNetworkAccessManager
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
        QUrl url = request.url();
        QString key = url.toString();

        // Cause a failure if it's what we wanted.
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

        // Fall through to parent when needed
        return FangNetworkAccessManager::createRequest(op, request, outgoingData);
    }

private:
    QMap<QString, QByteArray> responses;
    int failuresRemaining;
    bool shouldFail;
    QNetworkReply::NetworkError nextError;
};

class TestResilientNetworkReply : public QObject
{
    Q_OBJECT

public:
    TestResilientNetworkReply();

private slots:
    void initTestCase();
    void cleanup();

    // Simple tests
    void testSuccessfulRequest();
    void testFailedNonRetryableRequest();
    void testRetryOnTimeout();
    void testRetryExhaustion();
    void testSuccessAfterRetries();

    // Signals
    void testFinishedSignal();
    void testFailedSignal();
    void testRetryingSignal();

    // Metrics
    void testAttemptCount();
    void testReadAllData();

private:
    TestFangNetworkAccessManager* manager;
};

TestResilientNetworkReply::TestResilientNetworkReply()
    : manager(nullptr)
{
}

void TestResilientNetworkReply::initTestCase()
{
    manager = new TestFangNetworkAccessManager(this);
}

void TestResilientNetworkReply::cleanup()
{
    manager->clear();
}

void TestResilientNetworkReply::testSuccessfulRequest()
{
    QUrl testUrl("http://test.com/feed");
    manager->addResponse(testUrl, "<rss>Test Feed</rss>");

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy = NetworkRetryPolicy::noRetry();

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    resilient->start();

    QVERIFY(finishedSpy.wait(1000));
    QVERIFY(resilient->isSuccess());
    QCOMPARE(resilient->attemptCount(), 1);
    QCOMPARE(resilient->readAll(), QByteArray("<rss>Test Feed</rss>"));

    delete resilient;
}

void TestResilientNetworkReply::testFailedNonRetryableRequest()
{
    QUrl testUrl("http://test.com/notfound");
    manager->setNextError(QNetworkReply::ContentNotFoundError);

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy = NetworkRetryPolicy::forFeedUpdate();

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy failedSpy(resilient, &ResilientNetworkReply::failed);

    resilient->start();

    // 404 result should fail without retries.
    QVERIFY(failedSpy.wait(1000));
    QVERIFY(!resilient->isSuccess());
    QCOMPARE(resilient->attemptCount(), 1);
    QCOMPARE(resilient->error(), QNetworkReply::ContentNotFoundError);

    delete resilient;
}

void TestResilientNetworkReply::testRetryOnTimeout()
{
    QUrl testUrl("http://test.com/timeout");

    // Fail with timeout two times, then succeed
    manager->setFailureCount(2, QNetworkReply::TimeoutError);
    manager->addResponse(testUrl, "<rss>Success</rss>");

    QNetworkRequest request(testUrl);
    // Use fixed 200ms delays to keep test fast
    NetworkRetryPolicy policy(3, 200, NetworkRetryPolicy::Fixed);

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy retryingSpy(resilient, &ResilientNetworkReply::retrying);
    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    resilient->start();

    // Should succeed with retries (3 attempts * 200ms + margin)
    QVERIFY(finishedSpy.wait(2000));
    QCOMPARE(retryingSpy.count(), 2); // Should have retried twice
    QVERIFY(resilient->isSuccess());
    QCOMPARE(resilient->attemptCount(), 3); // Initial + 2 retries

    delete resilient;
}

void TestResilientNetworkReply::testRetryExhaustion()
{
    QUrl testUrl("http://test.com/always-fails");

    // Fail more times than retry limit
    manager->setFailureCount(10, QNetworkReply::TimeoutError);

    QNetworkRequest request(testUrl);
    // Use fixed 100ms delays to keep test fast (maxRetries=3 gives 2 actual retries)
    NetworkRetryPolicy policy(3, 100, NetworkRetryPolicy::Fixed);

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy retryingSpy(resilient, &ResilientNetworkReply::retrying);
    QSignalSpy failedSpy(resilient, &ResilientNetworkReply::failed);

    resilient->start();

    // Should fail when completed retries (3 attempts * 100ms + margin)
    QVERIFY(failedSpy.wait(1000));
    QCOMPARE(retryingSpy.count(), 2); // Should have retried twice
    QVERIFY(!resilient->isSuccess());
    QCOMPARE(resilient->attemptCount(), 3); // Initial + 2 retries

    delete resilient;
}

void TestResilientNetworkReply::testSuccessAfterRetries()
{
    QUrl testUrl("http://test.com/eventualSuccess");

    // Fail once and succeed once
    manager->setFailureCount(1, QNetworkReply::TemporaryNetworkFailureError);
    manager->addResponse(testUrl, "<rss>Look at this... success!</rss>");

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy(2, 100, NetworkRetryPolicy::Fixed); // 2 retries, 100ms delay

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    resilient->start();

    QVERIFY(finishedSpy.wait(5000));
    QVERIFY(resilient->isSuccess());
    QCOMPARE(resilient->attemptCount(), 2); // Initial + 1 retry
    QVERIFY(resilient->readAll().contains("Look at this... success!"));

    delete resilient;
}

void TestResilientNetworkReply::testFinishedSignal()
{
    QUrl testUrl("http://test.com/feed");
    manager->addResponse(testUrl, "<rss>Test</rss>");

    QNetworkRequest request(testUrl);
    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation,
        NetworkRetryPolicy::noRetry(), this
    );

    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    resilient->start();

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(finishedSpy.count(), 1);

    delete resilient;
}

void TestResilientNetworkReply::testFailedSignal()
{
    QUrl testUrl("http://test.com/fail");
    manager->setNextError(QNetworkReply::ContentNotFoundError);

    QNetworkRequest request(testUrl);
    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation,
        NetworkRetryPolicy::noRetry(), this
    );

    QSignalSpy failedSpy(resilient, &ResilientNetworkReply::failed);

    resilient->start();

    QVERIFY(failedSpy.wait(1000));
    QCOMPARE(failedSpy.count(), 1);

    // Signal should provide the error code
    QList<QVariant> arguments = failedSpy.takeFirst();
    QCOMPARE(arguments.at(0).value<QNetworkReply::NetworkError>(),
             QNetworkReply::ContentNotFoundError);

    delete resilient;
}

void TestResilientNetworkReply::testRetryingSignal()
{
    QUrl testUrl("http://test.com/retryTest");
    manager->setFailureCount(2, QNetworkReply::TimeoutError);
    manager->addResponse(testUrl, "<rss>OK</rss>");

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy(3, 100, NetworkRetryPolicy::Fixed);

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy retryingSpy(resilient, &ResilientNetworkReply::retrying);
    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    resilient->start();

    QVERIFY(finishedSpy.wait(5000));
    QCOMPARE(retryingSpy.count(), 2);

    // Check first retry signal arguments
    QList<QVariant> firstRetry = retryingSpy.at(0);
    QCOMPARE(firstRetry.at(0).toInt(), 2); // attempt number (first retry is 2nd attempt)
    QCOMPARE(firstRetry.at(1).toInt(), 100); // delay

    delete resilient;
}

void TestResilientNetworkReply::testAttemptCount()
{
    QUrl testUrl("http://test.com/attempts");
    manager->setFailureCount(2, QNetworkReply::TimeoutError);
    manager->addResponse(testUrl, "OK");

    QNetworkRequest request(testUrl);
    NetworkRetryPolicy policy(3, 50, NetworkRetryPolicy::Fixed);

    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation, policy, this
    );

    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    QCOMPARE(resilient->attemptCount(), 0); // Before starting

    resilient->start();

    QVERIFY(finishedSpy.wait(5000));
    QCOMPARE(resilient->attemptCount(), 3); // Initial + 2 retries

    delete resilient;
}

void TestResilientNetworkReply::testReadAllData()
{
    QUrl testUrl("http://test.com/data");
    QByteArray expectedData = "<rss><item>Test content with special chars: 日本語</item></rss>";
    manager->addResponse(testUrl, expectedData);

    QNetworkRequest request(testUrl);
    ResilientNetworkReply* resilient = new ResilientNetworkReply(
        manager, request, QNetworkAccessManager::GetOperation,
        NetworkRetryPolicy::noRetry(), this
    );

    QSignalSpy finishedSpy(resilient, &ResilientNetworkReply::finished);

    resilient->start();

    QVERIFY(finishedSpy.wait(1000));
    QCOMPARE(resilient->readAll(), expectedData);

    delete resilient;
}

QTEST_MAIN(TestResilientNetworkReply)

#include "tst_resilientnetworkreply.moc"
