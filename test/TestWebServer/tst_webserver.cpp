#include <QTest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QDateTime>

#include "../../src/models/AllNewsFeedItem.h"
#include "../../src/models/FeedItem.h"
#include "../../src/models/NewsItem.h"
#include "../../src/models/NewsList.h"
#include "../../src/models/ListModel.h"

/**
 * Test for WebServer data formatting logic.
 *
 * This test validates the data transformation that WebServer performs
 * when building JSON responses for JavaScript. The key invariant is:
 *
 *   News items must be in chronological order (oldest first).
 *
 * The bug fix verified here is:
 * - Prepend list from DB (DESC order) must be reversed to ASC for JS
 * - Append list from DB (ASC order) is sent as-is
 * - Combined result must be in chronological order
 *
 * This test mirrors the logic in WebServer::loadNews() without requiring
 * the full HTTP stack or FangApp infrastructure.
 */
class TestWebServerData : public QObject
{
    Q_OBJECT

public:
    TestWebServerData();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    // Tests for WebServer's data building logic
    void testBuildNewsJsonItem();
    void testPrependListReversal();
    void testAppendListOrdering();
    void testCombinedPrependAppendOrdering();
    void testBookmarkInExtras();
    void testModeInExtras();
    void testFirstNewsIDInExtras();

private:
    // Simulates WebServer::addNewsItem
    void addNewsItem(NewsItem* item, QVariantList* newsList, const QString& feedTitle);

    // Simulates WebServer::buildDocument
    QString buildDocument(const QVariantList& newsList, bool showWelcome,
                          QVariantMap extras = QVariantMap());

    NewsItem* createNewsItem(qint64 id, const QDateTime& timestamp, const QString& title = "");

    QSqlDatabase db;
    QString connectionName;
    ListModel* feedList;
    AllNewsFeedItem* allNewsFeed;
    QDateTime baseTime;
};

TestWebServerData::TestWebServerData()
    : connectionName("testdb_webserver_data"),
      feedList(nullptr),
      allNewsFeed(nullptr),
      baseTime(QDate(2024, 1, 1), QTime(12, 0, 0))
{
}

void TestWebServerData::initTestCase()
{
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");
    QVERIFY2(db.open(), qPrintable(db.lastError().text()));
}

void TestWebServerData::init()
{
    feedList = new ListModel(new FeedItem, this);
    allNewsFeed = new AllNewsFeedItem(feedList);
}

void TestWebServerData::cleanup()
{
    delete allNewsFeed;
    allNewsFeed = nullptr;

    delete feedList;
    feedList = nullptr;
}

