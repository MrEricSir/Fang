#include <memory>

#include <QString>
#include <QTest>
#include <QCoreApplication>
#include <QSignalSpy>
#include <QRegularExpression>
#include <QBuffer>
#include <QImage>

#include "../../src/utilities/RawFeedRewriter.h"
#include "../../src/utilities/HTMLSanitizer.h"
#include "../MockNetworkAccessManager.h"

class TestRawFeedRewriter : public QObject
{
    Q_OBJECT

public:
    TestRawFeedRewriter();

private:
    // Normalize image src attributes for comparison.
    // Replaces cached image paths with a placeholder so we can compare structure.
    static QString normalizeImageSrc(const QString& html);

    // Create an ImageData with a solid-color image of the given dimensions.
    static ImageData createImageData(int width, int height);

    // Create raw PNG bytes at the given dimensions (for mock network responses).
    static QByteArray createTestPNGData(int width, int height);

private slots:
    void testCase1();
    void testCase1_data();

    void testFinalizeUseFetchedDimensions();
    void testFinalizeFilterTrackingPixel();
    void testFinalizeFilterTrackingPixelBoundary();
    void testFinalizeKeepSmallImage();
    void testFinalizeFilterOneTinyDimension();
    void testFinalizeFetchFailedWithDimensions();
    void testFinalizeFetchFailedNoDimensions();
    void testFinalizeSmileyUsesSanitizeDimensions();
};

TestRawFeedRewriter::TestRawFeedRewriter()
{
}

QString TestRawFeedRewriter::normalizeImageSrc(const QString& html)
{
    QString normalized = html;
    // Cached image paths.
    QRegularExpression cachedImageRegex("src=\"/images/[^\"]+\"");
    normalized.replace(cachedImageRegex, "src=\"[CACHED_IMAGE]\"");
    // Strip data-original-src attributes.
    QRegularExpression originalSrcRegex(" data-original-src=\"[^\"]*\"");
    normalized.replace(originalSrcRegex, "");
    return normalized;
}

QByteArray TestRawFeedRewriter::createTestPNGData(int width, int height)
{
    QImage image(width, height, QImage::Format_RGB32);
    image.fill(Qt::red);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return ba;
}

void TestRawFeedRewriter::testCase1()
{
    QFETCH(QString, input);
    QFETCH(QString, output);

    // Mock network: return synthetic images for known URLs so tests don't hit the internet.
    MockNetworkAccessManager mockManager;
    mockManager.addResponse(QUrl("https://www.mrericsir.com/blog/wp-content/uploads/IMG_9016-768x1024.jpeg"),
                            createTestPNGData(768, 1024));
    mockManager.addResponse(QUrl("https://c4.staticflickr.com/8/7684/17161096410_55dcb799a3.jpg"),
                            createTestPNGData(500, 375));
    mockManager.addResponse(QUrl("https://burritojustice.files.wordpress.com/2013/10/bikes-to-books-map-crop.jpg?w=600&h=867"),
                            createTestPNGData(600, 866));
    mockManager.addResponse(QUrl("https://burritojustice.files.wordpress.com/2015/03/bikes-to-books-timeline-crop.png?w=600&h=635"),
                            createTestPNGData(600, 634));
    // imgur is expected to fail — the Streetsblog test verifies HTML-dimension fallback.
    mockManager.addErrorResponse(QUrl("http://i.imgur.com/523Qeov.jpg"),
                                 QNetworkReply::ContentNotFoundError);
    // WordPress emoji (72x72 PNGs with class="wp-smiley") should render at text size,
    // not at their natural 72x72 dimensions.
    mockManager.addResponse(QUrl("https://s.w.org/images/core/emoji/17.0.2/72x72/2728.png"),
                            createTestPNGData(72, 72));

    // Setup our "fake" raw news list.
    auto news = std::make_shared<RawNews>();
    news->description = input;
    QList<std::shared_ptr<RawNews>> newsList;
    newsList.append(news);

    // Send it to the rewriter.
    RawFeedRewriter rewriter(nullptr, &mockManager);
    QSignalSpy spy(&rewriter, &RawFeedRewriter::finished);
    rewriter.rewrite(&newsList);

    if (!spy.count()) {
        QVERIFY(spy.wait(5000));
    }
    
    QCOMPARE(spy.count(), 1);

    // Normalize both strings to handle cached images.
    QString normalizedOutput = normalizeImageSrc(news->description);
    QString normalizedExpected = normalizeImageSrc(output);

    qDebug() << "Expected output: " << normalizedExpected;
    qDebug() << "Output: " << normalizedOutput;

    // Check to see what we got!
    QCOMPARE(normalizedOutput, normalizedExpected);
}

