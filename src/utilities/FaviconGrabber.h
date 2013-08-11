#ifndef FAVICONGRABBER_H
#define FAVICONGRABBER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QWebPage>

#include "WebPageGrabber.h"

class FaviconGrabber : public QObject
{
    Q_OBJECT
public:
    explicit FaviconGrabber(QObject *parent = 0);
    
signals:
    /**
     * @brief Called when complete.
     * @param faviconUrl Either a valid favicon url, or an invalid URL.
     */
    void finished(const QUrl& faviconUrl);
    
public slots:
    
    /**
     * @brief Looks for a favicon for the given URL.
     * @param url
     */
    void find(const QUrl& url);
    
private slots:
    void checkUrl(const QUrl &url);
    
    /**
     * @brief Completion for root favicon check.
     * @param reply
     */
    void onRequestFinished(QNetworkReply *reply);
    
    /**
     * @brief Completion for HTML favicons.
     */
    void onWebGrabberReady(QWebPage* page);
    
    /**
     * @brief Determines if we've completed yet, figures out the result, and fires the finished signal.
     */
    void checkCompletion();
    
private:
    int urlsToCheck;
    QNetworkAccessManager manager;
    QNetworkReply *currentReply;
    QList<QUrl> results;
    WebPageGrabber webGrabber;
    QList<QUrl> webGrabberResults;
};

#endif // FAVICONGRABBER_H
