#ifndef FEEDFETCHER_H
#define FEEDFETCHER_H

#include <QObject>

#include <QString>
#include <QNetworkReply>
#include <QThread>

#include "../network/FangNetworkAccessManager.h"
#include "FeedSource.h"

// Max number of HTTP redirects to prevent looping.
#define MAX_PARSER_REDIRECTS 10

/*!
    PaRSSes RSS/Atom feeds into RawFeed/RawNews objects.
 */
class FeedFetcher : public FeedSource
{
    Q_OBJECT
    
public:
    explicit FeedFetcher(QObject *parent = nullptr);
    explicit FeedFetcher(QNetworkAccessManager* networkManager, QObject *parent = nullptr);
    virtual ~FeedFetcher();
    
public slots:
    virtual void parse(const QUrl& url, bool noParseIfCached = false,
                       const QString& ifNoneMatch = QString(),
                       const QString& ifModifiedSince = QString()); // Override.
    
    // For testing purposes.
    void parseFile(const QString& filename);
    
    virtual ParseResult getResult(); // Override.
    virtual QNetworkReply::NetworkError getNetworkError() { return networkError; }
    virtual RawFeed* getFeed(); // Override.
    virtual inline QUrl getURL() { return finalFeedURL; } // Override.
    
    virtual bool isFromCache() { return fromCache; } // Override
    virtual QString responseEtag() { return respEtag; }
    virtual QString responseLastModified() { return respLastModified; }
    bool wasPermanentRedirect() const { return permanentRedirect; }
    
    // These are used internally.
signals:

    // Send buffered data to the worker thread for parsing.
    void triggerParse(QByteArray data);
    
protected slots:
    void readyRead();
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);
    void netFinished(QNetworkReply *reply);
    
    // When the worker thread thinks the document is complete, or an error occured.
    void workerDone(RawFeed* rawFeed);
    
private:
    void initParse(const QUrl& url = QUrl("")); // called prior to parse.
    void parseInternal(const QUrl& url, bool noParseIfCached,
                       const QString& ifNoneMatch = QString(),
                       const QString& ifModifiedSince = QString()); // used for redirects.
    
    RawFeed* feed;
    ParseResult result;
    QNetworkReply::NetworkError networkError;
    
    FangNetworkAccessManager manager;
    QNetworkAccessManager* activeManager;
    QNetworkReply *currentReply;
    QUrl finalFeedURL;
    QNetworkReply *redirectReply;
    
    bool fromCache;
    bool noParseIfCached;

    QString condIfNoneMatch;
    QString condIfModifiedSince;
    QString respEtag;
    QString respLastModified;

    int redirectAttempts;
    bool permanentRedirect;

    QByteArray rawData;
    QThread workerThread;
};

#endif // FEEDFETCHER_H
