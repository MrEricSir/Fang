#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QDeclarativeContext>

#include "qmlapplicationviewer/qmlapplicationviewer.h"

#include "FangApp.h"

#include "models/MouseWheelArea.h"
#include "models/FeedValidator.h"
#include "models/FangApplicationViewer.h"
#include "models/FangSettings.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qmlRegisterType<MouseWheelArea>("Fang", 1, 0, "MouseWheelArea");
    qmlRegisterType<FeedValidator>("Fang", 1, 0, "FeedValidator");
    qmlRegisterType<FangSettings>("Fang", 1, 0, "FangSettings");
    
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    app->setOrganizationName("EricSoft");
    app->setOrganizationDomain("EricSoft.com");
    app->setApplicationName("Fang");
    
    FangApplicationViewer viewer;
    FangApp fang(app.data(), &viewer);
    fang.init();
    
    return app->exec();
}
