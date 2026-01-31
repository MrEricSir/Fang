#include "ParserXMLWorker.h"
#include <QtCore/qtimezone.h>
#include "../utilities/ErrorHandling.h"
#include "../utilities/FangLogging.h"

ParserXMLWorker::ParserXMLWorker(QObject *parent) :
    FangObject(parent), feed(nullptr), currentItem(nullptr), isValid(false), inAtomXHTML(false)
{
}

ParserXMLWorker::~ParserXMLWorker()
{
    delete feed;
}

void ParserXMLWorker::documentStart()
{
    // Make a new feed!  Yay!
    delete feed;
    feed = new RawFeed();
    isValid = true;
    
    resetParserVars();
}

void ParserXMLWorker::documentEnd()
{
    if (isValid) {
        if (feed->items.size() == 0) {
            // Edge case: we typically save the summary when we encounter the first item. This
            // handles the case where they were no items but we might have a summary.
            saveSummary();
        }
        emit done(feed);
    }
    
    // If it's not valid, we already emitted a signal.
}

void ParserXMLWorker::addXML(QByteArray data)
{
    if (!isValid) {
        return;
    }
    
    xml.addData(data);
    
    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();
        
        if (xml.isStartElement()) {
            elementStart();
        } else if (xml.isEndElement()) {
            elementEnd();
        } else if (xml.isCharacters() && !xml.isWhitespace()) {
            elementContents();
        }
    }
    
    // Standards need to be a bit lax for RSS.
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError &&
            xml.error() != QXmlStreamReader::NotWellFormedError) {
        isValid = false;
        qCWarning(logParser) << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
        emit done(nullptr);
    }
    
}


void ParserXMLWorker::elementStart()
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
        
        currentItem = new RawNews(feed);
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
    
    if (currentTag == "link" && urlHref.isEmpty() && xml.attributes().hasAttribute("href")) {
        // Used by atom feeds to grab the first link.
        urlHref = xml.attributes().value("href").toString();
    }
    
    // Add this new tag to our stack. :)
    tagStack.push(tagName);
}

void ParserXMLWorker::elementEnd()
{
    if (!inAtomXHTML) {
        tagStack.pop(); // Pop our tag stack, we're through with this one!
    }
    
    QString tagName = xml.name().toString().toLower();
    
    if ((tagName == "item" || tagName == "entry") && !inAtomXHTML) {
        //qDebug() << "End element:" << xml.name().toString();
        if (currentItem == nullptr) {
            // Throw some kinda error, this can't happen.
            qCDebug(logParser) << "Current item is null!";
            qCDebug(logParser) << "Current title: " << title;
            qCDebug(logParser) << "Xml element: " << tagName;
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
            qCWarning(logParser) << "ParserXMLWorker: RSS/Atom item missing GUID/URL, skipping item";
            qCWarning(logParser) << "  Title:" << title;
            delete currentItem;
            currentItem = nullptr;

            // Clear all strings for next item
            author = title = subtitle = content = QString();
            urlData = urlHref = guid = id = date = updated = timestamp = QString();
            return;
        }

        // Item space.
        currentItem->author = author;
        currentItem->title = title;
        currentItem->description = subtitle;
        currentItem->content = content;
        currentItem->url = urlData.isEmpty() ? QUrl(urlHref) : QUrl(urlData);
        currentItem->timestamp = dateFromFeedString(timestamp);
        currentItem->guid = myGuid;
        
        // Okay, give it up. :(
        if (!currentItem->timestamp.isValid()) {
            qCDebug(logParser) << "Time string: " << timestamp;
            qCDebug(logParser) << "invalid date!";
        }
        
        
        feed->items.append(currentItem);
        currentItem = nullptr;
        
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

void ParserXMLWorker::elementContents()
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
        } else if (currentTag == "description" || currentTag == "summary") {
            subtitle += xml.text().toString();
        } else if (currentTag == "name") {
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
        } else if (currentTag == "description" || currentTag == "summary") {
            subtitle += xml.text().toString();
        }
    }
}

