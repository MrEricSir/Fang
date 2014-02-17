#ifndef DROPBOXSTARTUPOPERATION_H
#define DROPBOXSTARTUPOPERATION_H

#include "DropboxOperation.h"

/**
 * @brief Checks the schema on the remote datastore, and sets it up if it doesn't exist.
 */
class DropboxStartupOperation : public DropboxOperation
{
    Q_OBJECT
    
    enum StartupState {
        INITIALIZED,
        GET_OR_CREATE
    };
    
public:
    explicit DropboxStartupOperation(OperationManager *parent);
    
public slots:
    virtual void execute();
    
protected slots:
    virtual void onResponse(QJsonDocument& doc);
    
private:
    StartupState state;
};

#endif // DROPBOXSTARTUPOPERATION_H
