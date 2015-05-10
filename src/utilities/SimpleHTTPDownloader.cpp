#include "SimpleHTTPDownloader.h"

SimpleHTTPDownloader::SimpleHTTPDownloader(int timeoutMS, QObject *parent) :
    timeoutMS(timeoutMS), currentReply(NULL), FangObject(parent)
{
    timeout.setSingleShot(true);

    // Signals!
    connect(&manager, &FangNetworkAccessManager::finished, this, &SimpleHTTPDownloader::onRequestFinished);
    connect(&timeout, &QTimer::timeout, this, &SimpleHTTPDownloader::onTimeout);
}

SimpleHTTPDownloader::~SimpleHTTPDownloader()
{
    if (currentReply) {
        currentReply->deleteLater();
        currentReply = NULL;
    }
}

void SimpleHTTPDownloader::load(const QUrl &url)
{
    // Delete last reply if needed.
    if (currentReply) {
        currentReply->deleteLater();
        currentReply = NULL;
    }

    if (url.isRelative()) {
        emit error("Relative URLs are not allowed");
    } else {
        QNetworkRequest request(url);
        currentReply = manager.get(request);
        connect(currentReply, &QNetworkReply::downloadProgress, this,
                &SimpleHTTPDownloader::onDownloadProgress);

        // Reset timer
        timeout.setInterval(timeoutMS);
    }
}

void SimpleHTTPDownloader::onRequestFinished(QNetworkReply *reply)
{
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
        QUrl redirectURL = redirectVariant.toUrl();
        load(redirectURL);

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
        currentReply = NULL;

        emit error("SimpleHTTPDownloader timeout!");
    }
}

