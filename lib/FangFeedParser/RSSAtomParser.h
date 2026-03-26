#ifndef RSSATOMPARSER_H
#define RSSATOMPARSER_H

#include <memory>

#include <QString>
#include <QByteArray>
#include <QXmlStreamReader>
#include <QStack>

#include "RawFeed.h"

/*!
    \brief Synchronous RSS/Atom XML parser.

    Public API: call RSSAtomParser::parse(data) to get a RawFeed.
 */
class RSSAtomParser
{
public:
    // Parse a complete RSS/Atom XML document and return a RawFeed.
    static std::unique_ptr<RawFeed> parse(const QByteArray& data);

private:
    RSSAtomParser();
    ~RSSAtomParser();

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
        \return The nth value in the tag stack, or the empty string.
     */
    QString getTagStackAt(qint32 n);

    std::unique_ptr<RawFeed> feed;
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
