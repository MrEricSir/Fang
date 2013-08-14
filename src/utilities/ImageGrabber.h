#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QObject>
#include <QImage>
#include <QNetworkAccessManager>
#include <QList>
#include <QUrl>
#include <QMap>

class ImageGrabber : public QObject
{
    Q_OBJECT
public:
    explicit ImageGrabber(QObject *parent = 0);
    
signals:
    /**
     * @brief Called when all images are found.
     */
    void finished();
    
public slots:
    
    /**
     * @brief Fetch a group of remote images.
     * @param urls
     */
    void fetchUrls(const QList<QUrl> &urls);
    
    /**
     * @brief Fetch a remote image.
     * @param url
     */
    void fetchUrl(const QUrl &url);
    
    inline QMap<QUrl, QImage>* getResults() {  return &results; }
    
private slots:
    void onRequestFinished(QNetworkReply *reply);
    
    void checkCompletion();
    
    void checkUrl(const QUrl &url);
    
private:
    QNetworkAccessManager manager;
    QList<QUrl> urlsToCheck;
    QMap<QUrl, QImage> results;
};

#endif // IMAGEGRABBER_H
