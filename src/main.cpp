#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDateTime>

#if defined(Q_OS_MAC)
#include <QtSvg> // Required for OS X SVG support (yes, really.)
#endif

#include "FangApp.h"

#include "models/FeedValidator.h"
#include "models/FangSettings.h"
#include "models/WebInteractor.h"
#include "models/ListModel.h"
#include "models/OPMLInteractor.h"

#include "network/FangQQmlNetworkAccessManagerFactory.h"

#include "db/DB.h"

#include "FangObject.h"

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
    
    int ret = 0;
    QQmlApplicationEngine engine;
    engine.setNetworkAccessManagerFactory(new FangQQmlNetworkAccessManagerFactory());
    
    // Use a code block to ensure FangApp is deleted.
    {
        FangApp fang(&app, &engine);
        fang.init();
    
        ret = app.exec();
    }
    
    // Make sure the database is shut down.
    delete DB::instance();
    
    FangObject::printRemainingObjects();
    
    return ret;
}
