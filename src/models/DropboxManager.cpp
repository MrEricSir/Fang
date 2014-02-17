#include "DropboxManager.h"
#include <QDebug>

#include "../operations/dropbox/DropboxLoginOperation.h"
#include "../operations/dropbox/DropboxLogoutOperation.h"
#include "../operations/dropbox/DropboxVerifyToken.h"
#include "../operations/dropbox/DropboxStartupOperation.h"

DropboxManager::DropboxManager(QQuickItem *parent) :
    QQuickItem(parent),
    manager(NULL),
    _connectedState(CONNECTED_STATE_CONNECTING)
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
    qDebug() << "Logging out!";
    DropboxLogoutOperation* logout = new DropboxLogoutOperation(manager);
    connect(logout, SIGNAL(finished(Operation*)), this, SLOT(onLogoutFinished(Operation*)));
    manager->add(logout);
}

void DropboxManager::setConnectedState(QString state)
{
    if (state == _connectedState)
        return;
    
    
    _connectedState = state;
    emit connectedStateChanged();
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

void DropboxManager::onLogoutFinished(Operation *operation)
{
    DropboxOperation* dbOp = qobject_cast<DropboxOperation*>(operation);
    Q_ASSERT(dbOp != NULL);
    
    if (dbOp->isError()) {
        qDebug() << "Error logging out!";
        
        return;
    }
    
    setConnectedState(CONNECTED_STATE_LOGOUT);
}

void DropboxManager::onVerifyFinished(Operation *operation)
{
    DropboxVerifyToken* dbOp = qobject_cast<DropboxVerifyToken*>(operation);
    Q_ASSERT(dbOp != NULL);
    
    if (dbOp->isError()) {
        qDebug() << "DropboxManager: Unable to connect.";
        
        // TODO: determine if it's because we're offline
        
        setConnectedState(CONNECTED_STATE_LOGOUT);
    } else {
        qDebug() << "DropboxManager: connected!";
        
        // Whohoo! We're there, y'all!
        setConnectedState(CONNECTED_STATE_CONNECTED);
        
        // Do the startup tasks like, checking if the remote is initialized and other stuff-esque junk.
        DropboxStartupOperation* startup = new DropboxStartupOperation(manager);
        connect(startup, SIGNAL(finished(Operation*)), this, SLOT(onStartupFinished(Operation*)));
        manager->add(startup);
    }
}

void DropboxManager::onStartupFinished(Operation *operation)
{
    DropboxVerifyToken* dbOp = qobject_cast<DropboxVerifyToken*>(operation);
    Q_ASSERT(dbOp != NULL);
    
    if (dbOp->isError()) {
        qDebug() << "DropboxManager: Unable to do the whole startup shebang.";
        setConnectedState(CONNECTED_STATE_LOGOUT);
        
        return;
    }
    
    
    
    //
    // MAJOR ASS TODO: get started with the change-checker thingie
    //
}
