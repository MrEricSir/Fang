#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QUrl>

#include "RawFeed.h"
#include "RawNews.h"

#include "../utilities/FaviconGrabber.h"

// PaRSSes RSS/Atom feeds into RawFeed/RawNews objects.
class Parser : public QObject
{
    Q_OBJECT
    
public:
    enum ParseResult { OK, NETWORK_ERROR, PARSE_ERROR, IN_PROGRESS };
    
    explicit Parser(QObject *parent = 0);
    
signals:
    // Call getResult() and getFeed() now, yo!
    void finished();
    
public slots:
    void parse(const QUrl& url, bool checkFavicon = false);
    
    ParseResult getResult();
    RawFeed* getFeed();
    inline QUrl getURL() { return finalFeedURL; }
    
protected slots:
    void readyRead();
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);
    void netFinished(QNetworkReply *reply);
    void onFaviconFinished(const QUrl& url);
    
private:
    void parseXml();
    void resetParserVars();
    
    bool checkFavicon;
    RawFeed* feed;
    RawNews* currentItem;
    ParseResult result;
    FaviconGrabber favicon;
    
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
    //
};

#endif // PARSER_H
