#ifndef SIMPLEHTTPDOWNLOADER_H
#define SIMPLEHTTPDOWNLOADER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

#include "../FangObject.h"
#include "../network/FangNetworkAccessManager.h"
#include "../FangObject.h"

// Fang will bite you if you try too many HTML redirects.
#define MAX_REDIRECTS 10

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
    explicit SimpleHTTPDownloader(int timeoutMS = 5000, QObject *parent = nullptr, QNetworkAccessManager* networkManager = nullptr);
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

    // Load function used internally.
    void loadInternal(const QUrl &url);

    // Request is done!
    void onRequestFinished(QNetworkReply* reply);

    // Check on download progress.
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    // Oh lame, we got a timeout. :(
    void onTimeout();

private:
    QNetworkAccessManager* manager;
    bool ownsManager;
    int timeoutMS;
    QNetworkReply* currentReply;
    QTimer timeout;
    int redirectAttempts;
};

#endif // SIMPLEHTTPDOWNLOADER_H
