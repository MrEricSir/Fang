#include "NetworkRetryPolicy.h"
#include <algorithm>
#include <cmath>

NetworkRetryPolicy::NetworkRetryPolicy()
    : maxNumRetries(0)
    , defaultDelayMs(1000)
    , maxDelayMs(60000)
    , strategy(Exponential)
    , shouldRetryOnTimeout(true)
    , shouldRetryOnDnsFailure(true)
    , shouldRetryOnConnectionRefused(true)
    , shouldRetryOnServerError(true)
{
}

NetworkRetryPolicy::NetworkRetryPolicy(int maxRetries, int baseDelay, BackoffStrategy strategy, int maxDelay)
    : maxNumRetries(maxRetries)
    , defaultDelayMs(baseDelay)
    , maxDelayMs(maxDelay)
    , strategy(strategy)
    , shouldRetryOnTimeout(true)
    , shouldRetryOnDnsFailure(true)
    , shouldRetryOnConnectionRefused(true)
    , shouldRetryOnServerError(true)
{
}

NetworkRetryPolicy NetworkRetryPolicy::forFeedUpdate()
{
    // Medium importance: 3 retries with exponential backoff: 2s, 4s, 8s
    return NetworkRetryPolicy(3, 2000, Exponential, 30000);
}

NetworkRetryPolicy NetworkRetryPolicy::forFavicon()
{
    // Non-critical: 2 retries with linear backoff: 1s, 2s
    return NetworkRetryPolicy(2, 1000, Linear, 5000);
}

NetworkRetryPolicy NetworkRetryPolicy::forCritical()
{
    // Give it our best shot: 5 retries with fibonacci backoff: 1s, 2s, 3s, 5s, 8s
    return NetworkRetryPolicy(5, 1000, Fibonacci, 60000);
}

NetworkRetryPolicy NetworkRetryPolicy::noRetry()
{
    return NetworkRetryPolicy(0, 0, Fixed, 0);
}

bool NetworkRetryPolicy::isRetryable(QNetworkReply::NetworkError error) const
{
    switch (error) {
    // Network errors
    case QNetworkReply::ConnectionRefusedError:
        return shouldRetryOnConnectionRefused;

    case QNetworkReply::RemoteHostClosedError:
    case QNetworkReply::HostNotFoundError:
        return shouldRetryOnDnsFailure;

    case QNetworkReply::TimeoutError:
    case QNetworkReply::OperationCanceledError:
        return shouldRetryOnTimeout;

    case QNetworkReply::TemporaryNetworkFailureError:
    case QNetworkReply::NetworkSessionFailedError:
    case QNetworkReply::BackgroundRequestNotAllowedError:
        return true;

    // Don't retry at all for SSL errors
    case QNetworkReply::SslHandshakeFailedError:
    case QNetworkReply::UnknownServerError:
        return false;

    // Protocol errors are also not retryable (is that a word?)
    case QNetworkReply::ProtocolUnknownError:
    case QNetworkReply::ProtocolInvalidOperationError:
    case QNetworkReply::ProtocolFailure:
        return false;

    // HTTP-specific errors
    case QNetworkReply::InternalServerError:
    case QNetworkReply::ServiceUnavailableError:
        return shouldRetryOnServerError;

    // Oddball errors that we should try again ASAP
    case QNetworkReply::UnknownNetworkError:
    case QNetworkReply::UnknownProxyError:
    case QNetworkReply::UnknownContentError:
        return true;

    // No point in retrying these
    case QNetworkReply::ContentAccessDenied:
    case QNetworkReply::ContentNotFoundError:
    case QNetworkReply::AuthenticationRequiredError:
    case QNetworkReply::ContentOperationNotPermittedError:
        return false;

    case QNetworkReply::NoError:
        return false;

    default:
        // Retry by default
        return true;
    }
}

int NetworkRetryPolicy::calculateDelay(int attemptNumber) const
{
    if (attemptNumber >= maxNumRetries) {
        return 0;
    }

    int delay;

    switch (strategy) {
    case Linear:
        delay = defaultDelayMs * (attemptNumber + 1);
        break;

    case Exponential:
        delay = static_cast<int>(defaultDelayMs * std::pow(2, attemptNumber));
        break;

    case Fibonacci: {
        // Math alert! Find the next Fibonacci number for this attempt.
        int fib1 = 1, fib2 = 1;
        for (int i = 0; i < attemptNumber; ++i) {
            int temp = fib1 + fib2;
            fib1 = fib2;
            fib2 = temp;
        }
        delay = defaultDelayMs * fib2;
        break;
    }

    case Fixed:
    default:
        delay = defaultDelayMs;
        break;
    }

    // Max delay.
    return std::min(delay, maxDelayMs);
}
