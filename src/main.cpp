#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QDeclarativeContext>

#include "FangApp.h"

#include "models/FangWebView.h"
#include "models/FangFeedSelection.h"
#include "qmlapplicationviewer/qmlapplicationviewer.h"


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qmlRegisterType<QDeclarativeWebView>("Fang", 1, 0, "FangWebView");
    qmlRegisterType<FangFeedSelection>("Fang", 1, 0, "FangFeedSelection");
    
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    
    QmlApplicationViewer viewer;
    
    FangApp fang(app.data(), &viewer);
    fang.init();
    
    return app->exec();
}
