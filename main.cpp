#include <QApplication>
#include <QFile>
#include "qmlapplicationviewer.h"
#include "NewsItem.h"
#include "FeedItem.h"
#include "ListModel.h"
#include <QDateTime>
#include <QDeclarativeContext>

QDateTime now;
QString title("Yo mamma");
QString author("Eric G");
QString description("asdflkjas dfl;kjasdf ;alskdfj a;lskdfj als;dkfjasdflkjas df");
QUrl url("http://www.google.com");


ListModel* createNewsModel() {
  ListModel *model = new ListModel(new NewsItem, qApp);
  model->appendRow(new NewsItem(title, author, description, now, url, model));
  return model;
}


ListModel* createFeed() {
  ListModel *model = new ListModel(new FeedItem, qApp);
  
  {
      QString title("All News");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("");
      QUrl imageUrl("");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, createNewsModel(), model));
  }
  
  {

      QString title("MrEricSir.com");
      QString subtitle("");
      QDateTime lastUpdated;
      quint32 minUpdate = 0;
      QUrl url("http://www.mrericsir.com");
      QUrl imageUrl("http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico");
      
      model->appendRow(new FeedItem(title, subtitle, lastUpdated, minUpdate, url, imageUrl, createNewsModel(), model));
  }
  
  return model;
}


 

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("feedListModel", createFeed());
    //viewer.rootContext()->setContextProperty("newsListModel", createModel());
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
