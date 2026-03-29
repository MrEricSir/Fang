#include "RSSAtomParser.h"
#include "FeedDateParser.h"
#include "FeedParserLogging.h"

// Some feeds (e.g. excelsior.com.mx) double-escape CDATA markers, producing
// literal "<![CDATA[...]]>" text instead of actual CDATA sections. Strip them.
static QString stripEscapedCDATA(const QString& text)
{
    QString trimmed = text.trimmed();
    if (trimmed.startsWith("<![CDATA[") && trimmed.endsWith("]]>")) {
        return trimmed.mid(9, trimmed.length() - 12).trimmed();
    }
    return text;
}

std::unique_ptr<RawFeed> RSSAtomParser::parse(const QByteArray& data)
{
    RSSAtomParser worker;

    // Init
    worker.feed = std::make_unique<RawFeed>();
    worker.isValid = true;
    worker.resetParserVars();

    // Parse
    worker.xml.addData(data);
    while (!worker.xml.atEnd()) {
        worker.xml.readNext();
        if (worker.xml.isStartElement()) {
            worker.elementStart();
        } else if (worker.xml.isEndElement()) {
            worker.elementEnd();
        } else if (worker.xml.isCharacters() && !worker.xml.isWhitespace()) {
            worker.elementContents();
        }
    }

    if (worker.xml.error()
        && worker.xml.error() != QXmlStreamReader::PrematureEndOfDocumentError
        && worker.xml.error() != QXmlStreamReader::NotWellFormedError) {
        worker.isValid = false;
        qCWarning(logFeedParser) << "XML ERROR:" << worker.xml.lineNumber()
                                 << ": " << worker.xml.errorString();
    }

    // Finalize
    if (worker.isValid && worker.feed->items.size() == 0) {
        worker.saveSummary();
    }

    return std::move(worker.feed);
}

RSSAtomParser::RSSAtomParser() :
    feed(nullptr), currentItem(nullptr), isValid(false), inAtomXHTML(false)
{
}

RSSAtomParser::~RSSAtomParser()
{
}

void RSSAtomParser::elementStart()
{
    QString tagName = xml.name().toString().toLower();
    
    // Look for start of entries.
    //qDebug() << "XML node: " << xml.name().toString() << " " << xml.prefix().toString();
    if ((tagName == "item" || tagName == "entry") && !inAtomXHTML) {
        
        if (urlHref.isEmpty()) {
            urlHref = xml.attributes().value("rss:about").toString();
        }
        
        if (numItems == 0) {
            // Oh, first item?  Assume we've seen the summary then.
            saveSummary();
        }
        
        currentItem = std::make_shared<RawNews>();
        numItems++;
    } else if ((tagName == "content" || tagName == "summary") && 
               xml.attributes().value("type").toString().toLower() == "xhtml") {
        // Atom has a crappy feature where you can just stick unescaped xhtml
        // into the Atom's DOM.  Someone at Google must not believe in SAX
        // parsers, I guess?
        inAtomXHTML = true;
    } else if (inAtomXHTML) {
        // Build a string of the tag's elements.
        QString elements = "";
        QXmlStreamAttributes attributes = xml.attributes();
        for (QXmlStreamAttribute attribute : attributes) {
            elements += " " + attribute.name().toString() + "=\""
                        + attribute.value().toString() + "\"";
        }
        
        // Mash the tag together.
        content += "<" + xml.qualifiedName().toString() + elements + ">";
        
        // Early exit!
        return;
    }
    
    currentTag = tagName;
    currentPrefix = xml.prefix().toString().toLower();
    hasType = xml.attributes().hasAttribute("type");

    // Podcast detection: only flag itunes elements that are specific to actual
    // podcast feeds. Many non-podcast feeds (e.g. Substack blogs) include generic
    // itunes metadata like itunes:owner, itunes:author, and itunes:block.
    if (currentPrefix == "itunes") {
        if (currentTag == "duration" || currentTag == "episode"
                || currentTag == "episodetype" || currentTag == "season"
                || currentTag == "explicit" || currentTag == "category") {
            hasPodcastSignals = true;
        }
    }

    // Podcast detection: audio enclosures.
    if (currentTag == "enclosure") {
        QString type = xml.attributes().value("type").toString().toLower();
        if (type.startsWith("audio/")) {
            hasPodcastSignals = true;
        }
    }

    // Media RSS image extraction (media:thumbnail and media:content).
    if (currentItem && currentPrefix == "media") {
        if (currentTag == "thumbnail") {
            QString url = xml.attributes().value("url").toString();
            int width = xml.attributes().value("width").toString().toInt();
            if (!url.isEmpty() && (mediaImageURL.isEmpty() || width > mediaImageWidth)) {
                mediaImageURL = url;
                mediaImageWidth = width;
            }
        } else if (currentTag == "content") {
            QString type = xml.attributes().value("type").toString().toLower();
            if (type.startsWith("image/")) {
                QString url = xml.attributes().value("url").toString();
                int width = xml.attributes().value("width").toString().toInt();
                if (!url.isEmpty() && (mediaImageURL.isEmpty() || width > mediaImageWidth)) {
                    mediaImageURL = url;
                    mediaImageWidth = width;
                }
            }
        }
    }

    if (currentTag == "link" && urlHref.isEmpty() && xml.attributes().hasAttribute("href")) {
        // Used by atom feeds to grab the first link.
        urlHref = xml.attributes().value("href").toString();
    }
    
    // Add this new tag to our stack. :)
    tagStack.push(tagName);
}

