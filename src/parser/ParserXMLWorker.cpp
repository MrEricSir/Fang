#include "ParserXMLWorker.h"

ParserXMLWorker::ParserXMLWorker(QObject *parent) :
    FangObject(parent), feed(NULL), currentItem(NULL), isValid(false)
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
        xml.readNext();
        if (xml.isStartElement()) {
            // Add this new tag to our stack.
            tagStack.push(xml.name().toString().toLower());
            
            // Look for start of entries.
            //qDebug() << "XML node: " << xml.name().toString() << " " << xml.prefix().toString();
            if (xml.name() == "item" || xml.name() == "entry") {
                
                if (url.isEmpty())
                    url = xml.attributes().value("rss:about").toString();
                
                if (numItems == 0) {
                    // Oh, first item?  Assume we've seen the summary then.
                    
                    // Global space.
                    //
                    //feed->url = finalFeedURL;
                    //
                    feed->title = title;
                    feed->subtitle = subtitle;
                    feed->siteURL = QUrl(url);
                    
                    //qDebug() << "Title " << title;
                    
                    // Clear all local strings.
                    title = "";
                    url = "";
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
                
                currentItem = new RawNews(feed);
                numItems++;
            }
            
            currentTag = xml.name().toString().toLower();
            currentPrefix = xml.prefix().toString().toLower();
            hasType = xml.attributes().hasAttribute("type");
            
            if (currentTag == "link" && url.isEmpty() && xml.attributes().hasAttribute("href")) {
                // Used by atom feeds to grab the first link.
                url = xml.attributes().value("href").toString();
            }
        } else if (xml.isEndElement()) {
            tagStack.pop(); // Pop our tag stack, we're through with this one!
            
            if (xml.name() == "item" || xml.name() == "entry") {
                //qDebug() << "End element:" << xml.name().toString();
                if (currentItem == NULL) {
                    // Throw some kinda error, this can't happen.
                    qDebug() << "Current item is null!";
                    qDebug() << "Current title: " << title;
                    qDebug() << "Xml element: " << xml.name().toString();
                }
                
                // Figure out which date to use.
                QString timestamp;
                if (!pubdate.trimmed().isEmpty()) {
                    timestamp = pubdate;
                } else if (!lastbuilddate.trimmed().isEmpty()) {
                    timestamp = lastbuilddate;
                } else if (!updated.trimmed().isEmpty()) {
                    timestamp = updated;
                } else if (!date.trimmed().isEmpty()) {
                    timestamp = date;
                }
                
                // Determine the GUID.
                QString guid;
                if (!id.trimmed().isEmpty()) {
                    guid = id.trimmed();
                } else if (!guid.trimmed().isEmpty()) {
                    guid = guid.trimmed();
                } else {
                    guid = url.trimmed();
                }
                
                // Yes, we need a guid!
                Q_ASSERT(!guid.isEmpty());
                
                // Item space.
                currentItem->author = author;
                currentItem->title = title;
                currentItem->description = subtitle;
                currentItem->content = content;
                currentItem->url = QUrl(url);
                currentItem->timestamp = dateFromFeedString(timestamp);
                currentItem->guid = guid;
                
                // Okay, give it up. :(
                if (!currentItem->timestamp.isValid()) {
                    qDebug() << "Time string: " << timestamp;
                    qDebug() << "invalid date!";
                }
                
                
                feed->items.append(currentItem);
                currentItem = NULL;
                
                // Clear all strings.
                title = "";
                url = "";
                subtitle = "";
                pubdate = "";
                lastbuilddate = "";
                date = "";
                updated = "";
                author = "";
                content = "";
                guid = "";
                id = "";
            }

        } else if (xml.isCharacters() && !xml.isWhitespace()) {
            QString parentTag = getTagStackAt(1);
            if (parentTag == "item" || parentTag == "entry") {
                //
                // Inside a news item.
                //
                
                if (currentTag == "title" && currentPrefix == "") {
                    title += xml.text().toString();
                } else if (currentTag == "link" && currentPrefix == "") {
                    url += xml.text().toString();
                } else if (currentTag == "description" || currentTag == "summary") {
                    subtitle += xml.text().toString();
                } else if (currentTag == "name") {
                    author += xml.text().toString();
                } else if (currentTag == "pubdate") {
                    pubdate += xml.text().toString();
                } else if (currentTag == "lastbuilddate") {
                    lastbuilddate += xml.text().toString();
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
                    url += xml.text().toString();
                } else if (currentTag == "description" || currentTag == "summary") {
                    subtitle += xml.text().toString();
                }
            }
        }
    }
    
    // Standards need to be a bit lax for RSS.
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError &&
            xml.error() != QXmlStreamReader::NotWellFormedError) {
        isValid = false;
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
        emit done(NULL);
    }
    
}

QDateTime ParserXMLWorker::dateFromFeedString(const QString& _timestamp)
{
    QDateTime ret; // Defaults to invalid timestamp.
    
    // Come up with a few versions of the time stamp.
    QString timestamp = _timestamp.trimmed();
    QString timestamps[] = {
        timestamp,
        timestamp.left(timestamp.lastIndexOf(" ")).trimmed(),
        timestamp.left(timestamp.lastIndexOf(".")).trimmed(),
        timestamp.left(timestamp.lastIndexOf("-")).trimmed(),
        timestamp.left(timestamp.lastIndexOf("+")).trimmed(),
        
        0 // must be last
    };
    
    // Date time.  Comes in many (ugh) different formats.
    const QString dateFormats[] = { 
        // Most typical RSS format
        // Example: Tue, 02 Jul 2013 01:01:24 +0000 or Sun, 13 Oct 2013 19:15:29  PST
        "ddd, dd MMM yyyy hh:mm:ss",
        
        // Same as above, but with full months.
        "ddd, dd MMMM yyyy hh:mm:ss",
        
        // Also same as above, but with potentially single-digit days. (Used by "The Hindu".)
        "ddd, d MMM yyyy hh:mm:ss",
        
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
        
        
        0 // must be last!
    };
    
    // Iterate over date formats.
    int i = 0;
    while (!ret.isValid() && dateFormats[i] != 0) {
        const QString& format = dateFormats[i];
        
        // Try each format against each possible manipulated timestamp.
        int j = 0;
        while (!ret.isValid() && timestamps[j] != 0) {
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
        //qDebug() << "Adj: " << sAdjustment;
        
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
    ret.setTimeSpec(Qt::UTC);
    
    return ret;
}

void ParserXMLWorker::resetParserVars()
{
    xml.clear();

    numItems = 0;
    currentTag = "";
    currentPrefix = "";
    url = "";
    title = "";
    subtitle = "";
    content = "";
    pubdate = "";
    lastbuilddate = "";
    updated = "";
    date = "";
    author = "";
    guid = "";
    id = "";
    hasType = false;
    tagStack.clear();
}

QString ParserXMLWorker::getTagStackAt(qint32 n)
{
    // n is from 0..size - 1
    if (tagStack.isEmpty() || (tagStack.size() - 1) < n)
        return "";
    
    return tagStack.at(tagStack.size() - 1 - n);
}