void TestRawFeedRewriter::testCase1_data()
{
    QTest::addColumn<QString>("input");  // HTML input
    QTest::addColumn<QString>("output"); // Expected HTML output

    // Simplest edge cases.
    QTest::newRow("Empty String") << "" << "";
    QTest::newRow("Bad HTML") << "</div>" << "";
    QTest::newRow("Bad HTML 2") << "<b>bold text" << "<b>bold text</b>";
    QTest::newRow("NBSP") << "Hello good sir&nbsp;<b>bold</b>" << "Hello good sir <b>bold</b>";
    QTest::newRow("Anchor") << "<a href=\"http://www.google.com\">link</a>" << "<a href=\"http://www.google.com\">link</a>";

    // Newlines need to work within a pre tag.
    QTest::newRow("Pre tag") << "<pre>hello\n\nhi</pre>" << "<pre>\nhello\n\nhi\n</pre>";

    // Newlines inside pre with nested code tags (e.g. syntax-highlighted code).
    QTest::newRow("Pre with code") << "<pre><code>line1\nline2\nline3</code></pre>"
                                   << "<pre><code>line1\nline2\nline3</code></pre>";

    // Syntax-highlighted code with spans inside pre>code (The Daily WTF pattern).
    QTest::newRow("Pre with spans") << "<pre><code><span class=\"k\">if</span> (x) {\n    y();\n}</code></pre>"
                                    << "<pre><code><span>if</span> (x) {\n    y();\n}</code></pre>";

    // Pre preserves newlines, but regular tags outside pre still collapse them.
    QTest::newRow("Pre and normal") << "<pre>code\nhere</pre><p>normal text</p>"
                                    << "<pre>\ncode\nhere\n</pre><p>normal text</p>";

    // Kill line breaks at the end.
    QTest::newRow("Line breaks") << "<p>Bunch of line breaks after last paragraph</p><br><br><br>"
                                 << "<p>Bunch of line breaks after last paragraph</p>";

    // 99 Percent Invisible does this very visible annoyance.
    QTest::newRow("Empty ps") << "<p>Empty paragraphs at end</p><p></p><p>&nbsp;</p><p> </p><p>\n\n</p>"
                              << "<p>Empty paragraphs at end</p>";

    // Yeah, WTF, W3C.
    QTest::newRow("Javascript") << "<script>document.write('u eat poop');</script>lol" << "lol";
    QTest::newRow("Javascript 2") << "<h1 onclick=\"alert('OH HAI')\">headline</h1>"
                                  << "<h1>headline</h1>";
    
    // "Share this" images.
    QTest::newRow("Share me") << "<p>hi</p><a href=\"http://www.facebook.com/share.php?u="
                                 "http://www.missionmission.org/2014/07/03/bingo/\"><img src=\""
                                 "http://i.imgur.com/ohnlAzj.png\">Share on Facebook</a>"
                              << "<p>hi</p>";

    // Image caching and dimension passthrough.
    // Images that are successfully downloaded are cached for offline viewing.
    // Original dimensions are written to the HTML for browser aspect-ratio layout;
    // CSS handles the max-width cap.
    QTest::newRow("Image test") << "<img src=\"https://www.mrericsir.com/blog/wp-content/uploads/IMG_9016-768x1024.jpeg\">"
                              << "<img src=\"[CACHED_IMAGE]\""
                                 " width=\"768\" height=\"1024\"/>";

    // Image with STYLE attribute (ignored; fetched dimensions used).
    QTest::newRow("Image test 2") << "<img src=\"https://www.mrericsir.com/blog/wp-content/uploads/IMG_9016-768x1024.jpeg\" style=\""
                                 "width: 500px;\">"
                              << "<img src=\"[CACHED_IMAGE]\""
                                 " width=\"768\" height=\"1024\"/>";

    // Image with HTML attributes. Actual fetched dimensions are preferred.
    QTest::newRow("Image test 3") << "<img src=\"https://www.mrericsir.com/blog/wp-content/uploads/IMG_9016-768x1024.jpeg\" align=\"left\""
                                     " width=\"400\" height=\"533\"/>"
                              << "<img src=\"[CACHED_IMAGE]\""
                                 " width=\"768\" height=\"1024\"/>";

    // NJ.com-style: HTML attributes have original width (768) with resizer target height (1200).
    // The actual image is 768x1024. Fetched dimensions should override the wrong HTML attributes.
    QTest::newRow("NJ.com smooshed image") << "<img src=\"https://www.mrericsir.com/blog/wp-content/uploads/IMG_9016-768x1024.jpeg\""
                                              " width=\"768\" height=\"1200\"/>"
                                           << "<img src=\"[CACHED_IMAGE]\""
                                              " width=\"768\" height=\"1024\"/>";

    // Embedded Vine video.
    QTest::newRow("Vine") << "<iframe class=\"vine-embed\" src=\""
                             "https://vine.co/v/MwxwzKAupL6/embed/postcard\" "
                             "width=\"560\" height=\"560\" frameborder=\"0\"></iframe>"
                          << "";

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
                                 << "<div><a href=\"http://la.streetsblog.org/wp-content/uploads/2014/08/hsr-Edited.jpg\">"
                                    "<img src=\"http://i.imgur.com/523Qeov.jpg\" width=\"576\" height=\"267\"/>"
                                    "</a><p>How should California\u2019s high speed rail interface with "
                                    "Los Angeles County? Give your input at an upcoming meeting or via email. "
                                    "Image via CAHSRA</p></div>";

    // MissionLocal whitespace issues
    QTest::newRow("MissionLocal") << "<p>As construction nears completion at V20, the 18 unit condo at 20th and Valencia, Sutter "
                                     "Pacific Medical Foundation plans to open a medical facility in the ground floor commercial "
                                     "space – if it&#8217;s approved by the Planning Commission.  Some Valencia Street neighbors, "
                                     "however,  are working to prevent that from happening or at least working to get it downsized.</p>"
                                  << "<p>As construction nears completion at V20, the 18 unit condo at 20th and Valencia, Sutter "
                                     "Pacific Medical Foundation plans to open a medical facility in the ground floor commercial "
                                     "space – if it’s approved by the Planning Commission. Some Valencia Street neighbors, "
                                     "however, are working to prevent that from happening or at least working to get it downsized.</p>";

    // From MrEricSir.com
    QTest::newRow("Grump Cat") << "<p><a href=\"https://www.flickr.com/photos/mrericsir/17161096410\" title=\"GOOD. by MrEricSir, on Flickr\">"
                                  "<img src=\"https://c4.staticflickr.com/8/7684/17161096410_55dcb799a3.jpg\" width=\"500\" height=\"375\" alt=\"GOOD.\">"
                                  "</a><br />\n&nbsp;</p><p>Grump Cat wearing a bicycle helmet?  I have no idea.  "
                                  "Perhaps it&#8217;s a statement about bicycle helmet laws, or maybe I&#8217;m reading "
                                  "too much into it.  Either way.</p><p>Spotted this wheatpaste during the Cinco de Mayo "
                                  "festival on Valencia.</p>"
                               << "<p><a href=\"https://www.flickr.com/photos/mrericsir/17161096410\">"
                                 "<img src=\"[CACHED_IMAGE]\" width=\"500\" height=\"375\"/>"
                                 "</a></p><p>Grump Cat wearing a bicycle helmet? I have no idea. "
                                 "Perhaps it\u2019s a statement about bicycle helmet laws, or maybe I\u2019m reading "
                                 "too much into it. Either way.</p><p>Spotted this wheatpaste during the Cinco de Mayo "
                                 "festival on Valencia.</p>";

    QTest::newRow("Burrito Justice") << "<p>Come ride the Bikes to Books tour with us on Saturday, May 30! Both the foldable maps and <a href=\"http://burritojustice.com/2015/03/08/bike-to-books-poster-bigger-stronger-faster/\">our new posters</a> will be available for sale.</p>\n"
                                        "<p>It&#8217;s a surprisingly easy ride, and you can have an IPA at the end.</p>\n"
                                        "<p><a href=\"https://burritojustice.files.wordpress.com/2013/10/bikes-to-books-map-crop.jpg\"><img class=\"alignnone size-large wp-image-9283\" src=\"https://burritojustice.files.wordpress.com/2013/10/bikes-to-books-map-crop.jpg?w=600&#038;h=867\" alt=\"bikes to books map crop\" width=\"600\" height=\"867\" /><img class=\"alignnone size-large wp-image-10591\" src=\"https://burritojustice.files.wordpress.com/2015/03/bikes-to-books-timeline-crop.png?w=600&#038;h=635\" alt=\"bikes to books timeline crop\" width=\"600\" height=\"635\" /></a></p>\n"
                                        "<p>&nbsp;</p>\n"
                                        "<p><strong><em>Bikes to Books Annual Springtime Ride!</em></strong></p>\n"
                                        "<p><em><b>Saturday, May 30, 1:00 p.m. &#8211; 4:00 p.m.</b></em></p>\n"
                                        "<p><em><b>Meet at 12:45 p.m. at Jack London Street, at South Park in San Francisco</b></em></p>\n"
                                        "<p><em><b>Ride will commence at 1:00 p.m. sharp</b></em></p>\n"
                                        "<p><em><b>Ride will end at approximately 4:00 p.m. in North Beach, outside City Lights Books</b></em></p>\n"
                                        "<p><em>Bring bikes with gears, snacks, and enthusiasm.</em></p>\n"
                                        "<p><em>Event is free. Maps and posters will be available for purchase.</em></p>\n"
                                        "<p><em>Combining San Francisco history, art, literature, cycling, and urban exploration,  “Bikes to Books” began as an bike ride homage to the 1988 street-naming project spearheaded by City Lights founder and former San Francisco Poet Laureate, Lawrence Ferlinghetti, in which twelve San Francisco streets were renamed for famous artists and authors who had once made San Francisco their home. The 7.1 mile tour, which takes between two and three hours to complete, is admittedly not for the faint of heart nor gear—these streets were not chosen for their proximity to bike lanes, and there is plenty of traffic to dodge, hills to climb, one-way streets, and even a set of stairs. But it’s a diverting and unique way to celebrate both the literary and the adventurous spirit of San Francisco. First published in 2013 in the San Francisco Bay Guardian, and later in partnership with City Lights Books, the physical map can be found in many of San Francisco’s finest book emporiums, and is appropriate for use as a navigational tool, a history lesson, and a unique work of art in its own right.</em></p>\n"
                                        "<p><em><a href=\"http://burritojustice.com/bikes-to-books-map/\" rel=\"nofollow\">http://burritojustice.com/bikes-to-books-map/</a></em></p><br />  <a rel=\"nofollow\" href=\"http://feeds.wordpress.com/1.0/gocomments/burritojustice.wordpress.com/10603/\"><img alt=\"\" border=\"0\" src=\"http://feeds.wordpress.com/1.0/comments/burritojustice.wordpress.com/10603/\" /></a> <img alt=\"\" border=\"0\" src=\"http://pixel.wp.com/b.gif?host=burritojustice.com&#038;blog=4823503&#038;post=10603&#038;subd=burritojustice&#038;ref=&#038;feed=1\" width=\"1\" height=\"1\" />\n"
                                     << "<p>Come ride the Bikes to Books tour with us on Saturday, May 30! Both the foldable maps and <a href=\"http://burritojustice.com/2015/03/08/bike-to-books-poster-bigger-stronger-faster/\"> our new posters</a> will be available for sale.</p>"
                                        "<p>It\u2019s a surprisingly easy ride, and you can have an IPA at the end.</p>"
                                        "<p><a href=\"https://burritojustice.files.wordpress.com/2013/10/bikes-to-books-map-crop.jpg\"><img src=\"[CACHED_IMAGE]\" width=\"600\" height=\"866\"/><img src=\"[CACHED_IMAGE]\" width=\"600\" height=\"634\"/></a></p>"
                                        "<p><strong><em>Bikes to Books Annual Springtime Ride!</em></strong></p>"
                                        "<p><em><b>Saturday, May 30, 1:00 p.m. – 4:00 p.m.</b></em></p>"
                                        "<p><em><b>Meet at 12:45 p.m. at Jack London Street, at South Park in San Francisco</b></em></p>"
                                        "<p><em><b>Ride will commence at 1:00 p.m. sharp</b></em></p>"
                                        "<p><em><b>Ride will end at approximately 4:00 p.m. in North Beach, outside City Lights Books</b></em></p><p><em>Bring bikes with gears, snacks, and enthusiasm.</em></p><p><em>Event is free. Maps and posters will be available for purchase.</em></p>"
                                        "<p><em>Combining San Francisco history, art, literature, cycling, and urban exploration, “Bikes to Books” began as an bike ride homage to the 1988 street-naming project spearheaded by City Lights founder and former San Francisco Poet Laureate, Lawrence Ferlinghetti, in which twelve San Francisco streets were renamed for famous artists and authors who had once made San Francisco their home. The 7.1 mile tour, which takes between two and three hours to complete, is admittedly not for the faint of heart nor gear—these streets were not chosen for their proximity to bike lanes, and there is plenty of traffic to dodge, hills to climb, one-way streets, and even a set of stairs. But it’s a diverting and unique way to celebrate both the literary and the adventurous spirit of San Francisco. First published in 2013 in the San Francisco Bay Guardian, and later in partnership with City Lights Books, the physical map can be found in many of San Francisco’s finest book emporiums, and is appropriate for use as a navigational tool, a history lesson, and a unique work of art in its own right.</em></p><p><em><a href=\"http://burritojustice.com/bikes-to-books-map/\">http://burritojustice.com/bikes-to-books-map/</a></em></p>"
                                        "<a href=\"http://feeds.wordpress.com/1.0/gocomments/burritojustice.wordpress.com/10603/\"/>";

    QTest::newRow("Burrito Law") << "<p>As burritos transcend the Mission, we here at Burrito Justice keep a watchful eye on quality worldwide and frankly, it&#8217;s not looking good. One of our agents has just reported in from the United Kingdom:</p>"
                                    "<p>&nbsp;</p>"
                                    "<p>&nbsp;</p>"
                                    "<div class=\"embed-twitter\">"
                                    "<blockquote class=\"twitter-tweet\" width=\"550\">"
                                    "<p lang=\"en\" dir=\"ltr\">you need new friends RT <a href=\"https://twitter.com/ellaraff\">@ellaraff</a>: a British friend claims &#39;this&#39; is how to eat burritos. Repulsive. <a href=\"https://twitter.com/hhickmore\">@hhickmore</a> <a href=\"http://t.co/MAG147j3NT\">pic.twitter.com/MAG147j3NT</a></p>"
                                    "<p>&mdash; Burrito Justice (@burritojustice) <a href=\"https://twitter.com/burritojustice/status/598580353012400128\">May 13, 2015</a></p></blockquote>"
                                    "<p><script async src=\"//platform.twitter.com/widgets.js\" charset=\"utf-8\"></script></div>"
                                    "<p>WTAF England. Looks like Gibbons needs to get cracking on a new book.</p>"
                                 << "<p>As burritos transcend the Mission, we here at Burrito Justice keep a watchful eye on quality worldwide and frankly, it’s not looking good. One of our agents has just reported in from the United Kingdom:</p>"
                                     "<div>"
                                     "<blockquote>"
                                     "<p>you need new friends RT <a href=\"https://twitter.com/ellaraff\">@ellaraff</a>: a British friend claims 'this' is how to eat burritos. Repulsive. <a href=\"https://twitter.com/hhickmore\">@hhickmore</a> <a href=\"http://t.co/MAG147j3NT\">pic.twitter.com/MAG147j3NT</a></p>"
                                     "<p>— Burrito Justice (@burritojustice) <a href=\"https://twitter.com/burritojustice/status/598580353012400128\">May 13, 2015</a></p></blockquote>"
                                     "</div>"
                                     "<p>WTAF England. Looks like Gibbons needs to get cracking on a new book.</p>";

    QTest::newRow("Stripe") << "<p>Starting at 10am Pacific Time this morning, you can watch "
                               "<a href=\"http://en.wikipedia.org/wiki/The_Interview_(2014_film)\">"
                               "The Interview</a> at <a href=\"https://www.seetheinterview.com\">"
                               "SeeTheInterview.com</a>, powered by Stripe.</p>"
                            << "<p>Starting at 10am Pacific Time this morning, you can watch "
                               "<a href=\"http://en.wikipedia.org/wiki/The_Interview_(2014_film)\">"
                               "The Interview</a> at <a href=\"https://www.seetheinterview.com\">"
                               "SeeTheInterview.com</a>, powered by Stripe.</p>";

    QTest::newRow("Stripe 2") << "<p>There’s also equivalent functionality available in the API—check out "
                                 "<a href=\"https://stripe.com/docs/fraud\">the documentation</a> for more details.</p>"
                              << "<p>There’s also equivalent functionality available in the API—check out "
                                 "<a href=\"https://stripe.com/docs/fraud\">the documentation</a> for more details.</p>";

    QTest::newRow("ML 2") << "<p>3.) Books on Socialism and Stalinism sell well regularly. Everything from <a href=\""
                             "https://www.etsy.com/listing/220145869/alexander-rodchenko-photographs-moscow\"><em>"
                             "Moscow</em> </a><em><a href=\"https://www.etsy.com/listing/220145869/alexander-rodchenko-photographs-moscow\""
                             ">1939</a>, </em>a Stalinist photography book, to hows and whys of the socialist party, such as <em><a href=\""
                             "http://www.amazon.co.uk/What-Socialist-Frederick-William-Jowett/dp/B000IUC17C\">"
                             "What Made Me a Socialist</a> </em>by Frederick William Jowett .</p>"
                          << "<p>3.) Books on Socialism and Stalinism sell well regularly. Everything from <a href=\""
                             "https://www.etsy.com/listing/220145869/alexander-rodchenko-photographs-moscow\"><em>"
                             "Moscow</em></a> <em><a href=\"https://www.etsy.com/listing/220145869/alexander-rodchenko-photographs-moscow\""
                             "> 1939</a>,</em> a Stalinist photography book, to hows and whys of the socialist party, such as <em><a href=\""
                             "http://www.amazon.co.uk/What-Socialist-Frederick-William-Jowett/dp/B000IUC17C\">"
                             " What Made Me a Socialist</a></em> by Frederick William Jowett .</p>";

    QTest::newRow("Text only") << " This is the first paragraph. I hope you like it!\n"
                               "Now this one -- this is the second paragraph.  "
                            << "<p>This is the first paragraph. I hope you like it!</p>"
                               "<p>Now this one -- this is the second paragraph.</p>";

    QTest::newRow("Text only 2") << "Just one line of text!"
                            << "<p>Just one line of text!</p>";

    QTest::newRow("Text only 3") << "Here's our first paragraph, ok?  You like?\r\n\r\n  \r\n   Here is the second one."
                            << "<p>Here's our first paragraph, ok?  You like?</p><p>Here is the second one.</p>";

    QTest::newRow("Mission Loco") << "<p>San Francisco’s 37th<span style=\"font-size: 10px; line-height: 9.09090900421143px;\"> </span>annual Carnaval festival is about the samba its way into the world once more. The two-day event kicks off with <a href=\"http://www.eventbrite.com/e/sf-carnaval-2015-kick-off-celebration-tickets-4393908298\">a party Thursday night at the Elbo Room</a>, followed on Saturday by a street festival and Sunday&#8217;s always epic parade of dancing, music, and costumed-extravagance.</p>"
                                    "<p>This year’s theme: Agua Sagrada, Spanish for &#8220;sacred water,&#8221; a reference to the current drought.</p>"
                                    "<p>Saturday’s festival, which takes over Harrison Street from 16th to 24th Street, has a musical lineup of nearly 20 bands playing across various stages, and includes a performance by Latin Jazz artist and Sheila E.’s father Pete Escovedo with Ray Obiedo. Other performers will be a Jimi Hendrix tribute band, <em>Harold Day and the Experience</em> and <em>Jose Najera and the Bernal Beat</em>.</p>"
                                    "<p><a href=\"http://www.nowmap.com/carnavalsf\">The parade </a> on Sunday will start at 9:30 am from 24<sup>th</sup> and Bryant St. to 24<sup>th</sup> and Mission, then north on Mission towards 17<sup>th</sup> and South Van Ness. The festival and parade have seen 400,000 visitors in previous years. But if you don&#8217;t want to be in the crowd, you can buy tickets to your own <a href=\"http://www.carnavalsanfrancisco.org/2015-events\">private reserved seating</a>, $30 dollars per ticket.  Otherwise, admission is free.</p>"
                                    "<p>The one and only Sheila E., best known as artist Prince’s drummer, will be leading the parade as this year’s Parade Grand Marshal. Former parade dignitaries have been actor Benjamin Pratt and his brother Peter Pratt, and San Francisco born actor Danny Glover.</p>"
                                    "<p>Parking will be restricted along the parade route starting on Friday the 22nd at 7 pm.  <a href=\"http://www.carnavalsanfrancisco.org/neighborhood--residents\">Check here</a> before  you park, for a full list of streets that will be towing cars.</p>"
                                    "<p>Carnaval is traditionally a festival held 40-50 days before Easter as a farewell to bad things and a beginning of a season of religious discipline. Carnaval translates to “to remove meat,” because Catholics traditionally give up meat for Lent.</p>"
                                    "<p>For a flavor of the flavor to come, check out our video fête:<br />"
                                    "<iframe src=\"https://player.vimeo.com/video/96467804\" width=\"600\" height=\"337\" frameborder=\"0\" allowfullscreen=\"allowfullscreen\"></iframe></p>"
                                    "<h2><em><a href=\"http://missionlocal.org/calendar-14/\">Events in the Mission Today</a></em></h2>"
                                    "<h2><em><a href=\"http://missionlocal.org/newcomers/\">The Essential Mission Guide</a></em></h2>"
                                  << "<p>San Francisco’s 37th annual Carnaval festival is about the samba its way into the world once more. The two-day event kicks off with <a href=\"http://www.eventbrite.com/e/sf-carnaval-2015-kick-off-celebration-tickets-4393908298\"> a party Thursday night at the Elbo Room</a>, followed on Saturday by a street festival and Sunday’s always epic parade of dancing, music, and costumed-extravagance.</p>"
                                     "<p>This year’s theme: Agua Sagrada, Spanish for “sacred water,” a reference to the current drought.</p>"
                                     "<p>Saturday’s festival, which takes over Harrison Street from 16th to 24th Street, has a musical lineup of nearly 20 bands playing across various stages, and includes a performance by Latin Jazz artist and Sheila E.’s father Pete Escovedo with Ray Obiedo. Other performers will be a Jimi Hendrix tribute band, <em>Harold Day and the Experience</em> and <em>Jose Najera and the Bernal Beat</em>.</p>"
                                     "<p><a href=\"http://www.nowmap.com/carnavalsf\">The parade</a> on Sunday will start at 9:30 am from 24<sup>th</sup> and Bryant St. to 24<sup>th</sup> and Mission, then north on Mission towards 17<sup>th</sup> and South Van Ness. The festival and parade have seen 400,000 visitors in previous years. But if you don’t want to be in the crowd, you can buy tickets to your own <a href=\"http://www.carnavalsanfrancisco.org/2015-events\">private reserved seating</a>, $30 dollars per ticket. Otherwise, admission is free.</p>"
                                     "<p>The one and only Sheila E., best known as artist Prince’s drummer, will be leading the parade as this year’s Parade Grand Marshal. Former parade dignitaries have been actor Benjamin Pratt and his brother Peter Pratt, and San Francisco born actor Danny Glover.</p>"
                                     "<p>Parking will be restricted along the parade route starting on Friday the 22nd at 7 pm. <a href=\"http://www.carnavalsanfrancisco.org/neighborhood--residents\">Check here</a> before you park, for a full list of streets that will be towing cars.</p>"
                                     "<p>Carnaval is traditionally a festival held 40-50 days before Easter as a farewell to bad things and a beginning of a season of religious discipline. Carnaval translates to “to remove meat,” because Catholics traditionally give up meat for Lent.</p>"
                                     "<p>For a flavor of the flavor to come, check out our video fête:<br/>"
                                     "</p>"
                                     "<h2><em><a href=\"http://missionlocal.org/calendar-14/\">Events in the Mission Today</a></em></h2>"
                                     "<h2><em><a href=\"http://missionlocal.org/newcomers/\">The Essential Mission Guide</a></em></h2>";

    // WordPress emoji (wp-smiley class): 72x72 PNGs that should display inline at text
    // size, not at their natural pixel dimensions. The style="height: 1em" is stripped
    // by the sanitizer, so we need to detect wp-smiley and set small dimensions.
    QTest::newRow("WP Smiley") << "<p>Celebrate <img src=\"https://s.w.org/images/core/emoji/17.0.2/72x72/2728.png\""
                                  " alt=\"✨\" class=\"wp-smiley\" style=\"height: 1em; max-height: 1em;\" /> today!</p>"
                               << "<p>Celebrate <img src=\"[CACHED_IMAGE]\""
                                  " width=\"16\" height=\"16\" class=\"smiley\"/> today!</p>";
}

