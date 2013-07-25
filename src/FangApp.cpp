#include "FangApp.h"
#include <QDebug>
#include "operations/UpdateFeedOperation.h"

FangApp::FangApp(QObject *parent, QmlApplicationViewer* viewer) :
    QObject(parent),
    viewer(viewer),
    manager(this)
{
}


ListModel* FangApp::createFeedList() {
    ListModel *model = new ListModel(new FeedItem, this);
  
  {
      QString title("All News");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com/blog/feed/");// TODO QUrl url("");
      QUrl imageUrl("");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, model));
  }
  {
      QString title("MrEricSir.com");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com/blog/feed/");
      QUrl imageUrl("http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, model));
  }
  
  {
      QString title("Ars Technica");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://feeds.arstechnica.com/arstechnica/index");
      QUrl imageUrl("http://static.arstechnica.net/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, model));
  }
  
  return model;
}

void FangApp::init()
{
    // Load the feed list.
    feedList = createFeedList();
    
    viewer->rootContext()->setContextProperty("feedListModel", feedList);
    viewer->addImportPath(QLatin1String("modules"));
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer->showExpanded();
    
    // Update each feed.
    int i = 0;
    while(i < feedList->rowCount()) {
        FeedItem* feed = getFeed(i);
        if (feed == NULL)
            break;
        
        manager.add(new UpdateFeedOperation(&manager, feed));
        
        i++;
    }
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

