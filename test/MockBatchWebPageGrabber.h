#ifndef MOCKBATCHWEBPAGEGRABBER_H
#define MOCKBATCHWEBPAGEGRABBER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QMap>
#include <QList>
#include <QTimer>
#include "../src/utilities/BatchWebPageGrabber.h"

/**
 * @brief Mock BatchWebPageGrabber for testing - allows pre-configuration of results
 */
class MockBatchWebPageGrabber : public BatchWebPageGrabber
{
    Q_OBJECT

public:
    explicit MockBatchWebPageGrabber(QObject *parent = nullptr)
        : BatchWebPageGrabber(parent),
          shouldError(false),
          loadCalled(false)
    {
    }

    /**
     * @brief Add a mock response for a specific URL
     * @param url The URL to match
     * @param content The HTML content to return (empty string for error)
     */
    void addResponse(const QUrl& url, const QString& content)
    {
        mockResponses[url] = content;
    }

    /**
     * @brief Set whether to simulate an error (return empty results)
     */
    void setError(bool error)
    {
        shouldError = error;
    }

    /**
     * @brief Check if load() was called
     */
    bool wasLoadCalled() const { return loadCalled; }

    /**
     * @brief Get the URLs that were requested
     */
    QList<QUrl> getRequestedURLs() const { return requestedURLs; }

public slots:
    /**
     * @brief Override load() to emit mock results asynchronously
     */
    void load(const QList<QUrl> &urls) override
    {
        loadCalled = true;
        requestedURLs = urls;

        // Build results from mock responses
        QMap<QUrl, QString> mockResults;
        if (!shouldError) {
            // For each requested URL, try to find a matching response
            for (const QUrl& requestedUrl : urls) {
                // Try exact match first
                bool found = false;
                for (auto it = mockResponses.constBegin(); it != mockResponses.constEnd(); ++it) {
                    const QUrl& mockUrl = it.key();
                    // Compare URLs ignoring trailing slashes
                    QString reqStr = requestedUrl.toString();
                    QString mockStr = mockUrl.toString();
                    if (reqStr.endsWith('/')) reqStr.chop(1);
                    if (mockStr.endsWith('/')) mockStr.chop(1);

                    if (reqStr == mockStr) {
                        mockResults[requestedUrl] = it.value();
                        found = true;
                        break;
                    }
                }

                // If we have mock responses but none matched, return the first one anyway
                // (for simple test scenarios)
                if (!found && !mockResponses.isEmpty()) {
                    mockResults[requestedUrl] = mockResponses.first();
                }
            }
        }

        // Store results
        cachedResults = mockResults;

        // Emit the ready signal asynchronously to mimic real behavior
        QTimer::singleShot(10, this, [this]() {
            emit ready();
        });
    }

    /**
     * @brief Override getResults() to return mock data
     */
    QMap<QUrl, QString> getResults() override
    {
        return cachedResults;
    }

private:
    QMap<QUrl, QString> mockResponses;
    QMap<QUrl, QString> cachedResults;
    QList<QUrl> requestedURLs;
    bool shouldError;
    bool loadCalled;
};

#endif // MOCKBATCHWEBPAGEGRABBER_H
