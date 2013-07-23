#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QDeclarativeContext>

#include "FangApp.h"

#include "qmlapplicationviewer/qmlapplicationviewer.h"


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    
    QmlApplicationViewer viewer;
    
    FangApp fang(app.data(), &viewer);
    fang.init();
    
    return app->exec();
}
