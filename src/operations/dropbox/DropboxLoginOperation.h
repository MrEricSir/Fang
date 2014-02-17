#ifndef DROPBOXLOGINOPERATION_H
#define DROPBOXLOGINOPERATION_H

#include "DropboxOperation.h"
#include <QString>
#include <QObject>

/**
 * @brief Given the raw auth code from the OAuth2 login process, this finishes the handshake,
 * returns the login token, and saves it to the database.
 * 
 * TODO: Implement safe keystore.
 */
class DropboxLoginOperation : public DropboxOperation
{
    Q_OBJECT
public:
    explicit DropboxLoginOperation(OperationManager *parent, QString authCode);
    
signals:
    
public slots:
    virtual void execute();
    
protected slots:
    virtual void onResponse(QJsonDocument& doc);
    
private:
    QString authCode;
};

#endif // DROPBOXLOGINOPERATION_H
