#ifndef DROPBOXMANAGER_H
#define DROPBOXMANAGER_H

#include <QQuickItem>
#include <QObject>
#include "../operations/OperationManager.h"
#include "../DropboxConstants.h"

// These are special and MUST NEVER BE CHANGED OMG
#define CONNECTED_STATE_CONNECTING "connecting"
#define CONNECTED_STATE_CONNECTED  "connected"
#define CONNECTED_STATE_LOGOUT     "logout"
#define CONNECTED_STATE_OFFLINE    "offline"

/**
 * @brief Handles Dropbox QML duties and waits for incoming requests from Dropbox.
 */
class DropboxManager : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(DropboxManager)
    
    // QML monitors changes in this string to know what to do with Dropbox GUIs.
    Q_PROPERTY(QString connectedState READ connectedState NOTIFY connectedStateChanged)
    
public:
    explicit DropboxManager(QQuickItem *parent = 0);
    virtual ~DropboxManager() {}
    
signals:
    
    // Reports changes in the connection state.
    void connectedStateChanged();
    
public slots:
    // Initializes the Dropbox manager.
    void init(OperationManager* manager);
    
    // Logs in with the provided token.  
    Q_INVOKABLE void login(QString authToken);
    
    // Connects to the server with the existing token, if any.
    Q_INVOKABLE void connectAccount();
    
    // Logs out.
    Q_INVOKABLE void logout();
    
    // Returns the Dropbox client code for Fang.
    Q_INVOKABLE QString getClientCode() { return DROPBOX_CLIENT_CODE; }
    
    QString connectedState() { return _connectedState; }
    
private slots:
    
    void setConnectedState(QString state);
    
    void onLoginFinished(Operation* operation);
    void onLogoutFinished(Operation* operation);
    void onVerifyFinished(Operation* operation);
    void onStartupFinished(Operation* operation);
    
private:
    OperationManager* manager;
    QString _connectedState;
};

QML_DECLARE_TYPE(DropboxManager)

#endif // DROPBOXMANAGER_H
