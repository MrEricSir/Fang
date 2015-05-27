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
    
    // Setup our "fake" raw news list.
    RawNews news;
    news.description = input;
    QList<RawNews*> newsList;
    newsList.append(&news);
    
    // Send it to the rewriter.
    RawFeedRewriter rewriter;
    QSignalSpy spy(&rewriter, SIGNAL(finished()));
    rewriter.rewrite(&newsList);
    
    if (!spy.count()) {
        // If the signal hasn't fired yet it's because there's images to be downloaded.
        QVERIFY(spy.wait());  // default: up to 5 seconds
    }
    
    QCOMPARE(spy.count(), 1);
    
    qDebug() << "Expected output: " << output;
    qDebug() << "Output: " << news.description;
    
    // Check to see what we got!
    QCOMPARE(news.description, output);
}

void TestRawFeedRewriterTest::testCase1_data()
{
    QTest::addColumn<QString>("input");  // HTML input
    QTest::addColumn<QString>("output"); // Expected HTML output
/*
    // Simplest edge cases.
    QTest::newRow("Empty String") << "" << "";
    QTest::newRow("Bad HTML") << "</div>" << "";
    QTest::newRow("Bad HTML 2") << "<b>bold text" << "<b>bold text</b>";
    QTest::newRow("NBSP") << "Hello good sir&nbsp;<b>bold</b>" << "Hello good sir <b>bold</b>";
    QTest::newRow("Anchor") << "<a href=\"http://www.google.com\">link</a>" << "<a href=\"http://www.google.com\">link</a>";

    // Newlines need to work within a pre tag.
    QTest::newRow("Pre tag") << "<pre>hello\n\nhi</pre>" << "<pre> hello\n\nhi </pre>";

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

    // Image size rewriter (and reducer.)
    QTest::newRow("Image test") << "<img src=\"http://i.imgur.com/ohnlAzj.png\">"
                              << "<img src=\"http://i.imgur.com/ohnlAzj.png\""
                                 " width=\"400\" height=\"286\" align=\"left\"/>";

    // Image size rewriter (and reducer) with STYLE.
    QTest::newRow("Image test 2") << "<img src=\"http://i.imgur.com/ohnlAzj.png\" style=\""
                                 "width: 500px;\">"
                              << "<img src=\"http://i.imgur.com/ohnlAzj.png\""
                                 " width=\"400\" height=\"286\" align=\"left\"/>";

    // Image size WITHOUT rewriter.
    QTest::newRow("Image test 3") << "<img src=\"http://i.imgur.com/ohnlAzj.png\" align=\"left\""
                                     " width=\"400\" height=\"286\"/>"
                              << "<img src=\"http://i.imgur.com/ohnlAzj.png\""
                                 " width=\"400\" height=\"286\" align=\"left\"/>";

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
                                    "<img src=\"http://i.imgur.com/523Qeov.jpg\" width=\"400\" height=\"185\" "
                                    "align=\"left\"/></a><p>How should California’s high speed rail interface with "
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
                                 "<img src=\"https://c4.staticflickr.com/8/7684/17161096410_55dcb799a3.jpg\" width=\"400\" height=\"300\" align=\"left\"/>"
                                 "</a></p><p>Grump Cat wearing a bicycle helmet? I have no idea. "
                                 "Perhaps it’s a statement about bicycle helmet laws, or maybe I’m reading "
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
                                        "<p>It’s a surprisingly easy ride, and you can have an IPA at the end.</p>"
                                        "<p><a href=\"https://burritojustice.files.wordpress.com/2013/10/bikes-to-books-map-crop.jpg\"><img src=\"https://burritojustice.files.wordpress.com/2013/10/bikes-to-books-map-crop.jpg?w=600&amp;h=867\" width=\"400\" height=\"578\" align=\"left\"/><img src=\"https://burritojustice.files.wordpress.com/2015/03/bikes-to-books-timeline-crop.png?w=600&amp;h=635\" width=\"400\" height=\"423\" align=\"left\"/></a></p>"
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
                            */
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
}

QTEST_MAIN(TestRawFeedRewriterTest)

#include "tst_testrawfeedrewritertest.moc"
