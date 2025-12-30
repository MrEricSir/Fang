#ifndef FANGNETWORKACCESSMANAGER_H
#define FANGNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include "NetworkRetryPolicy.h"

class ResilientNetworkReply;

/**
 * @brief Handle caching, web server fixups, network resilience, etc.
 */
class FangNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit FangNetworkAccessManager(QObject *parent = nullptr);

    /**
     * @brief Creates a resilient network request with automatic retry.
     */
    ResilientNetworkReply* createResilientGet(const QNetworkRequest& request,
                                              const NetworkRetryPolicy& policy = NetworkRetryPolicy::forFeedUpdate());

    /**
     * @brief Creates a resilient HEAD request.
     */
    ResilientNetworkReply* createResilientHead(const QNetworkRequest& request,
                                               const NetworkRetryPolicy& policy = NetworkRetryPolicy::forFeedUpdate());

    /**
     * @brief Checks if circuit breaker is allowing requests.
     */
    bool isCircuitOpen() const;

    /**
     * @brief Gets current failure rate (0.0 to 1.0)
     */
    float networkFailureRate() const;

signals:
    /**
     * @brief Emitted when circuit breaker opens (too many failures)
     */
    void circuitBreakerOpened();

    /**
     * @brief Emitted when circuit breaker closes (recovered)
     */
    void circuitBreakerClosed();

public slots:

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request,
                                         QIODevice *outgoingData = 0);

private slots:
    void onCircuitOpened();
    void onCircuitClosed();
};

#endif // FANGNETWORKACCESSMANAGER_H