void RSSAtomParser::elementEnd()
{
    if (!inAtomXHTML) {
        tagStack.pop(); // Pop our tag stack, we're through with this one!
    }
    
    QString tagName = xml.name().toString().toLower();
    
    if ((tagName == "item" || tagName == "entry") && !inAtomXHTML) {
        //qDebug() << "End element:" << xml.name().toString();
        if (!currentItem) {
            qCWarning(logFeedParser) << "Current item is null!";
            qCWarning(logFeedParser) << "Current title: " << title;
            qCWarning(logFeedParser) << "Xml element: " << tagName;
            return;
        }
        
        // Figure out which date to use.
        QString timestamp;
        if (!pubdate.trimmed().isEmpty()) {
            timestamp = pubdate;
        } else if (!lastbuilddate.trimmed().isEmpty()) {
            timestamp = lastbuilddate;
        } else if (!created.trimmed().isEmpty()) {
            timestamp = created;
        } else if (!date.trimmed().isEmpty()) {
            timestamp = date;
        } else if (!updated.trimmed().isEmpty()) {
            timestamp = updated;
        }
        
        // Determine the GUID.
        QString myGuid;
        if (!id.trimmed().isEmpty()) {
            myGuid = id.trimmed();
        } else if (!guid.trimmed().isEmpty()) {
            myGuid = guid.trimmed();
        } else if (!urlData.trimmed().isEmpty()) {
            myGuid = urlData.trimmed();
        } else {
            myGuid = urlHref.trimmed();
        }

        // Skip items without a GUID - malformed feed
        if (myGuid.isEmpty()) {
            qCWarning(logFeedParser) << "RSSAtomParser: RSS/Atom item missing GUID/URL, skipping item";
            qCWarning(logFeedParser) << "  Title:" << title;
            currentItem.reset();

            // Clear all strings for next item
            author = title = subtitle = content = QString();
            urlData = urlHref = guid = id = date = updated = timestamp = QString();
            return;
        }

        // Item space.
        currentItem->author = author;
        currentItem->title = stripEscapedCDATA(title);
        currentItem->description = stripEscapedCDATA(subtitle);
        currentItem->content = stripEscapedCDATA(content);

        currentItem->mediaImageURL = mediaImageURL;

        currentItem->url = urlData.isEmpty() ? QUrl(urlHref) : QUrl(urlData);
        currentItem->timestamp = FeedDateParser::dateFromFeedString(timestamp);
        currentItem->guid = myGuid;
        
        // Okay, give it up. :(
        if (!currentItem->timestamp.isValid()) {
            qCDebug(logFeedParser) << "Time string: " << timestamp;
            qCDebug(logFeedParser) << "invalid date!";
        }
        
        
        feed->items.append(currentItem);
        feed->isPodcast = feed->isPodcast || hasPodcastSignals;
        currentItem.reset();

        // Clear all strings.
        title = "";
        urlHref = "";
        urlData = "";
        subtitle = "";
        pubdate = "";
        lastbuilddate = "";
        created = "";
        date = "";
        updated = "";
        author = "";
        content = "";
        guid = "";
        id = "";
        mediaImageURL = "";
        mediaImageWidth = 0;
    } else if (tagName == "content" || tagName == "summary") {
        // Just accept that this is the end of one of these:
        // <contents type="xhtml">
        if (inAtomXHTML) {
            inAtomXHTML = false;
            tagStack.pop(); // We didn't do this earlier, you see.
        }
    }
    
    if (inAtomXHTML) {
        // SLORG we need to add this tag to the contents.
        
        // TODO: Is there a better way to do this?!
        content += "</" + xml.qualifiedName().toString() + ">";
    }
}

