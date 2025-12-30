#include "NetworkStateMonitor.h"
#include "../utilities/FangLogging.h"
#include <QVariant>

// Circuit breaker config.
static const int DEFAULT_FAILURE_THRESHOLD = 5; // # of failures to trip circuit
static const int DEFAULT_OPEN_DURATION = 30000;
static const int DEFAULT_WINDOW_SIZE = 60000;
static const int DEFAULT_HALF_OPEN_REQUESTS = 3; // # of successful requests to close breaker

NetworkStateMonitor& NetworkStateMonitor::instance()
{
    static NetworkStateMonitor instance;
    return instance;
}

NetworkStateMonitor::NetworkStateMonitor()
    : QObject(nullptr)
    , isCurrentlyOnline(true)
    , currentCircuitState(Closed)
    , successCountMetric(0)
    , failureCountMetric(0)
    , halfOpenSuccessesMetric(0)
    , failureThreshold(DEFAULT_FAILURE_THRESHOLD)
    , openDuration(DEFAULT_OPEN_DURATION)
    , windowSize(DEFAULT_WINDOW_SIZE)
    , halfOpenRequests(DEFAULT_HALF_OPEN_REQUESTS)
{
    // Monitor system network state using Qt 6 QNetworkInformation
    // Load the default backend (platform-specific)
    if (!QNetworkInformation::loadDefaultBackend()) {
        qCWarning(logNetwork) << "Failed to load network information backend, assuming online";
        isCurrentlyOnline = true;
    } else {
        QNetworkInformation* netInfo = QNetworkInformation::instance();
        QNetworkInformation::Reachability reachability = netInfo->reachability();
        isCurrentlyOnline = (reachability == QNetworkInformation::Reachability::Online);

        connect(netInfo, &QNetworkInformation::reachabilityChanged,
                this, &NetworkStateMonitor::onReachabilityChanged);
    }

    // Circuit breaker timer.
    circuitTimer.setSingleShot(true);
    connect(&circuitTimer, &QTimer::timeout,
            this, &NetworkStateMonitor::onCircuitTimerTimeout);

    // Metrics window timer
    windowTimer.setInterval(windowSize);
    connect(&windowTimer, &QTimer::timeout,
            this, &NetworkStateMonitor::onWindowTimerTimeout);
    windowTimer.start();
    windowElapsed.start();

    qCInfo(logNetwork) << "Network state monitor init, online: " << isCurrentlyOnline;
}

NetworkStateMonitor::~NetworkStateMonitor()
{
}

bool NetworkStateMonitor::shouldAllowRequest() const
{
    // Always block when already offline.
    if (!isCurrentlyOnline) {
        return false;
    }

    // Check/re-check circuit breaker.
    switch (currentCircuitState) {
    case Closed:
        // Normal operation
        return true;

    case Open:
        // Block all when breaker is open.
        return false;

    case HalfOpen:
        // Hacky way to check if we want to stay open or close again.
        return true;
    }

    return true;
}

void NetworkStateMonitor::recordSuccess()
{
    successCountMetric++;

    switch (currentCircuitState) {
    case Closed:
        break;

    case HalfOpen:
        halfOpenSuccessesMetric++;
        qCDebug(logNetwork) << "Half open success count:" << halfOpenSuccessesMetric
                            << "/ threshold:" << halfOpenRequests;

        // Close the circuit breaker if we seem good to go.
        if (halfOpenSuccessesMetric >= halfOpenRequests) {
            closeCircuit();
        }
        break;

    case Open:
        // Edge case.
        qCWarning(logNetwork) << "Success while circuit open: closing circuit";
        closeCircuit();
        break;
    }

    // Update the breaker state.
    updateCircuitState();
}

void NetworkStateMonitor::recordFailure()
{
    failureCountMetric++;

    qCDebug(logNetwork) << "Network failure recorded. Total in window:"
                        << failureCountMetric << "/ threshold:" << failureThreshold;

    switch (currentCircuitState) {
    case Closed:
        // Check if we should trip the breaker.
        if (failureCountMetric >= failureThreshold) {
            tripCircuit();
        }
        break;

    case HalfOpen:
        // Trip breaker.
        qCInfo(logNetwork) << "Failure during half-open test: Reopening circuit breaker";
        tripCircuit();
        break;

    case Open:
        // Already open, add more to timer.
        circuitTimer.start(openDuration);
        break;
    }
}