ImageData TestRawFeedRewriter::createImageData(int width, int height)
{
    ImageData data;
    data.image = QImage(width, height, QImage::Format_RGB32);
    data.image.fill(Qt::red);

    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    data.image.save(&buffer, "PNG");
    data.rawData = ba;
    data.mimeType = "image/png";
    return data;
}

// Test that finalize() uses actual fetched dimensions, not HTML attributes.
void TestRawFeedRewriter::testFinalizeUseFetchedDimensions()
{
    HTMLSanitizer sanitizer;

    // Simulate sanitize() output: an img tag with HTML dimensions as metadata.
    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<img id=\"FangID_3\" src=\"http://example.com/photo.jpg\""
                        " width=\"200\" height=\"100\"/>"
                        "</body></html>";

    // Provide a fetched image with different dimensions.
    QMap<QUrl, ImageData> results;
    results[QUrl("http://example.com/photo.jpg")] = createImageData(800, 600);

    QString output = sanitizer.finalize(sanitized, results);

    // Should use fetched dimensions (800x600), not HTML (200x100).
    QVERIFY(output.contains("width=\"800\""));
    QVERIFY(output.contains("height=\"600\""));
    QVERIFY(!output.contains("width=\"200\""));
}

// Test that finalize() filters tracking pixels detected by fetched dimensions.
void TestRawFeedRewriter::testFinalizeFilterTrackingPixel()
{
    HTMLSanitizer sanitizer;

    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<p id=\"FangID_3\">text</p>"
                        "<img id=\"FangID_4\" src=\"http://example.com/pixel.gif\"/>"
                        "</body></html>";

    // Fetched image is 1x1 - a tracking pixel.
    QMap<QUrl, ImageData> results;
    results[QUrl("http://example.com/pixel.gif")] = createImageData(1, 1);

    QString output = sanitizer.finalize(sanitized, results);

    QVERIFY(!output.contains("pixel.gif"));
    QVERIFY(output.contains("text"));
}

