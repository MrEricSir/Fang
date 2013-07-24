#include "FangApp.h"
#include <QDebug>

FangApp::FangApp(QObject *parent, QmlApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    parser()
{
//    for (int i = 0; i < 3; i++) {
//        newsModels[i] = new ListModel(new NewsItem, parent);
//    }
    
    feedList = createFeedList();
}


ListModel* FangApp::createFeedList() {
    ListModel *model = new ListModel(new FeedItem, parent());
  
  {
      QString title("All News");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("");
      QUrl imageUrl("");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, model));
  }
  
  {
      QString title("MrEricSir.com");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com");
      QUrl imageUrl("http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, model));
  }
  
  {
      QString title("Ars Technica");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com");
      QUrl imageUrl("http://static.arstechnica.net/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, model));
  }
  
  return model;
}

//ListModel* FangApp::createNewsModel() {
//    QDateTime now;
//    QString title("Yo mamma");
//    QString author("Eric G");
//    QString description("asdflkjas dfl;kjasdf ;alskdfj a;lskdfj als;dkfjasdflkjas df");
//    QUrl url("http://www.google.com");
//    ListModel *model = new ListModel(new NewsItem, parent());
//    model->appendRow(new NewsItem(title, author, description, now, url, model));
//    return model;
//}

void FangApp::init()
{
    viewer->rootContext()->setContextProperty("feedListModel", feedList);
    viewer->addImportPath(QLatin1String("modules"));
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer->showExpanded();
    
    // Parse our first feed.
    parser.parse(QUrl("http://www.mrericsir.com/blog/feed/"));
    QObject::connect(&parser, SIGNAL(finished()), this, SLOT(onFeedFinished()));
}

FeedItem* FangApp::getFeed(int index) {
    void* item = feedList->row(index);
    if (item == NULL) {
        qDebug() << "Feed #" << index << " was NULL";
        
        return NULL;
    }
                                //.data();
    return (FeedItem*) item;
}

QString FangApp::htmlifyContent(const QString& content) {
    return "<html><body>" + content + "</body></html>";
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
        {
        FeedItem* feed = getFeed(0); 
        if (feed == NULL)
            qDebug() << "Feed was null!";
        
        feed->getNewsList()->appendRow(
                    new NewsItem(feed, rawNews->title, rawNews->author, rawNews->description, now, 
                                 rawNews->url, feed->getNewsList()));
        }
        
        // And do it again!
        {
        FeedItem* feed = getFeed(1); 
        if (feed == NULL)
            qDebug() << "Feed was null!";
        
        feed->getNewsList()->appendRow(
                    new NewsItem(feed, rawNews->title, rawNews->author, 
                                 htmlifyContent(rawNews->content != "" ? rawNews->content : rawNews->description),
                                 now, rawNews->url, feed->getNewsList()));
        }
    }
    
}
