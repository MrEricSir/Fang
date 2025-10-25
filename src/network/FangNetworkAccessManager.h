#ifndef FANGNETWORKACCESSMANAGER_H
#define FANGNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

/**
 * @brief Handle caching, web server fixups, etc.
 */
class FangNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit FangNetworkAccessManager(QObject *parent = nullptr);
    
signals:
    
public slots:
    
protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request,
                                         QIODevice *outgoingData = 0);
    
};

#endif // FANGNETWORKACCESSMANAGER_H
