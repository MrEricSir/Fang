#ifndef BROWSERNETWORKACCESSMANAGER_H
#define BROWSERNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

/*!
    \brief BrowserNetworkAccessManager is a network access manager with a disk cache and some
    custom handling to behave more like a web browser.
 */
class BrowserNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit BrowserNetworkAccessManager(QObject *parent = nullptr);

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request,
                                         QIODevice *outgoingData = 0);
};

#endif // BROWSERNETWORKACCESSMANAGER_H
