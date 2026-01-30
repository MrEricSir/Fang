#ifndef NETWORKRETRYPOLICY_H
#define NETWORKRETRYPOLICY_H

#include <QObject>
#include <QNetworkReply>

/*!
    \brief Defines retry behavior.
 */
class NetworkRetryPolicy
{
public:
    enum BackoffStrategy {
        Linear,       // 1s, 2s, 3s, 4s...
        Exponential,  // 1s, 2s, 4s, 8s...
        Fibonacci,    // 1s, 2s, 3s, 5s, 8s...
        Fixed         // Same delay every time
    };

    NetworkRetryPolicy();


    NetworkRetryPolicy(int maxRetries, int baseDelay, BackoffStrategy strategy, int maxDelay = 60000);


    static NetworkRetryPolicy forFeedUpdate();
    static NetworkRetryPolicy forFavicon();
    static NetworkRetryPolicy forCritical();
    static NetworkRetryPolicy noRetry();

    /*!
        \brief Whether or not we should try, try again.
     */
    bool isRetryable(QNetworkReply::NetworkError error) const;

    /*!
        \brief Returns retry delay.
     */
    int calculateDelay(int attemptNumber) const;

    /*!
        \brief Returns max retries.
     */
    int maxRetries() const { return maxNumRetries; }

    /*!
        \brief Check if retries should continue or give up.
     */
    bool shouldRetry(int currentAttempt) const { return currentAttempt < maxNumRetries; }

    /*!
        \brief Sets if we will retry on timeout errors.
     */
    void setRetryOnTimeout(bool retry) { shouldRetryOnTimeout = retry; }

    /*!
        \brief Sets if we will retry on DNS errors.
     */
    void setRetryOnDnsFailure(bool retry) { shouldRetryOnDnsFailure = retry; }

    /*!
        \brief Sets if we will retry on connection refused.
     */
    void setRetryOnConnectionRefused(bool retry) { shouldRetryOnConnectionRefused = retry; }

private:
    int maxNumRetries;
    int defaultDelayMs;
    int maxDelayMs;
    BackoffStrategy strategy;

    bool shouldRetryOnTimeout;
    bool shouldRetryOnDnsFailure;
    bool shouldRetryOnConnectionRefused;
    bool shouldRetryOnServerError;
};

#endif // NETWORKRETRYPOLICY_H
