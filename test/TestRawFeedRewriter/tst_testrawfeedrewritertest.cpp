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
    // NOTE: In order to achieve consistent results, the QT_HASH_SEED environment variable MUST
    // be set to 1

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
    
    //qDebug() << "Expected output: " << output;
    //qDebug() << "Output: " << news.description;
    
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
                              << "<p>hi</p>"  << false; // The image gets removed by the share detector
    
    // Image size rewriter (and reducer.)
    QTest::newRow("Image test") << "<img src=\"http://i.imgur.com/ohnlAzj.png\">"
                              << "<img height=\"286\" width=\"400\" align=\"left\""
                                 " src=\"http://i.imgur.com/ohnlAzj.png\"/>"  << true;
    
    // Image size rewriter (and reducer) with STYLE.
    QTest::newRow("Image test 2") << "<img src=\"http://i.imgur.com/ohnlAzj.png\" style=\""
                                 "width: 500px;\">"
                                  << "<img height=\"286\" width=\"400\" align=\"left\""
                                     " src=\"http://i.imgur.com/ohnlAzj.png\"/>"  << true;
    
    // Embedded Vine video.
    QTest::newRow("Vine") << "<iframe class=\"vine-embed\" src=\""
                             "https://vine.co/v/MwxwzKAupL6/embed/postcard\" "
                             "width=\"560\" height=\"560\" frameborder=\"0\"></iframe>"
                          << ""  << false;

    // Streetsblog formatting
    QTest::newRow("Streetsblog") << "<p><div class=\"wp-caption aligncenter\" id=\"attachment_98788\" "
                                    "style=\"width: 586px;\"><a href=\"http://la.streetsblog.org/"
                                    "wp-content/uploads/2014/08/hsr-Edited.jpg\"><img alt=\"How should "
                                    "California's high speed rail interface with Los Angeles County? Give "
                                    "your input at an upcoming meeting or via email. Image via CAHSRA\" "
                                    "class=\" wp-image-98788 \" height=\"267\" src=\"http://i.imgur.com/523Qeov.jpg\" "
                                    "width=\"576\" /></a>"
                                    "<p class=\"wp-caption-text\">How should California&#8217;s high speed "
                                    "rail interface with Los Angeles County? Give your input at an upcoming "
                                    "meeting or via email. Image via CAHSRA</p></div></p>"
                                 << "<div id=\"attachment_98788\" class=\"wp-caption aligncenter\">"
                                    "<a href=\"http://la.streetsblog.org/wp-content/uploads/2014/08/hsr-Edited.jpg\">"
                                    "<img alt=\"How should California's high speed rail interface with Los Angeles "
                                    "County? Give your input at an upcoming meeting or via email. Image via CAHSRA\" "
                                    "height=\"185\" width=\"400\" align=\"left\" class=\"wp-image-98788\" "
                                    "src=\"http://i.imgur.com/523Qeov.jpg\"/></a><p class=\"wp-caption-text\">How should "
                                    "California’s high speed rail interface with Los Angeles County? Give your input "
                                    "at an upcoming meeting or via email. Image via CAHSRA</p></div>"  << false; // No image resize
}

QTEST_MAIN(TestRawFeedRewriterTest)

#include "tst_testrawfeedrewritertest.moc"
