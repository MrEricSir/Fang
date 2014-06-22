#ifndef PARSERXMLWORKER_H
#define PARSERXMLWORKER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QQueue>
#include <QXmlStreamReader>
#include <QStack>

#include "RawFeed.h"

/**
 * @brief Does the icky string work for RSS/Atom parking.  Intended
 * to be used as a background operation.
 * 
 */
class ParserXMLWorker : public QObject
{
    Q_OBJECT
public:
    explicit ParserXMLWorker(QObject *parent = 0);
    virtual ~ParserXMLWorker();
    
signals:
    
    // Returns the finished feed, or null.
    void done(RawFeed* feed);
    
public slots:
    
    // Call this prior to adding XML.
    void documentStart();
    
    // Call this when you're done adding XML.
    void documentEnd();
    
    // Add a blurb of XML to parse.
    void addXML(QByteArray data);
    
private:
    /**
     * @brief This is where the magic (you know, the parsing) really happens.
     * @param data
     */
    void parseXml(QByteArray data);
    
    void resetParserVars();
    
    /**
     * @brief Attempts to convert an unreliable RSS/Atom timestamp string into a real timestamp.
     * @param timestamp
     * @return 
     */
    static QDateTime dateFromFeedString(const QString &_timestamp);
    
    /**
     * @return The nth value in the tag stack, or the empty string.
     */
    QString getTagStackAt(qint32 n);
    
    RawFeed* feed;
    RawNews* currentItem;
    bool isValid;
    
    QXmlStreamReader xml;
    
    // Parser vars
    int numItems;
    QString currentTag;
    QString currentPrefix;
    QString url;
    QString title;
    QString subtitle;
    QString content;
    QString timestamp;
    QString author;
    bool hasType;
    QStack<QString> tagStack;
    //
};

#endif // PARSERXMLWORKER_H
