#ifndef FANGNETWORKACCESSMANAGER_H
#define FANGNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

/*!
    \brief FangNetworkAccessManager is a network access manager with a disk cache and some
    custom handling to behave more like a web browser.
 */
class FangNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit FangNetworkAccessManager(QObject *parent = nullptr);

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request,
                                         QIODevice *outgoingData = 0);
};

#endif // FANGNETWORKACCESSMANAGER_H
