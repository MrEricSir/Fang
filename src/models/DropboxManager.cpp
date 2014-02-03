#include "DropboxManager.h"
#include <QDebug>

#include "../operations/dropbox/DropboxLoginOperation.h"
#include "../operations/dropbox/DropboxVerifyToken.h"

DropboxManager::DropboxManager(QQuickItem *parent) :
    QQuickItem(parent),
    manager(NULL)
{
}

void DropboxManager::init(OperationManager *manager)
{
    this->manager = manager;
    
    // Attempt to connect.
    connectAccount();
}

void DropboxManager::login(QString authToken)
{
    qDebug() << "And the token is: " << authToken;
    DropboxLoginOperation* login = new DropboxLoginOperation(manager, authToken);
    connect(login, SIGNAL(finished(Operation*)), this, SLOT(onLoginFinished(Operation*)));
    manager->add(login);
}

void DropboxManager::connectAccount()
{
    // Try logging in.
    DropboxVerifyToken* verify = new DropboxVerifyToken(manager);
    connect(verify, SIGNAL(finished(Operation*)), this, SLOT(onVerifyFinished(Operation*)));
    manager->add(verify);
    
}

void DropboxManager::logout()
{
    
}

void DropboxManager::onLoginFinished(Operation *operation)
{
    DropboxOperation* dbOp = qobject_cast<DropboxOperation*>(operation);
    Q_ASSERT(dbOp != NULL);
    
    if (dbOp->isError()) {
        qDebug() << "Error on Dropbox login";
        
        return;
    }
    
    // Establish connection and GO!
    connectAccount();
}

void DropboxManager::onVerifyFinished(Operation *operation)
{
    DropboxVerifyToken* dbOp = qobject_cast<DropboxVerifyToken*>(operation);
    Q_ASSERT(dbOp != NULL);
    
    if (dbOp->isError()) {
        qDebug() << "DropboxManager: Unable to connect.";
        
        emit loggedOut();
    } else {
        qDebug() << "DropboxManager: connected!";
        
        emit connected();
    }
}
