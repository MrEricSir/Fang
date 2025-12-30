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
class MockNetworkReply : public QNetworkReply
{
    Q_OBJECT

public:
    MockNetworkReply(const QByteArray& data, const QUrl& url, QObject* parent = nullptr, bool isError = false, QNetworkReply::NetworkError errorCode = QNetworkReply::ContentNotFoundError);

    void abort() override {}
    qint64 bytesAvailable() const override;
    bool isSequential() const override { return true; }

protected:
    qint64 readData(char* data, qint64 maxSize) override;

private:
    QBuffer buffer;
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

protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest& request,
                                 QIODevice* outgoingData = nullptr) override;

private:
    QMap<QString, QByteArray> responses;
    QNetworkReply::NetworkError nextError;
    int failuresRemaining;
    bool shouldFail;
};

#endif // MOCKNETWORKACCESSMANAGER_H
