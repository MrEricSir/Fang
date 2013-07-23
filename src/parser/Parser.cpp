#include "Parser.h"

#include <QThread>
#include <QDebug>

Parser::Parser(QObject *parent) :
    QObject(parent), feed(NULL), result(OK), currentReply(NULL)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
                  this, SLOT(netFinished(QNetworkReply*)));
}

void Parser::parse(const QUrl& url) {
    result = Parser::OK;
    
    // in with the new shit
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    currentReply = manager.get(request);
    connect(currentReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));

    // Allocate our items.
    feed = new RawFeed(this);
    currentItem = NULL;
}

// Parsed in chunks -- NOT all in one go.
void Parser::parseXml() {
    // Static: MUST persist between calls!!!
    static int numItems = 0;
    static QString currentTag = "";
    static QString url = "";
    static QString title = "";
    static QString subtitle = "";
    static QString timestamp = "";
    static QString author = "";
    
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            // Look for start of entries.
            if (xml.name() == "item" || xml.name() == "entry") {
                qDebug() << "Start element:" << xml.name().toString();
                url = xml.attributes().value("rss:about").toString();
                
                if (numItems == 0) {
                    // Oh, first item?  Assume we've seen the summary then.
                    
                    // Global space.
                    feed->url = QUrl(url);
                    feed->title = title;
                    feed->subtitle = subtitle;
                    
                    qDebug() << "Title " << title;
                    
                    // Clear all strings.
                    title.clear();
                    url.clear();
                    subtitle.clear();
                    timestamp.clear();
                    author.clear();
                }
                
                currentItem = new RawNews(feed);
                numItems++;
            }
            
            currentTag = xml.name().toString();
        } else if (xml.isEndElement()) {
            if (xml.name() == "item" || xml.name() == "entry") {
                qDebug() << "End element:" << xml.name().toString();
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
                //currentItem->timestamp = QDateTime::fromString(timestamp);
                currentItem->url = QUrl(url);
                
                feed->items.append(currentItem);
                currentItem = NULL;
                
                // Clear all strings.
                title.clear();
                url.clear();
                subtitle.clear();
                timestamp.clear();
                author.clear();
            }

        } else if (xml.isCharacters() && !xml.isWhitespace()) {
            QString xmlString = xml.text().toString().toLower();
            if (currentTag == "title")
                title += xmlString;
            else if (currentTag == "link")
                url += xmlString;
            else if (currentTag == "description" || currentTag == "summary")
                subtitle += xmlString;
            else if (currentTag == "name")
                author = xmlString;
            else if (currentTag == "pubdate" || currentTag == "lastbuilddate" 
                     || currentTag == "updated")
                timestamp = xmlString;
        }
    }
    
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
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
    Q_UNUSED(reply);
    
    if (result == Parser::OK) {
        qDebug() << "Parse looked good, items = " << feed->items.size();
        emit finished();
    }
 }

