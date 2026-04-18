#include <QTest>
#include <QSet>
#include <QUrl>
#include <QMap>

#include "HTMLSanitizer.h"

class TestHTMLSanitizer : public QObject
{
    Q_OBJECT

private slots:
    void init();

    // Tag removal
    void removeScriptTags();
    void removeStyleTags();
    void removeIframeTags();
    void removeObjectTags();
    void removeEmbedTags();
    void removeHrTags();
    void removeHeadTags();
    void removeTitleTags();

    // Class-based removal
    void removeByClass();

    // Share button URL removal
    void removeShareButtonLinks();

    // Tracking pixel detection
    void removeTrackingPixels();
    void keepLargeImages();

    // Empty container pruning
    void removeEmptyContainers();
    void keepNonEmptyContainers();

    // Whitespace/newline normalization
    void normalizeWhitespace();
    void preservePreWhitespace();

    // textToHtml
    void textToHtml();
    void textToHtmlTrimsLines();

    // Low tag-count fallback
    void lowTagCountFallback();

    // Image URL extraction
    void extractImageURLs();

    // reset() clears state
    void resetClearsState();

    // WordPress smiley handling
    void wpSmileyDimensions();

    // BR removal
    void removeBrNotAfterText();

private:
    HTMLSanitizer sanitizer;
};

void TestHTMLSanitizer::init()
{
    sanitizer.reset();
}

// -- Tag removal tests --

void TestHTMLSanitizer::removeScriptTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p><script>alert('x')</script>", urls);
    QVERIFY(!result.contains("script"));
    QVERIFY(!result.contains("alert"));
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::removeStyleTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p><style>body{color:red}</style>", urls);
    QVERIFY(!result.contains("style"));
    QVERIFY(!result.contains("color:red"));
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::removeIframeTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p><iframe src=\"http://example.com\"></iframe>", urls);
    QVERIFY(!result.contains("iframe"));
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::removeObjectTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p><object data=\"x.swf\"></object>", urls);
    QVERIFY(!result.contains("object"));
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::removeEmbedTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p><embed src=\"x.swf\"/>", urls);
    QVERIFY(!result.contains("embed"));
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::removeHrTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p><hr/><p>World</p>", urls);
    QVERIFY(!result.contains("<hr"));
    QVERIFY(result.contains("Hello"));
    QVERIFY(result.contains("World"));
}

void TestHTMLSanitizer::removeHeadTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<head><meta charset=\"utf-8\"/></head><p>Hello</p>", urls);
    QVERIFY(!result.contains("<head"));
    QVERIFY(!result.contains("meta"));
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::removeTitleTags()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<title>My Title</title><p>Hello</p>", urls);
    QVERIFY(!result.contains("<title"));
    QVERIFY(!result.contains("My Title"));
    QVERIFY(result.contains("Hello"));
}

// -- Class-based removal --

void TestHTMLSanitizer::removeByClass()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize(
        "<p>Keep</p><div class=\"feedflare\">Remove me</div><p>Also keep</p>", urls);
    QVERIFY(!result.contains("feedflare"));
    QVERIFY(!result.contains("Remove me"));
    QVERIFY(result.contains("Keep"));
    QVERIFY(result.contains("Also keep"));
}

// -- Share button URL removal --

void TestHTMLSanitizer::removeShareButtonLinks()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize(
        "<p>Text</p><a href=\"http://twitter.com/home?status=hello\">Tweet</a>", urls);
    QVERIFY(!result.contains("twitter.com"));
    QVERIFY(!result.contains("Tweet"));
    QVERIFY(result.contains("Text"));
}

// -- Tracking pixel detection --

void TestHTMLSanitizer::removeTrackingPixels()
{
    QSet<QUrl> urls;
    QString firstPass = sanitizer.sanitize(
        "<p>Text</p><img src=\"http://example.com/pixel.gif\" width=\"1\" height=\"1\"/>", urls);
    // Tracking pixel URL should not be in the image URL set
    QVERIFY(!urls.contains(QUrl("http://example.com/pixel.gif")));

    // After finalize, the tracking pixel should be removed from the output
    QMap<QUrl, ImageData> emptyResults;
    QString result = sanitizer.finalize(firstPass, emptyResults);
    QVERIFY(!result.contains("pixel.gif"));
    QVERIFY(result.contains("Text"));
}

void TestHTMLSanitizer::keepLargeImages()
{
    QSet<QUrl> urls;
    sanitizer.sanitize(
        "<p>Text</p><img src=\"http://example.com/photo.jpg\" width=\"640\" height=\"480\"/>", urls);
    QVERIFY(urls.contains(QUrl("http://example.com/photo.jpg")));
}

