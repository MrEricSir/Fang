#include "Parser.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include "../utilities/NetworkUtilities.h"

Parser::Parser(QObject *parent) :
    ParserInterface(parent), checkFavicon(false), feed(NULL), result(OK), currentReply(NULL), redirectReply(NULL)
{
    //NetworkUtilities::addNetworkAccessManagerCache(&manager);
    
    // Connex0r teh siganls.
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(netFinished(QNetworkReply*)));
}

QDateTime Parser::dateFromFeedString(const QString& _timestamp)
{
    QDateTime ret; // Defaults to invalid timestamp.
    
    // Come up with a few versions of the time stamp.
    QString timestamp = _timestamp.trimmed();
    QString whiteStrippedTimestamp = timestamp.left(timestamp.trimmed().lastIndexOf(" "));
    QString dotStrippedTimestamp = timestamp.left(timestamp.trimmed().lastIndexOf("."));
    
    // Date time.  Comes in many (ugh) different formats.
    const int dateFormatLength = 4;
    const QString dateFormats[] = { 
        // Most typical RSS format
        // Example: Tue, 02 Jul 2013 01:01:24 +0000 or Sun, 13 Oct 2013 19:15:29  PST
        "ddd, dd MMM yyyy hh:mm:ss",
        
        // Same as above, but with full months.
        "ddd, dd MMMM yyyy hh:mm:ss",
        
        // RFC 3339, normally used by Atom.
        // Example: 2013-08-07T16:47:54Z
        "yyyy-MM-ddThh:mm:ssZ",
        
        // Format used by some Chinese site.
        // Example: 2014-02-27 08:26:16.995
        "yyyy-MM-dd hh:mm:ss"
    };
    
    int i = 0;
    while (!ret.isValid() && i < dateFormatLength) {
        const QString& format = dateFormats[i];
        
        // Try each type of manicured timestamp against this format.
        ret = QDateTime::fromString(timestamp, format); 
        
        if (!ret.isValid())
            ret = QDateTime::fromString(whiteStrippedTimestamp, format); 
        
        if (!ret.isValid())
            ret = QDateTime::fromString(dotStrippedTimestamp, format); 
        
        i++;
    }
    
    // All times are (supposedly) in UTC.
    ret.setTimeSpec(Qt::UTC);
    
    return ret;
}

void Parser::parse(const QUrl& url) {
    initParse();
    
    // in with the new
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
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
            if (currentTag == "title" && currentPrefix == "" && (getTagStackAt(1) != "image")) {
                title += xml.text().toString();
                //qDebug() << "Title: " << title << "  tagStack top: " << getTagStackAt(0) << " " << getTagStackAt(1);
            } else if (currentTag == "link" && currentPrefix == "") {
                url += xml.text().toString();
            } else if (currentTag == "description" || currentTag == "summary") {
                subtitle += xml.text().toString();
            } else if (currentTag == "name") {
                author += xml.text().toString();
            } else if (currentTag == "pubdate" || currentTag == "lastbuilddate" 
                     || currentTag == "updated") {
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
    qDebug() << "Error!!!!! " << ne << " " << currentReply->errorString();
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
        parse(redirectionTarget);
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

void Parser::initParse()
{
    result = Parser::IN_PROGRESS;
    finalFeedURL = url;
    
    resetParserVars();
    
    // Allocate our items.
    feed = new RawFeed();
    currentItem = NULL;
}
