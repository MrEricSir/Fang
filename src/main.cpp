#include <QApplication>
#include <QFile>
#include <QDateTime>

#include "qtquick2applicationviewer/qtquick2applicationviewer.h"

#include "FangApp.h"

#include "models/FeedValidator.h"
#include "models/FangApplicationViewer.h"
#include "models/FangSettings.h"
#include "models/WebInteractor.h"
#include "models/ListModel.h"
#include "models/OPMLInteractor.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qmlRegisterType<FeedValidator>("Fang", 1, 0, "FeedValidator");
    qmlRegisterType<FangSettings>("Fang", 1, 0, "FangSettings");
    qmlRegisterType<WebInteractor>("Fang", 1, 0, "WebInteractor");
    qmlRegisterType<ListItem>("Fang", 1, 0, "ListItem");
    qmlRegisterType<OPMLInteractor>("Fang", 1, 0, "OPMLInteractor");
    
    QApplication app(argc, argv);
    app.setOrganizationName("EricSoft");
    app.setOrganizationDomain("EricSoft.com");
    app.setApplicationName("Fang");
    
    FangApplicationViewer viewer;
    FangApp fang(&app, &viewer);
    fang.init();
    
    return app.exec();
}