// Test that a 2x2 image is filtered (boundary case - must be > 2 to keep).
void TestRawFeedRewriter::testFinalizeFilterTrackingPixelBoundary()
{
    HTMLSanitizer sanitizer;

    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<p id=\"FangID_3\">text</p>"
                        "<img id=\"FangID_4\" src=\"http://example.com/tiny.gif\"/>"
                        "</body></html>";

    QMap<QUrl, ImageData> results;
    results[QUrl("http://example.com/tiny.gif")] = createImageData(2, 2);

    QString output = sanitizer.finalize(sanitized, results);

    QVERIFY(!output.contains("tiny.gif"));
    QVERIFY(output.contains("text"));
}

// Test that a 3x3 image is kept (boundary case - smallest non-tracking-pixel).
void TestRawFeedRewriter::testFinalizeKeepSmallImage()
{
    HTMLSanitizer sanitizer;

    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<img id=\"FangID_3\" src=\"http://example.com/small.png\"/>"
                        "</body></html>";

    QMap<QUrl, ImageData> results;
    results[QUrl("http://example.com/small.png")] = createImageData(3, 3);

    QString output = sanitizer.finalize(sanitized, results);

    QVERIFY(output.contains("width=\"3\""));
    QVERIFY(output.contains("height=\"3\""));
}

