#ifndef MOCKNETWORKACCESSMANAGER_H
#define MOCKNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QMap>
#include <QByteArray>
#include <QBuffer>
#include <QTimer>

/**
 * @brief Mock QNetworkReply that returns pre-recorded data
 */
/**
 * @brief Mock QNetworkReply that returns pre-recorded data
 */
/**
 * @brief Mock QNetworkReply that returns pre-recorded data
 */
class MockNetworkReply : public QNetworkReply
{
    Q_OBJECT

public:
    // Full constructor taking QNetworkRequest (preserves request.url() for reply->request().url())
    MockNetworkReply(const QByteArray& data, const QNetworkRequest& request, QObject* parent = nullptr,
                     bool isError = false,
                     QNetworkReply::NetworkError errorCode = QNetworkReply::ContentNotFoundError,
                     int delayMs = 0,
                     const QUrl& redirectUrl = QUrl());

    // Backwards-compatible constructor taking QUrl (creates minimal QNetworkRequest internally)
    MockNetworkReply(const QByteArray& data, const QUrl& url, QObject* parent = nullptr,
                     bool isError = false,
                     QNetworkReply::NetworkError errorCode = QNetworkReply::ContentNotFoundError,
                     int delayMs = 0,
                     const QUrl& redirectUrl = QUrl());

    void abort() override;
    qint64 bytesAvailable() const override;
    bool isSequential() const override { return true; }

protected:
    qint64 readData(char* data, qint64 maxSize) override;

private slots:
    void emitFinished();
    void emitProgress();

private:
    QBuffer buffer;
    bool aborted;
};

/**
 * @brief Mock QNetworkAccessManager that returns pre-recorded responses
 *
 * Usage:
 *   MockNetworkAccessManager mock;
 *   mock.addResponse(QUrl("http://example.com"), "<html>Mock content</html>");
 *
 *   // Use in tests:
 *   FaviconGrabber grabber(nullptr, &mock);
 */
class MockNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit MockNetworkAccessManager(QObject* parent = nullptr);

    /**
     * @brief Add a mock response for a given URL
     * @param url The URL to mock
     * @param response The response data to return
     */
    void addResponse(const QUrl& url, const QByteArray& response);

    /**
     * @brief Add a mock response from a file
     * @param url The URL to mock
     * @param filePath Path to file containing the response
     */
    void addResponseFromFile(const QUrl& url, const QString& filePath);

    /**
     * @brief Clear all mock responses
     */
    void clear();

    /**
     * @brief Set the *next* request to fail with specified error.
     * @param errorCode The error that will be returned
     */
    void setNextError(QNetworkReply::NetworkError errorCode);

    /**
     * @brief Set the number of *consecutive* that will fail.
     * @param count Number of failed requests
     * @param errorCode The error code to return
     */
    void setFailureCount(int count, QNetworkReply::NetworkError errorCode = QNetworkReply::TimeoutError);

    /**
     * @brief Add a redirect from one URL to another
     * @param fromUrl The URL that will trigger the redirect
     * @param toUrl The URL to redirect to
     */
    void addRedirect(const QUrl& fromUrl, const QUrl& toUrl);

    /**
     * @brief Add a URL-specific error response
     * @param url The URL that will trigger the error
     * @param errorCode The error code to return
     */
    void addErrorResponse(const QUrl& url, QNetworkReply::NetworkError errorCode);

    /**
     * @brief Set a delay for all responses (simulates slow network)
     * @param delayMs Delay in milliseconds before response completes
     */
    void setResponseDelay(int delayMs);

    /**
     * @brief Set whether to emit progress signals
     * @param enabled If true, emits downloadProgress before finished
     */
    void setEmitProgress(bool enabled);

protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest& request,
                                 QIODevice* outgoingData = nullptr) override;

private:
    QMap<QString, QByteArray> responses;
    QMap<QString, QUrl> redirects;
    QMap<QString, QNetworkReply::NetworkError> urlErrors;
    QNetworkReply::NetworkError nextError;
    int failuresRemaining;
    bool shouldFail;
    int responseDelayMs;
    bool emitProgressEnabled;
};

#endif // MOCKNETWORKACCESSMANAGER_H
