#include <QTest>
#include <QFile>
#include <QXmlStreamReader>
#include <QTemporaryDir>
#include "../../src/utilities/OPMLExport.h"
#include "../../src/models/ListModel.h"
#include "../../src/models/FeedItem.h"

/**
 * OPML export tests
 */
class TestOPMLExport : public QObject
{
    Q_OBJECT

public:
    TestOPMLExport();

private slots:
    void initTestCase();
    void cleanup();

    // The most obvious tests
    void testExportEmptyList();
    void testExportSingleFeed();
    void testExportMultipleFeeds();
    void testExportWithSpecialCharacters();
    void testExportWithoutSiteURL();

    // Test XML structure
    void testValidXMLStructure();
    void testOPMLVersion();
    void testDateFormat();

private:
    QTemporaryDir* tempDir;
    QString getTempFilePath(const QString& name);
    ListModel* createTestModel();
    void verifyOPMLStructure(const QString& filePath);
    QXmlStreamReader::TokenType skipToElement(QXmlStreamReader& xml, const QString& elementName);
};

TestOPMLExport::TestOPMLExport()
    : tempDir(nullptr)
{
}

void TestOPMLExport::initTestCase()
{
    tempDir = new QTemporaryDir();
    QVERIFY(tempDir->isValid());
}

void TestOPMLExport::cleanup()
{
    // TODO: Cleanup: Do we need this?
}

QString TestOPMLExport::getTempFilePath(const QString& name)
{
    return tempDir->filePath(name);
}

ListModel* TestOPMLExport::createTestModel()
{
    // Create a feed item.
    FeedItem* prototype = new FeedItem();
    return new ListModel(prototype, this);
}

QXmlStreamReader::TokenType TestOPMLExport::skipToElement(QXmlStreamReader& xml, const QString& elementName)
{
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == elementName) {
            return xml.tokenType();
        }
    }
    return xml.tokenType();
}

void TestOPMLExport::verifyOPMLStructure(const QString& filePath)
{
    QFile file(filePath);
    QVERIFY2(file.open(QIODevice::ReadOnly), "Could not open exported file");

    QXmlStreamReader xml(&file);

    // Verify XML declaration
    QVERIFY(xml.readNext() == QXmlStreamReader::StartDocument);

    // Verify <opml> element
    QVERIFY(skipToElement(xml, "opml") == QXmlStreamReader::StartElement);
    QCOMPARE(xml.attributes().value("version").toString(), QString("1.1"));

    // Verify <head> element
    QVERIFY(skipToElement(xml, "head") == QXmlStreamReader::StartElement);

    // Verify <title> in head
    QVERIFY(skipToElement(xml, "title") == QXmlStreamReader::StartElement);
    QCOMPARE(xml.readElementText(), QString("Fang OPML export"));

    // Verify <dateModified> exists and has correct format
    QVERIFY(skipToElement(xml, "dateModified") == QXmlStreamReader::StartElement);
    QString dateStr = xml.readElementText();
    QVERIFY(!dateStr.isEmpty());
    QVERIFY(dateStr.endsWith(" GMT"));

    file.close();
}

void TestOPMLExport::testExportEmptyList()
{
    ListModel* model = createTestModel();
    QString filePath = getTempFilePath("empty.opml");

    bool result = OPMLExport::save(filePath, model);
    QVERIFY(result);

    QFile file(filePath);
    QVERIFY(file.exists());
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);

    // Find body element
    skipToElement(xml, "body");

    // Read through body - should have no outline elements
    int outlineCount = 0;
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == "outline") {
            outlineCount++;
        }
        if (xml.isEndElement() && xml.name() == "body") {
            break;
        }
    }

    QCOMPARE(outlineCount, 0);

    file.close();
    delete model;
}

