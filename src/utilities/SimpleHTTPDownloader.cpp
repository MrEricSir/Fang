#include "SimpleHTTPDownloader.h"

SimpleHTTPDownloader::SimpleHTTPDownloader(int timeoutMS, QObject *parent, QNetworkAccessManager* networkManager) :
    FangObject(parent),
    manager(networkManager ? networkManager : new FangNetworkAccessManager(this)),
    ownsManager(networkManager == nullptr),
    timeoutMS(timeoutMS),
    currentReply(nullptr),
    redirectAttempts(0)
{
    timeout.setSingleShot(true);

    // Signals!
    connect(manager, &QNetworkAccessManager::finished, this, &SimpleHTTPDownloader::onRequestFinished);
    connect(&timeout, &QTimer::timeout, this, &SimpleHTTPDownloader::onTimeout);
}

SimpleHTTPDownloader::~SimpleHTTPDownloader()
{
    if (currentReply) {
        currentReply->deleteLater();
        currentReply = nullptr;
    }
}

void SimpleHTTPDownloader::load(const QUrl &url)
{
    // Reset our counter.
    redirectAttempts = 0;

    loadInternal(url);
}

void SimpleHTTPDownloader::loadInternal(const QUrl &url)
{
    // Delete last reply if needed.
    if (currentReply) {
        currentReply->deleteLater();
        currentReply = nullptr;
    }

    if (url.isRelative()) {
        emit error("Relative URLs are not allowed");
    } else {
        QNetworkRequest request(url);
        currentReply = manager->get(request);
        connect(currentReply, &QNetworkReply::downloadProgress, this,
                &SimpleHTTPDownloader::onDownloadProgress);

        // Reset timer
        timeout.setInterval(timeoutMS);
    }
}

void SimpleHTTPDownloader::onRequestFinished(QNetworkReply *reply)
{
    // Only process replies that belong to us
    if (reply != currentReply) {
        return;
    }

    // Check for errors.
    if (reply->error() != QNetworkReply::NoError) {
        QString netError = "SimpleHTTPDownloader error: " + reply->errorString();
        qDebug() << netError;
        emit error(netError);

        return;
    }

    // Handle HTTP redirects.
    QVariant redirectVariant = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!redirectVariant.isNull()) {
        if (redirectAttempts > MAX_REDIRECTS) {
            emit error("Maximum HTTP redirects");

            return;
        }

        // Bump counter and call our internal load method that doesn't reset it.
        redirectAttempts++;

        QUrl redirectURL = redirectVariant.toUrl();
        loadInternal(redirectURL);

        return;
    }

    // We're done!
    emit finished(reply->readAll());
}

void SimpleHTTPDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    Q_UNUSED(bytesReceived);
    Q_UNUSED(bytesTotal);

    // Reset timer
    timeout.setInterval(timeoutMS);
}

void SimpleHTTPDownloader::onTimeout()
{
    if (currentReply) {
        currentReply->abort();
        currentReply->deleteLater();
        currentReply = nullptr;

        emit error("SimpleHTTPDownloader timeout!");
    }
}