// Test that one tiny dimension is enough to filter (e.g. 1x1000 spacer gif).
void TestRawFeedRewriter::testFinalizeFilterOneTinyDimension()
{
    HTMLSanitizer sanitizer;

    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<p id=\"FangID_3\">text</p>"
                        "<img id=\"FangID_4\" src=\"http://example.com/spacer.gif\"/>"
                        "</body></html>";

    QMap<QUrl, ImageData> results;
    results[QUrl("http://example.com/spacer.gif")] = createImageData(1, 1000);

    QString output = sanitizer.finalize(sanitized, results);

    QVERIFY(!output.contains("spacer.gif"));
    QVERIFY(output.contains("text"));
}

// Test that finalize() keeps images with HTML dimensions when fetch fails.
void TestRawFeedRewriter::testFinalizeFetchFailedWithDimensions()
{
    HTMLSanitizer sanitizer;

    // Image has width/height metadata from sanitize() (known good dimensions).
    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<img id=\"FangID_3\" src=\"http://example.com/photo.jpg\""
                        " width=\"640\" height=\"480\"/>"
                        "</body></html>";

    // Empty results - fetch failed.
    QMap<QUrl, ImageData> results;

    QString output = sanitizer.finalize(sanitized, results);

    // Should keep the image with HTML dimensions.
    QVERIFY(output.contains("photo.jpg"));
    QVERIFY(output.contains("width=\"640\""));
    QVERIFY(output.contains("height=\"480\""));
}

