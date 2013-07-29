#ifndef ADDFEEDOPERATION_H
#define ADDFEEDOPERATION_H

#include "DBOperation.h"

#include <QUrl>
#include <QString>
#include <QDebug>

#include "../models/ListModel.h"
#include "../parser/Parser.h"

class AddFeedOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit AddFeedOperation(QObject *parent, ListModel *feedList, const QUrl &feedURL,
                              const QUrl &imageURL, QString siteTitle);
    
signals:
    
public slots:
    virtual void execute();
    
private slots:
    void onFeedFinished();
    
private:
    ListModel *feedList;
    QUrl feedURL;
    QUrl imageURL;
    QString siteTitle;
    
    Parser parser;
};

#endif // ADDFEEDOPERATION_H
