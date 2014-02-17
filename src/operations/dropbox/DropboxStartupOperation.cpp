#include "DropboxStartupOperation.h"

DropboxStartupOperation::DropboxStartupOperation(OperationManager *parent) :
    DropboxOperation(IMMEDIATE, parent),
    state(INITIALIZED)
{
}

void DropboxStartupOperation::execute()
{
    state = GET_OR_CREATE;
    appendPostQuery("dsid", "default");
    doPost("/datastores/get_or_create_datastore");
}

void DropboxStartupOperation::onResponse(QJsonDocument &doc)
{
    Q_ASSERT(state != INITIALIZED);
    
    if (GET_OR_CREATE == state) {
        
    }
}
