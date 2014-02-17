#include "DropboxLoginOperation.h"

#include <QDebug>

DropboxLoginOperation::DropboxLoginOperation(OperationManager *parent, QString authCode) :
    DropboxOperation(IMMEDIATE, parent),
    authCode(authCode)
{
}

void DropboxLoginOperation::execute()
{
    //
    // At this point we're already partially logged in.  We just need to
    // hand the auth code back to the server and get a login token.
    //
    // Once we get the token we'll write it to the database.
    //
    
    appendPostQuery("code", authCode);
    appendPostQuery("grant_type", "authorization_code");
    
    doPost("oauth2/token");
}

void DropboxLoginOperation::onResponse(QJsonDocument& doc)
{
    // Json doc will contain something like this:
    // We only care about the access token.
    // {"access_token": "2KpF5HU1WC8AAAAAAAAAAXVIh5sWjCPQQ76ggWgUZX7CgP9QfJlC15RDC3X8LYc6", "token_type": "bearer", "uid": "178508400"}
    
    QJsonObject root = doc.object();
    QJsonValue value = root.value(QString("access_token"));
    
    if (!value.isString()) {
        reportError("No access token in OAuth2 handshake response");
        
        return;
    }
    
    // Yay, we did it!
    setAccessToken(value.toString());
    //qDebug() << "Access token: " << getAccessToken();
    
    QSqlQuery update(db());
    update.prepare("UPDATE DropboxConnectorTable SET authenticationToken = :authenticationToken WHERE id = 0");
    update.bindValue(":authenticationToken", getAccessToken());
    
    if (!update.exec()) {
        qDebug() << update.lastError().text();
        reportError("Dropbox login DB error!");
        
        return;
    }
    
    emit finished(this);
}