void TestOPMLExport::testExportSingleFeed()
{
    ListModel* model = createTestModel();

    // Add placeholder at index 0 (reserved for "All News" special feed)
    FeedItem* placeholder = new FeedItem(
        FEED_ID_ALLNEWS, -1, "All News", "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(), -1, true, model
    );
    model->appendRow(placeholder);

    // Add a real feed at index 1
    FeedItem* feed = new FeedItem(
        1,                                          // id
        0,                                          // ordinal
        "Test Feed",                                // title
        "Test Subtitle",                            // subtitle
        QDateTime::currentDateTime(),               // lastUpdated
        60,                                         // minutesToUpdate
        QUrl("http://example.com/feed.xml"),       // url
        QUrl("http://example.com"),                // siteURL
        "http://example.com/feed.xml",             // userURL
        QUrl("http://example.com/icon.png"),       // imageURL
        QDateTime::currentDateTime(),               // lastIconUpdate
        -1,                                         // parentFolder
        true,                                       // folderOpen
        model
    );

    model->appendRow(feed);

    QString filePath = getTempFilePath("single.opml");
    bool result = OPMLExport::save(filePath, model);
    QVERIFY(result);

    QFile file(filePath);
    QVERIFY(file.exists());
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);

    // Find body element
    skipToElement(xml, "body");

    // Find first outline element
    QVERIFY(skipToElement(xml, "outline") == QXmlStreamReader::StartElement);

    // Verify attributes
    QCOMPARE(xml.attributes().value("text").toString(), QString("Test Feed"));
    QCOMPARE(xml.attributes().value("title").toString(), QString("Test Feed"));
    QCOMPARE(xml.attributes().value("type").toString(), QString("rss"));
    QCOMPARE(xml.attributes().value("xmlUrl").toString(), QString("http://example.com/feed.xml"));
    QCOMPARE(xml.attributes().value("htmlUrl").toString(), QString("http://example.com"));

    file.close();
    delete model;
}

void TestOPMLExport::testExportMultipleFeeds()
{
    ListModel* model = createTestModel();

    // Add placeholder at index 0
    FeedItem* placeholder = new FeedItem(
        FEED_ID_ALLNEWS, -1, "All News", "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(), -1, true, model
    );
    model->appendRow(placeholder);

    // Add multiple real feeds
    for (int i = 1; i <= 3; i++) {
        FeedItem* feed = new FeedItem(
            i,
            i - 1,
            QString("Feed %1").arg(i),
            QString("Subtitle %1").arg(i),
            QDateTime::currentDateTime(),
            60,
            QUrl(QString("http://example.com/feed%1.xml").arg(i)),
            QUrl(QString("http://example.com/site%1").arg(i)),
            QString("http://example.com/feed%1.xml").arg(i),
            QUrl(),
            QDateTime::currentDateTime(),
            -1,
            true,
            model
        );
        model->appendRow(feed);
    }

    QString filePath = getTempFilePath("multiple.opml");
    bool result = OPMLExport::save(filePath, model);
    QVERIFY(result);

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);

    // Find body and count outline elements
    skipToElement(xml, "body");

    int outlineCount = 0;
    QStringList titles;

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == "outline") {
            outlineCount++;
            titles.append(xml.attributes().value("text").toString());
        }
        if (xml.isEndElement() && xml.name() == "body") {
            break;
        }
    }

    QCOMPARE(outlineCount, 3);
    QCOMPARE(titles.at(0), QString("Feed 1"));
    QCOMPARE(titles.at(1), QString("Feed 2"));
    QCOMPARE(titles.at(2), QString("Feed 3"));

    file.close();
    delete model;
}

void TestOPMLExport::testExportWithSpecialCharacters()
{
    ListModel* model = createTestModel();

    // Add placeholder at index 0
    FeedItem* placeholder = new FeedItem(
        FEED_ID_ALLNEWS, -1, "All News", "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(), -1, true, model
    );
    model->appendRow(placeholder);

    // Add feed with special XML characters
    FeedItem* feed = new FeedItem(
        1,
        0,
        "Feed with <special> & \"characters\"",
        "Subtitle",
        QDateTime::currentDateTime(),
        60,
        QUrl("http://example.com/feed.xml?foo=bar&baz=qux"),
        QUrl("http://example.com"),
        "http://example.com/feed.xml",
        QUrl(),
        QDateTime::currentDateTime(),
        -1,
        true,
        model
    );

    model->appendRow(feed);

    QString filePath = getTempFilePath("special.opml");
    bool result = OPMLExport::save(filePath, model);
    QVERIFY(result);

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);

    // Find the outline element
    skipToElement(xml, "outline");

    // Verify that special characters are properly escaped
    QString title = xml.attributes().value("text").toString();
    QCOMPARE(title, QString("Feed with <special> & \"characters\""));

    QString url = xml.attributes().value("xmlUrl").toString();
    QVERIFY(url.contains("&"));
    QVERIFY(url.contains("="));

    file.close();
    delete model;
}

