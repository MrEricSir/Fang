#ifndef FANGAPP_H
#define FANGAPP_H

#include <QObject>
#include <QDeclarativeContext>

#include "qmlapplicationviewer/qmlapplicationviewer.h"

#include "models/NewsItem.h"
#include "models/FeedItem.h"
#include "models/ListModel.h"
#include "parser/Parser.h"

class FangApp : public QObject
{
    Q_OBJECT
public:
    explicit FangApp(QObject *parent, QmlApplicationViewer* viewer);
    
    void init();
    
signals:
    
public slots:
    void onFeedFinished();
    
private:
    ListModel *createNewsModel();
    ListModel *createFeed();
    
    QmlApplicationViewer* viewer;
    Parser parser;
    ListModel* newsModels[3];
};

#endif // FANGAPP_H