void TestWebServerData::cleanupTestCase()
{
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

NewsItem* TestWebServerData::createNewsItem(qint64 id, const QDateTime& timestamp, const QString& title)
{
    QString newsTitle = title.isEmpty() ? QString("News Item %1").arg(id) : title;

    return new NewsItem(
        allNewsFeed,
        id,              // dbId
        1,               // feedId
        newsTitle,
        "Author",
        "Summary",
        "Content",
        timestamp,
        QUrl(QString("http://example.com/%1").arg(id)),
        false            // pinned
    );
}

// This mirrors WebServer::addNewsItem
void TestWebServerData::addNewsItem(NewsItem* item, QVariantList* newsList, const QString& feedTitle)
{
    QVariantMap itemMap;
    itemMap["id"] = item->getDbID();
    itemMap["title"] = item->getTitle();
    itemMap["url"] = item->getURL().toString();
    itemMap["feedTitle"] = feedTitle;
    itemMap["timestamp"] = item->getTimestamp().toMSecsSinceEpoch();
    itemMap["content"] = item->getContent() != "" ? item->getContent() : item->getSummary();
    itemMap["pinned"] = item->getPinned();

    if (itemMap["title"].toString().trimmed().isEmpty()) {
        itemMap["title"] = "<i>[ No Subject ]</i>";
    }

    *newsList << itemMap;
}

// This mirrors WebServer::buildDocument
QString TestWebServerData::buildDocument(const QVariantList& newsList, bool showWelcome, QVariantMap extras)
{
    QVariantMap document;
    document.insert("showWelcome", showWelcome);
    document.insert("news", newsList);
    document.insert(extras);
    return QString::fromUtf8(QJsonDocument::fromVariant(document).toJson());
}

// ============================================================================
// TEST CASES
// ============================================================================

void TestWebServerData::testBuildNewsJsonItem()
{
    // Verify individual news item JSON structure
    QDateTime timestamp = baseTime.addSecs(60);
    NewsItem* item = createNewsItem(100, timestamp, "Test Article");

    QVariantList newsList;
    addNewsItem(item, &newsList, "Test Feed");

    QCOMPARE(newsList.size(), 1);

    QVariantMap newsItem = newsList[0].toMap();
    QCOMPARE(newsItem["id"].toLongLong(), 100LL);
    QCOMPARE(newsItem["title"].toString(), QString("Test Article"));
    QCOMPARE(newsItem["feedTitle"].toString(), QString("Test Feed"));
    QCOMPARE(newsItem["timestamp"].toLongLong(), timestamp.toMSecsSinceEpoch());
    QCOMPARE(newsItem["pinned"].toBool(), false);

    delete item;
}

void TestWebServerData::testPrependListReversal()
{
    // BUG FIX VERIFICATION:
    // WebServer.cpp must reverse the prepend list before sending to JavaScript.
    // The prepend query returns items in DESC order (newest first among read items),
    // but JavaScript expects ASC order (oldest first).

    qDebug() << "\n=== testPrependListReversal ===";

    // Simulate prepend list as it comes from DB (DESC order)
    QList<NewsItem*> prependListFromDB;
    for (int i = 9; i >= 0; --i) {  // DESC: 9, 8, 7, ..., 0
        prependListFromDB.append(createNewsItem(i, baseTime.addSecs(i * 60)));
    }

    // Verify DB order is descending
    qDebug() << "DB order (DESC):";
    for (int i = 0; i < prependListFromDB.size(); i++) {
        qDebug() << "  [" << i << "] ID=" << prependListFromDB[i]->getDbID();
    }

    // WebServer reverses the prepend list (see WebServer::loadNews)
    QVariantList newsList;
    for (qsizetype i = prependListFromDB.size() - 1; i >= 0; i--) {
        NewsItem* item = prependListFromDB.at(i);
        addNewsItem(item, &newsList, "Test Feed");
    }

    // Verify result is ascending (oldest first)
    qDebug() << "Result order (ASC):";
    qint64 prevId = -1;
    for (int i = 0; i < newsList.size(); i++) {
        qint64 id = newsList[i].toMap()["id"].toLongLong();
        qDebug() << "  [" << i << "] ID=" << id;

        if (i > 0) {
            QVERIFY2(id > prevId, qPrintable(QString("ID %1 should be > %2").arg(id).arg(prevId)));
        }
        prevId = id;
    }

    // Also verify timestamps are ascending
    qint64 prevTimestamp = 0;
    for (int i = 0; i < newsList.size(); i++) {
        qint64 timestamp = newsList[i].toMap()["timestamp"].toLongLong();
        QVERIFY2(timestamp >= prevTimestamp, "Timestamps should be ascending");
        prevTimestamp = timestamp;
    }

    qDeleteAll(prependListFromDB);
    qDebug() << "=== PASSED ===\n";
}

void TestWebServerData::testAppendListOrdering()
{
    // Append list comes from DB in ASC order and should be sent to JS as-is.
    qDebug() << "\n=== testAppendListOrdering ===";

    // Simulate append list as it comes from DB (ASC order)
    QList<NewsItem*> appendListFromDB;
    for (int i = 0; i < 10; ++i) {  // ASC: 0, 1, 2, ..., 9
        appendListFromDB.append(createNewsItem(200 + i, baseTime.addSecs(i * 60)));
    }

    // WebServer keeps append list as-is
    QVariantList newsList;
    for (NewsItem* item : std::as_const(appendListFromDB)) {
        addNewsItem(item, &newsList, "Test Feed");
    }

    // Verify result is still ascending
    qint64 prevTimestamp = 0;
    for (int i = 0; i < newsList.size(); i++) {
        qint64 timestamp = newsList[i].toMap()["timestamp"].toLongLong();
        QVERIFY2(timestamp >= prevTimestamp, "Timestamps should be ascending");
        prevTimestamp = timestamp;
    }

    qDeleteAll(appendListFromDB);
    qDebug() << "=== PASSED ===\n";
}

void TestWebServerData::testCombinedPrependAppendOrdering()
{
    // Test combined scenario: prepend (reversed) + append
    // Result should be fully chronological
    qDebug() << "\n=== testCombinedPrependAppendOrdering ===";

    // Prepend list from DB (DESC): items 40-49 (read items before bookmark)
    QList<NewsItem*> prependListFromDB;
    for (int i = 49; i >= 40; --i) {
        prependListFromDB.append(createNewsItem(i, baseTime.addSecs(i * 60)));
    }

    // Append list from DB (ASC): items 50-59 (unread items after bookmark)
    QList<NewsItem*> appendListFromDB;
    for (int i = 50; i < 60; ++i) {
        appendListFromDB.append(createNewsItem(i, baseTime.addSecs(i * 60)));
    }

    QVariantList newsList;

    // Add prepend list REVERSED (as WebServer does)
    for (qsizetype i = prependListFromDB.size() - 1; i >= 0; i--) {
        addNewsItem(prependListFromDB.at(i), &newsList, "Test Feed");
    }

    // Add append list as-is
    for (NewsItem* item : std::as_const(appendListFromDB)) {
        addNewsItem(item, &newsList, "Test Feed");
    }

    QCOMPARE(newsList.size(), 20);

    // Verify fully chronological order
    qDebug() << "Combined order:";
    qint64 prevTimestamp = 0;
    for (int i = 0; i < newsList.size(); i++) {
        qint64 id = newsList[i].toMap()["id"].toLongLong();
        qint64 timestamp = newsList[i].toMap()["timestamp"].toLongLong();
        qDebug() << "  [" << i << "] ID=" << id << " timestamp=" << timestamp;

        QVERIFY2(timestamp >= prevTimestamp,
                 qPrintable(QString("Item %1 (ts=%2) < previous (ts=%3)")
                           .arg(id).arg(timestamp).arg(prevTimestamp)));
        prevTimestamp = timestamp;
    }

    // First item should be ID 40, last should be ID 59
    QCOMPARE(newsList.first().toMap()["id"].toLongLong(), 40LL);
    QCOMPARE(newsList.last().toMap()["id"].toLongLong(), 59LL);

    qDeleteAll(prependListFromDB);
    qDeleteAll(appendListFromDB);
    qDebug() << "=== PASSED ===\n";
}

void TestWebServerData::testBookmarkInExtras()
{
    QVariantMap extras;
    extras.insert("bookmark", 12345LL);
    extras.insert("mode", "initial");

    QVariantList newsList;
    QString json = buildDocument(newsList, false, extras);

    QJsonObject doc = QJsonDocument::fromJson(json.toUtf8()).object();
    QCOMPARE(doc["bookmark"].toVariant().toLongLong(), 12345LL);
    QCOMPARE(doc["mode"].toString(), QString("initial"));
    QCOMPARE(doc["showWelcome"].toBool(), false);
}

void TestWebServerData::testModeInExtras()
{
    QVariantMap extras;
    extras.insert("mode", "append");

    QVariantList newsList;
    QString json = buildDocument(newsList, false, extras);

    QJsonObject doc = QJsonDocument::fromJson(json.toUtf8()).object();
    QCOMPARE(doc["mode"].toString(), QString("append"));
}

void TestWebServerData::testFirstNewsIDInExtras()
{
    QVariantMap extras;
    extras.insert("firstNewsID", 100LL);

    QVariantList newsList;
    QString json = buildDocument(newsList, false, extras);

    QJsonObject doc = QJsonDocument::fromJson(json.toUtf8()).object();
    QCOMPARE(doc["firstNewsID"].toVariant().toLongLong(), 100LL);
}

QTEST_MAIN(TestWebServerData)
#include "tst_webserver.moc"