void TestOPMLExport::testExportWithoutSiteURL()
{
    ListModel* model = createTestModel();

    // Add placeholder at index 0
    FeedItem* placeholder = new FeedItem(
        FEED_ID_ALLNEWS, -1, "All News", "", QDateTime::currentDateTime(), 60,
        QUrl(), QUrl(), "", QUrl(), QDateTime::currentDateTime(), -1, true, model
    );
    model->appendRow(placeholder);

    // Add feed without siteURL
    FeedItem* feed = new FeedItem(
        1,
        0,
        "Feed Without Site URL",
        "Subtitle",
        QDateTime::currentDateTime(),
        60,
        QUrl("http://example.com/feed.xml"),
        QUrl(),  // Empty siteURL
        "http://example.com/feed.xml",
        QUrl(),
        QDateTime::currentDateTime(),
        -1,
        true,
        model
    );

    model->appendRow(feed);

    QString filePath = getTempFilePath("nosite.opml");
    bool result = OPMLExport::save(filePath, model);
    QVERIFY(result);

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);

    // Find the outline element
    skipToElement(xml, "outline");

    // Verify that htmlUrl is not present when siteURL is invalid
    QVERIFY(!xml.attributes().hasAttribute("htmlUrl"));

    // But other attributes should still be there
    QVERIFY(xml.attributes().hasAttribute("text"));
    QVERIFY(xml.attributes().hasAttribute("title"));
    QVERIFY(xml.attributes().hasAttribute("type"));
    QVERIFY(xml.attributes().hasAttribute("xmlUrl"));

    file.close();
    delete model;
}

void TestOPMLExport::testValidXMLStructure()
{
    ListModel* model = createTestModel();

    FeedItem* feed = new FeedItem(
        1, 0, "Test", "", QDateTime::currentDateTime(), 60,
        QUrl("http://example.com/feed.xml"), QUrl("http://example.com"),
        "http://example.com/feed.xml", QUrl(), QDateTime::currentDateTime(),
        -1, true, model
    );
    model->appendRow(feed);

    QString filePath = getTempFilePath("structure.opml");
    bool result = OPMLExport::save(filePath, model);
    QVERIFY(result);

    // Use verifyOPMLStructure helper
    verifyOPMLStructure(filePath);

    delete model;
}

void TestOPMLExport::testOPMLVersion()
{
    ListModel* model = createTestModel();

    QString filePath = getTempFilePath("version.opml");
    OPMLExport::save(filePath, model);

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);
    skipToElement(xml, "opml");

    QCOMPARE(xml.attributes().value("version").toString(), QString("1.1"));

    file.close();
    delete model;
}

void TestOPMLExport::testDateFormat()
{
    ListModel* model = createTestModel();

    QString filePath = getTempFilePath("date.opml");
    OPMLExport::save(filePath, model);

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly));

    QXmlStreamReader xml(&file);
    skipToElement(xml, "dateModified");

    QString dateStr = xml.readElementText();

    // Verify format: "ddd, dd MMM yyyy hh:mm:ss GMT"
    // Example: "Tue, 18 Mar 2014 04:09:51 GMT"
    QVERIFY(dateStr.endsWith(" GMT"));

    // Remove " GMT" and try to parse
    QString dateWithoutGMT = dateStr.left(dateStr.length() - 4);
    QDateTime parsed = QDateTime::fromString(dateWithoutGMT, "ddd, dd MMM yyyy hh:mm:ss");

    QVERIFY2(parsed.isValid(), qPrintable(QString("Invalid date format: %1").arg(dateStr)));

    file.close();
    delete model;
}

QTEST_MAIN(TestOPMLExport)

#include "tst_opmlexport.moc"
