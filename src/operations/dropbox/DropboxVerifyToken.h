#ifndef DROPBOXVERIFYTOKEN_H
#define DROPBOXVERIFYTOKEN_H

#include "DropboxOperation.h"

/**
 * @brief Tries logging in to Dropbox.  If there's no token, it's invalid, or we're offline, 
 * we emit an error.
 * 
 * TODO: Network manager to check if we're online or not
 */
class DropboxVerifyToken : public DropboxOperation
{
    Q_OBJECT
public:
    DropboxVerifyToken(OperationManager *parent);
    
public slots:
    virtual void execute();
    
protected slots:
    virtual void onResponse(QJsonDocument& doc);
};

#endif // DROPBOXVERIFYTOKEN_H
