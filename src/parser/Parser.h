#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>

#include "ParserInterface.h"
#include "ParserXMLWorker.h"

// PaRSSes RSS/Atom feeds into RawFeed/RawNews objects.
class Parser : public ParserInterface
{
    Q_OBJECT
    
public:
    explicit Parser(QObject *parent = 0);
    virtual ~Parser();
    
public slots:
    virtual void parse(const QUrl& url, bool noParseIfCached = false); // Override.
    
    // For testing purposes.
    void parseFile(const QString& filename);
    
    virtual ParseResult getResult(); // Override.
    virtual RawFeed* getFeed(); // Override.
    virtual inline QUrl getURL() { return finalFeedURL; } // Override.
    
    virtual bool isFromCache() { return fromCache; } // Override
    
    // These are used internally.
signals:
    
    // Call this prior to adding XML.
    void triggerDocStart();
    
    // Call this when you're done adding XML.
    void triggerDocEnd();
    
    // Add a blurb of XML to parse.
    void triggerAddXML(QByteArray data);
    
protected slots:
    void readyRead();
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);
    void netFinished(QNetworkReply *reply);
    
    // When the worker thread thinks the document is complete, or an error occured.
    void workerDone(RawFeed* rawFeed);
    
private:
    void initParse(const QUrl& url = QUrl("")); // called prior to parse.
    
    RawFeed* feed;
    ParseResult result;
    
    QNetworkAccessManager manager;
    QNetworkReply *currentReply;
    QUrl finalFeedURL;
    QNetworkReply *redirectReply;
    
    bool fromCache;
    bool noParseIfCached;
    
    QThread workerThread;
};

#endif // PARSER_H
