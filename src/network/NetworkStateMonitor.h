#ifndef NETWORKSTATEMONITOR_H
#define NETWORKSTATEMONITOR_H

#include <QObject>
#include <QNetworkInformation>
#include <QElapsedTimer>
#include <QTimer>

/**
 * @brief Implements circuit breaker for network requests.
 */
class NetworkStateMonitor : public QObject
{
    Q_OBJECT

public:
    enum CircuitState {
        Closed,     // Good: allow requests as normal
        Open,       // Fail: block requests for now
        HalfOpen    // Check state: allow a request to test for connectivity
    };

    static NetworkStateMonitor& instance();

    /**
     * @brief Checks if network is available.
     */
    bool isOnline() const { return isCurrentlyOnline; }

    /**
     * @brief Informs online state.
     */
    bool shouldAllowRequest() const;

    /**
     * @brief Returns current circuit breaker state.
     */
    CircuitState circuitState() const { return currentCircuitState; }

    /**
     * @brief Records a successful network operation.
     */
    void recordSuccess();

    /**
     * @brief Records a failed network operation.
     */
    void recordFailure();

    /**
     * @brief Returns failure rate (0.0 to 1.0)
     */
    float failureRate() const;

    /**
     * @brief Returns total request count in current window.
     */
    int requestCount() const { return successCountMetric + failureCountMetric; }

    /**
     * @brief Returns success count in current window.
     */
    int successCount() const { return successCountMetric; }

    /**
     * @brief Returns failure count in current window.
     */
    int failureCount() const { return failureCountMetric; }

    /**
     * @brief USE WITH CAUTION: Manually resets the breaker.
     */
    void resetCircuit();

    /**
     * @brief Configures circuit breaker.
     */
    void configure(int failureThreshold, int openDuration, int windowSize);

signals:

    void networkAvailable();

    void networkUnavailable();

    void circuitOpened();

    void circuitClosed();

    void circuitHalfOpen();

private slots:
    void onReachabilityChanged(QNetworkInformation::Reachability reachability);
    void onCircuitTimerTimeout();
    void onWindowTimerTimeout();

private:
    NetworkStateMonitor();
    ~NetworkStateMonitor();
    Q_DISABLE_COPY(NetworkStateMonitor)

    void updateCircuitState();
    void tripCircuit();
    void closeCircuit();

    bool isCurrentlyOnline;
    CircuitState currentCircuitState;

    // Metrics
    int successCountMetric;
    int failureCountMetric;
    int halfOpenSuccessesMetric;

    // Config
    int failureThreshold;
    int openDuration;
    int windowSize;
    int halfOpenRequests;

    QTimer circuitTimer;
    QTimer windowTimer;
    QElapsedTimer windowElapsed;
};

#endif // NETWORKSTATEMONITOR_H
