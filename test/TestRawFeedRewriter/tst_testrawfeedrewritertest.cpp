#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QSignalSpy>

#include "../../src/utilities/RawFeedRewriter.h"

class TestRawFeedRewriterTest : public QObject
{
    Q_OBJECT
    
public:
    TestRawFeedRewriterTest();
    
private Q_SLOTS:
    void testCase1();
    void testCase1_data();
};

TestRawFeedRewriterTest::TestRawFeedRewriterTest()
{
}

void TestRawFeedRewriterTest::testCase1()
{
    QFETCH(QString, input);
    QFETCH(QString, output);
    QFETCH(bool,    images);
    
    // Setup our "fake" raw news list.
    RawNews news;
    news.description = input;
    QList<RawNews*> newsList;
    newsList.append(&news);
    
    // Send it to the rewriter.
    RawFeedRewriter rewriter;
    QSignalSpy spy(&rewriter, SIGNAL(finished()));
    rewriter.rewrite(&newsList);
    
    if (images) {
        // There's images, so we need to wait for the download.
        QVERIFY(spy.wait());  // default: up to 5 seconds
    }
    
    QCOMPARE(spy.count(), 1);
    
    // Check to see what we got!
    QCOMPARE(news.description, output);
}

void TestRawFeedRewriterTest::testCase1_data()
{
    QTest::addColumn<QString>("input");  // HTML input
    QTest::addColumn<QString>("output"); // Expected HTML output
    QTest::addColumn<bool>("images");    // Set to true if we have to wait for image rewriter.
    
    // Simplest edge cases.
    QTest::newRow("Empty String") << "" << "" << false;
    QTest::newRow("Bad HTML") << "</div>" << "" << false;
    QTest::newRow("Bad HTML 2") << "<b>bold text" << "<b>bold text</b>" << false;
    
    // Newlines need to work within a pre tag.
    QTest::newRow("Pre tag") << "<pre>hello\n\nhi</pre>" << "<pre>hello\n\nhi</pre>"
                             << false;
    
    // Kill line breaks at the end.
    QTest::newRow("Line breaks") << "<p>Bunch of line breaks after last paragraph</p><br><br><br>"
                                 << "<p>Bunch of line breaks after last paragraph</p>"
                                 << false;
    
    // 99 Percent Invisible does this very visible annoyance.
    QTest::newRow("Empty ps") << "<p>Empty paragraphs at end</p><p></p><p>&nbsp;</p><p> </p><p>\n\n</p>"
                              << "<p>Empty paragraphs at end</p>" << false;
    
    // Yeah, WTF, W3C.
    QTest::newRow("Javascript") << "<script>document.write('u eat poop');</script>lol" << "lol"
                                << false;
    QTest::newRow("Javascript 2") << "<h1 onclick=\"alert('OH HAI')\">headline</h1>"
                                  << "<h1>headline</h1>" << false;
    
    // "Share this" images.
    QTest::newRow("Share me") << "<p>hi</p><a href=\"http://www.facebook.com/share.php?u="
                                 "http://www.missionmission.org/2014/07/03/bingo/\"><img src=\""
                                 "http://i.imgur.com/ohnlAzj.png\">Share on Facebook</a>"
                              << "<p>hi</p>"  << true;
    
    // Image size rewriter.
    QTest::newRow("Share me") << "<img src=\"http://i.imgur.com/ohnlAzj.png\">"
                              << "<img src=\"http://i.imgur.com/ohnlAzj.png\" width=\"610\""
                                 " height=\"437\">"  << true;
    
    // Embedded Vine video.
    QTest::newRow("Vine") << "<iframe class=\"vine-embed\" src=\""
                             "https://vine.co/v/MwxwzKAupL6/embed/postcard\" "
                             "width=\"560\" height=\"560\" frameborder=\"0\"></iframe>"
                          << ""  << true;
}

QTEST_MAIN(TestRawFeedRewriterTest)

#include "tst_testrawfeedrewritertest.moc"
