#include "DropboxOperation.h"

#include "../DropboxConstants.h"

#include <QUrlQuery>
#include <QDebug>

QString DropboxOperation::_token = "";

DropboxOperation::DropboxOperation(PriorityLevel priority, QObject *parent) :
    DBOperation(priority, parent),
    manager(),
    postData()
{
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(onNetworkFinished(QNetworkReply*)));
}

void DropboxOperation::appendPostQuery(const QString &key, const QString &value)
{
     postData.addQueryItem(key, value);
}

void DropboxOperation::doPost(QString queryString)
{
    QNetworkRequest req(QUrl("https://api.dropbox.com/1/" + queryString));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    
    if (!getAccessToken().isEmpty()) {
        // For most requests, we authenticate with the Oauth2 access token.
        QString headerData = "Bearer " + getAccessToken();
        req.setRawHeader("Authorization", headerData.toLocal8Bit());
    } else {
        // We don't have a token yet, so we must be logging in.  Sign the request using basic
        // HTTP authentication.
        QString concatenated = DROPBOX_CLIENT_CODE + QString(":") + DROPBOX_CLIENT_SECRET;
        QByteArray data = concatenated.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        req.setRawHeader("Authorization", headerData.toLocal8Bit());
    }
    
    qDebug() << "POST request " << req.url();
    qDebug() << "query string: " << postData.toString();
    
    getManager().post(req, postData.toString().toLocal8Bit());
}

void DropboxOperation::doGet(QString queryString)
{
    QNetworkRequest req(QUrl("https://api.dropbox.com/1/" + queryString));
    
    QString headerData = "Bearer " + getAccessToken();
    req.setRawHeader("Authorization", headerData.toLocal8Bit());
    
    qDebug() << "GET request " << req.url();
    
    getManager().get(req);
}

void DropboxOperation::onNetworkFinished(QNetworkReply *reply)
{
    QByteArray replyBuffer = reply->readAll();
    
    qDebug() << "Error? " << reply->errorString();
    qDebug() << replyBuffer;
    qDebug();
    
    if (reply->error() != QNetworkReply::NoError) {
        reportError(reply->errorString());
        
        return;
    }
    
    // Attempt to extract the document.
    
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(replyBuffer, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        // It happens.
        reportError("Json parse error: " + jsonError.errorString() + " offset: " + QString::number(jsonError.offset));
    } else {
        // Horay!
        onResponse(doc);
    }
}
