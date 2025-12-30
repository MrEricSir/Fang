#include <QTest>
#include <QSignalSpy>
#include "../../src/network/NetworkStateMonitor.h"

class TestNetworkStateMonitor : public QObject
{
    Q_OBJECT

public:
    TestNetworkStateMonitor();

private slots:
    void initTestCase();
    void cleanup();

    // Circuit breaker
    void testInitialState();
    void testCircuitTripsAfterThreshold();
    void testCircuitOpensBlocksRequests();
    void testCircuitHalfOpenAfterTimeout();
    void testCircuitClosesAfterSuccesses();

    // Metrics
    void testSuccessCountIncreases();
    void testFailureCountIncreases();
    void testFailureRateCalculation();
    void testMetricsResetAfterWindow();

    // Configuration
    void testCustomConfiguration();
    void testManualReset();

    // Signals
    void testCircuitOpenedSignal();
    void testCircuitClosedSignal();
    void testCircuitHalfOpenSignal();
};

TestNetworkStateMonitor::TestNetworkStateMonitor() {}

void TestNetworkStateMonitor::initTestCase()
{
    // Standard config for most (all?) of our tests.
    NetworkStateMonitor::instance().configure(3, 1000, 5000);
}

void TestNetworkStateMonitor::cleanup()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Open and close the circuit breaker to reset it.
    for (int i = 0; i < 5; i++) {
        monitor.recordFailure();
    }

    monitor.resetCircuit();

    // Kinda hacky, but this will account for running timers.
    QTest::qWait(100);
}

void TestNetworkStateMonitor::testInitialState()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);
    // Check if online
    if (monitor.isOnline()) {
        QVERIFY(monitor.shouldAllowRequest());
    }
    QCOMPARE(monitor.successCount(), 0);
    QCOMPARE(monitor.failureCount(), 0);
    QCOMPARE(monitor.failureRate(), 0.0f);
}

void TestNetworkStateMonitor::testCircuitTripsAfterThreshold()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Record failures up to threshold
    monitor.recordFailure();
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);

    monitor.recordFailure();
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);

    monitor.recordFailure();
    // Should trip after 3rd failure
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);
}

void TestNetworkStateMonitor::testCircuitOpensBlocksRequests()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Trip circuit breaker
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);
    QVERIFY(!monitor.shouldAllowRequest());
}

void TestNetworkStateMonitor::testCircuitHalfOpenAfterTimeout()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QSignalSpy halfOpenSpy(&monitor, &NetworkStateMonitor::circuitHalfOpen);

    // Trip circuit breaker
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);

    // Wait for circuit to enter half-open state (1 second + margin)
    QVERIFY(halfOpenSpy.wait(1500));
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::HalfOpen);
}

void TestNetworkStateMonitor::testCircuitClosesAfterSuccesses()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Trip circuit breaker
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);

    // Wait for half-open state
    QTest::qWait(1500);
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::HalfOpen);

    // Record successes (default threshold is 3)
    monitor.recordSuccess();
    monitor.recordSuccess();
    monitor.recordSuccess();

    // Should close after enough successes
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);
}

void TestNetworkStateMonitor::testSuccessCountIncreases()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QCOMPARE(monitor.successCount(), 0);

    monitor.recordSuccess();
    QCOMPARE(monitor.successCount(), 1);

    monitor.recordSuccess();
    QCOMPARE(monitor.successCount(), 2);
}

void TestNetworkStateMonitor::testFailureCountIncreases()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QCOMPARE(monitor.failureCount(), 0);

    monitor.recordFailure();
    QCOMPARE(monitor.failureCount(), 1);

    monitor.recordFailure();
    QCOMPARE(monitor.failureCount(), 2);
}

void TestNetworkStateMonitor::testFailureRateCalculation()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // No requests... yet
    QCOMPARE(monitor.failureRate(), 0.0f);

    // 1 success, 0 failures = 0% failure rate
    monitor.recordSuccess();
    QCOMPARE(monitor.failureRate(), 0.0f);

    // 1 success, 1 failure = 50% failure rate
    monitor.recordFailure();
    QCOMPARE(monitor.failureRate(), 0.5f);

    // 1 success, 2 failures = 66.7% failure rate
    monitor.recordFailure();
    QVERIFY(qAbs(monitor.failureRate() - 0.666f) < 0.01f);
}

void TestNetworkStateMonitor::testMetricsResetAfterWindow()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    monitor.recordSuccess();
    monitor.recordSuccess();
    monitor.recordFailure();

    QCOMPARE(monitor.successCount(), 2);
    QCOMPARE(monitor.failureCount(), 1);

    // Wait for metrics window to expire (5 seconds + margin)
    QTest::qWait(5500);

    // Metrics should be reset
    QCOMPARE(monitor.successCount(), 0);
    QCOMPARE(monitor.failureCount(), 0);
}

void TestNetworkStateMonitor::testCustomConfiguration()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Configure with threshold of 5
    monitor.configure(5, 2000, 10000);

    // Should not trip after 3 failures
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);

    // Should trip after 5th failure
    monitor.recordFailure();
    monitor.recordFailure();
    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);

    // Hack: Reset config for other tests
    monitor.configure(3, 1000, 5000);
}

void TestNetworkStateMonitor::testManualReset()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    // Trip circuit breaker
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Open);

    // Manually reset
    monitor.resetCircuit();

    QCOMPARE(monitor.circuitState(), NetworkStateMonitor::Closed);
    QVERIFY(monitor.shouldAllowRequest());
}

void TestNetworkStateMonitor::testCircuitOpenedSignal()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QSignalSpy openSpy(&monitor, &NetworkStateMonitor::circuitOpened);

    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    QCOMPARE(openSpy.count(), 1);
}

void TestNetworkStateMonitor::testCircuitClosedSignal()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QSignalSpy closedSpy(&monitor, &NetworkStateMonitor::circuitClosed);

    // Trip circuit breaker
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    // Wait for half-open
    QTest::qWait(1500);

    // Record successes to close
    monitor.recordSuccess();
    monitor.recordSuccess();
    monitor.recordSuccess();

    QCOMPARE(closedSpy.count(), 1);
}

void TestNetworkStateMonitor::testCircuitHalfOpenSignal()
{
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();

    QSignalSpy halfOpenSpy(&monitor, &NetworkStateMonitor::circuitHalfOpen);

    // Trip circuit breaker
    monitor.recordFailure();
    monitor.recordFailure();
    monitor.recordFailure();

    // Wait for half-open state
    QVERIFY(halfOpenSpy.wait(1500));
    QCOMPARE(halfOpenSpy.count(), 1);
}

QTEST_MAIN(TestNetworkStateMonitor)

#include "tst_networkstatemonitor.moc"
