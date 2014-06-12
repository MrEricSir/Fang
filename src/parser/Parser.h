#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QStack>

#include "ParserInterface.h"

// PaRSSes RSS/Atom feeds into RawFeed/RawNews objects.
class Parser : public ParserInterface
{
    Q_OBJECT
    
public:
    explicit Parser(QObject *parent = 0);
    
    /**
     * @brief Attempts to convert an unreliable RSS/Atom timestamp string into a real timestamp.
     * @param timestamp
     * @return 
     */
    static QDateTime dateFromFeedString(const QString &_timestamp);
    
public slots:
    virtual void parse(const QUrl& url); // Override.
    
    // For testing purposes.
    void parseFile(const QString& filename);
    
    virtual ParseResult getResult(); // Override.
    virtual RawFeed* getFeed(); // Override.
    virtual inline QUrl getURL() { return finalFeedURL; } // Override.
    
protected slots:
    void readyRead();
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);
    void netFinished(QNetworkReply *reply);
    
private:
    void initParse(const QUrl& url = QUrl("")); // called prior to parse.
    void parseXml();
    void resetParserVars();
    
    /**
     * @return The nth value in the tag stack, or the empty string.
     */
    QString getTagStackAt(qint32 n);
    
    bool checkFavicon;
    RawFeed* feed;
    RawNews* currentItem;
    ParseResult result;
    
    QXmlStreamReader xml;

    QNetworkAccessManager manager;
    QNetworkReply *currentReply;
    QUrl finalFeedURL;
    QNetworkReply *redirectReply;
    
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

#endif // PARSER_H