void ParserXMLWorker::resetParserVars()
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
    hasType = false;
    inAtomXHTML = false;
    tagStack.clear();
}

void ParserXMLWorker::saveSummary()
{
    // Global space.
    feed->title = title;
    feed->subtitle = subtitle;
    feed->siteURL = urlData.isEmpty() ? QUrl(urlHref) : QUrl(urlData);

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
}


QDateTime ParserXMLWorker::dateFromFeedString(const QString& _timestamp)
{
    QDateTime ret; // Defaults to invalid timestamp.
    
    // Come up with a few versions of the time stamp.
    QString timestamp = _timestamp.trimmed();
    yearFix(timestamp); //IMPORTANT: Must be done *before* weekday name is shaved.
    shaveWeekdayName(timestamp);
    monthMassager(timestamp);
    QString timestamps[] = {
        timestamp,
        timestamp.left(timestamp.lastIndexOf(" ")).trimmed(),
        timestamp.left(timestamp.lastIndexOf(".")).trimmed(),
        timestamp.left(timestamp.lastIndexOf("-")).trimmed(),
        timestamp.left(timestamp.lastIndexOf("+")).trimmed(),
        
        "" // must be last
    };
    
    // Date time.  Comes in many (ugh) different formats.
    const QString dateFormats[] = { 
        // Most typical RSS format
        // Example: Tue, 02 Jul 2013 01:01:24 +0000 or Sun, 13 Oct 2013 19:15:29  PST
        // But Fang shaves off weekday names (see above), because they're useless and are often screwed up.
        "dd MMM yyyy hh:mm:ss",
        
        // One-digit minutes (yes, this happens.)
        "dd MMM yyyy hh:m:ss",
        
        // Same as above, but with full months.
        "dd MMMM yyyy hh:mm:ss",
        
        // Full month, one digit minutes.
        "dd MMMM yyyy hh:m:ss",
        
        // Also same as above, but with potentially single-digit days. (Used by "The Hindu".)
        "d MMM yyyy hh:mm:ss",
        
        // RFC 3339, normally used by Atom.
        // Example: 2013-08-07T16:47:54Z
        "yyyy-MM-ddThh:mm:ssZ",
        
        // Variant of the above without the trailing Z.
        // Example: 2012-05-30T19:46:42
        "yyyy-MM-ddThh:mm:ss",
        
        // Variant of the above without seconds OR a trailing Z.
        // Example: 2012-05-30T19:46
        "yyyy-MM-ddThh:mm",
        
        // Format used by some Chinese site.
        // Example: 2014-02-27 08:26:16.995
        "yyyy-MM-dd hh:mm:ss",
        
        // "Lokmat" uses this custom format.  I provide a single-spaced version for sanity's sake.
        // Example: 25-02-2014  01:08:10
        "dd-MM-yyyy  hh:mm:ss",
        "dd-MM-yyyy hh:mm:ss",
        
        
        "" // must be last!
    };
    
    // Iterate over date formats.
    int i = 0;
    while (!ret.isValid() && !dateFormats[i].isEmpty()) {
        const QString& format = dateFormats[i];
        
        // Try each format against each possible manipulated timestamp.
        int j = 0;
        while (!ret.isValid() && !timestamps[j].isEmpty()) {
            QString& ts = timestamps[j];
            ret = QDateTime::fromString(ts, format);
            
            j++;
        }
        
        i++;
    }
    
    // Check if there's a time-based adjustment and/or timezone.
    // For now we only look for time identifiers in the format of -hhmm or +hhmm
    //
    // TODO: Three-letter time zones. (TLAs like GMT, PST, etc.)
    //
    int lastPlus = timestamp.lastIndexOf("+");
    int lastMinus = timestamp.lastIndexOf("-");
    if (lastPlus > 3 || lastMinus > 3) {
        // We have a plus or a minus.
        int signPos = lastPlus > 3 ? lastPlus : lastMinus;
        QString sAdjustment = timestamp.right(timestamp.length() - signPos);
        sAdjustment = sAdjustment.trimmed();
        
        // Check for an hour/minute adjustment, in the format of -hhmm or +hhmm
        // OR in the format of -hh:mm or +hh:mm
        if ((sAdjustment.length() == 5 || sAdjustment.length() == 6) &&
                (sAdjustment.startsWith("+") || sAdjustment.startsWith("-"))) {
            int adjustment = 0; // Adjustment in minutes.
            bool containsCol = sAdjustment.contains(':');
            bool isNum = false;
            int hours = 0;
            int minutes = 0;
            
            QString sNumber = sAdjustment.right(containsCol ? 5 : 4); // Skip + or -
            // YES!  We've got an adjustment!
            hours = sNumber.left(2).toInt(&isNum);
            if (isNum)
                minutes = sNumber.right(2).toInt(&isNum);
            
            // Looks like we're good!
            if (isNum) {
                // Condense down to minutes.
                minutes += (hours * 60);
                adjustment = sAdjustment.startsWith("-") ? minutes : -minutes;
                
                // Add in our adjustment if we need it.
                ret = ret.addSecs(adjustment * 60 /* seconds */);
            }
        }
    }
    
    // All times are (supposedly) in UTC.
    ret.setTimeZone(QTimeZone::UTC);

    return ret;
}


