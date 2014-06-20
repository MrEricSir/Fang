#include "Parser.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include "../utilities/NetworkUtilities.h"

Parser::Parser(QObject *parent) :
    ParserInterface(parent), checkFavicon(false), feed(NULL), result(OK), currentReply(NULL), redirectReply(NULL), fromCache(false), noParseIfCached(false)
{
    NetworkUtilities::addCache(&manager);
    
    // Connex0r teh siganls.
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(netFinished(QNetworkReply*)));
}

QDateTime Parser::dateFromFeedString(const QString& _timestamp)
{
    QDateTime ret; // Defaults to invalid timestamp.
    
    // Come up with a few versions of the time stamp.
    QString timestamp = _timestamp.trimmed();
    QString timestamps[] = {
        timestamp,
        timestamp.left(timestamp.lastIndexOf(" ")),
        timestamp.left(timestamp.lastIndexOf(".")),
        timestamp.left(timestamp.lastIndexOf("-")),
        timestamp.left(timestamp.lastIndexOf("+")),
        
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

void Parser::parse(const QUrl& url, bool noParseIfCached) {
    initParse(url);
    
    this->noParseIfCached = noParseIfCached;
    
    // in with the new
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
    // Use the cache, luke.
    NetworkUtilities::useCache(&request);
    
    currentReply = manager.get(request);
    connect(currentReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void Parser::parseFile(const QString &filename)
{
    initParse();
    
    QFile file(filename);
    
    QFileInfo fileInfo(filename);
    //qDebug() << "Filename: " << fileInfo.absoluteFilePath();
    
    Q_ASSERT(file.exists());
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Q_ASSERT(false);
        return;
    }
    
    QByteArray data = file.readAll();
    xml.addData(data);
    parseXml();
    
    // We have to do this manually for files.
    
    if (feed->items.size() > 0)
        result = Parser::OK;
    
    emit done();
}

void Parser::resetParserVars() {
    xml.clear();

    numItems = 0;
    currentTag = "";
    currentPrefix = "";
    url = "";
    title = "";
    subtitle = "";
    content = "";
    timestamp = "";
    author = "";
    hasType = false;
    tagStack.clear();
}

QString Parser::getTagStackAt(qint32 n)
{
    // n is from 0..size - 1
    if (tagStack.isEmpty() || (tagStack.size() - 1) < n)
        return "";
    
    return tagStack.at(tagStack.size() - 1 - n);
}

// Parsed in chunks -- NOT all in one go.
void Parser::parseXml() {
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
                    feed->url = finalFeedURL;
                    feed->title = title;
                    feed->subtitle = subtitle;
                    feed->siteURL = QUrl(url);
                    
                    //qDebug() << "Title " << title;
                    
                    // Clear all strings.
                    title = "";
                    url = "";
                    subtitle = "";
                    timestamp = "";
                    author = "";
                    content = "";
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
                // Item space.
                currentItem->author = author;
                currentItem->title = title;
                currentItem->description = subtitle;
                currentItem->content = content;
                currentItem->url = QUrl(url);
                currentItem->timestamp = dateFromFeedString(timestamp);
                
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
                timestamp = "";
                author = "";
                content = "";
            }

        } else if (xml.isCharacters() && !xml.isWhitespace()) {
            if (currentTag == "title" && currentPrefix == "" && getTagStackAt(1) != "image") {
                title += xml.text().toString();
                //qDebug() << "Title: " << title << "  tagStack top: " << getTagStackAt(0) << " " << getTagStackAt(1);
            } else if (currentTag == "link" && currentPrefix == "" && getTagStackAt(1) != "image") {
                url += xml.text().toString();
            } else if (currentTag == "description" || currentTag == "summary") {
                subtitle += xml.text().toString();
            } else if (currentTag == "name") {
                author += xml.text().toString();
            } else if (currentTag == "pubdate" || currentTag == "lastbuilddate" 
                     || currentTag == "updated" || currentTag == "date") {
                timestamp += xml.text().toString();
            } else if ((currentTag == "encoded" && currentPrefix == "content")
                     || (currentTag == "content" && hasType)) {
                content += xml.text().toString();
            }
        }
    }
    
    // Standards need to be a bit lax for RSS.
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError &&
            xml.error() != QXmlStreamReader::NotWellFormedError) {
        result = Parser::PARSE_ERROR;
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
        emit done();
    }
}

void Parser::error(QNetworkReply::NetworkError ne){
    Q_UNUSED(ne);
    //qDebug() << "Error!!!!! " << ne << " " << currentReply->errorString();
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
    
    result = Parser::NETWORK_ERROR;
    emit done();
}


void Parser::readyRead() {
    int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) {
        QByteArray data = currentReply->readAll();
        xml.addData(data);
        parseXml();
    }
}

void Parser::metaDataChanged() {
    QUrl redirectionTarget = currentReply->attribute(
                QNetworkRequest::RedirectionTargetAttribute).toUrl();
    
    // TODO: prevent endless loooooping!!!
    if (redirectionTarget.isValid()) {
        qDebug() << "Redirect: " << redirectionTarget.toString();
        redirectReply = currentReply;
        parse(redirectionTarget, noParseIfCached);
    }
    
    if (currentReply->attribute(
                QNetworkRequest::SourceIsFromCacheAttribute).isValid()) {
        if (currentReply->attribute(
                    QNetworkRequest::SourceIsFromCacheAttribute).toBool()) {
            if (noParseIfCached) {
                // Early exit for cache.
                currentReply->disconnect(this);
                currentReply->deleteLater();
                currentReply = 0;
                
                result = Parser::OK;
                emit done();
                
                return;
            }
        }
    }
}

Parser::ParseResult Parser::getResult() {
    return result;
}

RawFeed* Parser::getFeed() {
    return result == Parser::OK ? feed : NULL;
}

void Parser::netFinished(QNetworkReply *reply)
{
    if (redirectReply == reply)
        return; // This was the previous redirect.
    
    if (result != Parser::IN_PROGRESS)
        return; // Already emitted a finished signal.
    
    // This means we saw... something.  Do a sanity check here to make sure
    // that what we found was an actual feed.
    if (feed->items.size() > 0 || feed->title != "") {
        feed->url = reply->url();
        
        result = Parser::OK;
        emit done();
    } else {
        // What we found must not have been an RSS/Atom feed.
        result = Parser::PARSE_ERROR;
        emit done();
    }
}

void Parser::initParse(const QUrl& url)
{
    result = Parser::IN_PROGRESS;
    finalFeedURL = url;
    
    resetParserVars();
    
    // Allocate our items.
    feed = new RawFeed();
    currentItem = NULL;
}
