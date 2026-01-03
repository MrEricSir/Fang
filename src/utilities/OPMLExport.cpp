#include "OPMLExport.h"

#include <QXmlStreamWriter>
#include <QDateTime>
#include <QFile>
#include "../models/FeedItem.h"

OPMLExport::OPMLExport()
{
}

bool OPMLExport::save(const QString &sFile, ListModel* feedList)
{
    QFile file(sFile);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file: " << sFile << " error code: " << file.errorString();
        return false;
    }
    
    // Create date time string.
    // Format example: Tue, 18 Mar 2014 04:09:51 GMT
    QDateTime dateTime = QDateTime::currentDateTime();
    dateTime = dateTime.toUTC();
    QString dateTimeString = dateTime.toString("ddd, dd MMM yyyy hh:mm:ss") + " GMT";
    
    // Start the document.
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    
    // Main element.
    // <opml version="1.1">
    xmlWriter.writeStartElement("opml");
    xmlWriter.writeAttribute("version", "1.1");
    
    // Head element.
    //<head>
    //  <title>blah</title>
    //  <dateModified>Tue, 18 Mar 2014 04:09:51 GMT</dateModified>
    //</head>
    xmlWriter.writeStartElement("head");
    xmlWriter.writeTextElement("title", "Fang OPML export");
    xmlWriter.writeTextElement("dateModified", dateTimeString);
    xmlWriter.writeEndElement();
    
    // Start body.
    xmlWriter.writeStartElement("body");
    
    //
    // Here's where we write the feed list!
    //
    // <outline text="MrEricSir.com" title="MrEricSir.com" type="rss" xmlUrl="http://www.mrericsir.com/blog/feed/" htmlUrl="http://www.mrericsir.com/blog"/>
    for (int i = 1; i < feedList->count(); i++) {
        FeedItem* feedItem = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feedItem != nullptr);
        
        xmlWriter.writeStartElement("outline");
        
        xmlWriter.writeAttribute("text", feedItem->getTitle());
        xmlWriter.writeAttribute("title", feedItem->getTitle());
        xmlWriter.writeAttribute("type", "rss");
        xmlWriter.writeAttribute("xmlUrl", feedItem->getURL().toString());
        if (feedItem->getSiteURL().isValid()) {
            xmlWriter.writeAttribute("htmlUrl", feedItem->getSiteURL().toString());
        }
        
        xmlWriter.writeEndElement();
    }
    
    
    // End body element.
    xmlWriter.writeEndElement();
    
    // End main element.
    xmlWriter.writeEndElement();
    
    // Finish 'er up.
    xmlWriter.writeEndDocument();
    file.close();

    return true;
}