// Test that finalize() skips images with no dimensions when fetch fails.
void TestRawFeedRewriter::testFinalizeFetchFailedNoDimensions()
{
    HTMLSanitizer sanitizer;

    // Image has no width/height metadata - could be a tracking pixel.
    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<p id=\"FangID_3\">text</p>"
                        "<img id=\"FangID_4\" src=\"http://example.com/mystery.gif\"/>"
                        "</body></html>";

    // Empty results - fetch failed.
    QMap<QUrl, ImageData> results;

    QString output = sanitizer.finalize(sanitized, results);

    // Should skip the image - can't verify it's not a tracking pixel.
    QVERIFY(!output.contains("mystery.gif"));
    QVERIFY(output.contains("text"));
}

// Test that wp-smiley images use the small dimensions from sanitize()
// even when the fetched image has larger pixel dimensions.
void TestRawFeedRewriter::testFinalizeSmileyUsesSanitizeDimensions()
{
    HTMLSanitizer sanitizer;

    // Simulates sanitize() output for a wp-smiley image: small dimensions
    // and a data-smiley marker, even though the actual image is 72x72.
    QString sanitized = "<?xml version=\"1.0\"?>"
                        "<html id=\"FangID_1\"><body id=\"FangID_2\">"
                        "<p id=\"FangID_3\">text "
                        "<img id=\"FangID_4\" src=\"https://s.w.org/images/core/emoji/17.0.2/72x72/2728.png\""
                        " width=\"16\" height=\"16\" data-smiley=\"1\"/>"
                        "</p></body></html>";

    // Fetched image is 72x72 — but finalize should use 16x16 from sanitize.
    QMap<QUrl, ImageData> results;
    results[QUrl("https://s.w.org/images/core/emoji/17.0.2/72x72/2728.png")] = createImageData(72, 72);

    QString output = sanitizer.finalize(sanitized, results);

    QVERIFY(output.contains("width=\"16\""));
    QVERIFY(output.contains("height=\"16\""));
    QVERIFY(!output.contains("width=\"72\""));
    QVERIFY(!output.contains("data-smiley"));
    QVERIFY(output.contains("class=\"smiley\""));
}

QTEST_MAIN(TestRawFeedRewriter)

#include "tst_rawfeedrewriter.moc"
