#include "FangQQmlNetworkAccessManagerFactory.h"
#include "BrowserNetworkAccessManager.h"

FangQQmlNetworkAccessManagerFactory::FangQQmlNetworkAccessManagerFactory() :
    QQmlNetworkAccessManagerFactory()
{
}

QNetworkAccessManager* FangQQmlNetworkAccessManagerFactory::create(QObject* parent)
{
    return new BrowserNetworkAccessManager(parent);
}
