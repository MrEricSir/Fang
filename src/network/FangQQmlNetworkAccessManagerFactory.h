#ifndef FANGQQMLNETWORKACCESSMANAGERFACTORY_H
#define FANGQQMLNETWORKACCESSMANAGERFACTORY_H

#include <QQmlNetworkAccessManagerFactory>

class FangQQmlNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory 
{
public:
    explicit FangQQmlNetworkAccessManagerFactory();
    
    /**
     * Dis is vere we make ze netvork access maneyjurs for ze QtQuick.
     */
    virtual QNetworkAccessManager *create(QObject *parent);
    
signals:
    
public slots:
    
};

#endif // FANGQQMLNETWORKACCESSMANAGERFACTORY_H
