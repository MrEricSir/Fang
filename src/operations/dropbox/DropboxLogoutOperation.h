#ifndef DROPBOXLOGOUTOPERATION_H
#define DROPBOXLOGOUTOPERATION_H

#include "DropboxOperation.h"
#include <QObject>

class DropboxLogoutOperation : public DropboxOperation
{
    Q_OBJECT
public:
    explicit DropboxLogoutOperation(QObject *parent);
    
signals:
    
public slots:
    virtual void execute();
    
protected slots:
    virtual void onResponse(QJsonDocument& doc);
    
};

#endif // DROPBOXLOGOUTOPERATION_H