void RSSAtomParser::elementContents()
{
    if (inAtomXHTML) {
        // Atom sucks!
        content += xml.text().toString();
        
        return; // Early exit.
    }
    
    QString parentTag = getTagStackAt(1);
    if (parentTag == "item" || parentTag == "entry") {
        //
        // Inside a news item.
        //
        
        if (currentTag == "title" && currentPrefix == "") {
            title += xml.text().toString();
        } else if (currentTag == "link" && currentPrefix == "") {
            urlData += xml.text().toString();
        } else if ((currentTag == "description" || currentTag == "summary")
                   && currentPrefix == "") {
            subtitle += xml.text().toString();
        } else if (currentTag == "name"
                   || (currentTag == "creator" && currentPrefix == "dc")) {
            author += xml.text().toString();
        } else if (currentTag == "pubdate") {
            pubdate += xml.text().toString();
        } else if (currentTag == "lastbuilddate") {
            lastbuilddate += xml.text().toString();
        } else if (currentTag == "created") {
            created += xml.text().toString();
        } else if (currentTag == "updated") {
            updated += xml.text().toString();
        } else if (currentTag == "date") {
            date += xml.text().toString();
        } else if (currentTag == "guid") {
            guid += xml.text().toString();
        } else if (currentTag == "id") {
            id += xml.text().toString();
        } else if ((currentTag == "encoded" && currentPrefix == "content")
                   || (currentTag == "content" && hasType)) {
            content += xml.text().toString();
        }
    } else if (parentTag == "channel" || parentTag == "feed") {
        //
        // Top level items.
        //

        if (currentTag == "title" && currentPrefix == "") {
            title += xml.text().toString();
        } else if (currentTag == "link" && currentPrefix == "") {
            urlData += xml.text().toString();
        } else if ((currentTag == "description" || currentTag == "summary")
                   && currentPrefix == "") {
            subtitle += xml.text().toString();
        }
    }
}

void RSSAtomParser::resetParserVars()
{
    xml.clear();

    numItems = 0;
    currentTag = "";
    currentPrefix = "";
    urlHref = "";
    title = "";
    subtitle = "";
    content = "";
    pubdate = "";
    lastbuilddate = "";
    created = "";
    updated = "";
    date = "";
    author = "";
    guid = "";
    id = "";
    mediaImageURL = "";
    mediaImageWidth = 0;
    hasType = false;
    hasPodcastSignals = false;
    inAtomXHTML = false;
    tagStack.clear();
}

void RSSAtomParser::saveSummary()
{
    // Global space.
    feed->title = title;
    feed->subtitle = subtitle;
    feed->siteURL = urlData.isEmpty() ? QUrl(urlHref) : QUrl(urlData);
    feed->isPodcast = hasPodcastSignals;

    // Clear all local strings.
    title = "";
    urlHref = "";
    urlData = "";
    subtitle = "";
    pubdate = "";
    lastbuilddate = "";
    updated = "";
    date = "";
    author = "";
    content = "";
    guid = "";
    id = "";
    mediaImageURL = "";
    mediaImageWidth = 0;
}


QString RSSAtomParser::getTagStackAt(qint32 n)
{
    // n is from 0..size - 1
    if (tagStack.isEmpty() || (tagStack.size() - 1) < n) {
        return "";
    }
    
    return tagStack.at(tagStack.size() - 1 - n);
}
