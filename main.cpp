#include <QApplication>
#include <QFile>
#include "qmlapplicationviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setSource(QUrl("qrc:/qml/Fang/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
