#include "OPMLParser.h"

#include <QByteArray>

OPMLParser::OPMLParser(QObject *parent) :
    FangObject(parent),
    file(),
    feedList(),
    result(ParserInterface::IN_PROGRESS)
{
}

OPMLParser::~OPMLParser()
{
}

void OPMLParser::parseFile(QString filename)
{
    result = ParserInterface::IN_PROGRESS;
    QFile file(filename);
    
    // Open the file or die with an error.
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        result = ParserInterface::FILE_ERROR;
        qDebug() << "Couldn't read file: " << file.fileName();
        
        emit done();
        
        return;
    }
    
    // Read file!
    QByteArray data = file.readAll();
    xml.addData(data);
    
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            //qDebug() << "XML node: " << xml.name().toString() << " " << xml.prefix().toString();
            
            // Look for start of entries.
            QString name = xml.name().toString().toLower();
            
            // Start of outline.
            if ("outline" == name) {
                if (xml.attributes().hasAttribute("xmlUrl") &&
                        (xml.attributes().hasAttribute("title") || xml.attributes().hasAttribute("text") ))
                {
                    QString xmlUrl = xml.attributes().value("xmlUrl").toString();
                    QString htmlUrl = xml.attributes().value("htmlUrl").toString();
                    QString title;
                    
                    title = xml.attributes().value("title").toString();
                    if (title.isEmpty()) {
                        title = xml.attributes().value("text").toString();
                    }
                    
                    // Oh shit! We got one!
                    if (!xmlUrl.isEmpty() && !title.isEmpty()) {
                        RawFeed* feed = new RawFeed();
                        
                        feed->title   = title;
                        feed->url     = QUrl(xmlUrl);
                        feed->siteURL = QUrl(htmlUrl);
                        
                        feedList.append(feed);
                    }
                }
            }
        }
    }
    
    // Handle errors.
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError &&
            xml.error() != QXmlStreamReader::NotWellFormedError) {
        result = ParserInterface::PARSE_ERROR;
    } else if (feedList.size() > 0) {
        result = ParserInterface::OK;
    } else {
        result = ParserInterface::EMPTY_DOCUMENT;
    }
    
    //qDebug() << "Parser result (0 is good): " << result;
    
    emit done();
}
