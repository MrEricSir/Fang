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
    
    // Returns the feed for the given index from 0..feedCount
    FeedItem *getFeed(int index);
    
signals:
    
public slots:
    void onFeedFinished();
    
    inline int feedCount() { return feedList->rowCount(); }
    
private:
    //ListModel *createNewsModel();
    ListModel *createFeedList();
    
    QString htmlifyContent(const QString &content);
    
    QmlApplicationViewer* viewer;
    Parser parser;
    ListModel *feedList;
    ListModel* newsModels[3];
};

#endif // FANGAPP_H