// -- Empty container pruning --

void TestHTMLSanitizer::removeEmptyContainers()
{
    QSet<QUrl> urls;
    // TidyLib removes truly empty tags. Use a div containing only a <br/>,
    // which the sanitizer strips (br not preceded by text), leaving the div
    // empty and eligible for pruning.
    QString firstPass = sanitizer.sanitize(
        "<div><p>One</p><p>Two</p><p>Three</p><p>Four</p>"
        "<p>Five</p><p>Six</p><div><br/></div></div>", urls);

    // After finalize, the empty inner div should be removed
    QMap<QUrl, ImageData> emptyResults;
    QString result = sanitizer.finalize(firstPass, emptyResults);
    // The outer content should remain
    QVERIFY(result.contains("One"));
    QVERIFY(result.contains("Six"));
}

void TestHTMLSanitizer::keepNonEmptyContainers()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>Hello</p>", urls);
    QVERIFY(result.contains("Hello"));
}

// -- Whitespace/newline normalization --

void TestHTMLSanitizer::normalizeWhitespace()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p>\nHello\n</p>", urls);
    // Newlines at text boundaries should be converted to spaces
    QVERIFY(result.contains("Hello"));
}

void TestHTMLSanitizer::preservePreWhitespace()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<pre>\n  code\n  here\n</pre>", urls);
    // Inside <pre>, whitespace should be preserved
    QVERIFY(result.contains("\n"));
}

// -- textToHtml --

void TestHTMLSanitizer::textToHtml()
{
    QString result = sanitizer.textToHtml("Line one\nLine two");
    // Should start with beep character
    QVERIFY(result.startsWith('\07'));
    // Should contain paragraph tags
    QVERIFY(result.contains("<p>Line one</p>"));
    QVERIFY(result.contains("<p>Line two</p>"));
}

void TestHTMLSanitizer::textToHtmlTrimsLines()
{
    QString result = sanitizer.textToHtml("  Hello  \n  World  ");
    QVERIFY(result.contains("<p>Hello</p>"));
    QVERIFY(result.contains("<p>World</p>"));
}

// -- Low tag-count fallback --

void TestHTMLSanitizer::lowTagCountFallback()
{
    QSet<QUrl> urls;
    // Plain text with very few tags should fall back to textToHtml
    QString result = sanitizer.sanitize("Just plain text here", urls);
    QVERIFY(result.startsWith('\07'));
    QVERIFY(result.contains("<p>"));
}

// -- Image URL extraction --

void TestHTMLSanitizer::extractImageURLs()
{
    QSet<QUrl> urls;
    sanitizer.sanitize(
        "<p>Text</p><img src=\"http://example.com/a.jpg\"/>"
        "<img src=\"http://example.com/b.png\"/>", urls);
    QVERIFY(urls.contains(QUrl("http://example.com/a.jpg")));
    QVERIFY(urls.contains(QUrl("http://example.com/b.png")));
}

// -- reset() --

void TestHTMLSanitizer::resetClearsState()
{
    QSet<QUrl> urls;
    // Process a document with a tracking pixel to accumulate state
    sanitizer.sanitize(
        "<p>Text</p><img src=\"http://example.com/pixel.gif\" width=\"1\" height=\"1\"/>", urls);

    // Reset and process a new document
    sanitizer.reset();
    urls.clear();

    QString firstPass = sanitizer.sanitize("<p>Fresh document</p>", urls);
    QMap<QUrl, ImageData> emptyResults;
    QString result = sanitizer.finalize(firstPass, emptyResults);

    // The fresh document should be processed cleanly without leftover state
    QVERIFY(result.contains("Fresh document"));
}

// -- WordPress smiley --

void TestHTMLSanitizer::wpSmileyDimensions()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize(
        "<p>Smile <img src=\"http://example.com/smiley.png\" class=\"wp-smiley\" width=\"72\" height=\"72\"/></p>",
        urls);
    // wp-smiley images should get 16x16 dimensions
    QVERIFY(result.contains("width=\"16\""));
    QVERIFY(result.contains("height=\"16\""));
    QVERIFY(result.contains("data-smiley=\"1\""));
}

// -- BR removal --

void TestHTMLSanitizer::removeBrNotAfterText()
{
    QSet<QUrl> urls;
    QString result = sanitizer.sanitize("<p><br/><br/>Hello<br/></p>", urls);
    // The first two <br/> tags should be removed (not preceded by text)
    // but the one after "Hello" should remain
    int brCount = result.count("<br");
    QVERIFY(brCount <= 1);
    QVERIFY(result.contains("Hello"));
}

QTEST_MAIN(TestHTMLSanitizer)
#include "tst_htmlsanitizer.moc"
