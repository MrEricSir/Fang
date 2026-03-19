#ifndef MOCKGOOGLENEWSSITEMAPSYNTHESIZER_H
#define MOCKGOOGLENEWSSITEMAPSYNTHESIZER_H

#include <QTimer>
#include "../src/utilities/GoogleNewsSitemapSynthesizer.h"

/**
 * @brief Mock GoogleNewsSitemapSynthesizer for testing without network requests.
 * Follows the same pattern as MockWebPageGrabber and MockBatchNewsParser.
 */
class MockGoogleNewsSitemapSynthesizer : public GoogleNewsSitemapSynthesizer
{
    Q_OBJECT

public:
    explicit MockGoogleNewsSitemapSynthesizer(QObject* parent = nullptr)
        : GoogleNewsSitemapSynthesizer(parent)
    {
    }

    /**
     * @brief Configure the mock to return a successful result.
     * @param feed The RawFeed to return (ownership is NOT transferred).
     */
    void setResult(RawFeed* feed)
    {
        setResultState(feed, false, QString());
    }

    /**
     * @brief Configure the mock to return an error.
     * @param error The error message.
     */
    void setError(const QString& error)
    {
        setResultState(nullptr, true, error);
    }

    void synthesize(const QUrl& siteUrl, const QString& siteTitle) override
    {
        Q_UNUSED(siteUrl);
        Q_UNUSED(siteTitle);
        QTimer::singleShot(0, this, &GoogleNewsSitemapSynthesizer::done);
    }

    void synthesize(const QUrl& sitemapUrl, const QString& feedTitle,
                    const QDateTime& since) override
    {
        Q_UNUSED(sitemapUrl);
        Q_UNUSED(feedTitle);
        Q_UNUSED(since);
        QTimer::singleShot(0, this, &GoogleNewsSitemapSynthesizer::done);
    }
};

#endif // MOCKGOOGLENEWSSITEMAPSYNTHESIZER_H
