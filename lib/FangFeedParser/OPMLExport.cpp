#include "OPMLExport.h"
#include "FeedParserLogging.h"

#include <QXmlStreamWriter>
#include <QDateTime>
#include <QFile>

bool OPMLExport::save(const QString &sFile, const QList<RawFeed*>& feeds)
{
    QFile file(sFile);

    if (!file.open(QIODevice::WriteOnly)) {
        qCWarning(logFeedParser) << "Could not open file: " << sFile << " error code: " << file.errorString();
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
    for (const RawFeed* feed : feeds) {
        if (!feed) {
            continue;
        }

        xmlWriter.writeStartElement("outline");

        xmlWriter.writeAttribute("text", feed->title);
        xmlWriter.writeAttribute("title", feed->title);
        xmlWriter.writeAttribute("type", "rss");
        xmlWriter.writeAttribute("xmlUrl", feed->url.toString());
        if (feed->siteURL.isValid()) {
            xmlWriter.writeAttribute("htmlUrl", feed->siteURL.toString());
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
