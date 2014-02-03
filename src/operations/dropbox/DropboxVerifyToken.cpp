#include "DropboxVerifyToken.h"

DropboxVerifyToken::DropboxVerifyToken(QObject *parent) :
    DropboxOperation(IMMEDIATE, parent)
{
}

void DropboxVerifyToken::execute()
{
    if (getAccessToken().isEmpty()) {
        // Let's see if we have one on file.
        
        QSqlQuery query(db());
        query.prepare("SELECT authenticationToken FROM DropboxConnectorTable WHERE id = 0");
        
        if (!query.exec() || !query.next()) {
            reportError("DB error reading auth token from the dropbox table");
           
           return;
        }
        
        // We got something, so set it.
        setAccessToken(query.value(0).toString());
    }
    
    if (getAccessToken().isEmpty()) {
        reportError("Can't log in to Dropbox, 'cause we got no token on file.");
        
        return;
    }
    
    // Basically this does an "ls"
    doGet("datastores/list_datastores");
}

void DropboxVerifyToken::onResponse(QJsonDocument &doc)
{
    // We don't care about the result, we really just care about whether or
    // not it was valid.  So we'll just check for the token.
    QJsonObject root = doc.object();
    QJsonValue value = root.value(QString("token"));
    
    if (!value.isString()) {
        reportError("Didn't get a valid response from Dropbox.  HMMM.");
        
        return;
    }
    
    emit finished(this);
}

