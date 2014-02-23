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
    doPost("datastores/get_or_create_datastore");
}

void DropboxStartupOperation::onResponse(QJsonDocument &doc)
{
    Q_ASSERT(state != INITIALIZED);
    
    if (GET_OR_CREATE == state) {
        // Should get response like this:
        // {"handle": "1PuUJ3DvMI71OYx1gcqWHzzdva2EpF", "rev": 0, "created": true}
        
        QJsonObject root = doc.object();
        QJsonValue jsonHandle = root.value(QString("handle"));
        QJsonValue jsonRev = root.value(QString("rev"));
        QJsonValue jsonCreated = root.value(QString("created"));
        
        if (!jsonHandle.isString() || !jsonRev.isDouble() || !jsonCreated.isBool()) {
            reportError("Invalid DropBox get or create response!");
            
            return;
        }
        
        QString handle = jsonHandle.toString();
        setDatastoreHandle(handle);
        int rev = jsonRev.toInt();
        bool created = true; //jsonCreated.toBool();
        
        if (created || rev == 0) {
            // If this is your first time at Fang Club, you have to Fang.  Everbody Fang Chung Tonight.
            //
            // Okay, so we've got a brand new datastore, yay!  Fill it out with all our existing data.
            appendPostQuery("dsid", "default");
            doPost("datastores/put_delta");
        } else {
            //
            // MAJOR TODO:
            
            // We need to grab all the changes from the remote datastore, and also apply any changes that were made
            // since the user last connected to Dropbox.
            
            // If there are locally pending changes, we need to apply those.
            
            // If there are remote changes, we need to apply those too.
            
            // Use the newly available getOperationManger() method to invoke a new operation that reads a datastore thingie delta
        }
    }
}
