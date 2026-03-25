#ifndef RSSATOMPARSER_H
#define RSSATOMPARSER_H

#include <QString>
#include <QByteArray>
#include <QQueue>
#include <QXmlStreamReader>
#include <QStack>

#include "RawFeed.h"

/*!
    \brief Synchronous RSS/Atom XML parser.

    Public API: call RSSAtomParser::parse(data) to get a RawFeed*.

    Internally uses a streaming XML reader via documentStart/addXML/documentEnd.
 */
class RSSAtomParser
{
public:
    // Parse a complete RSS/Atom XML document and return a RawFeed*.
    // Caller takes ownership of the returned pointer.
    static RawFeed* parse(const QByteArray& data);

private:
    RSSAtomParser();
    ~RSSAtomParser();

    RawFeed* takeFeed();

    // Call this prior to adding XML.
    void documentStart();

    // Call this when you're done adding XML.
    void documentEnd();

    // Add a blurb of XML to parse.
    void addXML(QByteArray data);

    /*!
        \brief Parse a start element, e.g. <b>
     */
    void elementStart();

    /*!
        \brief Parse an end element, e.g. </b>
     */
    void elementEnd();

    /*!
        \brief Parse the contents, e.g. <tag>contents goes here</tag>
     */
    void elementContents();

    void resetParserVars();

    // Call this when we have a summary.
    void saveSummary();

    /*!
        \brief Attempts to convert an unreliable RSS/Atom timestamp string into a real timestamp.
        \param timestamp
        \return
     */
    static QDateTime dateFromFeedString(const QString &_timestamp);

    /*!
        \brief QDateTime doesn't handle two-digit years well.  This method
        appends "20" before a two-digit year.

        Why?  Well, we don't want QtDateTime thinking it's 1914 (as of this writing.)

        \param timestamp
     */
    static void yearFix(QString& timestamp);

    /*!
        \brief If the timestamp starts with a weekday name, like "Thu" or "Thurs" or "Thursday"
               or whatever, this shaves it off.
        \param timestamp
     */
    static void shaveWeekdayName(QString& timestamp);

    /*!
        \brief Fixes some common mistakes with months in time strings.
        \param timestamp
     */
    static void monthMassager(QString& timestamp);

    /*!
        \return The nth value in the tag stack, or the empty string.
     */
    QString getTagStackAt(qint32 n);

    RawFeed* feed;
    std::shared_ptr<RawNews> currentItem;
    bool isValid;

    QXmlStreamReader xml;

    // Parser vars
    int numItems;
    QString currentTag;
    QString currentPrefix;
    QString urlHref;
    QString urlData;
    QString title;
    QString subtitle;
    QString content;
    QString pubdate;
    QString lastbuilddate;
    QString created;
    QString updated;
    QString date;
    QString author;
    bool hasType;
    bool hasPodcastSignals;
    bool inAtomXHTML;
    QString guid;
    QString id;
    QString mediaImageURL;
    int mediaImageWidth;
    QStack<QString> tagStack;
    //
};

#endif // RSSATOMPARSER_H
