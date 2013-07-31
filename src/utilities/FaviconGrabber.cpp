#include "FaviconGrabber.h"
#include <QDebug>
#include <QString>
#include <QStringList>

#include "Utilities.h"

FaviconGrabber::FaviconGrabber(QObject *parent) :
    QObject(parent),
    urlsToCheck(0),
    manager(),
    currentReply(NULL),
    results()
{
    // Caching!
    Utilities::addNetworkAccessManagerCache(&manager);
    
    // Signals!
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
}

void FaviconGrabber::find(const QUrl &url)
{
    results.clear(); // clear result list.
    
    QUrl host = Utilities::getHost(url);
    
    QStringList extensions;
    extensions << "ico" << "jpg" << "jpeg" << "png" << "gif";
    urlsToCheck = extensions.size();
    
    // Check each extension.
    foreach(QString ext, extensions) {
        QUrl toCheck(host);
        qDebug() << "Checking host: "<< toCheck.toString();
        toCheck.setPath("/favicon." + ext);
        qDebug() << "Checking URL: "<< toCheck.toString();
        checkUrl(toCheck);
    }
}

void FaviconGrabber::checkUrl(const QUrl &url)
{
    manager.get(QNetworkRequest(url));
}

void FaviconGrabber::onRequestFinished(QNetworkReply * reply)
{
    urlsToCheck--;
    if (!reply->error())
        results.append(QUrl(reply->url()));
    
    
    if (urlsToCheck == 0) {
        // We're done!  Just return the first URL (for now.)
        if (results.size() == 0) {
            emit finished(QUrl());
        } else {
            QUrl url = results.at(0);
            qDebug() << "Found favicon: " << url;
            emit finished(url);
        }
    }
    
}

