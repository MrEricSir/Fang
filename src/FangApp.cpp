#include "FangApp.h"
#include <QDebug>

FangApp::FangApp(QObject *parent, QmlApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    parser()
{
    for (int i = 0; i < 3; i++) {
        newsModels[i] = new ListModel(new NewsItem, parent);
    }
}


ListModel* FangApp::createFeed() {
    ListModel *model = new ListModel(new FeedItem, parent());
  
  {
      QString title("All News");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("");
      QUrl imageUrl("");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, newsModels[0], model));
  }
  
  {
      QString title("MrEricSir.com");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com");
      QUrl imageUrl("http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, newsModels[1], model));
  }
  
  {
      QString title("Ars Technica");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com");
      QUrl imageUrl("http://static.arstechnica.net/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, newsModels[2], model));
  }
  
  return model;
}

ListModel* FangApp::createNewsModel() {
    QDateTime now;
    QString title("Yo mamma");
    QString author("Eric G");
    QString description("asdflkjas dfl;kjasdf ;alskdfj a;lskdfj als;dkfjasdflkjas df");
    QUrl url("http://www.google.com");
    ListModel *model = new ListModel(new NewsItem, parent());
    model->appendRow(new NewsItem(title, author, description, now, url, model));
    return model;
}

void FangApp::init()
{
    viewer->rootContext()->setContextProperty("feedListModel", createFeed());
    viewer->addImportPath(QLatin1String("modules"));
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer->showExpanded();
    
    // Parse our first feed.
    parser.parse(QUrl("http://www.mrericsir.com/blog/feed/"));
    QObject::connect(&parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
}

void FangApp::onFeedFinished()
{
    RawFeed* rawFeed = parser.getFeed();
    if (rawFeed == NULL) {
        qDebug() << "Raw feed was null :(";
        return;
    }
    
    qDebug() << "Num items" << rawFeed->items.size();
    
    RawNews* rawNews;
    foreach(rawNews, rawFeed->items) {
        qDebug() << rawNews->title;
        
        QDateTime now;
        newsModels[0]->appendRow(new NewsItem(rawNews->title, rawNews->author, rawNews->description, now, rawNews->url, parent()));
    }
    
}
