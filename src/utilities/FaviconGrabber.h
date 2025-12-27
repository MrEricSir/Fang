#ifndef FAVICONGRABBER_H
#define FAVICONGRABBER_H

#include <QObject>
#include <QUrl>
#include <QNetworkReply>
#include <QList>
#include <QPair>
#include <QImage>

#include "WebPageGrabber.h"
#include "SimpleStateMachine.h"
#include "../FangObject.h"
#include "../network/FangNetworkAccessManager.h"

class FaviconGrabber : public FangObject
{
    Q_OBJECT
    
private:
    
    enum FaviconGrabberState {
        START,           // Starts off our list by checking standard /favicon.* urls.
        WEB_GRABBER,     // Checks the webpage for links to favicons.
        CHECK_ICONS,     // Try downloading all of the icons.
        PICK_BEST,       // Determine which icon is best. (Emits finished() signal)
        GRAB_ERROR       // We're done, but there was a problemo.
    };
    
public:
    explicit FaviconGrabber(QObject *parent = nullptr, QNetworkAccessManager* networkManager = nullptr);
    
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
    
    // WEB_GRABBER
    void onWebGrabber();
    
    // CHECK_ICONS
    void onCheckIcons();
    
    // PICK_BEST
    void onPickBest();
    
    // ERROR
    void onError();
    
    /**
     * @brief Completion for CHECK_ICONS
     * @param reply
     */
    void onRequestFinished(QNetworkReply *reply);
    
    /**
     * @brief Completion for WEB_GRABBER
     */
    void onWebGrabberReady(QString* document);

    // Searches for icons in our XHTML doc.
    void findIcons(const QString& document);
    
private:
    SimpleStateMachine machine;
    QList<QUrl> urlsToCheck;
    int repliesWaiting;
    QList<QPair<QUrl, QImage> > imagesToCheck;
    QNetworkAccessManager* manager;
    bool ownsManager;
    WebPageGrabber webGrabber;
    QUrl location;
};

#endif // FAVICONGRABBER_H
