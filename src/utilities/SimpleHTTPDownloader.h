#ifndef SIMPLEHTTPDOWNLOADER_H
#define SIMPLEHTTPDOWNLOADER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

#include "../FangObject.h"
#include "../network/FangNetworkAccessManager.h"
#include "../FangObject.h"

/**
 * @brief The SimpleHTTPDownloader class downloads a web page.
 *
 * Supported features:
 *   Handles HTTP redirects
 *   Inactivity timeout
 *
 * Does not support:
 *   Streams or partial downloads
 */
class SimpleHTTPDownloader : public FangObject
{
    Q_OBJECT
public:
    explicit SimpleHTTPDownloader(int timeoutMS = 5000, QObject *parent = 0);
    ~SimpleHTTPDownloader();

signals:
    // Uh oh, an error!
    void error(QString);

    // We got some HTTP content!
    void finished(QByteArray);

public slots:

    // Fetches the web content.
    void load(const QUrl &url);

private slots:
    // Request is done!
    void onRequestFinished(QNetworkReply* reply);

    // Check on download progress.
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    // Oh lame, we got a timeout. :(
    void onTimeout();

private:
    FangNetworkAccessManager manager;
    int timeoutMS;
    QNetworkReply* currentReply;
    QTimer timeout;
};

#endif // SIMPLEHTTPDOWNLOADER_H
