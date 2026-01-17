#ifndef MOCKWEBPAGEGRABBER_H
#define MOCKWEBPAGEGRABBER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QTimer>
#include "../src/utilities/WebPageGrabber.h"

/**
 * @brief Mock WebPageGrabber for testing - allows pre-configuration of results
 * Note: Inherits from WebPageGrabber to satisfy type requirements, but overrides load()
 */
class MockWebPageGrabber : public WebPageGrabber
{
    Q_OBJECT

public:
    explicit MockWebPageGrabber(QObject *parent = nullptr)
        : WebPageGrabber(false, 0, parent), // Pass 0 timeout to minimize delays
          mockDocument(nullptr),
          shouldError(false),
          loadCalled(false)
    {
    }

    /**
     * @brief Set the document that will be returned on next load()
     * @param document The HTML document to return (nullptr for error)
     */
    void setMockDocument(QString* document)
    {
        mockDocument = document;
        shouldError = (document == nullptr);
    }

    /**
     * @brief Set whether to simulate an error (emit nullptr)
     */
    void setError(bool error)
    {
        shouldError = error;
        if (error) {
            mockDocument = nullptr;
        }
    }

    /**
     * @brief Check if load() was called
     */
    bool wasLoadCalled() const { return loadCalled; }

public slots:
    /**
     * @brief Emit mock result asynchronously, bypassing parent implementation
     */
    void load(const QUrl &url)
    {
        Q_UNUSED(url);
        loadCalled = true;

        // Emit the ready signal asynchronously to mimic real behavior
        // Use QTimer to ensure the signal is emitted in the next event loop iteration
        QTimer::singleShot(10, this, [this]() {
            if (shouldError) {
                emit ready(this, nullptr);
            } else {
                emit ready(this, mockDocument);
            }
        });
    }

private:
    QString* mockDocument;
    bool shouldError;
    bool loadCalled;
};

#endif // MOCKWEBPAGEGRABBER_H
