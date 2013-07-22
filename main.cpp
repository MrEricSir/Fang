#include <QApplication>
#include <QFile>
#include "qmlapplicationviewer.h"
#include "FeedItem.h"
#include "ListModel.h"
#include <QDateTime>
#include <QDeclarativeContext>

QDateTime now;
QString title("Yo mamma");
QString author("Eric G");
QString description("asdflkjas dfl;kjasdf ;alskdfj a;lskdfj als;dkfjasdflkjas df");
QUrl url("http://www.google.com");

ListModel* createModel() {
  ListModel *model = new ListModel(new FeedItem, qApp);
  model->appendRow(new FeedItem(title, author, description, now, url, model));
  return model;
}
 

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("feedModel",  createModel());
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
