#include <QtTest>

#include "../../src/utilities/NetworkUtilities.h"


class TestURLFixup : public QObject
{
    Q_OBJECT

public:
    TestURLFixup();

private slots:
    void testFixup();
    void testFixup_data();
};



TestURLFixup::TestURLFixup() {}

void TestURLFixup::testFixup()
{
    QFETCH(QString, url);
    QFETCH(QUrl, baseURL);
    QFETCH(QString, expectedResult);

    QString result = NetworkUtilities::urlFixup(url, baseURL);

    QCOMPARE(result, expectedResult);
}

void TestURLFixup::testFixup_data()
{
    QTest::addColumn<QString>("url");
    QTest::addColumn<QUrl>("baseURL");
    QTest::addColumn<QString>("expectedResult");

    // Valid URLs that should not require any fixups.
    QTest::newRow("valid 1")
        << "http://www.mrericsir.com/"
        << QUrl()
        << "http://www.mrericsir.com/";
    QTest::newRow("valid 2")
        << "http://www.mrericsir.com/"
        << QUrl("http://www.someotherbaseurl.com/")
        << "http://www.mrericsir.com/";
    QTest::newRow("valid 3")
        << "http://www.mrericsir.com/some/path"
        << QUrl("http://www.someotherbaseurl.com/")
        << "http://www.mrericsir.com/some/path";

    // Relative paths.
    QTest::newRow("relative 1")
        << "path"
        << QUrl("http://www.mrericsir.com/")
        << "http://www.mrericsir.com/path";
    QTest::newRow("relative 2")
        << "really/really/very/long/path"
        << QUrl("http://www.mrericsir.com")
        << "http://www.mrericsir.com/really/really/very/long/path";

    // Absolute paths.
    QTest::newRow("absolute 1")
        << "/"
        << QUrl("http://www.mrericsir.com/replace-me")
        << "http://www.mrericsir.com/";
    QTest::newRow("absolute 2")
        << "/new/path"
        << QUrl("http://www.mrericsir.com/replace-me")
        << "http://www.mrericsir.com/new/path";

    // Fishny and missing schemes.
    QTest::newRow("scheme 1")
        << "www.mrericsir.com"
        << QUrl()
        << "http://www.mrericsir.com";
    QTest::newRow("scheme 2")
        << "//www.mrericsir.com"
        << QUrl()
        << "http://www.mrericsir.com";
    QTest::newRow("scheme 3")
        << "/www.mrericsir.com"
        << QUrl()
        << "http://www.mrericsir.com";
    QTest::newRow("scheme 4")
        << "://www.mrericsir.com"
        << QUrl()
        << "http://www.mrericsir.com";
}

QTEST_APPLESS_MAIN(TestURLFixup)

#include "tst_urlfixup.moc"

