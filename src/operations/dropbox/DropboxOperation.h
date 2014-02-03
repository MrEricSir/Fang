#ifndef DROPBOXOPERATION_H
#define DROPBOXOPERATION_H

#include "../DBOperation.h"
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>

/**
 * Base class for all DropBox operations.
 */
class DropboxOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit DropboxOperation(PriorityLevel priority, QObject *parent);
    
protected slots:
    
    // Sets the global access token.
    static void setAccessToken(QString token) { _token = token; }
    
    // Returns the global access token.
    static QString getAccessToken() { return _token; }
    
    /**
     * @brief Implementers: this is called when you have a network
     * response to deal with.
     */
    virtual void onResponse(QJsonDocument& doc) =0;
    
    /**
     * @brief For POST queries, this adds a key/value pair.
     * @param key
     * @param value
     */
    void appendPostQuery(const QString& key, const QString& value);
    
    /**
     * @brief Perform a POST with the post query.
     */
    void doPost(QString queryString);
    
    /**
     * @brief Perform a GET request.
     * @param queryString
     */
    void doGet(QString queryString);
    
private slots:
    
    // Returns the network manager.
    QNetworkAccessManager& getManager() { return manager; }
    
    // Called when we got a reply.
    void onNetworkFinished(QNetworkReply* reply);
    
private:
    QNetworkAccessManager manager;
    QUrlQuery postData;
    static QString _token;
};

#endif // DROPBOXOPERATION_H
