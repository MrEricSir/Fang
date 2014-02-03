#ifndef DROPBOXMANAGER_H
#define DROPBOXMANAGER_H

#include <QQuickItem>
#include <QObject>
#include "../operations/OperationManager.h"
#include "../DropboxConstants.h"


class DropboxManager : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(DropboxManager)
    
public:
    explicit DropboxManager(QQuickItem *parent = 0);
    virtual ~DropboxManager() {}
    
signals:
    
    /**
     * @brief Huzzah, we're connected!
     */
    void connected();
    
    /**
     * @brief Fired when we discover that we're not logged in, either at startup or after
     * a manual logout.
     */
    void loggedOut();
    
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
    
private slots:
    
    void onLoginFinished(Operation* operation);
    void onVerifyFinished(Operation* operation);
    
private:
    OperationManager* manager;
};

QML_DECLARE_TYPE(DropboxManager)

#endif // DROPBOXMANAGER_H
