#include "FangQQmlNetworkAccessManagerFactory.h"
#include "FangNetworkAccessManager.h"

FangQQmlNetworkAccessManagerFactory::FangQQmlNetworkAccessManagerFactory() :
    QQmlNetworkAccessManagerFactory()
{
}

QNetworkAccessManager* FangQQmlNetworkAccessManagerFactory::create(QObject* parent)
{
    return new FangNetworkAccessManager(parent);
}