void ParserXMLWorker::yearFix(QString& timestamp)
{
    // If the timestamp is something like this:
    // Tue, 02 Jul 13 [etc]
    // We want to make it something like this:
    // Tue, 02 Jul 2013 [etc]
    if (timestamp.length() == 0 || !timestamp[0].isLetter()) {
        return; // Early exit.
    }
    
    bool seenWeekday = false;
    bool seenDay = false;
    bool seenMonth = false;
    bool seenYear = false;
    bool hitSpace = true; // This controls whether or not we examine the character.
    int charsInYear = 0;
    for (int i = 0; i < timestamp.length(); i++) {
        if (hitSpace && (timestamp[i].isLetter() || timestamp[i] == ',')) {
            hitSpace = false; // reset
            
            if (!seenWeekday) {
                seenWeekday = true;
            } else if (!seenMonth) {
                seenMonth = true;
            }
        } else if (hitSpace && (timestamp[i].isDigit())) {
            hitSpace = false; // reset
            
            if (!seenDay) {
                seenDay = true;
            } else if (!seenYear) {
                seenYear = true;
            }
        } else if (timestamp[i].isSpace()) {
            if (seenYear) {
                // Here's where we find out if we can leave yet.
                if (charsInYear != 2) {
                    break; // Early exit!
                } else {
                    // Sigh... okay, now we have to back up and insert a "20".
                    // Currently we're here: [Tue, 02 Jul 13 ]
                    timestamp = timestamp.insert(i - 2, "20");
                    return; // YAY! WE DID IT!
                }
            } else {
                hitSpace = true;
            }
        }
        
        if (seenYear) {
            ++charsInYear;
        }
    }
}


void ParserXMLWorker::shaveWeekdayName(QString& timestamp)
{
    // NOTE:
    // By the time we've reached this method, the timestamp has
    // already been trimmed, and we've made sure the year has four digits.
    
    int comma = timestamp.indexOf(',');
    if (comma < 0) {
        return; // Early exit.
    }
    
    // Remove up to and including the comma itself.
    timestamp = timestamp.remove(0, comma + 1).trimmed();
}

void ParserXMLWorker::monthMassager(QString& timestamp)
{
    // Add new ones as they're encountered.
    timestamp = timestamp.replace("Sept ", "Sep ");
}


QString ParserXMLWorker::getTagStackAt(qint32 n)
{
    // n is from 0..size - 1
    if (tagStack.isEmpty() || (tagStack.size() - 1) < n)
        return "";
    
    return tagStack.at(tagStack.size() - 1 - n);
}
