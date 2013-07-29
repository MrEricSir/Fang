#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QDeclarativeContext>

#include "qmlapplicationviewer/qmlapplicationviewer.h"

#include "FangApp.h"

#include "models/FangWebView.h"
#include "models/MouseWheelArea.h"
#include "models/FeedValidator.h"



Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qmlRegisterType<QDeclarativeWebView>("Fang", 1, 0, "FangWebView");
    qmlRegisterType<MouseWheelArea>("Fang", 1, 0, "MouseWheelArea");
    qmlRegisterType<FeedValidator>("Fang", 1, 0, "FeedValidator");
    
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    
    QmlApplicationViewer viewer;
    
    FangApp fang(app.data(), &viewer);
    fang.init();
    
    return app->exec();
}
