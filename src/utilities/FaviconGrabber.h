#ifndef FAVICONGRABBER_H
#define FAVICONGRABBER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>

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
    void onRequestFinished(QNetworkReply *reply);
    
private:
    int urlsToCheck;
    QNetworkAccessManager manager;
    QNetworkReply *currentReply;
    QList<QUrl> results;
};

#endif // FAVICONGRABBER_H
