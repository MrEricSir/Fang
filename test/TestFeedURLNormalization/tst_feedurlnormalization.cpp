#include <QtTest>

// Standalone copy of the URL normalization logic from FangApp::openFeedUrl().
// This lets us test the logic without pulling in FangApp dependencies.
static QString normalizeFeedUrl(const QString& url)
{
    QString normalized = url;
    if (normalized.startsWith("feed://")) {
        normalized = "http://" + normalized.mid(7);
    } else if (normalized.startsWith("feeds://")) {
        normalized = "https://" + normalized.mid(8);
    } else if (normalized.startsWith("feed:")) {
        normalized = normalized.mid(5);
    }
    return normalized;
}

class TestFeedURLNormalization : public QObject
{
    Q_OBJECT

private slots:
    void testNormalize();
    void testNormalize_data();
};

void TestFeedURLNormalization::testNormalize()
{
    QFETCH(QString, input);
    QFETCH(QString, expected);

    QString result = normalizeFeedUrl(input);
    QCOMPARE(result, expected);
}

void TestFeedURLNormalization::testNormalize_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("expected");

    // feed:// scheme -> http://
    QTest::newRow("feed:// basic")
        << "feed://example.com/rss"
        << "http://example.com/rss";
    QTest::newRow("feed:// with path")
        << "feed://rss.nytimes.com/services/xml/rss/nyt/HomePage.xml"
        << "http://rss.nytimes.com/services/xml/rss/nyt/HomePage.xml";
    QTest::newRow("feed:// bare host")
        << "feed://example.com"
        << "http://example.com";

    // feeds:// scheme -> https://
    QTest::newRow("feeds:// basic")
        << "feeds://example.com/rss"
        << "https://example.com/rss";
    QTest::newRow("feeds:// with path")
        << "feeds://example.com/feeds/main.xml"
        << "https://example.com/feeds/main.xml";

    // feed: prefix with embedded http/https URL
    QTest::newRow("feed:http://")
        << "feed:http://example.com/rss"
        << "http://example.com/rss";
    QTest::newRow("feed:https://")
        << "feed:https://example.com/rss"
        << "https://example.com/rss";

    // Already-normal URLs should pass through unchanged
    QTest::newRow("http:// passthrough")
        << "http://example.com/rss"
        << "http://example.com/rss";
    QTest::newRow("https:// passthrough")
        << "https://example.com/rss"
        << "https://example.com/rss";

    // Edge cases
    QTest::newRow("feed:// with port")
        << "feed://example.com:8080/rss"
        << "http://example.com:8080/rss";
    QTest::newRow("feeds:// with query string")
        << "feeds://example.com/rss?format=xml"
        << "https://example.com/rss?format=xml";
    QTest::newRow("feed:// with fragment")
        << "feed://example.com/rss#section"
        << "http://example.com/rss#section";
    QTest::newRow("feed:// with auth")
        << "feed://user:pass@example.com/rss"
        << "http://user:pass@example.com/rss";
}

QTEST_APPLESS_MAIN(TestFeedURLNormalization)

#include "tst_feedurlnormalization.moc"
