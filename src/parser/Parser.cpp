#include "Parser.h"

#include <QThread>
#include <QDebug>

#include "../utilities/Utilities.h"

Parser::Parser(QObject *parent) :
    QObject(parent), checkFavicon(false), feed(NULL), result(OK), currentReply(NULL), redirectReply(NULL)
{
    // Enble cache.
    Utilities::addNetworkAccessManagerCache(&manager);
    
    // Connex0r teh siganls.
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
                  this, SLOT(netFinished(QNetworkReply*)));
}

void Parser::parse(const QUrl& url) {
    result = Parser::IN_PROGRESS;
    finalFeedURL = url;
    
    resetParserVars();
    
    // Allocate our items.
    feed = new RawFeed(this);
    currentItem = NULL;
    
    // in with the new
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    currentReply = manager.get(request);
    connect(currentReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
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
}

// Parsed in chunks -- NOT all in one go.
void Parser::parseXml() {
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
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
                currentItem->timestamp = Utilities::dateFromFeedString(timestamp);
                
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
            QString xmlString = xml.text().toString();//.toLower();
            if (currentTag == "title" && currentPrefix == "")
                title += xmlString;
            else if (currentTag == "link" && currentPrefix == "") {
                url += xmlString;
            } else if (currentTag == "description" || currentTag == "summary")
                subtitle += xmlString;
            else if (currentTag == "name")
                author += xmlString;
            else if (currentTag == "pubdate" || currentTag == "lastbuilddate" 
                     || currentTag == "updated")
                timestamp += xmlString;
            else if ((currentTag == "encoded" && currentPrefix == "content")
                     || (currentTag == "content" && hasType))
                content += xmlString;
        }
    }
    
    // Standards need to be a bit lax for RSS.
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError &&
            xml.error() != QXmlStreamReader::NotWellFormedError) {
        result = Parser::PARSE_ERROR;
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
        emit finished();
    }
}

void Parser::error(QNetworkReply::NetworkError ne){
    qDebug() << "Error!!!!! " << ne;
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
    
    result = Parser::NETWORK_ERROR;
    emit finished();
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
        emit finished();
    } else {
        // What we found must not have been an RSS/Atom feed.
        result = Parser::PARSE_ERROR;
        emit finished();
    }
}