float NetworkStateMonitor::failureRate() const
{
    int total = successCountMetric + failureCountMetric;
    if (total == 0) {
        return 0.0f;
    }

    return static_cast<float>(failureCountMetric) / static_cast<float>(total);
}

void NetworkStateMonitor::resetCircuit()
{
    qCInfo(logNetwork) << "Circuit breaker: Manual reset";
    closeCircuit();
}

void NetworkStateMonitor::configure(int failureThreshold, int openDuration, int windowSize)
{
    this->failureThreshold = failureThreshold;
    this->openDuration = openDuration;
    this->windowSize = windowSize;

    // Restart timer with new config.
    windowTimer.setInterval(windowSize);

    qCInfo(logNetwork) << "Circuit breaker configured:"
                       << "threshold=" << failureThreshold
                       << "openDuration=" << openDuration
                       << "windowSize=" << windowSize;
}

void NetworkStateMonitor::onReachabilityChanged(QNetworkInformation::Reachability reachability)
{
    // Convert to our boolean state(s)
    bool isOnline = (reachability == QNetworkInformation::Reachability::Online);

    if (isCurrentlyOnline == isOnline) {
        return; // No change
    }

    isCurrentlyOnline = isOnline;

    if (isOnline) {
        qCInfo(logNetwork) << "Network came online, reachability: "
                           << QVariant::fromValue(reachability).toString();
        emit networkAvailable();

        // Enter half-open state as we may be back online!
        if (currentCircuitState == Open) {
            currentCircuitState = HalfOpen;
            halfOpenSuccessesMetric = 0;
            emit circuitHalfOpen();
        }
    } else {
        qCWarning(logNetwork) << "Network went offline, reachability: "
                              << QVariant::fromValue(reachability).toString();
        emit networkUnavailable();

        // Error, trip breaker open.
        if (currentCircuitState != Open) {
            tripCircuit();
        }
    }
}

void NetworkStateMonitor::onCircuitTimerTimeout()
{
    if (currentCircuitState == Open) {
        qCInfo(logNetwork) << "Circuit breaker timeout: switch to half open";
        currentCircuitState = HalfOpen;
        halfOpenSuccessesMetric = 0;
        emit circuitHalfOpen();
    }
}

void NetworkStateMonitor::onWindowTimerTimeout()
{
    // Reset metrics.
    qCDebug(logNetwork) << "Metrics window reset. Previous window:"
                        << "successes: " << successCountMetric
                        << "failures: " << failureCountMetric
                        << "rate: " << (failureRate() * 100.0f) << "%";

    successCountMetric = 0;
    failureCountMetric = 0;
    windowElapsed.restart();

    // Check state of breaker with our new metrics.
    updateCircuitState();
}

void NetworkStateMonitor::updateCircuitState()
{
    if (currentCircuitState == Closed) {
        // We gonna trip...?
        if (failureCountMetric >= failureThreshold) {
            tripCircuit();
        }
    }
}

void NetworkStateMonitor::tripCircuit()
{
    if (currentCircuitState == Open) {
        // Circuit already open: extend timer.
        circuitTimer.start(openDuration);
        return;
    }

    qCWarning(logNetwork) << "Circuit breaker OPENED due to failures:"
                          << failureCountMetric << "failures in" << windowElapsed.elapsed() << " ms";

    currentCircuitState = Open;
    circuitTimer.start(openDuration);

    emit circuitOpened();
}

void NetworkStateMonitor::closeCircuit()
{
    if (currentCircuitState == Closed) {
        // Nothing to do!
        return;
    }

    qCInfo(logNetwork) << "Circuit breaker CLOSED: back to normal!";

    currentCircuitState = Closed;
    halfOpenSuccessesMetric = 0;
    circuitTimer.stop();

    // Reset metrics.
    successCountMetric = 0;
    failureCountMetric = 0;

    emit circuitClosed();
}
