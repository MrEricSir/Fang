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
    RSSAtomParser() = default;

    struct ParseState {
        int numItems = 0;
        bool hasPodcastSignals = false;
        bool inAtomXHTML = false;
        QStack<QString> tagStack;

        // Per-element (set fresh on each start element)
        QString currentTag;
        QString currentPrefix;
        bool hasType = false;

        // Per-item accumulated text (cleared between items)
        QString title;
        QString subtitle;
        QString content;
        QString author;
        QString urlHref;
        QString urlData;
        QString pubdate;
        QString lastbuilddate;
        QString created;
        QString updated;
        QString date;
        QString guid;
        QString id;
        QString mediaImageURL;
        int mediaImageWidth = 0;

        void clearItemFields();
    };

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

    // Call this when we have a summary.
    void saveSummary();

    /*!
        \return The nth value in the tag stack, or the empty string.
     */
    QString getTagStackAt(qint32 n);

    std::unique_ptr<RawFeed> feed;
    std::shared_ptr<RawNews> currentItem;
    bool isValid = false;
    QXmlStreamReader xml;
    ParseState state;
};

#endif // RSSATOMPARSER_H
