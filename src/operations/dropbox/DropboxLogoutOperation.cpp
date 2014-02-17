#include "DropboxLogoutOperation.h"

DropboxLogoutOperation::DropboxLogoutOperation(OperationManager *parent) :
    DropboxOperation(IMMEDIATE, parent)
{
}

void DropboxLogoutOperation::execute()
{
    // Check if we're already logged out.
    if (getAccessToken().isEmpty()) {
        emit finished(this);
        return;
    }
    
    doGet("disable_access_token");
}

void DropboxLogoutOperation::onResponse(QJsonDocument &doc)
{
    Q_UNUSED(doc); // The empty document is expected.
    
    setAccessToken("");
    
    // So we're good?  Cool.  Delete the token locally as well.
    QSqlQuery update(db());
    update.prepare("UPDATE DropboxConnectorTable SET authenticationToken = '' WHERE id = 0");
    
    if (!update.exec()) {
        qDebug() << update.lastError().text();
        reportError("Dropbox logout DB error!");
        
        return;
    }
    
    emit finished(this);
}
